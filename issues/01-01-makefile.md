---
title: フェーズ1: Makefileの雛形
phase: 1
estimate: 20-30m
status: open
---

## 目的
`c++ -Wall -Wextra -Werror -std=c++98` でビルドできる最小Makefileを用意し、`make && ./webserv` が起動する。

## 手順
1. 変数 `NAME = webserv`
2. 基本ルール: `all clean fclean re`
3. 依存関係: パターンルールで `.cpp -> .o`
4. `CXXFLAGS` に `-Wall -Wextra -Werror -std=c++98`
5. 将来ソース追加に備えて `SRCS` 変数化

## Done (受入基準)
`make` 成功しバイナリ `webserv` が生成、実行で（まだ何もしなくても）即終了 or 待機する。エラーなし。

## 補足 / メモ
後で自動依存生成（`-MMD -MP`）を追加予定。
