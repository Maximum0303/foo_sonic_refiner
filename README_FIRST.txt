Sonic Refiner v0.1.0 — ビルドと梱包

■ 対象環境
- foobar2000 SDK 2025-03-07
- Visual Studio 2022
- Windows x64
- C++17
- Release / x64
- WTL

■ 配置例
このフォルダーを次の位置へ配置します。

F:\foobar2000-dev\SDK-2025-03-07\foobar2000\foo_sonic_refiner

WTLは次のファイルが存在するように配置します。

F:\foobar2000-dev\WTL\Include\atlapp.h

別ドライブを使う場合も、SDKフォルダーとWTLフォルダーの相対構成を
同じにしてください。

■ 自動ビルドと梱包
次のファイルをダブルクリックします。

build_and_package.cmd

日本語名の「ビルドと梱包.cmd」からも同じ処理を実行できます。

■ 出力
DLL:
x64\Release\foo_sonic_refiner.dll

配布パッケージ:
dist\foo_sonic_refiner_v0.1.0.fb2k-component

チェックサム:
dist\SHA256SUMS.txt

■ 手動ビルド
1. foo_sonic_refiner.slnをVisual Studio 2022で開きます。
2. 構成を「Release」、プラットフォームを「x64」にします。
3. 「ビルド」→「ソリューションのリビルド」を実行します。

■ インストール
生成されたfoo_sonic_refiner_v0.1.0.fb2k-componentをダブルクリックし、
foobar2000へインストールします。

詳細はREADME.mdとQUICK_START.mdを参照してください。
