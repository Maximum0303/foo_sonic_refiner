Sonic Refiner v1.0.0 — Build and Package / ビルドと梱包

ENGLISH

Purpose of this formal build:
- Formalize the validated v0.9.2 / v1.0.0-dev.1 behavior as Sonic Refiner v1.0.0.
- Do not change DSP algorithms, coefficients, Auto Headroom constants, ATB logic, Reverb tuning, A/B, Processing Monitor behavior, or the 16 built-in preset values.
- Keep SRP5, preset_version 10, .srpbackup, display-language behavior and all legacy readers unchanged.
- Confirm Help / Glossary / Important Notes as the v1.0 baseline terminology.
- Use the formal package identity v1.0.0.

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
dist\foo_sonic_refiner_v1.0.0.fb2k-component

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
- 検証済みv0.9.2／v1.0.0-dev.1の動作をSonic Refiner v1.0.0として正式版化します。
- DSPアルゴリズム、係数、Auto Headroom定数、ATB、Reverb調整、A/B、Processing Monitor動作、16内蔵プリセット値は変更しません。
- SRP5、preset_version 10、.srpbackup、表示言語、旧形式readerを維持します。
- Help／Glossary／Important Notesをv1.0の正式基準用語として確定します。
- 正式パッケージ識別をv1.0.0とします。

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
dist\foo_sonic_refiner_v1.0.0.fb2k-component

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
