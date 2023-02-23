# Community Scripting Commands
Community Scripts is a intercept project designed to provided Arma 3 sqf developers QOL scripts, that aren't currently in the RV engine.

# Building
Building CSC requires
- CMake
- MCVC or G++ with c++17 support

## steps

1. Clone repo
```
git clone https://github.com/killerswin2/csc.git
```
2. Generate Cmake Configs
```
cmake -S . -B out/build
```
3. Use Cmake to build or build mainly in vs
```
cmake --build build
```
