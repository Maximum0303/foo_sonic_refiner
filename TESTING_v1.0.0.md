# Sonic Refiner v1.0.0 Testing

## Basis

Formal v1.0.0 is produced from the user-validated v1.0.0-dev.1 source.
The formalization changes version/package/document identity only; DSP processing is unchanged.

## v1.0.0-dev.1 real-machine regression results

- [x] Release / x64 build succeeded.
- [x] Package `foo_sonic_refiner_v1.0.0-dev.1.fb2k-component` generated and installed.
- [x] Preferences → Components showed `1.0.0-dev.1`.
- [x] Normal playback: no dropout, noise, click, unexpected level change or obvious sound-quality fault.
- [x] Processing Monitor opened and four values updated live.
- [x] Monitor right-click order: Always on Top → separator → guide.
- [x] Monitor guide content opened normally.
- [x] Always on Top worked.
- [x] Monitor open state and Always on Top restored after restart.
- [x] English display-language switch propagated to settings / Playback menu / Monitor.
- [x] Automatic (Windows) returned to Japanese on Japanese Windows UI.
- [x] Preset Manager opened with list and preview.
- [x] Apply changed current DSP settings and current-setting marker appeared.
- [x] A/B switching produced no click/dropout/abnormal Reverb.
- [x] End Comparison restored the pre-comparison DSP settings.
- [x] `.srpbackup` Backup succeeded without changing DSP/preset content.
- [x] Restore recovered preset content/order without changing current DSP settings.
- [x] Reverb track-end tail decayed naturally.
- [x] Previous-track Reverb did not leak into the next track.
- [x] Seek cleared old Reverb state.
- [x] Stop then Play did not reproduce old Reverb.
- [x] Pause / Resume produced no abnormal Reverb burst.
- [x] Adaptive Dome + Auto Headroom: no abrupt level drop, pumping or clipping impression.
- [x] Adaptive Standard: ATB normal, Reverb 0, no clipping/unexpected level behavior.
- [x] Full Boost fixed mode: no low/high failure or abnormal Auto Headroom level movement.
- [x] Monitor followed Next / Previous.
- [x] Monitor followed Stop → Play.
- [x] Monitor continued updating after Seek.
- [x] Monitor state/update recovered after Pause / Resume.
- [x] Opening/closing Monitor and guide was audio-neutral.
- [x] Adaptive Hall < Arena < Dome spatial/Reverb progression confirmed.
- [x] Adaptive Open Air short-Reverb character confirmed.
- [x] All 16 built-in presets present.
- [x] Restart preserved DSP/preset state and Automatic display-language mode.
- [x] Preset Manager Ctrl+Backspace fully cleared Search without residual 0x7F.
- [x] Preset Manager Ctrl+F focused Search.
- [x] Preset Manager window size persisted.
- [x] Preset Manager split ratio persisted.
- [x] Preset Manager selection memory worked within the same parent settings dialog.
- [x] Apply then parent Cancel restored the parent-open DSP settings.
- [x] Monitor position persisted after restart.
- [x] Monitor duplicate prevention worked.
- [x] Dark mode: settings / Preset Manager / Monitor remained readable with no clipping or bad colors.

## Formal v1.0.0 post-build minimum check

After building the formal source, confirm at minimum:

- [ ] Release / x64 build succeeds.
- [ ] `foo_sonic_refiner_v1.0.0.fb2k-component` is generated.
- [ ] Preferences → Components shows `1.0.0`.
- [ ] One normal-playback check passes.
- [ ] `dist\SHA256SUMS.txt` is recorded before publication.

## Compatibility requirement

SRP5, `preset_version 10`, `.srpbackup`, legacy readers, all 16 built-in preset values, Monitor behavior, ATB, Auto Headroom and all v0.9.2/v1.0.0-dev.1 DSP behavior remain unchanged.
