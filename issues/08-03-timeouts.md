---
title: フェーズ8: 接続/読み書きタイムアウト
phase: 8
estimate: 30-45m
status: open
---

## 目的
ハング防止のためアイドル接続を掃除。

## 手順
1. Connに `last_activity`
2. pollループごとに `now - last_activity`
3. 読み/書き中の個別タイムアウト
4. 408 or サイレントクローズ

## Done
放置接続が一定時間後クローズ。

## 補足
ミリ秒精度不要。秒単位でOK。
