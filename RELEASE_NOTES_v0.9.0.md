# Sonic Refiner v0.9.0

## English

### Highlights

- Adds the independent compact **Sonic Refiner Processing Monitor**.
- Open it from the Playback menu while the normal settings dialog is closed.
- Displays live **Auto Low**, **Auto High**, **Auto Headroom attenuation**, and **Level Match attenuation** values.
- Refreshes at approximately 100 ms intervals without adding UI work to the DSP audio-processing path.
- Shows Active / Analyzing / Waiting / Paused / Disabled states.
- Remembers open/closed state, window position, and optional **Always on Top** state.
- Reopens automatically on the next foobar2000 launch if it was open at shutdown.
- Follows Sonic Refiner's resolved Automatic (Windows) / Japanese / English display language.

### Build fix carried into the formal release

- Includes the v0.9.0-dev.2 fix for MSVC C3246 with foobar2000 SDK `initquit_factory_t`.
- `sonic_refiner_monitor_initquit` is intentionally not declared `final`, allowing the SDK service wrapper to derive from it.

### Validation / Compatibility

- Validated development component SHA-256: `dbb831f98cbf7b26ab6c7f2a97f49e6edddd9e6d9dda72cd235dfa4775105db3`.
- Processing Monitor startup, real-time values, persistence, language switching, multi-instance prevention, playback transitions, and audio-neutral open/close behavior were verified on v0.9.0-dev.2.
- Existing user presets, A/B comparison, SRP5 `.srpbackup` Backup / Restore, Reverb tail handling, venue-preset progression, Open Air, Adaptive Standard Reverb 0, and Auto Headroom + strong Reverb regression checks passed.
- v0.8.4 DSP processing and Auto Headroom constants are unchanged.
- 16 built-in preset values, SRP5, `preset_version 10`, `.srpbackup`, display-language behavior, and legacy preset/backup compatibility are unchanged.

---

## 日本語

### 主な追加・変更

- 独立した小型の **Sonic Refiner 補正モニター** を正式搭載。
- 通常の設定画面を閉じたまま、Playbackメニューから表示可能。
- **Auto Low／Auto High／Auto Headroom減衰／Level Match減衰** をリアルタイム表示。
- 約100 ms間隔で表示更新し、DSP音声処理経路へUI処理を持ち込みません。
- 動作中／解析中／待機中／一時停止中／無効の状態を表示。
- 開閉状態、ウィンドウ位置、**常に手前に表示** の設定を記憶。
- 終了時に開いていた場合は、次回foobar2000起動時に自動再表示。
- Sonic Refinerの自動（Windows）／日本語／Englishの解決後表示言語へ追従。

### 正式版へ含めたビルド修正

- v0.9.0-dev.2で修正した、foobar2000 SDK `initquit_factory_t` によるMSVC C3246を反映。
- SDK側のサービスラッパーが継承できるよう、`sonic_refiner_monitor_initquit` は `final` を付けない実装としています。

### 検証・互換性

- 検証済みdev.2 component SHA-256：`dbb831f98cbf7b26ab6c7f2a97f49e6edddd9e6d9dda72cd235dfa4775105db3`。
- dev.2で、補正モニター起動、リアルタイム値、状態保存、表示言語追従、多重起動防止、曲送り／戻し／Stop→Play／Seek／Pause→Resume、再生中の開閉による音声影響なしを確認済み。
- 既存任意プリセット、A/B比較、SRP5 `.srpbackup` Backup / Restore、Reverb tail、会場系プリセット、Open Air、適応型標準Reverb 0、強いReverb＋Auto Headroomも回帰確認済み。
- v0.8.4のDSP処理およびAuto Headroom定数は変更していません。
- 16内蔵プリセット値、SRP5、`preset_version 10`、`.srpbackup`、表示言語仕様、旧形式互換は変更していません。
