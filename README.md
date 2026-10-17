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

## Playlist ordering

Opened files and restored playlists use case-insensitive natural filename
ordering (`Episode 2` before `Episode 10`). Opening an existing entry selects it
without creating a duplicate. Sorting keeps the playing file and item indices
consistent.

```sh
cmake -S tests -B /tmp/lingmo-playlist-tests
cmake --build /tmp/lingmo-playlist-tests
ctest --test-dir /tmp/lingmo-playlist-tests --output-on-failure
```
