-- Config
local config = {
    debug = true,
    version = "0.1",
    title = "Pesto Project",
    icon = nil,
    width = 800,
    height = 600,
    targetFPS = 60,
    resizable = true,
    minWidth = 1,
    minHeight = 1,
    fullscreen = false,
    letterbox = true,
    letterboxFilter = "point",
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
    require("pesto.imgui")
    require("pesto.keyboard")
    require("pesto.log")
    require("pesto.math")
    require("pesto.mouse")
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

    -- Scripts
    pesto.state = require("pesto.state")
    pesto.reload = require("pesto.reload")
    pesto.animation = require("pesto.animation")
    pesto.ldtk = require("pesto.ldtk")

    local directory = arg[1]

    if directory then
        if not pesto.filesystem.isDirectory(directory) then
            error("Directory does not exist!")
        end

        pesto.filesystem.changeDirectory(directory)

        if pesto.filesystem.isFile("conf.lua") then
            require("conf")

            if pesto.conf then pesto.conf(config) end
        end
    end

    pesto.window.init(config.width, config.height, config.title)
    pesto.window.setTargetFPS(config.targetFPS)

    if config.icon then
        local icon = pesto.graphics.loadTexture(config.icon)
        pesto.window.setIcon(icon)
    end

    pesto.window.setResizable(config.resizable)
    pesto.window.setMinSize(config.minWidth, config.minHeight)

    if config.fullscreen then
        pesto.window.toggleFullscreen()
    end

    pesto.audio.init()
    pesto.imgui.init()

    local major, minor = pesto.getVersion()

    if config.version ~= major .. "." .. minor then
        pesto.log.warn("Version mismatch!")
    end

    if config.debug then
        pesto.reload.init()
    end

    if directory then
        if not pesto.filesystem.isFile("main.lua") then
            error("No main.lua found!")
        end

        package.path = package.path .. ";" .. directory .. "/?.lua"

        require("main")
    else
        require("pesto.manager")
    end
end

function pesto.run()
    local target

    if config.letterbox then
        target = pesto.graphics.loadCanvas(config.gameWidth, config.gameHeight)
        target:setFilter(config.letterboxFilter)
    end

    while true do
        if pesto.window.shouldClose() then
            if not pesto.quit or not pesto.quit() then
                break
            end
        end

        local dt = pesto.graphics.getDelta()

        if config.debug then
            pesto.reload.update(dt)
        end

        pesto.tween.update(dt)
        pesto.timer.update(dt)

        if pesto.update then pesto.update(dt) end

        pesto.graphics.beginDrawing()

        if config.letterbox then
            target:beginDrawing()

            pesto.graphics.clear()

            if pesto.draw then pesto.draw() end

            target:endDrawing()

            local scale = math.min(pesto.window.getWidth() / config.gameWidth,
                pesto.window.getHeight() / config.gameHeight)

            pesto.mouse.setOffset(-(pesto.window.getWidth() - (config.gameWidth * scale)) * 0.5,
                -(pesto.window.getHeight() - (config.gameHeight * scale)) * 0.5)
            pesto.mouse.setScale(1 / scale, 1 / scale)

            pesto.graphics.clear(config.borderColor[1], config.borderColor[2], config.borderColor[3],
                config.borderColor[4])

            local r, g, b, a = pesto.graphics.getColor()
            pesto.graphics.setColor(255, 255, 255)

            target:draw((pesto.window.getWidth() - (config.gameWidth * scale)) * 0.5,
                (pesto.window.getHeight() - (config.gameHeight * scale)) * 0.5, 0, scale, -scale)

            pesto.graphics.setColor(r, g, b, a)
        else
            pesto.graphics.clear()

            if pesto.draw then pesto.draw() end
        end

        pesto.imgui.beginDrawing()

        if pesto.gui then pesto.gui() end

        pesto.imgui.endDrawing()

        pesto.graphics.endDrawing()
    end

    pesto.imgui.close()
    pesto.audio.close()
    pesto.window.close()
end

function pesto.errhand(msg)
    pesto.log.error(msg)

    pesto.window.init(config.width, config.height, config.title)
    pesto.window.setTargetFPS(config.targetFPS)

    pesto.mouse.enable()

    while not pesto.window.shouldClose() do
        pesto.graphics.beginDrawing()

        pesto.graphics.clear(119, 173, 120)

        pesto.graphics.setColor(255, 255, 255)

        pesto.graphics.text("Error", 10, 10)
        pesto.graphics.wrappedText(msg .. "\n\n" .. debug.traceback(), 10, 50, pesto.window.getWidth(),
            pesto.window.getHeight())

        pesto.graphics.endDrawing()
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
