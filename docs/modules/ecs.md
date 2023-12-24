# pesto.ecs

The `pesto.ecs` module provides a simple entity component system ([ECS](https://en.wikipedia.org/wiki/Entity_component_system)).
It is based on bakpakin's [tiny-ecs](https://github.com/bakpakin/tiny-ecs) library.

## Functions

## Filters

A Filter is a function that selects which Entities apply to a System.
Filters take two parameters, the System and the Entity, and return a boolean value indicating if the Entity should be processed by the System.
A truthy value includes the entity, while a falsey (`nil` or `false`) value excludes the entity.

Filters must be added to Systems by setting the `filter` field of the System.
Filter's returned by `pesto.ecs`'s Filter functions are immutable and can be used by multiple Systems.

Filters can also be passed as arguments to other Filter constructors.
This is a powerful way to create complex, custom Filters that select a very specific set of Entities.

``` lua
filter = pesto.ecs.requireAll("image", pesto.ecs.rejectAny("Player", "Enemy"))
```

### pesto.ecs.requireAll

Returns a Filter that selects Entities with all specified Components and Filters.

```
filter = pesto.ecs.requireAll(...)
```

**Arguments**

`pesto.ecs.requireAll` accepts an arbitrary number of parameters.
They can be either strings (component names) or Filters.

**Returns**

| Name     | Type     | Description             |
| -------- | -------- | ----------------------- |
| `filter` | function | The constructed Filter. |

### pesto.ecs.requireAny

Returns a Filter that selects Entities with at least one of the specified Components and Filters.

```
filter = pesto.ecs.requireAny(...)
```

**Arguments**

`pesto.ecs.requireAny` accepts an arbitrary number of parameters.
They can be either strings (component names) or Filters.

**Returns**

| Name     | Type     | Description             |
| -------- | -------- | ----------------------- |
| `filter` | function | The constructed Filter. |

### pesto.ecs.rejectAll

Returns a Filter that rejects Entities with all specified Components and Filters, and selects all other Entities.

```
filter = pesto.ecs.rejectAll(...)
```

**Arguments**

`pesto.ecs.rejectAll` accepts an arbitrary number of parameters.
They can be either strings (component names) or Filters.

**Returns**

| Name     | Type     | Description             |
| -------- | -------- | ----------------------- |
| `filter` | function | The constructed Filter. |

### pesto.ecs.rejectAny

Returns a Filter that rejects Entities with at least one of the specified Components and Filters, and selects all other Entities.

```
filter = pesto.ecs.rejectAny(...)
```

**Arguments**

`pesto.ecs.rejectAny` accepts an arbitrary number of parameters.
They can be either strings (component names) or Filters.

**Returns**

| Name     | Type     | Description             |
| -------- | -------- | ----------------------- |
| `filter` | function | The constructed Filter. |

### pesto.ecs.filter

Returns a Filter from a string.

```
filter = pesto.ecs.filter(pattern)
```

**Arguments**

| Name      | Type   | Description         |
| --------- | ------ | ------------------- |
| `pattern` | string | The filter pattern. |

Syntax of `pattern` is as follows:

- Tokens are alphanumeric strings including underscores.
- Tokens can be separated by `|`, `&`, or surrounded by parentheses.
- Tokens can be prefixed with `!`, and are then inverted.

``` lua
"a|b|c"          -- Matches entities with an "a" OR "b" OR "c".
"a&!b&c"         -- Matches entities with an "a" AND NOT "b" AND "c".
"a|(b&c&d)|e"    -- Matches "a" OR ("b" AND "c" AND "d") OR "e".
```

**Returns**

| Name     | Type     | Description             |
| -------- | -------- | ----------------------- |
| `filter` | function | The constructed Filter. |

## Systems

A System is a wrapper around function callbacks for manipulating Entities.
Systems are implemented as tables that contain at least one method; an update function that takes parameters like so:

```
function system:update(dt)
```

There are also a few other optional callbacks:

- `function system:filter(entity)`: Returns true if this System should include this Entity, otherwise should return false.
If this isn't specified, no Entities are included in the System.
- `function system:onAdd(entity)`: Called when an Entity is added to the System.
- `function system:onRemove(entity)`: Called when an Entity is removed from the System.
- `function system:onModify(dt)`: Called when the System is modified by adding or removing Entities from the System.
- `function system:onAddToWorld(world)`: Called when the System is added to the World, before any entities are added to the system.
- `function system:onRemoveFromWorld(world)`: Called when the System is removed from the world, after all Entities are removed from the System.
- `function system:preWrap(dt)`: Called on each system before update is called on any system.
- `function system:postWrap(dt)`: Called on each system in reverse order after update is called on each system.

For Filters, it is convenient to use `pesto.ecs.requireAll` or `pesto.ecs.requireAny`, but one can write their own filters as well.
Set the Filter of a System like so:

``` lua
system.filter = pesto.ecs.requireAll("a", "b", "c")
```

or

``` lua
function system:filter(entity)
    return entity.myRequiredComponentName ~= nil
end
```

All Systems also have a few important fields that are initialized when the system is added to the World.
A few are important, and few should be less commonly used.

- The `world` field points to the World that the System belongs to.
Useful for adding and removing Entities from the world dynamically via the System.
- The `active` flag is whether or not the System is updated automatically.
Inactive Systems should be updated manually or not at all via `system:update(dt)`.
Defaults to `true`.
- The `entities` field is an ordered list of Entities in the System.
This list can be used to quickly iterate through all Entities in a System.
- The `interval` field is an optional field that makes Systems update at certain intervals using buffered time, regardless of World update frequency.
For example, to make a System update once a second, set the System's interval to 1.
- The `index` field is the System's index in the World.
Lower indexed Systems are processed before higher indices.
The index is a read only field; to set the index, use `pesto.ecs.setSystemIndex(world, system)`.
- The `indices` field is a table of Entity keys to their indices in the entities list.
Most Systems can ignore this.
- The `modified` flag is an indicator if the System has been modified in the last update.
If so, the `onModify` callback will be called on the System in the next update, if it has one.
This is usually managed by `pesto.ecs`, so users should mostly ignore this, too.

### pesto.ecs.system

Creates a new System or System class from the supplied table.

```
system = pesto.ecs.system([table])
```

**Arguments**

| Name    | Type  | Description                                   |
| ------- | ----- | --------------------------------------------- |
| `table` | table | The table to create a System from. (optional) |

**Returns**

| Name     | Type  | Description     |
| -------- | ----- | --------------- |
| `system` | table | The new System. |

### pesto.ecs.processingSystem

Creates a new Processing System or Processing System class.
Processing Systems process each entity individual, and are usually what is needed.
Processing Systems have three extra callbacks besides those inheritted from vanilla Systems.

``` lua
function system:preProcess(dt)         -- Called before iteration.
function system:process(entity, dt)    -- Process each entity.
function system:postProcess(dt)        -- Called after iteration.
```

Processing Systems have their own `update` method, so don't implement a a custom `update` callback for Processing Systems.

```
system = pesto.ecs.processingSystem([table])
```

**Arguments**

| Name    | Type  | Description                                   |
| ------- | ----- | --------------------------------------------- |
| `table` | table | The table to create a System from. (optional) |

**Returns**

| Name     | Type  | Description     |
| -------- | ----- | --------------- |
| `system` | table | The new System. |

### pesto.ecs.sortedSystem

Creates a new Sorted System or Sorted System class.
Sorted Systems sort their Entities according to a user-defined method, `system:compare(e1, e2)`, which should return `true` if `e1` should come before `e2` and `false` otherwise.
Sorted Systems also override the default System's `onModify` callback, so be careful if defining a custom callback.
However, for processing the sorted entities, consider `pesto.ecs.sortedProcessingSystem(table)`.

```
system = pesto.ecs.sortedSystem([table])
```

**Arguments**

| Name    | Type  | Description                                   |
| ------- | ----- | --------------------------------------------- |
| `table` | table | The table to create a System from. (optional) |

**Returns**

| Name     | Type  | Description     |
| -------- | ----- | --------------- |
| `system` | table | The new System. |

### pesto.ecs.sortedProcessingSystem

Creates a new Sorted Processing System or Sorted Processing System class.
Sorted Processing Systems have both the aspects of Processing Systems and Sorted Systems.

```
system = pesto.ecs.sortedProcessingSystem([table])
```

**Arguments**

| Name    | Type  | Description                                   |
| ------- | ----- | --------------------------------------------- |
| `table` | table | The table to create a System from. (optional) |

**Returns**

| Name     | Type  | Description     |
| -------- | ----- | --------------- |
| `system` | table | The new System. |

## Worlds

A World is a container that manages Entities and Systems.
Typically, a program uses one World at a time.
For all World functions except `pesto.ecs.world(...)`, object-oriented syntax can be used instead of the documented syntax.
For example, `pesto.ecs.add(world, e1, e2, e3)` is the same as `world:add(e1, e2, e3)`.

### pesto.ecs.world

Creates a new World.
Can optionally add default Systems and Entities.
Returns the new World along with default Entities and Systems.

```
world = pesto.ecs.world(...)
```

**Arguments**

`pesto.ecs.world` accepts an arbitrary number of parameters.
They can be Systems or Entities.

**Returns**

| Name    | Type  | Description    |
| ------- | ----- | -------------- |
| `world` | table | The new World. |

### pesto.ecs.addEntity

Adds an Entity to the world.
Also call this on Entities that have changed Components such that they match different Filters.

```
entity = pesto.ecs.addEntity(world, entity)
```

**Arguments**

| Name     | Type  | Description        |
| -------- | ----- | ------------------ |
| `world`  | table | The World.         |
| `entity` | table | The Entity to add. |

**Returns**

| Name     | Type  | Description       |
| -------- | ----- | ----------------- |
| `entity` | table | The added Entity. |

### pesto.ecs.addSystem

Adds a System to the world.

```
system = pesto.ecs.addSystem(world, system)
```

**Arguments**

| Name     | Type  | Description        |
| -------- | ----- | ------------------ |
| `world`  | table | The World.         |
| `system` | table | The System to add. |

**Returns**

| Name     | Type  | Description       |
| -------- | ----- | ----------------- |
| `system` | table | The added System. |

### pesto.ecs.add

Shortcut for adding multiple Entities and Systems to the World.

```
added = pesto.ecs.add(world, ...)
```

**Arguments**

| Name    | Type  | Description |
| ------- | ----- | ----------- |
| `world` | table | The World.  |

`pesto.ecs.add` accepts an arbitrary number of parameters after the World.
They can be Systems or Entities.

**Returns**

| Name    | Type  | Description                     |
| ------- | ----- | ------------------------------- |
| `added` | table | The added Entities and Systems. |

### pesto.ecs.removeEntity

Removes an Entity from the World.

```
entity = pesto.ecs.removeEntity(world, entity)
```

**Arguments**

| Name     | Type  | Description           |
| -------- | ----- | --------------------- |
| `world`  | table | The World.            |
| `entity` | table | The Entity to remove. |

**Returns**

| Name     | Type  | Description         |
| -------- | ----- | ------------------- |
| `entity` | table | The removed Entity. |

### pesto.ecs.removeSystem

Removes a System from the world.

```
system = pesto.ecs.removeSystem(world, system)
```

**Arguments**

| Name     | Type  | Description           |
| -------- | ----- | --------------------- |
| `world`  | table | The World.            |
| `system` | table | The System to remove. |

**Returns**

| Name     | Type  | Description         |
| -------- | ----- | ------------------- |
| `system` | table | The removed System. |

### pesto.ecs.remove

Shortcut for removing multiple Entities and Systems from the World.

```
removed = pesto.ecs.remove(world, ...)
```

**Arguments**

| Name    | Type  | Description |
| ------- | ----- | ----------- |
| `world` | table | The World.  |

`pesto.ecs.remove` accepts an arbitrary number of parameters after the World.
They can be Systems or Entities.

**Returns**

| Name      | Type  | Description                       |
| --------- | ----- | --------------------------------- |
| `removed` | table | The removed Entities and Systems. |

### pesto.ecs.refresh

Manages Entities and Systems marked for deletion or addition.
Call this before modifying Systems and Entities outside of a call to `pesto.ecs.update`.
Do not call this within a call to `pesto.ecs.update`.

```
pesto.ecs.refresh(world)
```

**Arguments**

| Name    | Type  | Description |
| ------- | ----- | ----------- |
| `world` | table | The World.  |

**Returns**

None

### pesto.ecs.update

Updates the World by `dt` (delta time).
Takes an optional parameter, filter, which is a Filter that selects Systems from the World, and updates only those Systems.
If filter is not supplied, all Systems are updated.
Put this function in your main loop.

```
pesto.ecs.update(world, dt, [filter])
```

**Arguments**

| Name     | Type   | Description            |
| -------- | ------ | ---------------------- |
| `world`  | table  | The World.             |
| `dt`     | number | The delta time.        |
| `filter` | table  | The Filter. (optional) |

**Returns**

None

### pesto.ecs.clearEntities

Removes all Entities from the World.

```
pesto.ecs.clearEntities(world)
```

**Arguments**

| Name    | Type  | Description |
| ------- | ----- | ----------- |
| `world` | table | The World.  |

**Returns**

None

### pesto.ecs.clearSystems

Removes all Systems from the World.

```
pesto.ecs.clearSystems(world)
```

**Arguments**

| Name    | Type  | Description |
| ------- | ----- | ----------- |
| `world` | table | The World.  |

**Returns**

None

### pesto.ecs.getEntityCount

Returns the number of Entities in the World.

```
count = pesto.ecs.getEntityCount(world)
```

**Arguments**

| Name    | Type  | Description |
| ------- | ----- | ----------- |
| `world` | table | The World.  |

**Returns**

| Name    | Type   | Description             |
| ------- | ------ | ----------------------- |
| `count` | number | The number of Entities. |

### pesto.ecs.getSystemCount

Returns the number of Systems in the World.

```
count = pesto.ecs.getSystemCount(world)
```

**Arguments**

| Name    | Type  | Description |
| ------- | ----- | ----------- |
| `world` | table | The World.  |

**Returns**

| Name    | Type   | Description            |
| ------- | ------ | ---------------------- |
| `count` | number | The number of Systems. |

### pesto.ecs.setSystemIndex

Sets the `index` of a System in the World, and returns the old `index`.
Changes the order in which they are processed, because lower indexed Systems are processed first.

```
oldIndex = pesto.ecs.setSystemIndex(world, system, index)
```

**Arguments**

| Name     | Type   | Description    |
| -------- | ------ | -------------- |
| `world`  | table  | The World.     |
| `system` | table  | The System.    |
| `index`  | number | The new index. |

**Returns**

| Name       | Type   | Description    |
| ---------- | ------ | -------------- |
| `oldIndex` | number | The old index. |
