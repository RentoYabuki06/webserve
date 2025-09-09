---
title: フェーズ2: 受信バッファ実装（行単位）
phase: 2
estimate: 30-45m
status: open
---

## 目的
`recv` 断片を貯め `\r\n\r\n` を検出するヘッダ読み取り状態機械を実装。

## 手順
1. Connに `read_buf` (std::string)
2. pollで `POLLIN` 時 `recv` 反復
3. 0: クライアント切断, <0:EAGAINで停止
4. `read_buf.find("\r\n\r\n")` で判定
5. 見つかったら状態を HEADERS_COMPLETE に遷移

## Done
ヘッダ終端を検出ログ出力。

## 補足
将来: ヘッダサイズ上限で 431 など。
