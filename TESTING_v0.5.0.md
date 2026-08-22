# Sonic Refiner v0.5.0 Final Release Validation

Formal v0.5.0 build and packaging were completed successfully on 2026-08-23.

## Build and package

Confirmed outputs:
- `x64\Release\foo_sonic_refiner.dll`
- `dist\foo_sonic_refiner_v0.5.0.fb2k-component`
- `dist\SHA256SUMS.txt`

Package SHA-256:

`11ec1dd73d84de61984c40e55b20815782d4a93c40084fcd681a3a0f9a065a74  foo_sonic_refiner_v0.5.0.fb2k-component`

Source ZIP SHA-256:

`3aaee8b33d590000a11bffa64d5f0ffb46c722f2eced47453779423434a75c9d  foo_sonic_refiner_v0.5.0_source.zip`

## Formal build validation

Confirmed on the formal v0.5.0 build:
- settings window reports `Sonic Refiner - 0.5.0`
- public UI contains no development diagnostic line
- Adaptive Tone Balance can be enabled normally
- current Auto Low / Auto High correction is displayed while ATB is enabled
- ATB On state persists after foobar2000 restart
- continuous familiar-track playback completed without dropouts, clicks, or unexpected tonal jumps

## Compatibility validation carried forward to the formal release

The v0.5.0 feature set was also validated for:
- Light and Dark mode
- clean Cancel restoration
- ATB On/Off user-preset persistence
- SRP4 `.srpbackup` export/import
- legacy SRP3 import with ATB Off
- A/B ATB switching and restoration of the settings active before comparison began
- fresh analysis state after restart and ATB Off→On

## Recommended DSP order

Sonic Refiner
→ R128 Real-time Loudness Normalizer
→ Output

The formal build passed the release validation and is suitable for public release.
