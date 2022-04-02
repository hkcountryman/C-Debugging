# Large Quantities of Buggy Code

## Compiling the code in this repository

This code is designed to debug. We'll be using GCC (I'm using v11.2) and some special compiler options:

```
gcc ./*.c -g -fsanitize=address -fno-omit-frame-pointer
```

The ```-g``` flag compiles the program with debugging symbols. This is a must for using GDB, and you'll get more info out of your address sanitizer if you use it because it will be able to keep track of line numbers in your source code!

The ```-fsanitize=address``` option tells GCC to use the address sanitizer. A sanitizer is just something that is actually built into your code at compile time (no surprise there) so that undesirable behavior can be detected and reported at runtime. There are other types of sanitizers; of interest might be the thread, memory, kernel address, and undefined behavior sanitizers. (If you want to see documentation about them all, enter ```info gcc``` into your terminal and navigate to Invoking GCC > Instrumentation Options and search for "fsanitize" by entering "/fsanitize <enter>" while in info mode. To navigate to the next/previous result, enter "n" or "N" and to quit enter ":q".)

```-fno-omit-frame-pointer``` is probably unnecessary but might be needed. It's one of those things that doesn't hurt to use and might help. Better yet, it isn't as awful to type as it appears: start typing "-fno-om" and press tab to complete! Its related option, ```-fomit-frame-pointer```, tells the compiler to avoid storing stack frame pointers in a register if possible, which can technically grant some marginal performance improvements. That is the default behavior. By contrast, using this flag tells the compiler _not_ to do that and so forces the compiler to set aside a register for the frame pointer. That is desirable because we are not trying to optimize this code, we're trying to debug it, and if we don't keep the frame pointer readily available the debugger isn't always able to generate a nice stack trace.

Note that these options aren't need on your header files, but won't hurt.

## The sanitizer vs Valgrind

You may have heard of Valgrind as another way to locate memory bugs. Both accomplish the same objective in that sense. The address sanitizer slows down your compiled code but is substantially faster than running the code with Valgrind, however it is built into the code so that's an automatic performance hit (a slowdown of about ~2x according to the docs) every time you run the code until you recompile it without the sanitizer. Another difference is Valgrind can be used in cases when you don't have access to the source code, only the executables. In debugging my own code, I prefer sanitizers because I have the source and they're what I'm comfortable with.

## What the sanitizer can warn you about

### Use after free (dangling pointer dereference)

When you free a pointer, the memory it pointed to is returned to the OS and may be used to store anything. If you don't explicitly set the variable to NULL, dereferencing it later on may not crash your program and could cause bugs if the memory contains unexpected data.

### Heap buffer overflow

This occurs when you attempt to fill in a chunk of allocated memory with more bytes of data than were allocated for. So if you allocate an array of 4 integers and attempt to ```memcpy()``` some array of 5 integers into the other array, you have a heap buffer overflow.

### Stack buffer overflow

This is just like a heap buffer overflow but the memory that is overflowed is stack memory rather than heap memory.

### Global buffer overflow

Again, this is like heap and stack buffer overflows, but the memory that is overflowed is global.

### Use after return

This occurs when you refer to something that was on a call stack for a function that has returned. Ordinarily that is difficult to achieve but you can abuse pointers to accomplish it: get a pointer that will be accessible even after the function returns, like a global variable, set it to the address of some stack variable inside the function in question, execute the function, and then attempt to dereference the aforementioned pointer.

### Use after scope

Similar to use after return, this is an issue that can occur when some variable goes out of scope for some other reason besides a function return and we attempt to access it with sneaky pointer manipulation.

### Memory leaks

AddressSanitizer incorporates LeakSanitizer, so it can detect any time memory is leaked: allocated onto the heap without being freed at any point. You can actually achieve this functionality with the ```-fsanitize=leak``` option, which won't slow your program down like the address sanitizer does, but you'd miss out on all the other great features of AddressSanitizer.
