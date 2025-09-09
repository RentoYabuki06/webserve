---
title: フェーズ2: ヘッダのパース（最小）
phase: 2
estimate: 30-40m
status: open
id: F2-03
deps: [F2-01]
---

## 目的
`Host`, `Connection` のみ最小実装しキーを小文字化して map に保存。

## 手順
1. リクエストライン以降を行分割
2. `:` で前後 trim
3. key を小文字化
4. map.emplace(重複は上書き可)

## Done
`headers["host"]` に値が入る。

## 補足
将来: Folded header/複数値対応。

## 解説 / 背景
最小ヘッダで Host の存在確認を可能にし仮想ホストや keep-alive 判断準備を整える。

## リスク / 注意点
- 末尾空白/前後空白トリム漏れ
- 重複キー扱い統一されない
- 巨大ヘッダでメモリ肥大

## テスト観点
- Host/Connection 混在順序違い
- 値前後空白
- 重複Host最後優先

## 受入チェックリスト
- [ ] Host取得
- [ ] 小文字正規化
- [ ] 余分空白除去

## 簡易コード例
```cpp
static std::string lower(const std::string &s){ std::string r=s; for(size_t i=0;i<r.size();++i) r[i]=std::tolower(r[i]); return r; }
void parseHeaders(const std::string &raw, std::map<std::string,std::string> &hdrs){
	std::istringstream iss(raw); std::string line;
	while (std::getline(iss, line) && line != "\r") {
		if (!line.empty() && line[line.size()-1]=='\r') line.erase(line.size()-1);
		size_t p = line.find(':'); if (p==std::string::npos) continue;
		std::string k=line.substr(0,p); std::string v=line.substr(p+1);
		while(!v.empty() && (v[0]==' '||v[0]=='\t')) v.erase(0,1);
		hdrs[lower(k)] = v;
	}
}
```

