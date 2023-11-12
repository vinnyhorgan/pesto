function pesto.init()
    print("Hello from init")

    require("pesto.window")
    require("pesto.filesystem")

    pesto.Object = require("classic")

    print(pesto.getVersion())

    Cat = pesto.Object:extend()

    function Cat:new(name)
        self.name = name
    end

    local dude = Cat("Dude")
    local dudette = Cat("Dudette")

    print(dude.name)
    print(dudette.name)

    socket = require("socket")
    print(socket._VERSION)

    http = require("socket.http")
    print(http.request("http://info.cern.ch/"))

    pesto.window.init(800, 600, "Hello pesto")
end

function pesto.run()
    print("Hello from run")

    -- error("Test error")

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
