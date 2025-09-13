/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:05:03 by yabukirento       #+#    #+#             */
/*   Updated: 2025/09/13 16:40:15 by yabukirento      ###   ########.fr       */
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

// pollイベントループ
static void eventLoop(std::vector<struct pollfd> &pfds) {
    while (true) {
        // イベント発生したfdの数を返す. 1000msイベントが発生しない場合は0を返す.
        int n = ::poll(&pfds[0], pfds.size(), 1000);
        // エラーとタイムアウトの処理
        if (n < 0) {
            if (errno == EINTR) continue;   // シグナルによる中断のみループ継続
            Log::error("poll error");
            break;
        }
        if (n == 0) continue;
        for (size_t i = 0; i < pfds.size() && n; ++i) {
            // pdfs配列の各要素のreventsメンバーでイベント発生の有無を判断. 未発生時は0,発生時は1.
            if (pfds[i].revents) {
                --n;
            }
        }
    }
}

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;
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

    eventLoop(pfds);
    
    ::close(listen_fd);
    Log::info("Server Finishing ...");
    return 0;
}