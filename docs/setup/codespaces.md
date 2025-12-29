# Codespaces setup

This repo includes a `.devcontainer/` configuration so you can use GitHub Codespaces.

## Steps

1. Open the repository in GitHub.
2. Click **Code** -> **Codespaces** -> **Create codespace on main**.
3. Wait for the container to build.
4. Build the project:

```bash
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build -j$(nproc)
ctest --test-dir build --output-on-failure
```

