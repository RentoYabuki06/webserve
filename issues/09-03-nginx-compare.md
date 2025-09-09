---
title: フェーズ9: NGINXとの挙動比較
phase: 9
estimate: 40-60m
status: open
id: F9-03
deps: [F9-02]
---

## 目的
主要ケースでヘッダ/コード差分を確認し整合性向上。

## 手順
1. 同一root/設定をNginxで構築
2. 選定ケース: 200/404/403/405/リダイレクト/CGI
3. `curl -i` 比較
4. 乖離点列挙

## Done
主要ケースが概ね同等。

## 補足
完全一致より合理的差異の把握優先。

## 解説 / 背景
参照実装比較で仕様解釈のズレを早期発見。

## リスク / 注意点
- 時刻/Dateヘッダ比較ノイズ
- Nginx設定差異

## テスト観点
- 200/404/403/リダイレクト/CGI
- ヘッダ差分抽出

## 受入チェックリスト
- [ ] ケース定義
- [ ] 差分一覧
- [ ] 改善計画メモ

## 簡易コード例
```bash
cases=(/ /notfound /forbidden)
for c in "${cases[@]}"; do
	curl -s -o /dev/null -w "%{http_code} %{size_download}\n" http://127.0.0.1:8080$c
done
```

