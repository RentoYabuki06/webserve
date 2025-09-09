---
title: フェーズ11: E2Eテストスクリプト整備
phase: 11
estimate: 40-60m
status: open
id: F11-19
deps: [F9-02]
---

## 目的
主要機能の自動回帰テスト。

## 手順
1. シェル/ Python スクリプト
2. GET/POST/DELETE, CGI, chunked, エラー
3. 期待コード/本文アサート

## Done
1コマンドで全緑。

## 補足
CI化は任意。

## 解説 / 背景
自動化で回帰防止・品質可視化。

## リスク / 注意点
- 外部環境依存 (ポート衝突)
- 一時ファイル掃除漏れ

## テスト観点
- スクリプト idempotent
- 失敗時 exit!=0

## 受入チェックリスト
- [ ] 全ケースパス
- [ ] 再実行パス

## 簡易コード例
```bash
#!/bin/sh
set -e
curl -s -o /dev/null -w "GET / => %{http_code}\n" http://127.0.0.1:8080/
curl -s -X DELETE -o /dev/null -w "DELETE /tmp => %{http_code}\n" http://127.0.0.1:8080/tmp/test.txt || true
```

