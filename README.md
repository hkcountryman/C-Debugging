# Large Quantities of Buggy Code

This code is designed to debug. We'll be using GCC (I'm using v11.2) and some special compiler flags:

```
gcc ./*.c -g -fsanitize=address -fno-omit-frame-pointer
```

The ```-g``` flag compiles the program with debugging symbols. This is a must for using GDB, and you'll get more info out of your address sanitizer if you use it because it will be able to keep track of line numbers in your source code!

The ```-fsanitize=address``` option tells GCC to use the address sanitizer. A sanitizer is just something that is actually built into your code at compile time (no surprise there) so that undesirable behavior can be detected and reported at runtime. There are other types of sanitizers; of interest might be thread sanitizers, kernel address sanitizers, and undefined behavior sanitizers. (If you want to see documentation about them all, enter ```info gcc``` into your terminal and navigate to Invoking GCC > Instrumentation Options and search for "fsanitize" by entering "/fsanitize <enter>" while in info mode. To navigate to the next/previous result, enter "n" or "N" and to quit enter ":q".)

```-fno-omit-frame-pointer``` is probably unnecessary but might be needed. It's one of those things that doesn't hurt to use and might help. Better yet, it isn't as awful to type as it appears: start typing "-fno-om" and press tab to complete! Its related option, ```-fomit-frame-pointer```, tells the compiler to avoid storing stack frame pointers in a register if possible, which can technically grant some marginal performance improvements. That is the default behavior. By contrast, using this flag tells the compiler _not_ to do that and so forces the compiler to set aside a register for the frame pointer. That is desirable because we are not trying to optimize this code, we're trying to debug it, and if we don't keep the frame pointer readily available the debugger isn't always able to generate a nice stack trace.

