---
title: フェーズ6: トークナイザ（空白/波括弧/セミコロン）
phase: 6
estimate: 40-60m
status: open
id: F6-02
deps: [F6-01]
---

## 目的
`server { listen 8080; }` をトークン列に分解。

## 手順
1. 文字走査で空白スキップ
2. `{`, `}`, `;` は単独トークン
3. それ以外は連続英数字/記号まとめる
4. 行番号記録

## Done
単体テストで期待トークン確認。

## 補足
コメント `#` 対応は後回し。

## 解説 / 背景
正確な字句解析はエラーメッセージ品質向上に直結。

## リスク / 注意点
- 波括弧ネスト数カウント漏れ
- 末尾セミコロン忘れ検出失敗

## テスト観点
- 単純serverブロック
- 余分空白
- 不正文字

## 受入チェックリスト
- [ ] トークン列期待通り
- [ ] 行番号記録
- [ ] 不正文字でエラー

## 簡易コード例
```cpp
struct Token { std::string text; size_t line; };
std::vector<Token> tokenize(std::istream &in) {
	std::vector<Token> ts; std::string line; size_t ln=0;
	while (std::getline(in,line)) {
		++ln; std::string cur;
		for (size_t i=0;i<line.size();++i) {
			char c=line[i];
			if (std::isspace(c)) { if(!cur.empty()){ ts.push_back(Token()); ts.back().text=cur; ts.back().line=ln; cur.clear(); } }
			else if (c=='{'||c=='}'||c==';') { if(!cur.empty()){ ts.push_back(Token()); ts.back().text=cur; ts.back().line=ln; cur.clear(); } ts.push_back(Token()); ts.back().text=std::string(1,c); ts.back().line=ln; }
			else cur += c;
		}
		if(!cur.empty()){ ts.push_back(Token()); ts.back().text=cur; ts.back().line=ln; }
	}
	return ts;
}
```

