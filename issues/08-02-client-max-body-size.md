---
title: フェーズ8: client_max_body_size
phase: 8
estimate: 20-30m
status: open
---

## 目的
設定値超過ボディを 413 で即時拒否。

## 手順
1. Content-Length 参照
2. chunked は合計復元後判定
3. 超過でレスポンス生成→送信→クローズ

## Done
大きなPOSTが即拒否。

## 補足
設定は server / location 優先順位。
