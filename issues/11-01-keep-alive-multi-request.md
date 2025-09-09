---
title: フェーズ11: Keep-Alive & 複数リクエスト処理
phase: 11
estimate: 40-60m
status: open
id: F11-01
deps: [F2-05, F8-03]
---

## 目的
1接続上で複数HTTP/1.1リクエストを順次処理し接続再利用する。

## 手順
1. レスポンス送信完了後 read_buf の未消費データを次リクエストとして解析
2. Connectionヘッダが close の場合のみクローズ
3. keep-alive タイムアウト計測
4. パイプライン準備: 完全な次リクエストが届いていればキュー

## Done
curlで連続2回GETしても新しいTCP接続を張らない。

## 補足
後続のHTTPパイプラインIssueと連携。

## 解説 / 背景
接続再利用は性能とリソース削減に大きく寄与。

## リスク / 注意点
- バッファ残骸によるパースずれ
- Connection: close 判定漏れ

## テスト観点
- 1接続連続GET
- 明示close

## 受入チェックリスト
- [ ] 2連GET同一FD
- [ ] close指定で切断
- [ ] メモリ再利用

## 簡易コード例
```cpp
bool shouldKeepAlive(const std::map<std::string,std::string> &h) {
	std::map<std::string,std::string>::const_iterator it = h.find("connection");
	if (it==h.end()) return true; // HTTP/1.1 default keep
	return !(it->second == "close" || it->second == "Close");
}
```

