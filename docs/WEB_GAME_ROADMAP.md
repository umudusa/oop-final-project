# Blackjack Casino — Development Roadmap

This is a personal software portfolio project. **C++20 is authoritative** for rules, cards, chips, turns and server-side multiplayer state. React is a presentation layer only.

## Phase 1 — Local playable prototype (initial code committed)
- [x] C++ rules and single-player round lifecycle
- [x] CMake/CTest tests and GitHub Actions
- [x] Initial C++ Drogon HTTP API (localhost only)
- [x] Initial responsive React table, Deal/Hit/Stand controls
- [ ] Verify full browser-server integration, add automated API and end-to-end tests
- [ ] Replace single shared development game with isolated player sessions

## Phase 2 — Casino simulation parity
- Four player strategy families and four wagering levels
- 4–8 seat tables, traffic generation, controller, statistics keeper, dealer refill events
- Configurable level progression and UML diagrams

## Phase 3 — Secure multiplayer
- Server-authoritative WebSocket rooms, seat ownership, timers and reconnects
- Authentication, per-room state, persistent virtual chips, transactional settlement
- Lobby, real room occupancy, leaderboard and player profiles

## Phase 4 — Production
- Animations, responsive/mobile polish, accessibility, sound options
- Docker, CI/CD, database, monitoring, load/security testing and public deployment

Only virtual chips; no cash deposits, withdrawals or real-money gambling. See [feature checklist](FEATURE_REQUIREMENTS.md).
