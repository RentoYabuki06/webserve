---
title: フェーズ2: 固定文字列レスポンス200
phase: 2
estimate: 20-30m
status: open
id: F2-04
deps: [F2-02, F2-03]
---

## 目的
最小レスポンス生成と送信経路を確立。

## 手順
1. ヘッダ完了後に固定ボディ "Hello" を用意
2. `Content-Length` 計算
3. `HTTP/1.1 200 OK` + ヘッダ + 空行 + ボディ連結
4. Conn.write_buf に格納, write_offset=0
5. 次の poll で送信処理

## Done
`curl localhost:8080` で "Hello" 取得。

## 補足
Keep-Aliveは後でConnection header対応。

## 解説 / 背景
レスポンス送出経路を早期に固定化し後の複雑な生成(静的/CGI)を容易化。

## リスク / 注意点
- Content-Length 計算ミス
- 書き途中で接続切断処理漏れ

## テスト観点
- curl で本文/長さ一致
- telnet 手動検証

## 受入チェックリスト
- [ ] 正しいヘッダ＋本文
- [ ] send 部分書き考慮(後続Issue)準備

## 簡易コード例
```cpp
std::string buildSimple200() {
	const char *body = "Hello WebServ";
	std::ostringstream oss;
	oss << "HTTP/1.1 200 OK\r\n";
	oss << "Content-Length: " << std::strlen(body) << "\r\n";
	oss << "Content-Type: text/plain\r\n";
	oss << "Connection: close\r\n\r\n";
	oss << body;
	return oss.str();
}
```

