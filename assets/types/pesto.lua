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
---Callback function used to draw the imgui every frame.
---
---@type fun()
pesto.gui = nil

---
---Callback that is called right before the application is about to quit.
---
---If `true` is returned quitting gets aborted.
---
---@type fun():boolean
pesto.quit = nil

---@class pesto.Canvas
local Canvas = {}

---@class pesto.Font
local Font = {}

---@class pesto.Shader
local Shader = {}

---@class pesto.Texture
local Texture = {}

---@class pesto.Sound
local Sound = {}

---@class pesto.Stream
local Stream = {}

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

---
---The `pesto.filesystem` module provides filesystem-related functionalities.
---
---@class pesto.filesystem
pesto.filesystem = {}

---
---Changes the current working directory.
---
---@param dir string # The directory path to change to.
---@return boolean # Returns true if successful, false otherwise.
function pesto.filesystem.changeDirectory(dir) end

---
---Creates a new directory.
---
---@param dirpath string # The directory path to create.
---@return boolean # Returns true if successful, false otherwise.
function pesto.filesystem.createDirectory(dirpath) end

---
---Checks whether a file or directory exists.
---
---@param path string # The path to the file or directory.
---@return boolean # Returns true if the file or directory exists, false otherwise.
function pesto.filesystem.exists(path) end

---
---Gets the application directory.
---
---@return string # The application directory path.
function pesto.filesystem.getApplicationDirectory() end

---
---Gets a list of items in a directory.
---
---@param basepath string # The base directory path.
---@param filter string | nil # Optional filter for file names (can be nil).
---@param scanSubdirs boolean | nil # Indicates whether to scan subdirectories.
---@return table | nil # Returns a table containing directory items, or nil if no items found.
function pesto.filesystem.getDirectoryItems(basepath, filter, scanSubdirs) end

---
---Gets a list of dropped items.
---
---@return table | nil # Returns a table containing dropped file paths, or nil if none dropped.
function pesto.filesystem.getDroppedItems() end

---
---Gets the last modified time of a file.
---
---@param filename string # The file path.
---@return number # Returns the last modified time in seconds since epoch.
function pesto.filesystem.getLastModified(filename) end

---
---Gets the real directory path from a file path.
---
---@param filepath string # The file path.
---@return string # Returns the real directory path.
function pesto.filesystem.getRealDirectory(filepath) end

---
---Gets the size of a file in bytes.
---
---@param filename string # The file path.
---@return number # Returns the file size in bytes.
function pesto.filesystem.getSize(filename) end

---
---Gets the current working directory.
---
---@return string # Returns the current working directory path.
function pesto.filesystem.getWorkingDirectory() end

---
---Checks if a path is a directory.
---
---@param path string # The path to check.
---@return boolean # Returns true if the path is a directory, false otherwise.
function pesto.filesystem.isDirectory(path) end

---
---Checks if a path is a file.
---
---@param path string # The path to check.
---@return boolean # Returns true if the path is a file, false otherwise.
function pesto.filesystem.isFile(path) end

---
---Checks if a file has been dropped on the window.
---
---@return boolean # Returns true if a file has been dropped, false otherwise.
function pesto.filesystem.isFileDropped() end

---
---Reads the contents of a text file.
---
---@param filename string # The file path to read.
---@return string | nil # Returns the file content as a string, or nil if read fails.
function pesto.filesystem.read(filename) end

---
---Removes a file or empty directory.
---
---@param filename string # The file or directory path to remove.
---@return boolean # Returns true if successful, false otherwise.
function pesto.filesystem.remove(filename) end

---
---Writes text content to a file.
---
---@param filename string # The file path to write to.
---@param text string # The text content to write.
---@return boolean # Returns true if writing is successful, false otherwise.
function pesto.filesystem.write(filename, text) end

---
---The `pesto.audio` module provides audio-related functionalities.
---
---@class pesto.audio
pesto.audio = {}

---
---Closes the audio device.
---
function pesto.audio.close() end

