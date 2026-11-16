# OOP Final Project — Blackjack Casino Simulation

C++ / Object-Oriented Programming final project. This repository currently contains the **Part 1** implementation, with eight concrete player types and a separate dealer class. Later improvements can be committed to this repository.

## Project structure

- `src/main.cpp` — program entry point and basic assertions/demo
- `src/Player.h` — abstract player interface and shared state
- `src/PlayerTypes.h` — play strategies and red/green concrete player types
- `src/Dealer.h` — dealer behavior, balance, statistics, and salary calculations
- `BlackjackPart1.vcxproj` — Visual Studio C++ project
- `docs/` — Part 1 report, class hierarchy, and example output

## Build and run

**Visual Studio (Windows):** Open `BlackjackPart1.vcxproj`, select x64 Debug, and build/run. The project was exported from Visual Studio with toolset `v145`; if your installed Visual Studio uses a different toolset, use *Project → Retarget solution* or adjust project properties.

**Command line (g++):**

```bash
g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp -o blackjack
./blackjack
```

The program demonstrates each player's bet and hit/stand decision, followed by dealer rules and basic assertions. Random decisions are seeded for repeatability (`srand(7)`).

## Development status

- [x] Part 1: player class hierarchy and dealer demonstration
- [ ] Future project parts and improvements

This is a source-code repository, not a ZIP archive. Generated Visual Studio caches, executables, and build intermediates are excluded from version control by `.gitignore`.
