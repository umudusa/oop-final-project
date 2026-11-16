# Blackjack Casino — Feature Requirements

This is an independent portfolio game, not a university submission. The product retains the functional requirements from the supplied Blackjack Casino Simulation specification while extending them into a playable modern web game.

## Blackjack and simulation requirements
- [x] Number cards face value; face cards 10; Ace 1 or 11
- [x] Up to six decks; dealer hits 16 and stands 17
- [x] Blackjack 3:2; ordinary win 1:1; push returns wager
- [x] Red $5–45 step 5; Green $50–95 step 5; Black $100–490 step 10; Blue $500–1000 step 10
- [x] C++ single-player round lifecycle, betting, hit, stand and settlement
- [ ] Tables with 4–8 players and synchronized betting/dealing/playing/result stages
- [ ] Safe, Random, Mimics Dealer and custom player strategies
- [ ] Optional expert card counting and probability analysis
- [ ] Unique player IDs and four player levels
- [ ] Configurable progression thresholds: Red→Green 200, Green→Black 1000, Black→Blue 5000; Blue Hall of Fame 100000
- [ ] System Controller, Traffic Generator, Statistics Keeper and comprehensive reports
- [ ] Per-table dealer, dealer cash threshold and refill event
- [ ] UML structural and behavioral diagrams
- [ ] Optional double down, splitting and surrender

## Portfolio extensions
- [ ] Professional responsive casino lobby and playable GUI
- [ ] C++ HTTP/WebSocket backend with isolated per-player game sessions
- [ ] Real-time multiplayer rooms, 4–8 seats, visible real player counts
- [ ] Accounts, persistent virtual balances, history and leaderboard
- [ ] Deployment, monitoring, security and end-to-end tests

**No real-money wagering or cash-out.** The engine is tested locally, but the browser game and server are not yet deployed or verified.
