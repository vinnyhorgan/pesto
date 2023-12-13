local noto = pesto.graphics.loadFont("noto.ttf", 48)
local middleNoto = pesto.graphics.loadFont("noto.ttf", 24)

local icon, github, love, lua, raylib = pesto.graphics.loadLogos()
icon:setFilter("bilinear")

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

local currentPage = "projectList"

local Leaf = pesto.Object:extend()

function Leaf:new(x, y, direction)
    self.x = x
    self.y = y
    self.rotation = pesto.math.random(0, 360)
    self.speed = pesto.math.random(100, 300) * direction
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

local letters = {}

local function wave(lo, hi, t)
    local value = (math.sin(t) + 1) / 2
    return lo + (hi - lo) * value
end

local AnimatedLetter = pesto.Object:extend()

function AnimatedLetter:new(x, y, letter, index)
    self.x = x
    self.y = y
    self.letter = letter
    self.index = index
    self.currentY = y
    self.color = { 0, 0, 0 }
end

function AnimatedLetter:update(dt)
    self.color[1], self.color[2], self.color[3] = pesto.graphics.hsvToRgb(
        (pesto.system.getTime() * 72 + self.index * 36) % 360, 0.8,
        0.8)

    self.currentY = wave(self.y - 6, self.y + 6, pesto.system.getTime() * 4 + self.index * 0.5)
end

function AnimatedLetter:draw()
    pesto.graphics.setColor(self.color[1], self.color[2], self.color[3])

    noto:draw(self.letter, self.x, self.currentY)
end

local function animatedText(text, x, y)
    for i = 1, #text do
        table.insert(letters, AnimatedLetter(x + (i - 1) * 25, y, text:sub(i, i), i))
    end
end

function pesto.update(dt)
    for _, leaf in pairs(leaves) do
        leaf:update(dt)
    end

    for _, letter in pairs(letters) do
        letter:update(dt)
    end
end

