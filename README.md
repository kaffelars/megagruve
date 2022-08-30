# Megagruve

Minecraft ripoff written in c++ just for fun

Work in progress lol (lots of bugs)

Textures, shaders, data, etc. are in the zip in builds folder, as well as a compiled version (x64 win)

[Most of the default textures by XSSheep](https://www.minecraftforum.net/forums/mapping-and-modding-java-edition/resource-packs/1242533-pixel-perfection-now-with-polar-bears-1-11)

## Features

Features:
* blocks
* chunks (32x256x32 blocks)
* trees
* other plants and flowers
* biomes
* simplex noise based random world generation (now with changeable seed)
* water with "physics" (watch out)
* glowing blocks
* particles
* fall damage
* day/night cycle
* clouds and rain
* many interesting items
* player inventory
* doors and buttons
* working chests
* flagpoles (with flags)
* random crashes

Missing features:
* proper light propagation
* saving worlds
* crafting
* optimizations
* nice animals
* evil animals (enemies)
* lots more

## Default keys

* mouse to look around
* w/a/s/d to move
* shift = hold to run
* ctrl = hold to move slowly
* space = jump
* i = show/hide inventory
* left mouse button = use selected item (or move items around in inventory/actionbar)
* right mouse button = interact (with e.g. doors, chests, etc.)
* scroll wheel or number keys = select item on action bar
* m = toggle infobox (top-left corner)
* f = enable noclip fly hax mode

## Screenshots

![screenshot](https://github.com/kaffelars/megagruve/blob/main/screenshots/screenshot7.png)

![screenshot](https://github.com/kaffelars/megagruve/blob/main/screenshots/screenshot5.png)

![screenshot](https://github.com/kaffelars/megagruve/blob/main/screenshots/screenshot4.png)

![screenshot](https://github.com/kaffelars/megagruve/blob/main/screenshots/screenshot6.png)

## Using/compiling
* [SDL2](https://www.libsdl.org/)
* [glew](http://glew.sourceforge.net/)
* [GLM](https://github.com/g-truc/glm)
* [Dear ImGui](https://github.com/ocornut/imgui)
* [pugixml](https://pugixml.org/)

Dear ImGui and pugixml are included in the repo. SDL2, glew and GLM has to be downloaded separately and included and linked (SDL2 and glew) to compile. I compile (windows) through [Code::Blocks](https://www.codeblocks.org/) with the included mingw-w64 (GCC) set to C++17. Necessary dll-files to run the compiled program are in the zip in the builds folder. SDL2 has wide platform support, so compiling for other platforms should be doable (I haven't tried). Let me know if you have issues compiling.
