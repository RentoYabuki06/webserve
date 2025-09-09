---
title: フェーズ6: 複数ポートのlisten生成
phase: 6
estimate: 30-45m
status: open
---

## 目的
`listen 8080; listen 8081;` を両方ソケット化しpoll登録。

## 手順
1. parserで複数listen値を配列
2. 起動時にループでsocket/bind/listen
3. pollfdsへ全登録

## Done
両ポートで応答あり。

## 補足
既存ポート衝突時のエラー処理要。
