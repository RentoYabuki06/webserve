---
title: フェーズ2: リクエストラインのパース
phase: 2
estimate: 20-30m
status: open
---

## 目的
`METHOD PATH HTTP/1.1` の形式を分解し内部保持。メソッド列挙型。

## 手順
1. ヘッダ全文冒頭行を抽出
2. space split (3要素) 失敗で400
3. メソッド: `GET/POST/DELETE` のみ対応
4. HTTPバージョン検査 `HTTP/1.1`

## Done
`GET / HTTP/1.1` が正しく構造体に入る。

## 補足
拡張: QueryString 分離は後で。
