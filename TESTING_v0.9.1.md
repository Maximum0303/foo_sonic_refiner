# Sonic Refiner v0.9.1 Testing

## Build
- [ ] Release / x64 build succeeds
- [ ] `dist/foo_sonic_refiner_v0.9.1.fb2k-component` is created
- [ ] `SHA256SUMS.txt` is created
- [ ] Components page reports `0.9.1`

## Monitor geometry
- [x] Sonic Refiner monitor outer width matches R128
- [x] All four Sonic Refiner meter bars match the R128-style 49 DLU width
- [x] English row label shows `AutoHeadroom` on one line
- [x] Japanese row label shows `自動HR` on one line
- [x] No value text or meter bar overlaps the label

## Monitor guide
- [x] Guide uses full `Auto Headroom` / `自動ヘッドルーム` terminology
- [x] Right-click order is Always on Top / 常に手前に表示 → separator → guide
- [x] Guide opens and closes normally

## Persistence / runtime
- [x] Monitor live values update during playback
- [x] Always on Top works and persists
- [x] Open monitor state restores after foobar2000 restart
- [x] Opening / closing the monitor and guide does not audibly change processing

## Compatibility invariants
- [x] v0.9.0 DSP processing path is unchanged by the v0.9.1 source changes
- [x] Auto Headroom constants are unchanged
- [x] 16 built-in preset values are unchanged
- [x] SRP5 and `preset_version 10` are unchanged
- [x] `.srpbackup`, Reverb, A/B and legacy compatibility code paths are unchanged
