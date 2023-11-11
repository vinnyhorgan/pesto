function pesto.init()
    print("Hello from init")

    require("pesto.filesystem")

    print(pesto.filesystem.create())
end

function pesto.run()
    print("Hello from run")

    -- error("Test error")
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
