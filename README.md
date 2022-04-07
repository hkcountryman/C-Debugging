# C Debugging

The code in this repository is designed to debug as an exercise. See the video for a demo of GDB, the Gnu Debugger, and AddressSanitizer ("ASan"), an open source dynamic testing tool for catching memory bugs.

## Compiling the code in this repository for use with ASan and GDB

We'll be using GCC (I'm using v11.2) and some special compiler options:

```
gcc ./*.c -g -fsanitize=address -fno-omit-frame-pointer
```

The `-g` flag compiles the program with debugging symbols. This is a must for using GDB, and you'll get more info out of your address sanitizer if you use it because it will be able to keep track of line numbers in your source code!

The `-fsanitize=address` option tells GCC to compile so that ASan will be used at runtime.

`-fno-omit-frame-pointer` is probably unnecessary but might be needed. It's one of those things that doesn't hurt to use and might help. Better yet, it isn't as awful to type as it appears: start typing "-fno-om" and press tab to complete! Its related option, `-fomit-frame-pointer`, tells the compiler to avoid storing stack frame pointers in a register if possible, which can technically grant some marginal performance improvements. That is the default behavior. By contrast, using this flag tells the compiler _not_ to do that and so forces the compiler to set aside a register for the frame pointer. That is desirable because we are not trying to optimize this code, we're trying to debug it, and if we don't keep the frame pointer readily available the debugger isn't always able to generate a nice stack trace.

Note that these options aren't need on your header files, but won't hurt.

## Also see

[More about GDB](https://github.com/hkcountryman/C-Debugging/blob/main/GDB.md)

[More about ASan](https://github.com/hkcountryman/C-Debugging/blob/main/ASan.md)

## Thanks

It's surprisingly hard to write interesting bugs intentionally - thank you to [René García Avilés](https://github.com/Germfreekai) for giving me permission to modify and use quicksort.c!
