-- Hot reload implementation based on rxi's lurker <3
local reload = {}

local callbacks = { "update", "draw", "gui", "quit" }

function reload.init()
    reload.path = "."
    reload.preswap = function() end
    reload.postswap = function() end
    reload.interval = 0.5
    reload.timer = 0
    reload.lasterrorfile = nil
    reload.files = {}
    reload.funcwrappers = {}
    reload.pestofuncs = {}
    reload.state = "init"

    pesto.util.each(reload.getchanged(), reload.resetfile)
end

function reload.initwrappers()
    for _, v in pairs(callbacks) do
        reload.funcwrappers[v] = function(...)
            local args = { ... }

            xpcall(function()
                return reload.pestofuncs[v] and reload.pestofuncs[v](unpack(args))
            end, reload.onerror)
        end

        reload.pestofuncs[v] = pesto[v]
    end

    reload.updatewrappers()
end

function reload.updatewrappers()
    for _, v in pairs(callbacks) do
        if pesto[v] ~= reload.funcwrappers[v] then
            reload.pestofuncs[v] = pesto[v]
            pesto[v] = reload.funcwrappers[v]
        end
    end
end

function reload.onerror(e)
    reload.state = "error"

    for _, v in pairs(callbacks) do
        pesto[v] = function() end
    end

    pesto.update = reload.update

    local trace = debug.traceback()
    local err = {}

    table.insert(err, "Error\n")
    table.insert(err, e .. "\n\n")

    for l in string.gmatch(trace, "(.-)\n") do
        if not string.match(l, "boot.lua") then
            l = string.gsub(l, "stack traceback:", "Traceback\n")
            table.insert(err, l)
        end
    end

    local p = table.concat(err, "\n")

    p = string.gsub(p, "\t", "")
    p = string.gsub(p, "%[string \"(.-)\"%]", "%1")

    pesto.draw = function()
        pesto.graphics.clear(50, 59, 79, 255)

        pesto.graphics.setColor(255, 255, 255)

        pesto.graphics.text(p, 70, 70)
    end
end

function reload.exitinitstate()
    reload.state = "normal"
    reload.initwrappers()
end

function reload.exiterrorstate()
    reload.state = "normal"

    for _, v in pairs(callbacks) do
        pesto[v] = reload.funcwrappers[v]
    end
end

function reload.update(dt)
    if reload.state == "init" then
        reload.exitinitstate()
    end

    reload.timer = reload.timer + dt

    if reload.timer > reload.interval then
        reload.timer = 0

        local changed = reload.scan()

        if #changed > 0 and reload.lasterrorfile then
            local f = reload.lasterrorfile
            reload.lasterrorfile = nil
            reload.hotswapfile(f)
        end
    end
end

function reload.getchanged()
    local function fn(f)
        return reload.files[f] ~= pesto.filesystem.getLastModified(f)
    end

    return pesto.util.filter(pesto.filesystem.getDirectoryItems(reload.path, ".lua", true), fn)
end

function reload.modname(f)
    return (f:gsub("%.lua$", ""):gsub("[/\\]", "."))
end

function reload.resetfile(f)
    reload.files[f] = pesto.filesystem.getLastModified(f)
end

function reload.hotswapfile(f)
    pesto.log.debug("Hotswapping " .. f)

    if reload.state == "error" then
        reload.exiterrorstate()
    end

    if reload.preswap(f) then
        pesto.log.debug("Hotswap of " .. f .. " aborted by preswap")
        reload.resetfile(f)

        return
    end

    local modname = reload.modname(f)
    local t, ok, err = pesto.util.time(pesto.util.hotswap, modname)

    if ok then
        pesto.log.debug("Swapped " .. f .. " in " .. string.format("%.3f", t) .. " seconds")
    else
        pesto.log.debug("Failed to swap " .. f .. " : " .. err)

        reload.lasterrorfile = f
        reload.onerror(err)
        reload.resetfile(f)

        return
    end

    reload.resetfile(f)
    reload.postswap(f)

    reload.updatewrappers()
end

function reload.scan()
    if reload.state == "init" then
        reload.exitinitstate()
    end

    local changed = reload.getchanged()
    pesto.util.each(changed, reload.hotswapfile)

    return changed
end

return reload
