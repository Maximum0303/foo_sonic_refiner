# Sonic Refiner v0.6.1 Testing

## Build / package

- [x] Built v0.6.1-dev.2 with `ビルドと梱包.cmd`.
- [x] Confirmed `dist\foo_sonic_refiner_v0.6.1-dev.2.fb2k-component`.
- [x] Confirmed settings title `Sonic Refiner - 0.6.1-dev.2`.

## ATB analysis-state UI

With `適応型標準 / Adaptive Standard` and ATB ON:

- [x] Start playback from stopped state -> `解析中...`.
- [x] Next track -> immediately `解析中...`.
- [x] Previous track -> immediately `解析中...`.
- [x] Directly jump to another track -> immediately `解析中...`.
- [x] Seek -> immediately `解析中...`.
- [x] Natural track advance -> immediately `解析中...`.
- [x] Stop -> playback -> `解析中...`.
- [x] ATB Off -> On -> `解析中...`.
- [x] After enough fresh analysis, numeric Auto Low / Auto High status returns.
- [x] Pause -> Resume preserves the current analysis state and does not restart analysis.

## UI

- [x] Japanese status display.
- [x] English `Auto: Analyzing...` status display.
- [x] Dark mode: no clipping, overlap, or broken borders.
- [x] Light mode: no clipping, overlap, or broken borders.

## Playback regression

- [x] Full-track playback completed.
- [x] No dropout.
- [x] No click / pop noise.
- [x] No abrupt unnatural low/high tonal change.
- [x] No crash.

## Compatibility

- DSP / ATB decision algorithm unchanged from v0.6.0.
- 12 built-in presets unchanged.
- SRP4 unchanged.
- `preset_version 9` unchanged.
- Legacy preset / backup compatibility unchanged.
