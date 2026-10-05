# Sonic Refiner v0.9.0 Testing

## Build
- [ ] Release / x64 build succeeds
- [ ] `dist/foo_sonic_refiner_v0.9.0.fb2k-component` is created
- [ ] `SHA256SUMS.txt` is created
- [ ] Components page reports `0.9.0`

## Processing Monitor
- [ ] Playback menu opens only one Processing Monitor window
- [ ] Auto Low / Auto High update during ATB playback
- [ ] Auto Headroom moves when sustained high peaks require protection
- [ ] Level Match updates when Level-Matched Bypass is active
- [ ] Opening / closing the monitor does not affect audio
- [ ] Window position persists
- [ ] Open / closed state persists across foobar2000 restart
- [ ] Always on Top On / Off persists
- [ ] Japanese / English / Automatic (Windows) display behavior remains correct
- [ ] Next / Previous / Stop→Play / Seek / Pause→Resume continue updating normally

## v0.8.4 regression
- [ ] 16 built-in presets remain available
- [ ] Existing user presets remain available and apply correctly
- [ ] A/B comparison remains normal
- [ ] Reverb track-end tail remains normal
- [ ] Tail does not leak into the next track
- [ ] Seek / Stop clear old tail correctly
- [ ] Pause / Resume has no abnormal tail
- [ ] Hall < Arena < Dome spatial/reverb progression remains clear
- [ ] Open Air remains short-tailed
- [ ] Adaptive Standard remains Reverb 0
- [ ] Strong Reverb + Auto Headroom has no abrupt level drop, pumping or clipping-like distortion
- [ ] Current SRP5 `.srpbackup` Backup / Restore works

## Compatibility invariants
- [ ] v0.8.4 DSP processing unchanged
- [ ] Auto Headroom constants unchanged
- [ ] SRP5 unchanged
- [ ] `preset_version 10` unchanged
- [ ] 16 built-in preset values unchanged
- [ ] Legacy compatibility unchanged
