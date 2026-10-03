# Changelog

## [0.8.2] - 2026-10-03

### Changed

- Formalized the validated v0.8.2-dev.1 unified gain-ceiling update.
- Fixed Depth and Clarity maximum gain are unified at +15.0 dB.
- ATB Auto Low and Auto High absolute maximum correction are raised from +10.0 dB to +15.0 dB.
- Help / Glossary / Important Notes and user documentation describe the unified +15.0 dB ATB ceiling.

### Validation / Compatibility

- v0.8.2-dev.1 reached +15.0 dB in actual Adaptive Standard playback and passed targeted Adaptive Standard / Full Boost listening and restart-retention checks.
- ATB analysis / decision logic, history, rate limiting, intro protection, and boost-only policy are unchanged.
- Built-in preset parameter values are unchanged; presets using 100% Depth / Clarity may sound slightly different because the 100% gain mapping changed.
- SRP5, `preset_version 10`, `.srpbackup`, Reverb, Width, Ambience, Auto Headroom, Preset Manager, and legacy compatibility are unchanged.

## [0.8.2-dev.1] - 2026-10-03

### Changed

- Unified fixed Depth and Clarity maximum gain at +15.0 dB.
- Raised ATB Auto Low and Auto High absolute maximum correction from +10.0 dB to +15.0 dB.
- Updated Help / Glossary / Important Notes and user documentation to describe the +15.0 dB ATB ceiling.

### Compatibility

- ATB analysis / decision logic, history, attack / release behavior, and boost-only policy are unchanged.
- Built-in preset parameter values are unchanged; presets using 100% Depth / Clarity may sound slightly different because the 100% gain mapping changed.
- SRP5, `preset_version 10`, `.srpbackup`, Reverb, Width, Ambience, Auto Headroom, Preset Manager, and legacy compatibility are unchanged.

## [0.8.1] - 2026-10-03

### Changed

- Formalized the validated v0.8.1-dev.1 documentation and user-guidance refresh.
- Help / Glossary / Important Notes identify R128 Real-time Loudness Normalizer **Natural -18** as the recommended normal starting point and distinguish the four standard normalization presets from the three additional mastering presets.
- QUICK_START.md and README_FIRST.txt now reflect Reverb, 16 built-in presets, Preset Manager, SRP5, and `preset_version 10`.

### Compatibility

- No DSP / ATB / Reverb algorithm changes from v0.8.0.
- No built-in preset value changes.
- SRP5, `preset_version 10`, `.srpbackup`, and all legacy compatibility behavior are unchanged.

## [0.8.1-dev.1] - 2026-10-03

### Changed

- Refreshed user-facing Help / Glossary / Important Notes without changing audio processing.
- Documented R128 Real-time Loudness Normalizer **Natural -18** as the recommended starting point.
- Clarified standard R128 normalization presets versus additional mastering presets.
- Refreshed README.md, COMPONENT_README.txt, QUICK_START.md, and README_FIRST.txt for current v0.8.x functionality.

### Compatibility

- No DSP / ATB / Reverb algorithm changes from v0.8.0.
- No built-in preset value changes.
- SRP5, `preset_version 10`, `.srpbackup`, and all legacy compatibility behavior are unchanged.

## [0.8.0] - 2026-10-03

### Added

- Added a dedicated Reverb control (0-100) as a separate late-reverberation stage after the existing Ambience early-reflection stage.
- Added natural Reverb decay during in-track silence and track-end tail rendering.
- Added four built-in venue presets:
  - Adaptive Hall: Width 60 / Ambience 55 / Reverb 50.
  - Adaptive Arena: Width 72 / Ambience 65 / Reverb 68.
  - Adaptive Dome: Width 85 / Ambience 75 / Reverb 85.
  - Adaptive Open Air: Width 75 / Ambience 20 / Reverb 10.
- Added Reverb persistence to DSP presets and user presets.

### Persistence / Compatibility

- DSP preset format is now `preset_version 10`.
- User preset format is now SRP5.
- SRP1-SRP4, DSP preset versions 1-9, older user presets, and legacy `.srpbackup` files remain readable.
- Older presets default Reverb to 0, preserving their previous sound.
- Existing 12 built-in presets remain Reverb 0.
- `.srpbackup` outer header remains `SONIC_REFINER_PRESET_BACKUP_V1`.

### Changed

- Formalized the validated v0.8.0-dev.3 build as v0.8.0.
- No DSP, Reverb tuning, venue preset values, SRP5 layout, or compatibility behavior changed during formalization.

## [0.8.0-dev.3] - 2026-10-03

### Changed

- Strengthened the built-in venue Reverb presets after listening tests:
  - Adaptive Hall: Reverb 35 -> 50.
  - Adaptive Arena: Reverb 50 -> 68.
  - Adaptive Dome: Reverb 65 -> 85.
  - Adaptive Open Air remains Reverb 10.
- Width and Ambience values are unchanged.

### Compatibility

- No Reverb algorithm, SRP5 layout, `preset_version 10`, legacy preset parsing, or `.srpbackup` compatibility behavior changed from v0.8.0-dev.2.

## [0.8.0-dev.2] - 2026-10-03

### Fixed

- Fixed MSVC build errors in the new Reverb code caused by the Windows `max` macro colliding with three `std::max(...)` calls.
- Switched those calls to the project's existing Windows-safe `(std::max)(...)` form.

### Compatibility

- No DSP tuning, Reverb values, preset values, SRP5 layout, `preset_version 10`, or legacy compatibility behavior changed from v0.8.0-dev.1.

## [0.7.0] - 2026-09-11

### Added

- Added a dedicated Preset Manager for user presets.
- Added Search with partial-match filtering and ASCII case-insensitive matching.
- Added read-only preset preview for tonal/spatial, output/protection, and operation settings.
- Added current-settings match indicator (`●`).
- Added Apply, New from Current, Update from Current, Duplicate, Rename, Delete, Backup, and Restore operations.
- Added Preset Manager right-click context menu:
  Apply, Duplicate..., Rename..., Update from Current..., Delete...
- Added double-click Apply.
- Added keyboard shortcuts:
  F2 Rename, Delete, Ctrl+F, Ctrl+Backspace, Alt+Up, and Alt+Down.
- Added user-preset reordering by Move Up / Move Down buttons, Alt+Up / Alt+Down, and drag-and-drop.
- Added Preset Manager session-only selected-preset memory while the parent Sonic Refiner settings dialog remains open.
- Added persistent Preset Manager window-size memory.
- Added draggable left/right pane splitter with persistent split-ratio memory.
- Added explicit Preset Manager Tab order and excluded the read-only preview from Tab navigation.
- Simplified the parent Sonic Refiner User Presets area to:
  preset selection → Save... → Load → Preset Manager...

### Changed

- Parent-dialog user-preset management controls for Rename, Delete, Move Up, and Move Down were removed from the UI because those operations are now handled in Preset Manager.
- Preset Manager Backup / Restore use the existing all-user-presets `.srpbackup` format and preserve saved order.
- User-preset management changes persist immediately and are not reverted by parent-dialog Cancel.
- Applying a preset from Preset Manager still follows the parent dialog's existing OK / Cancel semantics for DSP settings.

### Fixed

- Fixed a Preset Manager Search issue where Ctrl+Backspace could leave a visible DEL (`0x7F`) character.

### Compatibility

- No DSP / Adaptive Tone Balance algorithm changes from v0.6.5.
- SRP4 is unchanged.
- `.srpbackup` format is unchanged.
- `preset_version 9` is unchanged.
- A/B behavior is unchanged.
- All 12 built-in preset values are unchanged.
- Existing older SRP1 / SRP2 / SRP3 / SRP4 compatibility is preserved.

## [0.7.0-dev.33] - 2026-09-11

### Changed

- Simplified the parent Sonic Refiner settings dialog's User Presets section.
- The parent section now contains only:
  user-preset combo → Save... → Load → Preset Manager...
- Removed the parent-dialog UI controls for:
  Rename..., Delete, Move Up, and Move Down.
- Those management operations remain available in Preset Manager.
- The remaining four controls are arranged on a single row.
- The User Presets group is compacted, with the A/B Comparison and Master/Output/Protection groups moved upward to use the freed space cleanly.

### Compatibility

- Existing parent management handlers remain in the source and are not modified by this UI-only build.
- Preset Manager behavior is unchanged.
- Window-size persistence, splitter-ratio persistence, selection memory, search, keyboard shortcuts, context menu, reordering, Backup, and Restore are unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.32] - 2026-09-11

### Changed

