---
title: フェーズ3: ファイル読み込みとContent-Length
phase: 3
estimate: 30-45m
status: open
---

## 目的
静的ファイルを読み込みボディ化し `Content-Length` 設定。

## 手順
1. `stat` で存在/権限チェック
2. `open` + `read` (小サイズ前提で一括)
3. バイナリ安全: `std::vector<char>`
4. レスポンス生成（後のMIMEは別Issue）

## Done
実ファイルの内容が返る。

## 補足
巨大ファイル分割送信は後で最適化。
