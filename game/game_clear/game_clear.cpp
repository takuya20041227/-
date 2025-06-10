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



//---------------------------------------------------------------------------------
//������ƃr������
//---------------------------------------------------------------------------------
void hit_mobu_check( TASK *ap )
{
	TASK *actp;
	for( actp = ap_start; actp != NULL; actp = actp->next )			//�^�X�N�̑S����
		if( actp->task_group == OBJECT_GROUP )						//�I�u�W�F�N�g�Ȃ�
			if( kawa_3d_hit_check( ap, actp ) != 0 )				//�������Ă�����
				actp->HP = 0;										//HP��0�ɂ���
}

//---------------------------------------------------------------------------------
//�r���̔j��𐬌��������Ƃ��ɒ��Ԃ�UFO�����ł���
//---------------------------------------------------------------------------------
void mobu_ufo_exec( TASK *ap )
{
	ap->pos[Z] += ap->vec[Z];
	ap->vec[Z] += ap->acc[Z];
	if( ap->pos[ Z ] > 45000.0f )
	{
		TASK_end( ap );
		return;
	}
	task_id_checge( ap, 0 );										//������J�����O
	hit_mobu_check( ap );											//���������I�u�W�F�N�g��j�󂷂�
}

void mobu_ufo_start( FLOAT x, FLOAT y )
{
	TASK *ap;
	ap = TASK_start_MODEL( mobu_ufo_exec, NO_GROUP, MODEL_JIKI, TEX_JIKI, "���u��UFO" );
	ap->grp_mode =  TEST_ZBUFFER | WRITE_ZBUFFER  | NO_SHADOW | USE_LIGHTING | USE_SPECULAR;
	ap->pos[X] = x;
	ap->pos[Y] = y;
	ap->pos[Z] = 1000.0f;
	ap->scale[X] = 5.0f;
	ap->scale[Y] = ap->scale[X];
	ap->scale[Z] = ap->scale[Y];

	ap->vec[Z] = F_Rand2( 100.0f,  120.0f );
	ap->acc[Z] = F_Rand2( 1.0f, 2.0f );
	ap->sphire = 64.0f;
}



//---------------------------------------------------------------------------------
//���Ԃ�UFO�̃W�F�l���[�^�[
//---------------------------------------------------------------------------------
void mobu_ufo_generator_exec( TASK *ap )
{
	SINT32 i;
	FLOAT x, y;
	ap->TIMER++;
	if( ap->TIMER > 9 )
	{
		for( i = 0; i < Rand2( 2, 6 ); i++ )
		{
			x = jiki->pos[ X ] + F_Rand2( -10000, 10000 );	//���@�̋߂�����o��悤�ɂ���
			y = camera_y[0] + F_Rand2( -2500, 3000 );		//�㉺�Ƀ����_���ł����
			if( y < GROUND )								//�n�ʂ�艺�ɍs������
				y = GROUND;									//�n�ʂɌŒ肷��

			mobu_ufo_start( x, y );							//UFO���o��������
		}
		ap->TIMER = RESET;								//������
	}
}

void mobu_ufo_generator_start( void )
{
	TASK *ap;
	ap = TASK_start( mobu_ufo_generator_exec, MANE_GROUP, "�W�F�l���[�^�[" );
	ap->TIMER = TIME_M;
}


//---------------------------------------------------------------------------------
//�Q�[���N���A�̕�����\������
//---------------------------------------------------------------------------------
void clear_exec( TASK *ap )
{
	
}

void clear_start( void )
{
	TASK *ap;
	ap = TASK_start_GRP( clear_exec, UI_GROUP, TEX_UI_FONT, clear_rect, 0, "�Q�[���N���A" );
	ap->pos[X] = WINDOW_WIDTH_HALF;								//�^��
	ap->pos[Y] = WINDOW_HEIGHT_HALF;							//�^��
}		


