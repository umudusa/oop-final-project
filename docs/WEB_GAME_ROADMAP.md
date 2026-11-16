# Blackjack Casino — Product Roadmap

A personal, independent, deployable blackjack game. **C++20 remains authoritative** for game rules, cards, balance calculations, turns, bots and server-side multiplayer state.

## Architecture
- `cpp/game-engine`: C++20 rules and round state machine, CMake/CTest
- `cpp/server` (planned): Drogon HTTP/WebSocket server
- `apps/web` (planned): React + TypeScript + Vite for UI only
- PostgreSQL (planned): users, game history, statistics
- GitHub Actions: C++ checks

## Milestones
1. C++ rules engine, wagers, round lifecycle and tests — initial version implemented.
2. C++ server API and single-player playable browser table.
3. Four strategy bots, room tiers, 4–8 seats, casino simulation/statistics and level progression.
4. Secure real-time multiplayer, accounts, session isolation, reconnects and transactional chips.
5. Responsive UI polish, accessibility, Docker, deployment and observability.

See [feature checklist](FEATURE_REQUIREMENTS.md) for specification coverage.

## Security
Only virtual chips. Never deploy a shared global table as multiplayer. Server must own the deck and payouts, validate actions and bets, isolate sessions, rate limit requests and handle concurrency.
