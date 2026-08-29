# Sonic Refiner

**Adaptive Audio Enhancement DSP for foobar2000**

Sonic Refiner adjusts tone and soundstage in real time. It combines low-frequency body, clarity, stereo width, short early reflections, Master Strength, Adaptive Tone Balance, output gain, lightweight headroom protection, and level-matched comparison in one DSP component.

> Current stable release: **v0.6.5**

## What is new in v0.6.5

v0.6.5 adds manual reordering for user presets without changing preset content or serialization. The validated v0.6.5-dev.1 implementation is used unchanged for the feature itself.

- Use `↑` / `↓` to move the selected user preset one position.
- The selected preset remains selected after moving.
- `↑` is disabled at the first item; `↓` is disabled at the last item.
- Both are disabled when no user preset is selected.
- Reordered user presets are persisted in the existing SRP4 list order.
- `.srpbackup`, `preset_version 9`, DSP / ATB processing, and all 12 built-in preset values are unchanged.

## What is new in v0.6.4

v0.6.4 adds **Rename... / 名前変更...** for existing user presets. It
changes only the preset name and keeps all stored DSP values unchanged.

- Select an existing user preset and press `Rename... / 名前変更...`.
- The current name is prefilled and selected for editing.
- Names remain UTF-8 and limited to 40 characters.
- Renaming to a name already used by another user preset is rejected.
- The Rename button is disabled when no user preset is selected.
- Built-in presets remain fixed and cannot be renamed.
- SRP4, `.srpbackup`, and `preset_version 9` are unchanged.
- No DSP / Adaptive Tone Balance algorithm or built-in preset value changes.

## What is new in v0.6.3

v0.6.3 is a UI and documentation refinement release. It keeps the validated
DSP / Adaptive Tone Balance processing unchanged while making current state and
ATB behavior easier to understand.

### Custom / カスタム state

- When the current DSP settings do not exactly match any of the 12 built-in
  presets, the Built-in Presets combo displays `Custom / カスタム`.
- `Custom / カスタム` is a UI-only state, not a 13th built-in preset.
- The built-in preset Load button is disabled while Custom is displayed.
- Selecting an actual built-in preset still does not apply it until Load is
  pressed.
- Japanese / English switching changes only the displayed Custom label.

### Clearer ATB Depth / Clarity labels

When Adaptive Tone Balance is ON:

- Depth is labeled as the **Auto Low correction limit**.
- Clarity is labeled as the **Auto High correction limit**.
- The descriptions explicitly state that 100% is an upper permission, not a
  constant +10 dB boost.
- Existing Auto Low / Auto High value displays are preserved.

When Adaptive Tone Balance is OFF, the original fixed-mode Depth / Clarity
labels and descriptions are shown.

### Help / Glossary clarity

- Help now explains ATB in practical user-oriented terms.
- It explicitly states that ATB is boost-only.
- It explains that Depth / Clarity are automatic correction limits when ATB is
  ON.
- It explains that Width / Ambience remain manual.
- It explains fresh-analysis behavior and Pause / Resume history preservation.
- Glossary entries separately define Adaptive Tone Balance, Auto Low, Auto High,
  and ATB Analysis State using the current validated frequency ranges.

### Compatibility

- No DSP processing changes.
- No Adaptive Tone Balance decision-algorithm changes.
- All 12 built-in preset values are unchanged.
- SRP4 remains unchanged.
- `preset_version 9` remains unchanged.
- Legacy DSP preset and SRP1 / SRP2 / SRP3 / SRP4 compatibility is preserved.

## What is new in v0.6.2

v0.6.2 fixed the Built-in Presets combo display so it reflects
the built-in preset that exactly matches the currently restored DSP settings.
If the current settings do not exactly match any built-in preset, the combo is
left unselected rather than incorrectly showing `Standard`.

This does not change DSP processing, ATB behavior, built-in preset values,
SRP4, or `preset_version 9`.

## What is new in v0.6.1

### Clear ATB analysis status on playback changes

v0.6.1 improves the Adaptive Tone Balance status display so values from the
previous playback position are not mistaken for fresh analysis results.

- Playback start, Next, Previous, direct track jumps, natural track changes, seeks,
  Stop -> playback, and ATB Off -> On show
  `自動補正：解析中...` / `Auto: Analyzing...`
  while fresh analysis is being accumulated
- After sufficient fresh analysis, the normal Auto Low / Auto High numeric status returns
- Pause / Resume preserves the current analysis state and does not restart analysis
- A runtime-only playback discontinuity generation makes new-track and seek resets reliable

