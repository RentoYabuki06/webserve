---
title: フェーズ6: 複数ポートのlisten生成
phase: 6
estimate: 30-45m
status: open
id: F6-04
deps: [F1-04, F6-03]
---

## 目的
`listen 8080; listen 8081;` を両方ソケット化しpoll登録。

## 手順
1. parserで複数listen値を配列
2. 起動時にループでsocket/bind/listen
3. pollfdsへ全登録

## Done
両ポートで応答あり。

## 補足
既存ポート衝突時のエラー処理要。

## 解説 / 背景
複数仮想ホストやポート比較テストを可能にする基盤。

## リスク / 注意点
- ソケット配列管理でFDリーク
- 片方失敗時のロールバック不備

## テスト観点
- 2ポート Listen
- 片方衝突

## 受入チェックリスト
- [ ] 全ポート成功
- [ ] 失敗時クリーンアップ
- [ ] poll 登録

## 簡易コード例
```cpp
bool openAll(const std::vector<int> &ports, std::vector<int> &fds) {
	for (size_t i=0;i<ports.size();++i) {
		int fd = createListenSocket(ports[i]);
		if (fd<0) { for(size_t j=0;j<fds.size();++j) ::close(fds[j]); fds.clear(); return false; }
		fds.push_back(fd);
	}
	return true;
}
```

