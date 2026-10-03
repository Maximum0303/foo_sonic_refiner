Sonic Refiner v0.8.2 — Build and Package / ビルドと梱包

ENGLISH

Purpose of this development build:
- Unify fixed Depth / Clarity maximum gain at +15.0 dB.
- Raise ATB Auto Low / Auto High absolute maximum from +10.0 dB to +15.0 dB.
- Keep ATB analysis / decision logic and boost-only behavior unchanged.
- Keep SRP5, preset_version 10, .srpbackup, built-in preset parameter values, Reverb, Width, Ambience, Auto Headroom, and legacy compatibility unchanged.

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
dist\foo_sonic_refiner_v0.8.2.fb2k-component

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

この開発版の目的：
- 固定Depth／Clarityの最大ゲインを+15.0 dBへ統一します。
- ATB Auto Low／Auto Highの絶対上限を+10.0 dBから+15.0 dBへ引き上げます。
- ATBの解析／判定ロジックとboost-only動作は変更しません。
- SRP5、preset_version 10、.srpbackup、内蔵プリセット設定値、Reverb、Width、Ambience、Auto Headroom、旧形式互換は変更しません。

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
dist\foo_sonic_refiner_v0.8.2.fb2k-component

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
