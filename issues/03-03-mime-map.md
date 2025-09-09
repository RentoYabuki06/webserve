---
title: フェーズ3: MIMEタイプの最小マップ
phase: 3
estimate: 20-30m
status: open
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
