# pesto

The `pesto` table is the only global exposed to every Pesto program.
It contains a set of **modules** and **callbacks**.

## Modules

Modules allow the programmer to do all sorts of things, from drawing stuff on the screen to checking keys on a keyboard.
Each one encapsulates a certain functionality, these are the modules Pesto exposes:

| Name                                | Description                                  |
| ----------------------------------- | :------------------------------------------: |
| [`pesto.animation`](animation.md)   | Sprite animation.                            |
| [`pesto.astar`](astar.md)           | A* Pathfinding.                              |
| [`pesto.audio`](audio.md)           | Audio playing and streaming.                 |
| [`pesto.collision`](collision.md)   | AABB collision detection and response.       |
| [`pesto.ecs`](ecs.md)               | Entity component system.                     |
| [`pesto.filesystem`](filesystem.md) | Filesystem access.                           |
| [`pesto.gamepad`](gamepad.md)       | Gamepad support.                             |
| [`pesto.graphics`](graphics.md)     | Everything related to drawing on the screen. |
| [`pesto.imgui`](imgui.md)           | ImGUI library.                               |
| [`pesto.inspect`](inspect.md)       | Pretty-printing of tables.                   |
| [`pesto.json`](json.md)             | JSON parsing and serialization.              |
| [`pesto.keyboard`](keyboard.md)     | Keyboard support.                            |
| [`pesto.ldtk`](ldtk.md)             | LDTK map editor support.                     |
| [`pesto.log`](log.md)               | Logging.                                     |
| [`pesto.math`](math.md)             | Random and noise.                            |
| [`pesto.mouse`](mouse.md)           | Mouse support.                               |
| [`pesto.reload`](reload.md)         | Hot code reloading.                          |
| [`pesto.rres`](rres.md)             | Resource loading.                            |
| [`pesto.signal`](signal.md)         | Observer pattern.                            |
| [`pesto.state`](state.md)           | State management.                            |
| [`pesto.system`](system.md)         | System management.                           |
| [`pesto.tween`](tween.md)           | Tweening.                                    |
| [`pesto.util`](util.md)             | Various utilities.                           |
| [`pesto.window`](window.md)         | Window management.                           |

## Callbacks

Callbacks are functions you can override and get called by the framework at a specific time.

### pesto.conf

This is a special callback: it needs to be defined in a special file called `conf.lua` next to your `main.lua`.
This file is loaded before everything else, and a configuration table is passed to the function.
This is an example `conf.lua` that sets all the settings to default:

``` lua title="conf.lua"
function pesto.conf(t)
    t.debug = true,                        -- Enables hot code reloading, set it to false when you release!
    t.version = "0.1",                     -- The version of Pesto the project uses
    t.title = "Pesto Project",             -- The title of the window
    t.icon = nil,                          -- Path to an icon image
    t.width = 960,                         -- Starting window width
    t.height = 540,                        -- Starting window height
    t.targetFPS = 60,                      -- FPS limit
    t.resizable = true,                    -- Is the window resizable?
    t.minWidth = 1,                        -- Minimum width of the window
    t.minHeight = 1,                       -- Minimum height of the window
    t.fullscreen = false,                  -- Start in fullscreen mode?
    t.letterbox = true,                    -- Enables resolution scaling
    t.letterboxFilter = "bilinear",        -- Filter to use for the letterbox canvas ("point" or "bilinear")
    t.gameWidth = 960,                     -- Fixed letterbox game width
    t.gameHeight = 540,                    -- Fixed letterbox game height
    t.borderColor = { 50, 79, 59, 255 }    -- Color of the letterbox border
end
```

### pesto.draw

This callback is called every frame and is used to draw on the screen.
Most `pesto.graphics` functions can only be called in here.

``` lua
function pesto.draw()
    -- Your code here
end
```

### pesto.gui

This callback is called every frame and is used to draw the gui on screen.
Most `pesto.imgui` functions can only be called in here.
The callback ignores the `letterbox` configuration.

``` lua
function pesto.gui()
    -- Your code here
end
```

### pesto.quit

This callback is called before quitting the application.
It can be used to perform cleanup work or abort quitting by returning `true`

``` lua
function pesto.quit()
    if shouldQuit() then
        return false
    else
        return true
    end
end
```

### pesto.update

This callback is called every frame and is used to update the program's logic.
It receives a `dt` argument, which contains the time since the last frame.

``` lua
function pesto.update(dt)
    -- Your code here
end
```

## Functions

### pesto.getVersion

Returns the current version of Pesto.

```
major, minor, patch, codename = pesto.getVersion()
```

**Arguments**

None

**Returns**

| Name       | Type   | Description                                        |
| ---------- | ------ | -------------------------------------------------- |
| `major`    | number | The major version.                                 |
| `minor`    | number | The minor version.                                 |
| `patch`    | number | The patch number.                                  |
| `codename` | string | The codename, for example "Saucy Serenade" for 0.1 |
