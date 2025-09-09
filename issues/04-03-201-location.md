---
title: フェーズ4: 201 Created とロケーション
phase: 4
estimate: 20-30m
status: open
id: F4-03
deps: [F4-02]
---

## 目的
アップロード成功で 201 と `Location` ヘッダ返却。

## 手順
1. 保存パスをURL化（簡易 `/uploads/<name>`）
2. レスポンス: `HTTP/1.1 201 Created` + Location

## Done
`curl -i` で 201 / Location 表示。

## 補足
後で重複時409など検討。

## 解説 / 背景
REST的振る舞い確立。クライアントに新リソース場所を通知。

## リスク / 注意点
- Location 先頭スラッシュ欠如
- Body とヘッダ不整合

## テスト観点
- 201 ステータス
- Location 形式

## 受入チェックリスト
- [ ] 201返却
- [ ] Location正当
- [ ] Content-Length整合

## 簡易コード例
```cpp
std::string response201(const std::string &loc) {
	std::string body="Created";
	std::ostringstream oss;
	oss << "HTTP/1.1 201 Created\r\nLocation: " << loc << "\r\nContent-Length: " << body.size() << "\r\n\r\n" << body;
	return oss.str();
}
```

