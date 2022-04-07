# ASan: The Address Sanitizer

A sanitizer is just something that is actually built into your code at compile time so that undesirable behavior can be detected and reported at runtime. AddressSanitizer reports bugs to do with memory management. There are also other types of sanitizers; of interest might be ThreadSanitizer and UndefinedBehaviorSanitizer! Check out the [compiler-rt runtime libraries project at llvm.org](https://compiler-rt.llvm.org/) to learn about them all.

(If you want to see how to use them all with GCC, enter `info gcc` into your terminal and navigate to Invoking GCC > Instrumentation Options. Search for "fsanitize" by entering "/fsanitize <enter>" while in info mode. To navigate to the next/previous search result, enter "n" or "N". To quit, enter ":q".)

## What ASan can warn you about

### Use after free (dangling pointer dereference)

When you free a pointer, the memory it pointed to is returned to the OS and may be used to store anything. If you don't explicitly set the variable to NULL, dereferencing it later on may not crash your program and could cause bugs if the memory contains unexpected data.

### Heap buffer overflow

This occurs when you attempt to fill in a chunk of allocated memory with more bytes of data than were allocated for. So if you allocate an array of 4 integers and attempt to `memcpy()` some array of 5 integers into the other array, you have a heap buffer overflow.

### Stack buffer overflow

This is just like a heap buffer overflow but the memory that is overflowed is stack memory rather than heap memory.

### Global buffer overflow

Again, this is like heap and stack buffer overflows, but the memory that is overflowed is global.

### Use after return

This occurs when you refer to something that was on a call stack for a function that has returned. Ordinarily that is difficult to achieve but you can abuse pointers to accomplish it: get a pointer that will be accessible even after the function returns, like a global variable, set it to the address of some stack variable inside the function in question, execute the function, and then attempt to dereference the aforementioned pointer.

### Use after scope

Similar to use after return, this is an issue that can occur when some variable goes out of scope for some other reason besides a function return and we attempt to access it with sneaky pointer manipulation.

### Memory leaks

AddressSanitizer incorporates LeakSanitizer, so it can detect any time memory is leaked: allocated onto the heap without being freed at any point. You can actually achieve this functionality with the `-fsanitize=leak` option, which won't slow your program down like the address sanitizer does, but you'd miss out on all the other great features of AddressSanitizer.

## Interpreting the output

AddressSanitizer will collect call stacks for allocations/frees, thread creations, and any failures. Look out primarily for the code closest to the top of these stacks (if they are displayed) that is not code belonging to the standard library, which is in all likelihood not the cause of a bug. (Standard library code is easy to spot: it probably has your architecture in the name and may include things like "glibc.") These call stacks are great for figuring out where to start debugging. Segmentation faults become run-of-the-mill crashes instead of nightmarish horrors that everyone inexplicably hates more than Python crashes when they come with stack traces!

Additionally, the sanitizer actually provides its own implementation for `malloc()` and `free()` so that it can keep track of heap memory. It tracks "shadow" memory that contains metadata for main memory. 1 byte of shadow memory corresponds to 8 bytes of main memory. If the sanitizer detects issues, you'll see a map of shadow memory corresponding to the area around the buggy address after any relevant call stacks print. If you see anything about "poisoning," just bear in mind that refers to writing some special value to shadow memory.

See [Google's wonderful docs](https://github.com/google/sanitizers/wiki/AddressSanitizer) for more info and usage examples!

## The sanitizer vs Valgrind

You may have heard of Valgrind as another way to locate memory bugs. Both accomplish the same objective in that sense. The address sanitizer slows down your compiled code but is substantially faster than running the code with Valgrind, however it is built into the code so that's an automatic performance hit (a slowdown of about ~2x according to the docs) every time you run the code until you recompile it without the sanitizer. Another difference is Valgrind can be used in cases when you don't have access to the source code, only the executables. In debugging my own code, I prefer sanitizers because I have the source and they're what I'm comfortable with.