### Compatibility

- No DSP or Adaptive Tone Balance decision-algorithm changes from v0.6.0
- Auto Low / Auto High limits remain **+10.0 dB**
- **SRP4** remains the user-preset / `.srpbackup` format
- **preset_version 9** remains the DSP preset format
- All **12 built-in presets** remain unchanged
- Legacy preset / backup compatibility is unchanged
- Runtime analyzer history and live Auto Low / Auto High values remain non-persistent

## What is new in v0.6.0

### Adaptive Standard built-in preset

v0.6.0 adds one built-in preset designed to make full practical use of
**Adaptive Tone Balance (ATB)** without changing the validated v0.5.0 ATB algorithm.

- Added **Adaptive Standard / 適応型標準** as the 12th built-in preset
- Depth: **100**
- Clarity: **100**
- Width: **50**
- Ambience: **40**
- Master Strength: **100%**
- Output Gain: **0.0 dB**
- Auto Headroom Protection: **On**
- Level-Matched Bypass: **On**
- Sonic Refiner: **Enabled**
- Adaptive Tone Balance: **On**
- With ATB On, Depth and Clarity act as maximum permissions, so Auto Low / Auto High can use the full allowed range up to **+10.0 dB** each when the source analysis calls for it
- Width and Ambience keep the existing Standard preset values, avoiding an unnecessarily extreme soundstage
- The existing 11 built-in presets remain unchanged and still load **ATB Off**

### UI refinement

- Widened the Depth and Clarity value fields so Japanese ATB limit text such as
  `100% / 自動上限 +10.0 dB` is fully visible
- Settings window remains **560 × 320**

### Compatibility

- No DSP or Adaptive Tone Balance algorithm changes from v0.5.0
- DSP write format remains **preset_version 9**
- User preset / `.srpbackup` write format remains **SRP4**
- SRP1 / SRP2 / SRP3 / SRP4 and legacy DSP preset reading remain supported
- Runtime analyzer history, Auto Low / Auto High values, and confidence remain non-persistent
- A/B, Cancel, direct settings access, Japanese/English UI, and existing protection behavior are unchanged

## What is new in v0.5.0

### Adaptive Tone Balance

v0.5.0 adds optional **Adaptive Tone Balance (ATB)** while preserving the
v0.4.0 fixed Depth/Clarity behavior whenever ATB is Off.

- Adaptive Tone Balance is **Off by default**
- Analysis uses the original signal before Sonic Refiner processing
- **Auto Low** compares Bass **60–180 Hz** with Body **200–500 Hz**
- Low decision target: Bass/Body **+6.5 dB**
- Auto Low processing preserves the dry signal and adds a parallel filtered **60–180 Hz** Bass component
- **Auto High** uses High/Mid balance (**3.5–10 kHz** vs **300 Hz–2.0 kHz**) together with Treble/Presence balance (**5–10 kHz** vs **2–5 kHz**) to choose correction strength
- High/Mid shortage reference remains **-6 dB** with a **1.5 dB** tolerance
- Automatic correction is **boost-only**; ATB does not perform automatic cuts
- Auto Low absolute maximum: **+10.0 dB**
- Auto High absolute maximum: **+10.0 dB**
- When ATB is On, **Depth and Clarity become maximum permissions** for automatic correction rather than fixed boost amounts
- Master Strength continues to scale the resulting Depth/Clarity effect
- Slow rolling analysis and gain movement are used to reduce audible pumping
- Very low input below approximately **-55 dBFS** does not update analysis
- Track changes, seeks, Stop, and ATB Off→On transitions restart analysis; Pause/Resume preserves it
- Multichannel analysis uses the first L/R pair
- The normal public UI shows current **Auto Low / Auto High** correction without development diagnostics

### Presets, compatibility, and A/B

- Existing 11 built-in presets remain unchanged and load **ATB Off**
- Existing built-in presets can be used normally; enable ATB afterward when automatic correction is wanted
- User presets store the ATB On/Off state
- User-preset / `.srpbackup` write format: **SRP4**
- foobar2000 DSP preset write format: **preset_version 9**
- SRP1 / SRP2 / SRP3 and DSP preset versions 1–8 remain readable
- Legacy data that has no ATB field loads with **ATB Off**
- A/B slots store ATB On/Off in addition to Depth, Clarity, Width, Ambience, and Master Strength
- A/B analyzer state and live automatic-gain state are runtime-only and are not persisted
- Ending A/B comparison restores the full settings that were active when comparison began

