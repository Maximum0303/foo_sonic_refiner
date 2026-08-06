Sonic Refiner 0.3.0
Adaptive Audio Enhancement DSP for foobar2000

This release adds a Japanese/English user interface. DSP processing behavior
is unchanged from v0.2.0.

LANGUAGE SUPPORT
- Japanese and English settings UI
- Default selected from the Windows display language on first use
- Instant switching without restarting foobar2000
- The selected language is remembered separately from DSP presets
- Built-in preset names, controls, messages, file dialogs, Help, Glossary,
  Important Notes, and License pages are localized
- Existing user-preset names are preserved and are not translated

MAIN FEATURES
- Depth around 120 Hz, up to approximately +16 dB
- Clarity above approximately 3.5 kHz, up to approximately +14 dB
- Mid/Side Width with low-frequency protection, up to Side 600%
- 11 ms and 19 ms early-reflection Ambience, up to 85% Wet Mix
- Master Strength from 0% to 100%
- Output Gain from -12.0 dB to +6.0 dB in 0.5 dB steps
- Auto Headroom Protection around -0.2 dBFS block peak
- Level-Matched Bypass
- Eleven built-in presets
- Up to 20 UTF-8 user presets
- .srpbackup export and import
- Light and dark mode support

RECOMMENDED DSP ORDER
Sonic Refiner -> R128 Real-time Loudness Normalizer -> Output

COMPATIBILITY
- DSP preset_version remains 8
- User-preset format remains SRP3
- SRP1, SRP2, and SRP3 remain readable
- .srpbackup format is unchanged
- Legacy settings and user presets remain compatible

IMPORTANT
Values from 80% to 100% are intended for extreme effects and testing.
Auto Headroom Protection is not a True Peak limiter. Lower the listening volume
before testing extreme settings.

LICENSE
MIT License. Copyright (c) 2026 Maximum.
The full license is included as MIT_LICENSE.txt and is also available from the
component's License page.

------------------------------------------------------------

日本語

Sonic Refiner 0.3.0は、日本語／英語表示に対応した正式版です。
DSPの音声処理はv0.2.0から変更していません。

- 初回はWindowsの表示言語から日本語／英語を選択
- 設定画面を閉じずに即時切り替え
- 言語設定はDSP presetや任意プリセットとは別に保存
- 内蔵プリセット名、操作項目、確認・エラー表示、ファイル選択、
  ヘルプ、用語集、注意事項、ライセンスを切り替え
- 既存の任意プリセット名は翻訳せず維持
- preset_version 8、SRP3、.srpbackup互換性を維持

推奨DSP順序:
Sonic Refiner -> R128 Real-time Loudness Normalizer -> Output
