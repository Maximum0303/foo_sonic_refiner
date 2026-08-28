# Sonic Refiner v0.6.3 Testing

Formal v0.6.3 is based on v0.6.3-dev.3.

## Confirmed in v0.6.3-dev.1

### Custom / カスタム state

- Standard matched and displayed normally.
- Changing Depth 55 -> 60 immediately changed the Built-in Presets display to
  `カスタム / Custom`.
- Custom settings and Custom display survived foobar2000 restart.
- The built-in Load button was disabled while Custom was displayed.
- Selecting Standard in the combo alone did not change Depth 60.
- Pressing Load applied Standard and restored Depth 55.
- Japanese / English switching changed `カスタム` <-> `Custom` without changing
  DSP values.
- Loading a user preset whose values were custom restored the Custom display.
- A/B switching correctly displayed Custom for A and Standard for B.
- End Comparison restored the pre-comparison Standard settings and display.
- Cancel restored Standard after a temporary custom change.
- Light / Dark display showed no clipping, overlap, or broken borders.
- Full-track Adaptive Standard playback completed without dropout, click/pop,
  abrupt unnatural low/high change, or crash.

## Confirmed in v0.6.3-dev.2

### ATB Depth / Clarity labels

- ATB OFF: original `Depth` / `Clarity` labels shown.
- ATB ON Japanese:
  `低域自動補正上限 (Depth)` / `高域自動補正上限 (Clarity)`.
- ATB ON English:
  `Depth (Auto Low Limit)` / `Clarity (Auto High Limit)`.
- The descriptions clearly communicate that 100% is an upper permission, not
  a constant +10 dB boost.
- Japanese / English switching preserved the current DSP settings.
- Japanese / English and Light / Dark combinations showed no clipping,
  overlap, or broken borders.
- Custom display and ATB limit labels coexisted correctly.
- Restart restored Depth 95 / ATB ON / Custom and the ATB limit labels.
- Cancel restored the previously committed ATB ON state and labels.
- Full-track Adaptive Standard playback completed without dropout, click/pop,
  abrupt unnatural low/high change, or crash.

## Confirmed in v0.6.3-dev.3

### Help / Glossary

- Japanese Help clearly explains boost-only correction, Depth / Clarity as
  limits, 100% not meaning constant +10 dB, manual Width / Ambience, and fresh
  analysis behavior.
- Japanese Glossary clearly separates Adaptive Tone Balance, Auto Low,
  Auto High, and ATB Analysis State.
- English Help and Glossary communicate the same concepts naturally.
- Help and Glossary were verified in Japanese / English, Light / Dark.
- No clipping, paragraph overlap, scroll problem, or unreadable contrast.
- Existing Adaptive Standard / Custom / ATB limit-label behavior remained
  correct after the documentation changes.
- Restart preserved the custom ATB settings and corresponding UI state.
- Full-track Adaptive Standard playback completed without dropout, click/pop,
  abrupt unnatural low/high change, or crash.

## Compatibility

- DSP / ATB algorithms unchanged.
- All 12 built-in preset values unchanged.
- SRP4 unchanged.
- `preset_version 9` unchanged.
- Legacy compatibility unchanged.
