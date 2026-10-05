# Sonic Refiner Processing Monitor / Sonic Refiner 補正モニター

Sonic Refiner (`foo_sonic_refiner`)

Monitor added in **v0.9.0**. The built-in **How to read the monitor... / モニターの見方...** guide is added in **v0.9.1**.

[English](#english) | [日本語](#日本語)

## English

### The four values

The monitor refreshes the current correction state about every 100 ms.

#### 1. Auto Low

Current low-frequency automatic correction from Adaptive Tone Balance (ATB). ATB boosts only low-frequency energy it considers deficient; it does not apply automatic cuts. `+0.0 dB` means no correction. Larger positive values mean stronger low-frequency correction. The allowed maximum follows the Depth setting, with an absolute ceiling of `+15.0 dB`. When ATB is off, the row shows `OFF`. During analysis, it shows `...`.

#### 2. Auto High

Current high-frequency automatic correction from ATB. `+0.0 dB` means no correction. Larger positive values mean stronger high-frequency correction. The allowed maximum follows the Clarity setting, with an absolute ceiling of `+15.0 dB`. A 100% setting does not mean a constant +15 dB boost. When ATB is off, the row shows `OFF`. During analysis, it shows `...`.

#### 3. Auto Headroom

Current protection gain from Auto Headroom Protection. `+0.0 dB` means no attenuation. Negative values show how much the whole signal is being reduced. It is lightweight protection designed to avoid reacting strongly to brief transients and to reduce sustained excessive peaks smoothly. It is not a True Peak limiter. Final True Peak management belongs to the downstream R128 Real-time Loudness Normalizer. When Auto Headroom is off, the row shows `OFF`.

#### 4. Level Match

Current attenuation from Level-Matched Bypass. It gently reduces average level added by enhancement so original/processed comparisons are less biased by simple loudness differences. `+0.0 dB` means no attenuation. Negative values mean level-matching attenuation. This stage never boosts; it attenuates only when needed. When Level-Matched Bypass is off, the row shows `OFF`.

### Units and bars

| Value | Bar range |
|---|---|
| Auto Low / Auto High | 0 to 15 dB |
| Auto Headroom / Level Match | Magnitude 0 to 12 dB |

Bars visualize correction magnitude. Auto Headroom and Level Match use the absolute magnitude for the bar even though their numeric values are negative during attenuation. A full bar is not a sound-quality or safety rating. If the displayed value exceeds the bar range, only the bar clamps at its endpoint while the number keeps the actual value.

### Display states

- **Active**: current values are being displayed.
- **Analyzing**: ATB is analyzing; Auto Low / Auto High show `...`.
- **Waiting**: playback is stopped; current values show an em dash.
- **Paused**: playback is paused; the most recent displayed values are retained.
- **Disabled**: Sonic Refiner is disabled, absent from the DSP chain, or cannot be identified safely.

An em dash means no reliable current value. It is different from numeric zero or `OFF`.

### Reading it and DSP order

Check the state first. When ATB is active, watch Auto Low and Auto High. Then check whether Auto Headroom or Level Match remains unusually large for long periods. Momentary readings alone do not rate sound quality.

Example: `Sonic Refiner → R128 Real-time Loudness Normalizer → Output`

Sonic Refiner handles tone and soundstage enhancement. R128 handles final loudness and True Peak. The two monitors use different values and measurement methods, so their numbers should not simply be added.

Open: **Playback → Sonic Refiner Processing Monitor**

Right-click → **Always on Top** toggles topmost display.

Right-click → **How to read the monitor...** opens this guide.

Position, visibility and topmost state are saved. Leaving the monitor open when quitting foobar2000 restores it on the next startup. Closing it manually prevents that restoration.

This is a display window. Opening, closing or reading this guide does not change DSP audio processing or settings.

## 日本語

### 4項目の意味

補正モニターは約100 ms間隔で現在の補正状態を表示します。

#### 1. 低域補正 / Auto Low

Adaptive Tone Balance（ATB）による現在の低域自動補正量です。ATBは不足していると判断した低域だけを補い、自動カットは行いません。`+0.0 dB`は補正なし、プラス値が大きいほど低域を強く補っています。最大許容量はDepth設定に従い、絶対上限は`+15.0 dB`です。ATBがオフなら「オフ」、解析中は`...`と表示します。

#### 2. 高域補正 / Auto High

ATBによる現在の高域自動補正量です。`+0.0 dB`は補正なし、プラス値が大きいほど高域を強く補っています。最大許容量はClarity設定に従い、絶対上限は`+15.0 dB`です。100%設定でも常時+15 dBになるわけではありません。ATBがオフなら「オフ」、解析中は`...`と表示します。

#### 3. 自動ヘッドルーム / Auto Headroom

Auto Headroom Protectionによる現在の保護ゲインです。`+0.0 dB`は減衰なし、マイナス値は全体を抑えている量を表します。短い瞬間ピークにはできるだけ反応せず、持続的な大きいピークだけを滑らかに抑える軽量保護です。True Peak limiterではありません。最終True Peak管理は後段のR128 Real-time Loudness Normalizerが担当します。Auto Headroomがオフなら「オフ」と表示します。

#### 4. レベル一致 / Level Match

Level-Matched Bypassによる現在のレベル合わせ量です。補正で増えた平均音量を穏やかに抑え、原音との比較で単なる音量差に惑わされにくくするための値です。`+0.0 dB`は減衰なし、マイナス値はレベル合わせのための減衰を表します。この処理は増幅せず、必要な場合だけ減衰します。Level-Matched Bypassがオフなら「オフ」と表示します。

### 単位とバー

| 項目 | バーの範囲 |
|---|---|
| 低域補正／高域補正 | 0～15 dB |
| 自動ヘッドルーム／レベル一致 | 絶対値0～12 dB |

バーは補正量の「大きさ」を見やすくした表示です。自動ヘッドルームとレベル一致は数値がマイナスでも、バーは絶対値で伸びます。バーが満杯だから音質が良い／悪い、安全／危険という意味ではありません。表示範囲を超えた場合はバーだけ端で止まり、数値は実際の値を表示します。

### 表示状態

- **動作中 / Active**：現在の値を表示しています。
- **解析中 / Analyzing**：ATBが解析中です。低域補正／高域補正は`...`になります。
- **待機中 / Waiting**：再生していません。現在値は「—」になります。
- **一時停止中 / Paused**：再生を一時停止しています。直前の表示値を保持します。
- **無効 / Disabled**：Sonic Refinerが無効、DSPチェーンにない、または安全に対象を特定できません。

「—」は現在値を表示できない状態です。数値の0や「オフ」とは意味が異なります。

### 読み方とDSP順序

まず状態を確認し、ATB使用時は低域補正／高域補正を見ます。次に自動ヘッドルームとレベル一致が必要以上に大きく動き続けていないかを確認します。瞬間的な数値だけで音質の良し悪しを判断するものではありません。

例：`Sonic Refiner → R128 Real-time Loudness Normalizer → 出力`

Sonic Refinerは音色・音場補正を担当し、R128は最終ラウドネスとTrue Peakを管理します。両モニターは表示する値・測定方法が異なるため、数値を単純に足し算しないでください。

開く：**Playback → Sonic Refiner 補正モニター**

右クリック → **常に手前に表示**：最前面表示を切り替えます。

右クリック → **モニターの見方...**：この解説を開きます。

位置・開閉状態・最前面設定を保存します。開いたままfoobar2000を終了すると次回起動時に再表示します。手動で閉じた場合は再表示しません。

この窓は表示用です。開く・閉じる・解説を読む操作でDSP音声処理や設定を変更しません。
