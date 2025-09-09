---
title: フェーズ7: 環境変数と引数の整備
phase: 7
estimate: 40-60m
status: open
id: F7-02
deps: [F7-01]
---

## 目的
CGIへ必要最低限の環境変数をセット。

## 手順
1. REQUEST_METHOD, CONTENT_LENGTH, QUERY_STRING
2. SCRIPT_FILENAME, PATH_INFO
3. SERVER_PROTOCOL, REMOTE_ADDR
4. map→`char* envp[]` 生成

## Done
CGI側で環境取得可。

## 補足
後で CONTENT_TYPE 等追加。

## 解説 / 背景
CGI 正常実行に最低限必要な環境を整備。

## リスク / 注意点
- PATH_INFO 分離ミス
- QUERY_STRING デコード未対応

## テスト観点
- echo CGI で環境表示
- GET/POST 差異

## 受入チェックリスト
- [ ] 必須変数設定
- [ ] 空値取り扱い

## 簡易コード例
```cpp
std::vector<std::string> buildCGIEnv(const Request &req, const std::string &script) {
	std::vector<std::string> env;
	env.push_back("REQUEST_METHOD=" + req.method);
	env.push_back("SCRIPT_FILENAME=" + script);
	env.push_back("SERVER_PROTOCOL=HTTP/1.1");
	env.push_back("GATEWAY_INTERFACE=CGI/1.1");
	env.push_back(std::string("CONTENT_LENGTH=") /* + body length later */);
	return env;
}
```

