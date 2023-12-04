---@meta

---
---`pesto` is the single global table that is exposed to every Pesto app. It contains a set of **modules** and a set of **callbacks**.
---
---@class pesto
pesto = {}

---
---Gets the current version of Pesto.
---
---@return number major # The major version.
---@return number minor # The minor version.
---@return number patch # The patch number.
---@return string codename # The version codename.
function pesto.getVersion() end

---
---Callback that lets you configure default settings for Pesto.
---
---It is called once right before the game starts.
---
---Make sure you put `pesto.conf` in a file called `conf.lua`, a special file that's loaded before the rest of the framework initializes.
---
---@type fun(config: table)
pesto.conf = nil

---
---The main function, containing the main loop. A sensible default is used when left out.
---
---@type fun()
pesto.run = nil

---
---Callback that gets run whenever an error occurs.
---
---It receives a parameter containing the error message.
---
---@type fun(message: string)
pesto.errhand = nil

---
---Callback function used to update the state of the game every frame.
---
---It receives a single parameter, `dt`, which represents the amount of elapsed time between frames.
---
---@type fun(dt: number)
pesto.update = nil

---
---Callback function used to draw on the screen every frame.
---
---@type fun()
pesto.draw = nil

---
---Callback that is called right before the application is about to quit.
---
---If `true` is returned quitting gets aborted.
---
---@type fun():boolean
pesto.quit = nil

---
---Module for filesystem access.
---
---@class pesto.filesystem
pesto.filesystem = {}
