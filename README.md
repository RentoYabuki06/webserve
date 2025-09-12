# webserve C++ Project

## 共通開発ルール
- branch戦略：[Github Flow](https://qiita.com/trsn_si/items/cfecbf7dff20c64628ea)
  - mainブランチは本番用
  - devブランチを開発用の主軸ブランチとして、そこからfeatureブランチを切って開発を行う
  - featureブランチは1つのissueに対して1つ作成し、完了したらdevブランチにマージする
    - commitメッセージにどのissueに対応しているかを明記する（ex. feat:XX, close #1）
- commitメッセージ例
  - feat: 新機能追加
  - fix: バグ修正
  - docs: ドキュメントのみの変更
  - style: フォーマットの変更、セミコロンの追加などコードの意味に影響しない変更
  - refactor: リファクタリング
  - test: テストコード、テストデータの追加や変更
  - chore: ビルドプロセスや補助ツール、ライブラリの変更などその他の変更
- PRルール
  - 1PRにつき1issueに対応する
  - レビューアを必ず2人以上つける（Copilot + RentoYabuki06）
  - 自己レビューを必ず行う
  - WIP（Work In Progress）の段階ではレビューアをつけない
  - レビューアからApproveが出たらマージする
  - マージは基本的にdevブランチに対して行う（mainは触らない！）
  - CI（ビルド/テスト）が通らないとマージしない（できないように設定済）
- コード規約
  - confilctを避けるため、42ヘッダーは使用しない（normないのでヘッダーをつける必要なし）
  - C++のコーディング規約は[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)に準拠する
  - class名はUpperCamelCase、メソッド名はlowerCamelCaseで、ファイル名とclass名は一対一対応させる

## ディレクトリ構成（最終形の目安）
チーム開発を前提とした責務分割。ヘッダは `includes/`、実装は `srcs/` に配置します。

```
/
  Makefile
  README.md
  .github/workflows/
    ci.yml                 # CI（ビルド/テスト）
  doc/                    # 設計やAPI凍結資料
  issues/                 # 開発タスクの仕様書（履歴）

  conf/
    default.conf          # サンプル設定
    mime.types            # MIMEマッピング

  public/                 # 静的ファイル配信ルート
    index.html
    uploads/              # アップロード保存先

  error_pages/            # カスタムエラーページ
    404.html 403.html 5xx.html

  cgi-bin/                # CGIサンプルスクリプト
    echo.py env.php

  includes/               # ヘッダ群
    core/
      Server.hpp Connection.hpp Router.hpp Buffer.hpp FileReader.hpp ErrorPage.hpp Timer.hpp
    net/
      ListeningSocket.hpp Poller.hpp SocketUtil.hpp
    http/
      Request.hpp Response.hpp Parser.hpp Headers.hpp ChunkedDecoder.hpp Status.hpp ReasonPhrases.hpp MimeTypes.hpp
    config/
      Config.hpp Tokenizer.hpp Parser.hpp Validator.hpp
    cgi/
      CgiDispatcher.hpp CgiEnv.hpp CgiProcess.hpp CgiHeaders.hpp
    utils/
      Log.hpp Fs.hpp String.hpp Path.hpp

  srcs/                   # 実装（.cpp）
    main.cpp
    core/   ...
    net/    ...
    http/   ...
    config/ ...
    cgi/    ...
    utils/  ...

  tests/
    unit/                 # 単体テスト
    e2e/                  # エンドツーエンドテスト
    fixtures/             # テスト用データ/設定/CGI
    run_unit_tests.sh
    run_e2e_tests.sh

  scripts/                # 開発補助スクリプト（任意）
    dev-run.sh valgrind.sh bench.sh compare-nginx.sh
```

