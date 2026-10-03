# Sonic Refiner v0.8.3 validation record

## Validated on v0.8.3-dev.2 before formalization

- Release / x64 build completed successfully with `ビルドと梱包.cmd`.
- Component version displayed `v0.8.3-dev.2`.
- Display-language choices were Automatic (Windows) / Japanese / English.
- Japanese label displayed `表示言語：`; English label displayed `Display language:` without reported clipping.
- Automatic (Windows) resolved to Japanese on Japanese Windows UI.
- Immediate Japanese / English switching passed.
- Automatic / English / Japanese selection each persisted after restarting foobar2000.
- Loading a built-in preset did not change the selected language mode.
- One-track normal playback passed with no reported sound dropout, abnormal level movement, noise, or ATB / Reverb regression.
- Validated v0.8.3-dev.2 component SHA-256:
  `b67ac81a8bd9b04b9cc5b6c9b44b80a18343216354a1afcbf0cc8ff331fcce9c`

## Formal v0.8.3 checks

1. Build Release / x64 with `ビルドと梱包.cmd`.
2. Confirm package name `foo_sonic_refiner_v0.8.3.fb2k-component`.
3. Install and confirm component/settings captions show `v0.8.3`.
4. Confirm Display language / 表示言語 offers Automatic (Windows) / Japanese / English.
5. Confirm Automatic (Windows) resolves normally and no UI regression is visible.
6. Confirm normal playback.
7. Restart foobar2000 and confirm settings retention.
8. Record formal component SHA-256 from `dist\SHA256SUMS.txt`.

No persistence format migration is required: SRP5, `preset_version 10`, `.srpbackup`, and legacy parsers remain unchanged.
