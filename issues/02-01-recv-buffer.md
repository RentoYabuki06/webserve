---
title: フェーズ2: 受信バッファ実装（行単位）
phase: 2
estimate: 30-45m
status: open
id: F2-01
deps: [F1-05]
---

## 目的
`recv` 断片を貯め `\r\n\r\n` を検出するヘッダ読み取り状態機械を実装。

## 手順
1. Connに `read_buf` (std::string)
2. pollで `POLLIN` 時 `recv` 反復
3. 0: クライアント切断, <0:EAGAINで停止
4. `read_buf.find("\r\n\r\n")` で判定
5. 見つかったら状態を HEADERS_COMPLETE に遷移

## Done
ヘッダ終端を検出ログ出力。

## 補足
将来: ヘッダサイズ上限で 431 など。

## 解説 / 背景
部分読み取りを抽象化し後続パース段階を単純化。断片化するTCPペイロード吸収が目的。

## リスク / 注意点
- 大量読みで無制限増大（上限未設定）
- CRLF シーケンスの誤判定
- バイナリ混入時の制御文字扱い

## テスト観点
- 分割送信: 1文字ずつ送る
- ヘッダ終端直後にBODY未読の保持
- 0バイト(切断)処理

## 受入チェックリスト
- [ ] CRLFCRLF 検出
- [ ] 部分読み対応
- [ ] 切断処理

## 簡易コード例
```cpp
bool readIntoBuffer(int fd, std::string &buf, bool &closed) {
	char tmp[4096];
	for (;;) {
		ssize_t n = ::recv(fd, tmp, sizeof(tmp), 0);
		if (n > 0) { buf.append(tmp, n); }
		else if (n == 0) { closed = true; break; }
		else { if (errno==EAGAIN||errno==EWOULDBLOCK) break; closed=true; return false; }
	}
	return true;
}
bool hasHeaderEnd(const std::string &b) {
	return b.find("\r\n\r\n") != std::string::npos;
}
```

