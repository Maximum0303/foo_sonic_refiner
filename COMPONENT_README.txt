Sonic Refiner v0.8.1
Adaptive Audio Enhancement DSP for foobar2000

============================================================
ENGLISH
============================================================

Sonic Refiner is a real-time tone and soundstage enhancement DSP for
foobar2000 2.x on Windows x64.

CURRENT STABLE RELEASE
v0.8.1

V0.8.1 DOCUMENTATION REFRESH
- User-facing guidance only; audio processing is unchanged from v0.8.0.
- Natural -18 is documented as the recommended R128 starting point.
- Standard R128 normalization presets are distinguished from additional mastering presets.
- DSP algorithms, venue preset values, SRP5, preset_version 10, and legacy compatibility are unchanged.

MAIN FUNCTIONS
- Depth
- Clarity
- Adaptive Tone Balance (ATB)
- Width
- Ambience
- Reverb
- Master Strength
- Output Gain
- Auto Headroom Protection
- Level-Matched Bypass
- A/B comparison
- Preset Manager
- Up to 20 user presets
- .srpbackup backup / restore
- Japanese / English UI
- foobar2000 Light / Dark mode support

V0.8.0 REVERB
v0.8.0 keeps the existing Ambience stage as short early reflections and
adds an independent late-Reverb stage after it.

Width     = stereo spread
Ambience  = early reflections / immediate room impression
Reverb    = late reflections / decay / tail

Reverb range: 0-100.

Reverb naturally decays through silent passages.
At track end, Sonic Refiner can emit a Reverb tail so that a cut-off ending
decays naturally before playback fully ends.

Reverb state is reset at track boundaries, seeks, Stop, and other playback
discontinuities so that the previous track's tail does not leak into the next.

With Reverb = 0, the Reverb processor is effectively disabled and older
Sonic Refiner sound is preserved.

NEW V0.8.0 VENUE PRESETS
- Adaptive Hall
  Width 60 / Ambience 55 / Reverb 50
- Adaptive Arena
  Width 72 / Ambience 65 / Reverb 68
- Adaptive Dome
  Width 85 / Ambience 75 / Reverb 85
- Adaptive Open Air
  Width 75 / Ambience 20 / Reverb 10

BUILT-IN PRESETS
1. Standard
2. Bass Boost
3. Vocal Focus
4. Wide
5. Live
6. Headphones
7. Extreme Bass
8. Extreme Clarity
9. Extreme Wide
10. Large Hall
11. Full Boost
12. Adaptive Standard
13. Adaptive Hall
14. Adaptive Arena
15. Adaptive Dome
16. Adaptive Open Air

The original 12 presets keep Reverb = 0.
Custom is a UI state, not a 17th built-in preset.

ADAPTIVE TONE BALANCE
ATB is Off by default.

ATB Off:
- Depth / Clarity use the fixed processing behavior.

ATB On:
- Depth becomes the Auto Low correction limit.
- Clarity becomes the Auto High correction limit.
- 100% means maximum permission, not a constant +10 dB boost.
- Automatic correction is boost-only; no automatic cuts.
- Auto Low absolute maximum: +10 dB.
- Auto High absolute maximum: +10 dB.
- Runtime analysis values are not persisted.

PRESET MANAGER
The Preset Manager supports:
- Search
- Read-only preview
- Current-setting match marker
- New from Current
- Update from Current
- Duplicate
- Rename
- Delete
- Backup / Restore
- Up / Down reordering
- Alt+Up / Alt+Down
- Drag & Drop
- Right-click menu
- Double-click Apply
- Keyboard shortcuts
- Resizable two-pane layout
- Japanese / English and Light / Dark modes

PROCESSING ORDER
Depth / Clarity / ATB
-> Width
-> Ambience
-> Reverb
-> Level-Matched Bypass
-> Output Gain
-> Auto Headroom
-> Output

RECOMMENDED DSP ORDER
Sonic Refiner
-> R128 Real-time Loudness Normalizer
-> Output

