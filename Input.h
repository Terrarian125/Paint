#pragma once


namespace Input {
	//キーボード取得関連
	void KeyStateUpdate();
	bool IsKeyUP(int keyCode);   // 離された瞬間
	bool IsKeyDown(int keyCode); // 押された瞬間
	int IsKeepKeyDown(int keyCode); // 押しっぱなしのフレーム数


	// マウス取得関連
	
	void MouseStateUpdate();
	bool IsMouseUP(int mouseCode);   // 離された瞬間
	bool IsMouseDown(int mouseCode); // 押された瞬間
	int IsKeepMouseDown(int mouseCode); // 押しっぱなしのフレーム数

	// マウス座標取得
	int GetMouseX();
	int GetMouseY();

	// マウスホイール取得
	int GetMouseWheel();


	// 音量レベル定義
	const int MAX_VOLUME_VALUE = 255;	// 基準となる最大値を定義

	// ５段階音量レベル
	const int Volume_5 = MAX_VOLUME_VALUE * 2;
	const int Volume_4 = MAX_VOLUME_VALUE + 128;
	const int Volume_3 = MAX_VOLUME_VALUE;
	const int Volume_2 = MAX_VOLUME_VALUE / 2;
	const int Volume_1 = MAX_VOLUME_VALUE / 4;
	const int Volume_0 = 0;
}

/*
◇今後の予定
〇入力関連の拡張機能
ゲームパッド/ジョイスティック入力対応:
ボタンの押された瞬間、離された瞬間、押しっぱなしの取得。
アナログスティック（軸）の**傾き（浮動小数点数）**の取得。
アナログスティックのデッドゾーン（微小なブレを無視する範囲）の適用。
入力アクションマッピング（抽象化）
物理入力（キー、マウスボタン、ゲームパッドボタン）を、ゲーム内の抽象的なアクション名（例: Jump、Attack）に関連付ける機能。
ユーザーによるキーコンフィグ（操作設定の変更）を容易にする。
タッチ入力対応 (モバイル/タブレット対応の場合):
画面に触れている座標とタッチID（マルチタッチ用）の取得。
ジェスチャー（タップ、フリック、ピンチなど）の検出。
特殊センサー入力:
加速度センサー/ジャイロセンサー（デバイスの傾きや揺れ）のデータ取得（モバイルや特定のハードウェア向け）。
〇設定関連の拡張機能
グラフィック設定:
画面モード（ウィンドウ / フルスクリーン）の切り替え。
実行時の画面解像度の設定。
V-Sync（垂直同期）の有効/無効設定。
描画品質（影、テクスチャなど）の調整。
〇パフォーマンス・同期設定
ゲーム全体の目標フレームレート（FPS）の制御。
タイムスケール（ゲーム全体の進行速度）の調整機能（デバッグや演出用）。
〇セーブ・ロード機能
ゲームやユーザー設定の状態をファイルに保存・読み込みする機能。
〇言語設定
アプリケーション内の表示言語（日本語、英語など）を切り替える機能。
*/