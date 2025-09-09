---
title: フェーズ4: Content-Length受信（ヘッダ）
phase: 4
estimate: 30-40m
status: open
id: F4-01
deps: [F2-03, F2-05]
---

## 目的
`Content-Length` 値を取得し固定長ボディ受信状態管理。

## 手順
1. ヘッダmapから `content-length`
2. 数値パースと上限チェック(暫定 1MB など)
3. 状態を `READING_BODY` に遷移
4. 既読バッファから不足分読み込む

## Done
既知サイズボディを完全に受信し次の処理に進む。

## 補足
後で chunked 優先処理を追加。

## 解説 / 背景
固定長ボディ処理の基盤。後続のアップロード/CGIの正確な受信に必要。

## リスク / 注意点
- 数値オーバーフロー
- 巨大値でメモリアロケーション過大

## テスト観点
- 正常 small body
- 大きな値 (閾値+1)
- 不正数字 (文字混入)

## 受入チェックリスト
- [ ] 数値パース
- [ ] 上限判定
- [ ] 状態遷移

## 簡易コード例
```cpp
bool parseContentLength(const std::map<std::string,std::string> &h, size_t &len) {
	std::map<std::string,std::string>::const_iterator it = h.find("content-length");
	if (it == h.end()) return false;
	std::istringstream iss(it->second);
	unsigned long v; if (!(iss >> v)) return false;
	len = v; return true;
}
```

