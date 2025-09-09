---
title: フェーズ11: pollfd 管理最適化
phase: 11
estimate: 20-30m
status: open
id: F11-13
deps: [F1-04, F1-05]
---

## 目的
多数接続時の削除コストを削減。

## 手順
1. fd→index の map
2. 削除: 末尾とスワップ
3. インデックス更新

## Done
大量接続で性能安定。

## 補足
統計ログ追加可。

## 解説 / 背景
大量接続時のスケール性確保。

## リスク / 注意点
- マッピング更新忘れ
- 重複FD登録

## テスト観点
- 100+接続追加/削除

## 受入チェックリスト
- [ ] O(1) 削除
- [ ] インデックス整合

## 簡易コード例
```cpp
void removePoll(std::vector<pollfd> &pfds, size_t idx) {
	pfds[idx] = pfds.back(); pfds.pop_back();
}
```

