---
title: フェーズ11: ディレクトリ末尾スラッシュリダイレクト
phase: 11
estimate: 20-30m
status: open
id: F11-09
deps: [F3-01]
---

## 目的
末尾スラッシュ欠如時の相対リンク崩れを防ぐ。

## 手順
1. stat でディレクトリ判定
2. URI末尾に / 無ければ 301 + Location (/付加)

## Done
ブラウザで相対リンク正常化。

## 補足
正規化後の重複//除去。

## 解説 / 背景
SEO / ブラウザ相対リンク安定化。

## リスク / 注意点
- 二重リダイレクト
- 既に末尾 / 付き判定バグ

## テスト観点
- `/dir` → 301
- `/dir/` 維持

## 受入チェックリスト
- [ ] 301 発行
- [ ] Location 正常

## 簡易コード例
```cpp
bool needDirSlashRedirect(const std::string &fsPath, const std::string &uri) {
	struct stat st; if (stat(fsPath.c_str(), &st)==0 && S_ISDIR(st.st_mode)) {
		return uri.empty() || uri[uri.size()-1] != '/';
	}
	return false;
}
```

