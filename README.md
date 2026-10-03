# Sonic Refiner

**Adaptive Audio Enhancement DSP for foobar2000**

Sonic Refiner is a real-time tone and soundstage enhancement DSP for foobar2000 2.x on Windows x64.

> Current stable release: **v0.8.0**

> Recommended downstream loudness processor: **R128 Real-time Loudness Normalizer**

[日本語はこちら](#日本語)

---

## English

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

See [RELEASE_NOTES_v0.8.0.md](RELEASE_NOTES_v0.8.0.md) for the formal v0.8.0 release notes and [CHANGELOG.md](CHANGELOG.md) for older history.

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
- Japanese / English UI
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
- 100% means the automatic correction may use the full allowed range when needed; it does not mean a constant +10 dB boost
- Auto Low / Auto High are boost-only; ATB does not perform automatic cuts
- Absolute maximum automatic correction is +10 dB for Auto Low and +10 dB for Auto High

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
- Japanese / English and Light / Dark mode support

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

> 現在の正式公開版：**v0.8.0**

> 推奨する後段ラウドネス処理：**R128 Real-time Loudness Normalizer**

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

正式なv0.8.0の変更内容は [RELEASE_NOTES_v0.8.0.md](RELEASE_NOTES_v0.8.0.md)、過去の履歴は [CHANGELOG.md](CHANGELOG.md) を参照してください。

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
- 100%は「必要な場合に最大許容量まで使える」という意味で、常時+10 dBではありません
- Auto Low / Auto Highはboost-onlyで、自動カットは行いません
- 自動補正の絶対上限はAuto Low / Auto Highそれぞれ+10 dB

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