function pesto.draw()
    pesto.graphics.setColor(50, 79, 59)
    pesto.graphics.rectangle(0, 0, 250, 600)
    pesto.graphics.setColor(255, 255, 255)

    local major, minor, patch, codename = pesto.getVersion()

    if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 250 / 2 - icon:getWidth() / 2, 30, icon:getWidth(), icon:getHeight()) then
        if pesto.mouse.isPressed(0) then
            for i = 1, 50 do
                table.insert(leaves, Leaf(-50, pesto.math.random(0, 540), 1))
            end

            for i = 1, 50 do
                table.insert(leaves, Leaf(960 + 50, pesto.math.random(0, 540), -1))
            end

            icon:draw(250 / 2 - icon:getWidth() / 2, 30)
        else
            icon:draw(250 / 2 - icon:getWidth() / 2 - 2, 30 - 2, 0, 1.2, 1.2)
        end
    else
        icon:draw(250 / 2 - icon:getWidth() / 2, 30)
    end

    pesto.graphics.text("v" .. major .. "." .. minor .. "." .. patch .. " " .. codename, 20, 500)

    if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 20, 100 - 6, 210, 40) and pesto.mouse.isPressed(0) then
        currentPage = "projectList"
        letters = {}
    end

    if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 20, 150 - 6, 210, 40) and pesto.mouse.isPressed(0) then
        currentPage = "newProject"
        letters = {}
    end

    if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 20, 200 - 6, 210, 40) and pesto.mouse.isPressed(0) then
        currentPage = "templates"
        letters = {}
    end

    if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 20, 250 - 6, 210, 40) and pesto.mouse.isPressed(0) then
        currentPage = "about"
        animatedText("Pesto " .. major .. "." .. minor .. "." .. patch .. " " .. codename, 290, 150)
    end

    if currentPage == "projectList" then
        pesto.graphics.setColor(37, 59, 44)
        pesto.graphics.rectangleRounded(20, 100 - 6, 210, 40, 0.2, 10)
        pesto.graphics.setColor(255, 255, 255)
    end

    local width = middleNoto:measure("Project List")
    middleNoto:draw("Project List", 125 - width / 2, 100)

    if currentPage == "newProject" then
        pesto.graphics.setColor(37, 59, 44)
        pesto.graphics.rectangleRounded(20, 150 - 6, 210, 40, 0.2, 10)
        pesto.graphics.setColor(255, 255, 255)
    end

    width = middleNoto:measure("New Project")
    middleNoto:draw("New Project", 125 - width / 2, 150)

    if currentPage == "templates" then
        pesto.graphics.setColor(37, 59, 44)
        pesto.graphics.rectangleRounded(20, 200 - 6, 210, 40, 0.2, 10)
        pesto.graphics.setColor(255, 255, 255)
    end

    width = middleNoto:measure("Templates")
    middleNoto:draw("Templates", 125 - width / 2, 200)

    if currentPage == "about" then
        pesto.graphics.setColor(37, 59, 44)
        pesto.graphics.rectangleRounded(20, 250 - 6, 210, 40, 0.2, 10)
        pesto.graphics.setColor(255, 255, 255)
    end

    width = middleNoto:measure("About")
    middleNoto:draw("About", 125 - width / 2, 250)

    pesto.graphics.clear(31, 49, 47)

    if currentPage == "projectList" then
        pesto.graphics.setColor(50, 79, 59)
        pesto.graphics.rectangleRounded(290, 150, 630, 350, 0.05, 10)
        pesto.graphics.setColor(255, 255, 255)

        noto:draw("Project List", 290, 40)

        for i, project in ipairs(projects) do
            if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 290, 120 + 70 * i - 15, 630, 60) then
                pesto.graphics.setColor(37, 59, 44)
                pesto.graphics.rectangleRounded(330, 120 + 70 * i - 15, 550, 60, 0.05, 10)
                pesto.graphics.setColor(255, 255, 255)
            end

            width = middleNoto:measure(project)
            middleNoto:draw(project, 290 + 630 / 2 - width / 2, 120 + 70 * i)

            pesto.graphics.line(330, 120 + 70 * i - 15 + 60, 880, 120 + 70 * i - 15 + 60)

            if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 290, 100 + 70 * i - 6, 470, 60) and pesto.mouse.isPressed(0) then
                package.path = "projects/" .. project .. "/?.lua;" .. package.path
                package.loaded.main = nil
                pesto.filesystem.changeDirectory("projects/" .. project)
                require("main")
            end

            if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 290, 100 + 70 * i - 6, 470, 60) and pesto.mouse.isPressed(1) then
                os.execute("explorer " .. pesto.filesystem.getWorkingDirectory() .. "\\projects\\" .. project)
            end
        end
    elseif currentPage == "newProject" then
        noto:draw("New Project", 290, 40)
    elseif currentPage == "templates" then
        noto:draw("Templates", 290, 40)
    elseif currentPage == "about" then
        noto:draw("About", 290, 40)

        width = middleNoto:measure("By Vinny Horgan with love <3")
        middleNoto:draw("By Vinny Horgan with love <3", 290 + 630 / 2 - width / 2, 250)

        github:draw(290 + 630 / 2 - github:getWidth() / 2, 300)

        if pesto.graphics.checkCollisionPointRec(pesto.mouse.getX(), pesto.mouse.getY(), 290 + 630 / 2 - github:getWidth() / 2, 300, github:getWidth(), github:getHeight()) and pesto.mouse.isPressed(0) then
            pesto.system.openURL("https://github.com/vinnyhorgan/pesto")
        end

        width = middleNoto:measure("Also thanks to these amazing people:")
        middleNoto:draw("Also thanks to these amazing people:", 290 + 630 / 2 - width / 2, 370)

        love:draw(290, 420)
        lua:draw(290 + 100, 420)
        raylib:draw(290 + 200, 420)
    end

    for _, leaf in pairs(leaves) do
        leaf:draw()
    end

    for _, letter in pairs(letters) do
        letter:draw()
    end
end
