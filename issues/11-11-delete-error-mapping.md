---
title: フェーズ11: DELETE エラー詳細マッピング
phase: 11
estimate: 15-25m
status: open
id: F11-11
deps: [F5-02]
---

## 目的
unlink失敗時の errno をHTTPステータスへ適切変換。

## 手順
1. ENOENT→404
2. EACCES/EPERM→403
3. EISDIR→403
4. その他→500

## Done
テストで各ケース期待通り。

## 補足
ログで errno とファイルパス。

## 解説 / 背景
精密なエラー返却でデバッグ効率向上。

## リスク / 注意点
- errno 上書き前読取

## テスト観点
- ENOENT/EACCES/EISDIR

## 受入チェックリスト
- [ ] 各errno変換
- [ ] ログ記録

## 簡易コード例
```cpp
int mapDeleteErrno(int e) {
	if (e==ENOENT) return 404; if (e==EACCES) return 403; if (e==EISDIR) return 403; return 500;
}
```

