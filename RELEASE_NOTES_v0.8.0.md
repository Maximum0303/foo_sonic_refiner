# Sonic Refiner v0.8.0 Release Notes

## English

Sonic Refiner v0.8.0 adds a dedicated late-Reverb stage while keeping the existing Ambience stage as early reflections. It also adds four venue-oriented built-in presets and preserves compatibility with older presets and backups.

### Highlights

- New **Reverb** control (0-100).
- Reverb naturally decays through silent passages instead of stopping abruptly.
- Track-end tail rendering lets a cut-off ending decay naturally before playback fully ends.
- Existing **Ambience** behavior remains the early-reflection / room-impression stage.
- Four new built-in venue presets:
  - **Adaptive Hall** — Width 60 / Ambience 55 / Reverb 50
  - **Adaptive Arena** — Width 72 / Ambience 65 / Reverb 68
  - **Adaptive Dome** — Width 85 / Ambience 75 / Reverb 85
  - **Adaptive Open Air** — Width 75 / Ambience 20 / Reverb 10

### Preset compatibility

- DSP presets use `preset_version 10`.
- User presets use SRP5.
- SRP1-SRP4 and DSP preset versions 1-9 remain readable.
- Older presets load with Reverb = 0, preserving their previous sound.
- Existing 12 built-in presets remain Reverb = 0.
- Existing `.srpbackup` files remain restorable.
- The `.srpbackup` outer header remains `SONIC_REFINER_PRESET_BACKUP_V1`.

### Validated behavior

The v0.8.0-dev.3 baseline was tested for venue-preset differences, track-end Reverb tails, next-track isolation, seek/stop/pause handling, A/B comparison, Auto Headroom behavior, restart persistence, SRP5 save/load, backup/restore, SRP4 backward compatibility, and Japanese/English UI.

---

## 日本語

Sonic Refiner v0.8.0では、従来のAmbienceを「初期反射」として維持したまま、その後段に独立した**Reverb（残響・余韻）**を追加しました。さらに、ホール／アリーナ／ドーム／野外を想定した4つの内蔵プリセットを追加し、旧プリセット・旧バックアップとの互換性も維持しています。

### 主な追加・変更

- 新しい **Reverb** コントロール（0～100）。
- 曲中の無音部分でも、残響が不自然に途切れず自然に減衰。
- カットアウト気味に終わる曲でも、曲末の残響テールを追加出力して自然な余韻を再現。
- 従来の **Ambience** は初期反射・空間感の役割をそのまま維持。
- 4つの新しい内蔵プリセット：
  - **適応型ホール** — Width 60 / Ambience 55 / Reverb 50
  - **適応型アリーナ** — Width 72 / Ambience 65 / Reverb 68
  - **適応型ドーム** — Width 85 / Ambience 75 / Reverb 85
  - **適応型野外** — Width 75 / Ambience 20 / Reverb 10

### プリセット互換性

- DSP presetは `preset_version 10`。
- 任意プリセットはSRP5。
- SRP1～SRP4、DSP preset version 1～9を引き続き読み込み可能。
- 旧プリセット読込時はReverb = 0として扱い、従来の音を維持。
- 既存12内蔵プリセットはReverb = 0のまま。
- 旧`.srpbackup`も引き続き復元可能。
- `.srpbackup`外側ヘッダーは`SONIC_REFINER_PRESET_BACKUP_V1`のまま変更なし。

### 確認済み項目

v0.8.0-dev.3を基準に、会場プリセットの段階差、曲末Reverbテール、次曲への持ち越し防止、シーク／停止／一時停止、A/B比較、Auto Headroom、再起動後の保持、SRP5保存・読込、バックアップ／復元、旧SRP4互換、日本語／英語UIを確認済みです。
