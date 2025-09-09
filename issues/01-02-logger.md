---
title: フェーズ1: ロガー（簡易）
phase: 1
estimate: 20-30m
status: open
id: F1-02
deps: [F1-01]
---

## 目的
進捗とエラーを統一フォーマットで標準出力 / 標準エラーに出す `Log` ユーティリティを実装。

## 手順
1. `Log` クラスに静的関数 `info`, `warn`, `error`
2. それぞれプレフィクス `[INFO]`, `[WARN]`, `[ERROR]`
3. 時刻（後回し可）or 簡単なカウンタ
4. `error` は `std::cerr`、他は `std::cout`

## Done
主要イベント（起動、listen開始など）でログ出力される。

## 補足
将来: ANSIカラー, レベルフィルタ。

## 解説 / 背景
初期段階で統一ログIFを持つとデバッグ出力の書き換えコストを削減。後からファイル出力や色付け拡張がしやすい。

## リスク / 注意点
- 例外投げないこと（ログで落ちない）
- マルチスレッド前提なし（本プロジェクトは単スレ）
- 出力flush忘れで即時表示されない

## テスト観点
- `Log::info("msg")` で `[INFO] msg`
- stderr と stdout の振り分け
- 空文字・長文・改行含むメッセージ

## 受入チェックリスト
- [ ] 3レベル呼び出し動作
- [ ] stderr / stdout 分離
- [ ] 依存含めビルド通過
- [ ] 主要イベントで呼ばれている

## 簡易コード例
```cpp
// include/Logger.hpp
#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <iostream>
#include <string>
class Log {
public:
	static void info(const std::string &m)  { std::cout  << "[INFO] "  << m << std::endl; }
	static void warn(const std::string &m)  { std::cout  << "[WARN] "  << m << std::endl; }
	static void error(const std::string &m) { std::cerr << "[ERROR] " << m << std::endl; }
};
#endif

// 使用例
// Log::info("server starting...");
```

