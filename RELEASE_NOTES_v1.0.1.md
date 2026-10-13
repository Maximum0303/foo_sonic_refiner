# Sonic Refiner v1.0.1

## English

### Processing Monitor pause-display alignment

- Formalizes the validated v1.0.1-dev.1 fix as **Sonic Refiner v1.0.1**.
- While playback is paused, all four Processing Monitor values show an em dash (`—`).
- Auto Low, Auto High, Auto Headroom and Level Match meter bars are all empty while paused.
- Playback resume returns the Monitor to live runtime values on the next refresh.
- This aligns the paused-state presentation with the R128 Real-time Loudness Normalizer monitor.
- The built-in Monitor guide and `MONITOR_GUIDE.md` document the same behavior.
- Formal package: `foo_sonic_refiner_v1.0.1.fb2k-component`.

### Compatibility

- This is a Monitor display-only change.
- DSP audio processing is unchanged.
- Pause does not reset ATB history, Auto Headroom internal state, Reverb state, or other DSP runtime state.
- No changes to ATB logic, Auto Headroom constants, Width, Ambience, Reverb/tail, Master Strength, Output Gain, Level-Matched Bypass or A/B.
- All 16 built-in preset values are unchanged.
- SRP5, `preset_version 10`, `.srpbackup`, legacy readers and display-language behavior are unchanged.

---

## 日本語

### Processing Monitorの一時停止表示を統一

- 検証済みv1.0.1-dev.1の修正を **Sonic Refiner v1.0.1** として正式版化します。
- 再生を一時停止すると、Processing Monitorの4項目をすべて「—」表示にします。
- 低域補正、高域補正、自動HR、レベル一致の4本のメーターバーもすべて空表示にします。
- 再生を再開すると、次回更新から現在のランタイム値表示へ戻ります。
- R128 Real-time Loudness Normalizerの補正モニターと一時停止中の見え方を揃えます。
- 内蔵Monitorガイドと`MONITOR_GUIDE.md`も同じ仕様を説明します。
- 正式パッケージ：`foo_sonic_refiner_v1.0.1.fb2k-component`

### 互換性

- Monitor表示だけの変更です。
- DSP音声処理は変更しません。
- 一時停止によってATB履歴、Auto Headroom内部状態、Reverb状態などのDSPランタイム状態をリセットしません。
- ATB、Auto Headroom定数、Width、Ambience、Reverb／tail、Master Strength、Output Gain、Level-Matched Bypass、A/Bは変更しません。
- 16内蔵プリセット値は変更しません。
- SRP5、`preset_version 10`、`.srpbackup`、旧形式reader、表示言語仕様を維持します。
