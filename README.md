# Pesto 🍃

Pesto is a tiny, lightweight, and fast game framework written entirely in C, utilizing Lua for scripting. It's designed to be cross-platform and is dependent on two main libraries: Raylib, an exceptional C library for graphics and input, and Lua. Pesto's architecture and design principles are heavily influenced by the fantastic Love2D framework.

## Introduction

Pesto aims to offer a simpler and more lightweight alternative to Love2D while staying true to the "Keep It Simple, Stupid" (KISS) principle. The primary motivation behind Pesto's creation was a desire for a lightweight project that emphasized readability, simplicity, and educational value. It aims to be self-contained, minimizing external dependencies and providing a more comprehensive feature set compared to the basic functionality of Love2D.

The word "Pesto" originates from my favorite Italian sauce, the country i'm from 😋.

## Features

- **Cross-Platform**: Built in C without significant dependencies, Pesto can support all platforms that Raylib supports, making it highly versatile.
- **Lightweight**: With a focus on simplicity and a small footprint, Pesto remains fast and efficient.
- **Lua Scripting**: Utilizes Lua for scripting, offering flexibility and ease of use in designing and developing games.
- **Readable Source Code**: Emphasizes readability and simplicity intentionally for educational purposes and easy understanding.
- **Inspired by Love2D**: Draws inspiration from Love2D's ease of use while aiming to be more self-contained.

## Getting Started

To start using Pesto, grab the latest release and refer to the documentation available on the [Pesto website](https://vinnyhorgan.github.io/pesto).

Here is a simple example:

```lua
function pesto.draw()
    pesto.graphics.print("Hello, World!")
end
```

## Building

You can build Pesto from source using CMake. Make sure to clone the project and its submodules, and then follow these steps:

```console
mkdir build
cd build
cmake ..
cmake --build .
```

## Differences with Love2D

- **Lightweight & Simplified**: While Love2D is a robust framework, Pesto aims to be more streamlined and less reliant on additional third-party libraries.
- **Maintained Ecosystem**: Leveraging modern libraries, Pesto harnesses the existing ecosystem, staying current with contemporary development practices.
- **Self-Contained Functionality**: Strives to offer a more comprehensive feature set without the need for excessive external dependencies.

## Contribution

Contributions to Pesto are welcome! Feel free to contribute by submitting bug reports, feature requests, or pull requests. Please adhere to the project's guidelines when contributing to maintain consistency and ease of integration.

## License

Pesto is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
