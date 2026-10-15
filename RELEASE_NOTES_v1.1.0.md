# Sonic Refiner v1.1.0 Release Notes

## English

### Processing Monitor minimize behavior

- Formalizes the validated v1.1.0-dev.1 feature as **Sonic Refiner v1.1.0**.
- Adds **Minimize with foobar2000** to the Processing Monitor right-click menu.
- The option defaults to **ON** to preserve the previous behavior.
- ON: minimizing the foobar2000 main window also hides the Processing Monitor; restoring foobar2000 restores the still-open Monitor.
- OFF: the Processing Monitor remains visible while the foobar2000 main window is minimized.
- With the option OFF, live Monitor values continue updating while playback continues.
- The setting is saved across restarts.
- The setting is independent from **Always on Top**.
- A Monitor that was manually closed is not reopened by minimize/restore behavior.
- Japanese / English / Automatic (Windows) language switching remains supported.
- The built-in Monitor guide and `MONITOR_GUIDE.md` document the new option.
- Formal package: `foo_sonic_refiner_v1.1.0.fb2k-component`.

### Compatibility

- This is a UI/window-behavior change only.
- DSP audio processing is unchanged.
- No changes to ATB, Auto Headroom, Level-Matched Bypass, Width, Ambience, Reverb/tail, Master Strength, Output Gain or A/B.
- All 16 built-in preset values are unchanged.
- SRP5, `preset_version 10`, `.srpbackup`, legacy readers and display-language behavior are unchanged.

---

## 日本語

### Processing Monitorの最小化動作

- 検証済みv1.1.0-dev.1の機能を **Sonic Refiner v1.1.0** として正式版化します。
- 補正モニターの右クリックメニューに **「foobar2000と一緒に最小化」** を追加します。
- 従来動作を維持するため、初期値は **オン** です。
- オン：foobar2000本体を最小化すると補正モニターも画面から消え、本体を復元すると開いたままのモニターも戻ります。
- オフ：foobar2000本体を最小化しても補正モニターは画面に残ります。
- オフ時も、再生中であればMonitorのリアルタイム値は更新を継続します。
- 設定は再起動後も保存します。
- **「常に手前に表示」** とは独立して動作します。
- 手動で閉じたモニターを最小化／復元によって勝手に開きません。
- 日本語／English／Automatic (Windows)の表示言語切替を維持します。
- 内蔵Monitorガイドと`MONITOR_GUIDE.md`も同じ仕様を説明します。
- 正式パッケージ：`foo_sonic_refiner_v1.1.0.fb2k-component`

### 互換性

- UI／ウィンドウ動作だけの変更です。
- DSP音声処理は変更しません。
- ATB、Auto Headroom、Level-Matched Bypass、Width、Ambience、Reverb／tail、Master Strength、Output Gain、A/Bは変更しません。
- 16内蔵プリセット値は変更しません。
- SRP5、`preset_version 10`、`.srpbackup`、旧形式reader、表示言語仕様を維持します。
