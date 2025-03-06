# Best 403 unlocker GUI

A Simple GUI tool to find optimal DNS server to bypass 403 restirections.

> [!WARNING]
> This project is currently under development and not complete but you can build and use the app.

## Build

1. Clone the repository
   ``` bash
   git clone --depth=1 https://github.com/403unlocker/best403unlocker-gui.git
   cd best403unlocker-gui
   ```
2. Install dependencies with Conan
   ``` bash
   conan install . --build=missing
   cmake --preset conan-release
   ```
3. Build
   ``` bash
   cmake --build build/Release
   ```

## Run

``` bash
./build/Release/best403unlocker
```

## License

This project is licensed under the GPL-3.0 License. See the [LICENSE](https://github.com/403unlocker/best403Unlocker-gui/blob/main/LICENSE) file for more information.
