---
title: フェーズ9: ブラウザ/curl/ab での確認
phase: 9
estimate: 30-45m
status: open
id: F9-02
deps: [F2-05, F3-02, F4-03, F5-02, F7-04, F8-02]
---

## 目的
基本動作とKeep-Aliveテスト。

## 手順
1. シナリオ表作成
2. curl でGET/POST/DELETE
3. ab や wrk で簡易負荷
4. 結果記録

## Done
期待レスポンス差異なし。

## 補足
スループット計測は参考値。

## 解説 / 背景
統合検証で全経路の整合を一次確認。

## リスク / 注意点
- 手動手順の属人化
- 比較ログ未保存

## テスト観点
- Keep-Alive 確認
- POST/DELETE/CGI

## 受入チェックリスト
- [ ] シナリオ表作成
- [ ] 期待一致ログ
- [ ] 差異0件または理由記録

## 簡易コード例
```bash
# sample curl comparison (手動スクリプト化の雛形)
curl -s -D headers.mine http://127.0.0.1:8080/ > body.mine
curl -s -D headers.nginx http://127.0.0.1:8081/ > body.nginx
diff -u headers.mine headers.nginx || true
```

