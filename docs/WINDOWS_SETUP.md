# Windows セットアップガイド

このガイドでは、Windows環境でVS Code KeyPadを構築・使用する方法を説明します。

## 必要なソフトウェア

### 1. Git for Windows (推奨)
- [Git for Windows](https://gitforwindows.org/)をダウンロード・インストール
- Git Bash、Command Prompt、PowerShell すべてで `git` コマンドが使用可能になります

### 2. Python (PlatformIO使用時)
- [Python 3.7以降](https://www.python.org/downloads/windows/)をインストール
- インストール時に "Add to PATH" オプションを有効にしてください

### 3. VS Code (推奨)
- [Visual Studio Code](https://code.visualstudio.com/)をダウンロード・インストール
- PlatformIO IDE拡張機能をインストール

## セットアップ手順

### ステップ 1: リポジトリのクローン
```cmd
git clone https://github.com/NW-Lab/VsCodeKeyPad.git
cd VsCodeKeyPad
```

### ステップ 2: PlatformIOのインストール

#### 方法A: VS Code拡張機能 (推奨)
1. VS Codeでプロジェクトフォルダを開く
2. 拡張機能タブ (Ctrl+Shift+X) を開く
3. "PlatformIO IDE" を検索してインストール
4. VS Codeを再起動

#### 方法B: コマンドライン
```cmd
pip install platformio
```

### ステップ 3: ビルドテスト

#### コマンドプロンプト
```cmd
build_test.bat
```

#### PowerShell
```powershell
# 実行ポリシーの設定 (初回のみ)
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser

# ビルドテスト実行
.\build_test.ps1
```

### ステップ 4: デバイスの接続とアップロード
1. Lilygo H621をUSBケーブルでPCに接続
2. デバイスマネージャーでCOMポートを確認 (例: COM3, COM4)
3. アップロード実行:
   ```cmd
   pio run --target upload
   ```

## Windows固有の注意点

### COM ポートの確認
- デバイスマネージャー → ポート(COMとLPT)
- ESP32デバイスが認識されない場合、CP2102またはCH340ドライバーが必要

### USB ドライバー
- **CP2102**: [Silicon Labs](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
- **CH340**: [WCH](http://www.wch-ic.com/downloads/CH341SER_EXE.html)

### Bluetooth ペアリング
1. Windowsの「設定」→「デバイス」→「Bluetoothとその他のデバイス」
2. 「Bluetoothまたはその他のデバイスを追加する」をクリック
3. "VS Code KeyPad" を選択してペアリング

## トラブルシューティング

### ビルドエラー

#### "pio' は、内部コマンドまたは外部コマンド...として認識されません"
```cmd
# PATHの確認
echo %PATH%

# PlatformIOの再インストール
pip uninstall platformio
pip install platformio
```

#### "アクセスが拒否されました" エラー
- 管理者権限でコマンドプロンプトを実行
- アンチウイルスソフトでフォルダを除外設定

### アップロードエラー

#### "シリアルポートに接続できません"
1. デバイスマネージャーでポートを確認
2. Arduino IDEのシリアルモニタやPuTTYを閉じる
3. USBケーブルを抜き差し
4. BOOTボタンを押しながらENボタンを押してリセット

#### "アップロード失敗"
```cmd
# 特定のポートを指定
pio run --target upload --upload-port COM3

# モニターでデバッグ
pio device monitor --port COM3 --baud 115200
```

### PowerShell エラー

#### "実行ポリシーにより禁止されています"
```powershell
# 現在のポリシーを確認
Get-ExecutionPolicy

# ユーザースコープで許可
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser

# または一時的に許可
powershell -ExecutionPolicy Bypass -File build_test.ps1
```

## 代替手順: Arduino IDE

PlatformIOが動作しない場合、Arduino IDEを使用できます:

1. [Arduino IDE](https://www.arduino.cc/en/software)をダウンロード・インストール
2. `arduino_ide_version/README_Arduino.md` の手順に従ってセットアップ
3. `arduino_ide_version/VsCodeKeyPad.ino` を開いてアップロード

## パフォーマンス最適化

### Windowsでの高速化
- Windows Defenderのリアルタイム保護でプロジェクトフォルダを除外
- SSDにプロジェクトを配置
- 仮想メモリの設定を適切に調整

### ビルド時間短縮
```cmd
# 並列ビルド (コア数に応じて調整)
pio run --jobs 4
```

## よくある質問

### Q: WindowsでLinuxのbashスクリプトは実行できますか？
A: Git BashまたはWSL (Windows Subsystem for Linux) を使用すれば可能ですが、ネイティブの `.bat` や `.ps1` スクリプトの使用を推奨します。

### Q: コマンドプロンプトとPowerShellのどちらを使うべきですか？
A: どちらでも動作しますが、PowerShellの方が豊富な機能とエラー処理を提供します。

### Q: Arduino IDEとPlatformIOのどちらがおすすめですか？
A: 初心者にはArduino IDE、開発者にはPlatformIOを推奨します。PlatformIOの方が依存関係の管理が自動化されています。