- Defined an explicit keyboard Tab order for Preset Manager:
  Search → preset list → Move Up → Move Down → New from Current → Update from Current → Duplicate → Rename → Delete → Backup → Restore → Apply → Close.
- The read-only settings preview is explicitly excluded from Tab navigation.
- The Tab order is configured when Preset Manager opens and does not change preset data, search state, DSP settings, or command behavior.

### Compatibility

- Window-size persistence and splitter-ratio persistence are unchanged.
- Session-only selected-preset memory is unchanged.
- Ctrl+F, Ctrl+Backspace, Delete-key, F2 Rename, double-click Apply, context menu, reordering, Backup, and Restore are unchanged.
- No parent Sonic Refiner settings-dialog Tab behavior is changed in this build.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.31] - 2026-09-11

### Added

- Added a draggable vertical splitter between the Preset Manager user-preset pane and preview pane.
- The 10-pixel center gap acts as the splitter drag target and shows the horizontal-resize cursor.
- The splitter starts at the existing 40% / 60% left/right ratio when no saved ratio exists.
- The last splitter ratio is saved as persistent UI-only configuration and restored when Preset Manager is opened again.
- Because a ratio is stored rather than an absolute pixel coordinate, resizing the Preset Manager window preserves the same relative split.
- Existing minimum pane widths remain enforced: 220 px for the left pane and 300 px for the right pane.

### Compatibility

- Existing Preset Manager window-size persistence is unchanged and remains independent of splitter-ratio persistence.
- Window position is still not persisted.
- Session-only selected-preset memory is unchanged.
- Search, Ctrl+F, Ctrl+Backspace, Delete-key, F2 Rename, double-click Apply, context menu, reordering, Backup, and Restore are unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.30] - 2026-09-11

### Added

- Preset Manager now remembers its last window width and height and restores that size the next time it is opened.
- The saved size is UI-only persistent configuration and does not affect user presets or DSP settings.
- Window position is not stored.
- The first launch with no saved size still uses the existing 720×460 dialog resource size.
- The existing 640×400 minimum size is preserved and also enforced when restoring a saved size.

### Not included

- Left/right pane splitter-ratio persistence is not included in this build.

### Compatibility

- Session-only selected-preset memory is unchanged.
- Search, Ctrl+F, Ctrl+Backspace, Delete-key, F2 Rename, double-click Apply, context menu, reordering, Backup, and Restore are unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.29] - 2026-09-11

### Added

- Preset Manager now remembers the last selected user preset while the same parent Sonic Refiner settings dialog remains open.
- Closing Preset Manager and reopening it from that same parent dialog restores the remembered user-preset selection.
- The remembered state is session-only and is discarded when the parent Sonic Refiner settings dialog itself is closed.
- The remembered preset is resolved by name first, with the remembered index as a fallback for parent-side rename/delete cases.
- On the first Preset Manager open of a parent-dialog session, the existing selection rule is unchanged: first current-settings match, otherwise first user preset, otherwise none.

### Compatibility

- No persistent setting or preset format was added for this feature.
- Search, Ctrl+F, Ctrl+Backspace, Delete-key, F2 Rename, double-click Apply, context menu, reordering, Backup, and Restore are unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.28] - 2026-09-11

### Fixed

- Fixed the Preset Manager Search issue where `Ctrl+Backspace` could leave a visible DEL (`0x7F`) character after the query was cleared.
- The existing `Ctrl+Backspace` clear behavior remains unchanged.
- The Search edit now suppresses the DEL character delivered after the handled key sequence.

### Compatibility

- Ctrl+F, Delete-key, F2 Rename, double-click Apply, context menu, reordering, Backup, and Restore are unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.27] - 2026-09-11

### Added

- Added `Ctrl+Backspace` to clear the Preset Manager Search field.
- The shortcut works only while the Search edit control has keyboard focus.
- Clearing the Search field uses the existing Search-change path, returning the list to the unfiltered all-presets view.
- User-preset data, saved order, and current DSP settings are not modified by the shortcut.

### Compatibility

- Ctrl+F Search focus is unchanged.
- Delete-key, F2 Rename, and double-click Apply are unchanged.
- `↑` / `↓`, `Alt+↑` / `Alt+↓`, drag-and-drop reordering, and the right-click context menu are unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.26] - 2026-09-11

### Added

- Added `Ctrl+F` to move keyboard focus to the Preset Manager Search field.
- The existing Search text is preserved exactly; the shortcut does not clear or modify the query.
- Search results, current preset selection, saved preset order, and DSP settings are not changed by the shortcut.

### Compatibility

- Delete-key, F2 Rename, and double-click Apply are unchanged.
- `↑` / `↓`, `Alt+↑` / `Alt+↓`, and drag-and-drop reordering are unchanged.
- Ctrl+Backspace search clearing is not included in this build.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.25] - 2026-09-11

### Added

- Added `Delete` key shortcut to the Preset Manager user-preset list.
- With a real user preset selected and the list focused, pressing `Delete` invokes the existing `Delete / 削除` command.
- The shortcut reuses the existing Delete handler, so the confirmation dialog, default `No`, post-delete selection behavior, Search handling, and immediate persistence are unchanged.
- Delete remains usable while Search is active as long as a real visible user preset is selected.

### Compatibility

- Existing Delete button and right-click Delete behavior are unchanged.
- F2 Rename and double-click Apply are unchanged.
- `↑` / `↓`, `Alt+↑` / `Alt+↓`, and drag-and-drop reordering are unchanged.
- Ctrl+F and Ctrl+Backspace shortcuts are not included in this build.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.24] - 2026-09-11

### Added

- Added `F2` rename shortcut to the Preset Manager user-preset list.
- With a real user preset selected and the list focused, pressing `F2` invokes the existing `Rename... / 名前変更...` command.
- The shortcut reuses the existing Rename handler, so current-name prefill, full selection, duplicate-name rejection, same-name no-op, Search handling, and immediate persistence are unchanged.
- F2 remains usable while Search is active as long as a real visible user preset is selected.

### Compatibility

- Existing Rename button and right-click Rename behavior are unchanged.
- Double-click Apply is unchanged.
- `↑` / `↓`, `Alt+↑` / `Alt+↓`, and drag-and-drop reordering are unchanged.
- Delete-key, Ctrl+F, and Ctrl+Backspace shortcuts are not included in this build.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.23] - 2026-09-11

### Added

- Added double-click Apply to the Preset Manager user-preset list.
- Double-clicking a user preset invokes the existing Apply command.
- If the selected preset already matches the current DSP settings and Apply is disabled, double-click does nothing.
- Selection-only behavior remains unchanged for a normal single click.

### Compatibility

- The existing Apply handler remains the single source of DSP application behavior.
- Right-click context menu behavior is unchanged.
- `↑` / `↓`, `Alt+↑` / `Alt+↓`, and drag-and-drop reordering are unchanged.
- F2 / Delete / Ctrl+F keyboard additions are not included in this build.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.22] - 2026-09-11

### Added

- Added a right-click context menu for user presets in Preset Manager.
- Right-clicking a visible preset selects that preset before the menu opens.
- Context-menu commands:
  - `Apply / 適用`
  - `Duplicate... / 複製...`
  - `Rename... / 名前変更...`
  - `Update from Current... / 現在の設定で上書き...`
  - `Delete... / 削除...`
- Every context-menu command dispatches to the same existing button command, so persistence, confirmations, DSP Apply behavior, duplicate limits, and Search behavior stay identical.
- `Apply` mirrors the existing Apply enabled/disabled state.
- `Duplicate` mirrors the existing 20-preset limit state.

### Compatibility

- Existing buttons, `↑` / `↓`, `Alt+↑` / `Alt+↓`, and drag-and-drop behavior are unchanged.
- Double-click Apply and the additional F2/Delete keyboard shortcuts are not included in this build.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.21] - 2026-09-11

### Added

- Added mouse drag-and-drop reordering to the Preset Manager user-preset list.
- Dragging a preset onto another visible preset moves the dragged preset to that position.
- The moved preset remains selected after the drop.
- The reordered list is persisted immediately through the existing user-preset persistence callback.
- Normal click selection remains unchanged when the pointer does not move beyond the Windows drag threshold.
- Dropping outside the list cancels the reorder.
- Drag reorder is blocked while Search contains text.

### Compatibility

- Existing `↑` / `↓` buttons are unchanged.
- Existing `Alt+↑` / `Alt+↓` keyboard reordering is unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.20] - 2026-09-11

### Added

