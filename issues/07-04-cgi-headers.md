---
title: フェーズ7: CGIヘッダの取り込み
phase: 7
estimate: 30-45m
status: open
---

## 目的
CGI出力の `Status`, `Content-Type` などをHTTPレスポンスに反映。

## 手順
1. CGI出力を `\r\n\r\n` まで分離
2. 行単位解析
3. `Status: 302 Found` → status_code
4. 残りをヘッダに追加

## Done
`Content-Type:text/html` が反映。

## 補足
未指定は200 & default text/html。
