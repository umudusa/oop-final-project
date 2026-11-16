# Blackjack Casino — Feature Requirements

This is an independent portfolio game, not a university submission. The product retains the Blackjack Casino Simulation specification as game requirements.

## Rules and simulation
- [x] Number cards face value, face cards 10, Ace 1 or 11
- [x] Up to six decks; dealer hits 16 and stands 17
- [x] Blackjack 3:2, ordinary win 1:1, push returns wager
- [x] Red $5–45 step 5; Green $50–95 step 5; Black $100–490 step 10; Blue $500–1000 step 10 wager validation
- [x] Single-player round lifecycle, betting, hit, stand and settlement in C++
- [ ] Tables with 4–8 players and synchronized betting/dealing/playing/result stages
- [ ] Safe, Random, Mimics Dealer and custom player strategies; optional expert counting AI
- [ ] Unique player IDs and four levels
- [ ] Configurable progression: Red→Green $200, Green→Black $1000, Black→Blue $5000, Blue Hall of Fame $100000
- [ ] System Controller, Traffic Generator, Statistics Keeper and reports
- [ ] Dealer cash threshold and refill events
- [ ] UML structural and behavioral diagrams
- [ ] Optional double down, splitting and surrender

## Independent product features
- [x] Initial React Blackjack table with cards and controls (not end-to-end verified)
- [x] Initial C++ Drogon HTTP API for local single-player preview (not end-to-end verified)
- [ ] Multiplayer lobby, WebSocket rooms, 4–8 seats and real player counts
- [ ] Accounts, persistent virtual balances, game history, leaderboard
- [ ] Animations, sound, accessibility, mobile QA
- [ ] Deployment, monitoring, security and end-to-end tests

**Security:** Current server uses a shared global development table and is not safe for public deployment. Implement isolated sessions, secure auth, rate limits, concurrency handling and transactional chips before hosting. Virtual chips only.
