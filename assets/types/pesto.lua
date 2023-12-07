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

---
---The `pesto.mouse` module provides functions for interacting with the mouse input.
---
---@class pesto.mouse
pesto.mouse = {}

---
---Disables the mouse cursor.
---
function pesto.mouse.disable() end

---
---Enables the mouse cursor.
---
function pesto.mouse.enable() end

---
---Gets the change in mouse position since the last frame.
---
---@return number deltaX # Change in X position.
---@return number deltaY # Change in Y position.
function pesto.mouse.getDelta() end

---
---Gets the current X coordinate of the mouse cursor.
---
---@return number x # The X coordinate of the mouse cursor.
function pesto.mouse.getX() end

---
---Gets the current Y coordinate of the mouse cursor.
---
---@return number y # The Y coordinate of the mouse cursor.
function pesto.mouse.getY() end

---
---Gets the movement of the mouse wheel.
---
---@return number deltaX # Horizontal movement of the mouse wheel.
---@return number deltaY # Vertical movement of the mouse wheel.
function pesto.mouse.getWheelMove() end

---
---Gets the current position of the mouse cursor.
---
---@return number x # The X coordinate of the mouse cursor.
---@return number y # The Y coordinate of the mouse cursor.
function pesto.mouse.getPosition() end

---
---Hides the mouse cursor.
---
function pesto.mouse.hide() end

---
---Checks if a mouse button is currently pressed down.
---
---@param button number # The button ID to check.
---@return boolean # Returns true if the button is pressed, false otherwise.
function pesto.mouse.isDown(button) end

---
---Checks if the mouse cursor is currently hidden.
---
---@return boolean # Returns true if the cursor is hidden, false otherwise.
function pesto.mouse.isHidden() end

---
---Checks if the mouse cursor is within the screen boundaries.
---
---@return boolean # Returns true if the cursor is within the screen, false otherwise.
function pesto.mouse.isOnScreen() end

---
---Checks if a mouse button was pressed during the last frame.
---
---@param button number # The button ID to check.
---@return boolean # Returns true if the button was pressed, false otherwise.
function pesto.mouse.isPressed(button) end

---
---Checks if a mouse button was released during the last frame.
---
---@param button number # The button ID to check.
---@return boolean # Returns true if the button was released, false otherwise.
function pesto.mouse.isReleased(button) end

---
---Checks if a mouse button is currently up (not pressed).
---
---@param button number # The button ID to check.
---@return boolean # Returns true if the button is up, false otherwise.
function pesto.mouse.isUp(button) end

---
---Sets the mouse cursor type.
---
---@param cursor string # The type of cursor to set (e.g., "default", "arrow").
function pesto.mouse.setCursor(cursor) end

---
---Sets the scale of the mouse cursor.
---
---@param x number # The scale factor along the X-axis.
---@param y number # The scale factor along the Y-axis.
function pesto.mouse.setScale(x, y) end

---
---Sets the offset of the mouse cursor.
---
---@param x number # The offset along the X-axis.
---@param y number # The offset along the Y-axis.
function pesto.mouse.setOffset(x, y) end

---
---Sets the position of the mouse cursor.
---
---@param x number # The X coordinate to set.
---@param y number # The Y coordinate to set.
function pesto.mouse.setPosition(x, y) end

---
---Shows the mouse cursor.
---
function pesto.mouse.show() end

---
---The `pesto.keyboard` module provides functions for interacting with keyboard input.
---
---@class pesto.keyboard
pesto.keyboard = {}

---
---Gets the unicode value of the character pressed on the keyboard.
---
---@return number # Unicode value of the pressed character.
function pesto.keyboard.getCharPressed() end

---
---Gets the key code of the key currently pressed on the keyboard.
---
---@return number # Key code of the currently pressed key.
function pesto.keyboard.getPressed() end

---
---Checks if a specific key is currently held down.
---
---@param key string # The key to check (e.g., "a", "space").
---@return boolean # Returns true if the key is down, false otherwise.
function pesto.keyboard.isDown(key) end

---
---Checks if a specific key was pressed during the last frame.
---
---@param key string # The key to check (e.g., "a", "space").
---@return boolean # Returns true if the key was pressed, false otherwise.
function pesto.keyboard.isPressed(key) end

---
---Checks if a specific key is being held down and repeated.
---
---@param key string # The key to check (e.g., "a", "space").
---@return boolean # Returns true if the key is being repeated, false otherwise.
function pesto.keyboard.isPressedRepeat(key) end

---
---Checks if a specific key was released during the last frame.
---
---@param key string # The key to check (e.g., "a", "space").
---@return boolean # Returns true if the key was released, false otherwise.
function pesto.keyboard.isReleased(key) end

