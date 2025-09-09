---
title: フェーズ11: pollfd 管理最適化
phase: 11
estimate: 20-30m
status: open
---

## 目的
多数接続時の削除コストを削減。

## 手順
1. fd→index の map
2. 削除: 末尾とスワップ
3. インデックス更新

## Done
大量接続で性能安定。

## 補足
統計ログ追加可。
