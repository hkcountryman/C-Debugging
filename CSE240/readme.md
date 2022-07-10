# Debugging guide for CSE 240

[See this page for a table of handy gdb commands](https://github.com/hkcountryman/C-Debugging/blob/CSE240/GDB.md)

## About

 - buggy.c is the initial state of the program
 - lessBuggy.c is the state of the program at the end of [this video](https://youtu.be/H7JMZ9IHpDg) (I lost internet in the middle; sorry!)
 - possibleSolution.c is a solution if you want to try debugging the program yourself; the debugging process is described below

## Process

The debugging process amounts to making guesses about where the bug may have occurred and narrowing down possible locations. Putting breakpoints at likely functions and stepping through them line by line, periodically printing values that seem likely to have caused a bug, is how you narrow down these locations. Print debugging isn't bad per se, but people typically compare it to using a debugger. A debugger is often just a more efficient way to print debug because it allows you to print different expressions without modifying your program or recompiling.

To fix the remainder of the bugs in this program, I checked the contents of the contact and person structs inside and outside of functions. Pay close attention to types and think about what you want to happen vs what you see is happening. If you see that a pointer contains address `0x0`, did you mean to allocate memory for it or is it supposed to be null? If head points to the end of the list, at what point in the program did it stop pointing at the first entry in the list? C copies only the value of passed parameters to the stack for a function, so are all your changes to data that you pass into functions persisting once the functions return? Another tip is that seg faults are caused by accessing memory without allocating it correctly, but just because you don't see a seg fault doesn't mean your memory has been allocated correctly.

Use compiler warnings. You should not have any - if you are 100% positive that the compiler is warning you about something that should work, think about changing your code to accomplish the same thing without the warning. Sure, you can use an integer just like a pointer on a 64 bit system, but what happens if you aren't running this code on a 64 bit system? The warnings exist to encourage best practices and avoid bugs that you might not trigger now but that will surface eventually.

Use man pages. Unix-like systems, including Macs with developer tools installed, should have man pages for C functions you can use on that system. The command is `man <function name>`; carefully read disclaimers about the exact behavior of the function as well as return type and parameter type.
