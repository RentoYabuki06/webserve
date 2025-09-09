---
title: フェーズ11: CGI環境変数拡充
phase: 11
estimate: 30-45m
status: open
id: F11-04
deps: [F7-02]
---

## 目的
CGI/Phpが期待する標準環境変数を追加。

## 手順
1. SERVER_SOFTWARE, SERVER_NAME, SERVER_PORT
2. GATEWAY_INTERFACE=CGI/1.1
3. SCRIPT_NAME, SCRIPT_FILENAME, PATH_INFO
4. CONTENT_TYPE, QUERY_STRING, REDIRECT_STATUS=200

## Done
phpinfo等で表示される。

## 補足
不足があれば随時追加。

## 解説 / 背景
より複雑なCGI/言語ランタイム互換性強化。

## リスク / 注意点
- REDIRECT_STATUS 忘れ (PHP)
- SCRIPT_NAME/SCRIPT_FILENAME 混同

## テスト観点
- phpinfo / env dumper
- サブディレクトリCGI

## 受入チェックリスト
- [ ] 追加変数出力
- [ ] 値正確

## 簡易コード例
```cpp
void addExtended(std::vector<std::string> &env, const Request &req) {
	env.push_back("QUERY_STRING=" + /* extract */ std::string(""));
	env.push_back("REDIRECT_STATUS=200"); // for php-cgi
}
```

