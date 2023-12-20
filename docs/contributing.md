# Contributing

Pesto has been designed to be a collaborative project.
Every little bit of help is appreciated!
My dream is to make Pesto the best it can be.
Here are some ideas for how you can contribute:

- Add new features
- Fix bugs
- Add documentation

The project structure is extremely simple, you can add either C++ or Lua modules to Pesto.
To add a native module just create a `.cpp` file in the `modules` directory.
Then make sure to add its `luaopen` function to the preloaded modules in `modules/pesto.cpp` and finally require it in `boot.lua`.

Only rule is: before submitting any code, please make sure it follows the style of the project.
Ensure your editor has [EditorConfig](https://editorconfig.org) and [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) installed.
