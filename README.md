<h1><img src="build/images/bomberman_logo_title.png" height="96" alt="Bomberman Logo"/></h1>

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](./LICENSE)
[![Version](https://img.shields.io/github/release/Astropilot/Bomberman.svg)](https://github.com/Astropilot/Bomberman/releases/latest)
![Made with love](https://img.shields.io/badge/Made%20with-%E2%9D%A4%EF%B8%8F-yellow.svg)

Bomberman is a school project where the goal is to develop the famous Bomberman game in C with the SDL2 library as well as the SDL_Image and SDL_TTf extensions.
No other libraries were allowed.

The game must be playable by 2 to 4 networked (multiplayer) players.

## About

Our game was developed thanks to our [gLib framework](./libs/glib/README.md) developed in parallel.
When launching the game you can choose to host a game or join an already hosted game.<br/>
It requires a minimum of 2 players for the creator of the game to launch the game.<br/>
Once the game is launched you can move with the directional arrows and set bombs with the space key.

For the rest of the gameplay I let you discover for yourself ;-)

## How to compile and play

Currently we can compile the game under Debian 8 & 9, Windows 10 x86 and x64, and Mac OSX !

### Prerequisites

You will need SDL 2 as well as the SDL2_Image, SDL2_TTf and SDL2_Mixer extensions.

### GNU/Linux / OSX

```bash
$> git clone https://github.com/Astropilot/Bomberman.git
$> cd Bomberman
Bomberman$> make
Bomberman$> cd build/
Bomberman$> ./bomberman
```

### Windows x86 & x64

We recommend that you use Visual Studio and import the header and source files.

## Credits

Lead developper: [@Astropilot](https://github.com/Astropilot)

Developpers: [@heinsenbergggg](https://github.com/heinsenbergggg) [@gaudesp](https://github.com/gaudesp) and [@GhostRolly](https://github.com/GhostRolly)
