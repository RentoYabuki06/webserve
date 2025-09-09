---
title: フェーズ11: シグナル優雅終了 (SIGINT/SIGTERM)
phase: 11
estimate: 20-30m
status: open
---

## 目的
安全に終了しリソースリーク防止。

## 手順
1. シグナルハンドラでフラグ
2. ループ脱出→全FD/子プロセスクリーンアップ

## Done
Ctrl+Cでメモリ/FDリークなし。

## 補足
複数回SIGINTで強制終了。
