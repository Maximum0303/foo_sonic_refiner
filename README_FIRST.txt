Sonic Refiner v0.8.1 — Build and Package / ビルドと梱包

ENGLISH

Purpose of this release:
- User-facing documentation and in-component guidance refresh only.
- Adds Natural -18 as the recommended R128 starting point in Help / Glossary / Important Notes.
- Refreshes QUICK_START.md and README_FIRST.txt for the current v0.8.x feature set.
- No DSP algorithm, Reverb tuning, built-in preset value, SRP5, preset_version 10, or compatibility change from v0.8.0.

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
dist\foo_sonic_refiner_v0.8.1.fb2k-component

Checksum:
dist\SHA256SUMS.txt

Manual build:
1. Open foo_sonic_refiner.sln in Visual Studio 2022.
2. Select Release and x64.
3. Run Build -> Rebuild Solution.

Current persistence / compatibility:
- User presets: SRP5
- DSP presets: preset_version 10
- SRP1-SRP4 remain readable
- DSP preset versions 1-9 remain readable
- Legacy .srpbackup remains restorable
- Older formats load Reverb = 0

------------------------------------------------------------

日本語

この正式版の目的：
- ユーザー向け文書とコンポーネント内説明だけを更新します。
- Help／用語集／注意事項へ、R128「ナチュラル -18」を基本推奨として追記します。
- QUICK_START.md／README_FIRST.txtを現行v0.8.x仕様へ更新します。
- v0.8.0からDSPアルゴリズム、Reverb調整値、内蔵プリセット値、SRP5、preset_version 10、互換動作は変更しません。

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
dist\foo_sonic_refiner_v0.8.1.fb2k-component

チェックサム:
dist\SHA256SUMS.txt

■ 手動ビルド
1. foo_sonic_refiner.slnをVisual Studio 2022で開きます。
2. 構成をRelease、プラットフォームをx64にします。
3. ビルド→ソリューションのリビルドを実行します。

■ 現行の保存形式・互換性
- 任意プリセット：SRP5
- DSP preset：preset_version 10
- SRP1～SRP4を引き続き読込可能
- DSP preset version 1～9を引き続き読込可能
- 旧.srpbackupを引き続き復元可能
- 旧形式読込時のReverbは0
