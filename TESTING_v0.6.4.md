# Sonic Refiner v0.6.4 Testing

## Release basis

- Formal release basis: **v0.6.4-dev.1**
- v0.6.4-dev.1 required tests: **all passed**
- Formalization changes only version/package text and formal release documentation; the validated Rename implementation is unchanged.

## Passed tests

1. Release / x64 build with `ビルドと梱包.cmd`.
2. Confirmed settings-window title `Sonic Refiner - 0.6.4-dev.1` in the validated development build.
3. Confirmed `名前変更... / Rename...` disabled with no user preset selected.
4. Saved a recognizable user preset: Depth 61, Clarity 47, Width 53, Ambience 42, Master Strength 88, ATB On.
5. Opened Rename for the selected user preset.
6. Confirmed the current name was prefilled and selected.
7. Renamed the preset and confirmed only the displayed user-preset name changed.
8. Loaded the renamed preset and confirmed all stored settings remained unchanged.
9. Created a second preset and confirmed renaming the first to the second preset's exact name was rejected.
10. Confirmed renaming a preset to its existing name is a harmless no-op.
11. Confirmed Japanese / English button and dialog localization.
12. Confirmed Light / Dark mode without clipping, overlap, or unreadable disabled text.
13. Exported `.srpbackup`, removed/imported presets, and confirmed renamed names and settings restored correctly.
14. Confirmed all 12 built-in presets are unchanged and have no rename operation.
15. Completed a full-track playback smoke test without audio dropout, click/pop, abrupt tonal change, or crash.
16. Confirmed Cancel / OK and A/B Store / Listen / End Comparison behavior remain unchanged.

## Compatibility confirmed by design and regression scope

- SRP4 unchanged.
- `preset_version 9` unchanged.
- `.srpbackup` wrapper/format unchanged.
- DSP / ATB algorithm unchanged.
- All 12 built-in preset values unchanged.
- Legacy DSP preset and SRP1 / SRP2 / SRP3 / SRP4 compatibility preserved.

## Formal v0.6.4 post-build checks

After building the formal source, confirm:

- Settings-window title: `Sonic Refiner - 0.6.4`.
- Output package: `dist\foo_sonic_refiner_v0.6.4.fb2k-component`.
- `dist\SHA256SUMS.txt` names the v0.6.4 package.
- Rename smoke test still passes.
- Full-track playback remains normal.
