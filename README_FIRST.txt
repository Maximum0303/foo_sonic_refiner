Sonic Refiner v1.1.0 — Build and Package / ビルドと梱包

ENGLISH

Purpose of this development build:
- Start directly from the formal Sonic Refiner v1.0.1 final source.
- Add Minimize with foobar2000 to the Processing Monitor right-click menu.
- Default ON preserves the existing behavior: minimizing foobar2000 also hides the monitor.
- OFF keeps the monitor visible while the foobar2000 main window is minimized.
- Save the setting across restarts and keep it independent from Always on Top.
- Do not change DSP processing, presets, runtime correction logic or compatibility formats.
- Use the formal package identity v1.1.0.

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
dist\foo_sonic_refiner_v1.1.0.fb2k-component

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
- 正式Sonic Refiner v1.0.1最終ソースを直接基準に開始します。
- 補正モニター右クリックに「foobar2000と一緒に最小化」を追加します。
- 初期値オンでは従来どおりfoobar2000本体を最小化するとモニターも画面から消えます。
- オフではfoobar2000本体を最小化してもモニターを画面に残します。
- 設定は再起動後も保存し、「常に手前に表示」と独立して動作させます。
- DSP音声処理、プリセット、ランタイム補正ロジック、互換形式は変更しません。
- 正式版パッケージ識別をv1.1.0とします。

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
dist\foo_sonic_refiner_v1.1.0.fb2k-component

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
