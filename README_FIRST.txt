Sonic Refiner v1.2.1 — Build and Package / ビルドと梱包

ENGLISH

Purpose of this development build:
- Start directly from the formal Sonic Refiner v1.2.0 final source.
- Fix Processing Monitor window-position persistence when foobar2000 itself is closed.
- Save the Monitor position immediately when a user finishes moving/resizing it.
- Keep the existing destroy/quit-time saves as fallback paths.
- Do not change DSP algorithms, ATB, presets or compatibility formats.

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

Expected package:
dist\foo_sonic_refiner_v1.2.1.fb2k-component

Test focus:
- Move the Processing Monitor to a new position.
- Leave it open and close foobar2000.
- Restart foobar2000.
- Confirm the Monitor reopens at the exact latest position.

------------------------------------------------------------

日本語

この開発版の目的：
- 正式Sonic Refiner v1.2.0最終ソースを直接基準にします。
- foobar2000本体を終了した際にProcessing Monitorの最終位置が記憶されない場合がある問題を修正します。
- Monitorの移動／サイズ変更操作が終わった時点で位置を即時保存します。
- 既存の破棄時／終了時保存も予備経路として維持します。
- DSPアルゴリズム、ATB、プリセット、互換形式は変更しません。

必要環境：
- foobar2000 SDK 2025-03-07
- Visual Studio 2022
- Windows x64
- C++17
- Release / x64
- WTL

配置先：
F:\foobar2000-dev\SDK-2025-03-07\foobar2000\foo_sonic_refiner

次のファイルが存在することを確認：
F:\foobar2000-dev\WTL\Include\atlapp.h

実行：
build_and_package.cmd

生成予定：
dist\foo_sonic_refiner_v1.2.1.fb2k-component

重点確認：
- Processing Monitorを明確に別の位置へ移動します。
- Monitorを開いたままfoobar2000本体を終了します。
- foobar2000を再起動します。
- Monitorが終了直前の最新位置に復元されることを確認します。
