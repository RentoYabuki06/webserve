---
title: フェーズ11: タイマー統合設計
phase: 11
estimate: 30-45m
status: open
---

## 目的
接続/CGI/書込み/keep-alive タイムアウトを一元管理。

## 手順
1. 最小期限を計算しpoll timeout短縮
2. 期限超過リスト走査
3. 統計(タイムアウト件数)ログ

## Done
無駄な短周期pollを削減。

## 補足
priority queue 検討可。
