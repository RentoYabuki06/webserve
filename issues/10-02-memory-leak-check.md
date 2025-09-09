---
title: フェーズ10: メモリリークチェック
phase: 10
estimate: 40-60m
status: open
id: F10-02
deps: [F10-01]
---

## 目的
終了時リークゼロ。

## 手順
1. macOS: `Leaks` か `Instruments`
2. Linux互換環境でValgrind実行
3. 主要経路テストスクリプト
4. 修正サイクル

## Done
主要経路でリークなし確認。

## 補足
長時間接続テストは任意。

## 解説 / 背景
リーク除去はリソース枯渇防止 & 信頼性証跡。

## リスク / 注意点
- false positive (lib内部)
- 一時バッファ誤報

## テスト観点
- Valgrind 主要シナリオ
- 繰返し100リクエスト

## 受入チェックリスト
- [ ] definitely lost 0
- [ ] indirect lost 0
- [ ] leak log保存

## 簡易コード例
```bash
valgrind --leak-check=full --show-leak-kinds=all ./webserv 2>&1 | tee valgrind.log
```

