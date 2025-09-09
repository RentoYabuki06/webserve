---
title: フェーズ8: chunked デコーダ（受信）
phase: 8
estimate: 40-60m
status: open
---

## 目的
`Transfer-Encoding: chunked` の本文を復元。

## 手順
1. 状態機械: SIZE_LINE -> DATA -> CRLF -> (repeat)
2. サイズは16進数パース
3. 0サイズで終了 -> 終端

## Done
chunked POST が素体ボディに復元。

## 補足
拡張パラメータ無視。
