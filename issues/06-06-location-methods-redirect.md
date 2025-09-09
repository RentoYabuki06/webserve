---
title: フェーズ6: locationのメソッド制限/リダイレクト
phase: 6
estimate: 40-60m
status: open
id: F6-06
deps: [F6-03]
---

## 目的
`allow_methods` と `return 301 URL` でメソッド制限 & リダイレクト。

## 手順
1. 最長一致location探索
2. メソッド未許可→405 + Allowヘッダ
3. return 指定で即 301 Location

## Done
禁止メソッドで405、301が機能。

## 補足
後で 302/307 等拡張。

## 解説 / 背景
柔軟なルーティング制御の土台。メソッド制限でセキュリティ境界強化。

## リスク / 注意点
- 最長一致ロジックバグ
- Allow ヘッダ未生成

## テスト観点
- 許可/禁止メソッド
- リダイレクト 301

## 受入チェックリスト
- [ ] 405 + Allow
- [ ] 301 動作
- [ ] 最長一致確認

## 簡易コード例
```cpp
LocationConf* longestMatch(ServerConf &s, const std::string &uri) {
	LocationConf *best = 0; size_t bestLen = 0;
	for (size_t i=0;i<s.locations.size();++i) {
		const std::string &p = s.locations[i].path;
		if (uri.find(p)==0 && p.size() > bestLen) { bestLen = p.size(); best = &s.locations[i]; }
	}
	return best;
}
```

