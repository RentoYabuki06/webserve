---
title: フェーズ5: ステータスの分岐 (DELETE)
phase: 5
estimate: 20-30m
status: open
id: F5-02
deps: [F5-01]
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

## 解説 / 背景
DELETE の明確なステータス返却はクライアント再試行判定に重要。

## リスク / 注意点
- errno マッピング漏れ
- 204 の Content-Length 誤送信

## テスト観点
- 存在/不存在/権限
- 既に削除後再DELETE

## 受入チェックリスト
- [ ] 成功で204
- [ ] ENOENT→404
- [ ] EACCES→403

## 簡易コード例
```cpp
int deleteFile(const std::string &path) {
	if (::unlink(path.c_str()) == 0) return 204;
	if (errno == ENOENT) return 404;
	if (errno == EACCES) return 403;
	return 500;
}
```

