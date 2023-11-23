function pesto.init()
    -- Pesto modules
    require("pesto.filesystem")
    require("pesto.graphics")
    require("pesto.log")
    require("pesto.mouse")
    require("pesto.window")

    -- Lua libraries
    pesto.astar = require("astar")
    pesto.Vector = require("brinevector")
    pesto.collision = require("bump")
    pesto.Object = require("classic")
    pesto.tween = require("flux")
    pesto.inspect = require("inspect")
    pesto.json = require("json")
    pesto.util = require("lume")
    pesto.signal = require("signal")
    pesto.timer = require("tick")
    pesto.ecs = require("tiny")

    -- Luasocket is left as is for now

    local directory = arg[1]

    if not directory then
        error("No directory specified!")
    end

    if not pesto.filesystem.directoryExists(directory) then
        error("Directory does not exist!")
    end

    if pesto.filesystem.fileExists("luacheck.exe") then
        local handle = io.popen("luacheck.exe " .. directory)
        local output = handle:read("*a")
        handle:close()

        local warnings, errors, message = output:match("Total: (%d+) warning?s? / (%d+) error?s?")

        if warnings or errors then
            error(output)
        end
    end

    package.path = package.path .. ";" .. directory .. "/?.lua"

    if pesto.filesystem.fileExists(directory .. "/main.lua") then
        -- Initializing window here to allow loading textures

        pesto.log.level("warn") -- Disable raylib's wall of info logs :)

        local major, minor, patch, codename = pesto.getVersion()

        pesto.window.init(800, 600, "Pesto " .. major .. "." .. minor .. "." .. patch .. " " .. codename)
        pesto.window.setTargetFPS(60)

        pesto.log.level("info")

        require("main")
    else
        error("No main.lua found!")
    end
end

function pesto.run()
    while not pesto.window.shouldClose() do
        local dt = pesto.window.getDelta()

        pesto.tween.update(dt)
        pesto.timer.update(dt)

        if pesto.update then pesto.update(dt) end

        pesto.window.beginDrawing()

        pesto.graphics.clear()

        if pesto.draw then pesto.draw() end

        pesto.window.endDrawing()
    end

    pesto.log.level("warn")

    pesto.window.close()
end

local function errorHandler(msg)
    pesto.log.error(msg)

    if not pesto.window.isReady() then
        pesto.log.level("warn")

        local major, minor, patch, codename = pesto.getVersion()

        pesto.window.init(800, 600, "Pesto " .. major .. "." .. minor .. "." .. patch .. " " .. codename)
        pesto.window.setTargetFPS(60)

        pesto.log.level("info")
    end

    while not pesto.window.shouldClose() do
        pesto.window.beginDrawing()

        pesto.graphics.clear(119, 173, 120)

        pesto.graphics.text("Error: " .. msg, 10, 10)

        pesto.window.endDrawing()
    end

    pesto.log.level("warn")

    pesto.window.close()
end

return function()
    local result = xpcall(pesto.init, errorHandler)
    if not result then return 1 end
    local result, retval = xpcall(pesto.run, errorHandler)
    if not result then return 1 end

    return tonumber(retval) or 0
end
