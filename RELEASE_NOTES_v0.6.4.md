# Sonic Refiner v0.6.4 Release Notes

## English

v0.6.4 adds a rename operation for existing user presets. The validated
v0.6.4-dev.1 implementation is used unchanged for the feature itself.

### Added

- `Rename...` button for the selected user preset.
- The rename dialog starts with the current name prefilled and selected.
- Names remain UTF-8 and are limited to 40 characters.
- A name already used by another user preset is rejected.
- Renaming to the same name is a harmless no-op.
- No user preset selected -> Rename is disabled.
- Built-in presets cannot be renamed.

### Compatibility

- Only the user-preset name is changed. Stored DSP settings are preserved exactly.
- SRP4 is unchanged.
- `.srpbackup` wrapper and format are unchanged.
- `preset_version 9` is unchanged.
- Legacy DSP presets and SRP1 / SRP2 / SRP3 / SRP4 remain readable.
- No DSP / Adaptive Tone Balance algorithm changes.
- All 12 built-in preset values are unchanged.

### Validation

The v0.6.4-dev.1 required test set passed before promotion:

- Release / x64 build
- settings-window version display
- Rename disabled with no selected user preset
- name prefill and selection
- renamed preset content preservation
- duplicate-name rejection
- same-name no-op
- Japanese / English localization
- Light / Dark UI
- `.srpbackup` export, removal, import, name restore, and setting restore
- built-in preset immutability
- full-track playback smoke test
- Cancel / OK behavior
- A/B Store / Listen / End Comparison behavior

## 日本語

v0.6.4では、既存の任意プリセットについて、保存済み設定を変えずに名前だけを
変更できる機能を追加しました。機能実装は、必須テストを完了したv0.6.4-dev.1を
そのまま正式版の基準としています。

### 追加

- 選択中の任意プリセットに `名前変更...` ボタンを追加。
- 名前変更画面では現在名をあらかじめ入力し、全選択状態で編集開始。
- UTF-8、最大40文字の既存仕様を維持。
- 他の任意プリセットとまったく同じ名前への変更は拒否。
- 現在名と同じ名前への変更は安全なno-op。
- 任意プリセット未選択時は名前変更ボタンを無効化。
- 内蔵プリセットは名前変更不可。

### 互換性

- 変更するのは任意プリセット名だけで、保存済みDSP設定値は変更しません。
- SRP4変更なし。
- `.srpbackup`のラッパー／形式変更なし。
- `preset_version 9`変更なし。
- 旧DSP presetおよびSRP1／SRP2／SRP3／SRP4の読み込み互換性を維持。
- DSP／Adaptive Tone Balanceアルゴリズム変更なし。
- 12種類の内蔵プリセット値変更なし。

### 検証

v0.6.4-dev.1の必須テストを正式版化前にすべて完了しました。

- Release / x64ビルド
- 設定画面のバージョン表示
- 任意プリセット未選択時の名前変更無効化
- 現在名の自動入力／全選択
- 名前変更後の保存内容維持
- 重複名拒否
- 同名no-op
- 日本語／English切り替え
- Light／Dark表示
- `.srpbackup`書出・削除・読込・名前／設定復元
- 内蔵プリセット不変
- 1曲通し再生
- Cancel／OK
- A/B保存・試聴・比較終了
