# Blackjack Casino — Development Roadmap

## Goal
Build a professional, independently developed, browser-playable blackjack casino using virtual chips, with multiplayer rooms and a C++ backend. This GitHub repository is for personal development and portfolio use; course submissions are handled separately outside this repository.

## Architecture
- C++20: authoritative game engine and backend; all card draws, turn validation, payouts and balances happen server-side
- Drogon: planned C++ HTTP/WebSocket API
- React + TypeScript + Tailwind: planned responsive browser GUI, with no duplicate blackjack rules engine
- PostgreSQL: planned persistent accounts and statistics
- CMake/CTest and GitHub Actions: build and automated verification

## Core game
- Ace 1/11, faces 10, natural blackjack pays 3:2, standard win 1:1, push returns wager
- Dealer hits on 16 and stands on 17
- Virtual chips only, no real-money gambling or cash-out
- Red, Green, Black and Blue betting tiers
- 4–8 seat rooms; show real online player counts only once network multiplayer works
- Bot strategies and optional advanced actions after the basic round works

## Delivery milestones
1. **Engine:** complete C++ round state machine, deterministic tests and wager validation
2. **Playable MVP:** C++ API + polished React table; bet, deal, hit, stand, settlement and restart
3. **Multiplayer:** server-authoritative WebSocket rooms, seats, turns, reconnects and anti-duplicate actions
4. **Production:** profiles, statistics, accessible mobile UI, CI and hosted deployment

## Structure
```
cpp/game-engine/     C++20 rules engine and tests
cpp/server/          Planned C++ API and WebSocket server
apps/web/            Planned React browser client
src/                 Earlier C++ prototype, retained as reference
docs/                Architecture and roadmap
```

**Current status:** The initial engine code and test target exist; the GUI, API, rooms and deployment are not implemented yet.
