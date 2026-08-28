# Unmatched Game

A digital, two-player adaptation of the **Unmatched** board game, built from scratch in C++ using [raylib](https://www.raylib.com/) for rendering, animation, and input handling.

## Overview

Two players draft a hero, deploy their sidekicks across a shared board, and battle it out through a full card-driven combat system — movement, scheming, attacking, and defending — until one side is defeated.

## Heroes

| Hero | Playstyle |
|---|---|
| **Dracula** | Feeds on his sisters and nearby sidekicks to heal and fuel devastating attacks |
| **Sherlock Holmes** | Fights alongside Dr. Watson, relying on deduction, trickery, and repositioning |
| **Invisible Man** | Uses a rolling fog and stealth mechanics to slip across the board unseen |

## Features

- Complete turn structure: movement → scheme → attack/defend → resolution
- Custom board engine with adjacency rules, hidden pathways, and fog-based movement
- Full combat resolution: card selection, damage calculation, and triggered effects
- Card system with timing windows (*Before / During / After / Immediate*) and combat styles (*Aggression / Intellect / Stealth*)
- Hand-built UI in raylib: main menu, hero/age selection, board view, combat screen, and a zoomable card/deck viewer

## Requirements

- C++17 (or later)
- [CMake](https://cmake.org/) 3.x+
- [raylib](https://www.raylib.com/) 6.0

## Build & Run

```bash
git clone <repo-url>
cd Unmatched_Game
cmake -B build
cmake --build build
cd build
./MyProject
```

> If a code change doesn't seem to take effect after rebuilding, do a clean build — stale object files can make `cmake --build` skip recompiling:
> ```bash
> cmake --build build --clean-first
> ```

## Project Structure

```
include/
  board/      # Board and Space definitions
  card/       # Card, CardText, Effect
  fighter/    # Heroes, Dracula, Sherlock Holmes, Invisible Man, sidekicks/tokens
  front/      # raylib UI: menus, pages, windows
  game/       # Game and Player logic
src/          # Implementation files mirroring include/
```


## Author

Made by **[Your Name]**
- GitHub: [@nikitaito](https://github.com/nikitaito)

Contributions, bug reports, and suggestions are welcome — feel free to open an issue or pull request.

