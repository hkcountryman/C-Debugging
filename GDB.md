# GDB: The Gnu Debugger

The Gnu Debugger, or GDB, is a debugger for a ton of different languages, but what we care about is that it can debug C. `gdb` is the text-based debugger, but numerous implementations exist that add a graphical interface. In this tutorial we'll use the text-based debugger because

- it is my preference since it involves less clicking and moving the mouse around (yes, I'm that lazy), and
- if you can use the command line tool you will understand how to use it in your IDE if you figure out where all the buttons are, but I couldn't possibly demo every single GUI out there in one tutorial!

[Read all about it on their website!](https://www.sourceware.org/gdb/)

## To use GDB

From the command line, after compiling with debugging symbols (`-g` flag in GCC), use either of the following. The latter will allow you to pass arguments to your program:

```
gdb <executable>
gdb --args <executable> <args...>
```

## Overview of useful commands

Many of these have shortened versions! You'll probably recognize their functionality from other debuggers you've used.

| Command | Abbrev. | Action
|-|-|-|
| `help <c>` | `h` | Help info about command c |
| | | |
| `file <b>` | | Reload the symbol table after recompiling the binary b to debug a modified program without quitting GDB |
| | | |
| `break <n>` | `b` | Insert breakpoint at line n/function named "n" |
| `break <f>::<n>` | `b` | Insert breakpoint at line n/function named "n" of file "f" (no file extension) |
| `disable <#>` | `dis` | Temporarily disable breakpoint # |
| `enable <#>` | `en` | Re-enable breakpoint # |
| `delete <#...>` | `d` | Delete breakpoint(s) # |
| `delete` | `d` | Delete all breakpoints |
| `condition <#> <e>` | `cond` | Stop at breakpoint # if expression e is true |
| | | |
| `run` | `r` | (Re)start the program until next breakpoint, crash, or end |
| `continue` | `c` | Continue until next breakpoint, crash, or end |
| `next` | `n` | Go to next instruction |
| `step` | `s` | Step into a function |
| `up` | | Go up (to caller) |
| `down` | `do` | Go back down (call after `up`) |
| `list` | `l` | Show surrounding code around current line |
| | | |
| `print <e>` | `p` | Print expression (identifier, or evaluate e) |
| | | |
| `record` / `record btrace` | | Enable rewinding from this point on in an already running program (not available on all environments; requisite for following commands) |
| `reverse-continue` | `rc` | Go back to point at which program last stopped |
| `reverse-step` | | Step *backwards* into the last executed line, if it was a function |
| `reverse-next` | | Go back one line |
