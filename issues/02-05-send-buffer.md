---
title: フェーズ2: 送信バッファ & 送信完了管理
phase: 2
estimate: 30-45m
status: open
---

## 目的
`send` の部分書きに対応し全量送信完了で接続を維持またはクローズ。

## 手順
1. Connに `write_buf`, `write_offset`
2. `POLLOUT` 発火で `send`(残量)
3. EAGAINで一時停止
4. 全送信でバッファクリア → 今回はクローズ(暫定)

## Done
大きめ（数KB）データでも正しく完了まで送る。

## 補足
後でKeep-Alive判定追加し再利用。
