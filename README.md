![floodfill resized](https://user-images.githubusercontent.com/66972514/167484626-d8addd59-4304-44f9-a5aa-fd560e7dd416.png)
# Flood Fill
The objective of the game is to fill the board with one color within 25 moves. You select a color by clicking on it, and it will fill from the top left color.

## Installation

Dependencies:
* C compiler \*
* Raylib \*
* meson \*
* ninja \*

_\* Compile-time dep_

Compilation:
``` sh
git clone "https://github.com/acly7946/Flood-Fill"
cd Flood-Fill
meson build
ninja -C build
sudo ninja -C build install # to install
sudo ninja -C build uninstall # to uninstall
```
