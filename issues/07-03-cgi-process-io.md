---
title: フェーズ7: fork/execve + pipe + poll
phase: 7
estimate: 40-60m
status: open
---

## 目的
親→子(STDIN), 子→親(STDOUT) を非ブロッキング pipe で接続し poll 監視。

## 手順
1. 2本pipe作成
2. fork → 子で dup2 & execve
3. 親: 書込/読込FD非ブロッキング
4. pollで書き切り/読み切り

## Done
短いCGIが応答返す。

## 補足
タイムアウトは後で統合。
