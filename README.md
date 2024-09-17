# ImGui running in android natively (root)

## Build Instructions
```
git clone https://github.com/valium007/imgui-android
cd imgui-android
mkdir build
cd build
cmake ../ -DCMAKE_TOOLCHAIN_FILE=/path/to/NDK/build/cmake/android.toolchain.cmake -DANDROID_ABI=armeabi-v7a -DANDROID_PLATFORM=android-28 -DCMAKE_BUILD_TYPE=Release -GNinja
```
Specify the arch and android version as per your need.

## Running
```sudo ./menu```
