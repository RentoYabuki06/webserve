---
title: フェーズ1: poll()ループの骨格
phase: 1
estimate: 30-45m
status: open
id: F1-04
deps: [F1-03]
---

## 目的
単一イベントループで `poll()` を呼び続け CPU暴走しない骨格を作る。

## 手順
1. `std::vector<pollfd>` に listen FD を `POLLIN`
2. 無限ループで `poll()`
3. 戻り値 <0 ならエラーログ
4. `timeout` は暫定 1000ms

## Done
ループが安定稼働（アイドル時CPU低負荷）。

## 補足
後でタイムアウト & 接続FD追加予定。

## 解説 / 背景
イベント駆動の中心ループ。ここをシンプルに保つことで後の状態管理追加が容易。

## リスク / 注意点
- タイムアウト値不適切でCPUスピン
- エラー時に致命的終了してしまう
- pollfds 変更時のイテレーション破壊

## テスト観点
- アイドル状態CPU使用率低い
- シグナル(Ctrl+C)で終了可能
- LISTEN fd 以外何もせずに安定

## 受入チェックリスト
- [ ] 無限ループ稼働
- [ ] CPU暴走なし
- [ ] エラー検知時ログ

## 簡易コード例
```cpp
void eventLoop(std::vector<struct pollfd> &pfds) {
	while (true) {
		int n = ::poll(&pfds[0], pfds.size(), 1000);
		if (n < 0) { if (errno == EINTR) continue; Log::error("poll error"); break; }
		if (n == 0) continue; // timeout
		for (size_t i = 0; i < pfds.size() && n; ++i) {
			if (pfds[i].revents) {
				// 後続Issueで分岐
				--n;
			}
		}
	}
}
```

