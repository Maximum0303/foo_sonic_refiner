# Sonic Refiner v0.6.5 Release Notes

## English

v0.6.5 adds manual reordering for existing user presets. The validated v0.6.5-dev.1 implementation is used unchanged for the feature itself.

### Added

- `↑` / `↓` buttons beside the user-preset management controls.
- Move the selected user preset one position up or down.
- The moved preset remains selected.
- Up is disabled for the first item; Down is disabled for the last item.
- Both move buttons are disabled when no user preset is selected or when only one preset exists.

### Persistence and compatibility

- Reordering changes only the order of entries in the existing user-preset list.
- SRP4 is unchanged; its existing serialized list order preserves the reordered list across restart.
- `.srpbackup` wrapper and format are unchanged, and export/import preserves the reordered list.
- `preset_version 9` is unchanged.
- User-preset names and all stored DSP values are unchanged by reordering.
- Legacy DSP presets and SRP1 / SRP2 / SRP3 / SRP4 remain readable.
- No DSP / Adaptive Tone Balance algorithm changes.
- All 12 built-in preset values are unchanged.

### Validation

The v0.6.5-dev.1 test sequence passed before promotion, including move-button states, up/down movement, selection retention, restart persistence, `.srpbackup` order restore, preset-content preservation, coexistence with Rename/Delete/new Save, Japanese / English, Light / Dark, A/B comparison, built-in presets, Adaptive Standard, ATB analyzing-state behavior, and full-track playback.

## 日本語

v0.6.5では、既存の任意プリセットを手動で並べ替えられる機能を追加しました。機能実装は、必須確認を完了したv0.6.5-dev.1をそのまま正式版の基準としています。

### 追加

- 任意プリセット管理欄に `↑` / `↓` ボタンを追加。
- 選択中の任意プリセットを1件ずつ上／下へ移動。
- 移動後も移動したプリセットを選択した状態を維持。
- 先頭では `↑`、末尾では `↓` を無効化。
- 任意プリセット未選択時、または1件だけの場合は移動できないボタンを無効化。

### 保存・互換性

- 変更するのは既存任意プリセット一覧の順序だけです。
- SRP4は変更せず、従来のリスト保存順序で再起動後も並べ替え後の順番を保持します。
- `.srpbackup`のラッパー／形式変更なし。書出／読込でも並び順を保持します。
- `preset_version 9`変更なし。
- 並べ替えで名前や保存済みDSP設定値は変更しません。
- 旧DSP presetおよびSRP1／SRP2／SRP3／SRP4の読み込み互換性を維持。
- DSP／Adaptive Tone Balanceアルゴリズム変更なし。
- 12種類の内蔵プリセット値変更なし。

### 検証

v0.6.5-dev.1で、↑／↓の有効状態、上下移動、選択維持、再起動後の順序保持、`.srpbackup`での順序復元、プリセット内容保持、名前変更・削除・新規保存との共存、日本語／English、Light／Dark、A/B比較、内蔵プリセット、適応型標準、ATB解析中表示、1曲通し再生を確認済みです。
