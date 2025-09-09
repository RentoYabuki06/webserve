---
title: フェーズ9: デフォルトエラーページ整備
phase: 9
estimate: 30-45m
status: open
id: F9-01
deps: [F3-04, F5-02, F7-04]
---

## 目的
400/403/404/405/413/500/502/504 など統一HTML。

## 手順
1. テンプレ: `<html><body><h1>{code} {text}</h1></body></html>`
2. コード→理由句のテーブル
3. 500系は同一テンプレ

## Done
全エラー経路で人間可読表示。

## 補足
後で `error_page` 設定による差替え。

## 解説 / 背景
統一テンプレで保守性確保、ユーザ体験改善。

## リスク / 注意点
- コードと文言不一致
- HTML エスケープ不足

## テスト観点
- 400/403/404/405/413/500 生成
- Content-Length 一致

## 受入チェックリスト
- [ ] 主要コードテンプレ
- [ ] 文言表整合
- [ ] 文字化けなし

## 簡易コード例
```cpp
std::string buildErrorBody(int code, const std::string &phrase) {
	std::ostringstream b; b << "<html><body><h1>"<<code<<" "<<phrase<<"</h1></body></html>"; return b.str();
}
```

