# Sonic Refiner v1.2.1 Testing

Target host: foobar2000 v2.26.1  
Build: Release / x64  
SDK: SDK-2025-03-07

## Validated in v1.2.1-dev.1

- [x] `build_and_package.cmd` succeeds.
- [x] `dist\foo_sonic_refiner_v1.2.1-dev.1.fb2k-component` is generated.
- [x] Component installs successfully.
- [x] Preferences → Components shows `1.2.1-dev.1`.
- [x] Move the Processing Monitor, leave it open, close foobar2000, restart foobar2000, and confirm it reopens at the last position.
- [x] Move the Monitor, manually close only the Monitor, reopen it from Playback, and confirm the position is retained.
- [x] `Minimize with foobar2000 = ON`: Monitor hides with foobar2000 and returns at the same position on restore.
- [x] `Minimize with foobar2000 = OFF`: Monitor remains visible, live values continue updating during playback, and its position is unchanged when foobar2000 is restored.
- [x] Normal playback has no dropout, noise, click or unexpected level change.
- [x] Processing Monitor continues updating normally during playback.

## Formal v1.2.1 build / install

- [ ] `build_and_package.cmd` succeeds.
- [ ] `dist\foo_sonic_refiner_v1.2.1.fb2k-component` is generated.
- [ ] Component installs successfully.
- [ ] Preferences → Components shows `1.2.1`.
- [ ] Processing Monitor position persists across foobar2000 shutdown/restart.
- [ ] Normal playback remains stable.

## Compatibility

Expected unchanged:
- DSP algorithms and coefficients.
- ATB behavior.
- Auto Headroom behavior.
- Level-Matched Bypass.
- Width / Ambience / Reverb / tail.
- Master Strength / Output Gain.
- A/B.
- All 18 built-in preset values.
- SRP5.
- `preset_version 10`.
- `.srpbackup`.
- Display-language behavior.
- Legacy readers.
- Existing Monitor Pause behavior and `Minimize with foobar2000` semantics.
