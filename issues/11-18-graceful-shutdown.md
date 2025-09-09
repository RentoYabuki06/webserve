---
title: フェーズ11: シグナル優雅終了 (SIGINT/SIGTERM)
phase: 11
estimate: 20-30m
status: open
id: F11-18
deps: [F1-04, F7-03]
---

## 目的
安全に終了しリソースリーク防止。

## 手順
1. シグナルハンドラでフラグ
2. ループ脱出→全FD/子プロセスクリーンアップ

## Done
Ctrl+Cでメモリ/FDリークなし。

## 補足
複数回SIGINTで強制終了。

## 解説 / 背景
運用停止時の安全リリースとデータ一貫性。

## リスク / 注意点
- 二度押しで中途半端解放
- 子プロセス残存

## テスト観点
- SIGINT 一回/二回
- CGI 実行中停止

## 受入チェックリスト
- [ ] 全FD閉鎖
- [ ] CGI回収

## 簡易コード例
```cpp
volatile sig_atomic_t g_stop=0; extern std::vector<int> g_listens;
extern std::map<int, Conn> g_conns;
void onSigInt(int){ g_stop=1; }
void gracefulStop(){
	for(size_t i=0;i<g_listens.size();++i) ::close(g_listens[i]);
	for(std::map<int,Conn>::iterator it=g_conns.begin(); it!=g_conns.end(); ++it) ::close(it->first);
}
```

