---
title: フェーズ2: ヘッダのパース（最小）
phase: 2
estimate: 30-40m
status: open
---

## 目的
`Host`, `Connection` のみ最小実装しキーを小文字化して map に保存。

## 手順
1. リクエストライン以降を行分割
2. `:` で前後 trim
3. key を小文字化
4. map.emplace(重複は上書き可)

## Done
`headers["host"]` に値が入る。

## 補足
将来: Folded header/複数値対応。
