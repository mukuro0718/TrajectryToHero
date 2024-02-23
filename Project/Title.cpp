//===========================================================================
//@brief タイトルクラス
//===========================================================================
#include"Title.h"
#include"TutorialStage.h"
#include"Camera.h"
#include"SwordGirl.h"
#include"Common.h"
#include"OperationUI.h"
#include"Load.h"
#include"TutorialEnemy.h"
#include"Collision.h"
#include"StatusUpParticle.h"

const int Title::FONT_COLOR = GetColor(200, 200, 200);
/// <summary>
/// コンストラクタ
/// </summary>
Title::Title()
	:startIconAlpha(MIN_ALPHA_VALUE)
	, titleAlpha(MAX_ALPHA_VALUE)
	, stageNameAlpha(MIN_ALPHA_VALUE)
	, addAlphaValue(ADD_ALPHA_VALUE)
	, frameCount(INIT_FRAME_COUNT)
	, isChangeAddAlpha(false)
	, isFrameCount(false)
	, isDrawTitleEnd(false)
	, isDrawTitleFinish(false)
	, isTitleEnd(false)
	, isDrawStageName(false)
	, isChangeScene(false)
	, stage(nullptr)
	, camera(nullptr)
	, player(nullptr)
	, opeUI(nullptr)
	, statusUpParticle(nullptr)
	, tutorialProgress(0)
	, isChange(false)
	, textAlpha(MIN_ALPHA_VALUE)
	, progressFrameCount(0)
	, destroyEnemy(false)
	, enemy(nullptr)
	, collision(nullptr)
	, prevPlayerAtk(0.0f)
	, isDescription(false)
	, strongUI(0)
{
	//ロードクラスのインスタンスを取得
	auto& load = Load::GetInstance();
	//画像のロード
	load.GetTitleData(&titleData, &fontData, &playerData, &enemyData, &stageData);
	load.GetStrongerUIData(&strongUI);
	stage = new TutorialStage(stageData);
	camera = new Camera();
	player = new SwordGirl(playerData[static_cast<int>(PlayerData::MODEL)], playerData[static_cast<int>(PlayerData::FRAME)], playerData[static_cast<int>(PlayerData::HP)], playerData[static_cast<int>(PlayerData::EXP)], fontData[static_cast<int>(FontType::TEXT)]);
	opeUI = new OperationUI();
	enemy = new TutorialEnemy(MV1LoadModel("Data/Model/Enemy/WeakEnemy.mv1"));
	collision = new Collision();
	statusUpParticle = new StatusUpParticle(player->GetLv());
	prevPlayerAtk = player->GetAtk();
	//初期化
	Init();
}
/// <summary>
/// 初期化
/// </summary>
void Title::Init()
{
	player->Init();
	enemy->Init();
	camera->Init(player->GetPos());
	for (int i = 0; i < PROGRESS_NUM; i++)
	{
		isProgress.push_back(false);
	}
}
/// <summary>
/// デストラクタ
/// </summary>
Title::~Title()
{
	if (player)
	{
		delete(player);
		player = nullptr;
	}
	if (camera)
	{
		delete(camera);
		camera = nullptr;
	}
	if (enemy)
	{
		delete(enemy);
		enemy = nullptr;
	}
	if (stage)
	{
		delete(stage);
		stage = nullptr;
	}
	if (opeUI)
	{
		delete(opeUI);
		opeUI = nullptr;
	}
	if (collision)
	{
		delete(collision);
		collision = nullptr;
	}
}
/// <summary>
/// タイトルメニュー用アルファ値変更
/// </summary>
void Title::ChangeTitleAlphaValue()
{
	int tmpAlpha = 0;
	if (!isDrawTitleFinish)
	{
		tmpAlpha = startIconAlpha;
	}
	if(isDrawTitleFinish && !isDrawTitleEnd)
	{
		tmpAlpha = titleAlpha;
	}
	if (isDrawStageName)
	{
		tmpAlpha = stageNameAlpha;
	}

	tmpAlpha += addAlphaValue;

	if (tmpAlpha >= MAX_ALPHA_VALUE)
	{
		if (isChangeAddAlpha)
		{
			addAlphaValue = -ADD_ALPHA_VALUE;
			isChangeAddAlpha = false;
		}
		else
		{
			tmpAlpha = MAX_ALPHA_VALUE;
			isFrameCount = true;
		}
	}

	if (tmpAlpha <= MIN_ALPHA_VALUE)
	{
		if (isChangeAddAlpha)
		{
			addAlphaValue = ADD_ALPHA_VALUE;
			isChangeAddAlpha = false;
		}
		else
		{
			tmpAlpha = MIN_ALPHA_VALUE;
			isFrameCount = true;
		}
	}

	if (isFrameCount)
	{
		frameCount++;
		if (frameCount == MAX_FRAME_COUNT)
		{
			isFrameCount = false;
			isChangeAddAlpha = true;
			frameCount = INIT_FRAME_COUNT;
		}
	}
	if (!isDrawTitleFinish)
	{
		startIconAlpha = tmpAlpha;
	}
	if (isDrawTitleFinish && !isDrawTitleEnd)
	{
		titleAlpha = tmpAlpha;
	}
	if (isDrawStageName)
	{
		stageNameAlpha = tmpAlpha;
	}

}
/// <summary>
/// 更新
/// </summary>
void Title::Update()
{
	FragChanger();
	//タイトル用のアルファ値を変更する（途中から使わない）
	ChangeTitleAlphaValue();
	//地面、焚火、ゲートの更新
	stage->Update();
	//カメラの更新
	camera->Update(player->GetPos());
	//焚火メニューを表示していた場合は、通らないようにする
	if (!player->GetIsShowStatusMenu())
	{
		//無敵時間の計測
		player->CountInvincibleTimer();
		//もしタイトルとステージ名の描画が終了していたら
		if (isDrawTitleEnd)
		{
			//プレイヤーの移動
			player->Move(camera->GetCameraToPlayer());
			//プレイヤーの攻撃
			player->Attack();
			OnDamage();
			FixMoveVec();
		}
		//プレイヤーの更新
		player->Update();
		enemy->Update();
		//操作説明UIの表示をする
		opeUI->Update(player->GetIsMove());
		//プレイヤーUIの更新
		player->UpdateUI();
		//アニメーションの変更
		player->AnimChange();
	}
	//ステータスの更新
	player->StatusUpdate(stage->GetBonfirePos());
	float atk = player->GetAtk();
	if (atk != prevPlayerAtk && !player->GetIsShowStatusMenu())
	{
		enemy->OnIsDamage();
	}
	if(!player->GetIsShowStatusMenu())
	{
		player->TutorialStatusReset();
	}
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		isChangeScene = true;
	}
	statusUpParticle->Update(player->GetPos(), player->GetIsBonfireMenu(), player->GetLv());

}
/// <summary>
/// 描画
/// </summary>
void Title::Draw()
{
	stage->Draw();
	enemy->Draw(player->GetLv());
	enemy->DrawShadow(stage->GetGroundModelHandle());
	player->Draw();
	player->DrawShadow(stage->GetGroundModelHandle(),player->GetPos(),1000.0f,20.0f);
	player->DrawUI();
	opeUI->Draw(stage->GetBonfirePos(), player->GetPos());
	DrawTutorialText();
	statusUpParticle->Draw(player->GetIsBonfireMenu());
	player->DrawMenu();
	/*タイトルロゴと開始ボタンの表示*/
	DrawTitle();
	DrawStageName();
	//DrawDetailedDescription();
	VECTOR gateToPlayer = VSub(stage->GetGatePos(), player->GetPos());
	gateToPlayer.y = 0.0f;
	float vecSize = VSize(gateToPlayer);
	if (vecSize < 60.0f)
	{
		//DrawExtendGraph(BOSS_UI_DRAW_RECT.lx, BOSS_UI_DRAW_RECT.ly, BOSS_UI_DRAW_RECT.rx, BOSS_UI_DRAW_RECT.ry, titleData[static_cast<int>(TitleData::BACKGROUND)], TRUE);
		DrawBox(BOSS_UI_DRAW_RECT.lx, BOSS_UI_DRAW_RECT.ly, BOSS_UI_DRAW_RECT.rx, BOSS_UI_DRAW_RECT.ry, GetColor(0,0,0),TRUE);
		DrawStringToHandle(TEXT_POS.x, TEXT_POS.y + 700, "ゲートをくぐる", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
		DrawExtendGraph(BUTTON_POS.lx + 20, BUTTON_POS.ly + 700, BUTTON_POS.rx + 20, BUTTON_POS.ry + 700, titleData[static_cast<int>(TitleData::A_BUTTON)], TRUE);
		int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		//Bが押されていたら攻撃
		if (input & PAD_INPUT_1)
		{
			isChangeScene = true;
		}
	}
}
/// <summary>
/// タイトル描画
/// </summary>
void Title::DrawTitle()
{
	if (!isDrawTitleEnd)
	{
		if (!isDrawTitleFinish)
		{
			//タイトルロゴの描画
			DrawExtendGraph(TITLE_LOGO_POS.lx, TITLE_LOGO_POS.ly, TITLE_LOGO_POS.rx, TITLE_LOGO_POS.ry, titleData[static_cast<int>(TitleData::LOGO)], TRUE);
			//スタートアイコン（PRESS A BUTTON）の描画
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, startIconAlpha);
			DrawStringToHandle(START_ICON_POS.x, START_ICON_POS.y, "PRESS A BUTTON", FONT_COLOR, fontData[static_cast<int>(FontType::PLAYER)]);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA_VALUE);
			int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
			//Bが押されていたら攻撃
			if (input & PAD_INPUT_1)
			{
				isDrawTitleFinish = true;
				addAlphaValue = -ADD_ALPHA_VALUE;
			}
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, titleAlpha);
			DrawExtendGraph(TITLE_LOGO_POS.lx, TITLE_LOGO_POS.ly, TITLE_LOGO_POS.rx, TITLE_LOGO_POS.ry, titleData[static_cast<int>(TitleData::LOGO)], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA_VALUE);
			if (titleAlpha <= MIN_ALPHA_VALUE)
			{
				isDrawTitleEnd = true;
				isDrawStageName = true;
				addAlphaValue = ADD_ALPHA_VALUE;
			}
		}
	}


}

