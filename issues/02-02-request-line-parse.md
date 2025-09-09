---
title: フェーズ2: リクエストラインのパース
phase: 2
estimate: 20-30m
status: open
id: F2-02
deps: [F2-01]
---

## 目的
`METHOD PATH HTTP/1.1` の形式を分解し内部保持。メソッド列挙型。

## 手順
1. ヘッダ全文冒頭行を抽出
2. space split (3要素) 失敗で400
3. メソッド: `GET/POST/DELETE` のみ対応
4. HTTPバージョン検査 `HTTP/1.1`

## Done
`GET / HTTP/1.1` が正しく構造体に入る。

## 補足
拡張: QueryString 分離は後で。

## 解説 / 背景
最初の構文検証ポイントで早期エラー返却の責務。曖昧さを許さず状態を確定。

## リスク / 注意点
- 空白複数やタブ対応漏れ
- HTTP/1.0 応答方針未定
- 未知メソッド許容で後段崩壊

## テスト観点
- 正常: GET / HTTP/1.1
- 異常: メソッドなし, 要素4つ
- 小文字 http/1.1 を拒否するか方針

## 受入チェックリスト
- [ ] 3トークン分割
- [ ] バージョン検証
- [ ] 未知メソッド拒否

## 簡易コード例
```cpp
struct Request { std::string method, target, version; };
bool parseRequestLine(const std::string &line, Request &r) {
	std::istringstream iss(line);
	if (!(iss >> r.method >> r.target >> r.version)) return false;
	if (r.version != "HTTP/1.1") return false;
	if (r.method != "GET" && r.method != "POST" && r.method != "DELETE") return false;
	return true;
}
```

