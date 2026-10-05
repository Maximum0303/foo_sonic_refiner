# Sonic Refiner v0.9.1 Quick Start

> v0.9.1 adds a built-in monitor-reading guide to the formal v0.9.0 Processing Monitor. DSP audio processing and compatibility formats are unchanged.

## English

### 1. Add the DSP

```text
Sonic Refiner
→ R128 Real-time Loudness Normalizer: Natural -18
→ Output
```

**Natural -18** is the recommended R128 starting point for normal music listening.

Standard R128 normalization presets:
- Natural -18
- Power Boost -14
- Relaxed -23
- Night Safe -22

Additional mastering presets:
- Modern Boost -9
- 1-Band Adaptive -10
- 3-Band Adaptive -10

The additional mastering presets also affect tone and dynamics. If preserving Sonic Refiner's tone, soundstage, and Reverb is the priority, start with one of the four standard normalization presets.

### 2. Select a language

Use the language selector at the top of the settings window:

- **Automatic (Windows)**
- **Japanese**
- **English**

Automatic follows the Windows UI language. Manual Japanese / English selections override Automatic. The display changes immediately without changing audio settings.

### 3. Open the Processing Monitor (optional)

From the Playback menu, choose **Sonic Refiner Processing Monitor**. The compact window can stay open while the normal settings dialog is closed.

It shows:
- Auto Low
- Auto High
- AutoHeadroom (Auto Headroom attenuation)
- Level Match attenuation

The display refreshes every 100 ms. Right-click the monitor and choose **How to read the monitor...** for a description of the four values, bars and states. The same menu also toggles **Always on Top**. Its open/closed state and window position are restored on the next foobar2000 launch.

### 4. Choose a starting preset

- **Standard**: fixed Depth / Clarity processing
- **Adaptive Standard**: ATB enabled with full Low / High correction allowance
- **Adaptive Hall / Arena / Dome / Open Air**: venue-style soundstage and Reverb

Sonic Refiner has 16 built-in presets. `Custom` is a UI state, not a 17th preset.

### 5. Adjust

- More bass/body: Depth
- More vocal/instrument definition: Clarity
- Wider stereo image: Width
- More early-reflection space: Ambience
- Longer late decay / tail: Reverb
- Automatic source-dependent low/high correction: Adaptive Tone Balance
- Overall enhancement amount: Master Strength

With ATB On, Depth and Clarity are automatic-correction limits rather than fixed boosts. 100% is a maximum permission, not a constant +15 dB boost.

### 6. Preset Manager

Use **Preset Manager...** for Search, preview, Apply, New from Current, Update from Current, Duplicate, Rename, Delete, Backup, Restore, and reordering.

User presets are saved in **SRP5**. Up to 20 user presets can be stored.

### 7. Backup and compatibility

- Backup extension: `.srpbackup`
- Current user-preset format: SRP5
- Current DSP preset format: `preset_version 10`
- SRP1-SRP4 and DSP preset versions 1-9 remain readable
- Older presets load with Reverb = 0

Auto Headroom Protection is lightweight protection, not a True Peak limiter. Final loudness and True Peak management remain the downstream R128 component's responsibility.

---

## 日本語

### 1. DSPを追加

```text
Sonic Refiner
→ R128 Real-time Loudness Normalizer「ナチュラル -18」
→ Output
```

通常の音楽鑑賞では、R128側は **「ナチュラル -18」** を基本推奨とします。

R128の標準ノーマライズ：
- ナチュラル -18
- パワーブースト -14
- リラックス -23
- ナイトセーフ -22

追加マスタリング処理：
- モダンブースト -9
- 1バンド・アダプティブ -10
- 3バンド・アダプティブ -10

追加3種は音量だけでなく音色・ダイナミクスにも影響します。Sonic Refinerの音色・音場・Reverbをなるべくそのまま生かしたい場合は、まず標準4種から選びます。

### 2. 表示言語を選択

設定画面上部で次から選択します。

- **自動（Windows）**
- **日本語**
- **English**

自動ではWindows UI言語に合わせます。日本語／Englishを手動選択した場合は手動指定を優先します。表示はその場で切り替わり、音質設定は変わりません。

### 3. 補正モニターを開く（任意）

Playbackメニューから **Sonic Refiner 補正モニター** を選びます。通常の設定画面を閉じたまま、小窓だけを常時表示できます。

表示項目：
- 低域補正（Auto Low）
- 高域補正（Auto High）
- 自動ヘッドルーム減衰
- レベル一致減衰

表示は100 ms間隔で更新します。小窓を右クリックすると **常に手前に表示** を切り替えられます。開閉状態とウィンドウ位置は次回起動時に復元されます。

### 4. 最初のプリセット

- **標準**：固定Depth / Clarity処理
- **適応型標準**：ATBを有効にし、低域／高域自動補正の許容量を最大化
- **適応型ホール／アリーナ／ドーム／野外**：会場風の音場とReverb

内蔵プリセットは16種類です。「カスタム」はUI状態であり17番目のプリセットではありません。

### 5. 調整

- 低音・厚み：Depth
- ボーカルや楽器の輪郭：Clarity
- 左右の広がり：Width
- 初期反射・近い空間感：Ambience
- 長い残響・余韻：Reverb
- 音源ごとの低域／高域自動補正：適応型音色補正
- 全体の補正量：Master Strength

ATB ON時はDepth／Clarityが自動補正の上限になります。100%は最大許容量であり、常時+15 dBではありません。

### 6. Preset Manager

**プリセット管理...** から、Search、プレビュー、Apply、New from Current、Update from Current、Duplicate、Rename、Delete、Backup、Restore、並び替えを利用できます。

任意プリセットの現行形式は **SRP5**、最大20件です。

### 7. バックアップと互換性

- バックアップ拡張子：`.srpbackup`
- 任意プリセット現行形式：SRP5
- DSP preset現行形式：`preset_version 10`
- SRP1～SRP4、DSP preset version 1～9も引き続き読込可能
- 旧プリセットのReverbは0として読み込み

自動ヘッドルーム保護は軽量な保護で、True Peakリミッターではありません。最終ラウドネスとTrue Peak管理は後段R128が担当します。

## Direct settings access / 設定画面の直接起動

After installation, use **Playback → Sonic Refiner Settings...** or assign the same command in **Preferences → Keyboard Shortcuts**.

インストール後は **Playback → Sonic Refiner の設定...** から直接開けます。同じコマンドには **Preferences → Keyboard Shortcuts** から任意のキーを割り当てられます。
