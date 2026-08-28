# Sonic Refiner v0.6.3

v0.6.3 refines the settings UI and built-in documentation without changing
the validated DSP / Adaptive Tone Balance processing.

## Changes

### Custom / カスタム display

- If the current DSP settings do not exactly match any of the 12 built-in
  presets, the Built-in Presets combo now displays `Custom / カスタム`.
- Custom is a UI-only state, not a 13th built-in preset.
- The built-in preset Load button is disabled while Custom is displayed.
- Selecting a real built-in preset still requires Load before DSP settings are
  changed.
- Japanese / English switching updates only the displayed Custom label.

### Clearer ATB control labels

- With Adaptive Tone Balance ON, Depth is identified as the Auto Low correction
  limit.
- With Adaptive Tone Balance ON, Clarity is identified as the Auto High
  correction limit.
- The ATB-mode descriptions clarify that 100% grants the maximum permitted
  correction range; it does not force a constant +10 dB boost.
- With ATB OFF, the original fixed-mode Depth / Clarity labels and descriptions
  are restored.

### Help / Glossary clarity

- Reorganized the ATB Help around practical behavior.
- Clarified that ATB is boost-only.
- Clarified that Depth / Clarity are automatic correction limits while ATB is
  ON.
- Clarified that Width / Ambience remain manual.
- Clarified fresh-analysis conditions and Pause / Resume history preservation.
- Added separate Glossary entries for Adaptive Tone Balance, Auto Low,
  Auto High, and ATB Analysis State using the current validated frequency
  ranges.

## Compatibility

- No DSP processing changes.
- No Adaptive Tone Balance decision-algorithm changes.
- All 12 built-in preset values are unchanged.
- SRP4 remains unchanged.
- `preset_version 9` remains unchanged.
- Legacy DSP preset and SRP1 / SRP2 / SRP3 / SRP4 compatibility is preserved.
- A/B persistence rules are unchanged.
- Runtime ATB analyzer history remains non-persistent.

## Recommended DSP order

`Sonic Refiner → R128 Real-time Loudness Normalizer → Output`
