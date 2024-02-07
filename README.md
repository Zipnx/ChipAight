
# ChipAight

A minimal Chip8 emulator in C

Chip-8 Reference: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

## Building

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
 - [x] Be able to somewhat run a bin
 - [ ] Add a proper display (probably SDL2)
 - [ ] Keyboard inputs
 - [x] Add the bit fonts
 - [x] Make some test bin to check instruction implementations
 - [ ] There are still some OPs missing
 - [ ] Documentation (lmao)
 - [ ] Fix timers to tick at 60hz
 - [ ] Cmdline arguments
 - [ ] Proper logging
