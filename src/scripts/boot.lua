function pesto.init()
    require("pesto.log")
    require("pesto.filesystem")
    require("pesto.window")

    pesto.update = function() end
    pesto.draw = function() end

    if pesto.filesystem.fileExists("main.lua") then
        pesto.log.info("Found main.lua!")

        require("main")
    else
        pesto.log.warn("No main.lua found!")
    end

    pesto.log.level("warn") -- Disable raylib's wall of info logs :)

    local major, minor, patch, codename = pesto.getVersion()

    pesto.window.init(800, 600, "Pesto " .. major .. "." .. minor .. "." .. patch .. " " .. codename)

    pesto.log.level("info") -- Return to info level
end

function pesto.run()
    while not pesto.window.shouldClose() do
        pesto.update()

        pesto.window.beginDrawing()

        pesto.draw()

        pesto.window.endDrawing()
    end

    pesto.log.level("warn") -- Same

    pesto.window.close()
end

local function errorHandler(msg)
    pesto.log.error(msg)
end

return function()
    local result = xpcall(pesto.init, errorHandler)
    if not result then return 1 end
    local result, retval = xpcall(pesto.run, errorHandler)
    if not result then return 1 end

    return tonumber(retval) or 0
end