void Title::DrawStageName()
{
	if (isDrawStageName)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, stageNameAlpha);
		DrawStringToHandle(TUTORIAL_LOGO_POS.x, TUTORIAL_LOGO_POS.y, "チュートリアル", FONT_COLOR, fontData[static_cast<int>(FontType::LOGO)], TRUE);
		DrawLine(TUTORIAL_LOGO_LINE_POS.lx, TUTORIAL_LOGO_LINE_POS.ly, TUTORIAL_LOGO_LINE_POS.rx, TUTORIAL_LOGO_LINE_POS.ry,FONT_COLOR,15);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA_VALUE);
		if (stageNameAlpha < MIN_ALPHA_VALUE)
		{
			isDrawStageName = false;
		}
	}
}
void Title::DrawDetailedDescription()
{
	if (isDrawText && isDescription)
	{
		int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		//Bが押されていたら攻撃
		if (input & PAD_INPUT_2)
		{
			isDescription = false;
		}
	}
}
void Title::DrawTutorialText()
{
	//文字用の背景画像の描画
	DrawBox(BACKGROUND_POS_FOR_DESCRIPTION.lx, BACKGROUND_POS_FOR_DESCRIPTION.ly, BACKGROUND_POS_FOR_DESCRIPTION.rx, BACKGROUND_POS_FOR_DESCRIPTION.ry, GetColor(0, 0, 0), TRUE);
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x, TEXT_POS_FOR_DESCRIPTION.y, "敵を倒すと、経験値を取得できます。\nレベルが上がると、ステータスポイントが\n付与されます。", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT_2)]);
	//文字用の背景画像の描画
	DrawExtendGraph(1390, 150, 1500, 230, strongUI, TRUE);
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x + 70, TEXT_POS_FOR_DESCRIPTION.y + 100, "このマークがついている敵は,\nあなたよりもレベルが上の敵です。\nステータスを強化して挑みましょう。", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT_2)]);
	//文字用の背景画像の描画
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x, TEXT_POS_FOR_DESCRIPTION.y + 200, "たき火で休むと、体力を回復することが\nできます。\nまたレベルアップメニューを選択すると、\nステータスポイントを消費してステータス\nを強化できます。", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT_2)]);
	//文字用の背景画像の描画
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x, TEXT_POS_FOR_DESCRIPTION.y + 350, "レベルが一定以上上がると、ゲートが出現\nします。\nゲートをくぐるとボス戦が始まるので、\nステータスを強化して挑みましょう。", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT_2)]);


	if (!isDrawStageName && isDrawTitleEnd)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, textAlpha);	
		//テキスト文字の描画
		switch (tutorialProgress)
		{
		case static_cast<int>(TutorialProgress::MOVE):
			//文字用の背景画像の描画
			DrawBox(BACKGROUND_POS_FOR_TEXT.lx, BACKGROUND_POS_FOR_TEXT.ly, BACKGROUND_POS_FOR_TEXT.rx, BACKGROUND_POS_FOR_TEXT.ry, GetColor(0, 0, 0), TRUE);
			DrawStringToHandle(TEXT_POS.x, TEXT_POS.y, "移動", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
			DrawExtendGraph(BUTTON_POS.lx, BUTTON_POS.ly, BUTTON_POS.rx, BUTTON_POS.ry, titleData[static_cast<int>(TitleData::L_STICK)], TRUE);
			//プレイヤーが移動したら次に行く
			if (isDrawText && player->GetIsMove())
			{
				isChange = true;
			}
			break;
		case static_cast<int>(TutorialProgress::CAMERA):
			//文字用の背景画像の描画
			DrawBox(BACKGROUND_POS_FOR_TEXT.lx, BACKGROUND_POS_FOR_TEXT.ly, BACKGROUND_POS_FOR_TEXT.rx, BACKGROUND_POS_FOR_TEXT.ry, GetColor(0, 0, 0), TRUE);
			DrawStringToHandle(TEXT_POS.x, TEXT_POS.y, "カメラ操作", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
			DrawExtendGraph(BUTTON_POS.lx, BUTTON_POS.ly, BUTTON_POS.rx, BUTTON_POS.ry, titleData[static_cast<int>(TitleData::R_STICK)], TRUE);
			//カメラのアングルが変わっていたら次に行く
			if (isDrawText && camera->GetAngleX() != 0.0f)
			{
				isChange = true;
			}
			break;
		case static_cast<int>(TutorialProgress::ATTACK):
			//文字用の背景画像の描画
			DrawBox(BACKGROUND_POS_FOR_TEXT.lx, BACKGROUND_POS_FOR_TEXT.ly, BACKGROUND_POS_FOR_TEXT.rx, BACKGROUND_POS_FOR_TEXT.ry, GetColor(0, 0, 0), TRUE);
			DrawStringToHandle(TEXT_POS.x, TEXT_POS.y, "攻撃", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
			DrawExtendGraph(BUTTON_POS.lx, BUTTON_POS.ly, BUTTON_POS.rx, BUTTON_POS.ry, titleData[static_cast<int>(TitleData::X_BUTTON)], TRUE);
			//プレイヤーが攻撃したら次に行く
			if (isDrawText && player->GetIsAttack())
			{
				isChange = true;
			}
			break;
		case static_cast<int>(TutorialProgress::DESTROY_ENEMY_1):
			//文字用の背景画像の描画
			DrawBox(BACKGROUND_POS_FOR_TEXT.lx, BACKGROUND_POS_FOR_TEXT.ly, BACKGROUND_POS_FOR_TEXT.rx, BACKGROUND_POS_FOR_TEXT.ry, GetColor(0, 0, 0), TRUE);
			DrawStringToHandle(TEXT_POS.x, TEXT_POS.y, "敵を倒す", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
			//敵が死亡したら次に行く
			if (isDrawText && enemy->GetIsDeath())
			{
				isChange = true;
			}
			break;
		case static_cast<int>(TutorialProgress::CAMPFIRE_2):
			//文字用の背景画像の描画
			DrawBox(BACKGROUND_POS_FOR_TEXT.lx, BACKGROUND_POS_FOR_TEXT.ly, BACKGROUND_POS_FOR_TEXT.rx, BACKGROUND_POS_FOR_TEXT.ry, GetColor(0, 0, 0), TRUE);
			DrawStringToHandle(TEXT_POS.x, TEXT_POS.y, "かがり火で休む", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
			//攻撃力がアップしていたら次に行く
			if (isDrawText && player->GetIsShowStatusMenu())
			{
				isChange = true;
			}
			break;
		case static_cast<int>(TutorialProgress::STATUS_UP):
				//文字用の背景画像の描画
				DrawBox(BACKGROUND_POS_FOR_TEXT.lx + 20, BACKGROUND_POS_FOR_TEXT.ly + 700, BACKGROUND_POS_FOR_TEXT.rx + 20, BACKGROUND_POS_FOR_TEXT.ry + 700, GetColor(0, 0, 0), TRUE);
				//敵が死亡していたら次に行く
				DrawStringToHandle(TEXT_POS.x + 120, TEXT_POS.y + 700, "攻撃力を強化してください。", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
				if (isDrawText && !enemy->GetIsDamage())
				{
					isChange = true;
				}
			break;
		case static_cast<int>(TutorialProgress::DESTROY_ENEMY_2):
				//文字用の背景画像の描画
				DrawBox(BACKGROUND_POS_FOR_TEXT.lx, BACKGROUND_POS_FOR_TEXT.ly, BACKGROUND_POS_FOR_TEXT.rx, BACKGROUND_POS_FOR_TEXT.ry, GetColor(0, 0, 0), TRUE);
				//敵が死亡していたら次に行く
				DrawStringToHandle(TEXT_POS.x, TEXT_POS.y, "敵を倒す。", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
				if (isDrawText&& enemy->GetIsDeath())
				{
					isChange = true;
					isDescription = true;
				}
			break;
		case static_cast<int>(TutorialProgress::GATE_2):
			//文字用の背景画像の描画
			DrawBox(BACKGROUND_POS_FOR_TEXT.lx, BACKGROUND_POS_FOR_TEXT.ly, BACKGROUND_POS_FOR_TEXT.rx, BACKGROUND_POS_FOR_TEXT.ry, GetColor(0, 0, 0), TRUE);
			DrawStringToHandle(TEXT_POS.x, TEXT_POS.y, "ゲートをくぐる。", FONT_COLOR, fontData[static_cast<int>(FontType::TEXT)]);
			if (isDrawText && stage->GetIsShowGate())
			{
				isChange = true;
			}
			break;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA_VALUE);
	}
}
/// <summary>
/// フラグを変更する
/// </summary>
void Title::FragChanger()
{
	if (!isDrawStageName && isDrawTitleEnd)
	{
		//最初に徐々に描画される
		if (!isDrawText)
		{
			//アルファ値を増加させる
			textAlpha += ADD_ALPHA_VALUE;
			//もし最大値に達していたら最大値を超えないようにする
			if (textAlpha >= MAX_ALPHA_VALUE)
			{
				textAlpha = MAX_ALPHA_VALUE;
				//アルファ値が最大になったらisDrawTextフラグを立てる
				isDrawText = true;
			}
		}
		//フラグが立っているときに指定のアクションがされたら徐々に描画をけす
		if (isChange)
		{
			textAlpha -= ADD_ALPHA_VALUE;
			//もしアルファ値が最小値を下回ったら最小値に設定する
			if (textAlpha < MIN_ALPHA_VALUE)
			{
				textAlpha = MIN_ALPHA_VALUE;
				//フラグを下す
				isDrawText = false;
				//チュートリアルの進行度を1進める
				tutorialProgress++;
				isChange = false;
			}
		}
	}
	//時間でテキストの表示を変更するための処理
	if (isDescription)
	{
		progressFrameCount++;
		if (progressFrameCount > 240)
		{
			progressFrameCount = 0;
			isProgress[tutorialProgress] = true;
			isDescription = false;
		}
	}
	if (tutorialProgress == static_cast<int>(TutorialProgress::GATE_2))
	{
		stage->OnIsShowGate();
	}
}
/// <summary>
/// 移動量補正
/// </summary>
void Title::FixMoveVec()
{
	VECTOR fixVec = collision->CapsuleToCapsuleCollision(player->GetMoveVec(), player->GetPos(), enemy->GetPos(), player->GetCapsuleInfo().radius, enemy->GetRadius());
	player->FixMoveVec(fixVec);
}
/// <summary>
/// ダメージ処理
/// </summary>
void Title::OnDamage()
{
	if (player->GetIsAttack() && !enemy->GetIsDamage() && tutorialProgress == static_cast<int>(TutorialProgress::DESTROY_ENEMY_1) ||
		player->GetIsAttack() && !enemy->GetIsDamage() && tutorialProgress == static_cast<int>(TutorialProgress::DESTROY_ENEMY_2))
	{
		//当たり判定チェック
		bool isHitEnemy = collision->OnDamage(false, enemy->GetIsDeath(), enemy->GetCapsuleInfo(), player->GetSphereInfo());
		//もし攻撃が当たっていたら
		if (isHitEnemy)
		{
			float exp = enemy->CalcHP( player->GetAtk(), player->GetPos());
			if (exp > 0)
			{
				player->CalcExp(exp);
				enemy->InitExpToGive();
			}
		}
	}
}