Sonic Refiner v1.0.1 — Build and Package / ビルドと梱包

ENGLISH

Purpose of this formal build:
- Start directly from formal Sonic Refiner v1.0.0.
- While playback is paused, show an em dash for all four Processing Monitor values and empty all four meter bars, matching the R128 monitor behavior.
- Resume live Monitor values on the next refresh after playback continues.
- Do not reset or change DSP processing, ATB history, Auto Headroom state, Reverb state, presets, or compatibility formats.
- Use the formal package identity v1.0.1.

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
dist\foo_sonic_refiner_v1.0.1.fb2k-component

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
- 正式Sonic Refiner v1.0.0を直接基準に開始します。
- 一時停止中はProcessing Monitorの4項目を「—」表示、4本のメーターバーを空表示とし、R128モニターの動作と揃えます。
- 再生再開後は次回更新からMonitorのライブ値表示へ戻します。
- DSP音声処理、ATB履歴、Auto Headroom内部状態、Reverb状態、プリセット、互換形式は変更・リセットしません。
- 正式版パッケージ識別をv1.0.1とします。

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
dist\foo_sonic_refiner_v1.0.1.fb2k-component

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
