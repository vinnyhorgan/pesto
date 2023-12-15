local icon, github, love, lua, raylib = pesto.graphics.loadLogos()
icon:setFilter("bilinear")

local major, minor, patch, codename = pesto.getVersion()

if not pesto.filesystem.exists("projects") then
    pesto.filesystem.createDirectory("projects")
end

local projects = {}

for _, item in pairs(pesto.filesystem.getDirectoryItems("projects")) do
    if pesto.filesystem.isDirectory(item) and pesto.filesystem.exists(item .. "/main.lua") then
        table.insert(projects, pesto.filesystem.getFilename(item))
    end
end

local function wave(lo, hi, t)
    local value = (math.sin(t) + 1) / 2
    return lo + (hi - lo) * value
end

local Letter = pesto.Object:extend()

function Letter:new(x, y, letter, index)
    self.x = x
    self.y = y
    self.letter = letter
    self.index = index
    self.currentY = y
    self.color = { 0, 0, 0 }
end

function Letter:update(dt)
    self.currentY = wave(self.y - 6, self.y + 6, pesto.system.getTime() * 4 + self.index * 0.5)

    self.color[1], self.color[2], self.color[3] = pesto.graphics.hsvToRgb(
        (pesto.system.getTime() * 72 + self.index * 36) % 360, 0.8, 0.8)
end

function Letter:draw()
    pesto.graphics.setColor(self.color[1], self.color[2], self.color[3])
    pesto.graphics.textBig(self.letter, self.x, self.currentY)
    pesto.graphics.setColor(255, 255, 255)
end

local letters = {}

local function animatedText(text, x, y)
    for i = 1, #text do
        table.insert(letters, Letter(x + (i - 1) * 25, y, text:sub(i, i), i))
    end
end

local Leaf = pesto.Object:extend()

function Leaf:new(x, y, direction)
    self.x = x
    self.y = y
    self.rotation = pesto.math.random(0, 360)
    self.speed = pesto.math.random(100, 400) * direction
end

function Leaf:update(dt)
    self.x = self.x + self.speed * dt
    self.y = self.y + self.speed * dt * math.sin(self.rotation * math.pi / 180)
    self.rotation = self.rotation + self.speed * dt
end

function Leaf:draw()
    icon:draw(self.x, self.y, self.rotation, 1, 1, icon:getWidth() / 2, icon:getHeight() / 2)
end

local leaves = {}

function pesto.update(dt)
    for _, letter in pairs(letters) do
        letter:update(dt)
    end

    for _, leaf in pairs(leaves) do
        leaf:update(dt)

        if leaf.x > 960 + 100 or leaf.x < -100 then
            pesto.util.remove(leaves, leaf)
        end
    end
end

local currentPage = "projectList"
local scroll = 0
local name = ""
local selected = false

