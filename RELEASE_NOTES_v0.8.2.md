# Sonic Refiner v0.8.2 Release Notes

## English

v0.8.2 formalizes the validated v0.8.2-dev.1 gain-ceiling update based on the official v0.8.1 source.

### Changed

- Fixed Depth at 100% now maps to a maximum of **+15.0 dB** instead of +16.0 dB.
- Fixed Clarity at 100% now maps to a maximum of **+15.0 dB** instead of +14.0 dB.
- ATB Auto Low absolute maximum is raised from **+10.0 dB to +15.0 dB**.
- ATB Auto High absolute maximum is raised from **+10.0 dB to +15.0 dB**.
- Help / Glossary / Important Notes and user documentation describe the unified +15.0 dB ATB ceiling.

### Validated in v0.8.2-dev.1

- Adaptive Standard reached **+15.0 dB** in actual playback.
- One-track Adaptive Standard listening test completed without audible clipping, bass breakup, treble harshness, abnormal level movement, or excessive Auto Headroom reduction.
- Fixed-mode Full Boost listening test completed without audible clipping, low-frequency breakup, treble harshness, or abnormal Auto Headroom reduction.
- Settings and display remained normal after restarting foobar2000.
- Validated dev component SHA-256: `009723c8f9e70b3c9d582aded1e9804e9d4dc1455ca2191e68764af91a11d141`.

### Compatibility

- ATB analysis, shortage decision logic, history, increase / release rates, startup protection, and boost-only behavior are unchanged.
- Width, Ambience, Reverb, Master Strength, Output Gain, Auto Headroom, Level-Matched Bypass, A/B, and Preset Manager behavior are unchanged.
- The 16 built-in preset **parameter values** are unchanged; presets using Depth or Clarity at 100% can sound slightly different because the 100% gain mapping changed.
- SRP5, `preset_version 10`, `.srpbackup`, and legacy compatibility are unchanged.

---

## 日本語

v0.8.2は、正式v0.8.1ソースを基準に実機検証したv0.8.2-dev.1のゲイン上限変更を正式版化したものです。

### 変更点

- 固定Depth 100%の最大ゲインを **+16.0 dB → +15.0 dB** に変更。
- 固定Clarity 100%の最大ゲインを **+14.0 dB → +15.0 dB** に変更。
- ATB Auto Lowの絶対上限を **+10.0 dB → +15.0 dB** に変更。
- ATB Auto Highの絶対上限を **+10.0 dB → +15.0 dB** に変更。
- Help／用語集／注意事項とユーザー向け文書を、統一したATB最大+15.0 dBに合わせて更新。

### v0.8.2-dev.1で確認済み

- 実再生で適応型標準が **+15.0 dB** に到達することを確認。
- 適応型標準で1曲通して試聴し、音割れ、低域の破綻、高域の刺さり、不自然な音量変動、Auto Headroomの過剰な音量低下なし。
- 固定モードのフルブーストでも、音割れ、低域の破綻、高域の刺さり、不自然なAuto Headroom低下なし。
- foobar2000再起動後も設定・表示が正常に保持。
- 検証済みdev component SHA-256：`009723c8f9e70b3c9d582aded1e9804e9d4dc1455ca2191e68764af91a11d141`。

### 互換性

- ATBの解析、補正量判定、履歴、増加／減少速度、開始時保護、boost-only動作は変更なし。
- Width、Ambience、Reverb、Master Strength、Output Gain、Auto Headroom、Level-Matched Bypass、A/B、Preset Managerの動作は変更なし。
- 16内蔵プリセットの**設定値そのもの**は変更なし。ただしDepthまたはClarityが100%のプリセットは100%時の実ゲイン対応が変わるため音がわずかに変化する可能性があります。
- SRP5、`preset_version 10`、`.srpbackup`、旧形式互換は変更なし。
