Sonic Refiner v0.9.2 — Build and Package / ビルドと梱包

ENGLISH

Purpose of this formal release:
- Formalize the validated v0.9.2-dev.2 pre-v1.0 polish build.
- Keep the v0.9.2-dev.1 terminology fixes: fixed Depth / Clarity descriptions use +15.0 dB and English adaptive Depth uses Auto Low.
- Update README / COMPONENT_README installation examples to the formal v0.9.2 package.
- Preserve historically correct v0.8.2 “was +16.0 / +14.0 dB” change notes.
- Record the broad pre-v1.0 regression validation completed on v0.9.2-dev.2.
- Keep DSP algorithms and all audio-processing constants unchanged from v0.9.1.
- Keep Auto Headroom constants, ATB logic, 16 built-in preset values, SRP5, preset_version 10, .srpbackup, Reverb, A/B, display language, Monitor behavior and legacy compatibility unchanged.

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
dist\foo_sonic_refiner_v0.9.2.fb2k-component

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
- 実機検証済みv0.9.2-dev.2をv1.0前の仕上げ版v0.9.2として正式版化します。
- v0.9.2-dev.1で確認した用語修正を維持し、固定Depth / Clarity説明を+15.0 dB、Englishの適応型DepthをAuto Lowへ統一します。
- README / COMPONENT_READMEのインストール例を正式v0.9.2パッケージへ更新します。
- v0.8.2の「旧+16.0 / +14.0 dB」など、変更履歴として正しい記述は残します。
- v0.9.2-dev.2で完了した広範囲のv1.0前回帰確認を記録します。
- DSPアルゴリズムおよび音声処理定数はv0.9.1から変更しません。
- Auto Headroom定数、ATB、16内蔵プリセット値、SRP5、preset_version 10、.srpbackup、Reverb、A/B、表示言語、Monitor挙動、旧形式互換は変更しません。

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
dist\foo_sonic_refiner_v0.9.2.fb2k-component

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
