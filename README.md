# Community Scripting Commands
Community Scripts is a intercept project designed to provided Arma 3 sqf developers QOL scripts, that aren't currently in the RV engine.

# What is the purpose
CSC mainly is designed to aid the developers sqf mission creators. Whether by providing json support in sqf or by adding more math commands,
the mission is to reduce the amount of times or work that a developer will need to build a complex system in sqf.

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
