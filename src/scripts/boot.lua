function pesto.init()
    -- Pesto modules
    require("pesto.filesystem")
    require("pesto.gamepad")
    require("pesto.graphics")
    require("pesto.keyboard")
    require("pesto.log")
    require("pesto.math")
    require("pesto.mouse")
    require("pesto.system")
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

    -- Scripts
    pesto.state = require("pesto.state")
    pesto.reload = require("pesto.reload")
    pesto.animation = require("pesto.animation")

    -- Debug
    pesto.debug = true

    local target = arg[1]
    local tempDir = os.getenv("TEMP")
    local luacheckPath = tempDir .. "\\luacheck.exe"

    if not target then
        error("No target specified!")
    end

    local file = pesto.filesystem.fileExists(target)
    local directory = pesto.filesystem.directoryExists(target)

    if not file and not directory then
        error("Target does not exist!")
    end

    if file and directory then
        file = false
    end

    if file and not pesto.filesystem.isFileExtension(target, ".lua") then
        error("Target is not a lua file!")
    end

    if directory and not pesto.filesystem.fileExists(target .. "/main.lua") then
        error("No main.lua found!")
    end

    if tempDir and pesto.filesystem.fileExists(luacheckPath) then
        local handle = io.popen(luacheckPath .. " " .. target .. " --globals pesto")
        local output = handle:read("*a")
        handle:close()

        local warnings, errors, message = output:match("Total: (%d+) warning?s? / (%d+) error?s?")

        if tonumber(warnings) > 0 then
            pesto.log.warn(output)
        end

        if tonumber(errors) > 0 then
            error(output)
        end
    end

    pesto.log.level("warn") -- Disable raylib's wall of info logs :)

    local major, minor, patch, codename = pesto.getVersion()

    pesto.window.init(800, 600, "Pesto " .. major .. "." .. minor .. "." .. patch .. " " .. codename)

    pesto.window.setTargetFPS(60)

    if pesto.debug then
        pesto.log.level("debug")
        pesto.reload.init()
        pesto.log.debug("Running in debug mode")
    else
        pesto.log.level("info")
    end

    if file then
        local path = pesto.filesystem.getDirectoryPath(target)

        package.path = package.path .. ";" .. path .. "/?.lua"

        pesto.filesystem.changeDirectory(path)

        require(pesto.filesystem.getFileNameWithoutExt(target))
    elseif directory then
        package.path = package.path .. ";" .. target .. "/?.lua"

        pesto.filesystem.changeDirectory(target)

        require("main")
    end
end

function pesto.run()
    while not pesto.window.shouldClose() do
        local dt = pesto.window.getDelta()

        if pesto.debug then
            pesto.reload.update(dt)
        end

        pesto.tween.update(dt)
        pesto.timer.update(dt)

        if pesto.update then pesto.update(dt) end

        pesto.window.beginDrawing()

        pesto.graphics.clear(0, 0, 0, 255)

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

        pesto.graphics.clear(119, 173, 120, 255)

        pesto.graphics.text("Error", 10, 10)
        pesto.graphics.wrappedText(msg .. "\n\n" .. debug.traceback(), 10, 50, pesto.window.getWidth(), pesto.window.getHeight())

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
