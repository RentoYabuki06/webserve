---
title: フェーズ8: 接続/読み書きタイムアウト
phase: 8
estimate: 30-45m
status: open
id: F8-03
deps: [F1-04, F2-05]
---

## 目的
ハング防止のためアイドル接続を掃除。

## 手順
1. Connに `last_activity`
2. pollループごとに `now - last_activity`
3. 読み/書き中の個別タイムアウト
4. 408 or サイレントクローズ

## Done
放置接続が一定時間後クローズ。

## 補足
ミリ秒精度不要。秒単位でOK。

## 解説 / 背景
ハング/遅延クライアント掃除のリソース回収仕組み。

## リスク / 注意点
- 過短タイムアウトで正常切断
- タイムスタンプ更新漏れ

## テスト観点
- アイドル接続
- 受信途中停止

## 受入チェックリスト
- [ ] 読みタイムアウト
- [ ] 書きタイムアウト
- [ ] クリーン切断

## 簡易コード例
```cpp
struct ConnTimers { time_t lastRead; time_t lastWrite; };
bool isReadTimeout(const ConnTimers &t, time_t now, int sec) { return now - t.lastRead > sec; }
bool isWriteTimeout(const ConnTimers &t, time_t now, int sec) { return now - t.lastWrite > sec; }
```

