---
title: フェーズ11: error_page ディレクティブ実装
phase: 11
estimate: 30-45m
status: open
id: F11-06
deps: [F6-03, F9-01]
---

## 目的
特定ステータスにカスタム静的エラーページを返す。

## 手順
1. `error_page 404 /404.html;` 解析
2. マッピング検索→該当ファイル読み込み
3. ファイル無い場合はデフォルトにフォールバック

## Done
404でカスタムHTML。

## 補足
複数コード→1ページ対応は拡張可。

## 解説 / 背景
運用時のブランド/UX 向上。

## リスク / 注意点
- ページ未存在でループ
- 相対パス誤解決

## テスト観点
- 404/500マッピング
- 不存在マッピング

## 受入チェックリスト
- [ ] 指定コード置換
- [ ] フォールバック動作

## 簡易コード例
```cpp
std::map<int,std::string> customErrorPages; // code -> path
std::string pickErrorPage(int code) {
	std::map<int,std::string>::iterator it = customErrorPages.find(code);
	if (it!=customErrorPages.end()) return it->second;
	return ""; // use default
}
```

