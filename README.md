# Sami-shell

A minimal Unix shell written in C — my first real systems project in the language.

It runs an interactive prompt, tokenizes input into a custom dynamic vector, and executes commands with `fork` / `execvp`. Built-ins that must change the shell process itself (`cd`, `exit`) run in the parent; everything else runs in a child.

## Demo

```text
Sami-shell> pwd
/Users/you/projects/terminal
Sami-shell> cd src
Sami-shell> ls
commands.c  main.c  string.c  terminal.c  vector.c
Sami-shell> samfetch
  ___________    ____
 /  ___/\__  \  /    \
 \___ \  / __ \|   |  \
/____  >(____  /___|  /
     \/      \/     \/
Sami-shell> exit
goodbye from sami :)
```

## Features

- Interactive REPL prompt (`Sami-shell>`)
- Custom growable `char**` vector (manual `malloc` / `realloc` / `free`)
- Custom tokenizer (split on spaces / newlines)
- External commands via `fork` + `execvp`, with `perror` on failure
- Parent built-ins: `cd`, `exit`
- Child commands: `ls`, `pwd`, `clear`, `samfetch`, unknown-command handling
- `Ctrl+C` (`SIGINT`) clean shutdown

## Build & run

**Requirements:** GCC (C11), Unix-like OS (`fork`, `execvp`, `wait`, signals)

```bash
make          # → build/sami
make run      # build + launch
make clean
```

```bash
./build/sami
```

## Project structure

```text
include/
  commands.h       Command enum + handler declarations
  customString.h   Tokenizer / string helpers
  terminal.h       Shell entry + exit
  vector.h         Dynamic argument vector
src/
  main.c           Entry point
  terminal.c       REPL, fork/exec, samfetch, signals
  commands.c       Parent built-ins (cd, exit)
  string.c         Tokenize line → vector
  vector.c         Growable char* storage
Makefile
```

## How it works

1. Read a line from stdin into a fixed buffer
2. Split tokens into a `vector` of `char*` (argv-style)
3. Handle parent-only commands (`cd`, `exit`)
4. `fork` — child runs `execvp` / `samfetch` / prints unknown; parent `wait`s
5. Loop back to the prompt

Parent vs child matters: `cd` has to call `chdir` in the shell process, or the directory change dies with the child.

## What I learned

- Manual memory management and owning a simple dynamic array in C
- Splitting a program across headers/modules instead of one big file
- Process control: `fork`, `execvp`, `wait`
- Why shells treat some commands as built-ins
- Signal handling (`SIGINT`) and cleaning up on exit
- Enums + `switch` / `default` for command dispatch

## Limitations

Learning scope — not a bash replacement:

- No pipes, redirects, or quoting
- No background jobs / job control
- Simple space-based tokenization
- Still some rough edges around empty input and wait status handling

## License

Personal / learning project — use as you like.
