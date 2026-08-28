# Sonic Refiner v0.3.0 Release Notes

Release date: 2026-08-06

## Added

- Japanese and English user interface
- First-run default based on the Windows display language
- Instant language switching without restarting foobar2000
- Persistent language preference stored separately from DSP settings
- Localized built-in preset names, controls, status text, messages, file dialogs, Help, Glossary, Important Notes, and License pages
- English-first public documentation

## Compatibility

- DSP processing behavior is unchanged from v0.2.0
- Settings window remains 560 × 320
- `preset_version 8` remains unchanged
- User-preset write format remains `SRP3`
- `SRP1`, `SRP2`, and `SRP3` remain readable
- `.srpbackup` format remains unchanged
- Existing UTF-8 user-preset names are preserved and are not translated
- Built-in preset values and order remain unchanged

## Language behavior

- Japanese Windows display language defaults to Japanese on first use
- Other Windows display languages default to English on first use
- The language selector updates the open settings window immediately
- Language switching does not recreate or reinitialize the DSP
- Slider values and current sound settings are unchanged
- Language preference is not stored in DSP presets, user presets, or `.srpbackup` files
- Cancel restores sound settings but does not undo a language change

## Validation

Confirmed on Windows with Visual Studio 2022, Release / x64:

- Build and `.fb2k-component` packaging
- Japanese → English and English → Japanese switching
- Help, Glossary, Important Notes, and License pages
- Built-in and user presets
- Backup export and import
- Light and dark modes
- Restart persistence
- Cancel restoration
- Continuous Master Strength and language operation during playback

## Deferred

- A/B comparison slots are planned for a later feature release.
