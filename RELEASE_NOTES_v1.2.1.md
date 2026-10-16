# Sonic Refiner v1.2.1 Release Notes

## English

### Processing Monitor position persistence fix

- Fixes a case where the Processing Monitor could reopen at an older position after closing foobar2000.
- The Monitor now saves its current window position immediately when a user finishes moving/resizing it.
- Existing position saves during Monitor destruction and foobar2000 shutdown remain in place as fallback paths.
- The change is limited to Monitor UI-state persistence.

### Compatibility

- DSP audio processing is unchanged.
- ATB, Auto Headroom, Level-Matched Bypass, Width, Ambience, Reverb/tail, Master Strength, Output Gain and A/B are unchanged.
- All 18 built-in preset values are unchanged.
- SRP5, `preset_version 10`, `.srpbackup`, display-language behavior and legacy compatibility are unchanged.

---

## 日本語

### Processing Monitor位置記憶の修正

- foobar2000本体を終了したあと、Processing Monitorが以前の位置へ戻る場合がある問題を修正します。
- Monitorを移動／サイズ変更し終えた時点で、現在のウィンドウ位置を即時保存するようにします。
- Monitor破棄時およびfoobar2000終了時の既存保存処理も、予備経路として維持します。
- 変更範囲はMonitorのUI状態保存だけです。

### 互換性

- DSP音声処理は変更しません。
- ATB、Auto Headroom、Level-Matched Bypass、Width、Ambience、Reverb／tail、Master Strength、Output Gain、A/Bは変更しません。
- 18個の内蔵プリセット値は変更しません。
- SRP5、`preset_version 10`、`.srpbackup`、表示言語仕様、旧形式互換を維持します。
