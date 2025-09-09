---
title: フェーズ11: 巨大静的ファイル分割/ゼロコピー
phase: 11
estimate: 40-60m
status: open
---

## 目的
大容量ファイル送信でメモリ効率を保つ。

## 手順
1. サイズ閾値(例:1MB)判定
2. 閾値以上: チャンク read+send ループ or sendfile
3. write_buf と併用管理

## Done
10MBファイル送信時の常駐メモリ低い。

## 補足
sendfile非対応環境 fallback。
