---
title: フェーズ4: ボディ保存（単純アップロード）
phase: 4
estimate: 30-45m
status: open
---

## 目的
受信ボディを `./uploads/` に安全な一時ファイル名で保存。

## 手順
1. ディレクトリ存在確認 or 作成
2. ファイル名: 時刻+乱数 (衝突回避)
3. `open(O_CREAT|O_EXCL)` で書込
4. 書込後 close

## Done
`curl -X POST --data-binary @file` で保存確認。

## 補足
後でmultipart対応は別範囲。
