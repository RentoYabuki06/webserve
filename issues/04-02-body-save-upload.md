---
title: フェーズ4: ボディ保存（単純アップロード）
phase: 4
estimate: 30-45m
status: open
id: F4-02
deps: [F4-01]
---

## 目的
受信ボディを `./uploads/` に安全な一時ファイル名で保存。

## 手順
1. ディレクトリ存在確認 or 作成
2. ファイル名: 時刻+乱数 (衝突回避)
3. `open(O_CREAT|O_EXCL)` で書込
4. 書込後 close

## Done
`curl -X POST --data-binary @file` で保存確認。

## 補足
後でmultipart対応は別範囲。

## 解説 / 背景
最小アップロードでPOST機能の価値可視化。保存基盤は後のセキュリティ強化の対象。

## リスク / 注意点
- 競合ファイル名衝突
- ディレクトリ権限不足
- ディスクフル未処理

## テスト観点
- 小/中サイズファイル
- 連続アップロード
- 保存後読み返し一致

## 受入チェックリスト
- [ ] ファイル生成
- [ ] 内容一致
- [ ] 権限想定(0644)

## 簡易コード例
```cpp
bool saveBody(const std::string &dir, const std::string &name, const std::string &body) {
	std::string path = dir + "/" + name; std::ofstream ofs(path.c_str(), std::ios::out|std::ios::binary);
	if (!ofs) return false; ofs.write(body.data(), body.size()); return ofs.good();
}
```

