# **Framebuffer for the Pico-ResTouch-LCD-3.5**

This is an implementation of the Python framebuf library for C++ alongside the drivers to run it on the <a href="https://www.waveshare.com/wiki/Pico-ResTouch-LCD-3.5">Pico-ResTouch-LCD-3.5</a> display for the Raspberry Pi Pico.

This was created due to the original Waveshare display drivers for C sending each drawing action as soon as it is done, rather than waiting for the code to call an update. For example if you drew a rectangle it would be sent immediately, meaning any subsequent rectangles drawn would appear after even if you wanted them all to show at once, creating a lag effect. 

This contrasts to their MicroPython implementation which uses the <a href="https://docs.micropython.org/en/latest/library/framebuf.html">framebuf</a> library where changes are first written to an array known as a framebuffer, which stores each pixel of the screen, and then only written to the display when the code calls a show function.

Presently, this has only been tested on the Pico 2W. To run on non-W Picos it will need adjustments.

## **Instructions**

### **Compilation**

These instructions are for Linux as it is the OS I use. If you're on another OS I recommend using cygwin or something similar to get access to bash.

**Setting up the environment**

If you have not already installed pico-sdk and ARM embedded toolchain then follow these instructions first.

1. Download the <a href="https://github.com/raspberrypi/pico-sdk">pico-sdk</a> and extract it to a folder on your system.
2. Download the relevant GCC ARM embedded toolchain from <a href="https://developer.arm.com/downloads/-/gnu-rm">ARM's developer page</a> and extract it to a folder on your system.
3. Add the following lines to your .bashrc:

```bash
export PICO_SDK_PATH="<path to pico-sdk>"
export PICO_TOOLCHAIN_PATH="<path to GCC ARM embedded>/bin"
export CMAKE_C_COMPILER="<path to GCC ARM embedded>/bin/arm-none-eabi-gcc"
export CMAKE_CXX_COMPILER="<path to GCC ARM embedded>/bin/arm-none-eabi-g++"
```

**Compiling**

```bash
cd "<path to code>"
mkdir build
cd build
cmake -DPICO_BOARD=pico2_w -DPICO_PLATFORM=rp2350 ..
make -j$(nproc --all)
```

### Running

Put the Pi Pico into <a href="https://projects.raspberrypi.org/en/projects/getting-started-with-the-pico">BOOTSEL mode</a> and run `fdisk -l`. It should return a list of mounted devices and the partitions. Find the corresponding entry for the Pi Pico and the name of the device, e.g. `/dev/sda1`.

In the `build` folder, run:

```bash
sudo mount <device name> /mnt
sudo cp main.uf2 /mnt/ && sudo umount /mnt
```

After a few seconds the demo should load on the Pi Pico. You should see a square in the top left of the screen changing colour every second for a total of 13 colours.

## Usage in your own projects

TBA

## Footage of demo

TBA

## Credits

### Waveshare Electronics

- The LCD, sdcard, and fatfs libraries. Originals can be downloaded <a href="https://www.waveshare.com/wiki/Pico-ResTouch-LCD-3.5">from their wiki.</a>

### Me

- Framebuf implementation for C++
- Display driver to draw the framebuffer to the display
- Coloured square demo
