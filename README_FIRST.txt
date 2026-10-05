Sonic Refiner v0.9.0 — Build and Package / ビルドと梱包

ENGLISH

Purpose of this release:
- Add an independent compact Sonic Refiner Processing Monitor.
- Show real-time Auto Low, Auto High, Auto Headroom attenuation and Level Match attenuation.
- Refresh the monitor UI every 100 ms without adding UI work to the audio processing thread.
- Add Active / Analyzing / Waiting / Paused / Disabled states.
- Remember monitor open/closed state, position, and optional Always on Top state.
- Open the monitor directly from the Playback menu.
- Keep the v0.8.4 DSP algorithms, 16 built-in preset values, SRP5, preset_version 10, .srpbackup, display-language behavior, and legacy compatibility unchanged.

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
dist\foo_sonic_refiner_v0.9.0.fb2k-component

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
- 通常の設定画面とは独立した小型のSonic Refiner補正モニターを追加します。
- 低域補正／高域補正／自動ヘッドルーム減衰／レベル一致減衰をリアルタイム表示します。
- 表示更新は100 ms間隔とし、音声処理スレッドへUI処理を持ち込みません。
- 動作中／解析中／待機中／一時停止中／無効の状態を表示します。
- 開閉状態、ウィンドウ位置、常に手前に表示の設定を記憶します。
- Playbackメニューから補正モニターを直接開けるようにします。
- v0.8.4のDSPアルゴリズム、16内蔵プリセット値、SRP5、preset_version 10、.srpbackup、表示言語、旧形式互換は変更しません。

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
dist\foo_sonic_refiner_v0.9.0.fb2k-component

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
