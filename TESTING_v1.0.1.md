# Sonic Refiner v1.0.1 Testing

## Basis

Formal v1.0.1 is produced from the user-validated v1.0.1-dev.1 source.
The formalization changes version/package/document identity only; DSP processing and the validated Monitor behavior are unchanged.

## v1.0.1-dev.1 real-machine validation results

- [x] Release / x64 build succeeded.
- [x] Package `foo_sonic_refiner_v1.0.1-dev.1.fb2k-component` generated and installed.
- [x] Preferences → Components showed `1.0.1-dev.1`.
- [x] Main settings caption showed `1.0.1-dev.1`.
- [x] Preset Manager caption showed `1.0.1-dev.1`.
- [x] Normal playback had no dropout, click, noise or unexpected level change.
- [x] Processing Monitor updated normally during playback.
- [x] Pause changed all four Monitor values to `—`.
- [x] Pause emptied all four Monitor meter bars.
- [x] Monitor status showed `Paused` / `一時停止中`.
- [x] Resume restored live Monitor values.
- [x] Pause / Resume produced no abnormal Reverb behavior.
- [x] Next / Previous continued Monitor updates.
- [x] Seek continued Monitor updates.
- [x] Stop → Play restored Monitor updates.
- [x] All 16 built-in presets remained present.
- [x] English → Automatic (Windows) display-language switching propagated to Monitor normally.

## Formal v1.0.1 post-build minimum check

Validated on foobar2000 v2.26.1:

- [x] Release / x64 build succeeded.
- [x] `foo_sonic_refiner_v1.0.1.fb2k-component` was generated.
- [x] Preferences → Components showed `1.0.1`.
- [x] Pause showed four `—` values and empty bars.
- [x] Resume restored live Monitor values.
- [x] Normal playback passed without dropout, click, noise or unexpected level change.
- [x] `dist\SHA256SUMS.txt` was recorded before publication.

Formal component SHA-256:

`f018bdc1ff69752253e5ec76d2b5e8ff99036e4827dd6616939c8814c03f5515`

## Compatibility requirement

SRP5, `preset_version 10`, `.srpbackup`, legacy readers, all 16 built-in preset values and all formal v1.0.0 DSP behavior remain unchanged.
