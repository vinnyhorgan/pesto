# Hello, World!

Ahh, "Hello, World!", the ultimate test program since the [1970s](https://en.wikipedia.org/wiki/%22Hello,_World!%22_program).
To create it in Pesto, we can define the `pesto.draw` callback in our `main.lua` file and call the `pesto.graphics.text` function.

``` lua
function pesto.draw()
    pesto.graphics.text("Hello, World!", 0, 0)
end
```

Now we can run the program by selecting it in the project manager.
This will draw the famous phrase in the top left corner, well done!
