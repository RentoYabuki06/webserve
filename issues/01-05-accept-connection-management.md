---
title: フェーズ1: accept() と接続FD管理
phase: 1
estimate: 30-45m
status: open
id: F1-05
deps: [F1-04]
---

## 目的
新規接続を非ブロッキングで受理し、`pollfds` に R/W 同時監視で追加。切断時にクリーンアップ。

## 手順
1. listen FD にイベントあったら `accept()` ループ
2. 新FDへ `O_NONBLOCK`
3. `pollfds` に `POLLIN | POLLOUT` (後で書き条件制御) 追加
4. 接続構造体 `Conn`（read_buf, write_buf, stateなど）map管理
5. 切断/エラーで削除

## Done
接続/切断がログされ FDリークなし。

## 補足
後で送信準備まで `POLLOUT` 抑制する最適化計画。

## 解説 / 背景
接続ライフサイクル管理の最初の実装。正しいFDクリーンアップはリーク防止の基礎。

## リスク / 注意点
- accept ループで EAGAIN 未処理→不要ループ
- クローズ時に pollfds と Conn map の不整合
- POLLOUT 常時登録で不要wake

## テスト観点
- 大量短時間接続(benchmarkツール) 後の FD 数
- リモート切断 (クライアント側 close)
- サーバ側強制 close

## 受入チェックリスト
- [ ] 新規接続ログ
- [ ] 切断でFD削除
- [ ] メモリリークなし (簡易チェック)

## 簡易コード例
```cpp
struct Conn { std::string in; std::string out; bool closed; };
std::map<int, Conn> g_conns;

void handleAccept(int listenFd, std::vector<pollfd> &pfds) {
	for (;;) {
		int cfd = ::accept(listenFd, 0, 0);
		if (cfd < 0) { if (errno==EAGAIN||errno==EWOULDBLOCK) break; Log::error("accept"); break; }
		int fl = fcntl(cfd, F_GETFL, 0); fcntl(cfd, F_SETFL, fl|O_NONBLOCK);
		pollfd p; p.fd=cfd; p.events=POLLIN; p.revents=0; pfds.push_back(p);
		g_conns[cfd] = Conn();
		Log::info("accepted fd=" + toString(cfd));
	}
}
```

