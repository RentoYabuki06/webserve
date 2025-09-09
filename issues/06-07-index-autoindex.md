---
title: フェーズ6: index と autoindex（簡易）
phase: 6
estimate: 40-60m
status: open
---

## 目的
ディレクトリアクセスで index があれば返却、無ければ autoindex。

## 手順
1. パスがディレクトリか判定
2. indexファイル存在チェック
3. 無ければ `readdir` で簡易HTML生成

## Done
`/dir/` で一覧表示。

## 補足
セキュリティ: 親ディレクトリリンク除外。
