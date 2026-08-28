# Sonic Refiner v0.6.2 Testing

Formal v0.6.2 is based on v0.6.2-dev.2.

## Confirmed in v0.6.2-dev.2

### Build
- Release / x64 build completed successfully.
- `foo_sonic_refiner_v0.6.2-dev.2.fb2k-component` was generated.

### Built-in preset display persistence
- `適応型標準 / Adaptive Standard` remained displayed after restart.
- `大ホール / Large Hall` remained displayed after restart.
- Custom settings that did not match any built-in preset remained unselected
  after restart.
- Selecting `標準 / Standard` in the combo alone did not change DSP values.
- Pressing Load applied Standard correctly and the combo remained Standard.

### Language
- Japanese `標準` switched to English `Standard` without changing DSP values.
- Switching back to Japanese restored `標準`.

### User preset integration
- A user preset containing Adaptive Standard settings restored the DSP settings
  and the Built-in Presets combo automatically displayed `適応型標準`.

### A/B integration
- A = Adaptive Standard
- B = Standard
- Listen A -> Built-in Presets displayed Adaptive Standard.
- Listen B -> Built-in Presets displayed Standard.
- End Comparison -> restored the pre-comparison Standard settings and display.

### Cancel
- Temporary Depth change from Standard caused the combo to become unselected.
- Cancel restored Depth 55 and the Built-in Presets combo to Standard.

### UI
- Dark mode: no clipping, overlap, or broken borders.
- Light mode: no clipping, overlap, or broken borders.

### Audio smoke
With Adaptive Standard:
- no dropouts
- no click / pop noise
- no unnatural sudden low/high changes
- no crash

## Compatibility
- DSP / ATB algorithms unchanged.
- All 12 built-in preset values unchanged.
- SRP4 unchanged.
- preset_version 9 unchanged.
- Legacy compatibility unchanged.
