# Changelog

All notable public changes to Sonic Refiner are documented here.

## [0.3.0] - 2026-08-06

### Added

- Japanese and English user interface
- Language selection based on the Windows display language on first use
- Instant language switching without restarting foobar2000
- Persistent language preference stored separately from DSP settings
- Localized built-in preset names, controls, messages, file dialogs, Help, Glossary, Important Notes and License pages
- English-first public documentation

### Compatibility

- DSP processing behavior is unchanged from v0.2.0
- `preset_version 8` remains unchanged
- User-preset format remains `SRP3`
- SRP1, SRP2 and SRP3 remain readable
- `.srpbackup` format remains unchanged
- Existing user-preset names are preserved and are not translated
- Settings window remains 560 × 320

### Validation

- Release / x64 build and package creation confirmed
- Japanese and English switching confirmed without restart or crash
- User-preset save/load and backup export/import confirmed
- Light and dark modes, restart persistence, cancellation, and continuous playback operation confirmed

## [0.2.0] - 2026-08-03

### Added

- Master Strength control from 0% to 100%
- Effective-value labels that reflect Master Strength
- SRP3 user-preset format with Master Strength storage
- Integrated Help, Glossary and Safety Notice documentation for Master Strength

### Compatibility

- v0.1.x DSP settings load with Master Strength at 100%
- SRP1 and SRP2 user presets load with Master Strength at 100%
- Output Gain, Automatic Headroom and Level Match are not scaled
- Existing built-in presets retain their original sound at 100%
- Confirmed operation at 0%, 50% and 100%, preset save/restore, backup import/export, restart persistence, cancellation, light/dark modes and continuous playback control

## [0.1.1] - 2026-08-02

### Changed

- Unified the official downstream normalizer name as
  `R128 Real-time Loudness Normalizer`
- Updated the integrated Help, Glossary and Safety Notices
- Updated README, Quick Start, component package documentation and release notes
- Updated the formal package version and filename to `v0.1.1`

### Compatibility

- No DSP processing behavior was changed
- No preset values or preset file formats were changed
- Existing settings and SRP1/SRP2 user presets remain compatible

## [0.1.0] - 2026-08-02

### Added

- Initial public release
- Depth low-frequency enhancement
- Clarity high-frequency enhancement
- Frequency-dependent stereo Width processing with low-frequency protection
- Short early-reflection Ambience processing
- Output Gain from -12.0 dB to +6.0 dB
- Automatic headroom protection
- Level-matched bypass comparison
- Eleven built-in presets
- Up to 20 user presets
- User-preset export and import using `.srpbackup`
- Integrated Help, Glossary, Safety Notices and License pages
- Light and dark mode support
- Automated Release/x64 build and `.fb2k-component` packaging
- SHA-256 checksum generation

### Compatibility

- Reads legacy preview DSP settings
- Reads SRP1 and SRP2 user-preset formats
- Legacy settings without Output Gain load at 0.0 dB

### Notes

- Values from 80% to 100% are intended for strong effects and testing.
- Automatic Headroom is not a True Peak limiter.
- Recommended DSP order:
  `Sonic Refiner -> R128 Real-time Loudness Normalizer -> output`
