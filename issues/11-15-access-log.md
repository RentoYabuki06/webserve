---
title: フェーズ11: ログ拡張（アクセスログ）
phase: 11
estimate: 20-30m
status: open
id: F11-15
deps: [F1-02, F2-05]
---

## 目的
各リクエスト統計を記録し解析可能にする。

## 手順
1. 開始時刻記録
2. 完了時 ステータス/バイト/処理ms
3. フォーマット: method path status bytes ms

## Done
ログ1行/リクエスト。

## 補足
将来: JSON出力オプション。

## 解説 / 背景
運用時の分析/トラブルシュート基盤。

## リスク / 注意点
- タイム計測精度過剰によるコスト
- ログ肥大 (ローテ未実装)

## テスト観点
- 成功/失敗リクエスト
- 大きなレスポンス

## 受入チェックリスト
- [ ] 1行1リクエスト
- [ ] 必須フィールド出力

## 簡易コード例
```cpp
void accessLog(const Request &req, int status, size_t bytes, long ms) {
	std::cout << req.method << ' ' << req.target << ' ' << status << ' ' << bytes << ' ' << ms << "ms" << std::endl;
}
```

