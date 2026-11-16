# Blackjack Casino

An independent, open-source **C++20-backed blackjack game** in development. The goal is a polished browser game with virtual chips, animated cards, online rooms and multiplayer.

> Current status: initial C++ rules engine and tests. **Not yet a playable GUI or deployed multiplayer game.**

## Tech direction

- **C++20** for authoritative blackjack rules, server and multiplayer game state
- **Drogon + WebSockets** planned for the C++ HTTP/realtime server
- **React + TypeScript** planned for the browser UI only
- **PostgreSQL** planned for accounts and statistics
- **CMake + CTest + GitHub Actions** for reproducible builds and checks

## Repository

- `cpp/game-engine/Blackjack.hpp`: cards, shuffled shoe, hand values, outcome and payout logic, table wager tiers
- `cpp/game-engine/tests.cpp`: baseline engine assertions
- `cpp/game-engine/CMakeLists.txt`: standalone engine test build
- `docs/WEB_GAME_ROADMAP.md`: product roadmap and architecture
- `src/`: legacy C++ prototype retained for reference while migrating to the game engine

## Run the current tests

```bash
cmake -S cpp/game-engine -B build/engine
cmake --build build/engine
ctest --test-dir build/engine --output-on-failure
```

## Development plan

1. C++ game engine with complete single-player round lifecycle and tests.
2. C++ server API and one fully playable browser table.
3. Lobby, 4–8-seat rooms, bots and real-time multiplayer.
4. Profiles, statistics, mobile polish and cloud deployment.

All wagers use **virtual chips only**, with no real-money deposits or withdrawals.

This repository is a personal software-development project, not a course submission. See the [roadmap](docs/WEB_GAME_ROADMAP.md).