### Release-candidate validation

The v0.5.0 release candidate was checked for:
- Light and Dark mode
- continuous playback
- restart persistence
- Cancel behavior
- ATB On/Off user presets and SRP4 backup restore
- SRP3 legacy import behavior
- A/B ATB switching and pre-comparison restoration
- fresh ATB analysis after restart and after Off→On

## What is new in v0.4.0

### Direct settings access

- Open **Playback → Sonic Refiner Settings...** to configure the single active Sonic Refiner instance without going through DSP Manager.
- The direct window is modeless and owned by foobar2000: foobar2000 remains usable, the window stays above foobar2000, and unrelated applications can still appear above it.
- The command is also available in **Preferences → Keyboard Shortcuts**. No default key binding is assigned.
- If Sonic Refiner is absent from the active DSP chain or appears more than once, direct editing is refused for safety.
- The conventional DSP Manager configuration path remains available.


v0.4.0 adds temporary A/B comparison slots and direct settings access from the Playback menu.

- Store Depth, Clarity, Width, Ambience, and Master Strength in A or B
- Listen to A or B instantly without changing Output Gain or protection settings
- End Comparison restores the full settings that were active before comparison began
- A/B slots are not written to DSP presets, user presets, or `.srpbackup` files
- A/B slots remain available while foobar2000 is running and are cleared after restart
- Japanese and English UI are both supported

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
- **Adaptive Tone Balance:** source-dependent boost-only Low/High correction using Bass/Body plus H/M + T/P analysis
- **Width:** Mid/Side widening with protection below approximately 180 Hz, up to Side 600%
- **Ambience:** short early reflections around 11 ms and 19 ms, up to 85% Wet Mix
- **Master Strength:** scales Depth, Clarity, Width, and Ambience together from 0% to 100%
- **Output Gain:** -12.0 dB to +6.0 dB in 0.5 dB steps
- **Auto Headroom Protection:** lightweight block/sample-peak protection around -0.2 dBFS
- **Level-Matched Bypass:** reduces average level added by processing for fairer comparison
- Twelve built-in presets
- Up to 20 UTF-8 user presets with rename support
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
| Adaptive Standard | 適応型標準 |

Only the displayed names change with the UI language. Preset values and internal order remain unchanged.

## Processing order

```text
Adaptive Tone Balance analysis (original input, when enabled)
→ Depth / adaptive low correction
→ Clarity / adaptive high correction
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

1. Double-click `foo_sonic_refiner_v0.6.5.fb2k-component`.
2. Apply the component installation in foobar2000.
3. Restart foobar2000.
4. Add `Sonic Refiner` from DSP Manager.


## Basic operation

1. Load the **Standard** built-in preset.
2. Adjust Depth, Clarity, Width, and Ambience.
3. Optionally enable **Adaptive Tone Balance**. When enabled, Depth and Clarity become automatic-correction limits.
4. Use Master Strength to adjust the overall amount while preserving the balance.
5. Adjust Output Gain when necessary.
6. Save the result as a user preset.

### Suggested ranges

- **0–60%:** normal adjustment range
- **60–80%:** strong enhancement range
- **80–100%:** extreme effects and testing

## Compatibility

- Windows x64
- Visual Studio 2022
- foobar2000 SDK 2025-03-07
- C++17
- DSP write format is `preset_version 9`
- User-preset write format is `SRP4`
- Reads `SRP1`, `SRP2`, `SRP3`, and `SRP4`
- Reads legacy DSP preset versions 1–8; Adaptive Tone Balance defaults to Off for legacy data
- Legacy settings without Master Strength load at 100%
- Legacy settings without Output Gain load at 0.0 dB
- Existing UTF-8 user-preset names are preserved and are not translated
- `.srpbackup` remains the backup extension; older backups remain readable and new backups carry SRP4 user-preset data

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
dist\foo_sonic_refiner_v0.6.5.fb2k-component
dist\SHA256SUMS.txt
```

See `README_FIRST.txt` for detailed build steps and `TESTING_v0.6.5.md` for the final release validation checklist.

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

> 現在の正式公開版：**v0.6.5**

## v0.6.5の変更点

v0.6.5では、既存の任意プリセットを **`↑` / `↓`** で手動並べ替えできる機能を追加しました。並べ替えで変更されるのは一覧の順序だけで、名前や保存済みDSP設定値は変更されません。

