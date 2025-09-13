# VS Code KeyPad - 3D Models

このディレクトリには、VS Code KeyPad (Lilygo H621) 用の3Dプリンタケースファイルが含まれています。

## 📁 ファイル一覧

### STLファイル（すぐに印刷可能）

| ファイル名 | 用途 | サイズ |
|-----------|------|--------|  
| `keypad_case_bottom.stl` | メインケースボディ | 95×65×18mm |
| `keypad_case_top.stl` | トップカバー | 95×65×3mm |
| `keypad_display_bezel.stl` | ディスプレイベゼル | 58×45×2mm |

## 🚀 クイックスタート

```bash
# 1. このリポジトリをクローン
git clone https://github.com/NW-Lab/VsCodeKeyPad.git
cd VsCodeKeyPad/3d_models/

# 2. STLファイルを3Dプリンタソフトウェアで開く
# 推奨: PrusaSlicer, Cura, Ultimaker Cura

# 3. 推奨設定
# - フィラメント: PLA
# - レイヤー高: 0.2mm  
# - 充填率: 25%
# - サポート: bottomのみ
```

## 📋 必要部品

### 3Dプリント済みパーツ
- [x] Main Case Bottom
- [x] Top Cover  
- [x] Display Bezel

### 追加購入部品
- [ ] M3ネジ × 4本 (長さ8-10mm)
- [ ] M3ナット × 4個 (オプション)
- [ ] 滑り止めゴム足 × 4個 (オプション)

### ハードウェア
- [ ] Lilygo H621 (ESP32 + 2.4" TFT)
- [ ] VS Code KeyPadファームウェア書き込み済み

## 📖 詳細ドキュメント

- **印刷手順**: [`../docs/3d_printing/README.md`](../docs/3d_printing/README.md)
- **クイックガイド**: [`../docs/3d_printing/QUICK_START.md`](../docs/3d_printing/QUICK_START.md)  
- **技術仕様**: [`../docs/3d_printing/TECHNICAL_SPECS.md`](../docs/3d_printing/TECHNICAL_SPECS.md)

## ⚠️ 印刷前チェック

- [ ] プリンタベッドサイズ: 最低100mm×70mm必要
- [ ] フィラメント: PLA約50g準備  
- [ ] サポート材設定: bottomケースのみ有効
- [ ] レイヤー高: 0.3mm以下推奨

## 🛠️ カスタマイズ

寸法を変更したい場合は、元のPythonジェネレータースクリプト（`generate_case_stl.py`）を使用して再生成できます。

## 📄 ライセンス

これらの3DモデルファイルはMITライセンスで提供されます。自由にご利用ください。

---

**Ready to print!** 🎯 印刷してVS Code開発体験を向上させましょう！