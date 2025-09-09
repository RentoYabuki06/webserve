---
title: フェーズ5: 削除対象の安全な解決
phase: 5
estimate: 30-40m
status: open
id: F5-01
deps: [F3-01]
---

## 目的
DELETE 対象パスを正規化しルート外アクセスとディレクトリ削除を拒否。

## 手順
1. パス正規化（`..` 排除）
2. ルート接頭辞一致確認
3. `stat` でディレクトリなら 403

## Done
安全でないパスは 403。

## 補足
シンボリックリンク対策は後検討。

## 解説 / 背景
不正削除を防ぎ安全境界を再確認する処理。

## リスク / 注意点
- 正規化ロジック欠陥
- 競合 (TOCTOU)

## テスト観点
- 既存ファイル
- ディレクトリ指定
- `..` 含む

## 受入チェックリスト
- [ ] 正常ファイル対象化
- [ ] ディレクトリ拒否
- [ ] ルート外拒否

## 簡易コード例
```cpp
bool isSafeDeletable(const std::string &root, const std::string &rel, std::string &abs) {
	if (rel.find("..")!=std::string::npos) return false;
	abs = root + rel;
	struct stat st; if (stat(abs.c_str(), &st) == 0 && S_ISREG(st.st_mode)) return true;
	return false;
}
```