---
---Checks if a specific key is currently up (not pressed).
---
---@param key string # The key to check (e.g., "a", "space").
---@return boolean # Returns true if the key is up, false otherwise.
function pesto.keyboard.isUp(key) end

---
---The `pesto.gamepad` module provides functions for interacting with gamepad input.
---
---@class pesto.gamepad
pesto.gamepad = {}

---
---Gets the number of axes available on the specified gamepad.
---
---@param gamepad number # The ID of the gamepad.
---@return number # The number of axes available.
function pesto.gamepad.getAxisCount(gamepad) end

---
---Gets the movement value of the specified axis on the gamepad.
---
---@param gamepad number # The ID of the gamepad.
---@param axis number # The axis ID to query.
---@return number # The movement value of the axis.
function pesto.gamepad.getAxisMovement(gamepad, axis) end

---
---Gets the name of the specified gamepad.
---
---@param gamepad number # The ID of the gamepad.
---@return string # The name of the gamepad.
function pesto.gamepad.getName(gamepad) end

---
---Gets the ID of the button currently being pressed on any gamepad.
---
---@return number # The ID of the pressed button.
function pesto.gamepad.getPressed() end

---
---Checks if the specified gamepad is available.
---
---@param gamepad number # The ID of the gamepad.
---@return boolean # Returns true if the gamepad is available, false otherwise.
function pesto.gamepad.isAvailable(gamepad) end

---
---Checks if the specified button on the gamepad is currently down.
---
---@param gamepad number # The ID of the gamepad.
---@param button number # The button ID to check.
---@return boolean # Returns true if the button is currently down, false otherwise.
function pesto.gamepad.isDown(gamepad, button) end

---
---Checks if the specified button on the gamepad was pressed during the last frame.
---
---@param gamepad number # The ID of the gamepad.
---@param button number # The button ID to check.
---@return boolean # Returns true if the button was pressed, false otherwise.
function pesto.gamepad.isPressed(gamepad, button) end

---
---Checks if the specified button on the gamepad was released during the last frame.
---
---@param gamepad number # The ID of the gamepad.
---@param button number # The button ID to check.
---@return boolean # Returns true if the button was released, false otherwise.
function pesto.gamepad.isReleased(gamepad, button) end

---
---Checks if the specified button on the gamepad is currently up (not pressed).
---
---@param gamepad number # The ID of the gamepad.
---@param button number # The button ID to check.
---@return boolean # Returns true if the button is up, false otherwise.
function pesto.gamepad.isUp(gamepad, button) end

---
---Sets the mappings for the gamepad.
---
---@param mappings string # The mapping configuration for the gamepad.
function pesto.gamepad.setMappings(mappings) end

---
---The `pesto.math` module provides various mathematical functions and utilities.
---
---@class pesto.math
pesto.math = {}

---
---Calculates 2D Simplex noise at a given (x, y) coordinate.
---
---@param x number # The x-coordinate.
---@param y number # The y-coordinate.
---@return number result # The calculated noise value.
function pesto.math.noise2d(x, y) end

---
---Calculates 3D Simplex noise at a given (x, y, z) coordinate.
---
---@param x number # The x-coordinate.
---@param y number # The y-coordinate.
---@param z number # The z-coordinate.
---@return number result # The calculated noise value.
function pesto.math.noise3d(x, y, z) end

---
---Generates a random integer within the specified range.
---
---@param min number # The minimum value of the range.
---@param max number # The maximum value of the range.
---@return number result # The generated random integer.
function pesto.math.random(min, max) end

---
---Sets the frequency for Simplex noise calculations.
---
---@param frequency number # The frequency value to set.
function pesto.math.setNoiseFrequency(frequency) end

---
---Sets the seed value for Simplex noise calculations.
---
---@param seed number # The seed value to set.
function pesto.math.setNoiseSeed(seed) end

---
---Sets the seed for the random number generator.
---
---@param seed number # The seed value to set.
function pesto.math.setRandomSeed(seed) end

---
---The `pesto.log` module provides logging functionalities.
---
---@class pesto.log
pesto.log = {}

---
---Logs a message at debug level.
---
---@param message string # The message to log.
function pesto.log.debug(message) end

---
---Logs a message at error level.
---
---@param message string # The message to log.
function pesto.log.error(message) end

---
---Logs a message at fatal level.
---
---@param message string # The message to log.
function pesto.log.fatal(message) end

---
---Logs a message at info level.
---
---@param message string # The message to log.
function pesto.log.info(message) end

---
---Sets the log level.
---
---@param level string # The log level to set ("trace", "debug", "info", "warn", "error", "fatal").
function pesto.log.level(level) end

---
---Logs a message at trace level.
---
---@param message string # The message to log.
function pesto.log.trace(message) end

---
---Logs a message at warning level.
---
---@param message string # The message to log.
function pesto.log.warn(message) end
