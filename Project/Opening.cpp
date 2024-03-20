#include"Opening.h"
#include"Load.h"
/// <summary>
/// コンストラクタ
/// </summary>
Opening::Opening()
{
	//ロードクラスのインスタンスを取得
	auto& load = Load::GetInstance();
	//画像のロード
	load.GetOpeningData(&image);
	//変数の初期化
	Init();
}
/// <summary>
/// デストラクタ
/// </summary>
Opening::~Opening()
{
	//ここでDeleteした場合、もう一度このクラスを読んだときに画像が描画されなくなる
	//ここで持っているのはロードしたハンドルなので０で初期化し、
	//ロードクラスでDeleteすべきかもしれない
	DeleteGraph(image[static_cast<int>(ImageType::SE_SITE)]);
	DeleteGraph(image[static_cast<int>(ImageType::MODEL_SITE)]);
	DeleteGraph(image[static_cast<int>(ImageType::MUSIC_SITE)]);
	DeleteGraph(image[static_cast<int>(ImageType::LANGUAGE)]);
	image.clear();
}
/// <summary>
/// 初期化
/// </summary>
const void Opening::Init()
{
	changeTimer   = FIRST_TIMER;
	alpha		  = MIN_ALPHA;
	isEndOpening  = false;
	isChangeAlpha = false;
	nowShowImageType = static_cast<int>(ImageType::SE_SITE);
}
/// <summary>
/// 更新
/// </summary>
const void Opening::Update()
{
	//カウントが必要な各変数のカウント処理を行う
	CountProcess();
	//オープニングの終了
	EndOpening();
}
/// <summary>
/// 描画
/// </summary>
const void Opening::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	if (nowShowImageType == static_cast<int>(ImageType::SE_SITE))
	{
		DrawGraph(IMAGE_POS.x, IMAGE_POS.y, image[static_cast<int>(ImageType::SE_SITE)], TRUE);
	}
	if (nowShowImageType == static_cast<int>(ImageType::MODEL_SITE))
	{ 
		DrawGraph(IMAGE_POS.x, IMAGE_POS.y, image[static_cast<int>(ImageType::MODEL_SITE)], TRUE);
	}
	if (nowShowImageType == static_cast<int>(ImageType::MUSIC_SITE))
	{ 
		DrawGraph(IMAGE_POS.x, IMAGE_POS.y, image[static_cast<int>(ImageType::MUSIC_SITE)], TRUE);
	}
	if (nowShowImageType == static_cast<int>(ImageType::LANGUAGE))
	{
		DrawGraph(IMAGE_POS.x, IMAGE_POS.y, image[static_cast<int>(ImageType::LANGUAGE)], TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, MAX_ALPHA);
}
/// <summary>
/// カウント処理
/// </summary>
const void Opening::CountProcess()
{
	//透明度の加算減算
	if (isChangeAlpha)
	{
		alpha -= ALPHA_COUNT;
	}
	else
	{
		alpha += ALPHA_COUNT;
	}

	//アルファ値が255以上の場合タイマー＋
	if (alpha >= MAX_ALPHA) 
	{ 
		changeTimer++;
	}
	/*HACK:アルファ値が最大の状態でタイマー時間分画像の描画をする
	終わったらアルファ値を減少させて０になったら次の画像に切り替える*/
	//もしタイマーが目標時間以上になったらアルファ変更フラグを立てる
	if (changeTimer >= LAST_TIMER)
	{ 
		isChangeAlpha = true;
		changeTimer = FIRST_TIMER; 
	}
	//ブレンド処理が終わったら次の画像に切り替え、アルファ値変更フラグをOFFにする
	if (alpha <= MIN_ALPHA) 
	{ 
		nowShowImageType++;
		isChangeAlpha = false;
	}
	//透明度の最大最小
	if (alpha >= MAX_ALPHA)
	{ 
		alpha = MAX_ALPHA;
	}
	if (alpha <= MIN_ALPHA) 
	{ 
		alpha = MIN_ALPHA;
	}
}
/// <summary>
/// オープニング終了
/// </summary>
const void Opening::EndOpening()
{
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//スペースが入力されたらエンドフラグON
	if (input & PAD_INPUT_2 || CheckHitKey(KEY_INPUT_RETURN))
	{ 
		isEndOpening = true;
	}
	//最後の画像が表示されたらエンドフラグON
	if (nowShowImageType >= static_cast<int>(ImageType::LANGUAGE))
	{ 
		isEndOpening = true;
	}
}