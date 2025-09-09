---
title: フェーズ1: accept() と接続FD管理
phase: 1
estimate: 30-45m
status: open
---

## 目的
新規接続を非ブロッキングで受理し、`pollfds` に R/W 同時監視で追加。切断時にクリーンアップ。

## 手順
1. listen FD にイベントあったら `accept()` ループ
2. 新FDへ `O_NONBLOCK`
3. `pollfds` に `POLLIN | POLLOUT` (後で書き条件制御) 追加
4. 接続構造体 `Conn`（read_buf, write_buf, stateなど）map管理
5. 切断/エラーで削除

## Done
接続/切断がログされ FDリークなし。

## 補足
後で送信準備まで `POLLOUT` 抑制する最適化計画。
