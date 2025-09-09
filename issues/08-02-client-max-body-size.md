---
title: フェーズ8: client_max_body_size
phase: 8
estimate: 20-30m
status: open
id: F8-02
deps: [F4-01, F8-01]
---

## 目的
設定値超過ボディを 413 で即時拒否。

## 手順
1. Content-Length 参照
2. chunked は合計復元後判定
3. 超過でレスポンス生成→送信→クローズ

## Done
大きなPOSTが即拒否。

## 補足
設定は server / location 優先順位。

## 解説 / 背景
過大リクエストの早期拒否でリソース保護。

## リスク / 注意点
- chunked 途中判定遅延
- 設定階層優先順位バグ

## テスト観点
- 直前許容サイズ
- 超過即時拒否

## 受入チェックリスト
- [ ] Content-Length 超過拒否
- [ ] chunked 合計超過拒否
- [ ] 正常境界通過

## 簡易コード例
```cpp
bool enforceLimitSize(size_t announced, size_t limit) { return announced <= limit; }
bool enforceAccumLimit(size_t accumulated, size_t limit) { return accumulated <= limit; }
```

