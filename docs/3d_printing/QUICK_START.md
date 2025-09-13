# 3D Printing Quick Start Guide

VS Code KeyPadの3D印刷可能ケースのクイックスタートガイドです。

## 🚀 すぐに印刷したい方へ

### 1. STLファイルダウンロード
```bash
git clone https://github.com/NW-Lab/VsCodeKeyPad.git
cd VsCodeKeyPad/3d_models/
```

### 2. 印刷設定（PLA推奨）
- **レイヤー高**: 0.2mm
- **充填率**: 25%
- **印刷速度**: 50mm/s
- **サポート**: bottomのみ必要

### 3. 印刷順序
1. `keypad_case_bottom.stl` （約45分）
2. `keypad_case_top.stl` （約20分）
3. `keypad_display_bezel.stl` （約15分）

### 4. 必要部品
- M3ネジ × 4本 (8mm長)
- M3ナット × 4個

## 📏 寸法チェックリスト

印刷前に以下を確認：

- [ ] プリンタベッドサイズ: 最低100mm × 70mm必要
- [ ] ノズル径: 0.4mm推奨
- [ ] フィラメント: PLA 約50g必要

## ⏱️ 印刷時間目安

| ファイル | 印刷時間 | フィラメント使用量 |
|---------|---------|----------------|
| Bottom Case | 約45分 | 約25g |
| Top Cover | 約20分 | 約15g |
| Display Bezel | 約15分 | 約10g |
| **合計** | **約80分** | **約50g** |

## 🔧 簡単組み立て

1. H621をbottomケースに配置
2. ベゼルでディスプレイを固定  
3. topカバーを被せてネジ止め
4. 完成！

詳細な手順は `README.md` を参照してください。