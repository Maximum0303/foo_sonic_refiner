# Sonic Refiner v0.2.0 テスト結果

## Master Strengthの基本動作

1. 内蔵プリセット「標準」を呼び出す
2. Master Strengthを100%にする
3. v0.1.1と同じ音であることを確認
4. 100%から50%へ下げ、4項目の効果がまとめて弱くなることを確認
5. 0%にし、Depth・Clarity・Width・Ambienceが無補正になることを確認

## 対象外の機能

Master Strengthを0%にしても、次の設定は変更されません。

- Output Gain
- 自動ヘッドルーム保護
- レベルマッチ・バイパス
- Sonic Refiner本体の有効／無効

## Width

- 0%：Side 100%
- 50%：Side 100%と設定値の中間
- 100%：Widthスライダーの設定値

低域保護は従来どおり約180 Hzです。

## プリセット互換性

- v0.1.1で保存した任意プリセットを呼び出すとMaster Strengthは100%
- 新規保存したプリセットにはMaster Strengthも保存される
- 書き出し・読み込み後もMaster Strengthが保持される
- 旧SRP1／SRP2バックアップを読み込める

## 表示

- 設定画面のサイズは560×320のまま
- Master Strengthの値が0～100%で表示される
- Depth、Clarity、Width、Ambienceの実効値表示がMaster Strengthに連動する
- ライトモードとダークモードの両方で表示が崩れない


## 実施結果

以下を実機で確認済みです。

- Master Strength 100%でv0.1.1と同じ音
- 50%で4項目の効果が一括で弱まる
- 0%でDepth・Clarity・Width・Ambienceが無補正
- Output Gain、保護機能、レベルマッチは対象外
- 任意プリセットへMaster Strengthを保存・呼び戻し
- .srpbackupへの書き出し・読み込み
- 内蔵プリセット呼び出し時は100%
- v0.1.1バックアップとの互換性
- 実効値表示の連動
- 再起動後の設定保持
- キャンセル時の変更破棄
- ライトモード・ダークモード
- 再生中の連続操作とプリセット切り替え
- 異音、音切れ、停止、クラッシュなし
