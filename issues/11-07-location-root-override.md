---
title: フェーズ11: location root 上書き & 継承
phase: 11
estimate: 30-40m
status: open
---

## 目的
location毎に別rootを利用可能にする。

## 手順
1. locationに root をオプションで保持
2. 解決時: location root 優先, 無ければ server root
3. 連結時の // 除去

## Done
異なるlocationで別ディレクトリ配信。

## 補足
root未指定は継承動作テスト。
