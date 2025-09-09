---
title: フェーズ7: 環境変数と引数の整備
phase: 7
estimate: 40-60m
status: open
---

## 目的
CGIへ必要最低限の環境変数をセット。

## 手順
1. REQUEST_METHOD, CONTENT_LENGTH, QUERY_STRING
2. SCRIPT_FILENAME, PATH_INFO
3. SERVER_PROTOCOL, REMOTE_ADDR
4. map→`char* envp[]` 生成

## Done
CGI側で環境取得可。

## 補足
後で CONTENT_TYPE 等追加。
