function pesto.init()
    require("pesto.filesystem")
    require("pesto.graphics")
    require("pesto.log")
    require("pesto.window")

    local directory = arg[1]

    if not directory then
        error("No directory specified!")
    end

    if not pesto.filesystem.directoryExists(directory) then
        error("Directory does not exist!")
    end

    package.path = package.path .. ";" .. directory .. "/?.lua"

    if pesto.filesystem.fileExists(directory .. "/main.lua") then
        require("main")
    else
        error("No main.lua found!")
    end
end

function pesto.run()
    pesto.log.level("warn") -- Disable raylib's wall of info logs :)

    local major, minor, patch, codename = pesto.getVersion()

    pesto.window.init(800, 600, "Pesto " .. major .. "." .. minor .. "." .. patch .. " " .. codename)
    pesto.window.setTargetFPS(60)

    pesto.log.level("info")

    while not pesto.window.shouldClose() do
        pesto.window.beginDrawing()

        pesto.graphics.clear()

        if pesto.step then pesto.step(pesto.window.getDelta()) end

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
