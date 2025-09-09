---
title: フェーズ7: CGIヘッダの取り込み
phase: 7
estimate: 30-45m
status: open
id: F7-04
deps: [F7-03, F7-02]
---

## 目的
CGI出力の `Status`, `Content-Type` などをHTTPレスポンスに反映。

## 手順
1. CGI出力を `\r\n\r\n` まで分離
2. 行単位解析
3. `Status: 302 Found` → status_code
4. 残りをヘッダに追加

## Done
`Content-Type:text/html` が反映。

## 補足
未指定は200 & default text/html。

## 解説 / 背景
CGI出力をHTTPに橋渡し。Status 行解釈が正確性鍵。

## リスク / 注意点
- ヘッダ終端検出ミス
- Status 不正書式

## テスト観点
- `Status: 302 Found`
- Content-Type 指定/未指定

## 受入チェックリスト
- [ ] Status 反映
- [ ] Content-Type 反映
- [ ] デフォルト200動作

## 簡易コード例
```cpp
struct CGIResult { int status; std::map<std::string,std::string> hdrs; std::string body; };
bool parseCGIResponse(const std::string &raw, CGIResult &r) {
	size_t p = raw.find("\r\n\r\n"); if (p==std::string::npos) return false;
	std::istringstream iss(raw.substr(0,p+2)); std::string line;
	r.status = 200;
	while (std::getline(iss,line) && line != "\r") {
		if (!line.empty() && line[line.size()-1]=='\r') line.erase(line.size()-1);
		size_t c=line.find(':'); if (c==std::string::npos) continue;
		std::string k=line.substr(0,c); std::string v=line.substr(c+1); while(!v.empty()&&v[0]==' ') v.erase(0,1);
		if (k=="Status") r.status = std::atoi(v.c_str()); else r.hdrs[k]=v;
	}
	r.body = raw.substr(p+4);
	return true;
}
```

