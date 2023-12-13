# pesto

The `pesto` table is the only global exposed from pesto. It contains a series of modules which encapsulate all of the framework's functionality.
It also exposes some callbacks that can be overridden and are called internally.

``` lua title="Basic Example"
-- Do your setup here

function pesto.update(dt)
    -- Update your logic here
end

function pesto.draw()
    -- Draw in here
end
```

## Functions

### getVersion

Gets the current version of pesto.

``` lua
major, minor, patch, codename = pesto.getVersion()
```

## Callbacks

### pesto.update

This callback is used to update the state of the game every frame.

``` lua
pesto.update(dt)
```

### pesto.draw

This callback is used to draw on the screen every frame.

``` lua
pesto.draw()
```

