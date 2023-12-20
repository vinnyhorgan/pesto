-- Config
local config = {
    debug = true,
    version = "0.1",
    title = "Pesto Project",
    icon = nil,
    width = 960,
    height = 540,
    targetFPS = 60,
    resizable = true,
    minWidth = 1,
    minHeight = 1,
    fullscreen = false,
    letterbox = true,
    letterboxFilter = "bilinear",
    gameWidth = 960,
    gameHeight = 540,
    borderColor = { 50, 79, 59, 255 }
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
    pesto.animation = require("pesto.animation")
    pesto.ldtk = require("pesto.ldtk")
    pesto.reload = require("pesto.reload")
    pesto.state = require("pesto.state")

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
    else
        local major, minor, patch, codename = pesto.getVersion()

        config.debug = false
        config.title = "Pesto " .. major .. "." .. minor .. "." .. patch .. " " .. codename .. " Manager"
        config.resizable = false
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
        pesto.log.debug("Running in debug mode.")
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
        local scale

        if config.letterbox then
            scale = math.min(pesto.window.getWidth() / config.gameWidth, pesto.window.getHeight() / config.gameHeight)

            pesto.mouse.setOffset(-(pesto.window.getWidth() - (config.gameWidth * scale)) * 0.5,
                -(pesto.window.getHeight() - (config.gameHeight * scale)) * 0.5)
            pesto.mouse.setScale(1 / scale, 1 / scale)
        end

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

        pesto.mouse.setOffset(0, 0)
        pesto.mouse.setScale(1, 1)

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

    pesto.window.setResizable(false)

    local trace = debug.traceback()
    local err = {}

    table.insert(err, "Error\n")
    table.insert(err, msg .. "\n\n")

    for l in string.gmatch(trace, "(.-)\n") do
        if not string.match(l, "boot.lua") then
            l = string.gsub(l, "stack traceback:", "Traceback\n")
            table.insert(err, l)
        end
    end

    local p = table.concat(err, "\n")

    p = string.gsub(p, "\t", "")
    p = string.gsub(p, "%[string \"(.-)\"%]", "%1")

    local target = pesto.graphics.loadCanvas(config.width, config.height)
    target:setFilter("bilinear")

    while not pesto.window.shouldClose() do
        local scale = math.min(pesto.window.getWidth() / config.width, pesto.window.getHeight() / config.height)

        pesto.graphics.beginDrawing()

        target:beginDrawing()

        pesto.graphics.clear(50, 79, 59)

        pesto.graphics.setColor(255, 255, 255)

        pesto.graphics.text(p, 70, 70)

        target:endDrawing()

        target:draw((pesto.window.getWidth() - (config.width * scale)) * 0.5,
            (pesto.window.getHeight() - (config.height * scale)) * 0.5, 0, scale, -scale)

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