Sonic Refiner handles tone and soundstage.
R128 Real-time Loudness Normalizer handles final loudness, LUFS, True Peak
management, and limiting.

RECOMMENDED R128 PRESET
For normal music listening, start with:

Sonic Refiner
-> R128 Real-time Loudness Normalizer: Natural -18
-> Output

As of 2026-10-03, R128 Real-time Loudness Normalizer v1.11.0 has these
built-in presets.

Standard normalization:
- Natural -18
- Power Boost -14
- Relaxed -23
- Night Safe -22

Use the standard four presets when transparent loudness matching is the
priority. Natural -18 is the recommended starting point.

Additional mastering processing:
- Modern Boost -9
  Compression + soft clipping + True Peak limiting.
- 1-Band Adaptive -10
  Automatically adjusts Modern Processing strength from loudness / LRA.
- 3-Band Adaptive -10
  Controls low / mid / high bands independently.
  Approximate crossover boundaries: 160 Hz / 4 kHz.

The three additional mastering presets affect tone and dynamics as well as
loudness. Use them only when that extra processing is desired.

3-Band Adaptive may overlap with Sonic Refiner Depth / Clarity / ATB because
it processes low, mid, and high bands independently.

PRESET COMPATIBILITY
- DSP write format: preset_version 10
- User-preset write format: SRP5
- SRP1 / SRP2 / SRP3 / SRP4 / SRP5 readable
- DSP preset versions 1-10 readable
- Older presets without Reverb load with Reverb = 0
- Older .srpbackup files remain restorable
- .srpbackup outer header remains:
  SONIC_REFINER_PRESET_BACKUP_V1

INSTALLATION
1. Install foo_sonic_refiner_v0.8.0.fb2k-component.
2. Restart foobar2000.
3. Add Sonic Refiner in DSP Manager.
4. If R128 Real-time Loudness Normalizer is used, place it after Sonic Refiner.

LICENSE
MIT License
Copyright (c) 2026 Maximum


============================================================
日本語
============================================================

Sonic Refinerは、foobar2000 2.x（Windows x64）向けの
リアルタイム音色・音場補正DSPです。

現在の正式公開版
v0.8.1

V0.8.1 説明更新
- ユーザー向け説明のみの更新で、音声処理はv0.8.0から変更していません。
- R128側の基本推奨として「ナチュラル -18」を明記します。
- R128の標準ノーマライズと追加マスタリング処理の違いを明確化します。
- DSPアルゴリズム、会場プリセット値、SRP5、preset_version 10、旧形式互換は変更しません。

主な機能
- Depth
- Clarity
- Adaptive Tone Balance（ATB）
- Width
- Ambience
- Reverb
- Master Strength
- Output Gain
- Auto Headroom Protection
- Level-Matched Bypass
- A/B比較
- Preset Manager
- 任意プリセット最大20件
- .srpbackupバックアップ／復元
- 日本語／英語UI
- foobar2000 Light／Darkモード対応

V0.8.0 REVERB
v0.8.0では、従来のAmbienceを短い初期反射として維持し、
その後段に独立したReverbを追加しました。

Width     = 左右方向の広がり
Ambience  = 初期反射・すぐ近くの空間感
Reverb    = 後期残響・余韻・テール

Reverbの範囲は0～100です。

曲中の無音でもReverbは自然に減衰します。
カットアウト気味の曲末では残響テールを追加出力し、
再生終了前に自然な余韻を作ります。

曲境界、シーク、Stopなどでは残響状態をリセットし、
前の曲の余韻が次の曲へ不自然に持ち越されないようにします。

Reverb = 0ではReverb処理が実質OFFとなり、
従来のSonic Refinerの音を維持します。

V0.8.0 新会場プリセット
- 適応型ホール
  Width 60 / Ambience 55 / Reverb 50
- 適応型アリーナ
  Width 72 / Ambience 65 / Reverb 68
- 適応型ドーム
  Width 85 / Ambience 75 / Reverb 85
- 適応型野外
  Width 75 / Ambience 20 / Reverb 10

