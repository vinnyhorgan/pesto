function pesto.init()
    require("pesto.log")
    require("pesto.filesystem")
    require("pesto.window")

    pesto.log.level("trace")
    pesto.log.trace("This is a trace log")
    pesto.log.debug("This is a debug log")
    pesto.log.info("This is an info log")
    pesto.log.warn("This is a warning log")
    pesto.log.error("This is an error log")
    pesto.log.fatal("This is a fatal log")

    local major, minor, patch, codename = pesto.getVersion()

    pesto.window.init(800, 600, "Pesto " .. major .. "." .. minor .. "." .. patch .. " " .. codename)
end

function pesto.run()
    while not pesto.window.shouldClose() do
        pesto.window.beginDrawing()

        pesto.window.endDrawing()
    end

    pesto.window.close()
end

local function errorHandler(msg)
    print("Error: " .. tostring(msg))
end

return function()
    local result = xpcall(pesto.init, errorHandler)
    if not result then return 1 end
    local result, retval = xpcall(pesto.run, errorHandler)
    if not result then return 1 end

    return tonumber(retval) or 0
end
