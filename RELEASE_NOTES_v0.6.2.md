# Sonic Refiner v0.6.2

v0.6.2 fixes the Built-in Presets display so it accurately reflects the
currently restored DSP settings.

## Changes

- After restarting foobar2000, the Built-in Presets combo now shows the
  built-in preset that exactly matches the restored DSP settings.
- Example: if `Adaptive Standard` is still active after restart, the combo now
  displays `Adaptive Standard` instead of incorrectly falling back to
  `Standard`.
- If the current DSP settings do not exactly match any built-in preset, the
  combo remains unselected rather than showing a misleading preset name.
- Manual parameter changes, user-preset loads, and A/B listening keep the
  displayed built-in preset selection synchronized with the current settings.
- Merely selecting an item in the combo still does not apply it. The existing
  Load button behavior is preserved.
- Japanese / English switching keeps the same internal preset selected and
  changes only the displayed name.

## Compatibility

- No DSP processing changes.
- No Adaptive Tone Balance algorithm changes.
- All 12 built-in preset values are unchanged.
- SRP4 remains unchanged.
- `preset_version 9` remains unchanged.
- Legacy DSP presets and SRP1 / SRP2 / SRP3 / SRP4 compatibility are
  preserved.
- A/B comparison behavior and persistence rules are unchanged.
- Runtime ATB analysis behavior is unchanged.

## 推奨DSP順序

`Sonic Refiner → R128 Real-time Loudness Normalizer → Output`
