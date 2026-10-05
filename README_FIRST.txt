Sonic Refiner v0.9.1 — Build and Package / ビルドと梱包

ENGLISH

Purpose of this release:
- Add How to read the monitor... / モニターの見方... to the formal v0.9.0 Processing Monitor.
- Explain Auto Low, Auto High, Auto Headroom, Level Match, bar ranges and display states.
- Keep the monitor width and meter-bar width aligned with R128; compact row label: AutoHeadroom / 自動HR.
- Add MONITOR_GUIDE.md.
- Keep the v0.9.0 monitor telemetry, persistence and audio behavior unchanged.
- Keep DSP algorithms, Auto Headroom constants, ATB logic, 16 built-in preset values, SRP5, preset_version 10, .srpbackup, Reverb, A/B, display language and legacy compatibility unchanged.

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
dist\foo_sonic_refiner_v0.9.1.fb2k-component

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
- 正式v0.9.0の補正モニターに「モニターの見方... / How to read the monitor...」を追加します。
- 低域補正、高域補正、自動ヘッドルーム、レベル一致、バー、状態表示を説明します。
- R128とモニター横幅・バー幅を揃えたまま、行ラベルのみ「自動HR / AutoHeadroom」に短縮します。
- MONITOR_GUIDE.mdを追加します。
- v0.9.0のMonitorテレメトリ、保存動作、音声挙動は変更しません。
- DSPアルゴリズム、Auto Headroom定数、ATB、16内蔵プリセット値、SRP5、preset_version 10、.srpbackup、Reverb、A/B、表示言語、旧形式互換は変更しません。

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
dist\foo_sonic_refiner_v0.9.1.fb2k-component

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
