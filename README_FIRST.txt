Sonic Refiner v0.7.0 — Build and Package / ビルドと梱包

ENGLISH

Required environment:
- foobar2000 SDK 2025-03-07
- Visual Studio 2022
- Windows x64
- C++17
- Release / x64
- WTL

Place this folder at:
F:\foobar2000-dev\SDK-2025-03-07\foobar2000\foo_sonic_refiner

Confirm that this WTL file exists:
F:\foobar2000-dev\WTL\Include\atlapp.h

Run:
build_and_package.cmd

The Japanese-named launcher runs the same process:
ビルドと梱包.cmd

Outputs:
DLL:
x64\Release\foo_sonic_refiner.dll

Package:
dist\foo_sonic_refiner_v0.7.0.fb2k-component

Checksum:
dist\SHA256SUMS.txt

v0.7.0 feature:
Adds the read-only Preset Manager foundation: user-preset list, settings preview, current-settings match marker, resizing, Japanese/English, and Light/Dark support.

Manual build:
1. Open foo_sonic_refiner.sln in Visual Studio 2022.
2. Select Release and x64.
3. Run Build -> Rebuild Solution.

This source builds the Sonic Refiner v0.7.0 development package. It is based on the formal v0.6.5 source and adds only the read-only Preset Manager foundation. DSP / ATB processing, SRP4, preset_version 9, .srpbackup, and built-in preset values are unchanged.

------------------------------------------------------------

日本語

■ 対象環境
- foobar2000 SDK 2025-03-07
- Visual Studio 2022
- Windows x64
- C++17
- Release / x64
- WTL

■ 配置先
F:\foobar2000-dev\SDK-2025-03-07\foobar2000\foo_sonic_refiner

■ WTL確認先
F:\foobar2000-dev\WTL\Include\atlapp.h

■ 自動ビルドと梱包
次をダブルクリックします。
build_and_package.cmd

日本語名の次のファイルでも同じ処理を実行できます。
ビルドと梱包.cmd

■ 出力
DLL:
x64\Release\foo_sonic_refiner.dll

配布パッケージ:
dist\foo_sonic_refiner_v0.7.0.fb2k-component

チェックサム:
dist\SHA256SUMS.txt

■ 手動ビルド
1. foo_sonic_refiner.slnをVisual Studio 2022で開きます。
2. 構成をRelease、プラットフォームをx64にします。
3. ビルド→ソリューションのリビルドを実行します。

このソースからSonic Refiner v0.7.0開発版パッケージを作成できます。正式v0.6.5ソースを基準に、読み取り専用Preset Managerの土台だけを追加しています。DSP／ATB処理、SRP4、preset_version 9、.srpbackup、内蔵プリセット値は変更していません。
