---
title: フェーズ2: 送信バッファ & 送信完了管理
phase: 2
estimate: 30-45m
status: open
id: F2-05
deps: [F2-04]
---

## 目的
`send` の部分書きに対応し全量送信完了で接続を維持またはクローズ。

## 手順
1. Connに `write_buf`, `write_offset`
2. `POLLOUT` 発火で `send`(残量)
3. EAGAINで一時停止
4. 全送信でバッファクリア → 今回はクローズ(暫定)

## Done
大きめ（数KB）データでも正しく完了まで送る。

## 補足
後でKeep-Alive判定追加し再利用。

## 解説 / 背景
非同期送信成立のコア。部分書き対応で大きな応答にも耐性。

## リスク / 注意点
- EAGAIN 無限ループ
- 送信完了後バッファ未解放
- write_offset オーバーフロー

## テスト観点
- 大きめ(>8KB) ボディ
- 途中切断時クリーンアップ
- 連続送信

## 受入チェックリスト
- [ ] 部分書きハンドリング
- [ ] 全送信後リセット
- [ ] エラー時安全終了

## 簡易コード例
```cpp
bool flushSend(int fd, std::string &out, size_t &off, bool &done) {
	while (off < out.size()) {
		ssize_t n = ::send(fd, out.data()+off, out.size()-off, 0);
		if (n > 0) off += n; else if (n<0 && (errno==EAGAIN||errno==EWOULDBLOCK)) return true; else return false;
	}
	if (off == out.size()) { out.clear(); off = 0; done = true; }
	return true;
}
```

