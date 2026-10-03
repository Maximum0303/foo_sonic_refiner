# Sonic Refiner v0.8.2 validation record

## Validated on v0.8.2-dev.1 before formalization

- Release / x64 build completed successfully with `ビルドと梱包.cmd`.
- Component version displayed `v0.8.2-dev.1`.
- Adaptive Standard reached the new **+15.0 dB** ATB ceiling in actual playback.
- Adaptive Standard one-track listening test: no audible clipping, bass breakup, treble harshness, abnormal level movement, or excessive Auto Headroom reduction reported.
- Fixed-mode Full Boost listening test: no audible clipping, low-frequency breakup, treble harshness, or abnormal Auto Headroom reduction reported.
- After restarting foobar2000, version/settings/display behavior remained normal.
- Validated v0.8.2-dev.1 component SHA-256:
  `009723c8f9e70b3c9d582aded1e9804e9d4dc1455ca2191e68764af91a11d141`

## Formal v0.8.2 checks

1. Build Release / x64 with `ビルドと梱包.cmd`.
2. Confirm package name `foo_sonic_refiner_v0.8.2.fb2k-component`.
3. Install and confirm component/settings captions show `v0.8.2`.
4. Confirm normal playback with Adaptive Standard and Full Boost.
5. Confirm restart retains settings and normal display.
6. Record formal component SHA-256 from `dist\SHA256SUMS.txt`.

No persistence format migration is required: SRP5, `preset_version 10`, `.srpbackup`, and legacy parsers remain unchanged.
