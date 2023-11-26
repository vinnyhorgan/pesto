-- State implementation based on hump <3
local function __NULL__() end

local base = setmetatable({leave = __NULL__}, {__index = function() error("State not initialized. Use pesto.state.switch()") end})
local stack = {base}
local initialized = setmetatable({}, {__mode = "k"})
local dirty = true

local state = {}

local function changeState(offset, to, ...)
    local pre = stack[#stack]

    ;(initialized[to] or to.init or __NULL__)(to)
    initialized[to] = __NULL__

    stack[#stack + offset] = to
    dirty = true
    return (to.enter or __NULL__)(to, pre, ...)
end

function state.switch(to, ...)
    assert(to, "Missing argument: state to switch to")
    assert(to ~= state, "Can't call switch with colon operator")
    ;(stack[#stack].leave or __NULL__)(stack[#stack])
    return changeState(0, to, ...)
end

function state.push(to, ...)
    assert(to, "Missing argument: state to switch to")
    assert(to ~= state, "Can't call push with colon operator")
    return changeState(1, to, ...)
end

function state.pop(...)
    assert(#stack > 1, "No more states to pop!")
    local pre, to = stack[#stack], stack[#stack - 1]
    stack[#stack] = nil
    ;(pre.leave or __NULL__)(pre)
    dirty = true
    return (to.resume or __NULL__)(to, pre, ...)
end

function state.current()
    return stack[#stack]
end

local callbacks = {"update", "draw"}

function state.registerEvents()
    local registry = {}
    for _, f in ipairs(callbacks) do
        registry[f] = pesto[f] or __NULL__
        pesto[f] = function(...)
            registry[f](...)
            return state[f](...)
        end
    end
end

setmetatable(state, {__index = function(_, func)
    if not dirty or func == "update" then
        dirty = false
        return function(...)
            return (stack[#stack][func] or __NULL__)(stack[#stack], ...)
        end
    end
    return __NULL__
end})

return state