- Added `Alt+↑` / `Alt+↓` keyboard reordering to Preset Manager.
- The shortcuts invoke the same one-step reorder commands as the existing `↑` / `↓` buttons.
- The moved user preset remains selected and the new order is persisted immediately.
- Search-active behavior is shared with the buttons: reordering is blocked while Search contains text.
- `Alt+↑` does nothing at the first preset; `Alt+↓` does nothing at the last preset.

### Compatibility

- Existing `↑` / `↓` button behavior is unchanged.
- Drag-and-drop reordering is not included in this build.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.19] - 2026-09-11

### Added

- Added `↑` / `↓` reorder buttons to Preset Manager.
- Moves the selected user preset exactly one position up or down.
- The moved preset remains selected after reordering.
- Reordering is persisted immediately through the existing user-preset persistence callback.
- `↑` is disabled for the first preset.
- `↓` is disabled for the last preset.
- Both reorder buttons are disabled while Search is active.
- Both buttons are disabled when there is no real selected preset.

### Compatibility

- No drag-and-drop reordering in this build.
- No `Alt+↑` / `Alt+↓` keyboard reordering in this build.
- Existing main-dialog reorder behavior is unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.18] - 2026-09-11

### Changed

- Adjusted only the main settings dialog layout for the User Presets section.
- Removed the large empty gap left after the old Export / Import buttons were removed.
- Repacked the second row controls to `Delete` → `Up` → `Down` → `Preset Manager...`.
- First-row controls are unchanged.

### Compatibility

- Layout-only update. No behavior changes.
- Preset Manager Backup / Restore behavior is unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.17] - 2026-09-11

### Changed

- Removed the legacy `Export... / 書出...` and `Import... / 読込...` buttons from the main Sonic Refiner settings dialog.
- User-preset backup and restore are now accessed through Preset Manager as `Backup... / バックアップ...` and `Restore... / 復元...`.

### Compatibility

- Existing backup / restore serialization and file handling code is unchanged.
- `.srpbackup` remains fully compatible with the existing `SONIC_REFINER_PRESET_BACKUP_V1` + SRP4 format.
- Preset Manager Backup / Restore behavior is unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.16] - 2026-09-11

### Fixed

- Fixed a Release/x64 compile error in the new Preset Manager Restore implementation.
- The Restore preset-count validation now uses the existing project constant `maximum_user_presets`.

### Compatibility

- No Restore behavior changes beyond the compile fix.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.15] - 2026-09-11

### Added

- Added `Restore... / 復元...` to Preset Manager.
- Reuses the existing `.srpbackup` reader and SRP4 backup parser.
- Fully validates the selected backup before modifying the current user-preset list.
- Shows a Yes/No warning before replacement, with No as the default.
- Successful Restore replaces the complete user-preset list and saved order, then persists immediately.
- After Restore, the first restored user preset is selected; an empty backup leaves no selection.
- Search clears after successful Restore so the restored list is shown unfiltered.
- Restore completion reports the restored preset count.

### Compatibility

- Restore changes only the user-preset collection and order.
- Restore does not Apply any restored preset and does not change current DSP settings.
- Existing parent-window `Import... / 読込...` behavior is left unchanged in this development step.
- Backup behavior is unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.14] - 2026-09-11

### Added

- Added `Backup... / バックアップ...` to Preset Manager.
- Saves the complete user-preset list and its saved order to `.srpbackup`.
- Reuses the existing `SONIC_REFINER_PRESET_BACKUP_V1` container and SRP4 serialization without changing the format.
- Backup remains available with zero user presets and creates a valid empty SRP4 backup.
- Added Backup-specific save-dialog and completion/error wording.
- Preset Manager bottom controls now use two rows to avoid overlap.

### Compatibility

- Existing parent-window `Export... / 書出...` behavior is left unchanged in this development step.
- Restore / Import is not changed in this development step.
- Backup does not change current DSP settings, built-in presets, or user-preset order.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.13] - 2026-09-11

### Added

- Added `Delete... / 削除...` to Preset Manager.
- Shows a Yes/No warning before deleting the selected user preset.
- Deletes only after explicit Yes confirmation.
- Persists the updated user-preset list and order immediately.
- After deletion, selects the preset now occupying the same list index when available.
- If the deleted item was the last preset, selects the previous preset.
- If the final remaining preset is deleted, leaves the list with no selection and moves focus to `New from Current...`.
- Clears Search after successful deletion so the post-delete selection is unambiguous.
- Delete is disabled when no real preset is selected.

### Compatibility

- Current DSP settings and built-in presets are never modified by Delete.
- Search, Apply, New from Current, Update from Current, Duplicate, and Rename behavior are unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.12] - 2026-09-11

### Added

- Added `Rename... / 名前変更...` to Preset Manager.
- The rename dialog opens with the current preset name prefilled and fully selected.
- Rename changes only the preset name; saved Sonic Refiner settings and list position are preserved.
- Renaming to another preset's existing name is rejected.
- Entering the same name performs no change.
- Successful rename is persisted immediately and the same preset remains selected.
- When Search is active, successful rename clears Search so the renamed preset remains visible and selected.
- Rename is disabled when no real preset is selected.

### Compatibility

- Search, Apply, New from Current, Update from Current, and Duplicate behavior are unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.11] - 2026-09-11

### Added

- Added `Duplicate... / 複製...` to Preset Manager.
- Duplicates the selected user preset's complete saved Sonic Refiner settings.
- Requires a new unique preset name; duplicate names are rejected.
- Inserts the duplicate immediately below the source preset.
- Selects the newly duplicated preset automatically.
- Persists the updated user-preset list and order immediately.
- Clears an active Search filter after successful duplication so the new preset can remain visible and selected.
- Disables Duplicate when no real preset is selected or when the 20-user-preset limit has been reached.

### Compatibility

- The source preset remains unchanged.
- Search, Apply, New from Current, and Update from Current behavior are unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.10] - 2026-09-11

### Added

- Added `Update from Current... / 現在の設定で上書き...` to Preset Manager.
- Updates only the saved settings of the selected user preset; its name and list position are preserved.
- Shows a Yes/No confirmation dialog before overwriting.
- Successful updates are persisted immediately through the existing parent callback.
- The selected preset remains selected after the update.
- Preview and current-settings `●` indicators are refreshed immediately after the update.
- The action is disabled when no real preset is selected, including zero-preset and zero-search-result states.

### Compatibility

- Search, Apply, and New from Current behavior are unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.9] - 2026-09-11

### Fixed

- Fixed the v0.7.0-dev.8 compile error in `New from Current...`.
- Preset Manager now keeps its user-preset collection as an editable local copy instead of a const reference.
- Successful management changes continue to be persisted immediately through the existing parent callback.

### Compatibility

- New from Current behavior is otherwise unchanged from dev.8.
- Search and Apply behavior are unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.8] - 2026-09-11

### Added

- Added `New from Current... / 新規作成...` to Preset Manager.
- Creates a new user preset from the current Sonic Refiner settings.
- New presets are appended to the end of the saved user-preset order and selected automatically.
- Creating a preset does not change the current DSP/audio settings.
- Duplicate names are rejected instead of overwritten.
- Existing UTF-8 name handling, 40-character input limit, and 20-preset maximum are preserved.
- When a search filter is active, successful creation clears Search so the newly created preset can be selected and shown.
- User-preset changes are saved immediately and remain independent of the parent settings dialog Cancel action.

### Fixed

- Restored the generic information dialog button caption to `Close / 閉じる`.

### Compatibility

- Apply/search behavior is otherwise unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.7] - 2026-09-11

### Changed

- Preset Manager `Apply / 適用` is now enabled only when the selected user preset differs from the current Sonic Refiner settings.
- After Apply succeeds and the selected preset becomes an exact current-settings match, Apply is disabled immediately.
- Selecting a different non-matching preset enables Apply again.
- Matching presets marked with `●` cannot be redundantly applied.

### Compatibility

- Search and Apply behavior are otherwise unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.6] - 2026-09-11

### Fixed

- Fixed the Preset Manager runtime localization bug that relabeled the Apply button as `閉じる / Close`.
- The left button now remains `適用 / Apply`.
- The right button remains `閉じる / Close`.
- Button actions are unchanged: Apply applies the selected preset; Close only closes Preset Manager.

### Compatibility

- No DSP / Adaptive Tone Balance algorithm changes.
- Search and Apply behavior are otherwise unchanged.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.5] - 2026-09-11

### Added

- Added `Apply / 適用` to Preset Manager.
- Selecting a preset remains preview-only; settings change only when Apply is executed.
- Enter activates Apply through the default dialog button.
- Apply immediately recalculates current-settings `●` indicators.
- Close / Esc / window X closes Preset Manager without applying a merely selected preset.

