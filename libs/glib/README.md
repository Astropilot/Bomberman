<h1><img src="https://www.codexus.fr/img/bomberman/glib_logo.png" height="96" alt="gLib Logo"/></h1>

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](./LICENSE)
[![Version](https://img.shields.io/github/release/Astropilot/gLib.svg)](https://github.com/Astropilot/gLib/releases/latest)
![Made with love](https://img.shields.io/badge/Made%20with-%E2%9D%A4%EF%B8%8F-yellow.svg)

Framework around the SDL library allowing to create small 2D video games quickly.

## About

Having dealt with the SDL library many times before, we were tired of always having to re-code the graphical management from zero.<br/>
We decided for this project to develop a framework around the SDL allowing to set up small 2D games quickly.

This framework offers a development architecture more adapted to games and manages the graphic loop as well as the creation and management of many graphic components such as buttons, simple or animated sprites, input fields or simply text.<br/>
gLib is extensible, which means that you can develop your own graphical components and use them with the resource manager.

In addition to providing high-level support to the SDL, it also provides support for the creation of a client/server architecture to integrate a concept of network multiplayers into your game.

The framework has been designed to be efficient and cross-platform.

## How to compile and use

Currently we can compile the framework under Debian 8 & 9, Windows 10 x86 and x64, and Mac OSX !

### Prerequisites

You will need SDL 2 as well as the SDL2_Image, SDL2_TTf and SDL2_Mixer extensions.

### Compile [GNU/Linux / OSX]

```bash
$> git clone https://github.com/Astropilot/gLib.git
$> cd gLib
gLib$> make
```

### Compile [Windows x86 & x64]

We recommend that you use Visual Studio and import the header and source files.

## Credits

Lead developper: [@Astropilot](https://github.com/Astropilot)

Developpers: [@heinsenbergggg](https://github.com/heinsenbergggg) [@gaudesp](https://github.com/gaudesp) and [@GhostRolly](https://github.com/GhostRolly)
