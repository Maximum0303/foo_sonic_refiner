# Sonic Refiner v0.1.1 リリースノート

Sonic Refiner v0.1.1は、正式名称と公開文書の表記を統一する修正版です。

## 変更内容

後段に配置するラウドネスノーマライザーの正式名称を、すべて次の表記へ統一しました。

```text
R128 Real-time Loudness Normalizer
```

修正対象：

- Sonic Refiner内のヘルプ
- 用語集
- 注意事項
- README
- Quick Start
- コンポーネント同梱文書
- リリースノート
- 推奨DSP順序の表記

## 推奨DSP順序

```text
Sonic Refiner
→ R128 Real-time Loudness Normalizer
→ Output
```

## 互換性

この更新では音声処理を変更していません。

- DSPの音質・音場処理：変更なし
- 内蔵プリセット：変更なし
- 任意プリセット：変更なし
- SRP1／SRP2形式：互換性維持
- 保存済み設定：そのまま継承

## 配布ファイル

- `foo_sonic_refiner_v0.1.1.fb2k-component`
- `SHA256SUMS.txt`
- `foo_sonic_refiner_v0.1.1_source.zip`

## License

MIT License  
Copyright (c) 2026 Maximum
