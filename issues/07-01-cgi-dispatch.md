---
title: フェーズ7: CGI起動の配線（拡張子マップ）
phase: 7
estimate: 30-45m
status: open
id: F7-01
deps: [F6-06, F3-01]
---

## 目的
拡張子に応じて CGI 実行を選択。

## 手順
1. locationに `cgi_pass` 風設定 (拡張子->実行ファイル)
2. 静的配信前に拡張子判定
3. CGIフローへ分岐

## Done
対象パスでCGI起動ログ。

## 補足
セキュリティ: 実行権限チェック。

## 解説 / 背景
静的/動的コンテンツ分岐ポイント。拡張子マップで低コスト判定。

## リスク / 注意点
- 任意拡張子実行
- 実行ファイルパス外部入力依存

## テスト観点
- .php/.py ファイル
- 非対象拡張子

## 受入チェックリスト
- [ ] 対象のみCGI
- [ ] 静的へフォールバック

## 簡易コード例
```cpp
bool isCGI(const std::string &path) {
	size_t p = path.rfind('.'); if (p==std::string::npos) return false;
	std::string ext = path.substr(p+1);
	return (ext=="py" || ext=="php");
}
```

