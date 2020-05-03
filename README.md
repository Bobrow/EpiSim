# EpiSim
This project is currently very much alpha and will contain many bugs (especially with the **Experimental** branch).

The name comes from the two words **Epi**demic and **Sim**ulator.
## Build Instructions
### On Windows

1. You need to install SDL2, Pugixml and Boost
2. Then change the additional include and library (for SDL2) directories to where you have installed these
3. Build using Visual Studio 2019

### On Linux
1. Install the packages `libsdl2-dev`,`libpugixml-dev` and `libboost-all-dev` (or platform equivalent) 
2. Use your favorite compiler to build `main.cpp` with those libraries included