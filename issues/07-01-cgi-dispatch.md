---
title: フェーズ7: CGI起動の配線（拡張子マップ）
phase: 7
estimate: 30-45m
status: open
---

## 目的
拡張子に応じて CGI 実行を選択。

## 手順
1. locationに `cgi_pass` 風設定 (拡張子->実行ファイル)
2. 静的配信前に拡張子判定
3. CGIフローへ分岐

## Done
対象パスでCGI起動ログ。

## 補足
セキュリティ: 実行権限チェック。
