---
title: フェーズ11: パス正規化 & シンボリックリンク対策
phase: 11
estimate: 30-45m
status: open
id: F11-08
deps: [F3-01]
---

## 目的
パスエスケープを防ぎ安全なファイルアクセス保証。

## 手順
1. 入力パスを split → . / .. 処理
2. realpathで最終パス検証 (失敗時403)
3. root prefix一致確認
4. シンボリックリンク方針: 許可 or 禁止（禁止なら判定）

## Done
`../` 攻撃を遮断。

## 補足
realpathコストはキャッシュ検討可。

## 解説 / 背景
ディレクトリトラバーサ攻撃からの防御。

## リスク / 注意点
- シンボリックリンク評価方針齟齬
- 大量パス realpath コスト

## テスト観点
- 正常
- `..` / `.%2e` 変種

## 受入チェックリスト
- [ ] 不正拒否
- [ ] 正常通過

## 簡易コード例
```cpp
std::string normalize(const std::string &p) {
	std::vector<std::string> segs; std::string cur; for(size_t i=0;i<=p.size();++i){
		if (i==p.size()||p[i]=='/') { if(!cur.empty()){ if(cur==".." && !segs.empty()) segs.pop_back(); else if(cur!="." && cur!="..") segs.push_back(cur); cur.clear(); } }
		else cur+=p[i];
	}
	std::string out="/"; for(size_t i=0;i<segs.size();++i){ out+=segs[i]; if(i+1<segs.size()) out+='/'; }
	return out;
}
```

