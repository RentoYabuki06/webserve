---
title: フェーズ6: server_nameとデフォルトサーバ
phase: 6
estimate: 30-45m
status: open
---

## 目的
Hostヘッダで仮想ホスト選択。該当なしは最初のserver。

## 手順
1. Serverに `server_names` vector
2. リクエスト解析時 Host 取得
3. ルックアップ→マッチ or fallback

## Done
異なるHostで別root返す。

## 補足
正規化 (ポート除去) 必要。
