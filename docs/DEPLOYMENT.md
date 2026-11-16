# Deploy Blackjack Casino

## Current architecture
The Docker image builds the React frontend, C++ game engine tests, and the Drogon server. Drogon serves both `/api/*` and the static frontend from one container.

## Render deployment
1. Open [Render Dashboard](https://dashboard.render.com/).
2. Select **New > Blueprint** and connect GitHub repository `umudusa/oop-final-project`.
3. Choose the repository's `main` branch and apply `render.yaml`.
4. Wait for the Docker build to finish and check build logs. Render will provide the HTTPS URL if deployment succeeds.
5. Open the URL and play. Select a Red Room bet, then Deal, Hit or Stand.

The first Docker build compiles Drogon from source and can take several minutes. Hosting costs and availability depend on your Render account/plan.

## Local Docker
```sh
docker build -t blackjack-casino .
docker run --rm -p 10000:10000 blackjack-casino
```
Open `http://localhost:10000`.

## Current limitations
- Single-player only; no multiplayer lobby or persistent accounts.
- Browser sessions are isolated by a secure cookie; session balances are **in-memory** and reset when the service restarts.
- Use HTTPS in hosted deployment; the session cookie is Secure and will not persist over ordinary HTTP localhost.
- This is a prototype: no persistent session store, rate limits, authentication, load testing or production security review.
- Virtual chips only, no real-money wagering.
- Docker build and hosted deployment must be verified on your hosting provider; source code in GitHub alone is not proof of a live game.
