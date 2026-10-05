# Sonic Refiner v0.9.1

## English

### Monitor guide and layout consistency

- Adds **How to read the monitor...** to the Processing Monitor right-click menu.
- Right-click order matches R128: **Always on Top → separator → How to read the monitor...**.
- Explains Auto Low, Auto High, Auto Headroom, Level Match, meter ranges, display states, and the recommended Sonic Refiner → R128 → Output order.
- Adds `MONITOR_GUIDE.md` with the same Japanese/English guidance.
- Keeps the Processing Monitor outer width at **156 DLU** and every meter bar at **49 DLU**, aligned with the R128 monitor.
- Uses the compact visible row label **AutoHeadroom** so it stays on one line; the guide keeps the full term **Auto Headroom**.
- No DSP audio-processing changes.

### Validation carried from v0.9.1-dev.5

- Japanese visible row label **自動HR** and English **AutoHeadroom** were verified to stay on one line.
- Monitor outer width and meter-bar width were verified side-by-side against R128.
- Guide opening, full Auto Headroom terminology, right-click menu order, Always on Top persistence, monitor startup restoration, live meter updating, and audio-neutral monitor/guide open-close behavior were verified.

### Compatibility

- `sonic_refiner_monitor_initquit` remains non-final.
- v0.9.0 monitor telemetry and persistence are unchanged.
- DSP algorithms, Auto Headroom constants, ATB logic, 16 built-in preset values, SRP5, `preset_version 10`, `.srpbackup`, Reverb, A/B, display-language behavior, and legacy compatibility are unchanged.

---

## 日本語

### モニターガイドとレイアウト統一

- 補正モニターの右クリックメニューに **「モニターの見方...」** を追加。
- 右クリック順をR128と揃え、**「常に手前に表示」→ 区切り線 →「モニターの見方...」** とします。
- 低域補正、高域補正、自動ヘッドルーム、レベル一致、バー範囲、状態表示、Sonic Refiner → R128 → 出力の推奨順序を説明します。
- 同内容の日本語／Englishガイド `MONITOR_GUIDE.md` を追加します。
- 補正モニター全体の横幅を **156 DLU**、各メーターバーを **49 DLU** のままとし、R128モニターと揃えます。
- 1行表示を保つため、モニター上の行ラベルだけ **自動HR / AutoHeadroom** と短縮し、ガイドでは正式名称 **自動ヘッドルーム / Auto Headroom** を使用します。
- DSP音声処理の変更はありません。

### v0.9.1-dev.5で確認済みの内容

- 日本語 **自動HR**、English **AutoHeadroom** が1行表示されることを確認。
- R128と横に並べ、モニター全体の横幅とバー幅が揃うことを確認。
- ガイド表示、正式名称、右クリック順、常に手前設定の保存、起動時復元、ライブ更新、モニター／ガイド開閉で音が変化しないことを確認。

### 互換性

- `sonic_refiner_monitor_initquit` は非`final`のままです。
- v0.9.0のモニターテレメトリと保存動作は変更しません。
- DSPアルゴリズム、Auto Headroom定数、ATB、16内蔵プリセット値、SRP5、`preset_version 10`、`.srpbackup`、Reverb、A/B、表示言語、旧形式互換は変更しません。
