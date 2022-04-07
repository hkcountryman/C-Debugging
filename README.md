# C Debugging

The code in this repository is designed to debug as an exercise to learn to use GDB, the Gnu Debugger, and AddressSanitizer ("ASan"), an open source dynamic testing tool for catching memory bugs.

[Click here for the accompanying playlist!](https://www.youtube.com/playlist?list=PLL5qsNefCAyXBJBMxNVeYm3MrFQe-PAtQ)

**The main branch is intentionally buggy. See solutions on debug branch!**

## Compiling the code in this repository for use with ASan and GDB

We'll be using GCC (I'm using v11.2) and some special compiler options:

```
gcc -g foo.*
gcc -g reverso.c
gcc -g -fsanitize=address -fno-omit-frame-pointer quicksort.c
```

The `-g` flag compiles the program with debugging symbols. This is a must for using GDB, and you'll get more info out of your address sanitizer if you use it because it will be able to keep track of line numbers in your source code!

The `-fsanitize=address` option tells GCC to compile so that ASan will be used at runtime.

`-fno-omit-frame-pointer` is probably unnecessary but might be needed. It's one of those things that doesn't hurt to use and might help. Better yet, it isn't as awful to type as it appears: start typing "-fno-om" and press tab to complete! It tells the compiler to reserve a register for storing the frame pointer. That is desirable because we are not trying to optimize this code (though if we were, the difference this makes is really negligible) - we're trying to debug it. If we don't keep the frame pointer readily available the debugger isn't always able to generate a nice stack trace.

## Also see

[More about GDB](https://github.com/hkcountryman/C-Debugging/blob/main/GDB.md)

[More about ASan](https://github.com/hkcountryman/C-Debugging/blob/main/ASan.md)

## Thanks

It's surprisingly hard to write interesting bugs intentionally - thank you to [René García Avilés](https://github.com/Germfreekai) for giving me permission to modify and use quicksort.c!
