# Sonic Refiner v1.1.0 Testing

Target host: foobar2000 v2.26.1  
Build: Release / x64  
SDK: SDK-2025-03-07

## Validated development build: v1.1.0-dev.1

- [x] Release / x64 build succeeded.
- [x] Component installed successfully.
- [x] Preferences → Components showed `1.1.0-dev.1`.
- [x] Right-click menu showed Always on Top → Minimize with foobar2000 → separator → guide.
- [x] New option was ON by default.
- [x] ON: minimizing foobar2000 hid the Monitor.
- [x] ON: restoring foobar2000 restored the previously open Monitor.
- [x] OFF: minimizing foobar2000 left the Monitor visible.
- [x] OFF: live Monitor values continued updating during playback.
- [x] OFF setting survived restart.
- [x] A manually closed Monitor was not reopened by minimize/restore.
- [x] Always on Top remained independent.
- [x] English label was `Minimize with foobar2000`.
- [x] Automatic (Windows) returned the menu to Japanese and preserved the option state.
- [x] Normal playback had no dropout, noise, click or unexpected level change.
- [x] Pause / Resume and Monitor updates remained normal.

## Formal v1.1.0 build / install

- [ ] `build_and_package.cmd` succeeds.
- [ ] `dist\foo_sonic_refiner_v1.1.0.fb2k-component` is generated.
- [ ] Component installs successfully.
- [ ] Preferences → Components shows `1.1.0`.

## Formal v1.1.0 focused regression

- [ ] Right-click menu order remains correct.
- [ ] ON: Monitor follows foobar2000 minimize/restore.
- [ ] OFF: Monitor remains visible while foobar2000 is minimized.
- [ ] OFF: Monitor continues live updates during playback.
- [ ] Saved ON/OFF state survives restart.
- [ ] Manually closed Monitor remains closed through minimize/restore.
- [ ] Always on Top remains independent.
- [ ] Japanese / English / Automatic (Windows) labels remain correct.
- [ ] Pause still shows four `—` values and empty meter bars.
- [ ] Resume returns to live runtime values.
- [ ] Normal playback has no dropout, noise, click or unexpected level change.
- [ ] 16 built-in presets remain present.
- [ ] No unexpected Reverb/tail behavior.

## Compatibility

Expected unchanged:
- DSP algorithms and coefficients.
- SRP5.
- `preset_version 10`.
- `.srpbackup`.
- Legacy readers.
- 16 built-in preset values.