- 選択中の任意プリセットを1件ずつ上／下へ移動
- 移動後も対象プリセットを選択した状態を維持
- 先頭では `↑`、末尾では `↓` を無効化
- 未選択時や1件だけの場合は移動できないボタンを無効化
- 並べ替え後の順序を再起動後も維持
- `.srpbackup`書出／読込でも並び順を維持
- SRP4、`.srpbackup`、`preset_version 9`は変更なし
- DSP／Adaptive Tone Balanceアルゴリズム、12種類の内蔵プリセット値は変更なし

## v0.6.4の変更点

v0.6.4では、既存の任意プリセットに **「名前変更... / Rename...」** を追加しました。変更されるのはプリセット名だけで、保存済みのDSP設定値はそのまま維持されます。

- 既存の任意プリセットを選択して `名前変更... / Rename...` を実行可能
- 名前変更画面では現在名を入力済み・全選択状態で編集開始
- 名前は従来どおりUTF-8、最大40文字
- 他の任意プリセットと同じ名前への変更は拒否
- 現在名と同じ名前への変更は安全なno-op
- 任意プリセット未選択時は名前変更ボタンを無効化
- 内蔵プリセットは名前変更不可
- SRP4、`.srpbackup`、`preset_version 9`は変更なし
- DSP／Adaptive Tone Balanceアルゴリズム、12種類の内蔵プリセット値は変更なし

## v0.6.3の変更点

v0.6.3は、DSP／Adaptive Tone Balanceの処理を変更せず、現在状態とATBの動作を分かりやすくするUI・文書改善版です。

### カスタム状態

- 現在のDSP設定が12種類のどの内蔵プリセットとも完全一致しない場合、内蔵プリセット欄に `カスタム / Custom` を表示
- `カスタム / Custom` は表示専用で、13番目の内蔵プリセットではない
- Custom表示中は内蔵プリセットの「呼出 / Load」を無効化
- 実在する内蔵プリセットを選択しただけでは適用せず、従来どおり「呼出 / Load」で適用
- 日本語／English切り替えでは表示名だけを切り替え

### ATB ON時のDepth／Clarity表示を明確化

適応型音色補正がONのとき：

- Depthを **低域自動補正上限 (Depth) / Depth (Auto Low Limit)** として表示
- Clarityを **高域自動補正上限 (Clarity) / Clarity (Auto High Limit)** として表示
- 100%は常時+10 dBを加える意味ではなく、自動補正へ与える最大許容量であることを明記
- 既存のAuto Low／Auto High補正量表示は維持

ATB OFF時は従来の固定式Depth／Clarity表示へ戻ります。

### Help／Glossary

- ATBが不足分だけを補うboost-only方式であることを明記
- ATB ON時のDepth／Clarityが自動補正上限であることを説明
- Width／AmbienceはATB ONでも手動であることを説明
- 新規解析条件とPause／Resume時の解析履歴保持を説明
- GlossaryでAdaptive Tone Balance、Auto Low、Auto High、ATB Analysis Stateを個別に整理

### 互換性

- DSP処理変更なし
- Adaptive Tone Balance判定アルゴリズム変更なし
- 12種類の内蔵プリセット値変更なし
- SRP4変更なし
- `preset_version 9`変更なし
- 旧DSP presetおよびSRP1／SRP2／SRP3／SRP4の読み込み互換性を維持

## v0.6.2の変更点

v0.6.2では、foobar2000再起動後などに内蔵プリセット欄が実際の保存済みDSP設定と一致しない表示になる問題を修正しました。

- 現在のDSP設定を12種類の内蔵プリセットと照合し、完全一致するプリセット名を表示
- どの内蔵プリセットとも一致しない設定では、v0.6.2時点では未選択表示
- スライダー／チェックボックス変更、任意プリセット読込、A/B試聴・比較終了でも現在設定に合わせて表示を再同期
- 日本語／English切り替えでも同じ内部プリセット番号を維持
- コンボ項目を選択しただけではDSP設定を変更せず、「呼出 / Load」で適用
- DSP／ATBアルゴリズム、12種類の内蔵プリセット値、SRP4、`preset_version 9`は変更なし

## v0.6.1の変更点

### 再生位置変更時のATB解析状態を明確化

v0.6.1では、前の再生位置のAuto Low／Auto High値が新しい解析結果のように見えないよう、Adaptive Tone Balanceの状態表示を改善しました。

