---
title: フェーズ1: Makefileの雛形
phase: 1
estimate: 20-30m
status: open
id: F1-01
deps: []
---

## 目的
`c++ -Wall -Wextra -Werror -std=c++98` でビルドできる最小Makefileを用意し、`make && ./webserv` が起動する。

## 手順
1. 変数 `NAME = webserv`
2. 基本ルール: `all clean fclean re`
3. 依存関係: パターンルールで `.cpp -> .o`
4. `CXXFLAGS` に `-Wall -Wextra -Werror -std=c++98`
5. 将来ソース追加に備えて `SRCS` 変数化

## Done (受入基準)
`make` 成功しバイナリ `webserv` が生成、実行で（まだ何もしなくても）即終了 or 待機する。エラーなし。

## 補足 / メモ
後で自動依存生成（`-MMD -MP`）を追加予定。

## 解説 / 背景
最初に高速で完成させることで他タスクのブロッキングを外す基盤。依存生成は後回しでもコンパイル速度への影響は軽微。

## リスク / 注意点
- フラグ漏れ (`-std=c++98`) で後工程レビュー時に差し戻し
- オブジェクト削除忘れで再ビルドされない（パターンルール不備）
- macOS / Linux でコマンド差異が出ないか（`c++` 想定）

## テスト観点
- `make -n` で想定コマンドが出る
- ソース新規追加後 `make` で自動的に再リンク
- `make re` が clean → build の順序で走る

## 受入チェックリスト
- [ ] `make` 成功
- [ ] バイナリ実行可能
- [ ] `make clean` で *.o 消える
- [ ] `make fclean` でバイナリ消える
- [ ] `make re` で再生成
- [ ] Werror で警告0

## 簡易コード例
```Makefile
NAME := webserv
SRCS := main.cpp \
        src/Logger.cpp
OBJS := $(SRCS:.cpp=.o)
CXX  := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98

all: $(NAME)
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
```