---
---Gets the master volume.
---
---@return number # The master volume.
function pesto.audio.getVolume() end

---
---Initializes the audio device.
---
function pesto.audio.init() end

---
---Checks if the audio device is ready.
---
---@return boolean # Returns true if the audio device is ready, false otherwise.
function pesto.audio.isReady() end

---
---Loads a sound file.
---
---@param filename string # The path to the sound file.
---@return pesto.Sound # Returns a loaded sound.
function pesto.audio.loadSound(filename) end

---
---Loads a music stream.
---
---@param filename string # The path to the music stream file.
---@return pesto.Stream # Returns a loaded stream.
function pesto.audio.loadStream(filename) end

---
---Sets the master volume.
---
---@param volume number # The volume to set.
function pesto.audio.setVolume(volume) end

---
---The `pesto.imgui` module provides a simple binding to the ImGui library.
---
---@class pesto.imgui
pesto.imgui = {}

---
---Begins drawing ImGui elements.
---
function pesto.imgui.beginDrawing() end

---
---Closes the ImGui environment.
---
function pesto.imgui.close() end

---
---Ends the ImGui drawing.
---
function pesto.imgui.endDrawing() end

---
---Initializes the ImGui environment.
---
function pesto.imgui.init() end

---
---Begins a new ImGui window.
---
---@param name string # The name of the window.
---@param ... string # Additional window flags.
---@return boolean # Returns true if the window is active, false otherwise.
function pesto.imgui.beginWindow(name, ...) end

---
---Ends the current ImGui window.
---
function pesto.imgui.endWindow() end

---
---Shows the ImGui demo window.
---
---@return boolean # Returns true if the demo window is active, false otherwise.
function pesto.imgui.showDemoWindow() end

---
---Displays text within the ImGui window.
---
---@param text string # The text to display.
function pesto.imgui.text(text) end

---
---Creates a button in the ImGui window.
---
---@param label string # The label of the button.
---@param width? number # Optional width of the button.
---@param height? number # Optional height of the button.
---@return boolean # Returns true if the button is pressed, false otherwise.
function pesto.imgui.button(label, width, height) end

---
---Creates a checkbox in the ImGui window.
---
---@param label string # The label of the checkbox.
---@param checked boolean # The initial state of the checkbox.
---@return boolean, boolean # Returns the current state of the checkbox and whether it was modified.
function pesto.imgui.checkbox(label, checked) end

---
---Creates a text input field in the ImGui window.
---
---@param label string # The label of the input field.
---@param defaultText string # The default text for the input field.
---@return string, boolean # Returns the entered text and whether the input field was modified.
function pesto.imgui.inputText(label, defaultText) end

---
---Creates a floating-point slider in the ImGui window.
---
---@param label string # The label of the slider.
---@param value number # The initial value of the slider.
---@param min number # The minimum value of the slider.
---@param max number # The maximum value of the slider.
---@return number, boolean # Returns the current value of the slider and whether it was modified.
function pesto.imgui.sliderFloat(label, value, min, max) end

---
---Creates an integer slider in the ImGui window.
---
---@param label string # The label of the slider.
---@param value number # The initial value of the slider.
---@param min number # The minimum value of the slider.
---@param max number # The maximum value of the slider.
---@return number, boolean # Returns the current value of the slider and whether it was modified.
function pesto.imgui.sliderInt(label, value, min, max) end

---
---Creates a color picker for three floating-point values in the ImGui window (RGB).
---
---@param label string # The label of the color picker.
---@param r number # The initial red value.
---@param g number # The initial green value.
---@param b number # The initial blue value.
---@return number, number, number, boolean # Returns the current RGB values and whether they were modified.
function pesto.imgui.colorEdit3(label, r, g, b) end

---
---Creates a color picker for four floating-point values in the ImGui window (RGBA).
---
---@param label string # The label of the color picker.
---@param r number # The initial red value.
---@param g number # The initial green value.
---@param b number # The initial blue value.
---@param a number # The initial alpha value.
---@return number, number, number, number, boolean # Returns the current RGBA values and whether they were modified.
function pesto.imgui.colorEdit4(label, r, g, b, a) end

