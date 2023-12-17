# pesto

The `pesto` table is the only global exposed to every Pesto program. It contains a set of **modules** and **callbacks**.

## Modules

Modules allow the programmer to do all sorts of things, from drawing stuff on the screen to checking keys on a keyboard.
Each one encapsulates a certain functionality, these are the modules Pesto exposes:

- [**pesto.animation**](animation.md)
- [**pesto.astar**](astar.md)
- [**pesto.audio**](audio.md)
- [**pesto.collision**](collision.md)
- [**pesto.ecs**](ecs.md)
- [**pesto.filesystem**](filesystem.md)
- [**pesto.gamepad**](gamepad.md)
- [**pesto.graphics**](graphics.md)
- [**pesto.imgui**](imgui.md)
- [**pesto.inspect**](inspect.md)
- [**pesto.json**](json.md)
- [**pesto.keyboard**](keyboard.md)
- [**pesto.ldtk**](ldtk.md)
- [**pesto.log**](log.md)
- [**pesto.math**](math.md)
- [**pesto.mouse**](mouse.md)
- [**pesto.reload**](reload.md)
- [**pesto.rres**](rres.md)
- [**pesto.signal**](signal.md)
- [**pesto.state**](state.md)
- [**pesto.system**](system.md)
- [**pesto.tween**](tween.md)
- [**pesto.util**](util.md)
- [**pesto.window**](window.md)

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

Gets the current version of Pesto.

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
