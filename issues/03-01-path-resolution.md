---
title: フェーズ3: パス解決（簡易root固定）
phase: 3
estimate: 30-45m
status: open
---

## 目的
要求 `/path` を `./www/path` に変換し `..` を拒否。

## 手順
1. 先頭の `/` を削除
2. 空文字は `index.html` 後で処理予定
3. `..` / 余計な `//` を検査して403
4. 連結: `root + '/' + relative`

## Done
`GET /index.html` → `www/index.html` 探索ログ。

## 補足
将来: URLデコード。
