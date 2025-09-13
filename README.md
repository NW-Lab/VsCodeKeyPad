# VsCodeKeyPad

VS Code用のタッチスクリーンキーパッドです。GitHub Copilotの操作と一般的なVS Codeショートカットに特化したデバイスです。

## 特徴

- **GitHub Copilot専用キー**: 
  - Accept (Tab): 提案を全て受け入れ
  - Accept Word (Ctrl+→): 単語単位で受け入れ  
  - Reject (Esc): 提案を却下
  - Show Copilot (Ctrl+Tab): Copilotパネル表示

- **VS Code便利ショートカット**:
  - Quick Open (Ctrl+P): ファイル検索
  - Command (Ctrl+Shift+P): コマンドパレット
  - Save All (Ctrl+Shift+S): 全保存
  - Format (Shift+Alt+F): コード整形
  - Debug (F5): デバッグ開始
  - Terminal (Ctrl+`): ターミナル表示
  - Settings (Ctrl+,): 設定画面

- **接続方式**: Bluetooth HID キーボード（USBモードも準備中）
- **ディスプレイ**: 2.4インチ TFTタッチスクリーン
- **ハードウェア**: Lilygo H621 (ESP32ベース)

## ハードウェア要件

- **Lilygo H621**: ESP32 + 2.4" ILI9341 TFT + タッチスクリーン
- microUSBケーブル (プログラム書き込み・電源用)

## セットアップ手順

> **Windows ユーザー向け**: 詳細なWindows固有の手順については [Windows セットアップガイド](docs/WINDOWS_SETUP.md) をご覧ください。

### 1. 開発環境の準備

#### すべてのOS共通
```bash
# このリポジトリをクローン
git clone https://github.com/NW-Lab/VsCodeKeyPad.git
cd VsCodeKeyPad
```

#### PlatformIOのインストール方法

**推奨: VS Code拡張機能**
1. VS CodeでPlatformIO IDE拡張機能をインストール
2. 自動的にPlatformIO Coreもインストールされます

**コマンドライン:**
```bash
# Python pip経由 (Linux/Mac/Windows)
pip install platformio
```

**Windows固有の注意点:**
- PowerShell実行ポリシーの設定が必要な場合があります:
  ```powershell
  Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
  ```

### 2. ライブラリの自動インストール

PlatformIOを使用する場合、必要なライブラリは自動的にインストールされます：

- TFT_eSPI (ディスプレイ制御)
- ESP32-BLE-Keyboard (Bluetooth HID)
- ArduinoJson (設定管理)

### 3. TFT_eSPI設定

`User_Setup.h`ファイルがLilygo H621用に設定済みです。追加設定は不要です。

### 4. コンパイルと書き込み

#### PlatformIOを使用する場合

**Linux/Mac:**
```bash
# ビルドテスト
./build_test.sh

# アップロード
pio run --target upload
```

**Windows:**
```cmd
# ビルドテスト (コマンドプロンプト)
build_test.bat

# ビルドテスト (PowerShell)
.\build_test.ps1

# アップロード
pio run --target upload
```

#### Arduino IDEを使用する場合
`arduino_ide_version/VsCodeKeyPad.ino` をArduino IDEで開いてアップロード
詳細は `arduino_ide_version/README_Arduino.md` を参照

### 5. ペアリング手順

1. デバイスの電源を入れる
2. PCのBluetooth設定を開く  
3. "VS Code KeyPad"デバイスを検索してペアリング
4. 画面上部に"BLE Connected"と表示されれば完了

## 使用方法

### 基本操作
- 画面上のキーをタッチしてキーコードを送信
- 赤色のキー: GitHub Copilot専用機能
- 青色のキー: VS Code一般機能
- Mode Switchキー: USB/Bluetooth切替（将来実装予定）

### GitHub Copilotでの使用例
1. VS CodeでCopilotが提案を表示
2. **Accept**キーをタッチして提案を全て受け入れ
3. **Accept Word**キーで単語ずつ受け入れ
4. **Reject**キーで提案を却下

### カスタマイズ

キー配置やショートカットは`src/display_manager.cpp`の`setupKeys()`関数で変更できます。

## トラブルシューティング

### Windows固有の問題

#### "build_test.bat は認識されません" エラー
- コマンドプロンプトでプロジェクトフォルダに移動してから実行
- または PowerShell で `.\build_test.ps1` を使用

#### PowerShellで "実行ポリシー" エラー
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

#### COM ポートが認識されない
1. デバイスマネージャーでCP2102/CH340ドライバーを確認
2. 必要に応じてUSB-Serialドライバーをインストール

### 共通の問題

### Bluetoothが接続できない
- PCのBluetoothを一度オフ/オンしてください
- デバイスを再起動してください
- PCの近くに配置してください

### タッチが反応しない  
- `User_Setup.h`のTOUCH_CS pin設定を確認
- タッチキャリブレーション値の調整が必要な場合があります

### 画面が表示されない
- TFT接続を確認
- `User_Setup.h`のピン設定がハードウェアと一致するか確認

## 開発・カスタマイズ

### プロジェクト構造
```
VsCodeKeyPad/
├── platformio.ini          # ビルド設定
├── User_Setup.h             # TFT_eSPI設定
├── include/                 # ヘッダーファイル
│   ├── keypad_config.h     # キー定義・設定
│   ├── display_manager.h   # ディスプレイ制御
│   └── keyboard_manager.h  # キーボード制御
└── src/                     # ソースファイル
    ├── main.cpp            # メイン処理
    ├── display_manager.cpp # UI描画・タッチ処理
    └── keyboard_manager.cpp # HID送信処理
```

### 新しいキーの追加
1. `display_manager.cpp`の`setupKeys()`で配置を定義
2. `main.cpp`の`handleKeyPress()`で動作を実装

## ライセンス

MIT License

## 貢献

プルリクエストやイシューの報告を歓迎します。

## 今後の予定

- [ ] USB HIDモードの実装
- [ ] 設定画面の追加
- [ ] カスタムキー設定機能
- [ ] バックライト自動調整
- [ ] バッテリー駆動対応
