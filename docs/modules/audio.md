# pesto.audio

The `pesto.audio` module provides functions to manage audio devices and files.

## Functions

### pesto.audio.getVolume

Returns the current master volume.

```
volume = pesto.audio.getVolume()
```

**Arguments**

None

**Returns**

| Name     | Type   | Description                |
| -------- | ------ | -------------------------- |
| `volume` | number | The current master volume. |

### pesto.audio.isReady

Checks if the audio device is ready.

```
ready = pesto.audio.isReady()
```

**Arguments**

None

**Returns**

| Name    | Type    | Description                        |
| ------- | ------- | ---------------------------------- |
| `ready` | boolean | True if the audio device is ready. |

### pesto.audio.loadSound

!!! warning
    Calling this function in `pesto.update` or `pesto.draw` can be slow! Store the result in a variable.

Loads an audio file into memory.

```
sound = pesto.audio.loadSound(filename)
```

**Arguments**

| Name       | Type   | Description                     |
| ---------- | ------ | ------------------------------- |
| `filename` | string | The filename of the audio file. |

**Returns**

| Name    | Type            | Description              |
| ------- | --------------- | ------------------------ |
| `sound` | [Sound](#sound) | The loaded Sound object. |

### pesto.audio.loadStream

!!! warning
    Calling this function in `pesto.update` or `pesto.draw` can be slow! Store the result in a variable.

Loads an audio stream into memory.

```
stream = pesto.audio.loadStream(filename)
```

**Arguments**

| Name       | Type   | Description                     |
| ---------- | ------ | ------------------------------- |
| `filename` | string | The filename of the audio file. |

**Returns**

| Name     | Type              | Description               |
| ---------| ----------------- | ------------------------- |
| `stream` | [Stream](#stream) | The loaded Stream object. |

### pesto.audio.setVolume

Sets the master volume.

```
pesto.audio.setVolume(volume)
```

**Arguments**

| Name     | Type   | Description             |
| -------- | ------ | ----------------------- |
| `volume` | number | The volume. (0.0 - 1.0) |

**Returns**

None

## Types

## Sound

A Sound object represents an audio file loaded into memory.

### Sound:isPlaying

Checks if the sound is playing.

```
playing = Sound:isPlaying()
```

**Arguments**

None

**Returns**

| Name      | Type    | Description                   |
| --------- | ------- | ----------------------------- |
| `playing` | boolean | True if the sound is playing. |

### Sound:isReady

Checks if the sound is ready.

```
ready = Sound:isReady()
```

**Arguments**

None

**Returns**

| Name    | Type    | Description                 |
| ------- | ------- | --------------------------- |
| `ready` | boolean | True if the sound is ready. |

### Sound:pause

Pauses the sound.

```
Sound:pause()
```

**Arguments**

None

**Returns**

None

### Sound:play

Plays the sound.

```
Sound:play()
```

**Arguments**

None

**Returns**

None

### Sound:resume

Resumes the sound.

```
Sound:resume()
```

**Arguments**

None

**Returns**

None

### Sound:setPan

Sets the pan of the sound.

```
Sound:setPan(pan)
```

**Arguments**

| Name  | Type   | Description                         |
| ----- | ------ | ----------------------------------- |
| `pan` | number | The pan. (0.0 - 1.0, 0.5 is center) |

**Returns**

None

### Sound:setPitch

Sets the pitch of the sound.

```
Sound:setPitch(pitch)
```

**Arguments**

| Name    | Type   | Description                         |
| ------- | ------ | ----------------------------------- |
| `pitch` | number | The pitch. (0.0 - 1.0, 1.0 is base) |

**Returns**

None

### Sound:setVolume

Sets the volume of the sound.

```
Sound:setVolume(pan)
```

**Arguments**

| Name     | Type   | Description             |
| -------- | ------ | ----------------------- |
| `volume` | number | The volume. (0.0 - 1.0) |

**Returns**

None

### Sound:stop

Stops the sound.

```
Sound:stop()
```

**Arguments**

None

**Returns**

None

## Stream

A Stream object represents an audio stream loaded into memory.

### Stream:getLength

Returns the length of the stream.

```
length = Stream:getLength()
```

**Arguments**

None

**Returns**

| Name     | Type   | Description                            |
| -------- | ------ | -------------------------------------- |
| `length` | number | The length of the stream. (in seconds) |

### Stream:getPosition

Returns the current position of the stream.

```
position = Stream:getPosition()
```

**Arguments**

None

**Returns**

| Name       | Type   | Description                        |
| ---------- | ------ | ---------------------------------- |
| `position` | number | The current position. (in seconds) |

### Stream:isPlaying

Checks if the stream is playing.

```
playing = Stream:isPlaying()
```

**Arguments**

None

**Returns**

| Name      | Type    | Description                   |
| --------- | ------- | ----------------------------- |
| `playing` | boolean | True if the stream is playing. |

### Stream:isReady

Checks if the stream is ready.

```
ready = Stream:isReady()
```

**Arguments**

None

**Returns**

| Name    | Type    | Description                 |
| ------- | ------- | --------------------------- |
| `ready` | boolean | True if the stream is ready. |

### Stream:pause

Pauses the stream.

```
Stream:pause()
```

**Arguments**

None

**Returns**

None

### Stream:play

Plays the stream.

```
Stream:play()
```

**Arguments**

None

**Returns**

None

### Stream:resume

Resumes the stream.

```
Stream:resume()
```

**Arguments**

None

**Returns**

None

### Stream:seek

Seeks the stream to the specified position.

```
Stream:seek(position)
```

**Arguments**

| Name       | Type   | Description                |
| ---------- | ------ | -------------------------- |
| `position` | number | The position. (in seconds) |

**Returns**

None

### Stream:setPan

Sets the pan of the stream.

```
Stream:setPan(pan)
```

**Arguments**

| Name  | Type   | Description                         |
| ----- | ------ | ----------------------------------- |
| `pan` | number | The pan. (0.0 - 1.0, 0.5 is center) |

**Returns**

None

### Stream:setPitch

Sets the pitch of the stream.

```
Stream:setPitch(pitch)
```

**Arguments**

| Name    | Type   | Description                         |
| ------- | ------ | ----------------------------------- |
| `pitch` | number | The pitch. (0.0 - 1.0, 1.0 is base) |

**Returns**

None

### Stream:setVolume

Sets the volume of the stream.

```
Stream:setVolume(pan)
```

**Arguments**

| Name     | Type   | Description             |
| -------- | ------ | ----------------------- |
| `volume` | number | The volume. (0.0 - 1.0) |

**Returns**

None

### Stream:stop

Stops the stream.

```
Stream:stop()
```

**Arguments**

None

**Returns**

None

### Stream:update

Updates the stream.

```
Stream:update()
```

**Arguments**

None

**Returns**

None
