# Sonic Refiner v0.9.2 Testing

## Formal build

- [ ] Release / x64 build succeeds.
- [ ] `dist\foo_sonic_refiner_v0.9.2.fb2k-component` is generated.
- [ ] `dist\SHA256SUMS.txt` is generated.
- [ ] Preferences → Components shows `0.9.2`.

## v0.9.2-dev.2 validated pre-v1.0 regression

- [x] README installation examples are updated and stale v0.8.0 package examples are removed.
- [x] COMPONENT_README installation examples are updated and stale v0.8.0 package examples are removed.
- [x] Fixed Depth / Clarity user-facing descriptions show +15.0 dB.
- [x] English adaptive Depth description uses `Auto Low`, not `Auto Bass`.
- [x] Glossary fixed Depth / Clarity descriptions show +15.0 dB.
- [x] Normal playback has no dropouts, noise, clicks or unexpected level changes.
- [x] Processing Monitor opens, shows four values and updates live.
- [x] Monitor context-menu order and monitor guide are correct.
- [x] Always on Top works and persists.
- [x] Monitor open state restores after restart.
- [x] Monitor position persists after restart.
- [x] Monitor does not open multiple instances.
- [x] English display-language switching updates settings, Playback menu and Monitor.
- [x] Automatic (Windows) returns to Japanese on the tested Japanese Windows UI.
- [x] Preset Manager opens with list and preview.
- [x] Preset Manager Apply updates DSP settings and matching indication.
- [x] Parent Cancel restores the DSP state from when the parent settings window opened.
- [x] A/B switching works without audible clicks/dropouts.
- [x] End Comparison restores the pre-comparison DSP state.
- [x] `.srpbackup` Backup succeeds.
- [x] `.srpbackup` Restore restores list/order without changing DSP settings.
- [x] Reverb track-end tail decays naturally.
- [x] Previous-track Reverb does not leak into the next track.
- [x] Seek clears old Reverb state.
- [x] Stop clears old Reverb state.
- [x] Pause / Resume has no abnormal Reverb burst/cut.
- [x] Adaptive Dome + Auto Headroom has no abrupt level dip, pumping or clipping impression.
- [x] Adaptive Standard keeps ATB operation, Reverb 0 and stable playback.
- [x] Full Boost fixed mode plays without obvious tonal break-up or unstable Auto Headroom behavior.
- [x] Monitor continues updating across Next / Previous.
- [x] Monitor handles Stop → Play and resumes updates.
- [x] Monitor continues updating after Seek.
- [x] Monitor handles Pause → Resume and resumes updates.
- [x] Opening / closing Monitor and guide is audio-neutral.
- [x] Adaptive Hall < Arena < Dome progression is perceptible and natural.
- [x] Adaptive Open Air remains shorter/drier than indoor venue presets.
- [x] All 16 built-in presets are present.
- [x] DSP settings / selected preset and Automatic display language persist over restart.
- [x] Preset Manager Ctrl+Backspace clears Search without leaving DEL `0x7F`.
- [x] Preset Manager Ctrl+F focuses Search.
- [x] Preset Manager window size persists.
- [x] Preset Manager split ratio persists.
- [x] Preset Manager selection memory works while the same parent settings window remains open.
- [x] Dark-mode UI remains readable for settings, Preset Manager and Monitor.

## Compatibility invariants

- [x] v0.9.2 source changes do not intentionally change DSP algorithms or coefficients from v0.9.1.
- [x] Auto Headroom constants are unchanged.
- [x] ATB logic is unchanged.
- [x] Reverb tuning and track-end-tail implementation are unchanged.
- [x] 16 built-in preset values are unchanged.
- [x] Processing Monitor geometry / telemetry / persistence are unchanged.
- [x] SRP5 and `preset_version 10` are unchanged.
- [x] `.srpbackup` outer format and legacy compatibility code paths are unchanged.
