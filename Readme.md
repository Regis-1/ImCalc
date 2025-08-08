# ImCalc
Simple C++ calculator with ImGui UI and Lua basic scripting capabilities.

# Building
Project uses CMake as a build system. To build application you need to have
installed SDL3 library and initialize/update git modules (ImGui is already
embedded in the project as submodule). 
```Bash
git submodule update --init
```
With those requirements fulfilled you can now build using standard CMake flow:
```Bash
mkdir build && cd build
cmake -S .. -B .         # if you are using make
cmake -S .. -B . -GNinja # if you are using ninja
```

The binary should be ready to run with `./imcalc`.
