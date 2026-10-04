Sonic Refiner v0.8.4 — Build and Package / ビルドと梱包

ENGLISH

Purpose of this release:
- Redesign Auto Headroom so brief transients do not cause an abrupt whole-signal gain drop.
- Detect sustained high peaks with a two-stage smoothed peak envelope.
- Apply protection gain with a gentle attack and release instead of instant attenuation.
- Keep the approx. -0.2 dBFS protection reference while leaving final True Peak control to the downstream R128 component.
- Keep ATB, Level-Matched Bypass, Reverb, preset values, SRP5, preset_version 10, .srpbackup, and legacy compatibility unchanged.

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
dist\foo_sonic_refiner_v0.8.4.fb2k-component

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
- 一瞬のピークで全体音量が急に下がらないよう、自動ヘッドルーム保護を見直します。
- 2段階の平滑化ピーク検出で、持続的な高ピークだけを保護対象にします。
- 瞬時減衰ではなく、穏やかなアタック／リリースで保護ゲインを動かします。
- 約-0.2 dBFSの保護基準は維持し、最終True Peak管理は後段R128へ任せます。
- ATB、レベルマッチ・バイパス、Reverb、内蔵プリセット値、SRP5、preset_version 10、.srpbackup、旧形式互換は変更しません。

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
dist\foo_sonic_refiner_v0.8.4.fb2k-component

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
