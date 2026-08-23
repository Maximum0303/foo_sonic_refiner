# Sonic Refiner v0.6.1

Sonic Refiner v0.6.1 is a small UI-state reliability update for Adaptive Tone Balance (ATB).

## Fixed

- Playback start, Next, Previous, direct track jumps, natural track changes, seeks,
  Stop -> playback, and ATB Off -> On now show
  `自動補正：解析中...` / `Auto: Analyzing...`
  while fresh analysis is being accumulated.
- Previous Auto Low / Auto High values are no longer presented as if they were
  the completed result for the new playback position.
- New-track and seek notifications use a runtime-only discontinuity generation
  consumed by the ATB processor so analysis reliably restarts for the new playback position.
- Pause / Resume continues to preserve the current ATB analysis state.

## Compatibility

- DSP / ATB Low and High decision algorithms are unchanged from v0.6.0.
- Auto Low / Auto High absolute maximum remains +10.0 dB.
- SRP4 is unchanged.
- `preset_version 9` is unchanged.
- All 12 built-in presets are unchanged.
- Legacy DSP preset and SRP1 / SRP2 / SRP3 / SRP4 compatibility is unchanged.
- Runtime analyzer history and current automatic-gain state remain non-persistent.

## Validation

The release candidate was checked for:

- Playback start -> analyzing state
- Next -> analyzing state
- Previous -> analyzing state
- Direct track jump -> analyzing state
- Seek -> analyzing state
- Natural track advance -> analyzing state
- Stop -> playback -> analyzing state
- ATB Off -> On -> analyzing state
- Pause -> Resume preserves analysis
- Analyzing state returns to numeric Auto Low / Auto High after sufficient fresh analysis
- Japanese and English UI
- Light and Dark mode
- Full-track playback with no dropout, click noise, abrupt unnatural tonal change, or crash

## Recommended DSP order

```text
Sonic Refiner
-> R128 Real-time Loudness Normalizer
-> Output
```

---

# Sonic Refiner v0.6.1 日本語

Sonic Refiner v0.6.1は、Adaptive Tone Balance（ATB／適応型音色補正）の
解析状態表示を分かりやすくする小規模な修正版です。

## 修正内容

- 再生開始、次の曲、前の曲、別曲への直接移動、自然な曲送り、シーク、
  Stop後の再生、ATB OFF -> ONで、新しい解析中は
  `自動補正：解析中...`
  と表示します。
- 前の再生位置のAuto Low／Auto High値を、新しい曲の解析完了値のように
  見せてしまう状態を解消しました。
- 新しい曲／シーク通知をruntime専用のdiscontinuity generationでATB処理へ伝え、
  新しい再生位置で解析を確実にやり直します。
- Pause -> Resumeでは従来どおり解析状態を維持します。

## 互換性

- v0.6.0からDSP／ATB Low・High判定アルゴリズムの変更なし
- Auto Low／Auto High絶対上限は各+10.0 dBのまま
- SRP4変更なし
- `preset_version 9`変更なし
- 12種類の内蔵プリセット変更なし
- 旧DSP preset、SRP1／SRP2／SRP3／SRP4互換性を維持
- analyzer履歴や現在の自動補正値は引き続きruntime専用で非保存

## 推奨DSP順序

```text
Sonic Refiner
-> R128 Real-time Loudness Normalizer
-> Output
```
