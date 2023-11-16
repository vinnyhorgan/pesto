function pesto.init()
    require("pesto.filesystem")
    require("pesto.graphics")
    require("pesto.log")
    require("pesto.window")

    if pesto.filesystem.fileExists("main.lua") then
        require("main")
    else
        error("No main.lua found!")
    end

    pesto.log.level("warn") -- Disable raylib's wall of info logs :)

    local major, minor, patch, codename = pesto.getVersion()

    pesto.window.init(800, 600, "Pesto " .. major .. "." .. minor .. "." .. patch .. " " .. codename)

    pesto.log.level("info")
end

function pesto.run()
    while not pesto.window.shouldClose() do
        if pesto.update then pesto.update() end

        pesto.window.beginDrawing()

        if pesto.draw then pesto.draw() end

        pesto.window.endDrawing()
    end

    pesto.log.level("warn")

    pesto.window.close()
end

local function errorHandler(msg)
    pesto.log.error(msg)

    pesto.log.level("warn")

    pesto.window.init(800, 600, "Pesto Error")

    pesto.log.level("info")

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
