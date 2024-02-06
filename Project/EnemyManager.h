/*インスタンスはすべて最初に生成する
変数で処理をする敵の数を変化させる*/
#pragma once

#include"DxLib.h"
#include<vector>
#include"BossEnemy.h"
#include"StrongEnemy.h"
#include"WeakEnemy.h"

class EnemyManager
{
public:
    EnemyManager();                                         //コンストラクタ
    ~EnemyManager();                                        //デストラクタ
    void Init();                           //初期化
    void Draw(VECTOR _playerPos, const bool _isFarm, const bool _isBoss);                            //描画
    void Move(const VECTOR _playerPos, const bool _isFarm, const bool _isBoss);//移動
    void Update(const VECTOR _playerPos,const float _playerLv, const bool _isFarm,const bool _isBoss);       //更新
    void CreateAndInit();                                          //生成
    void AllDestroy();//すべての削除
    void DrawShadow(const int _stageModelHandle, const bool _isFarm, const bool _isBoss);//影の描画
    void AdjustTheNumberOfEnemy(const int _playerLv);//エネミーのスポーン数の調整
    VECTOR RandomSpawnPos();//ランダムでスポーン座標を返す
    //移動量補正
    void FixMoveVecWeakEnemy(const int _enemyNum,const VECTOR _fixVec);
    void FixMoveVecStrongEnemy(const int _enemyNum, const VECTOR _fixVec);
    void FixMoveVecBossEnemy(const VECTOR _fixVec);
    //座標のgetter
    const VECTOR GetPosWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetPos(); }
    const VECTOR GetPosStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetPos(); }
    const VECTOR GetPosBossEnemy()const { return bossEnemy->GetPos(); }
    //移動量のgetter
    const VECTOR GetMoveVecWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetMoveVec(); }
    const VECTOR GetMoveVecStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetMoveVec(); }
    const VECTOR GetMoveVecBossEnemy()const { return bossEnemy->GetMoveVec(); }
    //エネミー配列のgetter
    const int GetMaxWeakEnemy()const { return MAX_WEAK_ENEMY_NUM; }
    const int GetMaxStrongEnemy()const { return MAX_STRONG_ENEMY_NUM; }
    const int GetNowWeakEnemyNum()const { return nowWeakEnemyNum; }
    const int GetNowStrongEnemyNum()const { return nowStrongEnemyNum; }
    const bool GetIsBossEnemy()const { return isBossEnemy; }
    //死亡フラグのgetter
    const bool GetIsDeathWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetIsDeath(); }
    const bool GetIsDeathStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetIsDeath(); }
    const bool GetIsDeathBossEnemy()const { return bossEnemy->GetIsDeath(); }
    //カプセル情報のgetter
    const CapsuleInfo GetCapsuleInfoWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetCapsuleInfo(); }
    const CapsuleInfo GetCapsuleInfoStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetCapsuleInfo(); }
    const CapsuleInfo GetCapsuleInfoBossEnemy()const { return bossEnemy->GetCapsuleInfo(); }
    //球情報のgetter
    const SphereInfo GetSphereInfoWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetSphereInfo(); }
    const SphereInfo GetSphereInfoStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetSphereInfo(); }
    const SphereInfo GetSphereInfoBossEnemy()const { return bossEnemy->GetSphereInfo(); }
    //攻撃力のgetter
    const float GetAtkWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetAtk(); }
    const float GetAtkStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetAtk(); }
    const float GetAtkBossEnemy()const { return bossEnemy->GetAtk(); }
    //攻撃フラグのgetter
    const float GetIsAttackWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetIsAttack(); }
    const float GetIsAttackStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetIsAttack(); }
    const float GetIsAttackBossEnemy()const { return bossEnemy->GetIsAttack(); }
    //無敵フラグのgetter
    const bool GetIsInvincibleWeakEnemy(const int _enemyNum)const { return weakEnemy[_enemyNum]->GetIsInvincible(); }
    const bool GetIsInvincibleStrongEnemy(const int _enemyNum)const { return strongEnemy[_enemyNum]->GetIsInvincible(); }
    const bool GetIsInvincibleBossEnemy()const { return bossEnemy->GetIsInvincible(); }
    //無敵フラグを下す
    void FlaggingBossEnemy();//フラグを下す
    //HP計算
    float CalcHPWeakEnemy(const int _enemyNum,const float _atk,const VECTOR _attackerPos);
    float CalcHPStrongEnemy(const int _enemyNum, const float _atk, const VECTOR _attackerPos);
    float CalcHPBossEnemy(const float _atk, const VECTOR _attackerPos);
    //与える経験値の初期化
    void InitExpToGive(const int _enemyNum);
    const void PhysicalRecoveryBossEnemy();

private:
    /*定数*/
    enum class ModelType//モデル変数
    {
        WEAK_MODEL,     //雑魚敵
        STRONG_MODEL,   //中ボス
        BOSS_MODEL,     //ボス
    };
    static constexpr int MAX_WEAK_ENEMY_NUM = 8;  //雑魚敵の最大数
    static constexpr int MAX_STRONG_ENEMY_NUM = 8;//中ボスの最大数

    static constexpr float  WEAK_ENEMY_RADIUS = 5.0f;         //雑魚敵の当たり判定用スフィア半径
    static constexpr float  STRONG_ENEMY_RADIUS = 5.0f;       //中ボスの当たり判定用スフィア半径
    static constexpr float  BOSS_ENEMY_RADIUS = 5.0f;         //ボスの当たり判定用スフィア半径

    static constexpr float  NORMAL_ENEMY_SHADOW_HEIGHT = 1000.0f;   //通常の敵の影の高さ
    static constexpr float  NORMAL_ENEMY_SHADOW_SIZE   = 20.0f;     //通常の敵の影のサイズ
    static constexpr float  BOSS_ENEMY_SHADOW_HEIGHT   = 1000.0f;   //ボスの影の高さ
    static constexpr float  BOSS_ENEMY_SHADOW_SIZE     = 30.0f;     //ボスの影のサイズ
    /*メンバ変数*/
    std::vector<WeakEnemy*> weakEnemy;      //雑魚敵
    std::vector<StrongEnemy*> strongEnemy;  //中ボス
    BossEnemy* bossEnemy;                   //ラスボス

    MV1_COLL_RESULT_POLY_DIM hitPolyDim;    //コリジョン結果代入用ポリゴン配列

    vector<int>model;       //モデル数
    int nowWeakEnemyNum;    //現在の雑魚敵の数
    int nowStrongEnemyNum;  //現在の中ボスの数
    bool isStrongEnemy;     //中ボスが生成されているか
    bool isBossEnemy;       //ボスが生成されているか
    bool isDrawImg;         //画像を描画しているか
    bool isHitCheckSetUp;   //コリジョン情報を構築したか
    int font;	            //フォントハンドル
    int frameImage;         //HPバーフレーム
    int hpImage;            //HPバー

    //スポーンポイントの変数
    static constexpr int SPAWN_POINT_NUM = 8;
    static const VECTOR SPAWN_POINT[SPAWN_POINT_NUM];
    bool isAlreadySpawn[SPAWN_POINT_NUM];
};


