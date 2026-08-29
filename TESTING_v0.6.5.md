# Sonic Refiner v0.6.5 Testing

## Release basis

- Formal release basis: **v0.6.5-dev.1**
- v0.6.5-dev.1 required regression sequence: **passed**
- Formalization changes only version/package text and formal release documentation; the validated user-preset reordering implementation is unchanged.

## Passed tests

1. Release / x64 build with `ビルドと梱包.cmd`.
2. Confirmed settings-window title `Sonic Refiner - 0.6.5-dev.1` in the validated development build.
3. Confirmed the 560 x 320 dialog displays `↑` / `↓` without overlap or clipping.
4. Confirmed both move buttons are disabled with no user preset selected.
5. Confirmed first-item `↑` disabled / `↓` enabled and last-item `↑` enabled / `↓` disabled.
6. Confirmed Down moves the selected preset one position and preserves selection and preset content.
7. Confirmed Up restores the preset one position and preserves selection.
8. Confirmed reordered list order survives a full foobar2000 restart.
9. Exported `.srpbackup`, changed the order, imported the backup, and confirmed the exported order is restored.
10. Loaded a moved preset and confirmed stored Depth / Clarity / Width / Ambience / Master Strength / Output Gain / ATB state are unchanged.
11. Renamed a moved preset and confirmed Rename remains functional without changing order unexpectedly; restored the original name successfully.
12. Deleted a test preset and confirmed the remaining relative order is preserved.
13. Saved a new preset and confirmed it is appended without disturbing the existing order.
14. Confirmed Japanese / English layout and `↑` / `↓` display.
15. Confirmed Dark Mode and Light Mode without overlap, clipping, or unreadable move-button state.
16. Completed a full-track playback smoke test without dropout, click/pop, abrupt tonal change, stop, or crash.
17. Confirmed both move buttons are disabled when only one user preset exists.
18. Restored the user-preset list from `.srpbackup` and confirmed presets and order returned.
19. Confirmed A/B Store / Listen / End Comparison behavior remains unchanged.
20. Confirmed all 12 built-in presets remain available and do not expose reordering controls.
21. Confirmed Adaptive Standard values remain Depth 100 / Clarity 100 / Width 50 / Ambience 40 / Master Strength 100% / Output Gain 0.0 dB / Auto Headroom On / Level-Matched Bypass On / Sonic Refiner enabled / ATB On.
22. Confirmed track change enters `自動補正：解析中... / Auto: Analyzing...` and returns to normal Auto Low / Auto High display after sufficient fresh analysis.

## Compatibility confirmed by design and regression scope

- SRP4 unchanged.
- `preset_version 9` unchanged.
- `.srpbackup` wrapper/format unchanged.
- DSP / ATB algorithm unchanged.
- All 12 built-in preset values unchanged.
- Legacy DSP preset and SRP1 / SRP2 / SRP3 / SRP4 compatibility preserved.
- A/B semantics, direct settings access, JP/EN, and Light/Dark behavior preserved.

## Formal v0.6.5 post-build checks

After building the formal source, confirm:

- Settings-window title: `Sonic Refiner - 0.6.5`.
- Output package: `dist\foo_sonic_refiner_v0.6.5.fb2k-component`.
- `dist\SHA256SUMS.txt` names the v0.6.5 package.
- One `↑` / `↓` reordering smoke test still passes.
- Restart persistence still passes.
- Full-track playback remains normal.
