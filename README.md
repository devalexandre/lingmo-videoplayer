# LingmoOS video player

Open source video player built using Qt/QML and libmpv.

### Third-party code

[haruna](https://github.com/g-fb/haruna)

## Dependencies

Qt 6 (Core, Gui, Quick, OpenGL, DBus, Widgets, LinguistTools), Qt 5 Compat
(GraphicalEffects), libmpv and the LingmoUI QML module. On Arch Linux:

```shell
sudo pacman -S cmake ninja qt6-base qt6-declarative qt6-5compat qt6-svg qt6-tools mpv
```

# Build

```
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ..
make
sudo make install
```

# License

This project has been licensed by GPLv3.
