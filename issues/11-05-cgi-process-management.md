---
title: フェーズ11: CGIプロセス管理(タイムアウト/上限)
phase: 11
estimate: 40-60m
status: open
---

## 目的
CGIハングやフォーク濫用を防ぐ。

## 手順
1. 実行中CGI数カウンタ/上限
2. 起動時に開始時刻記録
3. 一定秒数超でSIGTERM→SIGKILL
4. waitpid(WNOHANG) でゾンビ回収

## Done
無限ループCGIが強制終了され接続に適切エラー。

## 補足
タイムアウト応答は504。
