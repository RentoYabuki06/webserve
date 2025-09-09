---
title: フェーズ11: ログ拡張（アクセスログ）
phase: 11
estimate: 20-30m
status: open
---

## 目的
各リクエスト統計を記録し解析可能にする。

## 手順
1. 開始時刻記録
2. 完了時 ステータス/バイト/処理ms
3. フォーマット: method path status bytes ms

## Done
ログ1行/リクエスト。

## 補足
将来: JSON出力オプション。
