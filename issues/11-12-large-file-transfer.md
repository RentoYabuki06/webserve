---
title: フェーズ11: 巨大静的ファイル分割/ゼロコピー
phase: 11
estimate: 40-60m
status: open
id: F11-12
deps: [F3-02]
---

## 目的
大容量ファイル送信でメモリ効率を保つ。

## 手順
1. サイズ閾値(例:1MB)判定
2. 閾値以上: チャンク read+send ループ or sendfile
3. write_buf と併用管理

## Done
10MBファイル送信時の常駐メモリ低い。

## 補足
sendfile非対応環境 fallback。

## 解説 / 背景
大容量配信のスケール特性向上。

## リスク / 注意点
- 部分send エラー処理
- mmap/送信競合

## テスト観点
- 10MB ファイル
- 中断切断

## 受入チェックリスト
- [ ] メモリ常駐小
- [ ] 全送信

## 簡易コード例
```cpp
ssize_t sendChunk(int fd, int fileFd, off_t &offset, size_t chunk) {
	char buf[8192]; if (chunk > sizeof(buf)) chunk = sizeof(buf);
	ssize_t r = pread(fileFd, buf, chunk, offset); if (r <= 0) return r;
	ssize_t w = ::send(fd, buf, r, 0); if (w > 0) offset += w; return w;
}
```

