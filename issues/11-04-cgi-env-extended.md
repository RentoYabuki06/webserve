---
title: フェーズ11: CGI環境変数拡充
phase: 11
estimate: 30-45m
status: open
---

## 目的
CGI/Phpが期待する標準環境変数を追加。

## 手順
1. SERVER_SOFTWARE, SERVER_NAME, SERVER_PORT
2. GATEWAY_INTERFACE=CGI/1.1
3. SCRIPT_NAME, SCRIPT_FILENAME, PATH_INFO
4. CONTENT_TYPE, QUERY_STRING, REDIRECT_STATUS=200

## Done
phpinfo等で表示される。

## 補足
不足があれば随時追加。