### Compatibility

- Apply is routed through the parent Sonic Refiner settings update path, preserving the existing `notify_changed()` behavior.
- Parent `Cancel` still restores the exact settings that were active when the parent settings dialog opened.
- Search behavior is unchanged from dev.4.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.4] - 2026-09-11

### Fixed

- Restored the Preset Manager-specific `apply_language()` method that was accidentally removed while adding search in dev.3.
- Fixed the parent Sonic Refiner settings-window version title so it reports v0.7.0-dev.4.

### Compatibility

- Search behavior is unchanged from dev.3.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.3] - 2026-09-11

### Added

- Added the first Preset Manager search implementation.
- Search filters user presets by preset-name substring only.
- ASCII letters are matched case-insensitively; Japanese and other characters use literal substring matching.
- Filtering is display-only and does not modify preset contents or saved order.
- Added filtered-result counts and the localized `No matching presets` empty state.
- Added an explicit display-row to backing-preset index map so the read-only preview remains tied to the correct preset after filtering.

### Compatibility

- Preset Manager remains read-only in this development step.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.2] - 2026-09-11

### Fixed

- Fixed the v0.7.0-dev.1 Release / x64 compile failure in the new Preset Manager resize code.
- Changed the four newly added `std::max(...)` calls to the Windows-safe `(std::max)(...)` form already used by the existing source.
- Removed the UTF-8 BOM from `ビルドと梱包.cmd` so `cmd.exe` no longer interprets the first line as garbled text.

### Compatibility

- Preset Manager feature scope is unchanged from dev.1.
- No DSP / Adaptive Tone Balance algorithm changes.
- SRP4, `.srpbackup`, `preset_version 9`, A/B behavior, and all 12 built-in preset values are unchanged.

## [0.7.0-dev.1] - 2026-09-11

### Added

- Added the first read-only Preset Manager foundation.
- Added `Preset Manager... / プリセット管理...` to the existing Sonic Refiner settings dialog.
- Added a resizable 720 x 460 Preset Manager dialog with a user-preset list and read-only settings preview.
- Added current-settings match markers (`●`) without storing any new preset state.
- The first matching user preset is selected when the manager opens; otherwise the first preset is selected.
- Added Japanese / English UI text and foobar2000 Light / Dark mode hooks.

### Compatibility

- No DSP or Adaptive Tone Balance algorithm changes.
- No SRP4 serialization changes.
- No `.srpbackup` format changes.
- `preset_version 9` is unchanged.
- All 12 built-in preset values are unchanged.
- Existing v0.6.5 user-preset management controls remain available in this first development build.

### Scope

- This dev.1 build intentionally does not yet implement New / Apply / Update / Duplicate / Rename / Delete / Backup / Restore / Search / drag-and-drop operations inside Preset Manager.

## [0.6.5] - 2026-08-29

### Added

- Added `↑` / `↓` buttons to reorder the selected user preset one position at a time.
- The selected preset follows the moved item.
- Move buttons are disabled when no movement is possible.

### Compatibility

- Reordering changes only the order of existing `user_preset` entries.
- SRP4 serialization is unchanged and naturally preserves vector order.
- `.srpbackup` wrapper / format is unchanged.
- `preset_version 9` is unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- All 12 built-in preset values are unchanged.

### Validation

- v0.6.5-dev.1 passed the required reordering, persistence, backup/restore, rename/delete/new-save coexistence, JP/EN, Light/Dark, A/B, built-in preset, ATB analysis-state, and full-track playback checks before promotion.

## [0.6.5-dev.1] - 2026-08-29

### Added

- Added `↑` / `↓` buttons to reorder the selected user preset one position at a time.
- The selected preset follows the moved item.
- Move buttons are disabled when no movement is possible.

### Compatibility

- Reordering changes only the order of existing `user_preset` entries.
- SRP4 serialization is unchanged and naturally preserves vector order.
- `.srpbackup` wrapper / format is unchanged.
- `preset_version 9` is unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- All 12 built-in preset values are unchanged.

## [0.6.4] - 2026-08-28

### Added

- Added `名前変更... / Rename...` for existing user presets.
- The rename dialog pre-fills and selects the current user-preset name.
- Renaming changes only the user-preset name; all stored DSP settings remain unchanged.
- Exact duplicate names belonging to another user preset are rejected.
- Rename is disabled when no user preset is selected.
- Built-in presets remain fixed and cannot be renamed.

### Compatibility

- SRP4 is unchanged.
- `.srpbackup` wrapper and format are unchanged.
- `preset_version 9` is unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- All 12 built-in preset values are unchanged.
- Legacy DSP presets and SRP1 / SRP2 / SRP3 / SRP4 compatibility are preserved.

### Validation

- Release / x64 build of v0.6.4-dev.1 passed.
- Rename enable/disable state, prefilled selection, rename content preservation, duplicate rejection, and same-name no-op were verified.
- Japanese / English and Light / Dark display were verified.
- `.srpbackup` export/remove/import restored renamed names and stored settings correctly.
- Built-in presets, full-track playback, Cancel / OK, and A/B behavior were verified unchanged.

## [0.6.4-dev.1] - 2026-08-28

### Added

- Added `名前変更... / Rename...` for existing user presets.
- The rename dialog pre-fills the current user-preset name and edits only the name.
- The Rename button is disabled when no user preset is selected.
- Renaming to a name already used by another user preset is rejected.
- Built-in presets remain fixed and cannot be renamed.

### Compatibility

- Renaming does not change Depth, Clarity, Width, Ambience, Master Strength, Output Gain, protection flags, enabled state, or Adaptive Tone Balance state.
- SRP4 is unchanged.
- `.srpbackup` format is unchanged.
- `preset_version 9` is unchanged.
- No DSP / Adaptive Tone Balance algorithm changes.
- All 12 built-in preset values are unchanged.

## [0.6.3] - 2026-08-28

### Changed

- When current DSP settings do not match any of the 12 built-in presets, the
  Built-in Presets combo displays `Custom / カスタム` instead of appearing blank.
- `Custom / カスタム` is a UI-only state and is not loadable as a built-in preset.
- With Adaptive Tone Balance ON, Depth and Clarity labels explicitly identify
  them as the Auto Low / Auto High correction limits.
- ATB-mode descriptions clarify that 100% is an upper permission and does not
  force a constant +10 dB boost.
- Help / Glossary ATB explanations were reorganized for practical user
  understanding.
- Glossary entries separately define Adaptive Tone Balance, Auto Low, Auto High,
  and ATB Analysis State.

### Compatibility

- No DSP / ATB algorithm changes.
- All 12 built-in preset values are unchanged.
- SRP4 and `preset_version 9` are unchanged.
- Legacy preset / backup compatibility is unchanged.

### Validation

- Custom display: matching, non-matching, restart, language switching, user
  presets, A/B, Cancel, Light / Dark all verified.
- ATB labels: ON / OFF, Japanese / English, restart, Cancel, Light / Dark all
  verified.
- Help / Glossary: Japanese / English and Light / Dark verified.
- Full-track Adaptive Standard smoke playback completed without dropout,
  click / pop noise, abrupt unnatural tonal change, or crash.

## [0.6.3-dev.3] - 2026-08-28

### Help / Glossary clarity
- Reorganized Adaptive Tone Balance Help around practical user behavior.
- Clarified that ATB is boost-only and that Depth / Clarity are correction limits while ATB is On.
- Clarified that 100% permits up to +10.0 dB but does not force a constant +10 dB boost.
- Clarified that Width / Ambience remain manual and Master Strength also scales adaptive correction.
- Added separate Glossary entries for Auto Low, Auto High, and ATB Analysis State using the current validated frequency ranges.
- Clarified fresh-analysis conditions and Pause→Resume history preservation.
- No DSP / ATB algorithm, preset value, or serialization changes.

## [0.6.3-dev.2] - 2026-08-28

### Changed

- When Adaptive Tone Balance is ON, the Depth and Clarity labels now explicitly identify them as the Auto Low / Auto High correction limits.
- The ATB-mode descriptions now state that 100% is only a maximum permission and does not mean a constant +10 dB boost.
- When Adaptive Tone Balance is OFF, the original fixed-mode Depth / Clarity labels and descriptions are shown.
- The Depth / Clarity label fields were widened inside the existing 560 x 320 layout to avoid text clipping in Japanese and English.
- The `Custom / カスタム` state added in v0.6.3-dev.1 is retained unchanged.

### Compatibility

- No DSP / ATB algorithm changes.
- All 12 built-in preset values are unchanged.
- SRP4 and `preset_version 9` are unchanged.
- Legacy preset and backup compatibility is unchanged.

