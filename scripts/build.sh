#!/usr/bin/env bash
set -euo pipefail

ABI="${1:-arm64-v8a}"
NDK="${ANDROID_NDK_HOME:-${ANDROID_NDK_ROOT:-}}"
if [[ -z "$NDK" ]]; then
  echo "ANDROID_NDK_HOME/ANDROID_NDK_ROOT is not set" >&2
  exit 1
fi

cmake -S . -B "build-$ABI" \
  -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE="$NDK/build/cmake/android.toolchain.cmake" \
  -DANDROID_ABI="$ABI" \
  -DANDROID_PLATFORM=android-28 \
  -DANDROID_STL=c++_shared \
  -DMOD_ID=command_cheats_bypass \
  -DMOD_NAME="Command Cheats Bypass" \
  -DMOD_AUTHOR="Electrocharge" \
  -DMOD_VERSION=0.1.0 \
  -DMOD_LIBRARY_NAME=command_cheats_bypass \
  -DMOD_MINECRAFT_VERSIONS='[]'

cmake --build "build-$ABI" --target levi_package -j 2
mkdir -p dist
cp "build-$ABI/command_cheats_bypass.levipack" "dist/command_cheats_bypass-$ABI.levipack"
