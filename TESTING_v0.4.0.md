# Sonic Refiner v0.4.0 Release Test Record

Release validation completed on 2026-08-22.

## Build / install
- [x] Release / x64 build succeeds
- [x] `dist\foo_sonic_refiner_v0.4.0-dev.5.fb2k-component` development package was successfully built and installed before promotion
- [x] foobar2000 starts normally after installation

## A/B comparison
- [x] A and B store Depth, Clarity, Width, Ambience, and Master Strength
- [x] A/B listening switches only the five intended parameters
- [x] Output Gain, Auto Headroom Protection, Level-Matched Bypass, and enabled state remain outside A/B switching
- [x] End Comparison restores the complete pre-comparison settings
- [x] Editing a slider does not overwrite a stored slot until Store A / Store B is pressed
- [x] Built-in presets and user presets work with A/B comparison
- [x] A/B data is not written to user presets or `.srpbackup`
- [x] A/B slots clear after restarting foobar2000
- [x] Repeated A/B switching during playback causes no audio interruption, abnormal noise, unexpected level jump, or crash

## Direct settings access
- [x] Playback menu opens Sonic Refiner settings directly
- [x] Japanese and English command names follow the selected UI language
- [x] Opening the command again reactivates the existing direct window instead of creating another
- [x] foobar2000 remains usable while the direct window is open
- [x] The owned window stays above foobar2000 but is not topmost over unrelated applications
- [x] Minimizing/restoring foobar2000 hides/restores the direct settings window as expected
- [x] OK keeps changes; Cancel restores the settings present when the window was opened
- [x] A/B comparison works from the direct settings window
- [x] Missing Sonic Refiner instance is detected and direct editing is refused
- [x] Multiple Sonic Refiner instances are detected and direct editing is refused
- [x] Removing the active instance while the direct window is open is detected safely
- [x] Keyboard Shortcuts command is available and works
- [x] Shortcut assignment remains valid after Japanese/English switching

## UI
- [x] Japanese + Light
- [x] Japanese + Dark
- [x] English + Light
- [x] English + Dark
- [x] End Comparison remains readable when disabled
- [x] Master/Output/Protection group border is intact
- [x] No right-edge or bottom-edge clipping
- [x] Settings window remains 560 × 320

## Compatibility
- [x] DSP processing algorithm unchanged from v0.3.0
- [x] `preset_version 8` unchanged
- [x] `SRP3` write format unchanged
- [x] `SRP1`, `SRP2`, and `SRP3` read compatibility retained
- [x] `.srpbackup` format unchanged
- [x] Existing settings and user presets remain compatible
