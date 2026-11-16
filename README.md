# Blackjack Casino

An independent, modern **C++20-backed Blackjack Casino** game and software-engineering portfolio project.

> **Status:** C++ rules engine and single-player round lifecycle implemented. The web GUI, C++ server, multiplayer and deployment are upcoming, not yet playable.

## Technology
- **C++20** for authoritative game logic and future backend
- **CMake + CTest + GitHub Actions** for build and verification
- Planned: **Drogon (C++ HTTP/WebSocket)**, **React + TypeScript** UI, **PostgreSQL** persistence

## Current project
- `cpp/game-engine/Blackjack.hpp`: card/deck/hand rules, wager tiers, outcomes, payouts
- `cpp/game-engine/Round.hpp`: single-player round state machine with virtual chip balance
- `cpp/game-engine/tests.cpp` and `round_tests.cpp`: baseline tests
- `legacy/prototype/`: preserved early C++ prototype, not the current application
- `docs/FEATURE_REQUIREMENTS.md`: full feature checklist based on the Blackjack Casino specification

## Build and test
```sh
cmake -S cpp/game-engine -B build/engine
cmake --build build/engine
ctest --test-dir build/engine --output-on-failure
```

## Next milestones
C++ server, polished playable browser table, four strategies, 4–8-seat rooms, multiplayer and public deployment. See [roadmap](docs/WEB_GAME_ROADMAP.md).

Virtual chips only; no real-money wagering or withdrawals.
