# Arduino IDE Setup Instructions

## Arduino IDE でのセットアップ手順

### 1. ESP32ボードパッケージのインストール

1. Arduino IDEを開く
2. **File** → **Preferences** を選択
3. **Additional Boards Manager URLs** に以下を追加:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. **Tools** → **Board** → **Boards Manager** を選択
5. "esp32" を検索して **ESP32 by Espressif Systems** をインストール

### 2. 必要なライブラリのインストール

Arduino IDE のライブラリマネージャーから以下をインストール:

#### TFT_eSPI
1. **Sketch** → **Include Library** → **Manage Libraries**
2. "TFT_eSPI" を検索
3. **TFT_eSPI by Bodmer** をインストール

#### ESP32-BLE-Keyboard  
1. ライブラリマネージャーで "ESP32-BLE-Keyboard" を検索
2. **ESP32-BLE-Keyboard by T-vK** をインストール

### 3. TFT_eSPI の設定

#### 方法1: User_Setup.h をコピー (推奨)
1. このリポジトリの `User_Setup.h` をコピー
2. Arduino ライブラリフォルダを開く:
   - Windows: `Documents\Arduino\libraries\TFT_eSPI\`
   - Mac: `~/Documents/Arduino/libraries/TFT_eSPI/`
   - Linux: `~/Arduino/libraries/TFT_eSPI/`
3. 既存の `User_Setup.h` をバックアップ
4. コピーした `User_Setup.h` で置き換える

#### 方法2: User_Setup_Select.h を編集
1. `TFT_eSPI/User_Setup_Select.h` を開く
2. 既存の設定をコメントアウト
3. 以下の行のコメントを外す:
   ```cpp
   #include <User_Setups/Setup25_TTGO_T_Display.h>  // カスタム設定として使用
   ```

### 4. ボード設定

1. **Tools** → **Board** → **ESP32 Arduino** → **ESP32 Dev Module** を選択
2. 以下の設定を確認:
   - **Upload Speed**: 921600
   - **CPU Frequency**: 240MHz (WiFi/BT)
   - **Flash Frequency**: 80MHz
   - **Flash Mode**: QIO
   - **Flash Size**: 4MB (32Mb)
   - **Partition Scheme**: Default 4MB with spiffs
   - **Core Debug Level**: None

### 5. コンパイルとアップロード

1. `arduino_ide_version/VsCodeKeyPad.ino` を Arduino IDE で開く
2. Lilygo H621 をUSBで接続
3. **Tools** → **Port** で適切なCOMポートを選択
4. **Sketch** → **Upload** (または Ctrl+U)

### 6. 動作確認

1. シリアルモニタを開く (Ctrl+Shift+M)
2. ボーレート 115200 に設定
3. "VS Code KeyPad Ready!" が表示されるか確認
4. ディスプレイにキーパッドが表示されるか確認

## トラブルシューティング

### コンパイルエラー
```
fatal error: User_Setup.h: No such file or directory
```
→ User_Setup.h の設定が不完全です。上記手順3を再実行してください。

### アップロードエラー
```
A fatal error occurred: Failed to connect to ESP32
```
→ ボタンを押しながらアップロード:
1. BOOTボタンを押しながらENボタンを押す
2. ENボタンを離す
3. アップロード開始後にBOOTボタンを離す

### ディスプレイが表示されない
→ TFT_eSPI の設定を確認:
- ピン設定がハードウェアと一致しているか
- ドライバー設定 (ILI9341_DRIVER) が有効か

### Bluetooth接続できない
→ デバイスマネージャーで確認:
1. PCのBluetooth設定を開く
2. "VS Code KeyPad" が表示されるか確認
3. ペアリングを試行

## カスタマイズ

### キー配置の変更
`setupKeys()` 関数内でキーの位置とラベルを変更可能:

```cpp
keys[0] = {x, y, width, height, "Label", keycode, modifier, isCopilotKey, isPressed};
```

### 色の変更
ファイル上部の色定義を変更:

```cpp
#define COLOR_COPILOT 0xF800   // 赤色 (RGB565)
#define COLOR_KEY_BG 0x2945    // 青色
```

### 新しいキーの追加
1. `numKeys` の値を増やす
2. `keys` 配列にエントリを追加
3. `handleKeyPress()` に動作を実装

## ピン配置 (Lilygo H621)

| 機能 | ピン |
|------|------|
| TFT_MISO | 19 |
| TFT_MOSI | 23 |
| TFT_SCLK | 18 |
| TFT_CS   | 5  |
| TFT_DC   | 2  |
| TFT_RST  | 4  |
| TFT_BL   | 15 |
| TOUCH_CS | 33 |