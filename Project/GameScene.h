////===========================================================================
////@brief ゲームシーンクラス
//// ゲームシーンの処理を行う
////===========================================================================
//#pragma once
//#include"DxLib.h"
//#include"SceneBase.h"
//#include<vector>
//class Camera;
//class StageManager;
//class StageChanger;
//class EnemyManager;
//class PlayerManager;
//class Timer;
//class Collision;
//class Shadow;
//class Animation;
//
//using namespace std;
//
//class GameScene :public SceneBase
//{
//public:
//    GameScene();            //コンストラクタ
//    virtual ~GameScene();   //デストラクタ
//
//    void Create() override; //生成
//    void Final()  override; //最終処理
//    void Update() override; //更新
//    void Draw()   override; //描画
//
//    void EndWave(); //ウェーブの終了判定
//private:
//    static constexpr float  PLAYER_SHADOW_HEIGHT       = 1000.0f;   //プレイヤーの影の高さ
//    static constexpr float  PLAYER_SHADOW_SIZE         = 20.0f;     //プレイヤーの影のサイズ
//    static constexpr float  NORMAL_ENEMY_SHADOW_HEIGHT = 1000.0f;   //通常の敵の影の高さ
//    static constexpr float  NORMAL_ENEMY_SHADOW_SIZE   = 20.0f;     //通常の敵の影のサイズ
//    static constexpr float  BOSS_ENEMY_SHADOW_HEIGHT   = 1000.0f;   //ボスの影の高さ
//    static constexpr float  BOSS_ENEMY_SHADOW_SIZE     = 30.0f;     //ボスの影のサイズ
//    static constexpr int    FONT_SIZE                  = 28;        //フォントのサイズ
//    static constexpr int    FONT_THICK                 = 28;        //フォントの太さ
//    static const     int    FONT_COLOR;                             //フォントの色
//    static const     VECTOR SHADOW_OFFSET_POS;                      //プレイヤー座標オフセット
//
//    /*内部処理関数*/
//    void HitCheckAllEnemy();                    //球での当たり判定
//    void DrawShadow();                          //影の描画
//    void AttackToEnemy();                       //エネミーへの攻撃
//    void AttackToPlayer();                      //プレイヤーへの攻撃
//    void Init();                                //初期化
//    void ChangeNextScene();//シーン切り替え
//    /*クラス*/
//    Camera*        camera;          //カメラ
//    StageManager*  stageManager;    //ステージ
//    StageChanger*  stageChanger;    //ステージ変更
//    EnemyManager*  enemyManager;    //エネミー
//    PlayerManager* playerManager;   //プレイヤー
//    Collision*     collision;       //当たり判定
//    Shadow*        shadow;          //影
//    Animation* anim;
//    /*変数*/
//    int input;          //入力変数
//    int alpha;          //アルファ値
//    int fontHandle;     //フォントハンドル
//    int skyDomeHandle;
//    int bossModelHandle;
//};
//
