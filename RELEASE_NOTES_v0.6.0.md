# Sonic Refiner v0.6.0

Sonic Refiner v0.6.0 adds one built-in preset designed to make full practical
use of the Adaptive Tone Balance (ATB) introduced in v0.5.0.

The DSP and ATB algorithms themselves are unchanged from v0.5.0.

## Adaptive Standard / 適応型標準

The new 12th built-in preset uses:

- Depth: 100
- Clarity: 100
- Width: 50
- Ambience: 40
- Master Strength: 100%
- Output Gain: 0.0 dB
- Auto Headroom Protection: On
- Level-Matched Bypass: On
- Sonic Refiner: Enabled
- Adaptive Tone Balance: On

With ATB enabled, Depth and Clarity are maximum permissions rather than fixed
boost amounts. Adaptive Standard therefore allows Auto Low and Auto High to use
their full permitted range, up to +10.0 dB each when analysis determines that
correction is needed.

Width and Ambience retain the existing Standard preset values, so the preset
does not turn the soundstage controls into extreme-effect settings.

The existing 11 built-in presets are unchanged and continue to load ATB Off.

## UI refinement

The Depth and Clarity value fields were widened so Japanese ATB limit text such
as:

```text
100% / 自動上限 +10.0 dB
```

is fully visible.

The settings window remains 560 × 320.

## Compatibility

- DSP write format: `preset_version 9`
- User preset / `.srpbackup` write format: `SRP4`
- SRP1 / SRP2 / SRP3 / SRP4 remain readable
- Legacy DSP preset versions remain readable
- Legacy data without an ATB field loads with ATB Off
- Runtime analyzer history, Auto Low / Auto High values, and confidence are not persisted
- A/B behavior and Cancel restoration are unchanged
- Direct settings access and Keyboard Shortcuts support are unchanged
- Japanese / English UI behavior is unchanged

## Validation

The v0.6.0 release candidate was checked for:

- Japanese and English UI
- Light and Dark mode
- Adaptive Standard preset values
- full `自動上限 +10.0 dB` display without clipping
- ATB operation during playback
- restart persistence
- existing Standard preset returning ATB Off
- A/B ATB switching and pre-comparison restoration
- clean Cancel restoration
- ATB-On user preset save/restore
- SRP4 `.srpbackup` export/import
- continuous full-track playback without dropouts, clicks, sudden tonal jumps, or crashes
- exact source helper filename `ビルドと梱包.cmd`

## Recommended DSP order

Sonic Refiner
→ R128 Real-time Loudness Normalizer
→ Output

Sonic Refiner remains responsible for tone and soundstage processing.
Final loudness management, True Peak protection, and limiting remain the job of
the downstream R128 Real-time Loudness Normalizer.