- 再生開始、Next、Previous、別曲への直接移動、自然な曲送り、シーク、Stop後の再生、ATB OFF→ONでは、新しい解析が十分に蓄積されるまで `自動補正：解析中... / Auto: Analyzing...` を表示
- 十分な新規解析後は通常のAuto Low／Auto High数値表示へ戻る
- Pause／Resumeでは現在の解析状態を保持し、解析をやり直さない
- 再生トラック変更／シークをruntime ATBへ確実に通知する仕組みを追加

### 互換性

- v0.6.0からDSP／Adaptive Tone Balance判定アルゴリズム変更なし
- Auto Low／Auto High上限は各 **+10.0 dB** のまま
- 任意プリセット／`.srpbackup`形式は **SRP4** のまま
- DSP preset形式は **preset_version 9** のまま
- 12種類の内蔵プリセットは変更なし
- 旧プリセット／バックアップ互換性は変更なし
- analyzer historyや現在のAuto Low／Auto High値は引き続き保存しない

## v0.6.0の変更点

### 「適応型標準」内蔵プリセット

v0.6.0では、v0.5.0で確定した適応型音色補正（ATB）のアルゴリズムを変更せず、
ATBを最大限利用するための内蔵プリセットを1種類追加しました。

- 12個目の内蔵プリセットとして **「適応型標準 / Adaptive Standard」** を追加
- Depth：**100**
- Clarity：**100**
- Width：**50**
- Ambience：**40**
- Master Strength：**100%**
- Output Gain：**0.0 dB**
- 自動ヘッドルーム保護：**オン**
- レベルマッチ・バイパス：**オン**
- Sonic Refiner：**有効**
- 適応型音色補正：**オン**
- ATB ON時はDepth／Clarityが自動補正の上限になるため、解析結果に応じてAuto Low／Auto Highがそれぞれ最大 **+10.0 dB** まで利用可能
- Width／Ambienceは既存「標準」と同じ値を維持し、音場だけが極端にならない構成
- 既存11種類の内蔵プリセットは変更せず、引き続き呼び出し時は **ATB OFF**

### UI調整

- `100% / 自動上限 +10.0 dB` など、日本語のATB上限表示が右端で切れないようDepth／Clarityの値表示欄を調整
- 設定画面サイズは **560 × 320** のまま

### 互換性

- v0.5.0からDSP／ATBアルゴリズム変更なし
- DSP書き込み形式は **preset_version 9** のまま
- 任意プリセット／`.srpbackup`書き込み形式は **SRP4** のまま
- SRP1／SRP2／SRP3／SRP4と旧DSP presetの読み込み互換性を維持
- analyzer history／Auto Low／Auto High／confidenceは引き続き保存しない
- A/B、Cancel、直接起動、日本語／English、既存の保護動作は変更なし

## v0.5.0の変更点

### 適応型音色補正 (Adaptive Tone Balance)

v0.5.0では任意で有効にできる**適応型音色補正（ATB）**を追加しました。
ATBがオフのときは、v0.4.0までの固定Depth／Clarity動作をそのまま維持します。

- 適応型音色補正の初期値は**オフ**
- Sonic Refiner処理前の原音を解析
- **Auto Low**はBass **60～180 Hz** とBody **200～500 Hz** を比較
- Low判定目標：Bass/Body **+6.5 dB**
- Auto Lowは原音を残したまま、フィルターした **60～180 Hz** のBass成分を並列加算
- **Auto High**はHigh/Mid（**3.5～10 kHz** 対 **300 Hz～2.0 kHz**）に加え、Treble/Presence（**5～10 kHz** 対 **2～5 kHz**）も使って補正量を決定
- High/Mid不足判定の基準は **-6 dB**、許容範囲は **1.5 dB**
- 自動補正は**不足分のブーストのみ**で、自動カットは行わない
- Auto Low絶対上限：**+10.0 dB**
- Auto High絶対上限：**+10.0 dB**
- ATB ON時のDepth／Clarityは固定補正量ではなく、**自動補正に許可する上限**
- Master Strengthは自動補正にも適用
- ゆっくりしたローリング解析と追従で、不自然なポンピングを抑制
- 約 **-55 dBFS** 未満の極小音では解析を更新しない
- 曲変更・シーク・Stop・ATB OFF→ONで解析をやり直し、Pause/Resumeでは保持
- マルチチャンネル解析は最初のL/Rを使用
- 通常UIでは現在の**自動補正：低域 / 高域**だけを表示し、開発用診断値は表示しない

### プリセット・互換性・A/B

