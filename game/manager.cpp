//------------------------------------------------------------------------------------------------------------------------------------------------------
//                systemOZ Ver3
//			�Q�[�����C���v���O����
//						programed by TEAM_TAKUYA
//------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef WINDOWS_PC
#include    "../../../libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/town_break/src/game/game_include.h"
#include    "include.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�L�[����������^�C�g���ɖ߂�
//------------------------------------------------------------------------------------------------------------------------------------------------------
void title_return_exce( TASK *ap )
{
	SINT32 i;
	bool flag;										//�����������ꂽ��0�ȊO�ɂȂ�
	flag = 0;										//������

	if( SOZ_Inkey_TRG( DIK_Z ) != 0 )				//�L�[��������Ă�����
		flag = TRUE;								//1�ɂȂ�

	for( i = 0; i < 3; i++ )						//�E�N���b�N, ���N���b�N, �z�C�[���̉������݂����m
		if( SOZ_Mouse_Button( i ) == 1 )			//�}�E�X�������ꂽ��
			flag = TRUE;							//1�ɂȂ�

	if( flag == TRUE )								//�t���O�������Ă�����
	{
		if( game_type == GAME_CLERE + 1 )						//�Q�[���^�C�v���N���A��ʂȂ�
		{
			if( score > hi_score )					//�X�R�A���n�C�X�R�A�𒴂��Ă�����
			{
				hi_score = score;					//�n�C�X�R�A���X�V
				select_and_page_write( "data/hi_score_data.bn", &hi_score );	//�n�C�X�R�A��ۑ�
			}
				game_type = TITLE_SCENE;								//�^�C�g���ɖ߂�
				TASK_all_init();							//�^�X�N��S�ď���
				return;										//
		}
		else if( game_type == GAME_OVER + 1 )
		{
			shut_down_start();
			TASK_end( ap );
			return;
		}
	}
}

void title_return_start( SINT32 delay )
{
	TASK *ap;
	ap = TASK_start( title_return_exce, MANE_GROUP, "�^�C�g���ɖ߂�" );
	ap->delay = delay;
}