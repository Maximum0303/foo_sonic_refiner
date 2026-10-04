# Sonic Refiner v0.8.4 Release Notes

## English

v0.8.4 formalizes the validated v0.8.4-dev.1 Auto Headroom redesign based directly on the official v0.8.3 source.

### Auto Headroom Protection

- Replaces immediate block-peak attenuation with smoothed sustained-peak protection.
- Uses a fast peak envelope followed by a slower sustained-peak envelope.
- Brief transients normally pass without pulling down the whole signal.
- Sustained high peaks around the existing approximately -0.2 dBFS reference are attenuated gradually.
- Protection gain now uses a smooth attack and release, reducing audible level steps and pumping.
- Auto Headroom remains lightweight protection, not a True Peak limiter; final True Peak management remains the downstream R128 Real-time Loudness Normalizer's responsibility.

### Validated in v0.8.4-dev.1

- Release / x64 build completed successfully.
- The previously affected quiet / ballad passage with Adaptive Standard and ATB no longer showed the audible small abrupt level drop attributed to Auto Headroom.
- The same passage remained normal with Level-Matched Bypass re-enabled.
- A louder / denser track passed without abrupt level drops, audible pumping, clipping-like distortion, or unstable gain movement.
- Full Boost with ATB Off, Level-Matched Bypass On, and Auto Headroom On also passed without clipping-like distortion or abrupt level drops.
- Validated dev component SHA-256: `a3e7c60a4bf601fa55a4fa0ee7c0ae8b8ad836dbb630b02c17f686e4c5c0119a`.

### Compatibility

- Auto Headroom behavior is intentionally changed.
- ATB analysis / decision / history / rate limiting / intro protection / boost-only behavior is unchanged.
- Level-Matched Bypass, Depth / Clarity gain ceilings, Width, Ambience, Reverb, Master Strength, Output Gain, built-in preset values, SRP5, `preset_version 10`, `.srpbackup`, display-language behavior, and legacy compatibility are unchanged from v0.8.3.

---

## 日本語

v0.8.4は、正式v0.8.3ソースを直接基準に、実機検証したv0.8.4-dev.1の自動ヘッドルーム保護改善を正式版化したものです。

### 自動ヘッドルーム保護

- 瞬間的なブロックピークへの即時減衰をやめ、平滑化した持続ピーク保護へ変更。
- 高速ピーク包絡と、それを受ける遅い持続ピーク包絡の2段階で検出。
- 短いトランジェントでは原則として全体ゲインを下げない。
- 従来の約-0.2 dBFS基準付近を持続的に超える高ピークだけを穏やかに減衰。
- 保護ゲインの低下／復帰を滑らかにし、「ガクッ」とした音量低下やポンピングを抑制。
- True Peakリミッターではなく、最終True Peak管理は後段のR128 Real-time Loudness Normalizerが担当。

### v0.8.4-dev.1で確認済み

- Release / x64ビルド成功。
- 適応型標準／ATBで症状が出ていた静かな曲・バラードの同一箇所で、自動ヘッドルーム保護による微妙な急低下が改善。
- レベルマッチ・バイパスをONへ戻した状態でも問題なし。
- 音圧が高めの曲で、急な音量低下、不自然なポンピング、クリップ感、ゲイン不安定なし。
- フルブースト、ATB OFF、レベルマッチ・バイパスON、自動ヘッドルーム保護ONでも音割れ・急な音量低下なし。
- 検証済みdev component SHA-256：`a3e7c60a4bf601fa55a4fa0ee7c0ae8b8ad836dbb630b02c17f686e4c5c0119a`。

### 互換性

- Auto Headroomの動作だけを意図的に変更。
- ATB解析／判定／履歴／rate limiting／intro protection／boost-only方針は変更なし。
- レベルマッチ・バイパス、Depth / Clarity上限、Width、Ambience、Reverb、Master Strength、Output Gain、内蔵プリセット値、SRP5、`preset_version 10`、`.srpbackup`、表示言語、旧形式互換はv0.8.3から変更なし。
