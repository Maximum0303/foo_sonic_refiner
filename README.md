# Sonic Refiner

**Adaptive Audio Enhancement DSP for foobar2000**

Sonic Refiner is a real-time tone and soundstage enhancement DSP for foobar2000 2.x on Windows x64.

> Current stable release: **v0.9.0**

> v0.9.0 adds the independent compact **Sonic Refiner Processing Monitor**, showing real-time Auto Low, Auto High, Auto Headroom and Level Match correction values without changing the v0.8.4 audio-processing baseline.

> Recommended downstream loudness processor: **R128 Real-time Loudness Normalizer**

[日本語はこちら](#日本語)

---

## English

## What's new in v0.9.0

v0.9.0 formalizes the validated independent, modeless **Sonic Refiner Processing Monitor** developed in v0.9.0-dev.1/dev.2. The dev.2 build-compatibility fix for foobar2000 SDK `initquit_factory_t` is included. Monitor behavior does not change the DSP audio path.

- Open it from the Playback menu: **Sonic Refiner Processing Monitor**.
- Displays **Auto Low**, **Auto High**, **Headroom** attenuation, and **Level Match** attenuation.
- Updates the display every 100 ms without changing DSP processing.
- Shows Active / Analyzing / Waiting / Paused / Disabled states.
- Remembers whether it was open when foobar2000 exited and restores it on the next launch.
- Remembers its window position.
- Right-click the window to toggle **Always on Top**.
- Follows Sonic Refiner's Automatic (Windows) / Japanese / English display language and foobar2000 light/dark appearance.
- DSP algorithms, built-in preset values, SRP5, `preset_version 10`, `.srpbackup`, and legacy compatibility remain unchanged from v0.8.4.

## What's new in v0.8.4

v0.8.4 formalizes the validated **Auto Headroom Protection** redesign to reduce audible level dips, especially on quieter material and ballads using Adaptive Standard / ATB.

- Replaces instant block-peak attenuation with two-stage smoothed peak detection.
- Short transients normally pass without changing the whole-signal gain.
- Sustained high peaks around the existing approx. -0.2 dBFS reference are attenuated gradually.
- Protection gain now uses a smooth attack and recovery instead of an immediate drop plus a long 1.5-second release.
- This remains lightweight headroom protection, not a True Peak limiter; final True Peak control remains the downstream R128 component's responsibility.
- ATB analysis/decision logic, Level-Matched Bypass, Reverb, built-in preset values, SRP5, `preset_version 10`, `.srpbackup`, display-language behavior, and legacy compatibility are unchanged.

## What's new in v0.8.3

v0.8.3 aligns Sonic Refiner's display-language behavior with R128 Real-time Loudness Normalizer.
The settings label is standardized as **Display language** / **表示言語**.

- Adds **Automatic (Windows)** / **自動（Windows）** to the language selector.
- Automatic mode follows the Windows UI language: Japanese for Japanese Windows UI, English otherwise.
- Manual **Japanese** and **English** selections remain available and override Automatic.
- New installations default to Automatic. Existing saved manual `ja` / `en` choices are preserved.
- Language preference remains separate from DSP presets.
- Settings UI, Preset Manager, Help, Glossary, messages, and Playback-menu text continue to use the resolved display language.
- DSP processing, built-in preset values, SRP5, `preset_version 10`, `.srpbackup`, Reverb, ATB, and legacy compatibility are unchanged.

## What's new in v0.8.2

v0.8.2 formalizes the validated unified maximum gain ceiling used by the fixed tone controls and Adaptive Tone Balance.

- Fixed Depth at 100%: maximum **+15.0 dB** (was +16.0 dB).
- Fixed Clarity at 100%: maximum **+15.0 dB** (was +14.0 dB).
- ATB Auto Low absolute maximum: **+15.0 dB** (was +10.0 dB).
- ATB Auto High absolute maximum: **+15.0 dB** (was +10.0 dB).
- ATB analysis, demand logic, history, attack/release behavior, and boost-only policy are unchanged.
- SRP5, `preset_version 10`, `.srpbackup`, built-in preset parameter values, Reverb, Width, Ambience, Auto Headroom, and legacy compatibility are unchanged.

## What's new in v0.8.1

v0.8.1 updates user-facing guidance without changing audio processing.

- Help / Glossary / Important Notes clarify the recommended downstream R128 setup.
- **Natural -18 / ナチュラル -18** is documented as the recommended R128 starting point.
- The four standard R128 normalization presets are distinguished from the three additional mastering presets.
- QUICK_START.md and README_FIRST.txt are refreshed for Reverb, 16 built-in presets, Preset Manager, SRP5, and `preset_version 10`.
- No DSP algorithm, Reverb tuning, built-in preset value, persistence format, or legacy compatibility change.

## What's new in v0.8.0

v0.8.0 adds a dedicated **Reverb** stage while keeping the existing **Ambience** stage as short early reflections.

- New **Reverb** control: 0–100
- Natural Reverb decay through silent passages
- Track-end Reverb tail rendering for cut-off endings
- Existing Ambience remains the early-reflection / room-impression stage
- Four new venue-oriented built-in presets:
  - **Adaptive Hall** — Width 60 / Ambience 55 / Reverb 50
  - **Adaptive Arena** — Width 72 / Ambience 65 / Reverb 68
  - **Adaptive Dome** — Width 85 / Ambience 75 / Reverb 85
  - **Adaptive Open Air** — Width 75 / Ambience 20 / Reverb 10
- Built-in presets increased from 12 to **16**
- User-preset format updated to **SRP5**
- foobar2000 DSP preset format updated to **preset_version 10**
- SRP1–SRP4, DSP preset versions 1–9, and older `.srpbackup` files remain readable
- Older presets load with **Reverb = 0** to preserve their previous sound

See [RELEASE_NOTES_v0.8.2.md](RELEASE_NOTES_v0.8.2.md) for the formal v0.8.2 release notes and [CHANGELOG.md](CHANGELOG.md) for full history.

## Main features

- **Depth** — low-frequency body enhancement
- **Clarity** — high-frequency clarity enhancement
- **Adaptive Tone Balance (ATB)** — source-dependent boost-only Low/High correction
- **Width** — Mid/Side stereo widening with low-frequency protection
- **Ambience** — short early reflections around 11 ms and 19 ms
- **Reverb** — independent late-reverberation / decay stage
- **Master Strength** — scales the overall enhancement amount
- **Output Gain** — output-level adjustment
- **Auto Headroom Protection** — lightweight output protection
- **Level-Matched Bypass** — fairer processed/original comparison
- **A/B comparison**
- **Preset Manager**
- Up to 20 user presets
- `.srpbackup` backup / restore
- Automatic (Windows) / Japanese / English UI
- foobar2000 Light / Dark mode support

## Ambience and Reverb

Ambience and Reverb have different roles.

```text
Width     = stereo spread
Ambience  = early reflections / immediate room impression
Reverb    = late reflections / decay / tail
```

The existing Ambience stage is unchanged from earlier versions.

With **Reverb = 0**, the Reverb processor is effectively disabled and the sound remains compatible with v0.7.0-era behavior.

The Reverb tail is reset at track boundaries and playback discontinuities so that the previous track's decay does not leak unnaturally into the next track.

## Built-in presets

| # | English | Japanese | Depth | Clarity | Width | Ambience | Reverb | ATB |
|---:|---|---|---:|---:|---:|---:|---:|---|
| 1 | Standard | 標準 | 55 | 45 | 50 | 40 | 0 | Off |
| 2 | Bass Boost | 低域強化 | 90 | 30 | 30 | 25 | 0 | Off |
| 3 | Vocal Focus | ボーカル重視 | 35 | 90 | 25 | 25 | 0 | Off |
| 4 | Wide | ワイド | 40 | 45 | 90 | 30 | 0 | Off |
| 5 | Live | ライブ | 55 | 50 | 70 | 80 | 0 | Off |
| 6 | Headphones | ヘッドホン | 45 | 50 | 65 | 40 | 0 | Off |
| 7 | Extreme Bass | 超低域強化 | 100 | 35 | 30 | 20 | 0 | Off |
| 8 | Extreme Clarity | 超明瞭 | 30 | 100 | 25 | 20 | 0 | Off |
| 9 | Extreme Wide | 超ワイド | 30 | 40 | 100 | 25 | 0 | Off |
| 10 | Large Hall | 大ホール | 45 | 45 | 75 | 100 | 0 | Off |
| 11 | Full Boost | フルブースト | 100 | 100 | 100 | 100 | 0 | Off |
| 12 | Adaptive Standard | 適応型標準 | 100 | 100 | 50 | 40 | 0 | On |
| 13 | Adaptive Hall | 適応型ホール | 100 | 100 | 60 | 55 | 50 | On |
| 14 | Adaptive Arena | 適応型アリーナ | 100 | 100 | 72 | 65 | 68 | On |
| 15 | Adaptive Dome | 適応型ドーム | 100 | 100 | 85 | 75 | 85 | On |
| 16 | Adaptive Open Air | 適応型野外 | 100 | 100 | 75 | 20 | 10 | On |

All built-in presets use Master Strength 100%, Output Gain 0.0 dB, Auto Headroom On, Level-Matched Bypass On, and Sonic Refiner Enabled.

`Custom / カスタム` is a UI state, not a 17th built-in preset.

## Adaptive Tone Balance

ATB is **Off by default**.

When ATB is Off, Depth and Clarity use the fixed processing behavior.

When ATB is On:

- Depth becomes the maximum permission for **Auto Low**
- Clarity becomes the maximum permission for **Auto High**
- 100% means the automatic correction may use the full allowed range when needed; it does not mean a constant +15 dB boost
- Auto Low / Auto High are boost-only; ATB does not perform automatic cuts
- Absolute maximum automatic correction is +15 dB for Auto Low and +15 dB for Auto High

Runtime analysis values are not stored in presets.

## Preset Manager

The Preset Manager provides:

- Search
- Read-only preset preview
- Current-setting match marker `●`
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
- Automatic (Windows) / Japanese / English and Light / Dark mode support

User presets are saved immediately when they are created, renamed, deleted, reordered, updated, backed up, or restored.

Applying a preset changes the current DSP settings. If the parent Sonic Refiner settings dialog is later cancelled, the DSP settings return to the state that existed when the parent dialog was opened.

## Processing order

```text
Depth / Clarity / ATB
→ Width
→ Ambience
→ Reverb
→ Level-Matched Bypass
→ Output Gain
→ Auto Headroom
→ Output
```

## Recommended DSP order

```text
Sonic Refiner
→ R128 Real-time Loudness Normalizer
→ Output
```

Sonic Refiner handles tone and soundstage. The downstream **R128 Real-time Loudness Normalizer** handles final loudness, LUFS, True Peak management, and limiting.

### Recommended R128 preset

For normal music listening, the recommended starting point is:

```text
Sonic Refiner
→ R128 Real-time Loudness Normalizer: Natural -18
→ Output
```

As of 2026-10-03, R128 Real-time Loudness Normalizer v1.11.0 has seven built-in presets.

#### Standard normalization

- **Natural -18** — recommended starting point
- **Power Boost -14** — higher loudness
- **Relaxed -23** — lower loudness / long listening
- **Night Safe -22** — night / low-volume listening

These four are the preferred choices when transparent loudness matching is the priority.

#### Additional mastering processing

- **Modern Boost -9** — compression + soft clipping + True Peak limiting
- **1-Band Adaptive -10** — automatically adjusts Modern Processing strength from loudness / LRA
- **3-Band Adaptive -10** — controls low / mid / high bands independently; approximate crossover boundaries are 160 Hz and 4 kHz

The three additional mastering presets also affect tone and dynamics. When the goal is to preserve Sonic Refiner's tone, soundstage, and Reverb as transparently as possible, start with one of the four standard R128 presets, especially **Natural -18**.

In particular, **3-Band Adaptive** may overlap with Sonic Refiner's Depth / Clarity / ATB role because it processes low, mid, and high bands independently.

## Installation

1. Download `foo_sonic_refiner_v0.8.0.fb2k-component` from the v0.8.0 GitHub Release.
2. Open the component package and follow the foobar2000 installation prompt.
3. Restart foobar2000.
4. Add **Sonic Refiner** to the active DSP chain in DSP Manager.
5. If using R128 Real-time Loudness Normalizer, place it **after** Sonic Refiner.

## Basic operation

A simple starting setup is:

1. Load **Adaptive Standard** for automatic tonal correction, or **Standard** for fixed adjustment.
2. Adjust Width and Ambience as needed.
3. Add Reverb only when a longer decay is desired.
4. For venue-style sound, try Adaptive Hall / Arena / Dome / Open Air.
5. Keep Auto Headroom enabled unless there is a specific reason to disable it.
6. If using R128 Real-time Loudness Normalizer, start with **Natural -18** downstream.
7. Save your preferred Sonic Refiner settings as a user preset.

## Compatibility

- Windows x64
- foobar2000 2.x
- Visual Studio 2022 for source builds
- foobar2000 SDK 2025-03-07
- C++17
- DSP write format: **preset_version 10**
- User-preset write format: **SRP5**
- Reads SRP1 / SRP2 / SRP3 / SRP4 / SRP5
- Reads DSP preset versions 1–10
- Older presets without Reverb load with **Reverb = 0**
- Older `.srpbackup` files remain restorable
- `.srpbackup` outer header remains `SONIC_REFINER_PRESET_BACKUP_V1`

## License

MIT License  
Copyright (c) 2026 Maximum

---

# 日本語

**Sonic Refiner** は、foobar2000 2.x（Windows x64）向けのリアルタイム音色・音場補正DSPです。

> 現在の正式版：**v0.9.0**  
> v0.9.0では、独立した小型の **Sonic Refiner 補正モニター** を追加しました。Auto Low／Auto High／Auto Headroom／Level Matchの補正値をリアルタイム表示し、v0.8.4の音声処理基準は変更していません。

> 推奨する後段ラウドネス処理：**R128 Real-time Loudness Normalizer**

## v0.9.0の変更点

v0.9.0では、v0.9.0-dev.1/dev.2で実機検証した独立型の **Sonic Refiner 補正モニター** を正式搭載します。dev.2で行ったfoobar2000 SDK `initquit_factory_t` とのビルド互換性修正も含みます。モニターはDSP音声処理経路を変更しません。

- Playbackメニューの **Sonic Refiner 補正モニター** から表示
- **低域補正（Auto Low）／高域補正（Auto High）／ヘッドルーム減衰／レベル一致減衰** をリアルタイム表示
- 100 ms間隔で表示更新し、DSP音声処理そのものは変更なし
- 動作中／解析中／待機中／一時停止中／無効を表示
- foobar2000終了時に開いていれば次回起動時に自動再表示
- ウィンドウ位置を記憶
- 右クリックから **常に手前に表示** をON/OFF可能
- Sonic Refinerの自動（Windows）／日本語／English表示とfoobar2000のライト／ダーク表示に追従
- DSPアルゴリズム、16内蔵プリセット値、SRP5、`preset_version 10`、`.srpbackup`、旧形式互換はv0.8.4から変更なし

## v0.8.4の変更点

v0.8.4では、特に静かな曲やバラードを適応型標準／ATBで聴いた際に起きた「音量が微妙にガクッと下がる」現象を改善するため、**自動ヘッドルーム保護**を見直しました。

- 瞬間的なブロックピークで即座に全体ゲインを下げる方式を廃止
- 2段階の平滑化ピーク検出で短いトランジェントを見送り、持続的な高ピークを検出
- 約-0.2 dBFSの保護基準付近を継続的に超えたときだけ穏やかに減衰
- 保護ゲインの低下／復帰を滑らかにし、急な音量変化を抑制
- True Peakリミッターではなく、最終True Peak管理は従来どおり後段R128が担当
- ATB解析・判定、レベルマッチ・バイパス、Reverb、内蔵プリセット値、SRP5、`preset_version 10`、`.srpbackup`、表示言語、旧形式互換は変更なし

## v0.8.3の変更点

v0.8.3では、R128 Real-time Loudness Normalizerと表示言語の動作を統一します。

- 言語選択へ **自動（Windows）** を追加
- 自動時はWindows UI言語が日本語なら日本語、それ以外はEnglishを使用
- 手動の **日本語**／**English** は引き続き選択でき、自動より優先
- 新規・初期状態は自動。既存の手動`ja`／`en`設定は維持
- 言語設定はDSPプリセットとは別に保存
- 設定画面、Preset Manager、Help、用語集、メッセージ、Playbackメニュー表示へ反映
- DSP処理、内蔵プリセット値、SRP5、`preset_version 10`、`.srpbackup`、Reverb、ATB、旧形式互換は変更なし

## v0.8.2の主な変更

v0.8.2では、実機検証済みのv0.8.2-dev.1を正式版化し、固定音色補正と適応型音色補正（ATB）の最大ゲイン上限を統一しました。

- 固定Depth 100%：最大 **+15.0 dB**（従来+16.0 dB）。
- 固定Clarity 100%：最大 **+15.0 dB**（従来+14.0 dB）。
- ATB Auto Low絶対上限：**+15.0 dB**（従来+10.0 dB）。
- ATB Auto High絶対上限：**+15.0 dB**（従来+10.0 dB）。
- ATBの解析・判定・履歴・増減速度・boost-only方針は変更しません。
- SRP5、`preset_version 10`、`.srpbackup`、内蔵プリセット設定値、Reverb、Width、Ambience、Auto Headroom、旧形式互換は変更しません。

## v0.8.1の主な変更

v0.8.1は、音声処理を変更せず、ユーザー向け説明を現行仕様へ整備した更新です。

- Help／用語集／注意事項で、後段R128の基本推奨として **「ナチュラル -18」** を明記
- R128の標準ノーマライズ4種と追加マスタリング3種の違いを明確化
- QUICK_START.md／README_FIRST.txtをReverb、16内蔵プリセット、Preset Manager、SRP5、`preset_version 10`の現行仕様へ更新
- DSPアルゴリズム、Reverb調整値、内蔵プリセット値、保存形式、旧形式互換はv0.8.0から変更なし

## v0.8.0の主な追加・変更

v0.8.0では、従来の **Ambience** を短い初期反射として維持したまま、その後段に独立した **Reverb** を追加しました。

- 新しい **Reverb** コントロール：0～100
- 曲中の無音でも自然に減衰する残響
- カットアウト気味の曲末にも残響テールを追加出力
- Ambienceは従来どおり初期反射・空間感を担当
- 会場向けプリセット4種を追加
  - **適応型ホール** — Width 60 / Ambience 55 / Reverb 50
  - **適応型アリーナ** — Width 72 / Ambience 65 / Reverb 68
  - **適応型ドーム** — Width 85 / Ambience 75 / Reverb 85
  - **適応型野外** — Width 75 / Ambience 20 / Reverb 10
- 内蔵プリセットを12種類から **16種類**へ拡張
- 任意プリセット形式を **SRP5** へ更新
- foobar2000 DSP preset形式を **preset_version 10** へ更新
- SRP1～SRP4、DSP preset version 1～9、旧`.srpbackup`を引き続き読込可能
- 旧プリセットは **Reverb = 0** として読み込み、従来の音を維持

正式なv0.8.2の変更内容は [RELEASE_NOTES_v0.8.2.md](RELEASE_NOTES_v0.8.2.md)、全履歴は [CHANGELOG.md](CHANGELOG.md) を参照してください。

## 主な機能

- **Depth** — 低域の厚み
- **Clarity** — 高域の明瞭感
- **Adaptive Tone Balance（ATB）** — 音源に応じたboost-onlyの低域／高域自動補正
- **Width** — 低域保護付きMid/Sideステレオ拡張
- **Ambience** — 約11 ms / 19 msの短い初期反射
- **Reverb** — 独立した後期残響・余韻・テール
- **Master Strength** — 全体の補正量
- **Output Gain**
- **Auto Headroom Protection**
- **Level-Matched Bypass**
- **A/B比較**
- **Preset Manager**
- 任意プリセット最大20件
- `.srpbackup`によるバックアップ／復元
- 日本語／英語UI
- foobar2000 Light／Darkモード対応

## AmbienceとReverb

AmbienceとReverbは役割が異なります。

```text
Width     = 左右方向の広がり
Ambience  = 初期反射・すぐ近くの空間感
Reverb    = 後期残響・余韻・テール
```

従来のAmbience処理自体は変更していません。

**Reverb = 0** ではReverb処理が実質OFFとなり、v0.7.0までの音を維持します。

曲末やシーク／停止などでは残響状態を適切にリセットし、前の曲の余韻が次の曲へ不自然に持ち越されないようにしています。

## 内蔵プリセット

内蔵プリセットは16種類です。上の英語セクションの表に、日本語名と主要パラメータを併記しています。

新しい会場プリセットは：

- **適応型ホール** — Width 60 / Ambience 55 / Reverb 50
- **適応型アリーナ** — Width 72 / Ambience 65 / Reverb 68
- **適応型ドーム** — Width 85 / Ambience 75 / Reverb 85
- **適応型野外** — Width 75 / Ambience 20 / Reverb 10

`カスタム / Custom` はUI上の状態表示であり、17番目の内蔵プリセットではありません。

## Adaptive Tone Balance（ATB）

ATBの初期状態は **OFF** です。

ATB OFFでは、Depth / Clarityは従来の固定補正として動作します。

ATB ONでは：

- Depthは **Auto Lowの自動補正上限**
- Clarityは **Auto Highの自動補正上限**
- 100%は「必要な場合に最大許容量まで使える」という意味で、常時+15 dBではありません
- Auto Low / Auto Highはboost-onlyで、自動カットは行いません
- 自動補正の絶対上限はAuto Low / Auto Highそれぞれ+15 dB

解析履歴や現在のAuto Low / Auto High値はプリセットへ保存しません。

## Preset Manager

Preset Managerでは次を利用できます。

- Search
- 読み取り専用プレビュー
- 現在設定との一致表示 `●`
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

任意プリセットの作成・名前変更・削除・並び替え・更新・バックアップ／復元などの管理操作は即時保存されます。

Applyで現在のDSP設定を変更した後、親のSonic Refiner設定画面でCancelした場合は、親画面を開いた時点のDSP設定へ戻ります。

## Sonic Refiner内の処理順序

```text
Depth / Clarity / ATB
→ Width
→ Ambience
→ Reverb
→ Level-Matched Bypass
→ Output Gain
→ Auto Headroom
→ Output
```

## 推奨DSP順序

```text
Sonic Refiner
→ R128 Real-time Loudness Normalizer
→ Output
```

Sonic Refinerは音色・音場を担当し、後段の **R128 Real-time Loudness Normalizer** が最終ラウドネス、LUFS、True Peak管理、リミッター系を担当します。

### R128側の基本推奨

通常の音楽鑑賞では、まず：

```text
Sonic Refiner
→ R128 Real-time Loudness Normalizer「ナチュラル -18」
→ Output
```

を基本推奨とします。

2026-10-03時点のR128 Real-time Loudness Normalizer v1.11.0には7つの内蔵プリセットがあります。

#### 標準ノーマライズ

- **ナチュラル -18** — 基本推奨
- **パワーブースト -14** — より高いラウドネス感
- **リラックス -23** — 控えめな音量・長時間再生
- **ナイトセーフ -22** — 夜間・小音量再生

Sonic Refinerで作った音色・音場・Reverbをなるべくそのまま生かしながら音量を整えたい場合は、まずこの標準4種類から選びます。

#### 追加マスタリング処理

- **モダンブースト -9** — コンプレッション＋ソフトクリッピング＋True Peakリミッター
- **1バンド・アダプティブ -10** — loudness / LRAからModern Processingの強度を自動調整
- **3バンド・アダプティブ -10** — low / mid / highを独立制御。crossoverの目安は約160 Hz / 4 kHz

この3種類は音量だけでなく音色・ダイナミクスにも影響します。Sonic Refinerの音作りをできるだけそのまま残したい場合は、必要なときだけ使用してください。

特に **3バンド・アダプティブ** はlow / mid / highを独立制御するため、Sonic RefinerのDepth / Clarity / ATBとの役割重複に注意してください。

## インストール

1. v0.8.0のGitHub Releaseから `foo_sonic_refiner_v0.8.0.fb2k-component` をダウンロードします。
2. ファイルを開き、foobar2000の確認画面に従ってインストールします。
3. foobar2000を再起動します。
4. DSP Managerで **Sonic Refiner** を使用中のDSPへ追加します。
5. R128 Real-time Loudness Normalizerを併用する場合は、Sonic Refinerの**後段**へ配置します。

## 基本的な使い方

最初の設定例：

1. 自動音色補正を使う場合は **適応型標準**、固定補正から始める場合は **標準** を読み込みます。
2. Width / Ambienceを好みに合わせて調整します。
3. 長い余韻が必要な場合だけReverbを加えます。
4. 会場風の音場は適応型ホール／アリーナ／ドーム／野外を試します。
5. 特別な理由がなければAuto HeadroomをONのまま使用します。
6. R128 Real-time Loudness Normalizerを併用する場合は、まず **ナチュラル -18** を後段に設定します。
7. 好みのSonic Refiner設定は任意プリセットとして保存します。

## 互換性

- Windows x64
- foobar2000 2.x
- ソースビルド：Visual Studio 2022
- foobar2000 SDK 2025-03-07
- C++17
- DSP書込形式：**preset_version 10**
- 任意プリセット書込形式：**SRP5**
- SRP1 / SRP2 / SRP3 / SRP4 / SRP5を読込可能
- DSP preset version 1～10を読込可能
- Reverb項目を持たない旧プリセットは **Reverb = 0**
- 旧`.srpbackup`も復元可能
- `.srpbackup`外側ヘッダーは `SONIC_REFINER_PRESET_BACKUP_V1` のまま

## ライセンス

MIT License  
Copyright (c) 2026 Maximum
