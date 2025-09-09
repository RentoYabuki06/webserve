---
title: フェーズ6: 最小パーサ（再帰下降）
phase: 6
estimate: 40-60m
status: open
id: F6-03
deps: [F6-02]
---

## 目的
`server` ブロックと内部ディレクティブを構造体へ構築。

## 手順
1. grammar: config -> server_block*
2. server_block -> 'server' '{' directive* '}'
3. directive -> key value ';'
4. エラー時: 行番号付き例外

## Done
サンプル設定を読み込める。

## 補足
locationは後のIssueで拡張。

## 解説 / 背景
構文木生成基盤。拡張しやすい再帰下降方針を固定化。

## リスク / 注意点
- エラー位置情報欠落
- 無限ループ (インデックス更新漏れ)

## テスト観点
- 正常設定
- 構文エラー位置

## 受入チェックリスト
- [ ] 正常解析
- [ ] 異常で行番号エラー
- [ ] メモリリーク無し

## 簡易コード例
```cpp
// 擬似: server { listen 8080; }
bool parseServer(const std::vector<Token> &t, size_t &i, ServerConf &out) {
	if (t[i].text != "server") return false; ++i;
	if (t[i].text != "{") return false; ++i;
	while (i < t.size() && t[i].text != "}") {
		if (t[i].text == "listen") { ++i; int p = std::atoi(t[i].text.c_str()); ++i; if (t[i].text != ";") return false; ++i; out.listens.push_back(p); }
		else return false; // 簡易
	}
	if (i==t.size()||t[i].text!="}") return false; ++i; return true;
}
```

