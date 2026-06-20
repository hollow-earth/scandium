# Scandium

A Vulkan game engine written in C++.

<img width="785" height="603" alt="image" src="https://github.com/user-attachments/assets/0c5e2e90-991d-4a68-91b6-d8286760aa97" />

*Scandium rendering a colored cube using Vulkan.*

## Overview
Scandium is a Vulkan-based game engine written in C++ that uses GLSL for shaders and GLM for mathematics. It began as a graphics programming learning project based on Brendan Galea's [Vulkan engine tutorial](https://www.youtube.com/playlist?list=PL8327DO66nu9qYVKLDmdLW_84-yE4auCR), which I worked through by implementing the engine myself while learning modern C++, Vulkan, and CMake.

Beyond the tutorial, I extended the engine by implementing additional [3D transformation utilities](https://github.com/hollow-earth/scandium/blob/main/src/game/gameObject.cpp), including rotation and translation functions, and developed a [seed generation system based on a pseudohash function](https://github.com/hollow-earth/scandium/blob/main/src/world/worldgen.cpp) for future procedural generation experiments. Building the project also required creating a cross-platform CMake build system targeting both Linux and Windows.

This project introduced me to low-level graphics programming and sparked my interest in computer graphics, which later led me to take COMP 557 (Computer Graphics) as an elective during my undergraduate studies.

## Features
- Vulkan rendering pipeline
- Cross-platform CMake build (Linux and Windows)
- GLSL shader support
- 3D transformation system
- Procedural seed generation utilities

## Built With
- C++
- Vulkan
- GLSL
- GLM
- CMake

## Building
```
git clone https://github.com/hollow-earth/scandium.git
cd scandium
cmake <choose between Linux and Windows>
```

This project is no longer under active development. It remains available as a learning project documenting my introduction to Vulkan and graphics programming.

## What I Learned

Scandium was my first substantial C++ project outside of coursework. Through it I became familiar with the Vulkan graphics pipeline, GLSL shaders, CMake, and the process of structuring a larger software project. The experience ultimately motivated me to take COMP 557 (Computer Graphics), where I explored many of the same graphics concepts using OpenGL.

## Future Work
Possible future improvements include:
- Entity Component System (ECS)
- Dynamic lighting
- Skeletal animation
- Physics integration

## Acknowledgements
This project began as an implementation of Brendan Galea's excellent Vulkan tutorial series and was later extended with additional functionality and experimentation.
