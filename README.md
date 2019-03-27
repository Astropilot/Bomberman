# Bomberman ![Made with love](https://img.shields.io/badge/Made%20with-%E2%9D%A4%EF%B8%8F-yellow.svg)

![Image of Bomberman](https://static.tvtropes.org/pmwiki/pub/images/bomberman.png)

## Description
[![MIT license](https://img.shields.io/badge/license-MIT-green.svg)](./LICENSE)

Bomberman is a school project where the goal is to develop the famous Bomberman game in C with the SDL2 library as well as the SDL_Image and SDL_TTf extensions. <img align="right" width="220" height="100" src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/cd/SDL_Logo.svg/220px-SDL_Logo.svg.png">
No other libraries were allowed.

The game must be playable by 2 to 4 networked (multiplayer) players.

## Bomberman

Our game was developed thanks to our [gLib framework](#glib-framework) developed in parallel.
When launching the game you can choose to host a game or join an already hosted game.<br/>
It requires a minimum of 2 players for the creator of the game to launch the game.<br/>
Once the game is launched you can move with the directional arrows and set bombs with the space key.

For the rest of the gameplay I let you discover for yourself ;-)

Note: Currently we can compile the game under Debian 8 & 9, Windows 10 x86 and x64, and Mac OSX !

## gLib Framework

Having dealt with the SDL library many times before, we were tired of always having to re-code the graphical management from zero.<br/>
We decided for this project to develop a framework around the SDL allowing to set up small 2D games quickly.

This framework offers a development architecture more adapted to games and manages the graphic loop as well as the creation and management of many graphic components such as buttons, simple or animated sprites, input fields or simply text.<br/>
gLib is extensible, which means that you can develop your own graphical components and use them with the resource manager.

In addition to providing high-level support to the SDL, it also provides support for the creation of a client/server architecture to integrate a concept of network multiplayers into your game.

The framework has been designed to be efficient and cross-platform.

## Team

Lead developper: [@Astropilot](https://github.com/Astropilot)

Developpers: [@heinsenbergggg](https://github.com/heinsenbergggg) [@gaudesp](https://github.com/gaudesp) and [@GhostRolly](https://github.com/GhostRolly)
