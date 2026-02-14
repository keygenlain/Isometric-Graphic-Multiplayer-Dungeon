#!/bin/bash

# Android Build Script for Isometric MUD
# This script builds the Android APK

echo "Building Isometric MUD for Android..."

# Set Android SDK and NDK paths
# export ANDROID_SDK_ROOT=/path/to/android/sdk
# export ANDROID_NDK_ROOT=/path/to/android/ndk

# Create build directory
mkdir -p build-android
cd build-android

# Configure with CMake for Android
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_ROOT/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a \
    -DANDROID_PLATFORM=android-21 \
    -DBUILD_ANDROID=ON \
    -DBUILD_SERVER=OFF \
    -DBUILD_LAUNCHER=OFF \
    -DBUILD_EDITOR=OFF

# Build
cmake --build . --parallel

echo "Android build complete!"
