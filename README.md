# kusanagi-effect
## 機能概要
入力された動画に、炎の動画を合成して保存する。

## 動作環境
OepnCV、CMakeのインストールが必要です。

## ビルド方法
### build用のディレクトリの作成
```
mkdir build && cd build
```
### buildの設定
```
cmake ../
```

### build
```
cmake --build .
```

### アプリケーションの実行
```
./main 読み込む動画ファイルのパス
```

## サンプル動画
### 入力動画
```
hand.mp4
```

### 合成する動画
```
fire.mp4
```

### 出力動画
```
result.mp4
```