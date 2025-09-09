---
title: フェーズ11: Keep-Alive & 複数リクエスト処理
phase: 11
estimate: 40-60m
status: open
---

## 目的
1接続上で複数HTTP/1.1リクエストを順次処理し接続再利用する。

## 手順
1. レスポンス送信完了後 read_buf の未消費データを次リクエストとして解析
2. Connectionヘッダが close の場合のみクローズ
3. keep-alive タイムアウト計測
4. パイプライン準備: 完全な次リクエストが届いていればキュー

## Done
curlで連続2回GETしても新しいTCP接続を張らない。

## 補足
後続のHTTPパイプラインIssueと連携。
