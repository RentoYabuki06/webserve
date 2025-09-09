---
title: フェーズ6: index と autoindex（簡易）
phase: 6
estimate: 40-60m
status: open
id: F6-07
deps: [F3-01, F6-03]
---

## 目的
ディレクトリアクセスで index があれば返却、無ければ autoindex。

## 手順
1. パスがディレクトリか判定
2. indexファイル存在チェック
3. 無ければ `readdir` で簡易HTML生成

## Done
`/dir/` で一覧表示。

## 補足
セキュリティ: 親ディレクトリリンク除外。

## 解説 / 背景
ディレクトリ閲覧を可能にしデプロイ確認・デバッグを容易に。

## リスク / 注意点
- N+1 I/O (大規模) は許容範囲
- HTML エスケープ不足

## テスト観点
- index有無
- 空ディレクトリ

## 受入チェックリスト
- [ ] index 優先
- [ ] autoindex 生成
- [ ] 親リンク不在

## 簡易コード例
```cpp
std::string generateListing(const std::string &dir) {
	DIR *d = opendir(dir.c_str()); if(!d) return "";
	std::ostringstream html; html << "<html><body>";
	struct dirent *e; while ((e=readdir(d))) {
		if (std::string(e->d_name) == "." || std::string(e->d_name)=="..") continue;
		html << "<a href='" << e->d_name << "'>" << e->d_name << "</a><br/>";
	}
	closedir(d); html<<"</body></html>"; return html.str();
}
```

