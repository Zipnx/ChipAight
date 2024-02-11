
# ChipAight

A minimal Chip8 emulator in C

Chip-8 Reference: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

## Building

Will probably port this to windows at some point, only needs some tweaking in the Makefile.

Requires SDL2 to be available (uses sdl2-config for building)

You might have to change the compiler path for your specific system.

To build the emulator run 

```
make build
```

To run you can then use
```
./emulator <CH8 Bytecode File>
```
If a file is not specified a default test file will be used

## TODO:
 - [x] Add a proper display
 - [x] Keyboard inputs
 - [ ] Drawing to display
 - [ ] Documentation (lmao)
 - [ ] Fix timers to tick at 60hz
 - [ ] Cmdline arguments
 - [ ] Proper logging
 - [ ] Fix the input mapping
 - [ ] Properly have SDL2 render at 60fps
