print("Hello from lua!")

local wabbit = loadTexture("wabbit_alpha.png")

print(wabbit)

function update(dt)
    drawTexture(wabbit, 10, 10)
end
