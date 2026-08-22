Sonic Refiner 0.5.0
Adaptive Audio Enhancement DSP for foobar2000
Formal release / 正式版

ENGLISH

Sonic Refiner combines tone and soundstage enhancement with optional
Adaptive Tone Balance (ATB). ATB is OFF by default, so the existing fixed
Depth / Clarity behavior is preserved until ATB is enabled.

ADAPTIVE TONE BALANCE
- Analyzes the original signal before Sonic Refiner processing
- Auto Low decision: Bass 60-180 Hz vs Body 200-500 Hz
- Bass/Body target: +6.5 dB
- Auto Low processing: dry signal + parallel filtered 60-180 Hz Bass addition
- Auto High primary balance: 3.5-10 kHz vs 300 Hz-2.0 kHz
- Auto High secondary balance: 5-10 kHz vs 2-5 kHz
- High/Mid shortage reference: -6 dB, tolerance 1.5 dB
- Boost only; no automatic cuts
- Auto Low absolute maximum: +10.0 dB
- Auto High absolute maximum: +10.0 dB
- With ATB ON, Depth and Clarity act as maximum permissions for automatic correction
- Master Strength scales the final automatic correction
- Slow rolling analysis and gain movement reduce pumping
- Input below approximately -55 dBFS does not update analysis
- Track changes, seeks, Stop and ATB Off->On restart analysis
- Pause/Resume preserves analysis
- Multichannel analysis uses the first L/R pair

PRESETS AND A/B
- Existing 11 built-in presets remain unchanged and load ATB OFF
- Existing built-in presets can be used normally; enable ATB afterward if desired
- User presets save the ATB On/Off state
- A/B stores the ATB On/Off state
- A/B slots remain runtime-only and are cleared when foobar2000 exits
- Runtime analyzer history and live Auto Low/High values are not persisted

PRESETS AND COMPATIBILITY
- DSP write format: preset_version 9
- User-preset write format: SRP4
- SRP1, SRP2, SRP3 and SRP4 are readable
- Legacy DSP preset versions 1-8 remain readable
- Legacy data without an ATB field loads ATB OFF
- New .srpbackup files include ATB On/Off
- Older .srpbackup files remain importable

OTHER FEATURES
- Depth around 120 Hz, up to approximately +16 dB in fixed mode
- Clarity above approximately 3.5 kHz, up to approximately +14 dB in fixed mode
- Mid/Side Width with low-frequency protection, up to Side 600%
- 11 ms and 19 ms early-reflection Ambience, up to 85% Wet Mix
- Master Strength from 0% to 100%
- Output Gain from -12.0 dB to +6.0 dB in 0.5 dB steps
- Auto Headroom Protection around -0.2 dBFS block/sample peak
- Level-Matched Bypass
- Eleven built-in presets
- Up to 20 UTF-8 user presets
- Direct settings access from the Playback menu
- Keyboard Shortcuts support
- Japanese/English UI
- Light and dark mode support

RECOMMENDED DSP ORDER
Sonic Refiner -> R128 Real-time Loudness Normalizer -> Output

IMPORTANT
Adaptive Tone Balance is a tonal balance helper, not a loudness normalizer,
AGC, True Peak limiter, or restoration tool. Auto Headroom Protection is not
a True Peak limiter. The downstream R128 Real-time Loudness Normalizer remains
responsible for final loudness and True Peak management.

LICENSE
MIT License. Copyright (c) 2026 Maximum.
The full license is included as MIT_LICENSE.txt and is also available from the
component's License page.

------------------------------------------------------------

日本語

Sonic Refiner 0.5.0では、従来の音色・音場補正に
「適応型音色補正（Adaptive Tone Balance / ATB）」を追加しました。
ATBの初期値はオフなので、有効にするまでは従来の固定Depth／Clarity動作です。

適応型音色補正
- Sonic Refiner処理前の原音を解析
- Auto Low判定：Bass 60～180 Hz 対 Body 200～500 Hz
- Bass/Body目標：+6.5 dB
- Auto Low処理：原音 + フィルターした60～180 Hz Bass成分の並列加算
- Auto High主判定：3.5～10 kHz 対 300 Hz～2.0 kHz
- Auto High補助判定：5～10 kHz 対 2～5 kHz
- High/Mid不足判定基準：-6 dB、許容1.5 dB
- 不足分のブーストのみ。自動カットなし
- Auto Low絶対上限：+10.0 dB
- Auto High絶対上限：+10.0 dB
- ATB ON時はDepth／Clarityが自動補正の上限として動作
- Master Strengthは自動補正にも適用
- ゆっくりした解析と追従でポンピングを抑制
- 約-55 dBFS未満では解析を更新しない
- 曲変更・シーク・Stop・ATB OFF->ONで解析をやり直す
- Pause/Resumeでは解析を保持
- マルチチャンネル解析は最初のL/Rを使用

プリセットとA/B
- 既存11種類の内蔵プリセットは変更せず、呼び出し時はATB OFF
- 既存プリセットをそのまま使い、必要な場合だけATBをONにして使用可能
- 任意プリセットにはATBのON/OFFも保存
- A/BにもATBのON/OFFを保存
- A/Bスロットはメモリ上のみで、foobar2000終了時に消去
- 解析履歴や現在のAuto Low／High値は保存しない

プリセット互換性
- DSP書き込み形式：preset_version 9
- 任意プリセット書き込み形式：SRP4
- SRP1／SRP2／SRP3／SRP4を読み込み可能
- 旧DSP preset version 1～8を読み込み可能
- ATB項目を持たない旧データはATB OFFとして読み込む
- 新しい.srpbackupにはATB ON/OFFを含む
- 旧.srpbackupも引き続き読み込み可能

推奨DSP順序
Sonic Refiner -> R128 Real-time Loudness Normalizer -> Output

注意
Adaptive Tone Balanceは音色バランス補助であり、ラウドネスノーマライズ、
AGC、True Peakリミッター、音源修復機能ではありません。
最終的なラウドネスとTrue Peak管理は従来どおり
R128 Real-time Loudness Normalizerが担当します。

ライセンス
MIT License. Copyright (c) 2026 Maximum.