## [0.6.3-dev.1] - 2026-08-28

### Changed

- When current DSP settings do not match any of the 12 built-in presets, the Built-in Presets combo now displays `Custom / カスタム` instead of appearing blank.
- `Custom / カスタム` is a UI-only state, not an additional built-in preset.
- The built-in preset Load button remains disabled while the Custom state is displayed.
- Japanese / English switching updates the Custom label while preserving the current DSP settings.
- Loading or otherwise reaching an exact built-in preset match returns the combo to that built-in preset name.

### Compatibility

- No DSP / ATB algorithm changes.
- All 12 built-in preset values are unchanged.
- SRP4 and `preset_version 9` are unchanged.
- Legacy preset and backup compatibility is unchanged.

## [0.6.2] - 2026-08-23

### Fixed

- The Built-in Presets combo now reflects the built-in preset that exactly matches the currently restored DSP settings when the settings dialog opens.
- Restarting foobar2000 after using a built-in preset no longer causes the combo to visually fall back to `Standard` while another preset's settings remain active.
- When the current settings do not exactly match any built-in preset, the built-in combo is left unselected instead of showing a misleading preset name.
- Slider / option changes, user-preset loads, and A/B listening resynchronize the displayed built-in preset selection.
- Selecting a combo item still requires `Load` before the DSP settings are changed.

### Compatibility

- No DSP / ATB algorithm changes.
- All 12 built-in preset values are unchanged.
- SRP4 and `preset_version 9` are unchanged.
- Legacy preset and backup compatibility is unchanged.

## [0.6.1] - 2026-08-23

### Fixed

- Added a clear ATB analysis-pending status so stale Auto Low / Auto High values from the previous playback position are not shown as if they belonged to the new one.
- Playback start, Next, Previous, direct track jumps, natural track changes, seeks, Stop -> playback, and ATB Off -> On now show `自動補正：解析中...` / `Auto: Analyzing...` while fresh analysis is being accumulated.
- New-track and seek notifications use a runtime-only playback discontinuity generation consumed by the ATB processor so fresh analysis begins reliably on the new playback position.
- Pause / Resume continues to preserve the current ATB analysis state.

### Compatibility

- No audible DSP or Adaptive Tone Balance decision-algorithm changes from v0.6.0.
- Auto Low / Auto High mapping, smoothing, startup protection, and +10.0 dB absolute limits are unchanged.
- SRP4 and `preset_version 9` are unchanged.
- All 12 built-in presets are unchanged.
- Legacy DSP presets and SRP1 / SRP2 / SRP3 / SRP4 backup/preset compatibility are unchanged.
- Runtime analyzer state remains non-persistent.

### Validation

- Verified playback start, Next, Previous, direct track jump, seek, natural track advance, Stop -> playback, and ATB Off -> On all enter the analyzing state.
- Verified Pause -> Resume preserves analysis and does not restart it.
- Verified the analyzing state returns to numeric Auto Low / Auto High status after sufficient fresh analysis.
- Verified Japanese / English, Light / Dark, and full-track playback without dropout, click noise, abrupt unnatural tonal change, or crash.

## [0.6.1-dev.2] - 2026-08-23

### Fixed

- Track changes triggered by Next / Previous / direct track jumps now immediately enter the ATB `Analyzing...` UI state.
- Added a runtime-only playback discontinuity generation so the ATB analyzer is reset for new-track and seek notifications even when the DSP discontinuity callback arrives through a different path or timing.
- Pause / Resume continues to preserve ATB analysis history.

### Compatibility

- No change to the ATB Low / High decision algorithm, boost mapping, smoothing rates, or absolute limits.
- No change to SRP4, `preset_version 9`, user presets, `.srpbackup`, or the 12 built-in presets.

## [0.6.1-dev.1] - 2026-08-23

### Fixed

- Track changes and seeks now invalidate the previous track's displayed Auto Low / Auto High values immediately while Adaptive Tone Balance is enabled.
- The normal ATB status line shows `自動補正：解析中...` / `Auto: Analyzing...` until the new playback segment has accumulated the normal minimum stable analysis history.
- Added a runtime-only UI analysis-pending guard so a retained transition gain cannot be mistaken for the new track's completed analysis result.

### Unchanged

- No audible DSP or Adaptive Tone Balance algorithm changes.
- ATB targets, filters, smoothing, startup protection, gain limits and click-free transition behavior are unchanged from v0.6.0.
- Pause / Resume history behavior, built-in presets, `preset_version 9`, SRP4, legacy compatibility, `.srpbackup`, A/B, Cancel and persistence behavior are unchanged.

## [0.6.0] - 2026-08-23

### Added

- Added the 12th built-in preset, `Adaptive Standard / 適応型標準`.
- Adaptive Standard uses Depth 100, Clarity 100, Width 50, Ambience 40, Master Strength 100%, Output Gain 0.0 dB, both protection options On, Sonic Refiner enabled, and Adaptive Tone Balance On.
- The preset gives Auto Low / Auto High the full permitted automatic-correction range while retaining the Standard preset's Width / Ambience values.

### Fixed

- Widened the Depth and Clarity value fields so Japanese ATB limit text such as `100% / 自動上限 +10.0 dB` is fully visible.
- Formal source packaging retains the exact Japanese helper filename `ビルドと梱包.cmd` without a garbled duplicate.

### Compatibility

- Existing 11 built-in presets remain unchanged and continue to load ATB Off.
- DSP and Adaptive Tone Balance algorithms are unchanged from v0.5.0.
- `preset_version 9` and SRP4 remain unchanged.
- SRP1 / SRP2 / SRP3 / SRP4 and legacy DSP preset reading remain supported.
- `.srpbackup`, A/B, Cancel, direct settings access, language behavior, and runtime analyzer persistence rules are unchanged.

### Validation

- The release candidate was verified in Japanese and English, Light and Dark mode.
- Adaptive Standard settings, restart persistence, A/B switching/restoration, Cancel restoration, SRP4 user-preset backup/restore, existing Standard behavior, and continuous playback were checked.
- v0.6.0 formal source keeps the validated v0.6.0-dev.3 DSP and preset behavior; formalization changes version markers and public release documentation only.

## [0.6.0-dev.3] - 2026-08-23

### Fixed

- Corrected the source ZIP packaging so the Japanese build helper is stored with the exact filename `ビルドと梱包.cmd`.
- Removed the garbled duplicate filename that was accidentally present in the v0.6.0-dev.2 source ZIP.

### Unchanged

- Compiled DSP code and Adaptive Tone Balance behavior are unchanged from v0.6.0-dev.2.
- Adaptive Standard settings and the existing 11 built-in presets are unchanged.
- `preset_version 9`, SRP4, legacy preset reading, `.srpbackup`, A/B and runtime-state persistence behavior are unchanged.
- The v0.6.0-dev.2 UI clipping fix is retained.

## [0.6.0-dev.2] - 2026-08-23

### Fixed

- Widened the Depth and Clarity value text fields so the Japanese ATB limit display such as `100% / 自動上限 +10.0 dB` is not clipped at the right edge.

### Unchanged

- No DSP or Adaptive Tone Balance algorithm changes.
- Adaptive Standard settings are unchanged from v0.6.0-dev.1.
- `preset_version 9`, SRP4, legacy preset reading, `.srpbackup`, A/B and runtime-state persistence behavior are unchanged.

## [0.6.0-dev.1] - 2026-08-23

### Added

- Added one built-in preset: **適応型標準 / Adaptive Standard**.
- The preset uses Depth 100, Clarity 100, Width 50, Ambience 40, Master Strength 100%, Output Gain 0.0 dB, both protection options On, Sonic Refiner enabled, and Adaptive Tone Balance On.
- With ATB On, Depth / Clarity 100 grant the existing Auto Low / Auto High logic the full permitted range without changing the ATB algorithm.

### Compatibility

- Existing 11 built-in presets are unchanged.
- `preset_version 9`, SRP4, legacy preset reading and `.srpbackup` compatibility are unchanged.
- No DSP algorithm, ATB target, filter, smoothing, A/B or runtime-state persistence behavior changed.

## [0.5.0] - 2026-08-23

### Added

- Added optional Adaptive Tone Balance (ATB), disabled by default.
- Added source-dependent boost-only automatic Low and High tonal correction.
- Added current Auto Low / Auto High status to the normal settings UI.
- Added ATB On/Off to A/B slots, user presets, DSP presets, and `.srpbackup` data.

### Adaptive Tone Balance

