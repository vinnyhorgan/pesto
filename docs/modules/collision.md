# pesto.collision

The `pesto.collision` module provides AABB (axis-aligned bounding box) collision detection and response.
It is based on kikito's amazing [bump](https://github.com/kikito/bump.lua) library.

## Functions

### pesto.collision.newWorld

Creates a new world object.

```
world = pesto.collision.newWorld([cellSize])
```

**Arguments**

| Name       | Type   | Default | Description            |
| ---------- | ------ | ------- | ---------------------- |
| `cellSize` | number | 64      | The size of each cell. |

- `cellSize` represents the size of the cells that will be used internally to provide the data.
In tile-based games, it's usually a multiple of the tile side size.

**Returns**

| Name    | Type            | Description           |
| ------- | --------------- | --------------------- |
| `world` | [World](#world) | The new world object. |

## Types

## World

World objects store collision items.
They can also act as spatial dictionaries. (useful to draw only the visible parts of the world)

### World:add

Inserts a new item into the world.

```
World:add(item, x, y, w, h)
```

**Arguments**

| Name   | Type   | Description                 |
| ------ | ------ | --------------------------- |
| `item` | table  | The item to add.            |
| `x`    | number | The x position of the item. |
| `y`    | number | The y position of the item. |
| `w`    | number | The width of the item.      |
| `h`    | number | The height of the item.     |

**Returns**

None

### World:remove

Removes an item from the world.

```
World:remove(item)
```

**Arguments**

| Name   | Type   | Description         |
| ------ | ------ | ------------------- |
| `item` | table  | The item to remove. |

**Returns**

None

### World:update

Changes the position, and optionally the size, of an item.
It ignores all collisions.

```
World:update(item, x, y, [w], [h])
```

**Arguments**

| Name   | Type   | Description                |
| ------ | ------ | -------------------------- |
| `item` | table  | The item to modify.        |
| `x`    | number | The new x position.        |
| `y`    | number | The new y position.        |
| `w`    | number | The new width. (optional)  |
| `h`    | number | The new height. (optional) |

**Returns**

None

### World:move

Moves the item in the world with collision resolution.

```
actualX, actualY, cols, len = World:move(item, goalX, goalY, [filter])
```

**Arguments**

| Name     | Type     | Description                     |
| -------- | -------- | ------------------------------- |
| `item`   | table    | The item to move.               |
| `goalX`  | number   | The desired x position.         |
| `goalY`  | number   | The desired y position.         |
| `filter` | function | The filter function. (optional) |

- If `filter` is provided, it must have this signature: `local type = filter(item, other)`.
By default, filter always returns `"slide"`.
    - `item` is the item being moved (the same one passed to `world:move` on the first param).
    - `other` is an item (different from `item`) which can collide with `item`.
    - `type` is a value which defines how `item` collides with `other`.
        - If `type` is `false` or `nil`, `item` will ignore `other` completely (there will be no collision).
        - If `type` is `"touch"`, `"cross"`, `"slide"` or `"bounce"`, `item` will respond to the collisions in different ways (explained below).
        - Any other value will provoke an error.

Collision types:

- `"touch"`: Type of collision for things like arrows or bullets that "get stuck" on their targets.
- `"cross"`: Type of collision for cases where you want to detect a collision but you don't want any response. (useful for detecting when the player has entered a new area, or consumables)
- `"slide"`: Default type, what you want to use for solid objects.
- `"bounce"`: Type of collision for things that "move away" after touching others. (arkanoid ball)

Example:

``` lua
local playerFilter = function(item, other)
    if     other.isCoin   then return "cross"
    elseif other.isWall   then return "slide"
    elseif other.isExit   then return "touch"
    elseif other.isSpring then return "bounce"
    end
end

function movePlayer(player, dt)
    local goalX, goalY = player.vx * dt, player.vy * dt
    local actualX, actualY, cols, len = world:move(player, goalX, goalY, playerFilter)
    player.x, player.y = actualX, actualY

    for i = 1, len do
        local other = cols[i].other

        if other.isCoin then
            takeCoin(other)
        elseif other.isExit then
            changeLevel()
        elseif other.isSpring then
            highJump()
        end
    end
end
```

**Returns**

| Name      | Type   | Description                |
| --------- | ------ | -------------------------- |
| `actualX` | number | The item's new x position. |
| `actualY` | number | The item's new y position. |
| `cols`    | table  | The collisions.            |
| `len`     | number | The number of collisions.  |

Here's the info contained on every collision item contained in the `cols` table:

``` lua
cols[i] = {
    item,        -- The item being moved / checked
    other,       -- An item colliding with the item being moved
    type,        -- The result of "filter(other)". It's usually "touch", "cross", "slide" or "bounce"
    overlaps,    -- True if item "was overlapping" other when the collision started. False if it didn't but "tunneled" through other
    ti,          -- Number between 0 and 1. How far along the movement to the goal did the collision occur?
    move,        -- Vector({x=number,y=number}). The difference between the original coordinates and the actual ones
    normal,      -- Vector({x=number,y=number}). The collision normal: usually -1,0 or 1 in "x" and "y"
    touch,       -- Vector({x=number,y=number}). The coordinates where item started touching other
    itemRect,    -- The rectangle item occupied when the touch happened ({x = N, y = N, w = N, h = N})
    otherRect    -- The rectangle other occupied when the touch happened ({x = N, y = N, w = N, h = N})
}
```

### World:check

Like `World:move`, but only checks for collisions.
Does not update the position of the item.
Useful for "planning ahead".

```
actualX, actualY, cols, len = World:check(item, goalX, goalY, [filter])
```

**Arguments**

| Name     | Type     | Description                     |
| -------- | -------- | ------------------------------- |
| `item`   | table    | The item to move.               |
| `goalX`  | number   | The desired x position.         |
| `goalY`  | number   | The desired y position.         |
| `filter` | function | The filter function. (optional) |

**Returns**

| Name      | Type   | Description                |
| --------- | ------ | -------------------------- |
| `actualX` | number | The item's new x position. |
| `actualY` | number | The item's new y position. |
| `cols`    | table  | The collisions.            |
| `len`     | number | The number of collisions.  |

### World:queryPoint

Returns all items that overlap with the given point.

```
items, len = World:queryPoint(x,y, [filter])
```

**Arguments**

| Name     | Type     | Description                     |
| -------- | -------- | ------------------------------- |
| `x`      | number   | The x position to query.        |
| `y`      | number   | The y position to query.        |
| `filter` | function | The filter function. (optional) |

- `filter` takes one parameter (an item). `queryPoint` will not return the items that return `false` or `nil` on `filter(item)`.

**Returns**

| Name      | Type   | Description             |
| --------- | ------ | ----------------------- |
| `items`   | table  | The items that overlap. |
| `len`     | number | The number of items.    |

### World:queryRect

Returns all items that overlap with the given rectangle.

```
items, len = World:queryRect(x, y, w, h, [filter])
```

**Arguments**

| Name     | Type     | Description                     |
| -------- | -------- | ------------------------------- |
| `x`      | number   | The x position to query.        |
| `y`      | number   | The y position to query.        |
| `w`      | number   | The width to query.             |
| `h`      | number   | The height to query.            |
| `filter` | function | The filter function. (optional) |

- `filter` takes one parameter (an item). `queryPoint` will not return the items that return `false` or `nil` on `filter(item)`.

**Returns**

| Name      | Type   | Description             |
| --------- | ------ | ----------------------- |
| `items`   | table  | The items that overlap. |
| `len`     | number | The number of items.    |

### World:querySegment

Returns all items that overlap with the given segment.

```
items, len = World:querySegment(x1, y1, x2, y2, [filter])
```

**Arguments**

| Name     | Type     | Description                     |
| -------- | -------- | ------------------------------- |
| `x1`     | number   | The x1 position to query.       |
| `y1`     | number   | The y1 position to query.       |
| `x2`     | number   | The x2 position to query.       |
| `y2`     | number   | The y2 position to query.       |
| `filter` | function | The filter function. (optional) |

- `filter` takes one parameter (an item). `queryPoint` will not return the items that return `false` or `nil` on `filter(item)`.

**Returns**

| Name      | Type   | Description             |
| --------- | ------ | ----------------------- |
| `items`   | table  | The items that overlap. |
| `len`     | number | The number of items.    |

### World:querySegmentWithCoords

Extended version of `World:querySegment` which returns the collision points of the segment with the items, in addition to the items.

```
itemInfo, len = World:querySegmentWithCoords(x1, y1, x2, y2, [filter])
```

**Arguments**

| Name     | Type     | Description                     |
| -------- | -------- | ------------------------------- |
| `x1`     | number   | The x1 position to query.       |
| `y1`     | number   | The y1 position to query.       |
| `x2`     | number   | The x2 position to query.       |
| `y2`     | number   | The y2 position to query.       |
| `filter` | function | The filter function. (optional) |

- `filter` takes one parameter (an item). `queryPoint` will not return the items that return `false` or `nil` on `filter(item)`.

**Returns**

| Name       | Type   | Description             |
| ---------- | ------ | ----------------------- |
| `itemInfo` | table  | The items that overlap. |
| `len`      | number | The number of items.    |

- Each element in `itemInfo` is a table with the following fields:
    - `item`: The item being intersected by the segment.
    - `x1` and `y1`: The coordinates of the first intersection between item and the segment.
    - `x2` and `y2`: The coordinates of the second intersection between item and the segment.
    - `ti1` and `ti2`: Numbers between 0 and 1 which say "how far from the starting point of the segment did the impact happen".

### World:hasItem

Checks if an item is in the world.

```
result = World:hasItem(item)
```

**Arguments**

| Name   | Type   | Description        |
| ------ | ------ | ------------------ |
| `item` | table  | The item to check. |

**Returns**

| Name     | Type    | Description                       |
| -------- | ------- | --------------------------------- |
| `result` | boolean | Whether the item is in the world. |

### World:countItems

Returns the number of items in the world.

```
count = World:countItems()
```

**Arguments**

None

**Returns**

| Name     | Type   | Description                       |
| -------- | ------ | --------------------------------- |
| `count`  | number | The number of items in the world. |

### World:getItems

Returns all items in the world.

```
items, len = World:getItems()
```

**Arguments**

None

**Returns**

| Name    | Type   | Description                        |
| ------- | ------ | ---------------------------------- |
| `items` | table  | The items in the world.            |
| `len`   | number | The number of items in the world.  |

### World:getRect

Returns the bounds of the item.

```
x, y, w, h = World:getRect(item)
```

**Arguments**

| Name   | Type   | Description        |
| ------ | ------ | ------------------ |
| `item` | table  | The item to check. |

**Returns**

| Name     | Type    | Description                 |
| -------- | ------- | --------------------------- |
| `x`      | number  | The x position of the item. |
| `y`      | number  | The y position of the item. |
| `w`      | number  | The width of the item.      |
| `h`      | number  | The height of the item.     |
