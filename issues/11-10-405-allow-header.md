---
title: フェーズ11: 405 Allow ヘッダ出力
phase: 11
estimate: 15-25m
status: open
id: F11-10
deps: [F6-06]
---

## 目的
405応答に許可メソッド列挙。

## 手順
1. location/server設定から許可集合
2. カンマ区切りでAllow出力

## Done
405レスポンスでAllow確認。

## 補足
大文字メソッド。

## 解説 / 背景
クライアント再試行を導く標準ヘッダ実装。

## リスク / 注意点
- Allow 並び順の揺れ (テスト安定性)

## テスト観点
- 禁止メソッド
- 部分的許可

## 受入チェックリスト
- [ ] Allow 出力
- [ ] 405 ステータス

## 簡易コード例
```cpp
std::string buildAllow(const std::vector<std::string> &meths) {
	std::string r; for(size_t i=0;i<meths.size();++i){ if(i) r+=", "; r+=meths[i]; }
	return r;
}
```