内蔵プリセット
1. 標準
2. 低域強化
3. ボーカル重視
4. ワイド
5. ライブ
6. ヘッドホン
7. 超低域強化
8. 超明瞭
9. 超ワイド
10. 大ホール
11. フルブースト
12. 適応型標準
13. 適応型ホール
14. 適応型アリーナ
15. 適応型ドーム
16. 適応型野外

既存12種類はReverb = 0のままです。
「カスタム」はUI状態であり、17番目の内蔵プリセットではありません。

ADAPTIVE TONE BALANCE
ATBの初期状態はOFFです。

ATB OFF:
- Depth / Clarityは固定補正として動作します。

ATB ON:
- DepthはAuto Lowの自動補正上限になります。
- ClarityはAuto Highの自動補正上限になります。
- 100%は最大許容量であり、常時+10 dBではありません。
- 自動補正はboost-onlyで、自動カットは行いません。
- Auto Low絶対上限：+10 dB
- Auto High絶対上限：+10 dB
- 解析中のruntime値は保存しません。

PRESET MANAGER
Preset Managerでは次を利用できます。
- Search
- 読み取り専用プレビュー
- 現在設定との一致表示
- New from Current
- Update from Current
- Duplicate
- Rename
- Delete
- Backup / Restore
- ↑ / ↓
- Alt+↑ / Alt+↓
- ドラッグ＆ドロップ
- 右クリックメニュー
- ダブルクリックApply
- キーボードショートカット
- リサイズ可能な2ペインUI
- 日本語／英語、Light／Dark対応

SONIC REFINER内の処理順序
Depth / Clarity / ATB
-> Width
-> Ambience
-> Reverb
-> Level-Matched Bypass
-> Output Gain
-> Auto Headroom
-> Output

推奨DSP順序
Sonic Refiner
-> R128 Real-time Loudness Normalizer
-> Output

Sonic Refinerは音色・音場を担当します。
R128 Real-time Loudness Normalizerは最終ラウドネス、LUFS、
True Peak管理、リミッター系を担当します。

R128側の基本推奨
通常の音楽鑑賞では、まず次を推奨します。

Sonic Refiner
-> R128 Real-time Loudness Normalizer「ナチュラル -18」
-> Output

2026-10-03時点のR128 Real-time Loudness Normalizer v1.11.0には
次の内蔵プリセットがあります。

標準ノーマライズ:
- ナチュラル -18
- パワーブースト -14
- リラックス -23
- ナイトセーフ -22

Sonic Refinerで作った音色・音場・Reverbをなるべくそのまま生かして
音量を整えたい場合は、標準4種類から選びます。
基本推奨は「ナチュラル -18」です。

追加マスタリング処理:
- モダンブースト -9
  コンプレッション＋ソフトクリッピング＋True Peakリミッター
- 1バンド・アダプティブ -10
  loudness / LRAからModern Processingの強度を自動調整
- 3バンド・アダプティブ -10
  low / mid / highを独立制御
  crossoverの目安：約160 Hz / 4 kHz

追加3種類は音量だけでなく音色・ダイナミクスにも影響します。
必要な場合だけ使用してください。

特に3バンド・アダプティブはlow / mid / highを独立制御するため、
Sonic RefinerのDepth / Clarity / ATBとの役割重複に注意してください。

プリセット互換性
- DSP書込形式：preset_version 10
- 任意プリセット書込形式：SRP5
- SRP1 / SRP2 / SRP3 / SRP4 / SRP5を読込可能
- DSP preset version 1～10を読込可能
- Reverb項目を持たない旧プリセットはReverb = 0
- 旧.srpbackupも復元可能
- .srpbackup外側ヘッダー：
  SONIC_REFINER_PRESET_BACKUP_V1

インストール
1. foo_sonic_refiner_v0.8.0.fb2k-componentをインストールします。
2. foobar2000を再起動します。
3. DSP ManagerへSonic Refinerを追加します。
4. R128 Real-time Loudness Normalizerを併用する場合は、
   Sonic Refinerの後段へ配置します。

ライセンス
MIT License
Copyright (c) 2026 Maximum
