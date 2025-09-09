---
title: フェーズ11: タイマー統合設計
phase: 11
estimate: 30-45m
status: open
id: F11-14
deps: [F8-03]
---

## 目的
接続/CGI/書込み/keep-alive タイムアウトを一元管理。

## 手順
1. 最小期限を計算しpoll timeout短縮
2. 期限超過リスト走査
3. 統計(タイムアウト件数)ログ

## Done
無駄な短周期pollを削減。

## 補足
priority queue 検討可。

## 解説 / 背景
全タイムアウト統合で複雑化抑制。

## リスク / 注意点
- 過去時刻扱い
- 多数タイマーの線形探索コスト

## テスト観点
- 複数種タイムアウト
- 最小期限更新

## 受入チェックリスト
- [ ] 最小期限計算
- [ ] 期限切れ処理

## 簡易コード例
```cpp
struct Timer { time_t at; int id; };
time_t nextTimeout(const std::vector<Timer> &ts, time_t now) {
	time_t best = now + 3600; for(size_t i=0;i<ts.size();++i) if (ts[i].at < best) best = ts[i].at; return best;
}
```

