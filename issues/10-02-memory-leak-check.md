---
title: フェーズ10: メモリリークチェック
phase: 10
estimate: 40-60m
status: open
---

## 目的
終了時リークゼロ。

## 手順
1. macOS: `Leaks` か `Instruments`
2. Linux互換環境でValgrind実行
3. 主要経路テストスクリプト
4. 修正サイクル

## Done
主要経路でリークなし確認。

## 補足
長時間接続テストは任意。
