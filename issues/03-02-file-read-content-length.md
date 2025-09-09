---
title: フェーズ3: ファイル読み込みとContent-Length
phase: 3
estimate: 30-45m
status: open
id: F3-02
deps: [F3-01, F2-05]
---

## 目的
静的ファイルを読み込みボディ化し `Content-Length` 設定。

## 手順
1. `stat` で存在/権限チェック
2. `open` + `read` (小サイズ前提で一括)
3. バイナリ安全: `std::vector<char>`
4. レスポンス生成（後のMIMEは別Issue）

## Done
実ファイルの内容が返る。

## 補足
巨大ファイル分割送信は後で最適化。

## 解説 / 背景
静的配信の基本経路確立。後でMIME/キャッシュ処理追加が容易。

## リスク / 注意点
- 読み失敗時のエラーレスポンス未送信
- バイナリ扱いで文字列誤用

## テスト観点
- 小さいテキスト
- バイナリ( PNG )
- 存在しないファイル

## 受入チェックリスト
- [ ] Content-Length 正
- [ ] 読みエラー処理
- [ ] バイナリ破損なし

## 簡易コード例
```cpp
bool readFile(const std::string &path, std::string &data) {
	std::ifstream ifs(path.c_str(), std::ios::in | std::ios::binary); if(!ifs) return false;
	std::ostringstream oss; oss << ifs.rdbuf(); data = oss.str(); return true;
}
```