- 既存11種類の内蔵プリセットは変更せず、呼び出し時は**ATB OFF**
- 既存プリセットをそのまま使い、必要なときだけATBをONにして使用可能
- 任意プリセットにはATBのON/OFFも保存
- 任意プリセット／`.srpbackup`書き込み形式：**SRP4**
- foobar2000 DSP preset書き込み形式：**preset_version 9**
- SRP1／SRP2／SRP3、旧DSP preset version 1～8を引き続き読み込み可能
- ATB項目を持たない旧データは**ATB OFF**として読み込む
- A/BにはDepth／Clarity／Width／Ambience／Master Strengthに加えてATB ON/OFFも保存
- A/Bの解析履歴や現在の自動補正量は保存しない
- 「比較終了」で比較開始直前の全設定へ復元

### リリース候補で確認した項目

- Light / Dark表示
- 連続再生
- 再起動後の設定保持
- キャンセル動作
- ATB ON/OFFを含む任意プリセットとSRP4バックアップ
- 旧SRP3読み込み
- A/BでのATB切替と比較開始前状態への復元
- 再起動後／ATB OFF→ON後の新規解析

## v0.4.0の変更点

### 設定画面の直接起動

- **Playback → Sonic Refiner の設定...** から、DSP Managerを経由せずActive DSPs内の1個のSonic Refinerを直接設定できます。
- 直接起動画面はモードレスでfoobar2000に所有され、画面を開いたままfoobar2000本体を操作できます。別アプリは通常どおり前面に出せます。
- **Preferences → Keyboard Shortcuts** から任意のショートカットキーを割り当てられます。初期割り当てはありません。
- Sonic RefinerがDSPチェーンにない場合、または複数登録されている場合は、安全のため直接編集を開始しません。
- 従来のDSP Manager経由の設定方法もそのまま利用できます。


v0.4.0では、一時的なA/B比較スロットとPlaybackメニューからの設定画面直接起動を追加しました。

- Depth、Clarity、Width、Ambience、Master StrengthをA/Bへ保存
- Output Gainや保護設定を変えずにA/Bを即時試聴
- 「比較終了」で比較開始直前の全設定へ復元
- A/B内容はDSP preset、任意プリセット、`.srpbackup`へ保存しない
- A/Bスロットはfoobar2000起動中のみ保持し、再起動後は空に戻る
- 日本語／Englishの両方に対応

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
- **適応型音色補正**：Bass/BodyとH/M＋T/P解析による音源依存のブースト型Low／High自動補正
- **Width**：約180 Hz以下を保護するMid/Side方式、Side最大600%
- **Ambience**：約11 ms・19 msの短い初期反射、Wet Mix最大85%
- **Master Strength**：4つの補正効果を0～100%で一括調整
- **Output Gain**：-12.0～+6.0 dB、0.5 dB刻み
- **自動ヘッドルーム保護**：約-0.2 dBFS付近の軽量なブロック／サンプルピーク保護
- **レベルマッチ・バイパス**：処理による平均音量増加分を抑えた比較
- 内蔵プリセット12種類
- UTF-8任意プリセット最大20件（名前変更対応）
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

## 内部処理順序

```text
適応型音色補正の解析（ON時・処理前原音）
→ Depth / 自動低域補正
→ Clarity / 自動高域補正
→ Width
→ Ambience
→ Master Strengthによる実効効果量
→ Level Match
→ Output Gain
→ Automatic Headroom Protection
```

## 推奨DSP順序

```text
Sonic Refiner
→ R128 Real-time Loudness Normalizer
→ Output
```

## 互換性

- DSP書き込み形式は`preset_version 9`
- 任意プリセット書き込み形式は`SRP4`
- `SRP1`／`SRP2`／`SRP3`／`SRP4`を読み込み可能
- 旧DSP preset version 1～8を読み込み可能。旧データでは適応型音色補正はオフ
- Master Strengthを持たない旧設定は100%
- Output Gainを持たない旧設定は0.0 dB
- 既存の日本語名を含む任意プリセット名は翻訳せず維持
- `.srpbackup`拡張子とバックアップヘッダーは維持し、旧バックアップを読み込み可能。新規バックアップの任意プリセット内容はSRP4

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
ビルドと梱包.cmd
```

出力：

```text
dist\foo_sonic_refiner_v0.6.5.fb2k-component
dist\SHA256SUMS.txt
```

詳しい手順は`README_FIRST.txt`、正式版の最終確認項目は`TESTING_v0.6.5.md`を参照してください。
