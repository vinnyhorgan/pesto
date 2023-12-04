-- Config
local config = {
    debug = true,
    version = "0.1",
    title = "Pesto",
    width = 800,
    height = 600,
    resizable = true,
    letterbox = true,
    gameWidth = 800,
    gameHeight = 600,
    borderColor = { 119, 173, 120, 255 }
}

function pesto.init()
    -- Pesto modules
    require("pesto.audio")
    require("pesto.filesystem")
    require("pesto.gamepad")
    require("pesto.graphics")
    require("pesto.gui")
    require("pesto.keyboard")
    require("pesto.log")
    require("pesto.math")
    require("pesto.mouse")
    require("pesto.physics")
    require("pesto.rres")
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
    pesto.ldtk = require("pesto.ldtk")

    local directory = arg[1]

    if not directory then
        error("No directory specified!")
    end

    if not pesto.filesystem.isDirectory(directory) then
        error("Directory does not exist!")
    end

    pesto.filesystem.changeDirectory(directory)

    if not pesto.filesystem.isFile("main.lua") then
        error("No main.lua found!")
    end

    package.path = package.path .. ";" .. directory .. "/?.lua"

    if pesto.filesystem.isFile("conf.lua") then
        require("conf")
    end

    if pesto.conf then pesto.conf(config) end

    local major, minor = pesto.getVersion()

    if config.version ~= major .. "." .. minor then
        pesto.log.warn("Version mismatch!", config.version, major .. "." .. minor)
    end

    pesto.window.init(config.width, config.height, config.title)

    pesto.window.setTargetFPS(60)

    pesto.gui.setup()

    if config.resizable then
        pesto.window.setResizable(true)
    end

    if config.debug then
        pesto.reload.init()
    end

    require("main")
end

function pesto.run()
    local target

    if config.letterbox then
        target = pesto.graphics.loadRenderTexture(config.gameWidth, config.gameHeight)
    end

    while true do
        if pesto.window.shouldClose() then
            if not pesto.quit or not pesto.quit() then
                break
            end
        end

        local scale = math.min(pesto.window.getWidth() / config.gameWidth, pesto.window.getHeight() / config.gameHeight)

        local dt = pesto.window.getDelta()

        if config.debug then
            pesto.reload.update(dt)
        end

        pesto.tween.update(dt)
        pesto.timer.update(dt)

        if pesto.update then pesto.update(dt) end

        if config.letterbox then
            pesto.graphics.beginTextureMode(target)

            pesto.graphics.clear(0, 0, 0, 255)

            if pesto.draw then pesto.draw() end

            pesto.graphics.endTextureMode()
        end

        pesto.window.beginDrawing()

        pesto.graphics.clear(config.borderColor[1], config.borderColor[2], config.borderColor[3], config.borderColor[4])

        if config.letterbox then
            pesto.graphics.drawRenderTexturePro(target, 0, 0, config.gameWidth, -config.gameHeight,
                (pesto.window.getWidth() - (config.gameWidth * scale)) * 0.5,
                (pesto.window.getHeight() - (config.gameHeight * scale)) * 0.5,
                config.gameWidth * scale, config.gameHeight * scale, 0, 0, 0)
        else
            pesto.graphics.clear(0, 0, 0, 255)

            if pesto.draw then pesto.draw() end
        end

        pesto.gui.beginDrawing()

        pesto.gui.demo()

        pesto.gui.endDrawing()

        pesto.window.endDrawing()
    end

    pesto.gui.shutdown()

    pesto.window.close()
end

function pesto.errhand(msg)
    pesto.log.error(msg)

    if not pesto.window.isReady() then
        pesto.window.init(800, 600, "Pesto Error")
        pesto.window.setTargetFPS(60)
    end

    while not pesto.window.shouldClose() do
        pesto.window.beginDrawing()

        pesto.graphics.clear(119, 173, 120, 255)

        pesto.graphics.text("Error", 10, 10)
        pesto.graphics.wrappedText(msg .. "\n\n" .. debug.traceback(), 10, 50, pesto.window.getWidth(),
            pesto.window.getHeight())

        pesto.window.endDrawing()
    end

    pesto.window.close()
end

return function()
    local result = xpcall(pesto.init, pesto.errhand)
    if not result then return 1 end
    local result, retval = xpcall(pesto.run, pesto.errhand)
    if not result then return 1 end

    return tonumber(retval) or 0
end
