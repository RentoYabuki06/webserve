---
title: フェーズ11: location root 上書き & 継承
phase: 11
estimate: 30-40m
status: open
id: F11-07
deps: [F6-03]
---

## 目的
location毎に別rootを利用可能にする。

## 手順
1. locationに root をオプションで保持
2. 解決時: location root 優先, 無ければ server root
3. 連結時の // 除去

## Done
異なるlocationで別ディレクトリ配信。

## 補足
root未指定は継承動作テスト。

## 解説 / 背景
柔軟なディレクトリ配置を許容し仮想ホスト構成を簡潔化。

## リスク / 注意点
- 二重スラッシュ
- 継承漏れ

## テスト観点
- 上書き root
- 継承 root

## 受入チェックリスト
- [ ] 上書き有効
- [ ] 継承正しい

## 簡易コード例
```cpp
std::string resolveRoot(const ServerConf &srv, const LocationConf *loc) {
	if (loc && !loc->root.empty()) return loc->root;
	return srv.locations.size()? srv.locations[0].root : std::string("."); // 仮仕様
}
```

