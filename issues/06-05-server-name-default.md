---
title: フェーズ6: server_nameとデフォルトサーバ
phase: 6
estimate: 30-45m
status: open
id: F6-05
deps: [F6-03, F2-03]
---

## 目的
Hostヘッダで仮想ホスト選択。該当なしは最初のserver。

## 手順
1. Serverに `server_names` vector
2. リクエスト解析時 Host 取得
3. ルックアップ→マッチ or fallback

## Done
異なるHostで別root返す。

## 補足
正規化 (ポート除去) 必要。

## 解説 / 背景
Hostヘッダベース仮想ホスト選択で本格的な振り分け機能を提供。

## リスク / 注意点
- 末尾ドット/大文字扱い
- ポート付きHostの分離

## テスト観点
- Host一致/不一致
- ポート付き `example.com:8080`

## 受入チェックリスト
- [ ] マッチ成功
- [ ] フォールバック動作

## 簡易コード例
```cpp
ServerConf* matchServer(const std::vector<ServerConf*> &servers, const std::string &host) {
	for (size_t i=0;i<servers.size();++i) if (servers[i]->server_name == host) return servers[i];
	return servers.empty()?0:servers[0];
}
```

