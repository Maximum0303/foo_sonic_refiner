# Sonic Refiner v1.0.0

## English

### First stable milestone

- Formalizes the validated v1.0.0-dev.1 stabilization build as **Sonic Refiner v1.0.0**.
- Establishes the validated v0.9.2 / v1.0.0-dev.1 DSP, UI, compatibility, preset-management and Processing Monitor behavior as the v1.0 stable baseline.
- No new DSP algorithm is introduced in v1.0.0.
- Built-in Help / Glossary / Important Notes are confirmed as the v1.0 baseline terminology.
- Formal package: `foo_sonic_refiner_v1.0.0.fb2k-component`.

### Validation

The v1.0.0-dev.1 build passed broad real-machine regression checks covering:

- normal playback without dropouts, noise, clicks, unexpected level changes or obvious sound-quality faults;
- Processing Monitor live values, context-menu order, guide, Always on Top, startup restoration, position persistence and multi-instance prevention;
- Next / Previous, Stop → Play, Seek and Pause / Resume monitor tracking;
- Automatic (Windows) / Japanese / English display-language switching;
- Preset Manager list/preview, Apply, current-setting marker, Search shortcuts, window-size/split-ratio/selection persistence and parent-Cancel restoration;
- A/B switching and End Comparison restoration;
- `.srpbackup` Backup / Restore;
- Reverb track-end tail, next-track isolation, Seek/Stop reset and Pause/Resume behavior;
- Adaptive Standard, Full Boost, Adaptive Hall / Arena / Dome progression and Adaptive Open Air;
- strong Reverb + Auto Headroom behavior;
- all 16 built-in presets;
- restart persistence, dark-mode UI and audio-neutral Monitor / guide open-close behavior.

### Compatibility

- No DSP audio-processing algorithm or coefficient changes from v0.9.2 / v1.0.0-dev.1.
- Fixed Depth 100% maximum remains **+15.0 dB**.
- Fixed Clarity 100% maximum remains **+15.0 dB**.
- ATB Auto Low / Auto High absolute maxima remain **+15.0 dB**.
- ATB analysis / decision / history / rate limiting / intro protection / boost-only behavior is unchanged.
- Auto Headroom algorithm/constants are unchanged.
- Width, Ambience, Reverb tuning/tail, Master Strength, Output Gain, Level-Matched Bypass and A/B are unchanged.
- Processing Monitor geometry, telemetry, persistence and guide behavior are unchanged.
- All 16 built-in preset values are unchanged.
- SRP5, `preset_version 10`, `.srpbackup`, SRP1-SRP4 reading, DSP preset versions 1-9 reading, display-language behavior and legacy compatibility are unchanged.

---

## 日本語

### 最初の正式安定版

- 検証済みv1.0.0-dev.1安定化ビルドを **Sonic Refiner v1.0.0** として正式版化します。
- v0.9.2／v1.0.0-dev.1で検証済みのDSP、UI、互換性、Preset Manager、Processing Monitorの動作をv1.0の安定仕様として確定します。
- v1.0.0では新しいDSPアルゴリズムを追加しません。
- 内蔵Help／Glossary／Important Notesをv1.0の正式基準用語として確定します。
- 正式パッケージ：`foo_sonic_refiner_v1.0.0.fb2k-component`

### 実機確認

v1.0.0-dev.1では、次を広範囲に実機回帰確認しました。

- 通常再生で音切れ、ノイズ、クリック、不自然な音量変動、明らかな音質異常なし
- Processing Monitorのライブ値、右クリック順、ガイド、常に手前、起動時復元、位置保存、多重起動防止
- Next / Previous、Stop→Play、Seek、Pause / ResumeでMonitor追従
- 自動（Windows）／日本語／English表示言語切替
- Preset Managerの一覧／preview、Apply、現在設定一致マーカー、Searchショートカット、window size／split ratio／選択記憶、親Cancel復元
- A/B切替と比較終了時の復元
- `.srpbackup` Backup / Restore
- Reverb曲末tail、次曲への非持ち越し、Seek／Stop reset、Pause／Resume
- 適応型標準、フルブースト、ホール／アリーナ／ドームの段階差、適応型野外
- 強いReverb + Auto Headroom
- 16内蔵プリセット
- 再起動後の設定保持、Dark UI、Monitor／guide開閉による音声影響なし

### 互換性

- v0.9.2／v1.0.0-dev.1からDSP音声処理アルゴリズム・係数は変更しません。
- 固定Depth 100%最大は **+15.0 dB** のままです。
- 固定Clarity 100%最大は **+15.0 dB** のままです。
- ATB Auto Low / Auto High絶対最大は **+15.0 dB** のままです。
- ATB解析／判定／履歴／rate limiting／intro protection／boost-onlyは変更しません。
- Auto Headroomアルゴリズム／定数は変更しません。
- Width、Ambience、Reverb調整／tail、Master Strength、Output Gain、Level-Matched Bypass、A/Bは変更しません。
- Processing Monitorのgeometry、telemetry、保存、guide動作は変更しません。
- 16内蔵プリセット値は変更しません。
- SRP5、`preset_version 10`、`.srpbackup`、SRP1～4読込、DSP preset version 1～9読込、表示言語、旧形式互換を維持します。