---
---Displays an image in the ImGui window.
---
---@param texture pesto.Texture # The image texture.
function pesto.imgui.image(texture) end

---
---Inserts a horizontal separator in the ImGui window.
---
function pesto.imgui.separator() end

---
---Moves the next item to the same line in the ImGui window.
---
---@param offset? number # Optional offset from the start of the line.
---@param spacing? number # Optional spacing from the previous item.
function pesto.imgui.sameLine(offset, spacing) end

---
---Sets the next window's position in the ImGui window.
---
---@param x number # The x-coordinate of the window's position.
---@param y number # The y-coordinate of the window's position.
---@param condition? string # Optional condition for setting the position ("none", "always", "once", "firstUseEver", "appearing").
function pesto.imgui.setNextWindowPos(x, y, condition) end

---
---Sets the next window's size in the ImGui window.
---
---@param x number # The x-coordinate of the window's size.
---@param y number # The y-coordinate of the window's size.
---@param condition? string # Optional condition for setting the size ("none", "always", "once", "firstUseEver", "appearing").
function pesto.imgui.setNextWindowSize(x, y, condition) end

---
---Begins the main menu bar in the ImGui window.
---
---@return boolean # Returns true if the main menu bar is active.
function pesto.imgui.beginMainMenuBar() end

---
---Ends the main menu bar in the ImGui window.
---
function pesto.imgui.endMainMenuBar() end

---
---Begins a menu bar in the ImGui window.
---
---@return boolean # Returns true if the menu bar is active.
function pesto.imgui.beginMenuBar() end

---
---Ends the menu bar in the ImGui window.
---
function pesto.imgui.endMenuBar() end

---
---Begins a menu in the ImGui window.
---
---@param label string # The label of the menu.
---@param enabled? boolean # Optional parameter for menu enablement.
---@return boolean # Returns true if the menu is active.
function pesto.imgui.beginMenu(label, enabled) end

---
---Ends the menu in the ImGui window.
---
function pesto.imgui.endMenu() end

---
---Adds a menu item in the ImGui window.
---
---@param label string # The label of the menu item.
---@param shortcut? string # Optional keyboard shortcut for the menu item.
---@param selected? boolean # Optional parameter for initial selection of the menu item.
---@param enabled? boolean # Optional parameter for enabling the menu item.
---@return boolean # Returns true if the menu item is selected.
function pesto.imgui.menuItem(label, shortcut, selected, enabled) end

---
---The `pesto.graphics` module provides functions for graphics rendering.
---
---@class pesto.graphics
pesto.graphics = {}

---
---Begins the drawing process.
---
function pesto.graphics.beginDrawing() end

---
---Draws a filled circle.
---
---@param x number # The x-coordinate of the circle's center.
---@param y number # The y-coordinate of the circle's center.
---@param radius number # The radius of the circle.
function pesto.graphics.circle(x, y, radius) end

---
---Draws an outlined circle.
---
---@param x number # The x-coordinate of the circle's center.
---@param y number # The y-coordinate of the circle's center.
---@param radius number # The radius of the circle.
function pesto.graphics.circleLines(x, y, radius) end

---
---Clears the screen with a specified color.
---
---@param r number? # Red component (0-255).
---@param g number? # Green component (0-255).
---@param b number? # Blue component (0-255).
---@param a number? # Alpha component (0-255).
function pesto.graphics.clear(r, g, b, a) end

---
---Ends the drawing process.
---
function pesto.graphics.endDrawing() end

---
---Gets the current color used for drawing.
---
---@return number, number, number, number # The current color used for drawing.
function pesto.graphics.getColor() end

---
---Gets the time difference between frames.
---
---@return number deltaTime # The time difference between frames in seconds.
function pesto.graphics.getDelta() end

---
---Gets the frames per second (FPS) of the application.
---
---@return number fps # The current FPS value.
function pesto.graphics.getFPS() end

