---
title: フェーズ1: ソケット作成・非ブロッキング化
phase: 1
estimate: 30-45m
status: open
id: F1-03
deps: [F1-01, F1-02]
---

## 目的
`socket/bind/listen` でポート(例:8080)を開き、`fcntl(O_NONBLOCK)` を設定。

## 手順
1. `AF_INET`, `SOCK_STREAM`
2. `setsockopt(SO_REUSEADDR)`
3. `bind(0.0.0.0:8080)`
4. `listen(backlog=128)`
5. `fcntl(fd, F_SETFL, O_NONBLOCK)`
6. 成功ログ: `Listening on :8080`

## Done
起動時にログが表示され、プロセスが落ちない。

## 補足
後で複数listen対応予定。エラー時は `Log::error`。

## 解説 / 背景
最初のネットワークI/O起点。ここでノンブロッキング化を確実にしておくと以降のpoll駆動モデルに一貫性。

## リスク / 注意点
- `SO_REUSEADDR` 忘れによる再起動バインド失敗
- fcntl の戻り値未チェック
- IPv6 対応は範囲外（明示）

## テスト観点
- `netstat` / `lsof` でポートLISTEN確認
- 連続再起動で bind 失敗しない
- 失敗パス（ポート占有）でエラーログ

## 受入チェックリスト
- [ ] LISTEN ソケット生成
- [ ] ノンブロッキング化
- [ ] エラーにログ
- [ ] プロセス続行

## 簡易コード例
```cpp
int createListenSocket(int port) {
	int fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) { Log::error("socket fail"); return -1; }
	int on = 1; ::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	sockaddr_in addr; std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET; addr.sin_addr.s_addr = htonl(INADDR_ANY); addr.sin_port = htons(port);
	if (::bind(fd, (sockaddr*)&addr, sizeof(addr)) < 0) { Log::error("bind fail"); ::close(fd); return -1; }
	if (::listen(fd, 128) < 0) { Log::error("listen fail"); ::close(fd); return -1; }
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	return fd;
}
```

