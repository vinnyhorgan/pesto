-- Hot reload implementation inspired by rxi's lurker
local reload = {}

function reload.init()
    reload.path = "."
    reload.preswap = function() end
    reload.postswap = function() end
    reload.interval = 0.5
    reload.timer = 0
    reload.files = {}

    pesto.util.each(reload.getchanged(), reload.resetfile)
end

function reload.update(dt)
    reload.timer = reload.timer + dt

    if reload.timer > reload.interval then
        reload.timer = 0

        local changed = reload.getchanged()
        pesto.util.each(changed, reload.hotswapfile)
    end
end

function reload.getchanged()
    local function fn(f)
        return reload.files[f] ~= pesto.filesystem.getFileModTime(f)
    end

    return pesto.util.filter(pesto.filesystem.loadDirectoryFilesEx(reload.path, ".lua", true), fn)
end

function reload.resetfile(f)
    reload.files[f] = pesto.filesystem.getFileModTime(f)
end

function reload.hotswapfile(f)
    pesto.log.debug("Hotswapping " .. f)

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
    end

    reload.resetfile(f)
    reload.postswap(f)
end

function reload.modname(f)
    return (f:gsub("%.lua$", ""):gsub("[/\\]", "."))
end

return reload
