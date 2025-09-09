---
title: フェーズ6: 構造体設計（Config/Server/Location）
phase: 6
estimate: 30-40m
status: open
id: F6-01
deps: [F1-01]
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

## 解説 / 背景
設定ロードの内部モデルを早期確立しパーサ/適用ロジックの接点を用意。

## リスク / 注意点
- デフォルト値未設定
- 循環参照構造

## テスト観点
- 空構造体インスタンス化
- デフォルト初期値

## 受入チェックリスト
- [ ] 構造体定義
- [ ] ビルド成功
- [ ] デフォルト初期化

## 簡易コード例
```cpp
struct LocationConf {
	std::string path;
	std::string root;
	std::vector<std::string> methods;
	bool autoindex;
	LocationConf(): autoindex(false) {}
};
struct ServerConf {
	std::vector<int> listens;
	std::string server_name;
	std::vector<LocationConf> locations;
};
```

