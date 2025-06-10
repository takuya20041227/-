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

#define	BAR_SCALE		1.0f

//------------------------------------------------------------------------------------------------------------------------------------------------------
//�r����HP��\��
//------------------------------------------------------------------------------------------------------------------------------------------------------
void hp_bar_exec( TASK *ap )
{
	FLOAT hp_scale;
	SINT32 hp;										//HP�̍������m�F����
	hp = MAIN_BILL_HP_MAX - main_bill_hp;			//HP�̃}�b�N�X�l�ƌ��݂�HP�̍���������
	hp_scale = hp * ap->fwork1[X];					//���ɏ�Z���ăT�C�Y�����炷
	ap->scale[Y] = BAR_SCALE  - hp_scale;				//HP�ɍ��킹�ăT�C�Y���ϓ�
	if( main_bill_hp <= 0 )							//HP��0�ɂȂ�����
		ap->base_color[0][0] = 0x00;				//�����ɂ���
}

void main_bill_hp_exec( TASK *ap )
{

}

void main_bill_hp_start( void )
{
	TASK *ap, *actp;
	ap = TASK_start_GRP( main_bill_hp_exec, UI_GROUP, TEX_OBJECT_ICON, main_bill_rect, 0, "���C���r���̃A�C�R��" );
	ap->pos[X] = 140.0f;
	ap->pos[Y] = WINDOW_HEIGHT_HALF;
	ap->pri = UI_PRI * WP;
	ap->scale[X] = 2.0f;
	ap->scale[Y] = ap->scale[X];

	ap = TASK_start_GRP( main_bill_hp_exec, UI_GROUP, TEX_OBJECT_ICON, hp_bar_rect, 0, "���C���r����HP�\��" );
	ap->pos[X] = 20;
	ap->pos[Y] = WINDOW_HEIGHT_HALF + 42.0f;
	ap->scale[Y] = BAR_SCALE + 0.02f;									//���o�[��Z������
	ap->scale[X] = 1.3f;									//������������
	ap->ang[Z] = 0x4000;									//���ɂ���
	ap->base_color[ 0 ][ 1 ] = 0x0;							//���ɂ��邽�߂ɐF�𔲂�
	ap->base_color[ 0 ][ 2 ] = 0x0;							//���ɂ��邽�߂ɐF�𔲂�
	ap->base_color[ 0 ][ 3 ] = 0x0;							//���ɂ��邽�߂ɐF�𔲂�
	ap->pri = UI_PRI * WP;									//�`��D��x

	actp = TASK_start_GRP( hp_bar_exec, UI_GROUP, TEX_OBJECT_ICON, hp_bar_rect, 0, "���C���r����HP�\��" );
	actp->pos[X] = ap->pos[X] + 2;							//
	actp->pos[Y] = ap->pos[Y];								//
	actp->scale[Y] = BAR_SCALE;								//���o�[��Z������
	actp->ang[Z] = 0x4000;									//���ɂ���
	actp->fwork1[X] = BAR_SCALE / ( FLOAT )MAIN_BILL_HP_MAX;//HP��1����Ƃǂ��܂ŃT�C�Y�������邩�v�Z����
	actp->pri = ap->pri + 1;

}


//--------------------------------------------------------------------------------------------------------------------------
//�Q�[���N���A�̏�����\������
//--------------------------------------------------------------------------------------------------------------------------
void show_game_goal_exec( TASK *ap )
{
	alpha_chenge( ap, 0xff, 0xa0 );
	if( ap->TIMER > TIME_S * 10 )
	{
		TASK_end( ap );
		return;
	}
}

void show_game_goal_start( void )
{
	TASK *ap;
	ap = TASK_start_GRP( show_game_goal_exec, UI_GROUP, TEX_UI_FONT, game_goal_rect, 0, "�Q�[���̃N���A����" );
	ap->pos[X] = WINDOW_WIDTH_HALF;						//��
	ap->pos[Y] = WINDOW_HEIGHT_HALF +60.0f;			//�c
	ap->scale[X] = 1.5f;
	ap->scale[Y] = ap->scale[X];
	ap->pri = UI_PRI * WP;								//�`��D��x

	ap = TASK_start_GRP( show_game_goal_exec, UI_GROUP, TEX_UI_FONT, game_goal_rect, 1, "�Q�[���̃N���A����" );
	ap->pos[X] = WINDOW_WIDTH_HALF;						//��
	ap->pos[Y] = WINDOW_HEIGHT_HALF - 40.0f;			//�c
	ap->scale[X] = 1.5f;
	ap->scale[Y] = ap->scale[X];
	ap->pri = UI_PRI * WP;								//�`��D��x
}


