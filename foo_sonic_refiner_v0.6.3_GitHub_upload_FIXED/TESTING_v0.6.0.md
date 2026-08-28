# Sonic Refiner v0.6.0 Final Release Validation

The v0.6.0 formal source intentionally keeps the validated v0.6.0-dev.3 DSP,
ATB, preset, persistence, and compatibility behavior. Formalization changes
version markers and release documentation only.

## 1. Build and package

Run:

```text
ビルドと梱包.cmd
```

Expected output:

- `x64\Release\foo_sonic_refiner.dll`
- `dist\foo_sonic_refiner_v0.6.0.fb2k-component`
- `dist\SHA256SUMS.txt`

Confirm the build ends with:

```text
Build and packaging completed.
```

## 2. Install

Install `foo_sonic_refiner_v0.6.0.fb2k-component` and restart foobar2000.

Confirm the settings window reports:

```text
Sonic Refiner - 0.6.0
```

## 3. Adaptive Standard

Load `適応型標準 / Adaptive Standard` and confirm:

- Depth 100
- Clarity 100
- Width 50
- Ambience 40
- Master Strength 100%
- Output Gain 0.0 dB
- Auto Headroom Protection On
- Level-Matched Bypass On
- Sonic Refiner enabled
- Adaptive Tone Balance On

## 4. UI

Check Japanese and English in both Light and Dark mode:

- no clipped text
- no overlapping text
- no broken group frames
- `100% / 自動上限 +10.0 dB` is fully visible in Japanese
- settings window remains 560 × 320

## 5. Persistence

- Adaptive Standard -> OK -> reopen: settings remain
- restart foobar2000: ATB remains On and settings remain
- runtime analyzer history / current Auto Low / Auto High are freshly analyzed after restart
- clean Cancel restores the settings that were active when the window opened

## 6. Existing built-in preset regression

Load `標準 / Standard` and confirm:

- Depth 55
- Clarity 45
- Width 50
- Ambience 40
- Master Strength 100%
- Output Gain 0.0 dB
- protection options On
- Adaptive Tone Balance Off

## 7. User preset / backup

- save an ATB-On user preset derived from Adaptive Standard
- restore it and confirm ATB On
- export SRP4 `.srpbackup`
- import it and confirm the ATB-On preset restores correctly

Legacy SRP1 / SRP2 / SRP3 and older DSP-preset reading paths are unchanged
from v0.5.0 and must remain intact.

## 8. A/B

- store Adaptive Standard in A
- store Standard in B
- A restores ATB On
- B restores ATB Off
- switching causes no dropout, click, or crash
- End Comparison restores the complete pre-comparison settings

## 9. Playback smoke test

Play familiar music from start to finish with Adaptive Standard / ATB On and
confirm:

- no dropouts
- no clicks
- no sudden unnatural Low / High jumps
- no crash

## 10. Source package integrity

Confirm the source ZIP contains both:

```text
build_and_package.cmd
ビルドと梱包.cmd
```

and no garbled duplicate `.cmd` filename.

## 11. Recommended chain

Sonic Refiner
→ R128 Real-time Loudness Normalizer
→ Output

If all final-build checks pass, the build is suitable for the v0.6.0 public release.
