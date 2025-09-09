---
title: フェーズ1: ソケット作成・非ブロッキング化
phase: 1
estimate: 30-45m
status: open
---

## 目的
`socket/bind/listen` でポート(例:8080)を開き、`fcntl(O_NONBLOCK)` を設定。

## 手順
1. `AF_INET`, `SOCK_STREAM`
2. `setsockopt(SO_REUSEADDR)`
3. `bind(0.0.0.0:8080)`
4. `listen(backlog=128)`
5. `fcntl(fd, F_SETFL, O_NONBLOCK)`
6. 成功ログ: `Listening on :8080`

## Done
起動時にログが表示され、プロセスが落ちない。

## 補足
後で複数listen対応予定。エラー時は `Log::error`。
