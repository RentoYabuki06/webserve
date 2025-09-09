---
title: フェーズ4: Content-Length受信（ヘッダ）
phase: 4
estimate: 30-40m
status: open
---

## 目的
`Content-Length` 値を取得し固定長ボディ受信状態管理。

## 手順
1. ヘッダmapから `content-length`
2. 数値パースと上限チェック(暫定 1MB など)
3. 状態を `READING_BODY` に遷移
4. 既読バッファから不足分読み込む

## Done
既知サイズボディを完全に受信し次の処理に進む。

## 補足
後で chunked 優先処理を追加。
