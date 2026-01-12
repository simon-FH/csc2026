# TT-E1: Debugging with Sanitizers (Broken Reconstruction)

This mini-project is **intentionally buggy**. Your goal is to use tooling to find and fix:
- Heap buffer overflow
- Memory leak
- Use-after-free

## Build (normal)

```bash
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

Run the program:

```bash
./build/analyze
```

It may or may not crash. Undefined behaviour is not deterministic.

## Enable AddressSanitizer / UBSan

Re-configure with sanitizers enabled:

```bash
cmake -B build-asan -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON
```

Run again:

```bash
./build-asan/analyze
```

Expected ASan failures (in typical order):
1. `heap-buffer-overflow` in `TrackReconstructor::reconstruct()`
2. After fixing the loop bound, a `heap-use-after-free` in `getBestTrack()`
3. After fixing that, `LeakSanitizer: detected memory leaks`

## Run tests (optional)

```bash
ctest --test-dir build-asan --output-on-failure
```

The test is expected to fail or crash until you fix the exercise code.


rm -rf build-asan/
CC=clang CXX=clang++ cmake -B build-asan -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON
cmake --build build-asan
./build-asan/analyze
