---
title: フェーズ6: 最小パーサ（再帰下降）
phase: 6
estimate: 40-60m
status: open
---

## 目的
`server` ブロックと内部ディレクティブを構造体へ構築。

## 手順
1. grammar: config -> server_block*
2. server_block -> 'server' '{' directive* '}'
3. directive -> key value ';'
4. エラー時: 行番号付き例外

## Done
サンプル設定を読み込める。

## 補足
locationは後のIssueで拡張。
