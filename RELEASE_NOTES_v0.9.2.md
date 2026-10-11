# Sonic Refiner v0.9.2

## English

### Pre-v1.0 polish

- Formalizes the validated v0.9.2-dev.2 build as the final pre-v1.0 polish release.
- Corrects stale user-facing fixed Depth / Clarity descriptions so both 100% maxima are documented as **+15.0 dB**.
- Standardizes the old English adaptive Depth term **Auto Bass** to **Auto Low**.
- Updates README / COMPONENT_README installation examples to `foo_sonic_refiner_v0.9.2.fb2k-component`.
- Preserves historical v0.8.2 change notes such as “+15.0 dB (was +16.0 dB / +14.0 dB)” because they correctly describe the version history.

### Pre-v1.0 regression validation

The validated v0.9.2-dev.2 build passed broad real-machine checks covering:

- normal playback without dropouts, noise, clicks or unexpected level changes;
- Processing Monitor live values, context menu, guide, Always on Top, startup restoration, position persistence, multi-instance prevention and playback-transition tracking;
- Automatic (Windows) / Japanese / English display-language switching;
- Preset Manager opening, preview, Apply, parent Cancel restoration, Search shortcuts, selection memory, window-size memory and split-ratio memory;
- A/B switching and End Comparison restoration;
- `.srpbackup` Backup / Restore;
- Reverb track-end tail, next-track isolation, Seek / Stop reset and Pause / Resume behavior;
- Adaptive Standard, Full Boost, Adaptive Hall / Arena / Dome progression and Adaptive Open Air;
- strong Reverb + Auto Headroom behavior;
- all 16 built-in presets;
- restart persistence and dark-mode UI;
- audio-neutral Monitor / guide open-close behavior.

### Compatibility

- No DSP audio-processing algorithm or coefficient changes from v0.9.1.
- Auto Headroom constants are unchanged.
- ATB analysis / decision / history / rate limiting / intro protection / boost-only behavior is unchanged.
- Width, Ambience, Reverb tuning, track-end tail, Master Strength, Output Gain, Level-Matched Bypass and A/B behavior are unchanged.
- Processing Monitor geometry, telemetry and persistence are unchanged.
- 16 built-in preset values are unchanged.
- SRP5, `preset_version 10`, `.srpbackup`, display-language behavior and legacy compatibility are unchanged.

---

## 日本語

### v1.0前の仕上げ

- 実機検証済みv0.9.2-dev.2を、v1.0前の仕上げ版v0.9.2として正式版化します。
- 固定モードのDepth / Clarity説明に残っていた古い表記を整理し、どちらも100%時の最大 **+15.0 dB** と明記します。
- Englishの適応型Depth説明に残っていた旧用語 **Auto Bass** を **Auto Low** へ統一します。
- README / COMPONENT_READMEのインストール例を `foo_sonic_refiner_v0.9.2.fb2k-component` へ更新します。
- v0.8.2の「+15.0 dB（旧+16.0 dB / +14.0 dB）」など、変更履歴として正しい記述は維持します。

### v1.0前の回帰確認

検証済みv0.9.2-dev.2では、実機で次を広範囲に確認しました。

- 通常再生で音切れ、ノイズ、クリック音、不自然な音量変動なし
- 補正モニターのライブ値、右クリック、ガイド、常に手前、起動時復元、位置保存、多重起動防止、再生遷移追従
- 自動（Windows）／日本語／Englishの表示言語切替
- Preset Managerの起動、プレビュー、Apply、親Cancel復元、Searchショートカット、選択記憶、ウィンドウサイズ記憶、分割比率記憶
- A/B切替と比較終了時の復元
- `.srpbackup` Backup / Restore
- Reverbの曲末tail、次曲への非持ち越し、Seek / Stop reset、Pause / Resume
- 適応型標準、フルブースト、ホール／アリーナ／ドームの段階差、適応型野外
- 強いReverb + Auto Headroom
- 16内蔵プリセット
- 再起動後の設定保持とDark表示
- Monitor / guide開閉による音質・音量・再生への影響なし

### 互換性

- v0.9.1からDSP音声処理アルゴリズム・係数は変更していません。
- Auto Headroom定数は変更していません。
- ATB解析／判定／履歴／rate limiting／intro protection／boost-onlyは変更していません。
- Width、Ambience、Reverb調整、曲末tail、Master Strength、Output Gain、Level-Matched Bypass、A/Bは変更していません。
- Processing Monitorのgeometry、telemetry、保存動作は変更していません。
- 16内蔵プリセット値は変更していません。
- SRP5、`preset_version 10`、`.srpbackup`、表示言語、旧形式互換は変更していません。