- Auto Low uses Bass 60–180 Hz vs Body 200–500 Hz with a +6.5 dB Bass/Body target.
- Auto Low preserves the dry signal and adds a parallel filtered 60–180 Hz Bass component.
- Auto High combines High/Mid and Treble/Presence balance.
- Auto Low absolute maximum is +10.0 dB.
- Auto High absolute maximum is +10.0 dB.
- Depth and Clarity become automatic-correction limits while ATB is On.
- ATB Off preserves the v0.4.0 fixed Depth / Clarity behavior.
- Slow rolling analysis, startup protection, confidence gating, and asymmetric gain movement reduce abrupt tonal changes.
- Track changes, seeks, Stop, and ATB Off→On restart analysis; Pause/Resume preserves it.

### Presets and compatibility

- DSP preset write format advanced to `preset_version 9`.
- User-preset / `.srpbackup` write format advanced to `SRP4`.
- SRP1, SRP2, SRP3, SRP4 and DSP preset versions 1–8 remain readable.
- Legacy data without ATB state loads ATB Off.
- Existing 11 built-in presets remain unchanged and load ATB Off.
- Runtime analyzer history and current automatic-gain state are not persisted.

### A/B and UI

- A/B slots store ATB On/Off and restore the complete pre-comparison settings when comparison ends.
- Development-only diagnostic readouts were removed from the formal UI.
- Light/Dark mode, continuous playback, restart persistence, Cancel behavior, preset backup/restore, legacy SRP3 import, and A/B ATB switching were validated on the release candidate.

## [0.5.0-dev.25] - 2026-08-23

### UI / cleanup

- Removed the development-only diagnostic text from the normal settings window.
- Restored the bottom status line to the normal processing state display while Adaptive Tone Balance is enabled.
- Kept the user-facing Adaptive Tone Balance runtime status showing current Auto Low / Auto High correction.
- Disabled the development-only pre/post Bass/Body comparison pass because it did not feed the correction algorithm.

### Unchanged

- No intended audio correction change from dev.23/dev.24.
- Low: parallel 60–180 Hz Bass-band addition, Bass/Body target +6.5 dB, Auto Low maximum +10.0 dB.
- High: H/M + T/P combined decision, Auto High maximum +10.0 dB.
- T/P analysis required by Auto High remains active.
- Smoothing and startup protection are unchanged.
- `preset_version 9` and `SRP4` persistence are unchanged.
- Legacy SRP1/2/3 and DSP preset versions 1–8 remain compatible with ATB Off.
- A/B behavior, presets, Output Gain, level matching, and automatic headroom are unchanged.

## [0.5.0-dev.24] - 2026-08-22

### Persistence integration

- Formalized the existing Adaptive Tone Balance persistence contract without changing the tested dev.23 audio algorithm.
- DSP preset write format is `preset_version 9` and stores Adaptive Tone Balance On/Off.
- User-preset and `.srpbackup` write format is `SRP4` and stores Adaptive Tone Balance On/Off.
- `SRP1`, `SRP2`, `SRP3`, and DSP preset versions 1–8 remain readable.
- Legacy formats default Adaptive Tone Balance to Off.
- Built-in presets continue to use Adaptive Tone Balance Off.
- Runtime analysis history, current automatic gains, confidence values, and diagnostics are not persisted.
- Updated current Help / Important Notes / README documentation to the tested +10 dB Auto Low and +10 dB Auto High absolute limits.

### Audio

- No DSP algorithm changes from dev.23.
- Low remains the parallel 60–180 Hz Bass-band design with Bass/Body target +6.5 dB and Auto Low absolute maximum +10.0 dB.
- High remains the H/M + T/P combined decision with Auto High absolute maximum +10.0 dB.
- Smoothing, startup protection, Width, Ambience, Master Strength, Output Gain, level matching, and automatic headroom are unchanged.

## [0.5.0-dev.23] - 2026-08-22

### Changed

- Raised the Auto Low absolute maximum from +8.0 dB to +10.0 dB.

### Unchanged

- Adaptive Low filter topology is identical to dev.22/dev.13: dry signal plus parallel 60-180 Hz Bass-band addition.
- Bass/Body decision target remains +6.5 dB.
- Low confidence logic and smoothing are unchanged.
- H/M + T/P combined High decision is identical to dev.22/dev.21.
- Auto High absolute maximum remains +10.0 dB.
- High thresholds, confidence logic and smoothing are unchanged.
- Startup protection, Master Strength, Width, Ambience, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.

## [0.5.0-dev.22] - 2026-08-22

### Changed

- Raised the Auto Low absolute maximum from +6.0 dB to +8.0 dB.

### Unchanged

- Adaptive Low filter topology is identical to dev.21/dev.13: dry signal plus parallel 60-180 Hz Bass-band addition.
- Bass/Body decision target remains +6.5 dB.
- H/M + T/P combined High decision is identical to dev.21.
- Auto High absolute maximum remains +10.0 dB.
- All High thresholds, confidence logic and smoothing are unchanged.
- Startup protection, Master Strength, Width, Ambience, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.

## [0.5.0-dev.21] - 2026-08-22

### Changed

- Raised the Auto High absolute maximum from +8.0 dB to +10.0 dB.

### Unchanged

- H/M + T/P combined High decision logic is identical to dev.20.
- Gentle High baseline remains +3.2 dB.
- H/M severity mapping remains -13.0 dB to -16.0 dB.
- T/P severity mapping remains -5.0 dB to -7.5 dB.
- Existing H/M shortage confidence gate is unchanged.
- Low processing and Low decision logic are unchanged.
- Bass/Body target remains +6.5 dB and Auto Low maximum remains +6.0 dB.
- Smoothing, startup protection, Master Strength, Width, Ambience, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.

## [0.5.0-dev.20] - 2026-08-22

### Changed

- Experimental Auto High demand now combines H/M and T/P after at least six valid T/P windows are available.
- The existing H/M shortage percentage still controls increase / hold / release behavior.
- The old H/M-only candidate remains the hard upper bound for the new combined candidate.
- Added `HC` (High Candidate) to the development diagnostic line so the current automatic target can be inspected without waiting for the smoothed output gain to catch up.

### Experimental combined High map

- Gentle baseline: up to +3.2 dB.
- H/M extra-correction severity begins below -13.0 dB and reaches full severity at -16.0 dB.
- T/P extra-correction severity begins below -5.0 dB and reaches full severity at -7.5 dB.
- Extra correction uses `sqrt(H/M severity * T/P severity)`, so both metrics must indicate a deeper deficiency before HC approaches +8.0 dB.
- HC never exceeds the original H/M-derived shortage estimate, the Clarity slider limit, or the +8.0 dB absolute Auto High cap.

### Unchanged

- Low processing is identical to dev.19/dev.13: dry signal plus parallel 60-180 Hz Bass-band addition.
- Bass/Body target remains +6.5 dB and Auto Low absolute maximum remains +6.0 dB.
- H/M target remains -6.0 dB and the existing H/M shortage confidence thresholds remain unchanged.
- Smoothing, startup protection, Master Strength, Width, Ambience, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.
- H/M MAD, T/P MAD, P/M and Crest remain diagnostic-only.

## [0.5.0-dev.19] - 2026-08-22

### Added

- Added diagnostic-only H/M variability using MAD (median absolute deviation) across the existing 12 valid 1-second analysis windows.
- Added diagnostic-only T/P variability using MAD across the same 12-window history used by T/P.
- H/M and T/P are displayed as `median±MAD`.
- Added a coherent H/M stability snapshot so H/M median, MAD, shortage percentage and history count are published from the same analysis update.

### Changed

- Compacted the development diagnostic status line to make room for the variability values.

### Unchanged

- MAD values do not control Auto High or Auto Low.
- Audio processing is identical to dev.18/dev.17.
- Auto High absolute maximum remains +8.0 dB.
- Existing H/M target and all High decision/confidence/smoothing behavior are unchanged.
- Low processing remains the dev.13 parallel 60-180 Hz Bass-band design with Bass/Body target +6.5 dB and Auto Low maximum +6.0 dB.
- T/P, P/M and Crest remain diagnostic-only.
- Width, Ambience, Master Strength, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.

## [0.5.0-dev.18] - 2026-08-22

### Added

- Added diagnostic-only `Crest`, measuring crest factor in the 2-10 kHz high-detail band (upper edge limited to 45% of sample rate when necessary).
- Crest is calculated per valid 1-second window as `20 * log10(peak / RMS)` and displayed as the median of the same 12-window history used by T/P and P/M.
- T/P, P/M and Crest are published together in one coherent 64-bit runtime snapshot.

### Unchanged

