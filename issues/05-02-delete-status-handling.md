---
title: フェーズ5: ステータスの分岐 (DELETE)
phase: 5
estimate: 20-30m
status: open
---

## 目的
削除結果に応じて 200/204, 404, 403 を返す。

## 手順
1. `unlink` 戻り値チェック
2. 存在しない: errno=ENOENT → 404
3. 権限: errno=EACCES → 403
4. 成功: body無し 204 or 簡易メッセージ 200 (方針選択)

## Done
`curl -X DELETE` で期待通りのコード。

## 補足
204優先（ボディ不要）。
