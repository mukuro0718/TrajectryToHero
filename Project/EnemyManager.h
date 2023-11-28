///*インスタンスはすべて最初に生成する
//変数で処理をする敵の数を変化させる*/
//#pragma once
//
//#include"DxLib.h"
//#include"EnemyBase.h"
//#include<vector>
//
//using namespace std;
//class EnemyManager
//{
//public:
//    EnemyManager();                                         //コンストラクタ
//    ~EnemyManager();                                        //デストラクタ
//    void Init();                           //初期化
//    void Draw(VECTOR playerPos, const bool isFarm, const bool isBoss);                            //描画
//    void Update(CharacterBase playerBase, CharacterStatus playerStatus,const bool isFarm,const bool isBoss);       //更新
//    void CreateAndInit();                                          //生成
//    void AllDestroy();//すべての削除
//    void PushBack();    //当たり判定
//    bool CountDestroyEnemy();
//
//    //エネミー配列のgetter/setter
//    CharacterBase GetWeakBase(int i) { return weakEnemy[i]->GetBase(); }
//    void SetWeakBase(int i, CharacterBase _set) { weakEnemy[i]->SetBase(_set); }
//    CharacterStatus GetWeakStatus(int i) { return weakEnemy[i]->GetStatus(); }
//    void SetWeakStatus(int i, CharacterStatus _set) { weakEnemy[i]->SetStatus(_set); }
//    const int GetMaxWeakEnemy()const { return MAX_WEAK_ENEMY_NUM; }
//    const int GetNowEnemyIndex()const { return nowEnemyIndex; }
//
//    CharacterBase GetStrongBase() { return strongEnemy->GetBase(); }
//    void SetStrongBase(CharacterBase _set) { strongEnemy->SetBase(_set); }
//    CharacterStatus GetStrongStatus() { return strongEnemy->GetStatus(); }
//    void SetStrongStatus(CharacterStatus _set) { strongEnemy->SetStatus(_set); }
//    const bool GetIsStrongEnemy()const { return isStrongEnemy; }
//
//    CharacterBase GetBossBase() { return bossEnemy->GetBase(); }
//    void SetBossBase(CharacterBase _set) { bossEnemy->SetBase(_set); }
//    CharacterStatus GetBossStatus() { return bossEnemy->GetStatus(); }
//    void SetBossStatus(CharacterStatus _set) { bossEnemy->SetStatus(_set); }
//    const bool GetIsBossEnemy()const { return isBossEnemy; }
//private:
//    /*定数*/
//    enum class ModelType//モデル変数
//    {
//        WEAK_MODEL,     //雑魚敵
//        STRONG_MODEL,   //中ボス
//        BOSS_MODEL,     //ボス
//    };
//    static constexpr int    MAX_WEAK_ENEMY_NUM = 8;         //雑魚敵の数
//    static constexpr float  weakEnemyRadius = 5.0f;         //雑魚敵の当たり判定用スフィア半径
//    static constexpr float  strongEnemyRadius = 5.0f;       //中ボスの当たり判定用スフィア半径
//    static constexpr float  bossEnemyRadius = 5.0f;         //ボスの当たり判定用スフィア半径
//    
//    /*メンバ変数*/
//    EnemyBase* weakEnemy[MAX_WEAK_ENEMY_NUM];
//    EnemyBase* strongEnemy;
//    EnemyBase* bossEnemy;                                   //ラスボス
//    MV1_COLL_RESULT_POLY_DIM hitPolyDim;                    //コリジョン結果代入用ポリゴン配列
//    vector<int>model;
//    bool isStrongEnemy;                                     //中ボスが生成されているか
//    bool isBossEnemy;                                       //ボスが生成されているか
//    bool isDrawImg;                                         //画像を描画しているか
//    bool isHitCheckSetUp;                                   //コリジョン情報を構築したか
//    int nowEnemyIndex;                                      //現在いる敵の数
//    int destroyEnemy;                                       //倒されたエネミーの数
//    int deathStrongEnemyNum;
//    static const	 int   FONT_COLOR_GREEN;			//フォントの色
//    static constexpr int   HP_FONT_SIZE = 64;		//フォントのサイズ
//    static constexpr int   HP_FONT_THICK = 28;		//フォントの太さ
//    int   hpFontHandle;	//HPフォントハンドル
//    
//    //スポーンポイントの変数
//    static constexpr int SPAWN_POINT_NUM = 8;
//    static const VECTOR SPAWN_POINT[SPAWN_POINT_NUM];
//    bool isAlreadySpawn[SPAWN_POINT_NUM];
//};
//
//
