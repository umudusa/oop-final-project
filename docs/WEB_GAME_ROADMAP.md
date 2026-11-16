# Blackjack Casino — C++ Backend Game Roadmap

This branch is an independent portfolio game track. Preserve the academic C++ assignment on main; do not mix instructor submissions with portfolio features.

## Architecture decision
**C++20 is authoritative for all gameplay and backend logic.** No TypeScript/JavaScript game engine.

- `cpp/game-engine/`: portable C++20 classes for Card, Deck/Shoe, Hand, Player, Dealer, Table, Wager, Rules and settlement, with CMake and unit tests.
- `cpp/server/`: C++ Drogon HTTP/WebSocket server; server-owned room state, cards, turns, virtual-chip balances and settlement.
- `apps/web/`: React + TypeScript frontend ONLY for lobby, cards, controls, animations, room display and communication with C++ backend.
- `docs/`: design decisions, architecture and deployment.
- PostgreSQL later for accounts, history and statistics.

Reuse/refactor the existing C++ Player, RandomPlayer, RandomRedPlayer and Dealer classes after reviewing their implementations. Do not assume they already implement full game rules.

## Game requirements
- Browser-playable blackjack, virtual chips only (no deposits, withdrawals or cash-out).
- Dealer draws on 16 or less and stands on 17 or more; natural blackjack pays 3:2, regular wins 1:1, pushes return wagers.
- Red ($5–45 in steps of 5), Green ($50–95 in steps of 5), Black ($100–490 in steps of 10), Blue ($500–1000 in steps of 10).
- Room capacity 4–8 seats; real online seat counts only after multiplayer is implemented.
- Bot strategies: Safe, Random, Mimics Dealer, custom; optional expert counting.
- All card draws, wager validation and outcomes must be calculated in C++ on the server.

## Delivery milestones
1. C++20 game engine with CMake, unit tests and deterministic game simulations.
2. C++ Drogon server with endpoints for starting a round, placing bets, hit, stand and retrieving state.
3. React frontend: polished lobby, one fully playable single-player table, animations and virtual chips.
4. C++ WebSocket multiplayer rooms, seats, synchronized turns, reconnect handling, anti-duplicate action safeguards.
5. Persistent profiles and stats, CI, production deployment and monitoring.

## Proposed repository layout
```
cpp/
  game-engine/
  server/
apps/
  web/
docs/
  WEB_GAME_ROADMAP.md
```

**Status:** Architecture plan only; no playable GUI or server implemented yet.
