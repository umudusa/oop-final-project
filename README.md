# Blackjack Casino

A personal, independent **C++20-backed Blackjack Casino** game. This is a portfolio software project, not a course submission.

## Current status

- **C++ engine:** cards, six-deck shoe, hand totals, wagers, outcomes, payouts, and single-player round lifecycle.
- **Browser prototype:** React + TypeScript responsive Blackjack table with Deal, Hit and Stand.
- **C++ API prototype:** Drogon server exposing state/start/hit/stand endpoints on localhost.
- **Not yet complete:** multiplayer, player accounts, persistent balances, full casino simulation, split/double/surrender, and public deployment.
- **Security:** current server holds one shared development-only game. **Do not deploy publicly** until player sessions and server protections are implemented.

## Stack
C++20 + Drogon backend, React + TypeScript + Vite frontend, CMake/CTest and GitHub Actions. PostgreSQL and WebSockets planned.

## Run C++ tests
```sh
cmake -S cpp/game-engine -B build/engine
cmake --build build/engine
ctest --test-dir build/engine --output-on-failure
```

## Run locally
Install a C++20 compiler, CMake 3.20+, Node.js 20+, and Drogon with its CMake package configuration (e.g. via vcpkg).

**C++ server:**
```sh
cmake -S cpp/server -B build/server -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake
cmake --build build/server --config Release
```
Run the resulting `blackjack_server` executable (on Windows, usually `build/server/Release/blackjack_server.exe`). The server listens on `127.0.0.1:8844`.

**Web client (second terminal):**
```sh
cd apps/web
npm install
npm run dev
```
Open the Vite URL, normally `http://127.0.0.1:5173`. The frontend proxies `/api` to the C++ server. The game cannot run without the backend.

## Structure
- `cpp/game-engine/`: C++ rules and round state machine
- `cpp/server/`: Drogon local API prototype
- `apps/web/`: responsive React browser UI
- `docs/FEATURE_REQUIREMENTS.md`: original simulation requirements plus portfolio extensions
- `legacy/prototype/`: preserved early C++ prototype for reference only

See [development roadmap](docs/WEB_GAME_ROADMAP.md). Virtual chips only; no real-money gambling.
