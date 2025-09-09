---
title: フェーズ11: 必須レスポンスヘッダ(Date/Connection/Server)
phase: 11
estimate: 20-30m
status: open
id: F11-03
deps: [F2-04]
---

## 目的
共通ヘッダを統一的に付与し互換性を高める。

## 手順
1. 共通ヘッダビルダ関数作成
2. Date(RFC1123)生成
3. Connection: keep-alive/close ロジック
4. Server: "webserv/0.1" (任意)

## Done
任意レスポンスでヘッダを確認。

## 補足
ETag/Last-Modified は対象外。

## 解説 / 背景
標準的なHTTPクライアント互換性確保。

## リスク / 注意点
- Dateフォーマット誤り
- Connection 判定ミス

## テスト観点
- 任意レスポンスヘッダ
- keep-alive / close 両方

## 受入チェックリスト
- [ ] Date 形式
- [ ] Connection 正しい
- [ ] Server 文字列

## 簡易コード例
```cpp
std::string rfc1123(time_t t) {
	char buf[128]; struct tm g; gmtime_r(&t, &g);
	strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", &g);
	return buf;
}
```

