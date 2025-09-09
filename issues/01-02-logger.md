---
title: フェーズ1: ロガー（簡易）
phase: 1
estimate: 20-30m
status: open
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
