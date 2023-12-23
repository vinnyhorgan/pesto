# pesto.astar

The `pesto.astar` module provides an implementation of the [A*](https://en.wikipedia.org/wiki/A*_search_algorithm) pathfinding algorithm.
It is based on the [lua-star](https://github.com/wesleywerner/lua-star) library.

## Functions

### pesto.astar:find

Finds the path between two nodes.

```
path = pesto.astar:find(width, height, start, goal, isWalkable, useCache, excludeDiagonal)
```

**Arguments**

| Name              | Type     | Default | Description                                                                      |
| ----------------- | -------- | ------- | -------------------------------------------------------------------------------- |
| `width`           | number   |         | The width of the map.                                                            |
| `height`          | number   |         | The height of the map.                                                           |
| `start`           | table    |         | The start node. (table with `x` and `y` keys)                                    |
| `goal`            | table    |         | The goal node. (table with `x` and `y` keys)                                     |
| `isWalkable`      | function |         | A function that accepts an `x` and `y` and returns `true` if a node is walkable. |
| `useCache`        | boolean  | false   | Whether to use the cache.                                                        |
| `excludeDiagonal` | boolean  | false   | Whether to exclude diagonal movement.                                            |

**Returns**

| Name     | Type   | Description                                                    |
| -------- | ------ | -------------------------------------------------------------- |
| `path`   | table  | The path from `start` to `goal`. (`false` if no path is found) |

### pesto.astar:clearCached

Clears all cached paths.

```
pesto.astar:clearCached()
```

**Arguments**

None

**Returns**

None
