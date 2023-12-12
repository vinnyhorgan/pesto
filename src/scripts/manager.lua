if not pesto.filesystem.exists("projects") then
    pesto.filesystem.createDirectory("projects")
end

local projects = {}

local items = pesto.filesystem.getDirectoryItems("projects")

for _, item in pairs(items) do
    if pesto.filesystem.isDirectory(item) then
        if pesto.filesystem.exists(item .. "/main.lua") then
            table.insert(projects, pesto.filesystem.getFilename(item))
        end
    end
end

function pesto.draw()
    pesto.graphics.text("Hello from manager :)", 10, 10)
end
