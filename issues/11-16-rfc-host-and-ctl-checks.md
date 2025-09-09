---
title: フェーズ11: RFC細部: Host必須/制御文字検証
phase: 11
estimate: 20-30m
status: open
---

## 目的
HTTP/1.1 要件満たし不正ヘッダ拒否。

## 手順
1. Host未提供→400
2. 制御文字(0x00-0x1F,0x7F) 検知→400
3. 複数Host → 400

## Done
異常ケースが拒否。

## 補足
HTTP/1.0 は例外ハンドリング。
