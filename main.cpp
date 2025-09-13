/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:05:03 by yabukirento       #+#    #+#             */
/*   Updated: 2025/09/13 21:04:28 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Log.hpp"
#include <cstring>       // std::memset, std::strerror
#include <sys/types.h>   // socket, bind, listen 用
#include <sys/socket.h>  // socket, setsockopt, bind, listen
#include <netinet/in.h>  // sockaddr_in, htons, htonl, INADDR_ANY
#include <arpa/inet.h>   // htons, htonl
#include <unistd.h>      // close
#include <fcntl.h>       // fcntl, O_NONBLOCK, FD_CLOEXEC
#include <cerrno>        // errno
#include <poll.h>        // poll, struct pollfd
#include <vector>        // std::vector
#include <map>        // std::map
#include <csignal>       // std::signal, sig_atomic_t

// 個々のクライアントの接続状態を管理する構造体
struct Conn {
	std::string in;     // 受信バッファ
	std::string out;    // 送信バッファ
	bool closed;        // 切断フラグ
	Conn(): in(), out(), closed(false) {}
};

// 各fdとConn構造体を紐づけておくmapコンテナ（static:ファイル内のみのグローバル変数）
static std::map<int, Conn> g_conns;

// Ctrl+C/SIGTERM で終了するためのフラグ
static volatile sig_atomic_t g_stop = 0;
static void onSignal(int) { g_stop = 1; }

// ポート番号を受け取り、待受用ソケットを作って返す関数
static int create_listen_socket(in_port_t port) {
	// IPv4（AF_INET）、TCP（SOCK_STREAM）のソケットを生成。
	int fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		Log::error(std::string("socket failed: ") + std::strerror(errno));
		return -1;
	}
	// アドレス再利用
	int yes = 1;
	if (::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
		Log::error(std::string("setsockopt(SO_REUSEADDR) failed: ") + std::strerror(errno));
		::close(fd);
		return -1;
	}
	// 非ブロッキングモードon
	int flags = ::fcntl(fd, F_GETFL, 0);
	if (flags == -1 || ::fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) { // 既存フラグを消さずにO_NONBLOCKを追加
		Log::error(std::string("fcntl(O_NONBLOCK) failed: ") + std::strerror(errno));
		::close(fd);
		return -1;
	}
	// 子プロセスにfdを渡さない（exec安全化）
	int fdflags = ::fcntl(fd, F_GETFD);
	if (fdflags != -1) {
		if (::fcntl(fd, F_SETFD, fdflags | FD_CLOEXEC) == -1) {
			Log::error(std::string("fcntl(FD_CLOEXEC) failed: ") + std::strerror(errno));
			::close(fd);
			return -1;
		}
	}
	// bind
	struct sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;                // IPv4 用
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // 0.0.0.0（すべてのNICで待ち受ける）
	addr.sin_port = htons(port);              // 指定ポート

	if (::bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		Log::error(std::string("bind failed: ") + std::strerror(errno));
		::close(fd);
		return -1;
	}
	// listen
	if (::listen(fd, SOMAXCONN) == -1) {
		Log::error(std::string("listen failed: ") + std::strerror(errno));
		::close(fd);
		return -1;
	}
	return fd;
}

// fdを閉じて後片付けする関数
static void cleanup_fd(int fd, std::vector<struct pollfd> &pfds, size_t i) {
	::close(fd);
	g_conns.erase(fd);      // map構造体から該当fdを削除
	pfds[i] = pfds.back();  // 削除したいpfds[i]の位置に末尾要素を上書き
	pfds.pop_back();        // その後に末尾要素を削除することで実質pfds[i]を削除
}

// 非ブロッキング＆子プロセスにfdが漏れない設定
static bool set_nonblock_cloexec(int fd) {
	// 非ブロッキング設定
	int fl = ::fcntl(fd, F_GETFL, 0);
	if (fl == -1 || ::fcntl(fd, F_SETFL, fl | O_NONBLOCK) == -1) return false;
	// 子プロセスにfdが漏れない設計（fork→exec時に自動でfdを閉じる）
	int fdfl = ::fcntl(fd, F_GETFD);
	if (fdfl == -1 || ::fcntl(fd, F_SETFD, fdfl | FD_CLOEXEC) == -1) return false;
	return true;
}

// accept受領処理
static void handleAccept(int listen_fd, std::vector<struct pollfd> &pfds) {
	while (true) {
		int cfd = ::accept(listen_fd, 0, 0);
		if (cfd < 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK) break;
			Log::error("accept failed");
			break;
		}
		if (!set_nonblock_cloexec(cfd)) {
			::close(cfd);
			continue;
		}
		struct pollfd p;
		p.fd = cfd;
		p.events = POLLIN;
		p.revents = 0;
		pfds.push_back(p);
		g_conns[cfd] = Conn();
		Log::info("accepted connection");
	}
}

// pollイベントループ
static void eventLoop(int listen_fd, std::vector<struct pollfd> &pfds) {
    while (!g_stop) {
        // イベント発生したfdの数を返す. 1000msイベントが発生しない場合は0を返す.
        int n = ::poll(pfds.empty() ? nullptr : pfds.data(), pfds.size(), 1000);
        // エラーとタイムアウトの処理
        if (n < 0) {
            if (errno == EINTR) {           // シグナル割り込み
                if (g_stop) break;          // 終了要求なら抜ける
                continue;                   // それ以外は続行
            }
            Log::error("poll error");
            break;
        }
        if (n == 0) continue;
        // 各イベントの処理
        for (size_t i = 0; i < pfds.size() && n; ) {
            // pdfs配列の各要素のreventsメンバーでイベント発生の有無を判断. 未発生時は0,発生時は1.
            struct pollfd &p = pfds[i];
            if (p.revents == 0) {
                ++i;
                continue;
            }
            // イベント処理判定
            short re = p.revents;
            p.revents = 0;
            --n;
            // エラー/切断検知
            if (re & (POLLERR | POLLHUP | POLLNVAL)) {
                cleanup_fd(p.fd, pfds, i);
                continue;
            }
            // accept処理
            if (p.fd == listen_fd) {
                if (re & POLLIN) handleAccept(listen_fd, pfds);
                ++i;
                continue;
            }
            Conn &c = g_conns[p.fd];
			
			// 読み取り
			if (re & POLLIN) {
				while (true) {
					char buf[4096];
					ssize_t r = ::recv(p.fd, buf, sizeof(buf), 0);
					if (r > 0) {
						c.in.append(buf, static_cast<size_t>(r));
						c.out.append(buf, static_cast<size_t>(r));
					} else if (r == 0) {
						c.closed = true;
						break;
					} else {
						if (errno == EAGAIN || errno == EWOULDBLOCK) break;
						c.closed = true;
						break;
					}
				}
			}
			// 書き込み（部分送信に対応）
			if ((re & POLLOUT) && !c.out.empty()) {
				while (true) {
					ssize_t w = ::send(p.fd, c.out.data(), c.out.size(), MSG_NOSIGNAL);
					if (w > 0) {
						c.out.erase(0, static_cast<size_t>(w));
					} else if (w < 0) {
						if (errno == EAGAIN || errno == EWOULDBLOCK) break;
						c.closed = true;
						break;
					}
				}
			}

			// POLLOUTの動的切り替え
			if (!c.closed) {
				if (c.out.empty())
					p.events &= static_cast<short>(~POLLOUT);
				else
					p.events |= POLLOUT;
			}
			// クリーンアップ設定
			if (c.closed && c.out.empty()) {
				cleanup_fd(p.fd, pfds, i);
				continue;
			}
			++i;
		}
	}
}

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    // シグナルハンドラ登録（Ctrl+C / kill で終了）
    std::signal(SIGINT, onSignal);
    std::signal(SIGTERM, onSignal);

    Log::info("Server Starting ...");

	const in_port_t port = 8080;
	int listen_fd = create_listen_socket(port);
	if (listen_fd < 0) {
		Log::info("Server Finishing ...");
		return 1;
	}
	Log::info("Listening on 0.0.0.0:8080 (non-blocking)");

	std::vector<struct pollfd> pfds;
	struct pollfd pfd;
	pfd.fd = listen_fd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	pfds.push_back(pfd);

	eventLoop(listen_fd, pfds);
	
	::close(listen_fd);
	Log::info("Server Finishing ...");
	return 0;
}