function pesto.draw()
    -- Sidebar
    pesto.graphics.setColor(50, 79, 59)
    pesto.graphics.rectangle(0, 0, 250, 540)
    pesto.graphics.setColor(255, 255, 255)

    -- Icon
    if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 250 / 2 - icon:getWidth() / 2, 40, icon:getWidth(), icon:getHeight()) then
        if pesto.mouse.isPressed(0) then
            for i = 1, 50 do
                table.insert(leaves, Leaf(-50, pesto.math.random(0, 540), 1))
                table.insert(leaves, Leaf(960 + 50, pesto.math.random(0, 540), -1))
            end

            icon:draw(250 / 2 - icon:getWidth() / 2, 40)
        elseif pesto.mouse.isDown(0) then
            icon:draw(250 / 2 - icon:getWidth() / 2, 40)
        else
            icon:draw(250 / 2 - icon:getWidth() / 2 - 2, 40 - 2, 0, 1.2, 1.2)
        end
    else
        icon:draw(250 / 2 - icon:getWidth() / 2, 40)
    end

    -- Tabs
    if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 20, 150 - 6, 210, 40) and pesto.mouse.isPressed(0) then
        currentPage = "projectList"
        letters = {}
    end

    if currentPage == "projectList" then
        pesto.graphics.setColor(37, 59, 44)
        pesto.graphics.rectangleRounded(20, 150 - 6, 210, 40, 0.2, 10)
        pesto.graphics.setColor(255, 255, 255)
    end

    local width = pesto.graphics.measureMedium("Project List")
    pesto.graphics.textMedium("Project List", 250 / 2 - width / 2, 150)

    if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 20, 200 - 6, 210, 40) and pesto.mouse.isPressed(0) then
        currentPage = "newProject"
        letters = {}
    end

    if currentPage == "newProject" then
        pesto.graphics.setColor(37, 59, 44)
        pesto.graphics.rectangleRounded(20, 200 - 6, 210, 40, 0.2, 10)
        pesto.graphics.setColor(255, 255, 255)
    end

    width = pesto.graphics.measureMedium("New Project")
    pesto.graphics.textMedium("New Project", 250 / 2 - width / 2, 200)

    if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 20, 250 - 6, 210, 40) and pesto.mouse.isPressed(0) then
        currentPage = "templates"
        letters = {}
    end

    if currentPage == "templates" then
        pesto.graphics.setColor(37, 59, 44)
        pesto.graphics.rectangleRounded(20, 250 - 6, 210, 40, 0.2, 10)
        pesto.graphics.setColor(255, 255, 255)
    end

    width = pesto.graphics.measureMedium("Templates")
    pesto.graphics.textMedium("Templates", 250 / 2 - width / 2, 250)

    if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 20, 300 - 6, 210, 40) and pesto.mouse.isPressed(0) then
        currentPage = "about"
        animatedText("Pesto " .. major .. "." .. minor .. "." .. patch .. " " .. codename, 280, 150)
    end

    if currentPage == "about" then
        pesto.graphics.setColor(37, 59, 44)
        pesto.graphics.rectangleRounded(20, 300 - 6, 210, 40, 0.2, 10)
        pesto.graphics.setColor(255, 255, 255)
    end

    width = pesto.graphics.measureMedium("About")
    pesto.graphics.textMedium("About", 250 / 2 - width / 2, 300)

    -- Version
    width = pesto.graphics.measure("v" .. major .. "." .. minor .. "." .. patch .. " " .. codename)
    pesto.graphics.text("v" .. major .. "." .. minor .. "." .. patch .. " " .. codename, 250 / 2 - width / 2,
        540 - 40 - 18)

    -- Main
    pesto.graphics.clear(31, 49, 47)

    if currentPage == "projectList" then
        pesto.graphics.setColor(50, 79, 59)
        pesto.graphics.rectangleRounded(290, 150, 960 - 250 - 80, 540 - 150 - 40, 0.05, 10)
        pesto.graphics.setColor(255, 255, 255)

        pesto.graphics.textBig("Project List", 290, 40)

        local _, wheelY = pesto.mouse.getWheelMove()

        if wheelY > 0 then
            scroll = scroll + 20
        elseif wheelY < 0 then
            scroll = scroll - 20
        end

        pesto.graphics.beginScissorMode(290, 190, 960 - 250 - 80, 540 - 150 - 40 - 80)

        for i, project in pairs(projects) do
            if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 290 + 40, scroll + 150 + 60 * i - 10, 550, 50) then
                pesto.graphics.setColor(37, 59, 44)
                pesto.graphics.rectangleRounded(290 + 40, scroll + 150 + 60 * i - 10, 550, 50, 0.1, 10)
                pesto.graphics.setColor(255, 255, 255)
            end

            width = pesto.graphics.measureMedium(project)
            pesto.graphics.textMedium(project, 290 + 630 / 2 - width / 2, scroll + 150 + 60 * i)

            pesto.graphics.line(290 + 40, scroll + 150 + 60 * i - 15 + 60, 880, scroll + 150 + 60 * i - 15 + 60)

            if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 290 + 40, scroll + 150 + 60 * i - 10, 550, 50) and pesto.mouse.isPressed(0) then
                package.path = "projects/" .. project .. "/?.lua;" .. package.path
                pesto.filesystem.changeDirectory("projects/" .. project)
                pesto.update = nil
                pesto.draw = nil
                require("main")
            end

            if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 290 + 40, scroll + 150 + 60 * i - 10, 550, 50) and pesto.mouse.isPressed(1) then
                if pesto.system.getOS() == "windows" then
                    os.execute("explorer " .. pesto.filesystem.getWorkingDirectory() .. "\\projects\\" .. project)
                end
            end
        end

        pesto.graphics.endScissorMode()
    elseif currentPage == "newProject" then
        pesto.graphics.textBig("New Project", 290, 40)

        width = pesto.graphics.measureMedium("Name")
        pesto.graphics.textMedium("Name", 250 + 710 / 2 - width / 2, 150)

        if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 250 + 710 / 2 - 150, 200, 300, 50) then
            pesto.mouse.setCursor("ibeam")

            if pesto.mouse.isPressed(0) then
                selected = true
            end
        else
            pesto.mouse.setCursor("arrow")

            if pesto.mouse.isPressed(0) then
                selected = false
            end
        end

        pesto.graphics.setColor(50, 79, 59)
        pesto.graphics.rectangleRounded(250 + 710 / 2 - 150, 200, 300, 50, 0.2, 10)
        pesto.graphics.setColor(255, 255, 255)

        if selected then
            pesto.graphics.rectangleRoundedLines(250 + 710 / 2 - 150, 200, 300, 50, 0.1, 10, 2)

            local key = pesto.keyboard.getCharPressed()

            while key > 0 do
                if key >= 32 and key <= 125 and #name < 25 then
                    name = name .. string.char(key)
                end

                key = pesto.keyboard.getCharPressed()
            end

            if pesto.keyboard.isPressed("backspace") then
                name = string.sub(name, 1, -2)
            end
        end

        width = pesto.graphics.measureMedium(name)
        pesto.graphics.textMedium(name, 250 + 710 / 2 - width / 2, 210)

        if pesto.keyboard.isPressed("enter") or pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 250 + 710 / 2 - 100, 300, 200, 50) and pesto.mouse.isPressed(0) then
            if #name > 0 then
                pesto.filesystem.createDirectory("projects/" .. name)
                pesto.filesystem.write("projects/" .. name .. "/main.lua",
                    "function pesto.draw()\n    pesto.graphics.text(\"Hello, World!\", 10, 10)\nend")

                projects = {}

                for _, item in pairs(pesto.filesystem.getDirectoryItems("projects")) do
                    if pesto.filesystem.isDirectory(item) and pesto.filesystem.exists(item .. "/main.lua") then
                        table.insert(projects, pesto.filesystem.getFilename(item))
                    end
                end

                name = ""

                currentPage = "projectList"
            end
        end

        pesto.graphics.setColor(50, 79, 59)
        pesto.graphics.rectangleRounded(250 + 710 / 2 - 100, 300, 200, 50, 0.2, 10)
        pesto.graphics.setColor(255, 255, 255)

        width = pesto.graphics.measureMedium("Create")
        pesto.graphics.textMedium("Create", 250 + 710 / 2 - width / 2, 310)
    elseif currentPage == "templates" then
        pesto.graphics.textBig("Templates", 290, 40)
        pesto.graphics.textBig("Coming Soon", 290, 150)
    elseif currentPage == "about" then
        pesto.graphics.textBig("About", 290, 40)

        width = pesto.graphics.measureMedium("By Vinny Horgan with love <3")
        pesto.graphics.textMedium("By Vinny Horgan with love <3", 250 + 710 / 2 - width / 2, 250)

        if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 250 + 710 / 2 - github:getWidth() / 2, 300, github:getWidth(), github:getHeight()) and pesto.mouse.isPressed(0) then
            pesto.system.openURL("https://github.com/vinnyhorgan/pesto")
        end

        github:draw(250 + 710 / 2 - github:getWidth() / 2, 300)

        width = pesto.graphics.measureMedium("Also thanks to these amazing people")
        pesto.graphics.textMedium("Also thanks to these amazing people", 290 + 630 / 2 - width / 2, 360)

        if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 250 + 710 / 2 - lua:getWidth() / 2, 430, lua:getWidth(), lua:getHeight()) and pesto.mouse.isPressed(0) then
            pesto.system.openURL("https://www.lua.org/")
        end

        lua:draw(250 + 710 / 2 - lua:getWidth() / 2, 430)

        if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 250 + 710 / 2 - love:getWidth() / 2 - 100, 430, love:getWidth(), love:getHeight()) and pesto.mouse.isPressed(0) then
            pesto.system.openURL("https://love2d.org/")
        end

        love:draw(250 + 710 / 2 - lua:getWidth() / 2 - 100, 430)

        if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 250 + 710 / 2 - raylib:getWidth() / 2 + 100, 430, raylib:getWidth(), raylib:getHeight()) and pesto.mouse.isPressed(0) then
            pesto.system.openURL("https://www.raylib.com/")
        end

        raylib:draw(250 + 710 / 2 - lua:getWidth() / 2 + 100, 430)
    end

    for _, letter in pairs(letters) do
        letter:draw()
    end

    for _, leaf in pairs(leaves) do
        leaf:draw()
    end
end
