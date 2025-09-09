---
title: フェーズ3: パス解決（簡易root固定）
phase: 3
estimate: 30-45m
status: open
id: F3-01
deps: [F2-02, F2-03]
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

## 解説 / 背景
安全なファイルアクセスの第一段階。サーバ全体のセキュリティ境界を定義。

## リスク / 注意点
- `..` 判定抜け (URLエンコード)
- 二重スラッシュの残存
- 空パス扱い揺れ

## テスト観点
- `/index.html`
- `//index.html`
- `/../secret`

## 受入チェックリスト
- [ ] 正常パス結合
- [ ] 不正パス拒否
- [ ] ログ出力

## 簡易コード例
```cpp
bool safeJoin(const std::string &root, const std::string &req, std::string &out) {
	std::string p = root + req; // 後で正規化
	if (p.find("..") != std::string::npos) return false;
	out = p;
	return true;
}
```