- Crest does not control Auto High in dev.18.
- Audio processing is identical to dev.17/dev.16/dev.15.
- Auto High absolute maximum remains +8.0 dB.
- H/M target and all existing High decision/confidence/smoothing logic are unchanged.
- Low processing remains the dev.13 parallel 60-180 Hz Bass-band design with Bass/Body target +6.5 dB and Auto Low maximum +6.0 dB.
- Width, Ambience, Master Strength, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.

## [0.5.0-dev.17] - 2026-08-22

### Added

- Added diagnostic-only `P/M`, defined as Presence (2-5 kHz) energy density divided by Mid (300-2000 Hz) energy density.
- `P/M` is shown next to the existing `T/P` runtime diagnostic.
- `P/M` uses the same pre-Sonic-Refiner source, 1-second valid windows, 12-window history and median display as `T/P`.

### Unchanged

- `P/M` does not control Auto High in dev.17.
- Audio processing is identical to dev.16/dev.15.
- Auto High absolute maximum remains +8.0 dB.
- H/M target and all existing High decision/confidence/smoothing logic are unchanged.
- Low processing remains the dev.13 parallel 60-180 Hz Bass-band design with Bass/Body target +6.5 dB and Auto Low maximum +6.0 dB.
- Width, Ambience, Master Strength, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.

## [0.5.0-dev.16] - 2026-08-22

### Added

- Added a diagnostic-only Presence band at 2-5 kHz.
- Added a diagnostic-only Treble band at 5-10 kHz (upper edge limited to 45% of sample rate when necessary).
- Added `T/P` (Treble/Presence energy-density ratio) to the runtime diagnostic line.
- The diagnostic uses the pre-Sonic-Refiner input and a 12-window median, matching the existing analysis cadence.

### Unchanged

- Audio processing is identical to dev.15.
- Auto High absolute maximum remains +8.0 dB.
- Existing H/M target and all High decision/smoothing logic are unchanged.
- Low processing remains the dev.13 parallel 60-180 Hz Bass-band design with Bass/Body target +6.5 dB and Auto Low maximum +6.0 dB.
- Width, Ambience, Master Strength, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.

## [0.5.0-dev.15] - 2026-08-22

### Changed

- Increased the Adaptive Tone Balance Auto High absolute maximum from +6.0 dB to +8.0 dB.

### Unchanged

- H/M target remains -6.0 dB.
- High shortage-confidence logic, smoothing and timing behavior are unchanged.
- Low processing remains identical to dev.14/dev.13, including the parallel 60-180 Hz Bass-band addition, Bass/Body target +6.5 dB and Auto Low maximum +6.0 dB.
- Width, Ambience, Master Strength, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.


## [0.5.0-dev.13] - 2026-08-22

### Changed

- While Adaptive Tone Balance is ON, Auto Low now preserves the dry signal and adds a filtered 60-180 Hz Bass-band component in parallel.
- Added band scale is derived from the current Auto Low gain as `10^(gain/20) - 1`.
- Adaptive Tone Balance OFF continues to use the original 120 Hz Depth low shelf.

### Fixed

- Normalized the Japanese build wrapper filename to `ビルドと梱包.cmd`.
- Removed mojibake duplicate CMD wrapper filenames from the source package.

### Unchanged

- Bass/Body target remains +6.5 dB.
- Auto Low caps, smoothing, confidence logic and intro protection are unchanged.
- High correction remains H/M-based with target -6.0 dB.
- The paired Input/Post/Delta Bass/Body diagnostic remains enabled.
- Presets, A/B behavior, Width, Ambience, Output Gain, level matching and headroom protection are unchanged.

## [0.5.0-dev.12] - 2026-08-22

### Changed

- While Adaptive Tone Balance is ON, Auto Low now uses a 180 Hz fourth-order Linkwitz-Riley-style low/high crossover.
- Auto Low gain is applied only to the Low branch; the High branch is recombined without Low gain.
- Adaptive Tone Balance OFF continues to use the original 120 Hz Depth low shelf.

### Unchanged

- Bass/Body target remains +6.5 dB.
- Auto Low caps, smoothing, confidence logic and intro protection are unchanged.
- High correction remains H/M-based with target -6.0 dB.
- The paired Input/Post/Delta Bass/Body diagnostic remains enabled.
- Presets, A/B behavior, Width, Ambience, Output Gain, level matching and headroom protection are unchanged.

## [0.5.0-dev.11] - 2026-08-22

### Changed

- While Adaptive Tone Balance is ON, Auto Low now uses two peaking EQs centered at 80 Hz and 150 Hz.
- Both peaks use Q 1.4 and 85% of the current Auto Low gain.
- Adaptive Tone Balance OFF continues to use the original 120 Hz Depth low shelf.

### Unchanged

- Bass/Body target remains +6.5 dB.
- Auto Low caps, smoothing, confidence logic and intro protection are unchanged.
- High correction remains H/M-based with target -6.0 dB.
- The paired Input/Post/Delta Bass/Body diagnostic remains enabled.
- Presets, A/B behavior, Width, Ambience, Output Gain, level matching and headroom protection are unchanged.

## [0.5.0-dev.10] - 2026-08-22

### Changed

- While Adaptive Tone Balance is ON, automatic Low correction now uses a dedicated 110 Hz, Q 1.0 peaking EQ.
- Adaptive Tone Balance OFF continues to use the original 120 Hz Depth low shelf.

### Unchanged

- Bass/Body decision target remains +6.5 dB.
- Auto Low caps, smoothing, confidence logic and intro protection are unchanged.
- High correction remains H/M-based with target -6.0 dB.
- The paired Input/Post/Delta Bass/Body diagnostic remains enabled.
- Presets, A/B behavior, Width, Ambience, Output Gain, level matching and headroom protection are unchanged.

## [0.5.0-dev.9] - 2026-08-22

### Changed

- While Adaptive Tone Balance is ON, automatic Low correction now uses a 180 Hz low shelf instead of the legacy 120 Hz shelf.
- Adaptive Tone Balance OFF continues to use the original 120 Hz Depth shelf.

### Unchanged

- Bass/Body target remains +6.5 dB.
- Auto Low gain calculation, caps, smoothing, confidence logic and intro protection are unchanged.
- High correction remains H/M-based with target -6.0 dB.
- The paired Input/Post/Delta Bass/Body diagnostic from dev.8 remains enabled.
- Presets, A/B storage, Width, Ambience, Output Gain, level matching and headroom behavior are unchanged.

## [0.5.0-dev.8] - 2026-08-22

### Added

- Added a paired, measurement-only Bass/Body analyzer before and immediately after the Depth/Clarity tone-filter stage.
- Added diagnostic display of Input Bass/Body, Post Bass/Body, and Delta.
- Paired values are accumulated from the same frames and published coherently.

### Unchanged

- Audible DSP and Adaptive Tone Balance behavior are unchanged from v0.5.0-dev.7.
- Low target remains Bass/Body +6.5 dB.
- High target remains H/M -6.0 dB.
- Gain caps, smoothing, intro protection, presets, A/B, headroom protection, and level matching are unchanged.

## [0.5.0-dev.7] - 2026-08-22

### Changed

- Low automatic correction now uses Bass/Body (60-180 Hz / 200-500 Hz) instead of L/M as its primary decision metric.
- Added a provisional Bass/Body target of +6.5 dB for development listening tests.
- L/M remains diagnostic-only.

### Unchanged

- High correction remains H/M-based with target -6.0 dB.
- Boost caps, tolerance, confidence thresholds, smoothing, intro protection, presets, A/B behavior, headroom protection, and level matching are unchanged from v0.5.0-dev.6.

## [0.5.0-dev.6] - 2026-08-22

### Added

- Added a diagnostic-only Bass band (60-180 Hz).
- Added a bandwidth-corrected Bass/Body diagnostic ratio using Body 200-500 Hz.
- Included Bass/Body in the coherent single-atomic diagnostic snapshot.

### Unchanged

- Adaptive Tone Balance targets, gain decisions, audible processing, preset behavior, and A/B behavior remain unchanged from v0.5.0-dev.5.

## [0.5.0-dev.5] - 2026-08-22

### Fixed

- Made the development diagnostic data a single coherent 64-bit atomic snapshot.
- Prevented L/M, Body/Core, H/M, shortage percentages, and history count from being mixed across different analysis updates.
- Adaptive Tone Balance audio/correction behavior remains unchanged from v0.5.0-dev.4.

## [0.5.0-dev.4] - 2026-08-22

### Diagnostic

- Added Body 200–500 Hz / Core 500 Hz–2 kHz diagnostic analysis.
- Added Body/Core median ratio to the development diagnostic line.
- Adaptive Tone Balance correction logic remains identical to v0.5.0-dev.3.

