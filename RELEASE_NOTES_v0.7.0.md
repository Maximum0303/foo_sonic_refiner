# Sonic Refiner v0.7.0 Release Notes

## English

Sonic Refiner v0.7.0 introduces a dedicated Preset Manager for user presets while preserving the existing DSP and Adaptive Tone Balance processing.

### Highlights

- Dedicated Preset Manager for up to 20 user presets.
- Search with partial matching.
- Read-only preset preview.
- Current-settings match indicator (`●`).
- Apply, New from Current, Update from Current, Duplicate, Rename, Delete, Backup, and Restore.
- Right-click context menu for common preset operations.
- Double-click Apply.
- Keyboard shortcuts:
  - F2: Rename
  - Delete: Delete
  - Ctrl+F: Focus Search
  - Ctrl+Backspace: Clear Search
  - Alt+Up / Alt+Down: Reorder
- Reordering by buttons, keyboard, and drag-and-drop.
- Session-only selected-preset memory while the parent settings dialog remains open.
- Persistent Preset Manager window-size memory.
- Draggable left/right pane splitter with persistent split-ratio memory.
- Explicit Tab navigation order with the read-only preview excluded.
- Simplified parent User Presets area:
  preset selection → Save... → Load → Preset Manager...

### Backup / Restore

Preset Manager Backup and Restore operate on all user presets and their saved order using the existing `.srpbackup` format.

### Compatibility

- No DSP / Adaptive Tone Balance algorithm changes from v0.6.5.
- SRP4 remains unchanged.
- `.srpbackup` remains unchanged.
- `preset_version 9` remains unchanged.
- A/B behavior remains unchanged.
- All 12 built-in preset values remain unchanged.
- Existing older SRP compatibility is preserved.

---

## 日本語

Sonic Refiner v0.7.0では、DSP処理・Adaptive Tone Balance処理を変更せず、任意プリセットをまとめて管理する専用のPreset Managerを追加しました。

### 主な追加・変更

- 最大20件の任意プリセットを管理する専用Preset Manager。
- 部分一致による検索。
- 読み取り専用のプリセット内容プレビュー。
- 現在設定と一致するプリセットへの`●`表示。
- Apply、New from Current、Update from Current、Duplicate、Rename、Delete、Backup、Restore。
- よく使う操作の右クリックメニュー。
- ダブルクリックApply。
- キーボードショートカット：
  - F2：名前変更
  - Delete：削除
  - Ctrl+F：検索欄へ移動
  - Ctrl+Backspace：検索クリア
  - Alt+↑ / Alt+↓：並び替え
- ボタン・キーボード・ドラッグ＆ドロップによる並び替え。
- 親のSonic Refiner設定画面を開いている間だけ有効な選択プリセット記憶。
- Preset Managerのウィンドウサイズ記憶。
- 左右ペインのドラッグ分割と比率記憶。
- 読み取り専用プレビューを除外した明示的なTab移動順。
- 親画面の任意プリセット欄を
  プリセット選択 → 保存... → 呼出 → プリセット管理...
  の4項目に整理。

### Backup / Restore

Preset ManagerのBackup / Restoreは、既存の`.srpbackup`形式を使って、任意プリセット一式と保存順をまとめて扱います。

### 互換性

- v0.6.5からDSP／Adaptive Tone Balanceアルゴリズム変更なし。
- SRP4変更なし。
- `.srpbackup`形式変更なし。
- `preset_version 9`変更なし。
- A/B動作変更なし。
- 12個の内蔵プリセット値変更なし。
- 既存の旧SRP互換性も維持しています。
