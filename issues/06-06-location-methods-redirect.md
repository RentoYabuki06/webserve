---
title: フェーズ6: locationのメソッド制限/リダイレクト
phase: 6
estimate: 40-60m
status: open
---

## 目的
`allow_methods` と `return 301 URL` でメソッド制限 & リダイレクト。

## 手順
1. 最長一致location探索
2. メソッド未許可→405 + Allowヘッダ
3. return 指定で即 301 Location

## Done
禁止メソッドで405、301が機能。

## 補足
後で 302/307 等拡張。
