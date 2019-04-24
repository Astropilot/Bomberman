<h1><img src="https://www.codexus.fr/img/bomberman/glib_logo.png" height="96" alt="gLib Logo"/></h1>

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](./LICENSE)
[![Version](https://img.shields.io/github/release/Astropilot/gLib.svg)](https://github.com/Astropilot/gLib/releases/latest)
![Made with love](https://img.shields.io/badge/Made%20with-%E2%9D%A4%EF%B8%8F-yellow.svg)

Framework around the SDL library allowing to create small 2D video games quickly.

## About

During another project in C with the SDL library, I was getting tired of having to recode the game's graphic management every time. That's why I decided to make my own framework around the SDL allowing to set up as simply as possible small 2D video games.

This framework offers a development architecture more adapted to games and manages the graphic loop as well as the creation and management of many graphic components such as buttons, simple or animated sprites, input fields, sounds or simply text.<br/>
gLib is extensible, which means that you can develop your own graphical components and use them with the resource manager.

In addition to providing high-level support to SDL, it also provides support for the creation of a client/server architecture to integrate a network multiplayer concept into your game as well as pathfinding algorithms.

The framework is currently compatible with Linux (tested on Debian 8 & 9), Windows (tested on Windows 10 x86 and x64) and Mac OSX.

## How to compile

### Prerequisites

* [SDL2](https://www.libsdl.org/download-2.0.php)
* [SDL_image 2.0](https://www.libsdl.org/projects/SDL_image/)
* [SDL_ttf 2.0](https://www.libsdl.org/projects/SDL_ttf/)
* [SDL_mixer 2.0](https://www.libsdl.org/projects/SDL_mixer/)

### Compile [GNU/Linux / OSX]

```bash
$> git clone https://github.com/Astropilot/gLib.git
$> cd gLib
gLib$> make
```

### Compile [Windows x86 & x64]

We recommend that you use Visual Studio and import the header and source files.

## How to use

First import the `includes` folder into your project and include the `glib.h` file.
In your compilation tool add a reference to the static library `libglib.a` previously compiled.

All the documentation of the framework is available in the wiki of the [git repository](https://github.com/Astropilot/gLib/wiki).

Here is a simple example:

```
├── includes
│   ├── glib.h
│   └── ...
├── libglib.a
└── main.c
```

main.c:
```c
#include <stdlib.h>

#include "glib.h"

int main(void)
{
    return (EXIT_SUCCESS);
}
```

Compilation:
```bash
$ gcc main.c -o mygame -Iincludes/ -lglib
```

## Credits

Lead developper: [@Astropilot](https://github.com/Astropilot)

Developpers: [@heinsenbergggg](https://github.com/heinsenbergggg) [@gaudesp](https://github.com/gaudesp) and [@GhostRolly](https://github.com/GhostRolly)
