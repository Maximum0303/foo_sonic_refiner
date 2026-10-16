Sonic Refiner v1.2.0 — Build and Package / ビルドと梱包

ENGLISH

Purpose of this formal release:
- Start directly from the formal Sonic Refiner v1.1.0 final source.
- Add Adaptive Bass Emphasis / 適応型低域強調.
- Add Adaptive Treble Emphasis / 適応型高域強調.
- Increase the built-in preset count from 16 to 18.
- Keep all existing 16 built-in preset values unchanged.
- Do not change ATB algorithms, DSP processing, Monitor behavior or compatibility formats.
- Use formal package identity v1.2.0.

New preset values:
- Adaptive Bass Emphasis: Depth 100 / Clarity 65 / Width 50 / Ambience 40 / Reverb 0
- Adaptive Treble Emphasis: Depth 65 / Clarity 100 / Width 50 / Ambience 40 / Reverb 0
- Common: Master Strength 100 / Output Gain 0.0 dB / Auto Headroom ON / Level-Matched Bypass ON / Sonic Refiner ON / ATB ON

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

Outputs:
DLL:
x64\Release\foo_sonic_refiner.dll

Package:
dist\foo_sonic_refiner_v1.2.0.fb2k-component

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
- 正式Sonic Refiner v1.1.0最終ソースを直接基準に開始します。
- 「適応型低域強調 / Adaptive Bass Emphasis」を追加します。
- 「適応型高域強調 / Adaptive Treble Emphasis」を追加します。
- 内蔵プリセットを16個から18個へ増やします。
- 既存16個の内蔵プリセット値は変更しません。
- ATBアルゴリズム、DSP音声処理、Monitor動作、互換形式は変更しません。
- 正式版パッケージ識別をv1.2.0とします。

追加プリセット値：
- 適応型低域強調：Depth 100 / Clarity 65 / Width 50 / Ambience 40 / Reverb 0
- 適応型高域強調：Depth 65 / Clarity 100 / Width 50 / Ambience 40 / Reverb 0
- 共通：Master Strength 100 / Output Gain 0.0 dB / Auto Headroom ON / Level-Matched Bypass ON / Sonic Refiner ON / ATB ON

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

■ 出力
DLL:
x64\Release\foo_sonic_refiner.dll

配布パッケージ:
dist\foo_sonic_refiner_v1.2.0.fb2k-component

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