---
---Draws a line between two points.
---
---@param x1 number # The x-coordinate of the starting point.
---@param y1 number # The y-coordinate of the starting point.
---@param x2 number # The x-coordinate of the ending point.
---@param y2 number # The y-coordinate of the ending point.
function pesto.graphics.line(x1, y1, x2, y2) end

---
---Loads a canvas with specified width and height.
---
---@param width number # The width of the canvas.
---@param height number # The height of the canvas.
---@return pesto.Canvas canvas # RenderTexture object representing the canvas.
function pesto.graphics.loadCanvas(width, height) end

---
---Loads a font from a file with a specified size.
---
---@param filename string # The path to the font file.
---@param size number # The size of the font.
---@return pesto.Font font # Font object loaded from the file.
function pesto.graphics.loadFont(filename, size) end

---
---Loads a shader from vertex and fragment shader files.
---
---@param vsFilename string # The path to the vertex shader file.
---@param fsFilename string # The path to the fragment shader file.
---@return pesto.Shader shader # Shader object loaded from the files.
function pesto.graphics.loadShader(vsFilename, fsFilename) end

---
---Loads a texture from an image file.
---
---@param filename string # The path to the image file.
---@return pesto.Texture # Texture object loaded from the file.
function pesto.graphics.loadTexture(filename) end

---
---Draws a single pixel at the specified position.
---
---@param x number # The x-coordinate of the pixel.
---@param y number # The y-coordinate of the pixel.
function pesto.graphics.pixel(x, y) end

---
---Draws a polygon with specified parameters.
---
---@param x number # The x-coordinate of the polygon's center.
---@param y number # The y-coordinate of the polygon's center.
---@param sides number # The number of sides of the polygon.
---@param radius number # The radius of the polygon.
---@param rotation number # The rotation angle of the polygon.
function pesto.graphics.polygon(x, y, sides, radius, rotation) end

---
---Draws an outlined polygon with specified parameters.
---
---@param x number # The x-coordinate of the polygon's center.
---@param y number # The y-coordinate of the polygon's center.
---@param sides number # The number of sides of the polygon.
---@param radius number # The radius of the polygon.
---@param rotation number # The rotation angle of the polygon.
function pesto.graphics.polygonLines(x, y, sides, radius, rotation) end

---
---Draws a rectangle at the specified position with the given dimensions.
---
---@param x number # The x-coordinate of the top-left corner of the rectangle.
---@param y number # The y-coordinate of the top-left corner of the rectangle.
---@param width number # The width of the rectangle.
---@param height number # The height of the rectangle.
function pesto.graphics.rectangle(x, y, width, height) end

---
---Draws an outlined rectangle at the specified position with the given dimensions.
---
---@param x number # The x-coordinate of the top-left corner of the rectangle.
---@param y number # The y-coordinate of the top-left corner of the rectangle.
---@param width number # The width of the rectangle.
---@param height number # The height of the rectangle.
function pesto.graphics.rectangleLines(x, y, width, height) end

---
---Sets the color for subsequent drawing operations.
---
---@param r number # Red component (0-255).
---@param g number # Green component (0-255).
---@param b number # Blue component (0-255).
---@param a number # Alpha component (0-255).
function pesto.graphics.setColor(r, g, b, a) end

---
---Sets the font for subsequent text drawing operations.
---
---@param font pesto.Font # Font object obtained from `pesto.graphics.loadFont`.
function pesto.graphics.setFont(font) end

---
---Draws text at the specified position using the current font and color.
---
---@param text string # The text to draw.
---@param x number # The x-coordinate of the text position.
---@param y number # The y-coordinate of the text position.
function pesto.graphics.text(text, x, y) end

---
---Draws wrapped text within a box at the specified position using the current font and color.
---
---@param text string # The text to draw.
---@param x number # The x-coordinate of the text position.
---@param y number # The y-coordinate of the text position.
---@param width number # The width of the box for text wrapping.
---@param height number # The height of the box for text wrapping.
function pesto.graphics.wrappedText(text, x, y, width, height) end
