# Sonic Refiner v0.4.0 Release Notes

Release date: 2026-08-22

## English

### Added

- Temporary A/B comparison slots for Depth, Clarity, Width, Ambience, and Master Strength.
- Instant A/B listening while keeping Output Gain, Auto Headroom Protection, Level-Matched Bypass, and the component enabled state outside the A/B slots.
- End Comparison restores the complete settings that were active immediately before A/B listening began.
- Direct settings access from **Playback → Sonic Refiner Settings...** without opening DSP Manager.
- Modeless owned direct-settings window: foobar2000 remains usable while the settings window is open.
- Integration with **Preferences → Keyboard Shortcuts**; no default shortcut is assigned.
- Safety checks that refuse direct editing when Sonic Refiner is missing from the active DSP chain or appears more than once.
- Runtime safety detection when the active DSP chain is changed while the direct settings window is open.

### UI fixes during development

- Improved disabled End Comparison readability in dark mode.
- Adjusted A/B and Master/Output/Protection spacing while keeping the 560 × 320 window size.
- Fixed the lower-left border of the Master/Output/Protection group being erased by the extreme-range notice.
- Fixed the Visual Studio C3246 build failure in the new main-menu command registration.

### Compatibility

- DSP processing algorithm and processing order are unchanged from v0.3.0.
- `preset_version 8` remains unchanged.
- User-preset write format remains `SRP3`; `SRP1`, `SRP2`, and `SRP3` remain readable.
- `.srpbackup` format remains unchanged.
- Existing settings and user presets remain compatible.
- A/B slot contents are memory-only and are not stored in DSP presets, user presets, or `.srpbackup` files.
- The settings window remains 560 × 320.
- Japanese/English UI behavior remains compatible with v0.3.0.

## 日本語

### 追加

- Depth、Clarity、Width、Ambience、Master Strengthを一時保存するA/B比較スロットを追加。
- Output Gain、自動ヘッドルーム保護、レベルマッチ・バイパス、本体有効状態をA/B対象外にしたまま即時比較可能。
- 「比較終了」でA/B試聴開始直前の全設定へ復元。
- **Playback → Sonic Refiner の設定...** からDSP Managerを経由せず設定画面を直接起動可能。
- 直接起動画面はモードレスで、開いたままfoobar2000本体を操作可能。
- **Preferences → Keyboard Shortcuts** から任意のショートカットキーを割り当て可能（初期割り当てなし）。
- Sonic RefinerがDSPチェーンにない場合、または複数登録されている場合は、安全のため直接編集を拒否。
- 直接起動画面を開いている途中でDSPチェーンが変更された場合も誤編集を防止。

### 開発中に修正したUI・ビルド項目

- ダークモードで無効状態の「比較終了」が読みにくい問題を修正。
- 560 × 320を維持しながらA/B欄と全体効果・出力・保護欄の余白を調整。
- 強い演出用の注意文がグループ枠の左下線を消していた問題を修正。
- 新しいメインメニューコマンド登録で発生したVisual Studio C3246ビルドエラーを修正。

### 互換性

- DSP処理アルゴリズムと処理順序はv0.3.0から変更なし。
- `preset_version 8`を維持。
- 任意プリセットの書き込み形式は`SRP3`、`SRP1`／`SRP2`／`SRP3`読み込み互換を維持。
- `.srpbackup`形式は変更なし。
- 既存設定・既存任意プリセットの互換性を維持。
- A/B内容はメモリ上だけに保持し、DSP preset・任意プリセット・`.srpbackup`には保存しない。
- 設定画面は560 × 320を維持。
- 日本語／Englishの動作はv0.3.0と互換。
