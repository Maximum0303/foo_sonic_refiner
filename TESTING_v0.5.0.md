# Sonic Refiner v0.5.0 Final Release Validation

The v0.5.0 formal source intentionally keeps the validated dev.25 DSP and
persistence behavior. Only formal versioning and release documentation change.

## 1. Build and package

Expected output:
- `x64\Release\foo_sonic_refiner.dll`
- `dist\foo_sonic_refiner_v0.5.0.fb2k-component`
- `dist\SHA256SUMS.txt`

## 2. Install

Install `foo_sonic_refiner_v0.5.0.fb2k-component` over the release candidate
and restart foobar2000.

Confirm the component and settings window report v0.5.0.

## 3. UI

Check both Light and Dark mode:
- no clipped text or controls
- no development diagnostic line
- ATB runtime line still displays current Auto Low / Auto High correction
- normal processing status remains visible

## 4. Persistence

- ATB On -> OK -> reopen: remains On
- restart foobar2000: remains On
- clean Cancel test restores the state from when the settings window opened

## 5. User presets / backup

- ATB-On user preset restores On
- ATB-Off user preset restores Off
- SRP4 `.srpbackup` export/import preserves both
- legacy SRP3 data loads ATB Off

## 6. A/B

- save A with ATB On
- save B with ATB Off
- A switches to On
- B switches to Off
- End Comparison restores the state that was active immediately before comparison began

## 7. Playback smoke test

Play familiar music continuously and confirm:
- no dropouts
- no clicks
- no unexpected tonal jumps
- Low / High behavior sounds the same as dev.25

## 8. Recommended chain

Sonic Refiner
→ R128 Real-time Loudness Normalizer
→ Output

If all checks pass, the build is suitable for the v0.5.0 public release.
