---
title: フェーズ7: fork/execve + pipe + poll
phase: 7
estimate: 40-60m
status: open
id: F7-03
deps: [F7-01, F1-04]
---

## 目的
親→子(STDIN), 子→親(STDOUT) を非ブロッキング pipe で接続し poll 監視。

## 手順
1. 2本pipe作成
2. fork → 子で dup2 & execve
3. 親: 書込/読込FD非ブロッキング
4. pollで書き切り/読み切り

## Done
短いCGIが応答返す。

## 補足
タイムアウトは後で統合。

## 解説 / 背景
非同期プロセスI/Oの中心。pipe + poll の雛形確立。

## リスク / 注意点
- pipe FD の close 忘れ (デッドロック)
- EAGAIN ループ

## テスト観点
- 標準出力短文
- 標準入力経由エコー

## 受入チェックリスト
- [ ] 双方向通信
- [ ] ノンブロッキング
- [ ] 正常終了 wait

## 簡易コード例
```cpp
pid_t launchCGI(const std::string &path, int &inW, int &outR) {
	int inPipe[2], outPipe[2];
	if (pipe(inPipe)||pipe(outPipe)) return -1;
	pid_t pid = fork();
	if (pid==0) {
		dup2(inPipe[0], 0); dup2(outPipe[1], 1);
		::close(inPipe[1]); ::close(outPipe[0]);
		char *argv[2]; argv[0] = const_cast<char*>(path.c_str()); argv[1]=0;
		execve(path.c_str(), argv, 0);
		_exit(1);
	}
	::close(inPipe[0]); ::close(outPipe[1]);
	inW = inPipe[1]; outR = outPipe[0];
	return pid;
}
```

