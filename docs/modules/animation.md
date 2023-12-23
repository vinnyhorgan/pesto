# pesto.animation

The `pesto.animation` module provides functions to animate sprites.
It is based on kikito's amazing [anim8](https://github.com/kikito/anim8) library.

## Functions

### pesto.animation.newAnimation

Creates a new animation object.

```
animation = pesto.animation.newAnimation(frames, durations, [onLoop])
```

**Arguments**

| Name        | Type         | Description                                               |
| ----------- | ------------ | --------------------------------------------------------- |
| `frames`    | table        | The frames to animate.                                    |
| `durations` | number/table | The duration of each frame.                               |
| `onLoop`    | function     | The function to call when the animation loops. (optional) |

- `frames` is a table of frames, you can provide your own, but using the [Grid](#grid) object is very convenient.
- When `durations` is a number, it represents the duration of all frames in the animation.
When it's a table, it can represent different durations for different frames.
You can specify durations for all frames individually, like this: `{0.1, 0.5, 0.1}` or you can specify durations for ranges of frames: `{["3-5"]=0.2}`.
- `onLoop` is an optional parameter which does nothing by default.
If specified, it will be called every time an animation "loops".
It will have two parameters: the animation instance, and how many loops have been elapsed.

**Returns**

| Name        | Type                    | Description               |
| ----------- | ----------------------- | ------------------------- |
| `animation` | [Animation](#animation) | The new animation object. |


### pesto.animation.newGrid

Creates a new grid object.

```
grid = pesto.animation.newGrid(frameWidth, frameHeight, imageWidth, imageHeight, left, top, border)
```

**Arguments**

| Name          | Type   | Default | Description                    |
| ------------- | ------ | ------- | ------------------------------ |
| `frameWidth`  | number |         | The width of each frame.       |
| `frameHeight` | number |         | The height of each frame.      |
| `imageWidth`  | number |         | The width of the image.        |
| `imageHeight` | number |         | The height of the image.       |
| `left`        | number | 0       | The left position of the grid. |
| `top`         | number | 0       | The top position of the grid.  |
| `border`      | number | 0       | The border between the frames. |

- `frameWidth` and `frameHeight` are the dimensions of the animation frames: each of the individual "sub-images" that compose the animation.
- `imageWidth` and `imageHeight` are the dimensions of the image where all the frames are.
In Pesto, they can be obtained by doing image:getWidth() and image:getHeight().
- `left` and `top` are optional, and both default to 0.
They are "the left and top coordinates of the point in the image where you want to put the origin of coordinates of the grid".
- `border` is also an optional value, and it also defaults to 0.
It allows you to define "gaps" between your frames in the image.

**Returns**

| Name   | Type          | Description          |
| ------ | ------------- | -------------------- |
| `grid` | [Grid](#grid) | The new grid object. |

## Types

## Animation

Animation objects are groups of frames that are interchanged at a specific time.

### Animation:update

Updates the animation according to the time passed.

```
Animation:update(dt)
```

**Arguments**

| Name | Type   | Description                     |
| ---- | ------ | ------------------------------- |
| `dt` | number | The time since the last update. |

**Returns**

None

### Animation:draw

Draws the animation.

```
Animation:draw(image, x, y, r, sx, sy, ox, oy)
```

**Arguments**

| Name    | Type   | Description                      |
| ------- | ------ | -------------------------------- |
| `image` | Image  | The image to draw the animation. |
| `x`     | number | The x position of the animation. |
| `y`     | number | The y position of the animation. |
| `r`     | number | The rotation of the animation.   |
| `sx`    | number | The scale factor on the x axis.  |
| `sy`    | number | The scale factor on the y axis.  |
| `ox`    | number | The origin offset on the x axis. |
| `oy`    | number | The origin offset on the y axis. |

**Returns**

None

### Animation:gotoFrame

Goes to a specific frame.
Frames start at 1.

```
Animation:gotoFrame(frame)
```

**Arguments**

| Name    | Type   | Description         |
| ------- | ------ | ------------------- |
| `frame` | number | The frame to go to. |

**Returns**

None

### Animation:pause

Stops the animation from updating.

```
Animation:pause()
```

**Arguments**

None

**Returns**

None

### Animation:resume

Unpauses the animation.

```
Animation:resume()
```

**Arguments**

None

**Returns**

None

### Animation:clone

Creates a new animation identical to the current one.
The only difference is that its internal counter is reset to the first frame.

```
animation = Animation:clone()
```

**Arguments**

None

**Returns**

| Name        | Type                    | Description                  |
| ----------- | ----------------------- | ---------------------------- |
| `animation` | [Animation](#animation) | The cloned animation object. |

### Animation:flipH

Flips the animation horizontally.
It does not create a new animation object.

```
Animation:flipH()
```

**Arguments**

None

**Returns**

None

### Animation:flipV

Flips the animation vertically.
It does not create a new animation object.

```
Animation:flipV()
```

**Arguments**

None

**Returns**

None

### Animation:pauseAtEnd

Moves the animation to its last frame and then pauses it.

```
Animation:pauseAtEnd()
```

**Arguments**

None

**Returns**

None

### Animation:pauseAtStart

Moves the animation to its first frame and then pauses it.

```
Animation:pauseAtStart()
```

**Arguments**

None

**Returns**

None

### Animation:getDimensions

Returns the width and height of the current frame of the animation.

```
width, height = Animation:getDimensions()
```

**Arguments**

None

**Returns**

| Name     | Type   | Description              |
| -------- | ------ | ------------------------ |
| `width`  | number | The width of the frame.  |
| `height` | number | The height of the frame. |

## Grid

Grid objects are just a convenient way of getting frames from a sprite.

### Grid:getFrames

Returns the frames specified in the parameters.

```
frames = Grid:getFrames(...)
```

**Arguments**

`Grid:getFrames` accepts an arbitrary number of parameters.
They can be either numbers or strings.

- Each two numbers are interpreted as quad coordinates in the format `(column, row)`.
This way, `grid:getFrames(3,4)` will return the frame in column 3, row 4 of the grid.
There can be more than just two: `grid:getFrames(1,1, 1,2, 1,3)` will return the frames in {1,1}, {1,2} and {1,3} respectively.
- Using numbers for long rows or columns is tedious, so grids also accept strings indicating range plus a row/column index.
Differentiating rows and columns is based on the order in which the range and index are provided.
A row can be fetch by calling `grid:getFrames("range", rowNumber)` and a column by calling `grid:getFrames(columnNumber, "range")`.
The previous column of 3 elements, for example, can be also expressed like this: `grid:getFrames(1,"1-3")`.
Again, there can be more than one string-index pair (`grid:getFrames(1,"1-3", "2-4",3)`).
- It's also possible to combine both formats.
For example: `grid:getFrames(1,4, 1,"1-3")` will get the frame in {1,4} plus the frames 1 to 3 in column 1.

You can use a grid as if it was a function, and `getFrames` will be called.
In other words, given a grid called `g`, this:

``` lua
g:getFrames("2-8",1, 1,2)
```

Is equivalent to this:

``` lua
g("2-8",1, 1,2)
```

**Returns**

| Name     | Type  | Description           |
| -------- | ----- | --------------------- |
| `frames` | table | The requested frames. |
