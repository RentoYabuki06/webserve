---
title: フェーズ8: chunked デコーダ（受信）
phase: 8
estimate: 40-60m
status: open
id: F8-01
deps: [F2-05]
---

## 目的
`Transfer-Encoding: chunked` の本文を復元。

## 手順
1. 状態機械: SIZE_LINE -> DATA -> CRLF -> (repeat)
2. サイズは16進数パース
3. 0サイズで終了 -> 終端

## Done
chunked POST が素体ボディに復元。

## 補足
拡張パラメータ無視。

## 解説 / 背景
streaming POST 受信の基盤。サイズ不明を段階再構築。

## リスク / 注意点
- 16進サイズパース失敗
- 最終チャンク 0 処理漏れ

## テスト観点
- 複数チャンク
- 最終0チャンク
- 不正サイズ文字

## 受入チェックリスト
- [ ] サイズ毎正常
- [ ] 終端検出
- [ ] エラー処理

## 簡易コード例
```cpp
enum ChunkState { CH_SIZE, CH_DATA, CH_CRLF, CH_END };
struct ChunkDecoder { ChunkState st; size_t remain; std::string out; ChunkDecoder():st(CH_SIZE),remain(0){} };
bool feedChunk(ChunkDecoder &d, std::string &buf) {
	while (true) {
		if (d.st==CH_SIZE) {
			size_t pos = buf.find("\r\n"); if (pos==std::string::npos) return true;
			std::istringstream iss(buf.substr(0,pos)); iss >> std::hex >> d.remain; buf.erase(0,pos+2);
			if (d.remain==0) { d.st=CH_END; return true; }
			d.st=CH_DATA;
		} else if (d.st==CH_DATA) {
			if (buf.size() < d.remain) return true;
			d.out.append(buf,0,d.remain); buf.erase(0,d.remain); d.st=CH_CRLF;
		} else if (d.st==CH_CRLF) {
			if (buf.size()<2) return true; buf.erase(0,2); d.st=CH_SIZE;
		} else if (d.st==CH_END) { return true; }
	}
}
```

