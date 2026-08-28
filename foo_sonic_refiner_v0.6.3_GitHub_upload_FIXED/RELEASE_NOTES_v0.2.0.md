# Sonic Refiner v0.2.0 リリースノート

Sonic Refiner v0.2.0では、4つの音質・音場補正をまとめて調整できる
Master Strength（全体効果量）を正式搭載しました。

## 新機能

### Master Strength

```text
範囲：0～100%
初期値：100%
```

Depth、Clarity、Width、Ambienceのバランスを保ったまま、
実際の効果量を一括で弱められます。

- 100%：各スライダーの設定どおり
- 50%：各補正効果を約半分へ
- 0%：4項目を無補正

Output Gain、自動ヘッドルーム保護、レベルマッチ・バイパスは
Master Strengthの対象外です。

WidthはSide 100%を基準に補間します。

```text
Master 0%   → Side 100%
Master 50%  → Side 100%と設定値の中間
Master 100% → Widthスライダーの設定値
```

## プリセットと互換性

- 内蔵プリセットはMaster Strength 100%で従来の音を維持
- 任意プリセットへMaster Strengthを保存
- `.srpbackup`へMaster Strengthを保存
- 新しい任意プリセット形式はSRP3
- SRP1／SRP2形式も引き続き読み込み可能
- v0.1.xの設定はMaster Strength 100%として読み込み
- 保存済み設定と従来プリセットの互換性を維持

## 推奨DSP順序

```text
Sonic Refiner
→ R128 Real-time Loudness Normalizer
→ Output
```

## 確認済み項目

- 0%・50%・100%の基本動作
- 任意プリセット保存・呼び戻し
- バックアップ書き出し・読み込み
- v0.1.1バックアップとの互換性
- 再起動後の保持
- キャンセル時の復元
- ライト／ダークモード
- 再生中の連続操作
- 異音、音切れ、停止、クラッシュなし

## 配布ファイル

- `foo_sonic_refiner_v0.2.0.fb2k-component`
- `SHA256SUMS.txt`
- `foo_sonic_refiner_v0.2.0_source.zip`

## License

MIT License  
Copyright (c) 2026 Maximum
