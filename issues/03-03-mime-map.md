---
title: フェーズ3: MIMEタイプの最小マップ
phase: 3
estimate: 20-30m
status: open
id: F3-03
deps: [F3-02]
---

## 目的
拡張子→`Content-Type` の最小テーブル実装。

## 手順
1. map: .html .css .js .png .jpg
2. デフォルト: `application/octet-stream`
3. 拡張子抽出は最後の '.' 以降

## Done
`curl -I` に適切なType付与。

## 補足
後で `.gif .svg .ico` など拡張。

## 解説 / 背景
ブラウザ適正表示とキャッシュ挙動に必須の基本Content-Type制御。

## リスク / 注意点
- 拡張子なしファイル扱い
- 大文字拡張子未対応

## テスト観点
- .html/.css/.js/.png/.jpg
- 未知拡張子 fallback

## 受入チェックリスト
- [ ] 既知拡張子Type一致
- [ ] 未知→octet-stream

## 簡易コード例
```cpp
std::string mimeType(const std::string &path) {
	size_t p = path.rfind('.'); if (p==std::string::npos) return "application/octet-stream";
	std::string ext = path.substr(p+1);
	if (ext=="html") return "text/html";
	if (ext=="css") return "text/css";
	if (ext=="js") return "application/javascript";
	if (ext=="png") return "image/png";
	if (ext=="jpg"||ext=="jpeg") return "image/jpeg";
	return "application/octet-stream";
}
```

