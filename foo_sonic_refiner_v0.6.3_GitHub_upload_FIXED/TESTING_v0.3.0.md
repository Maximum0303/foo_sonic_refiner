# Sonic Refiner v0.3.0 Release Test Record

Test date: 2026-08-06  
Environment: Windows, Visual Studio 2022, Release / x64, Japanese Windows display language

## 1. Build and package

- [x] Release / x64 build succeeds
- [x] `x64\Release\foo_sonic_refiner.dll` is created
- [x] `dist\foo_sonic_refiner_v0.3.0.fb2k-component` is created
- [x] `dist\SHA256SUMS.txt` is created

## 2. Language behavior

- [x] Japanese Windows display language defaults to 日本語
- [x] Selected language is remembered after restarting foobar2000
- [x] 日本語 → English updates the open settings window
- [x] English → 日本語 updates the open settings window
- [x] Cancel does not undo the language preference
- [x] No crash, playback stop, sound interruption, or sudden level change
- [x] Slider values remain unchanged during language switching
- [ ] Non-Japanese Windows first-run default to English was not directly runtime-tested on a non-Japanese Windows installation

## 3. Localized UI

- [x] Main labels and buttons
- [x] Eleven built-in preset names and order
- [x] Status text
- [x] User-preset save, load, and delete
- [x] Export and import file dialogs and messages
- [x] Help, Glossary, Important Notes, and License
- [x] No text overlap or right-edge clipping

## 4. Presets and backup

- [x] User preset saved and loaded in English UI
- [x] User-preset name remains unchanged after switching to Japanese
- [x] `.srpbackup` export succeeds
- [x] Deleting and importing restores the user preset and stored values
- [x] Import does not change the current DSP settings
- [x] Language preference is separate from preset and backup data

## 5. Regression tests

- [x] Built-in preset switching works
- [x] Master Strength, Output Gain, Auto Headroom, and Level Match retain expected behavior
- [x] Cancel restores the pre-dialog sound settings
- [x] Apply and OK persist settings after restart
- [x] Light mode layout is correct
- [x] Dark mode layout is correct
- [x] Continuous Master Strength operation during playback is stable
- [x] Continuous language switching during playback is stable

## Compatibility retained

- `preset_version 8`
- `SRP3` write format
- `SRP1` / `SRP2` / `SRP3` read compatibility
- `.srpbackup` format
- Existing UTF-8 user-preset names
- Built-in preset values and order
- Settings window size 560 × 320
