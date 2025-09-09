---
title: フェーズ11: RFC細部: Host必須/制御文字検証
phase: 11
estimate: 20-30m
status: open
id: F11-16
deps: [F2-03]
---

## 目的
HTTP/1.1 要件満たし不正ヘッダ拒否。

## 手順
1. Host未提供→400
2. 制御文字(0x00-0x1F,0x7F) 検知→400
3. 複数Host → 400

## Done
異常ケースが拒否。

## 補足
HTTP/1.0 は例外ハンドリング。

## 解説 / 背景
RFC整合性で互換性とセキュリティ両立。

## リスク / 注意点
- 制御文字検出範囲ミス
- Host 複数ヘッダ処理

## テスト観点
- Host欠如
- 制御文字含む

## 受入チェックリスト
- [ ] Host必須チェック
- [ ] 制御文字拒否

## 簡易コード例
```cpp
bool hasCtl(const std::string &s) { for(size_t i=0;i<s.size();++i) if ((unsigned char)s[i] < 0x20) return true; return false; }
```

