# TODO
1. Implement Memory Allocation (Keeps track of how much ram is free) (Manages 64 MiB)
    - `void* malloc(long ammount)`
    - `void* mfree(void* addr, long ammount)`
2. Shell Variables
    - `set [variablename] [stringvalue]` (string goes to end of input)
    - `copy [srcvariablename] [destvariablename]`
    - `get [variablename]...` (infinite variablenames to get/print to terminal.)
3. Shell Math (if a variable has a non numerical value, it becomes 0 in calculation)
    - `add [srcvariablename] [destvariablename]` (infinite destination variables) (source variable is added to all destination variables)
    - `subtract [srcvariablename] [destvariablename]` (same as add but with subtraction)
    - `multiply [srcvariablename] [destivariablename]`
    - `divide [srcvariablename] [destvariablename]`
4. Shell Control Flow
    - `if [variablename] <"=="/"!="/">"/"<"/">="/"<=", or "is"> [variablename/string] <and/or> [otherconditions]...`
        - Starts an if statement
    - `function [functionname]`
        - Starts a function, instructions called after do not get run, instead get saved to a buffer
    - `end`
        - Ends a function or an if statement
    - `run [functionname]`
5. BitFS
    - BitOS RAM Filesystem
    - Uses malloc
    - Files are buffers
    - Directories are files that have pointers to other files
        - Key value pairs in struct
6. Shell Filesystem
    - Interact with BitFS
    - `write [variablename] [filename]`
    - `read [filename] [variablename]`
    - `append [variablename] [filename]`
    - `touch [filename]`
    - `remove [filename]` (Removes entries of file in all directories including links)
    - `move [filename]` (Rename file in parent directory)
    - `link [filename] [linkname]` (Add entry in directory pointing to file)
    - `exists [filename]`
        - Returns "true" if directory entry found, "false" is not found
    - `follow [pathname]`
7. Graphics Mode 80x25 Mext Mode Emulation
    - All x86 platform support
