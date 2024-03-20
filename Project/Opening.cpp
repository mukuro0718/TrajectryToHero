#include"Opening.h"
#include"Load.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
Opening::Opening()
{
	//���[�h�N���X�̃C���X�^���X���擾
	auto& load = Load::GetInstance();
	//�摜�̃��[�h
	load.GetOpeningData(&image);
	//�ϐ��̏�����
	Init();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Opening::~Opening()
{
	//������Delete�����ꍇ�A������x���̃N���X��ǂ񂾂Ƃ��ɉ摜���`�悳��Ȃ��Ȃ�
	//�����Ŏ����Ă���̂̓��[�h�����n���h���Ȃ̂łO�ŏ��������A
	//���[�h�N���X��Delete���ׂ���������Ȃ�
	DeleteGraph(image[static_cast<int>(ImageType::SE_SITE)]);
	DeleteGraph(image[static_cast<int>(ImageType::MODEL_SITE)]);
	DeleteGraph(image[static_cast<int>(ImageType::MUSIC_SITE)]);
	DeleteGraph(image[static_cast<int>(ImageType::LANGUAGE)]);
	image.clear();
}
/// <summary>
/// ������
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
/// �X�V
/// </summary>
const void Opening::Update()
{
	//�J�E���g���K�v�Ȋe�ϐ��̃J�E���g�������s��
	CountProcess();
	//�I�[�v�j���O�̏I��
	EndOpening();
}
/// <summary>
/// �`��
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
/// �J�E���g����
/// </summary>
const void Opening::CountProcess()
{
	//�����x�̉��Z���Z
	if (isChangeAlpha)
	{
		alpha -= ALPHA_COUNT;
	}
	else
	{
		alpha += ALPHA_COUNT;
	}

	//�A���t�@�l��255�ȏ�̏ꍇ�^�C�}�[�{
	if (alpha >= MAX_ALPHA) 
	{ 
		changeTimer++;
	}
	/*HACK:�A���t�@�l���ő�̏�ԂŃ^�C�}�[���ԕ��摜�̕`�������
	�I�������A���t�@�l�����������ĂO�ɂȂ����玟�̉摜�ɐ؂�ւ���*/
	//�����^�C�}�[���ڕW���Ԉȏ�ɂȂ�����A���t�@�ύX�t���O�𗧂Ă�
	if (changeTimer >= LAST_TIMER)
	{ 
		isChangeAlpha = true;
		changeTimer = FIRST_TIMER; 
	}
	//�u�����h�������I������玟�̉摜�ɐ؂�ւ��A�A���t�@�l�ύX�t���O��OFF�ɂ���
	if (alpha <= MIN_ALPHA) 
	{ 
		nowShowImageType++;
		isChangeAlpha = false;
	}
	//�����x�̍ő�ŏ�
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
/// �I�[�v�j���O�I��
/// </summary>
const void Opening::EndOpening()
{
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//�X�y�[�X�����͂��ꂽ��G���h�t���OON
	if (input & PAD_INPUT_2 || CheckHitKey(KEY_INPUT_RETURN))
	{ 
		isEndOpening = true;
	}
	//�Ō�̉摜���\�����ꂽ��G���h�t���OON
	if (nowShowImageType >= static_cast<int>(ImageType::LANGUAGE))
	{ 
		isEndOpening = true;
	}
}