# Sonic Refiner v0.6.5 Quick Start

> v0.6.5 note: select a user preset and use `↑` / `↓` to move it one position. The order is preserved with the existing SRP4 / `.srpbackup` format; DSP / ATB processing is unchanged.
> v0.6.3 documentation note: Help / Glossary now explain ATB in user-oriented terms and distinguish Auto Low, Auto High, and analysis state. Audio processing is unchanged.

> v0.6.3 UI note: with Adaptive Tone Balance ON, Depth is shown as the Auto Low limit and Clarity as the Auto High limit. 100% is an upper permission, not a constant +10 dB boost.

> Adaptive Tone Balance is OFF by default. Use **Adaptive Standard / 適応型標準** when you want ATB enabled with the full Low/High correction allowance while keeping Standard Width/Ambience values.

# Sonic Refiner Quick Start

## English

### 1. Add the DSP

```text
Sonic Refiner
→ R128 Real-time Loudness Normalizer
→ Output
```

### 2. Select a language

Use the language selector at the top of the settings window.

```text
日本語
English
```

The display changes immediately. Audio settings and playback processing are not changed.

### 3. Initial settings

1. Load **Standard** for the original fixed mode, or **Adaptive Standard** for ATB-enabled automatic tonal correction.
2. Keep **Auto Headroom Protection** enabled.
3. Keep **Level-Matched Bypass** enabled.
4. Keep **Adaptive Tone Balance** off for the original fixed mode, or enable it for source-dependent correction.
5. Set **Master Strength** to 100%.
6. Set **Output Gain** to 0.0 dB.

### 4. Adjust

- More bass/body: Depth
- More vocal/instrument definition: Clarity
- Wider stereo image: Width
- More space/depth: Ambience
- Automatic source-dependent low/high correction: Adaptive Tone Balance
- When Adaptive Tone Balance is ON, Depth and Clarity set the maximum automatic correction
- Reduce all four while preserving balance: Master Strength

Use 0–60% for normal adjustment. Values above 80% are for extreme effects and testing.

### 5. Save and back up

- `Save...`: save the current settings as a user preset, including Adaptive Tone Balance On/Off
- `Rename...`: rename the selected user preset without changing its stored settings
- `↑` / `↓`: move the selected user preset one position; the order persists across restart and `.srpbackup` export/import
- `Export...`: save all user presets to `.srpbackup`, including each preset's Adaptive Tone Balance On/Off state
- `Import...`: replace the current user preset list with a backup

Auto Headroom Protection is lightweight protection, not a True Peak limiter.

---

## 日本語

### 1. DSPを追加

```text
Sonic Refiner
→ R128 Real-time Loudness Normalizer
→ Output
```

### 2. 言語を選択

設定画面上部の選択欄から変更します。

```text
日本語
English
```

表示はその場で切り替わり、音質設定や再生処理は変更されません。

### 3. 最初の設定

1. 従来の固定補正なら内蔵「標準」、ATBを最大限利用するなら「適応型標準」を呼び出す
2. 自動ヘッドルーム保護をオン
3. レベルマッチ・バイパスをオン
4. 従来の固定補正なら適応型音色補正をオフ、音源別の自動補正ならオン
5. Master Strengthを100%
6. Output Gainを0.0 dB

### 4. 調整

- 低音・厚み：Depth
- ボーカルや楽器の輪郭：Clarity
- 左右の広がり：Width
- 空間・奥行き：Ambience
- 音源ごとの低域／高域自動補正：適応型音色補正
- 適応型音色補正ON時はDepth／Clarityが自動補正の上限
- 4項目のバランスを保って全体を弱める：Master Strength

通常は0～60%を中心に調整し、80%以上は強い効果や動作確認に使用します。

### 5. 保存とバックアップ

- `保存...`：現在の設定を、適応型音色補正のON/OFFを含めて任意プリセットとして保存
- `名前変更...`：保存済み設定値を変えずに選択中の任意プリセット名だけを変更
- `↑` / `↓`：選択中の任意プリセットを1件ずつ並べ替え。順序は再起動後や`.srpbackup`でも維持
- `書出...`：各プリセットの適応型音色補正ON/OFFを含め、任意プリセット全件を`.srpbackup`へ保存
- `読込...`：現在の任意プリセット一覧をバックアップ内容で置換

自動ヘッドルーム保護は軽量な保護であり、True Peakリミッターではありません。


## Direct settings access / 設定画面の直接起動

After installation, use **Playback → Sonic Refiner Settings...** (English) or **Playback → Sonic Refiner の設定...** (Japanese). You can assign the same command in **Preferences → Keyboard Shortcuts**.

インストール後は **Playback → Sonic Refiner の設定...** から設定画面を直接開けます。同じコマンドには **Preferences → Keyboard Shortcuts** から任意のキーを割り当てられます。
