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
#include    "../include.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�^�C�g������`���[�g���A���ɔ�΂�
//------------------------------------------------------------------------------------------------------------------------------------------------------
void tutorial_skep_mane_exec(TASK *ap)
{
	SINT32 i, index;
    index = 0;
    if( SOZ_Inkey_TRG( DIK_Z ) != 0 )
		    index++;
    for( i = 0; i < 3; i++ )
        if( SOZ_Mouse_Button( i ) == 1 )
            index++;

    if( index != 0 )
    {
        game_type = TUTORIAL;
        TASK_all_init();
        return;
    }
}

void tutorial_skep_mane_start( void )
{
	TASK *ap;
	ap = TASK_start( tutorial_skep_mane_exec, MANE_GROUP, "�`���[�g���A���ɔ�΂�" );
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�^�C�g������Q�[���ɍs�����߂̐��������o��
//------------------------------------------------------------------------------------------------------------------------------------------------------
void game_start_purpose_exec( TASK *ap )
{
	alpha_chenge( ap, 0xff, 0xa0 );														//�����x���ێ���
}

void game_start_child_exec( TASK *ap )
{
	ap->base_color[0][0] = ap->parent->base_color[0][0];								//�e�̓����x����������
}

void game_start_purpose_start( void )
{
	TASK *ap, *actp;
	ap = TASK_start_GRP( game_start_purpose_exec, UI_GROUP, TEX_UI_FONT, title_proposal_rect, 0, "�U��������I�u�W�F�N�g�̐���" );
	ap->pos[ X ] = WINDOW_WIDTH_HALF;													//
	ap->pos[ Y ] = WINDOW_HEIGHT - 300.0f;												//
	ap->pri = UI_PRI * WP;																//�`��D��x
	ap->scale[X] = 1.5f;
	ap->scale[Y] = ap->scale[X];

	actp = TASK_start_GRP( game_start_purpose_exec, UI_GROUP, TEX_UI_FONT, title_proposal_rect, 1, "�Q�[���X�^�[�g�̕���" );
	actp->pos[ X ] = WINDOW_WIDTH_HALF;													//
	actp->pos[ Y ] = ap->pos[Y] + 100.0f;												//�U��������I�u�W�F�N�g�̐����̉��ɗ��邭�炢�̍����ɕς���
	actp->scale[X] = ap->scale[X];
	actp->scale[Y] = actp->scale[X];
	actp->parent   = ap;
	ap->child[ 0 ] = actp;
	actp->pri = UI_PRI * WP;															//�`��D��x
}


