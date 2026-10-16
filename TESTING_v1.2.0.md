# Sonic Refiner v1.2.0 Testing

Target host: foobar2000 v2.26.1  
Build: Release / x64  
SDK: SDK-2025-03-07

## Validated development build: v1.2.0-dev.1

- [x] `build_and_package.cmd` succeeded.
- [x] `dist\foo_sonic_refiner_v1.2.0-dev.1.fb2k-component` was generated.
- [x] Component installed successfully.
- [x] Preferences → Components showed `1.2.0-dev.1`.

## New built-in presets

- [x] Built-in preset count is 18.
- [x] `適応型低域強調 / Adaptive Bass Emphasis` is present.
- [x] Bass Emphasis loads Depth 100 / Clarity 65 / Width 50 / Ambience 40 / Reverb 0.
- [x] Bass Emphasis loads Master 100 / Output 0.0 dB / Auto Headroom ON / Level-Matched Bypass ON / Sonic Refiner ON / ATB ON.
- [x] `適応型高域強調 / Adaptive Treble Emphasis` is present.
- [x] Treble Emphasis loads Depth 65 / Clarity 100 / Width 50 / Ambience 40 / Reverb 0.
- [x] Treble Emphasis loads Master 100 / Output 0.0 dB / Auto Headroom ON / Level-Matched Bypass ON / Sonic Refiner ON / ATB ON.
- [x] Adaptive Standard retained Depth 100 / Clarity 100 / Width 50 / Ambience 40 / Reverb 0 / ATB ON.
- [x] English names are Adaptive Bass Emphasis / Adaptive Treble Emphasis.
- [x] Automatic (Windows) returns to Japanese correctly.

## Listening / runtime behavior

- [x] Adaptive Bass Emphasis played normally with no reported dropout, noise, click or unexpected level jump.
- [x] Adaptive Treble Emphasis played normally with no reported dropout, noise, click or unexpected level jump.
- [x] Processing Monitor Auto Low / Auto High updated normally during listening.
- [x] Bass Emphasis subjectively emphasized the low-frequency side without an abnormal high-frequency loss.
- [x] Treble Emphasis subjectively emphasized the high-frequency side without an abnormal low-frequency loss or excessive harshness.

## Compatibility basis

Source comparison against the v1.1.0 formal final source confirms that production-code changes are limited to:
- Version / package identity updates.
- Two new entries in `g_built_in_presets`.

No ATB algorithm, DSP coefficient, Auto Headroom, Reverb, Monitor, A/B or persistence logic is changed.

Expected unchanged:
- SRP5.
- `preset_version 10`.
- `.srpbackup`.
- Legacy readers.
- Processing Monitor behavior including Minimize with foobar2000.

## Formal v1.2.0 build / install

- [ ] `build_and_package.cmd` succeeds.
- [ ] `dist\foo_sonic_refiner_v1.2.0.fb2k-component` is generated.
- [ ] Component installs successfully.
- [ ] Preferences → Components shows `1.2.0`.
- [ ] Both new presets remain present with the approved values.
- [ ] Normal playback remains stable.
