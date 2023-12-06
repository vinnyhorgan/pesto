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

---@class pesto.Texture
local Texture = {}

---
---The `pesto.rres` module provides functions for interacting with `.rres` resource files.
---
---@class pesto.rres
pesto.rres = {}

---
---Gets information about a `.rres` resource file.
---
---@param rresFilename string # The name of the `.rres` resource file.
---@return table info # Information about the resource file.
function pesto.rres.getInfo(rresFilename) end

---
---Loads a text file from a `.rres` resource file.
---
---@param rresFilename string # The name of the `.rres` resource file.
---@param filename string # The name of the text file.
---@return string text # The contents of the text file.
function pesto.rres.loadText(rresFilename, filename) end

---
---Loads an image file from a `.rres` resource file.
---
---@param rresFilename string # The name of the `.rres` resource file.
---@param filename string # The name of the image file.
---@return pesto.Texture image # The image.
function pesto.rres.loadTexture(rresFilename, filename) end

---
---The `pesto.system` module provides functions for interacting with the operating system.
---
---@class pesto.system
pesto.system = {}

---
---Gets the clipboard text.
---
---@return string text # The clipboard text.
function pesto.system.getClipboardText() end

---
---Gets the operating system.
---
---@return string os # The operating system.
function pesto.system.getOS() end

---
---Gets the time since the game started.
---
---@return number time # The time in seconds.
function pesto.system.getTime() end

---
---Opens a URL in the default browser.
---
---@param url string # The URL to open.
function pesto.system.openURL(url) end

---
---Quits the application.
---
function pesto.system.quit() end

---
---Sets the clipboard text.
---
---@param text string # The text to set.
function pesto.system.setClipboardText(text) end

---
---Sleeps the current thread.
---
---@param seconds number # The number of seconds to sleep.
function pesto.system.sleep(seconds) end

---
---Takes a screenshot.
---
---@param filename string # The name of the screenshot.
function pesto.system.takeScreenshot(filename) end
