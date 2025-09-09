---
title: フェーズ4: 201 Created とロケーション
phase: 4
estimate: 20-30m
status: open
---

## 目的
アップロード成功で 201 と `Location` ヘッダ返却。

## 手順
1. 保存パスをURL化（簡易 `/uploads/<name>`）
2. レスポンス: `HTTP/1.1 201 Created` + Location

## Done
`curl -i` で 201 / Location 表示。

## 補足
後で重複時409など検討。
