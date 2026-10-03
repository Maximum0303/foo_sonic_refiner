# Sonic Refiner v0.8.3 Release Notes

## English

v0.8.3 formalizes the validated v0.8.3-dev.2 display-language update based on the official v0.8.2 source.

### Display language

- Adds **Automatic (Windows)** alongside **Japanese / English**.
- Automatic follows the Windows UI language: Japanese for Japanese Windows UI, English otherwise.
- Manual Japanese / English selections override Automatic.
- New installations default to Automatic; existing saved manual `ja` / `en` choices are preserved.
- Language preference remains separate from DSP presets.
- Standardizes the settings label as **Display language** / **表示言語**.
- Adjusts the label/control layout so **Display language** is not clipped in English.

### Validated in v0.8.3-dev.2

- Automatic (Windows) displayed and resolved correctly on a Japanese Windows UI.
- Immediate switching between Japanese and English passed.
- Automatic, English, and Japanese modes each remained selected after restarting foobar2000.
- Loading a built-in preset did not change the display-language preference.
- Normal one-track playback passed without reported sound dropout, abnormal level movement, noise, or ATB / Reverb regression.
- Validated dev component SHA-256: `b67ac81a8bd9b04b9cc5b6c9b44b80a18343216354a1afcbf0cc8ff331fcce9c`.

### Compatibility

- Audio processing is unchanged from v0.8.2.
- Built-in preset parameter values are unchanged.
- SRP5, `preset_version 10`, `.srpbackup`, ATB, Reverb, and legacy compatibility are unchanged.

---

## 日本語

v0.8.3は、正式v0.8.2ソースを基準に実機検証したv0.8.3-dev.2の表示言語更新を正式版化したものです。

### 表示言語

- **「自動（Windows）／日本語／English」** の3択に対応。
- 自動（Windows）はWindows UIが日本語なら日本語、それ以外はEnglishを使用。
- 日本語／Englishを手動選択した場合は自動判定より優先。
- 新規環境の初期値は自動（Windows）。既存の手動 `ja` / `en` 設定は維持。
- 言語設定はDSPプリセットとは別に保存。
- 設定画面の項目名を **「表示言語」／「Display language」** に統一。
- English表示で **Display language** が欠けないようラベル／コントロール配置を調整。

### v0.8.3-dev.2で確認済み

- 日本語Windows UIで自動（Windows）が日本語表示になることを確認。
- 日本語／Englishの即時切り替えを確認。
- 自動（Windows）／English／日本語の各モードがfoobar2000再起動後も保持されることを確認。
- 内蔵プリセットを読み込んでも表示言語設定が変わらないことを確認。
- 1曲通常再生し、音切れ、異常な音量変動、ノイズ、ATB／Reverbの異常なし。
- 検証済みdev component SHA-256：`b67ac81a8bd9b04b9cc5b6c9b44b80a18343216354a1afcbf0cc8ff331fcce9c`。

### 互換性

- 音声処理はv0.8.2から変更なし。
- 内蔵プリセットの設定値は変更なし。
- SRP5、`preset_version 10`、`.srpbackup`、ATB、Reverb、旧形式互換は変更なし。
