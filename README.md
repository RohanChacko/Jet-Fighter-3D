# Jet Fighter 3D

Jet Fighter Game in 3D built using OpenGL 3.3

## Build & Run
* `mkdir build`
* `cd build`
* `cmake ..`
* `make all`
* `./jet_fighter`

## Controls

* Increase Speed: W
* Decrease Speed: S
* Pitch: Space Bar
* Yaw left: A
* Yaw right: D
* Roll left: Q
* Roll right: E
* Missile: Left click
* Bomb: Right click
* Camera angle toggle: 1/2/3/4/5
* Barrel roll: 7

## Objects implemented
* Airplane
* Ammunition (Bombs & Missiles)
* Checkpoints
* Smoke Rings
* Dashboard
* Enemies (2 types)
* Volcano
* Land
* Sea

## Directory Structure
```
.
├── CMakeLists.txt
├── LICENSE
├── README.md
└── src
    ├── addons.cpp
    ├── addons.h
    ├── airplane.cpp
    ├── airplane.h
    ├── ammunition.cpp
    ├── ammunition.h
    ├── checkpoint.cpp
    ├── checkpoint.h
    ├── color.cpp
    ├── dashboard.cpp
    ├── dashboard.h
    ├── enemy.cpp
    ├── enemy.h
    ├── floor.cpp
    ├── floor.h
    ├── input.cpp
    ├── land.cpp
    ├── land.h
    ├── main.cpp
    ├── main.h
    ├── nonedit.cpp
    ├── other_handlers.cpp
    ├── parachute.cpp
    ├── parachute.h
    ├── Sample_GL.frag
    ├── Sample_GL.vert
    ├── smokering.cpp
    ├── smokering.h
    ├── timer.cpp
    ├── timer.h
    ├── volcano.cpp
    └── volcano.h
```
## Notes

* src directory contains the .cpp files for the game
* run the executable is named 'jet_fighter' to play the game
* Do a `make clean` once done playing the game to remove all the compiled object files.
* There might be enemies way in parachutes above the plane. Look out!

## License
The MIT License https://rohanc.mit-license.org/  
Copyright &copy; 2019 Rohan Chacko <rohanchacko007@gmail.com>