## [0.5.0-dev.3] - 2026-08-22

### Added

- Added a temporary Adaptive Tone Balance diagnostic readout for real-world tuning.
- The bottom status line now shows the current median Low/Mid and High/Mid analysis values, configured targets, shortage-window percentages, and valid history count.
- Diagnostic data is runtime-only and is not stored in DSP presets, user presets, A/B slots, or `.srpbackup` files.
- No intended Adaptive Tone Balance algorithm or target change from v0.5.0-dev.2.

## [0.5.0-dev.2] - 2026-08-22

### Fixed

- Fixed Visual Studio C2275 / C2737 in the Adaptive Tone Balance analysis-window size calculation.
- Corrected the `std::max` call syntax for `window_frame_target`.
- No intended DSP behavior change from v0.5.0-dev.1.

## [0.5.0-dev.1] - 2026-08-22

### Added

- Added **Adaptive Tone Balance** (適応型音色補正), disabled by default.
- Added boost-only source-dependent low/high correction using the original pre-processing signal.
- Analysis bands: Low 60-250 Hz, Mid reference 300 Hz-2.0 kHz, High 3.5-10 kHz.
- Targets: Low = Mid +3 dB, High = Mid -6 dB, with 1.5 dB tolerance.
- Safety limits: Auto Depth up to +6.0 dB and Auto Clarity up to +4.0 dB.
- Added compact live status for Off / Waiting / Analyzing / applied Low & High correction.
- Added Adaptive Tone Balance On/Off state to A/B slots, user presets and preset backups.
- User-preset write format advanced to SRP4 and foobar2000 DSP preset format to `preset_version 9`.

### Behavior

- With Adaptive Tone Balance Off, Depth and Clarity retain the v0.4.0 fixed behavior.
- With Adaptive Tone Balance On, Depth and Clarity act as maximum automatic-correction limits.
- Width and Ambience remain manual. Master Strength also scales the adaptive correction.
- The analyzer uses lightweight IIR/Biquad filters rather than FFT.
- Runtime analysis history is never serialized.
- Track changes, seeks and Stop reset analysis; Pause/Resume preserves it.
- Existing 11 built-in presets explicitly keep Adaptive Tone Balance Off.

### Compatibility

- SRP1, SRP2 and SRP3 remain readable; legacy user presets load Adaptive Tone Balance as Off.
- Legacy DSP preset versions 1-8 remain readable; Adaptive Tone Balance defaults to Off.
- Existing `.srpbackup` files remain importable.
- Recommended DSP order remains Sonic Refiner -> R128 Real-time Loudness Normalizer -> Output.

## [0.4.0] - 2026-08-22

### Added
- Temporary A/B comparison slots for Depth, Clarity, Width, Ambience, and Master Strength.
- Playback menu command for direct Sonic Refiner settings access.
- Modeless owned direct-settings window and Keyboard Shortcuts integration.
- Safety checks for missing/multiple active instances and runtime DSP-chain changes.

### Fixed
- Finalized A/B layout readability and group-border rendering in Japanese/English Light/Dark modes.
- Fixed the C3246 service-registration build error found during direct-settings development.

### Compatibility
- DSP processing remains unchanged from v0.3.0.
- SRP3, `preset_version 8`, `.srpbackup`, and existing preset compatibility are unchanged.

## [0.4.0-dev.5] - 2026-08-22

### Fixed
- Fixed the Visual Studio C3246 build failure in the direct-settings main-menu command registration.
- Removed the invalid `final` qualifier from `mainmenu_commands_sonic_refiner_settings`; foobar2000 SDK service registration wraps and derives from this command class.

### Compatibility
- Direct-settings behavior is otherwise unchanged from v0.4.0-dev.4.
- DSP processing, A/B comparison, SRP3, `preset_version 8`, and `.srpbackup` are unchanged.

## [0.4.0-dev.4] - 2026-08-22

### Added
- Playback menu command for direct Sonic Refiner settings access.
- Modeless owned settings window so foobar2000 remains usable while editing.
- Keyboard Shortcuts integration through the main-menu command.
- Safety checks for missing or multiple Sonic Refiner instances in the active DSP chain.
- Runtime detection if the target Sonic Refiner is removed or duplicated while direct editing is open.

### Compatibility
- DSP processing is unchanged from v0.4.0-dev.3.
- SRP3, preset_version 8 and .srpbackup remain unchanged.
- The conventional DSP Manager configuration path remains available.

All notable public changes to Sonic Refiner are documented here.

## [0.4.0-dev.3] - 2026-08-22

### Fixed
- Prevented the lower-left border of the Master/Output/Protection group from being erased by the extreme-range notice control.
- Kept the settings window at 560 x 320 with no A/B or DSP behavior changes.

## [0.4.0-dev.2] - 2026-08-22

### Fixed
- Improved disabled End Comparison button readability in dark mode.
- Adjusted A/B and Master/Output/Protection layout spacing while retaining the 560 x 320 settings window.

## [0.4.0-dev.1] - 2026-08-22

### Added
- Temporary A/B comparison slots for Depth, Clarity, Width, Ambience, and Master Strength
- Instant A/B listening with restoration of the settings present before comparison began
- Japanese/English A/B comparison controls and status text

### Compatibility
- DSP processing algorithm is unchanged from v0.3.0
- `preset_version 8` remains unchanged
- User-preset write format remains `SRP3`
- `.srpbackup` format remains unchanged
- A/B slots are held only in memory and are cleared when foobar2000 exits

## [0.3.0] - 2026-08-06

### Added

- Japanese and English user interface
- Language selection based on the Windows display language on first use
- Instant language switching without restarting foobar2000
- Persistent language preference stored separately from DSP settings
- Localized built-in preset names, controls, messages, file dialogs, Help, Glossary, Important Notes and License pages
- English-first public documentation

### Compatibility

- DSP processing behavior is unchanged from v0.2.0
- `preset_version 8` remains unchanged
- User-preset format remains `SRP3`
- SRP1, SRP2 and SRP3 remain readable
- `.srpbackup` format remains unchanged
- Existing user-preset names are preserved and are not translated
- Settings window remains 560 × 320

### Validation

- Release / x64 build and package creation confirmed
- Japanese and English switching confirmed without restart or crash
- User-preset save/load and backup export/import confirmed
- Light and dark modes, restart persistence, cancellation, and continuous playback operation confirmed

## [0.2.0] - 2026-08-03

### Added

- Master Strength control from 0% to 100%
- Effective-value labels that reflect Master Strength
- SRP3 user-preset format with Master Strength storage
- Integrated Help, Glossary and Safety Notice documentation for Master Strength

### Compatibility

- v0.1.x DSP settings load with Master Strength at 100%
- SRP1 and SRP2 user presets load with Master Strength at 100%
- Output Gain, Automatic Headroom and Level Match are not scaled
- Existing built-in presets retain their original sound at 100%
- Confirmed operation at 0%, 50% and 100%, preset save/restore, backup import/export, restart persistence, cancellation, light/dark modes and continuous playback control

## [0.1.1] - 2026-08-02

### Changed

- Unified the official downstream normalizer name as
  `R128 Real-time Loudness Normalizer`
- Updated the integrated Help, Glossary and Safety Notices
- Updated README, Quick Start, component package documentation and release notes
- Updated the formal package version and filename to `v0.1.1`

### Compatibility

- No DSP processing behavior was changed
- No preset values or preset file formats were changed
- Existing settings and SRP1/SRP2 user presets remain compatible

## [0.1.0] - 2026-08-02

### Added

- Initial public release
- Depth low-frequency enhancement
- Clarity high-frequency enhancement
- Frequency-dependent stereo Width processing with low-frequency protection
- Short early-reflection Ambience processing
- Output Gain from -12.0 dB to +6.0 dB
- Automatic headroom protection
- Level-matched bypass comparison
- Eleven built-in presets
- Up to 20 user presets
- User-preset export and import using `.srpbackup`
- Integrated Help, Glossary, Safety Notices and License pages
- Light and dark mode support
- Automated Release/x64 build and `.fb2k-component` packaging
- SHA-256 checksum generation

### Compatibility

- Reads legacy preview DSP settings
- Reads SRP1 and SRP2 user-preset formats
- Legacy settings without Output Gain load at 0.0 dB

### Notes

- Values from 80% to 100% are intended for strong effects and testing.
- Automatic Headroom is not a True Peak limiter.
- Recommended DSP order:
  `Sonic Refiner -> R128 Real-time Loudness Normalizer -> output`
