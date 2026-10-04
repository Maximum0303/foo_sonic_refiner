# Sonic Refiner v0.8.4 validation record

## Validated on v0.8.4-dev.1 before formalization

- Release / x64 build completed successfully with `ビルドと梱包.cmd`.
- Component version displayed `v0.8.4-dev.1`.
- The previously affected quiet / ballad passage was tested with Adaptive Standard, ATB On, Level-Matched Bypass Off, and Auto Headroom On; the abrupt small level dip was no longer apparent.
- Level-Matched Bypass was then turned back On; the same passage remained normal.
- A louder / denser track was played with Adaptive Standard, ATB On, Level-Matched Bypass On, and Auto Headroom On; no abrupt level drop, audible pumping, clipping-like distortion, or unstable gain movement was reported.
- Full Boost was tested with ATB Off, Level-Matched Bypass On, and Auto Headroom On; no clipping-like distortion or abrupt level drop was reported.
- Validated v0.8.4-dev.1 component SHA-256:
  `a3e7c60a4bf601fa55a4fa0ee7c0ae8b8ad836dbb630b02c17f686e4c5c0119a`

## Formal v0.8.4 checks

1. Build Release / x64 with `ビルドと梱包.cmd`.
2. Confirm package name `foo_sonic_refiner_v0.8.4.fb2k-component`.
3. Install and confirm component/settings captions show `v0.8.4`.
4. Repeat the previously affected quiet / ballad passage with Adaptive Standard / ATB and Auto Headroom On.
5. Confirm Level-Matched Bypass On does not reintroduce the abrupt level dip.
6. Play a louder / denser track and confirm there is no abrupt level drop, audible pumping, clipping-like distortion, noise, or dropout.
7. Run a Full Boost stress check with Auto Headroom On.
8. Restart foobar2000 and confirm settings retention.
9. Record formal component SHA-256 from `dist\SHA256SUMS.txt`.

No persistence format migration is required: SRP5, `preset_version 10`, `.srpbackup`, and legacy parsers remain unchanged.
