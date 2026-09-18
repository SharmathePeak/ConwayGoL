# Conway's Game of Life

A multi-language implementation of Conway's Game of Life — simulation logic in C++, rendering in Python, connected via a Unix pipe.

## Architecture

```
C++ (simulation) --stdout--> pipe --stdin--> Python (rendering, pygame)
```

- **C++** owns the grid state and simulation rules. Computes each generation and writes it to stdout as plain text, one row per line, with a `---` sentinel marking the end of a frame.
- **Python** reads frames from stdin and draws them with pygame.
- Communication is one-way (C++ → Python) over a standard pipe (`./gol | python3 render.py`).

This split was built partly as an exercise in cross-language IPC — understanding how two processes in different languages talk over stdin/stdout, buffering behavior, and frame framing (the `---` sentinel), before moving to raw `pipe()`/`fork()`/`exec()` syscalls.

## Rules

Standard Conway's Game of Life:
- A live cell with 2 or 3 live neighbors survives.
- A dead cell with exactly 3 live neighbors becomes alive.
- Any other cell dies or stays dead.

Grid is currently fixed-size (not infinite/toroidal) — edge cells have fewer neighbors, which affects behavior near boundaries.

## Seeding

Initial cell positions are set programmatically for now. A custom lexer/parser for a seed-definition format (to specify starting patterns without recompiling) is planned.

## Version Control

This project uses [jj (Jujutsu)](https://github.com/martinvonz/jj) on a colocated git backend — standard `git`/GitHub tooling works normally alongside it.

## Status

- [x] Core simulation logic (double-buffered generation updates)
- [x] Basic pipe output from C++
- [ ] Python/pygame rendering of piped frames
- [ ] Custom lexer/parser for seed patterns
- [ ] Configurable grid size (currently fixed small grid for testing)

## Running

```bash
g++ -o gol main.cpp
./gol | python3 render.py
```

## Requirements

- C++ compiler (g++/clang++)
- Python 3
- `pygame` (`pip install pygame`)
