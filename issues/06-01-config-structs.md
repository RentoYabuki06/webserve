---
title: フェーズ6: 構造体設計（Config/Server/Location）
phase: 6
estimate: 30-40m
status: open
---

## 目的
設定構造体の最小スケルトンを定義しビルド可能にする。

## 手順
1. `Config { std::vector<Server> servers; }`
2. `Server { std::vector<int> listen; std::string root; ... }`
3. `Location { std::string path; allowed_methods; cgi_pass; }`
4. 空実装でコンパイル通す

## Done
空の構造体を含めてビルド成功。

## 補足
デフォルト値初期化方針決定。
