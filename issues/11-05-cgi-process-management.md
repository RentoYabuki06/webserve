---
title: フェーズ11: CGIプロセス管理(タイムアウト/上限)
phase: 11
estimate: 40-60m
status: open
id: F11-05
deps: [F7-03]
---

## 目的
CGIハングやフォーク濫用を防ぐ。

## 手順
1. 実行中CGI数カウンタ/上限
2. 起動時に開始時刻記録
3. 一定秒数超でSIGTERM→SIGKILL
4. waitpid(WNOHANG) でゾンビ回収

## Done
無限ループCGIが強制終了され接続に適切エラー。

## 補足
タイムアウト応答は504。

## 解説 / 背景
リソース隔離と暴走防止で安定稼働。

## リスク / 注意点
- ゾンビ化 (wait忘れ)
- 過剰killで正常短時間CGI影響

## テスト観点
- 無限ループCGI
- 同時数上限

## 受入チェックリスト
- [ ] タイムアウト kill
- [ ] 上限超過拒否
- [ ] ゾンビ0

## 簡易コード例
```cpp
struct CGISlot { pid_t pid; time_t start; };
void reap(std::vector<CGISlot> &slots) {
	for(size_t i=0;i<slots.size();) {
		int st; pid_t r = waitpid(slots[i].pid, &st, WNOHANG);
		if (r==0) ++i; else slots.erase(slots.begin()+i);
	}
}
```

