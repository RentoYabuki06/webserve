---
title: フェーズ11: DELETE エラー詳細マッピング
phase: 11
estimate: 15-25m
status: open
---

## 目的
unlink失敗時の errno をHTTPステータスへ適切変換。

## 手順
1. ENOENT→404
2. EACCES/EPERM→403
3. EISDIR→403
4. その他→500

## Done
テストで各ケース期待通り。

## 補足
ログで errno とファイルパス。
