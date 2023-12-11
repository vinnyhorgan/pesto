-- LDTK implementation based on ldtk-love <3
local cache = {
    tilesets = {},
    quads = {}
}

local ldtk = {
    levels = {},
    levelNames = {},
    tilesets = {},
    currentLevelIndex = nil,
    currentLevelName = "",
    flipped = true,
    cache = cache
}

local _path

local flipX = {
    [0] = 1,
    [1] = -1,
    [2] = 1,
    [3] = -1
}

local flipY = {
    [0] = 1,
    [1] = 1,
    [2] = -1,
    [3] = -1
}

local oldColor = {}

local function create_layer_object(self, data, auto)
    self._offsetX = {
        [0] = 0,
        [1] = data.__gridSize,
        [2] = 0,
        [3] = data.__gridSize
    }

    self._offsetY = {
        [0] = 0,
        [1] = 0,
        [2] = data.__gridSize,
        [3] = data.__gridSize
    }

    if auto then
        self.tiles = data.autoLayerTiles
        self.intGrid = data.intGridCsv
    else
        self.tiles = data.gridTiles
        self.intGrid = nil
    end

    self._tilesLen = #self.tiles

    self.relPath = data.__tilesetRelPath
    self.path = ldtk.getPath(data.__tilesetRelPath)

    self.id = data.__identifier
    self.x, self.y = data.__pxTotalOffsetX, data.__pxTotalOffsetY
    self.visible = data.visible
    self.color = { 255, 255, 255, data.__opacity * 255 }

    self.width = data.__cWid
    self.height = data.__cHei
    self.gridSize = data.__gridSize

    self.tileset = ldtk.tilesets[data.__tilesetDefUid]
    self.tilesetID = data.__tilesetDefUid

    if not cache.tilesets[data.__tilesetDefUid] then
        cache.tilesets[data.__tilesetDefUid] = pesto.graphics.loadTexture(self.path)

        cache.quads[data.__tilesetDefUid] = {}
        local count = 0
        for ty = 0, self.tileset.__cHei - 1, 1 do
            for tx = 0, self.tileset.__cWid - 1, 1 do
                cache.quads[data.__tilesetDefUid][count] = {
                    x = self.tileset.padding + tx * (self.tileset.tileGridSize + self.tileset.spacing),
                    y = self.tileset.padding + ty * (self.tileset.tileGridSize + self.tileset.spacing),
                    w = self.tileset.tileGridSize,
                    h = self.tileset.tileGridSize
                }

                count = count + 1
            end
        end
    end
end

local function draw_layer_object(self)
    if self.visible then
        oldColor[1], oldColor[2], oldColor[3], oldColor[4] = pesto.graphics.getColor()

        pesto.graphics.setColor(self.color[1], self.color[2], self.color[3], self.color[4])

        for i = 1, self._tilesLen do
            local quad = cache.quads[self.tileset.uid][self.tiles[i].t]

            cache.tilesets[self.tileset.uid]:drawRec(
                quad.x, quad.y, quad.w, quad.h,
                self.x + self.tiles[i].px[1] + self._offsetX[self.tiles[i].f],
                self.y + self.tiles[i].px[2] + self._offsetY[self.tiles[i].f],
                0,
                flipX[self.tiles[i].f],
                flipY[self.tiles[i].f]
            )
        end

        pesto.graphics.setColor(oldColor[1], oldColor[2], oldColor[3], oldColor[4])
    end
end

function ldtk.hex2rgb(color)
    local r = load("return {0x" .. color:sub(2, 3) .. ",0x" .. color:sub(4, 5) .. ",0x" .. color:sub(6, 7) .. "}")()
    return { r[1], r[2], r[3] }
end

local function is_empty(t)
    for _, _ in pairs(t) do
        return false
    end

    return true
end

