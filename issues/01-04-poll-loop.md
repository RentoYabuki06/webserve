---
title: フェーズ1: poll()ループの骨格
phase: 1
estimate: 30-45m
status: open
---

## 目的
単一イベントループで `poll()` を呼び続け CPU暴走しない骨格を作る。

## 手順
1. `std::vector<pollfd>` に listen FD を `POLLIN`
2. 無限ループで `poll()`
3. 戻り値 <0 ならエラーログ
4. `timeout` は暫定 1000ms

## Done
ループが安定稼働（アイドル時CPU低負荷）。

## 補足
後でタイムアウト & 接続FD追加予定。
