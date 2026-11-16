# Blackjack Casino — Web Game Roadmap

This branch is the independent portfolio/game development track. The original C++ academic assignment remains unchanged on `main` until separately reviewed.

## Product
A browser-playable, virtual-chip blackjack casino with a polished lobby, animated table, 4–8-seat rooms, bot players, and eventually online multiplayer. No real-money wagering or cash-out.

## Rules baseline
- Standard blackjack: numbered cards at face value, faces 10, ace 1/11; dealer hits through 16 and stands on 17+.
- Natural blackjack pays 3:2; equal totals push; ordinary wins pay 1:1.
- Red ($5–45 in $5 steps), Green ($50–95 in $5 steps), Black ($100–490 in $10 steps), Blue ($500–1000 in $10 steps).
- Rules and strategies should be independently testable; avoid putting game logic in UI components.
- Room capacity 4–8 seats; do not confuse a visible seat count with actual connected multiplayer users.

## Proposed structure
```
apps/
  web/           React + TypeScript + Vite + Tailwind; responsive lobby and game table
  server/        Node.js + TypeScript + Socket.IO; authoritative room state
packages/
  game-engine/   Pure TypeScript rules, deck, hand, wagers, settlement, bot strategies
  shared/        Event and API types
docs/
  WEB_GAME_ROADMAP.md
```

## Milestones
1. Single-player playable MVP: lobby, one table, virtual chips, bet, deal, hit, stand, settlement, restart, tests.
2. Add dealer/bot strategies, room categories, 4–8 seats, responsive card animations.
3. Server-authoritative multiplayer: join/leave, seat assignment, turn timers, reconnects, concurrent rooms.
4. Persistent accounts, history, stats, rankings and optional Hall of Fame.
5. CI, deployment, monitoring, security review and accessible mobile UI.

## Engineering principles
- Academic C++ code is retained as historical source, not silently replaced.
- Never trust a client-supplied card, balance or payout in multiplayer.
- All chips are virtual, with no deposits, withdrawals or cash conversion.
- Protect against duplicate game actions and disconnections.
- Every milestone must be playable and accompanied by reproducible tests and setup instructions.

## First implementation task
Build and test `packages/game-engine` and `apps/web` for a complete single-player round before advertising multiplayer or deployment as working.
