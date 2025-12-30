# SD-E1 Parallel Event Processing (OpenMP)

Goal: make a parallel loop **correct** first, then reduce performance loss from false sharing.

## Success criteria

- With `-DENABLE_OPENMP=ON`, results match the serial implementation
- Unit tests pass
- You can explain what changed (race vs false sharing)

## Build + run (starter)

```bash
cd exercises/SD-E1-parallel-event-processing/starter

cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DENABLE_OPENMP=ON
cmake --build build -j"$(nproc)"
ctest --test-dir build --output-on-failure

./build/event_processor
```

## Stretch
* Add padding or per-thread aggregation to reduce false sharing
* Validate with ThreadSanitizer in a debug build
