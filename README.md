# Sonic Refiner

**Adaptive Audio Enhancement DSP for foobar2000**

Sonic Refiner adjusts tone and soundstage in real time. It combines low-frequency body, clarity, stereo width, short early reflections, Master Strength, output gain, lightweight headroom protection, and level-matched comparison in one DSP component.

> Current release: **v0.3.0**

## What is new in v0.3.0

- Japanese and English user interface
- Instant language switching without restarting foobar2000
- First-run language selection based on the Windows display language
- The selected language is remembered independently of DSP presets
- Built-in preset names, buttons, status text, messages, file dialogs, Help, Glossary, Important Notes, and License pages are localized
- English-first public documentation

The DSP processing algorithm is unchanged from v0.2.0.

## Main features

- **Depth:** low-shelf enhancement around 120 Hz, up to approximately +16 dB
- **Clarity:** high-shelf enhancement above approximately 3.5 kHz, up to approximately +14 dB
- **Width:** Mid/Side widening with protection below approximately 180 Hz, up to Side 600%
- **Ambience:** short early reflections around 11 ms and 19 ms, up to 85% Wet Mix
- **Master Strength:** scales Depth, Clarity, Width, and Ambience together from 0% to 100%
- **Output Gain:** -12.0 dB to +6.0 dB in 0.5 dB steps
- **Auto Headroom Protection:** lightweight block/sample-peak protection around -0.2 dBFS
- **Level-Matched Bypass:** reduces average level added by processing for fairer comparison
- Eleven built-in presets
- Up to 20 UTF-8 user presets
- User-preset export and import with `.srpbackup` files
- Integrated Help, Glossary, Important Notes, and MIT License pages
- foobar2000 light and dark mode support

## Built-in presets

| English | Japanese |
|---|---|
| Standard | 標準 |
| Bass Boost | 低域強化 |
| Vocal Focus | ボーカル重視 |
| Wide | ワイド |
| Live | ライブ |
| Headphones | ヘッドホン |
| Extreme Bass | 超低域強化 |
| Extreme Clarity | 超明瞭 |
| Extreme Wide | 超ワイド |
| Large Hall | 大ホール |
| Full Boost | フルブースト |

Only the displayed names change with the UI language. Preset values and internal order remain unchanged.

## Processing order

```text
Depth
→ Clarity
→ Width
→ Ambience
→ effective amount controlled by Master Strength
→ Level Match
→ Output Gain
→ Automatic Headroom Protection
```

## Recommended DSP order

```text
Sonic Refiner
→ R128 Real-time Loudness Normalizer
→ Output
```

Sonic Refiner handles tone and soundstage. The downstream **R128 Real-time Loudness Normalizer** handles final loudness management, True Peak protection, and limiting.

## Language behavior

- Japanese Windows display language: Japanese by default
- Other Windows display languages: English by default
- Change the language from the selector at the top of the settings window
- The open settings window updates immediately
- Audio processing is not restarted or reinitialized
- Slider values, current sound settings, and user-preset names are not changed
- The language setting is not stored in DSP presets, user presets, or `.srpbackup` files
- Cancel restores sound settings as before, but does not undo a language change

## Installation

1. Double-click `foo_sonic_refiner_v0.3.0.fb2k-component`.
2. Apply the component installation in foobar2000.
3. Restart foobar2000.
4. Add `Sonic Refiner` from DSP Manager.


## Basic operation

1. Load the **Standard** built-in preset.
2. Adjust Depth, Clarity, Width, and Ambience.
3. Use Master Strength to adjust the overall amount while preserving the balance.
4. Adjust Output Gain when necessary.
5. Save the result as a user preset.

### Suggested ranges

- **0–60%:** normal adjustment range
- **60–80%:** strong enhancement range
- **80–100%:** extreme effects and testing

## Compatibility

- Windows x64
- Visual Studio 2022
- foobar2000 SDK 2025-03-07
- C++17
- DSP `preset_version 8` remains unchanged
- User-preset format remains `SRP3`
- Reads `SRP1`, `SRP2`, and `SRP3`
- Legacy settings without Master Strength load at 100%
- Legacy settings without Output Gain load at 0.0 dB
- Existing UTF-8 user-preset names are preserved and are not translated
- `.srpbackup` format is unchanged

## Building from source

Required:

- Visual Studio 2022
- foobar2000 SDK 2025-03-07
- WTL
- Windows x64

Place the project at:

```text
F:\foobar2000-dev\SDK-2025-03-07\foobar2000\foo_sonic_refiner
```

Confirm that WTL includes:

```text
F:\foobar2000-dev\WTL\Include\atlapp.h
```

Run:

```text
build_and_package.cmd
```

Output:

```text
dist\foo_sonic_refiner_v0.3.0.fb2k-component
dist\SHA256SUMS.txt
```

See `README_FIRST.txt` for detailed build steps and `TESTING_v0.3.0.md` for the release test record.

## Safety notes

- Values above 80% are not intended as a natural everyday adjustment range.
- Strong Depth can increase the load on speakers, subwoofers, and amplifiers.
- Strong Clarity can emphasize sibilance, cymbals, noise, and distortion.
- Strong Width can reduce center stability and mono compatibility.
- Strong Ambience can create separated echoes, distance, or muddiness.
- Auto Headroom Protection is not a True Peak limiter.
- Lower the playback volume before testing extreme settings.

## License

MIT License

```text
Copyright (c) 2026 Maximum
```

See `LICENSE.txt`. foobar2000 and the foobar2000 SDK remain subject to their respective rights and terms. See `THIRD_PARTY_NOTICES.txt`.

## Clean-room statement

This project is an independent clean-room implementation. It does not include or use Winamp Enhancer 017 source code, DLLs, images, presets, settings data, or other assets.

---

# 日本語

Sonic Refinerは、音色と音場をリアルタイムで調整するfoobar2000用DSPコンポーネントです。低域の厚み、明瞭感、ステレオの広がり、短い初期反射による空間・奥行き感、Master Strength、出力ゲイン、軽量な保護、レベルを合わせた比較を1つの設定画面にまとめています。

> 現在の正式公開版：**v0.3.0**

## v0.3.0の変更点

- 設定画面の日本語／英語切り替え
- foobar2000を再起動せず、その場で表示を切り替え
- 初回はWindowsの表示言語を判定
- 選択した言語を音質設定とは別に保存
- 内蔵プリセット名、ボタン、状態表示、確認・エラー表示、ファイル選択、ヘルプ、用語集、注意事項、ライセンスを英語化
- README等を英語先・日本語後の構成へ変更

DSP処理アルゴリズムはv0.2.0から変更していません。

## 主な機能

- **Depth**：約120 Hzを中心とするLow Shelf、最大約+16 dB
- **Clarity**：約3.5 kHz以上のHigh Shelf、最大約+14 dB
- **Width**：約180 Hz以下を保護するMid/Side方式、Side最大600%
- **Ambience**：約11 ms・19 msの短い初期反射、Wet Mix最大85%
- **Master Strength**：4つの補正効果を0～100%で一括調整
- **Output Gain**：-12.0～+6.0 dB、0.5 dB刻み
- **自動ヘッドルーム保護**：約-0.2 dBFS付近の軽量なブロック／サンプルピーク保護
- **レベルマッチ・バイパス**：処理による平均音量増加分を抑えた比較
- 内蔵プリセット11種類
- UTF-8任意プリセット最大20件
- `.srpbackup`による書き出し・読み込み
- ヘルプ・用語集・注意事項・MIT License
- ライト／ダークモード対応

## 言語切り替えの動作

- Windowsの表示言語が日本語：初期表示は日本語
- それ以外：初期表示はEnglish
- 設定画面上部の選択欄から変更
- 開いている設定画面を即時更新
- DSPの再作成・再初期化は行わない
- スライダー値、現在の音質設定、任意プリセット名は変更しない
- 言語設定はDSP preset、任意プリセット、`.srpbackup`へ保存しない
- キャンセル時は従来どおり音質設定を戻すが、言語変更は戻さない

## 推奨DSP順序

```text
Sonic Refiner
→ R128 Real-time Loudness Normalizer
→ Output
```

## 互換性

- `preset_version 8`を維持
- 任意プリセット形式は`SRP3`を維持
- `SRP1`／`SRP2`／`SRP3`を読み込み可能
- Master Strengthを持たない旧設定は100%
- Output Gainを持たない旧設定は0.0 dB
- 既存の日本語名を含む任意プリセット名は翻訳せず維持
- `.srpbackup`形式は変更なし

## ビルド

配置先：

```text
F:\foobar2000-dev\SDK-2025-03-07\foobar2000\foo_sonic_refiner
```

WTL確認先：

```text
F:\foobar2000-dev\WTL\Include\atlapp.h
```

次を実行します。

```text
build_and_package.cmd
```

出力：

```text
dist\foo_sonic_refiner_v0.3.0.fb2k-component
dist\SHA256SUMS.txt
```

詳しい手順は`README_FIRST.txt`、公開前確認記録は`TESTING_v0.3.0.md`を参照してください。
