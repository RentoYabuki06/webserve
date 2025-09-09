---
title: フェーズ2: 固定文字列レスポンス200
phase: 2
estimate: 20-30m
status: open
---

## 目的
最小レスポンス生成と送信経路を確立。

## 手順
1. ヘッダ完了後に固定ボディ "Hello" を用意
2. `Content-Length` 計算
3. `HTTP/1.1 200 OK` + ヘッダ + 空行 + ボディ連結
4. Conn.write_buf に格納, write_offset=0
5. 次の poll で送信処理

## Done
`curl localhost:8080` で "Hello" 取得。

## 補足
Keep-Aliveは後でConnection header対応。
