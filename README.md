# Conway's Game of Life

A multi-language implementation of Conway's Game of Life — simulation logic in C++, rendering in Python.

## Preview

![Pulsar pattern](GoL.gif)

*Pulsar oscillator (period 3) — screen recording of the actual pygame renderer, one full loop.*

## Architecture

```
C++ (simulation) --stdout--> pipe --stdin--> Python (rendering, pygame)
```

- **C++** owns the grid state and simulation rules. Computes each generation and writes it to stdout as plain text — one row per line, with a `---` sentinel marking the end of a frame.
- **Python** reads frames from stdin (on a background thread, via a queue) and draws them with pygame.
- Communication is one-way (C++ → Python) over a standard Unix pipe.

## Rules

Standard Conway's Game of Life:
- A live cell with 2 or 3 live neighbors survives.
- A dead cell with exactly 3 live neighbors becomes alive.
- Any other cell dies or stays dead.

Grid is fixed-size (not infinite/toroidal) — cells near the edge have fewer neighbors, and patterns that move (like gliders) disappear once they reach the boundary.

## Seeding

Initial cell positions are currently set in code (`init()`). Supports classic patterns for testing: pentadecathlon (p15), pulsar (p3), figure eight (p8), and the Gosper glider gun. A custom lexer/parser for a text-based seed format is planned, so patterns can be defined without recompiling.

## Running

```bash
g++ -o gol main.cpp
./gol | python3 render.py
```

## Requirements

- C++ compiler (g++/clang++)
- Python 3
- `pygame` (`pip install pygame`)
