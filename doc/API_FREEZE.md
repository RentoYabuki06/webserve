## Minimal API Freeze (Initial E2E /healthz)

目的: /healthz 200 を返す最小サーバを基点に、以後の大幅インターフェース変更を避けつつ 3 分担 (A/B/C) を可能にする。

### 現在実装されている最小構成
- `Server` : ポートで listen, poll, accept, 受信, 単純 GET 判定, 即時レスポンス, close
- `Logger` : `Log::info|warn|error`
- 内部 `Conn` : inバッファのみ

### 今後追加予定層 (責務境界案)
| Layer | 主担当 | 役割 | 公開予定インターフェース (Freeze 対象) |
|-------|--------|------|-------------------------------------------|
| Network (A) | A | poll/接続/タイムアウト/送受信非同期 | `class EventLoop` (後で導入), コールバック: onReadable(fd), onWritable(fd) |
| HTTP/Core (B) | B | Request/Response パース生成, 静的/メソッド | `struct HttpRequest`, `struct HttpResponse`, `int HttpProcessor::handle(int fd, Buffer&)` |
| Config/CGI/VHost (C) | C | 設定ロードと仮想ホスト選択, CGI環境 | `class Config`, `ServerConfig resolve(host,port,uri)` |

### Freeze 指針 (この段階で確定してよいもの)
1. ログ IF: `Log::info|warn|error(const std::string&)`
2. 今後もポーリング駆動 (select へ変更しない)
3. リクエストバッファは文字列 (後でリングバッファに最適化可) だが API は抽象 `Buffer` に差し替え予定 → まだ Freeze しない

### 追加予定の型スケルトン (次ステップで導入)
```cpp
struct HttpRequest {
    std::string method;
    std::string target;
    std::string version; // "HTTP/1.1"
    std::map<std::string,std::string> headers;
    std::string body;
};
struct HttpResponse {
    int status;
    std::map<std::string,std::string> headers;
    std::string body;
};
```

### 3 人分担マッピング
#### A: Network / Event
- Issues: F1-03, F1-04, F1-05, F11-13 (poll最適化), F8-03 (タイムアウト), F11-14 (タイマー), F11-17 (パイプライン), F11-18 (graceful)
- 追加 Deliverables: EventLoop 抽象, Connection state struct 拡張 (write buffer, timers)

#### B: HTTP / 静的 / メソッド
- Issues: F2-01..F2-05, F3-01..F3-04, F4-01..F4-03, F5-01..F5-02, F8-01..F8-02, F9-01, F11-01 (keep-alive), F11-02, F11-03, F11-09, F11-10, F11-11, F11-12 (large file), F11-16, F11-20
- 追加 Deliverables: Request parser, Response builder, StaticFileHandler, BodyLimitChecker

#### C: Config / VHost / CGI
- Issues: F6-01..F6-07, F7-01..F7-04, F11-04..F11-08, F11-06 (error_page), F11-05 (CGI管理), F11-07 (root override), F11-15 (access log format調整?), F11-19 (E2E scripts with config variants)
- 追加 Deliverables: ConfigLoader, VirtualHostResolver, CgiExecutor

### 移行ステップ (ソロ作業者向け)
1. (完了) 最小 /healthz 応答
2. Logger/Server のヘッダに大規模変更が不要かレビュー → Freeze 宣言
3. HTTP層: Request/Response 型導入 (空実装) + Server から分離 (B が後で展開)
4. Config層: 空 `Config` と `ServerConfig` スケルトン (C 着手準備)
5. 分担開始: A は EventLoop 抽象化, B はパーサ, C はトークナイザ開始

### 将来リファクタ計画フック
- Server::handleClient → A/B 境界: 近く `dispatchReadable(fd)` に差し替え予定
- tryParseAndRespond → B へ移行
- buildHealthz → HealthHandler (B)

### テスト基盤最初の1本
```bash
curl -s -o /dev/null -w "health:%{http_code}\n" http://127.0.0.1:8080/healthz
```

### 注意
Freeze 後は public ヘッダの関数シグネチャ変更は PR & 合意必須。内部実装は自由。
