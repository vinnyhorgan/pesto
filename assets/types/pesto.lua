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

---
---The `pesto.window` module provides functions for managing window properties and behavior.
---
---@class pesto.window
pesto.window = {}

---
---Closes the window.
---
---Does not quit the application, use `pesto.system.quit()` instead.
---
function pesto.window.close() end

---
---Gets the index of the current monitor.
---
---@return number monitorIndex # The index of the current monitor.
function pesto.window.getCurrentMonitor() end

---
---Gets the DPI scale of the window.
---
---@return number scaleX # The horizontal DPI scale.
---@return number scaleY # The vertical DPI scale.
function pesto.window.getDPIScale() end

---
---Gets the height of the window.
---
---@return number height # The height of the window.
function pesto.window.getHeight() end

---
---Gets the number of available monitors.
---
---@return number count # The number of available monitors.
function pesto.window.getMonitorCount() end

---
---Gets the height of a specific monitor.
---
---@param monitorIndex number # The index of the monitor.
---@return number height # The height of the monitor.
function pesto.window.getMonitorHeight(monitorIndex) end

---
---Gets the name of a specific monitor.
---
---@param monitorIndex number # The index of the monitor.
---@return string name # The name of the monitor.
function pesto.window.getMonitorName(monitorIndex) end

---
---Gets the physical height of a specific monitor in millimeters.
---
---@param monitorIndex number # The index of the monitor.
---@return number physicalHeight # The physical height of the monitor.
function pesto.window.getMonitorPhysicalHeight(monitorIndex) end

---
---Gets the physical width of a specific monitor in millimeters.
---
---@param monitorIndex number # The index of the monitor.
---@return number physicalWidth # The physical width of the monitor.
function pesto.window.getMonitorPhysicalWidth(monitorIndex) end

---
---Gets the position of a specific monitor.
---
---@param monitorIndex number # The index of the monitor.
---@return number x # The x-coordinate of the monitor's position.
---@return number y # The y-coordinate of the monitor's position.
function pesto.window.getMonitorPosition(monitorIndex) end

---
---Gets the refresh rate of a specific monitor.
---
---@param monitorIndex number # The index of the monitor.
---@return number refreshRate # The refresh rate of the monitor.
function pesto.window.getMonitorRefreshRate(monitorIndex) end

---
---Gets the width of a specific monitor.
---
---@param monitorIndex number # The index of the monitor.
---@return number width # The width of the monitor.
function pesto.window.getMonitorWidth(monitorIndex) end

---
---Gets the position of the window.
---
---@return number x # The x-coordinate of the window's position.
---@return number y # The y-coordinate of the window's position.
function pesto.window.getPosition() end

---
---Gets whether the window is resizable.
---
---@return boolean resizable # Returns true if the window is resizable, false otherwise.
function pesto.window.getResizable() end

---
---Gets whether VSync is enabled.
---
---@return boolean vsync # Returns true if VSync is enabled, false otherwise.
function pesto.window.getVSync() end

---
---Gets the width of the window.
---
---@return number width # The width of the window.
function pesto.window.getWidth() end

---
---Initializes the window with specified width, height, and title.
---
---@param width number # The width of the window.
---@param height number # The height of the window.
---@param title string # The title of the window.
function pesto.window.init(width, height, title) end

---
---Checks whether the window is focused.
---
---@return boolean focused # Returns true if the window is focused, false otherwise.
function pesto.window.isFocused() end

---
---Checks whether the window is in fullscreen mode.
---
---@return boolean fullscreen # Returns true if the window is in fullscreen mode, false otherwise.
function pesto.window.isFullscreen() end

---
---Checks whether the window is hidden.
---
---@return boolean hidden # Returns true if the window is hidden, false otherwise.
function pesto.window.isHidden() end

---
---Checks whether the window is maximized.
---
---@return boolean maximized # Returns true if the window is maximized, false otherwise.
function pesto.window.isMaximized() end

---
---Checks whether the window is minimized.
---
---@return boolean minimized # Returns true if the window is minimized, false otherwise.
function pesto.window.isMinimized() end

---
---Checks whether the window is ready.
---
---@return boolean ready # Returns true if the window is ready, false otherwise.
function pesto.window.isReady() end

---
---Checks whether the window has been resized.
---
---@return boolean resized # Returns true if the window has been resized, false otherwise.
function pesto.window.isResized() end

---
---Maximizes the window.
---
function pesto.window.maximize() end

---
---Minimizes the window.
---
function pesto.window.minimize() end

---
---Restores the window from minimized/maximized state.
---
function pesto.window.restore() end

---
---Sets the window focused.
---
function pesto.window.setFocused() end

---
---Sets the window icon with a provided Texture.
---
---@param icon pesto.Texture # The Texture object to set as the window icon.
function pesto.window.setIcon(icon) end

---
---Sets the maximum size of the window.
---
---@param width number # The maximum width of the window.
---@param height number # The maximum height of the window.
function pesto.window.setMaxSize(width, height) end

---
---Sets the minimum size of the window.
---
---@param width number # The minimum width of the window.
---@param height number # The minimum height of the window.
function pesto.window.setMinSize(width, height) end

---
---Sets the window to a specified monitor.
---
---@param monitorIndex number # The index of the monitor.
function pesto.window.setMonitor(monitorIndex) end

---
---Sets the opacity of the window.
---
---@param opacity number # The opacity value (0.0 - 1.0).
function pesto.window.setOpacity(opacity) end

---
---Sets the position of the window.
---
---@param x number # The x-coordinate of the window's position.
---@param y number # The y-coordinate of the window's position.
function pesto.window.setPosition(x, y) end

---
---Sets whether the window is resizable.
---
---@param resizable boolean # Whether the window should be resizable (true or false).
function pesto.window.setResizable(resizable) end

---
---Sets the size of the window.
---
---@param width number # The width of the window.
---@param height number # The height of the window.
function pesto.window.setSize(width, height) end

---
---Sets the title of the window.
---
---@param title string # The title of the window.
function pesto.window.setTitle(title) end

---
---Sets the target frames-per-second (FPS) of the window.
---
---@param fps number # The target frames-per-second (FPS).
function pesto.window.setTargetFPS(fps) end

---
---Sets whether VSync is enabled for the window.
---
---@param vsync boolean # Whether VSync should be enabled (true or false).
function pesto.window.setVSync(vsync) end

---
---Checks if the window should close.
---
---@return boolean shouldClose # Returns true if the window should close, false otherwise.
function pesto.window.shouldClose() end

---
---Toggles between borderless and windowed mode.
---
function pesto.window.toggleBorderless() end

---
---Toggles between fullscreen and windowed mode.
---
function pesto.window.toggleFullscreen() end