function ldtk:load(file, level)
    self.data = pesto.json.decode(pesto.filesystem.read(file))
    self.entities = {}
    self.x, self.y = self.x or 0, self.x or 0
    self.countOfLevels = #self.data.levels
    self.countOfLayers = #self.data.defs.layers

    _path = {}
    for str in string.gmatch(file, "([^" .. "/" .. "]+)") do
        table.insert(_path, str)
    end
    _path[#_path] = nil

    for index, value in ipairs(self.data.levels) do
        self.levels[value.identifier] = index
    end

    for key, value in pairs(self.levels) do
        self.levelNames[value] = key
    end

    for index, value in ipairs(self.data.defs.tilesets) do
        self.tilesets[value.uid] = self.data.defs.tilesets[index]
    end

    if level then
        self:goTo(level)
    end
end

function ldtk.getPath(relPath)
    local newPath = ""
    local newRelPath = {}
    local pathLen = #_path

    for str in string.gmatch(relPath, "([^" .. "/" .. "]+)") do
        table.insert(newRelPath, str)
    end

    for i = #newRelPath, 1, -1 do
        if newRelPath[i] == ".." then
            pathLen = pathLen - 1
            newRelPath[i] = nil
        end
    end

    for i = 1, pathLen, 1 do
        newPath = newPath .. (i > 1 and "/" or "") .. _path[i]
    end

    local keys = {}
    for key, _ in pairs(newRelPath) do
        table.insert(keys, key)
    end
    table.sort(keys)

    local len = #keys
    for i = 1, len, 1 do
        newPath = newPath .. (newPath ~= "" and "/" or "") .. newRelPath[keys[i]]
    end

    return newPath
end

local types = {
    Entities = function(currentLayer, order, level)
        for _, value in ipairs(currentLayer.entityInstances) do
            local props = {}

            for _, p in ipairs(value.fieldInstances) do
                props[p.__identifier] = p.__value
            end

            ldtk.onEntity(
                {
                    id = value.__identifier,
                    iid = value.iid,
                    x = value.px[1],
                    y = value.px[2],
                    width = value.width,
                    height = value.height,
                    px = value.__pivot[1],
                    py = value.__pivot[2],
                    order = order,
                    visible = currentLayer.visible,
                    props = props
                },
                level
            )
        end
    end,
    Tiles = function(currentLayer, order, level)
        if not is_empty(currentLayer.gridTiles) then
            local layer = { draw = draw_layer_object }
            create_layer_object(layer, currentLayer, false)
            layer.order = order
            ldtk.onLayer(layer, level)
        end
    end,
    IntGrid = function(currentLayer, order, level)
        if not is_empty(currentLayer.autoLayerTiles) and currentLayer.__tilesetDefUid then
            local layer = { draw = draw_layer_object }
            create_layer_object(layer, currentLayer, true)
            layer.order = order
            ldtk.onLayer(layer, level)
        end
    end,
    AutoLayer = function(currentLayer, order, level)
        if not is_empty(currentLayer.autoLayerTiles) and currentLayer.__tilesetDefUid then
            local layer = { draw = draw_layer_object }
            create_layer_object(layer, currentLayer, true)
            layer.order = order
            ldtk.onLayer(layer, level)
        end
    end
}

function ldtk:goTo(index)
    if index > self.countOfLevels or index < 1 then
        error("There are no levels with that index.")
    end

    self.currentLevelIndex = index
    self.currentLevelName = ldtk.levelNames[index]

    local layers
    if self.data.externalLevels then
        layers = pesto.json.decode(pesto.filesystem.read(self.getPath(self.data.levels[index].externalRelPath)))
            .layerInstances
    else
        layers = self.data.levels[index].layerInstances
    end

    local levelProps = {}
    for _, p in ipairs(self.data.levels[index].fieldInstances) do
        levelProps[p.__identifier] = p.__value
    end

    local levelEntry = {
        backgroundColor = ldtk.hex2rgb(self.data.levels[index].__bgColor),
        id = self.data.levels[index].identifier,
        worldX = self.data.levels[index].worldX,
        worldY = self.data.levels[index].worldY,
        width = self.data.levels[index].pxWid,
        height = self.data.levels[index].pxHei,
        neighbours = self.data.levels[index].__neighbours,
        index = index,
        props = levelProps
    }

    self.onLevelLoaded(levelEntry)

    if self.flipped then
        for i = self.countOfLayers, 1, -1 do
            types[layers[i].__type](layers[i], i, levelEntry)
        end
    else
        for i = 1, self.countOfLayers do
            types[layers[i].__type](layers[i], i, levelEntry)
        end
    end

    self.onLevelCreated(levelEntry)
end

function ldtk:level(name)
    self:goTo(
        self.levels[tostring(name)] or
        error('There are no levels with the name: "' .. tostring(name) .. '".\nDid you forget to save?')
    )
end

function ldtk:next()
    self:goTo(self.currentLevelIndex + 1 <= self.countOfLevels and self.currentLevelIndex + 1 or 1)
end

function ldtk:previous()
    self:goTo(self.currentLevelIndex - 1 >= 1 and self.currentLevelIndex - 1 or self.countOfLevels)
end

function ldtk:reload()
    self:goTo(self.currentLevelIndex)
end

function ldtk.getIndex(name)
    return ldtk.levels[name]
end

function ldtk.getName(index)
    return ldtk.levelNames[index]
end

function ldtk:getCurrent()
    return self.currentLevelIndex
end

function ldtk:getCurrentName()
    return ldtk.levelNames[self:getCurrent()]
end

function ldtk:setFlipped(flipped)
    self.flipped = flipped
end

function ldtk:getFlipped()
    return self.flipped
end

function ldtk.removeCache()
    cache = {
        tilesets = {},
        quads = {},
    }

    collectgarbage()
end

function ldtk.onEntity(entity, level)
end

function ldtk.onLayer(layer, level)
end

function ldtk.onLevelLoaded(levelData)
end

function ldtk.onLevelCreated(levelData)
end

return ldtk
