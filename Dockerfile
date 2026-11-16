# syntax=docker/dockerfile:1
FROM node:22-bookworm-slim AS frontend
WORKDIR /web
COPY apps/web/package*.json apps/web/tsconfig.json apps/web/vite.config.ts apps/web/index.html ./
COPY apps/web/src ./src
RUN npm install --no-audit --no-fund && npm run build

FROM ubuntu:24.04 AS cppbuild
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
  build-essential cmake git pkg-config libssl-dev libjsoncpp-dev uuid-dev \
  zlib1g-dev libsqlite3-dev libpq-dev libbrotli-dev ca-certificates \
  && rm -rf /var/lib/apt/lists/*
RUN git clone --depth 1 --branch v1.9.11 https://github.com/drogonframework/drogon.git /tmp/drogon \
  && git -C /tmp/drogon submodule update --init --recursive \
  && cmake -S /tmp/drogon -B /tmp/drogon/build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF \
  && cmake --build /tmp/drogon/build -j2 \
  && cmake --install /tmp/drogon/build
COPY cpp /app/cpp
RUN cmake -S /app/cpp/game-engine -B /app/build/engine -DCMAKE_BUILD_TYPE=Release \
  && cmake --build /app/build/engine -j2 \
  && ctest --test-dir /app/build/engine --output-on-failure
RUN cmake -S /app/cpp/server -B /app/build/server -DCMAKE_BUILD_TYPE=Release \
  && cmake --build /app/build/server -j2

FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive PORT=10000
RUN apt-get update && apt-get install -y --no-install-recommends \
  libssl3t64 libjsoncpp25 libuuid1 zlib1g libsqlite3-0 libpq5 libbrotli1 \
  ca-certificates && rm -rf /var/lib/apt/lists/*
COPY --from=cppbuild /usr/local/lib /usr/local/lib
COPY --from=cppbuild /app/build/server/blackjack_server /app/blackjack_server
COPY --from=frontend /web/dist /app/public
WORKDIR /app
RUN ldconfig
EXPOSE 10000
CMD ["./blackjack_server"]