//--------------------------------------------------------------------------------------------------------------------------
//���Ԃ��v������
//--------------------------------------------------------------------------------------------------------------------------
void timer_drawfunc( TASK *ap )
{
	TASK spr;
	SINT8 str[4];												

	TASK_init_member_pointer( &spr );						//�܂��̓^�X�N�������̏�����
	sprintf( str, "%2d", ap->work1[Y] );		 			//�b���������ɕۑ�����
	spr.uv_rect = number_rect;								//�����̋�`���i�[
	spr.tex_no  = TEX_UI_FONT;								//����������e�N�X�`���[���i�[
	
	spr.pos[X] = ap->pos[X] - 96.0f;						//���W������
	spr.pos[Y] = ap->pos[Y] + 1.0f;								//���W������

	spr.scale[X] = 2.0f;
	spr.scale[Y] = spr.scale[X];

	spr.base_color[0][2] = ap->base_color[0][2];			//�x�[�X�J���[�̗΂�
	spr.base_color[0][3] = ap->base_color[0][2];			//
	spr.pri = ap->pri;

//���̕`��
	spr.anime_no = ap->work1[X];						 	//����\��
	SOZ_sprite_draw( &spr );								//�����ŕ`�悷��

	spr.pos[X] += 96.0f  * spr.scale[X];								
//�b�̕`��
	if( str[ 0 ] >= '0' && str[ 0 ] <= '9' )			//
	{
		spr.anime_no = str[ 0 ] - '0'; 					//�������0���當�����0�������Ɛ�����0�ɂȂ�
		if( spr.anime_no == 6 )
			spr.anime_no = 0;
		SOZ_sprite_draw( &spr );						//�����ŕ`��
	}
	else
	{
		spr.anime_no = 0;		//�v�Z���ʂ�0
		SOZ_sprite_draw( &spr );			
	}

	spr.pos[X] += 64.0f * spr.scale[X];
	if( str[ 1 ] >= '0' && str[ 1 ] <= '9' )			//
	{
		spr.anime_no = str[ 1 ] - '0'; 					//�������0���當�����0�������Ɛ�����0�ɂȂ�
		SOZ_sprite_draw( &spr );						//�����ŕ`��
	}
	

}

void timer_exec( TASK *ap )
{
#if DEBUG
	if( SOZ_Inkey_TRG(DIK_I) != 0 )
	{
		ap->work1[Y] = 0;											//�b��0��
		ap->work1[X] = 0;											//����0��
	}
#endif

	if( game_type == 101 )											//�Q�[�����Ȃ�
	{
		SINT32 color_gb_box[ 2 ] = {0xff, 0x60};					//�΂Ɛ̒l
		ap->TIMER++;												//�t���[�����v��
		if( ap->TIMER % TIME_S == 0 )								//������b�o������
			if( ap->work1[ Y ] > 0 )								//0���傫���Ȃ�
				ap->work1[ Y ]--;									//�b�������炷

		if( ap->work1[ X ] > 0 )									//����0������Ȃ����
		{
			if( ap->TIMER % TIME_M == 0 )							//�������ꕪ�o������
				ap->work1[ Y ] = 60;								//�b�������Z�b�g

			if( ap->work1[ Y ] == 59 && ap->TIMER % TIME_S == 0 )
				ap->work1[ X ]--;									//�������Z
		}

		if( ap->work1[ X ] <= 0 && ap->work1[ Y ] <= 30 )			//�c�莞�Ԃ�30�b�Ȃ�
		{
			if( ap->TIMER % ap->work2[ Z ] == 0 )					//����̃t���[���o��
				ap->work2[ Y ]++;									//���Z����

			if( ap->TIMER % (TIME_S * 7) == 0 )
				if( ap->work1[ Y ] > 0 )							//0�b�łȂ��Ȃ�
					ap->work2[ Z ] -= 2;									//�_�ł܂ł̎��Ԃ𑁂�����
		}

		if( ap->work1[ X ] <= 0 && ap->work1[ Y ] <= 0 )			//0��0�b�ɂȂ�����
		{
			game_type = 120;										//�Q�[���I�[�o�[�Ɉړ�
			game_over_flag = 1;										//�t���O��
			TASK_end_group( BREAK_OBJECT_GROUP );					//�I�u�W�F�N�g������
			TASK_end( ap );
			return;
		}

		ap->work2[ Y ] %= 2;											//0��1�����݂ɍs���悤�ɂ���

		ap->base_color[ 0 ][ 2 ] = color_gb_box[ ap->work2[ Y ] ];		//�ԂƔ������݂ɍs��
		ap->base_color[ 0 ][ 3 ] = color_gb_box[ ap->work2[ Y ] ];		//�ԂƔ������݂ɍs��
	}
}

void timer_start( void )
{
	TASK *ap;
	ap = TASK_start_DRAWFUNC( timer_exec, timer_drawfunc, UI_GROUP, "�Q�[���̎��Ԃ��v��" );
	ap->pos[X] = WINDOW_WIDTH_HALF - 92.0f;
	ap->pos[Y] = 72.0f;
	ap->work1[X] = 3;										//��
	ap->work1[Y] = 60;										//�b
	ap->work2[Z] = 15;
	ap->pri = UI_PRI;
}
