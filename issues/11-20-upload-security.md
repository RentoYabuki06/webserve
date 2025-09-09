---
title: フェーズ11: アップロード/実行権限セキュリティ強化
phase: 11
estimate: 30-40m
status: open
id: F11-20
deps: [F4-02]
---

## 目的
アップロードを利用した意図しないCGI実行防止。

## 手順
1. 保存時モード 0644 固定
2. CGI対象拡張子ホワイトリスト
3. 実行ビット自動除去

## Done
不正アップロードが実行されない。

## 補足
拡張: ウイルススキャン連携は範囲外。

## 解説 / 背景
アップロード機能悪用リスク低減。

## リスク / 注意点
- 実行ビット除去忘れ
- CGI対象拡張子網羅不足

## テスト観点
- 実行権限付与ファイル
- 危険拡張子

## 受入チェックリスト
- [ ] 実行権限除去
- [ ] ホワイトリスト適用

## 簡易コード例
```cpp
bool sanitizeUpload(const std::string &path) {
	struct stat st; if (stat(path.c_str(), &st)!=0) return false;
	chmod(path.c_str(), st.st_mode & 0644); // 実行権限除去
	return true;
}
```

