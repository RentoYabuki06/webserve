---
title: フェーズ11: 必須レスポンスヘッダ(Date/Connection/Server)
phase: 11
estimate: 20-30m
status: open
---

## 目的
共通ヘッダを統一的に付与し互換性を高める。

## 手順
1. 共通ヘッダビルダ関数作成
2. Date(RFC1123)生成
3. Connection: keep-alive/close ロジック
4. Server: "webserv/0.1" (任意)

## Done
任意レスポンスでヘッダを確認。

## 補足
ETag/Last-Modified は対象外。
