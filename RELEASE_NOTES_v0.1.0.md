# Sonic Refiner v0.1.0 リリースノート

Sonic Refinerの最初の正式公開版です。

## 概要

Sonic Refinerは、foobar2000上で音色と音場をリアルタイムに調整する適応型音質補正DSPです。低域の厚み、明瞭感、ステレオの広がり、短い初期反射による空間・奥行き感を調整できます。

## 主な機能

- Depth：最大約+16 dB
- Clarity：最大約+14 dB
- Width：Side最大600%
- Ambience：Wet Mix最大85%
- Output Gain：-12.0～+6.0 dB
- 自動ヘッドルーム保護
- レベルマッチ・バイパス
- 内蔵プリセット11種類
- 任意プリセット最大20件
- `.srpbackup`によるバックアップと復元
- ヘルプ、用語集、注意事項、MIT License表示
- ライト／ダークモード対応

## 推奨DSP順序

```text
Sonic Refiner
→ R128 Real-time Loudness Normalizer
→ Output
```

## 注意

80～100%は強い演出・動作確認用です。極端な設定では定位、残響、機器負荷が大きく変化するため、再生音量を下げて試してください。

自動ヘッドルーム保護はTrue Peakリミッターではありません。通常使用では後段のR128 Real-time Loudness Normalizerなどを併用してください。

## 配布予定ファイル

- `foo_sonic_refiner_v0.1.0.fb2k-component`
- `SHA256SUMS.txt`
- `foo_sonic_refiner_v0.1.0_source.zip`

## ライセンス

MIT License  
Copyright (c) 2026 Maximum
