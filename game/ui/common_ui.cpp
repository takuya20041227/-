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
//---------------�^�C�g���ł��Q�[����ʂł��g����UI�̃\�[�X�t�@�C��------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define	BASE_COLOR			0x70
#define	ICON_MAX			30

ICON_DATA icon_box[ ICON_MAX ];													//�͂�ł���I�u�W�F�N�g
SINT32 score = 0, hi_score = 0, icon_num = 0;


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�A�C�R���̃{�b�N�X��S�ď���������
//------------------------------------------------------------------------------------------------------------------------------------------------------
void icon_box_all_init( void )
{
	SINT32 i;
	for( i = 0; i < ICON_MAX; i++ )										//
	{
		icon_box[ i ].unique_id = 0;									//���j�[�NID�̒��g��0�ɂ���
		icon_box[ i ].id = 0;											//ID�̒��g��0�ɂ���
	}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�A�C�R���̃{�b�N�X��1����������
//------------------------------------------------------------------------------------------------------------------------------------------------------
void icon_box_init( TASK *ap )
{ 
	SINT32 i;
	for( i = 0; i < ICON_MAX; i++ )										//
	{
		if( icon_box[ i ].unique_id == ap->unique_id )					//�A�C�R���ƃ^�X�N���ꏏ�Ȃ�
			break;														//�������ꏊ��for���~�߂�
	}

	icon_box[ i ].unique_id = 0;										//���j�[�NID�̒��g��0�ɂ���
	icon_box[ i ].id = 0;												//ID�̒��g��0�ɂ���
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�A�C�R���̏�������
//------------------------------------------------------------------------------------------------------------------------------------------------------
void icon_param_get( TASK *ap )
{
	SINT32 i;

	for( i = 0; i < ICON_MAX; i++ )										//
		if( icon_box[ i ].unique_id == ap->unique_id )					//
			return;														//

	for( i = 0; i < ICON_MAX; i++ )										//
		if( icon_box[ i ].id == 0 )										//�A�C�R����0�Ȃ�
			break;														//�������ꏊ��for���~�߂�

	if( icon_box[ ICON_MAX - 1 ].unique_id != NULL )					//�z�񂪖��^���Ȃ�
		return;															//���g�����Ȃ��悤�ɂ���

	icon_box[ i ].unique_id = ap->unique_id;							//���j�[�NID�̒��g��0�ɂ���
	icon_box[ i ].id = ap->ID;											//ID�̒��g��0�ɂ���
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�A�C�R���̏d����h��
//------------------------------------------------------------------------------------------------------------------------------------------------------
void icon_box_check_exec( TASK *ap )
{
	SINT32 i, check, num;

	num = 0;

	check = 0;

	for( i = 0; i < ICON_MAX; i++ )
	{
		if( check > 4 )
		{
			check = 0;
			num++;
		}

		if( icon_box[ i ].id == NULL )
			break;

		check++;
	}

	icon_num = num;


	for( i = 0; i < ICON_MAX; i++ )												//��ՂƂȂ�z��̔ԍ�
		for( check = i; check < ICON_MAX; check++ )								//
			if( icon_box[ i ].unique_id == icon_box[ check ].unique_id )		//
			{
				icon_box[ check ].unique_id = 0;
				icon_box[ check ].id = 0; 
			}


	
}

void icon_box_check_start( void )
{
	TASK *ap;
	ap = TASK_start( icon_box_check_exec, UI_GROUP, "�A�C�R�����d�����Ă������" );
}



//------------------------------------------------------------------------------------------------------------------------------------------------------
//�A�C�R���̃^�X�N
//------------------------------------------------------------------------------------------------------------------------------------------------------
void icon_exec( TASK *ap )
{
	OBJECT_DATA * op;
	ICON_DATA *ip;
	ip = &icon_box[ ap->ID ];
	ap->task_id = TASK_GRP;												//��ɃO���t�B�b�N��`�悷��悤�ɂ���
	if( ip->id == 0 )													//���ʔԍ����Ȃ����
	{
		ap->task_id = TASK_PROGRAM;										//�`������Ȃ�
		return;															//�������������s���Ȃ�
	}

//�I�u�W�F�N�g��͂�ł����Ƃ��̃A�C�R��
	op = &object_data[ ip->id ];										//�I�u�W�F�N�g�̍\���̂ɃA�N�Z�X����
	ap->anime_no = op->icon;											//�A�C�R����\��
}

void frame_exec( TASK *ap )
{
	ICON_DATA *ip;
	ip = &icon_box[ ap->parent->ID ];
	ap->task_id = TASK_GRP;												//��ɃO���t�B�b�N��`�悷��悤�ɂ���
	if( ip->id == 0 )													//���ʔԍ����Ȃ����
	{
		ap->task_id = TASK_PROGRAM;										//�`������Ȃ�
		return;															//�������������s���Ȃ�
	}
}

void icon_start( FLOAT x, FLOAT y,SINT32 id )
{
	TASK *ap, *actp;
	ap = TASK_start_GRP( icon_exec, UI_GROUP, TEX_OBJECT_ICON, object_icon_rect, 0, "�A�C�R��" );
	ap->pos[X] = WINDOW_WIDTH - ( 72.0f * x );
	ap->pos[Y] = WINDOW_HEIGHT_QUARTER + ( 90.0f * y ) + 45.0f;
	ap->pri = UI_PRI * WP;
	ap->ID = id;														//���ʔԍ���ۑ�

	actp = TASK_start_GRP( frame_exec, UI_GROUP, TEX_OBJECT_ICON, object_icon_rect, 0, "�A�C�R��" );
	actp->pos[X] = ap->pos[X];
	actp->pos[Y] = ap->pos[Y];
	actp->pri = ap->pri - 1;
	ap->child[0] = actp;
	actp->parent = ap;

}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�A�C�R���̃^�X�N���o��������
//------------------------------------------------------------------------------------------------------------------------------------------------------
void icon_set( void )
{
	SINT32 i;
	FLOAT pos_x, pos_y;
	pos_y = ICON_MAX / 5;
	pos_x = 0;
	for( i = 0; i < ICON_MAX; i++ )
	{
		if( i % 5 == 0 )
		{
			pos_x = 1;
			pos_y--;												//�����łǂ�ǂ񍶂Ɉړ�������
		}

		icon_start( pos_x, pos_y, i );											//�A�C�R���̃^�X�N���o��
		pos_x++;
	}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//��̏�
//------------------------------------------------------------------------------------------------------------------------------------------------------
void hand_ui_exec( TASK *ap )
{
	if( catch_switch == 0 )												//���������͂�ł��Ȃ�������
		ap->anime_no = 0;												//��̂Ђ���L���Ă�
	else																//�Ȃɂ��͂�ł�����
		ap->anime_no = 1;												//�͂�ł�O���t�B�b�N

	ap->pos[Y] = WINDOW_HEIGHT_HALF + 86 - ( 90.0f * icon_num );
}

void hand_ui_start( void )
{
	TASK*ap;
	ap = TASK_start_GRP( hand_ui_exec, UI_GROUP, TEX_OBJECT_ICON, hand_ui_rect, 0, "��̏�" );
	ap->pos[X] = WINDOW_WIDTH - 200.0f;
	ap->pos[Y] = WINDOW_HEIGHT_HALF - 370.0f;
	ap->scale[X] = 2.0f;
	ap->scale[Y] = ap->scale[X];
	ap->pri = UI_PRI * WP;												//�`��̗D��x
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�}�E�X�̑��������UI
//------------------------------------------------------------------------------------------------------------------------------------------------------
void mouse_font_ui_exec( TASK *ap )										//�}�E�X�����̎��s��
{
	if( ap->work1[ X ] == CLICK_RIGHT )									//�E�N���b�N�̏ꍇ
	{
		ap->anime_no = 0;												//�ŏ�����0�ɂ��Ă���

		if( catch_switch != 0 )											//�����͂�ł�����
			ap->anime_no = 1;											//������ɕς���

		if( ap->anime_no == 1 )											//����������ɂȂ��Ă�����
		{
			ap->TIMER++;												//�t���[�����v��

			if( ap->TIMER % 15 == 0 )									//���t���[���Ɉ�x
			{
				if( ap->base_color[ 0 ][ 2 ] == 0xff )					//�����Ɨ΂��}�b�N�X�Ȃ�
				{
					ap->base_color[ 0 ][ 2 ] = BASE_COLOR;				//�����𗎂Ƃ�
					ap->base_color[ 0 ][ 3 ] = BASE_COLOR;				//�����΂𗎂Ƃ�
				}
				else													//�����Ɨ΂��}�b�N�X�ł͂Ȃ��Ȃ�
				{
					ap->base_color[0][2] = 0xff;						//�����ɖ߂�
					ap->base_color[0][3] = 0xff;						//�΂����ɖ߂�
				}
			}
		}
		else															//�t�H���g���u �͂� �v	�ɖ߂�����
		{
			ap->base_color[0][2] = 0xff;								//�����ɖ߂�
			ap->base_color[0][3] = 0xff;								//�΂����ɖ߂�
		}
	}
}


void mouse_ui_exec( TASK *ap )											//�}�E�X�̎��s��
{
	ap->shader_pass = SOZ_UNCLEAR;										//����������

	if( ap->work1[X] == CLICK_LEFT )									//���N���b�N�̏ꍇ
	{
		if( SOZ_Mouse_Button( 0 ) % BEAM_TIME == 0 && SOZ_Mouse_Button( 0 ) != 0 || SOZ_Mouse_Button( 0 ) == 1 )		//�E�N���b�N�����	
			ap->shader_pass = 101;										//�Ԃ����Ԃ�����
	}

	if( ap->work1[X] == CLICK_RIGHT  )									//�E�N���b�N�̏ꍇ
	{
		if( SOZ_Mouse_Button( 1 ) != 0 )								//��𔭎˂����Ƃ�
			ap->shader_pass = 101;										//�Ԃ����Ԃ�����
	}
}


void mouse_ui_start( void )
{
	TASK *ap, *actp;
	//------------�E�N���b�N�̐���----------//
	ap = TASK_start_GRP( mouse_ui_exec, UI_GROUP, TEX_OBJECT_ICON, mouse_ui_rect, 0, "���N���b�N�̐���" );
	ap->pos[X] = WINDOW_WIDTH  - 256.0f;
	ap->pos[Y] = WINDOW_HEIGHT - 236.0f;
	ap->scale[X] = 2.0f;
	ap->scale[Y] = ap->scale[X];
	ap->work1[X] = CLICK_LEFT;											//���N���b�N�̏ꍇ
	ap->shader_param1 = 3.0f;											//�Ԃ����Ԃ�����V�F�[�_�[�ɂ킽���p�����[�^�[
	ap->pri = UI_PRI * WP;												//�`��̗D��x

	actp = TASK_start_GRP( mouse_font_ui_exec, UI_GROUP, TEX_UI_FONT, shot_ui_rect, 0, "�U���̐���" );
	actp->pos[X] = ap->pos[X] + 64.0f;
	actp->pos[Y] = ap->pos[Y];
	actp->work1[X] = CLICK_LEFT;				
	actp->pri = ap->pri;												//�`��̗D��x

	//------------���N���b�N�̐���----------//
	ap = TASK_start_GRP( mouse_ui_exec, UI_GROUP, TEX_OBJECT_ICON, mouse_ui_rect, 1, "�E�N���b�N�̐���" );
	ap->pos[X] = WINDOW_WIDTH  - 256.0f;
	ap->pos[Y] = WINDOW_HEIGHT - 100.0f;
	ap->scale[X] = 2.0f;
	ap->scale[Y] = ap->scale[X];
	ap->work1[X] = CLICK_RIGHT;											//�E�N���b�N�̏ꍇ
	ap->shader_param1 = 3.0f;											//�Ԃ����Ԃ�����V�F�[�_�[�ɂ킽���p�����[�^�[
	ap->pri = UI_PRI * WP;												//�`��̗D��x

	actp = TASK_start_GRP( mouse_font_ui_exec, UI_GROUP, TEX_UI_FONT, catch_font_rect, 0, "�͂ނⓊ����̐���" );
	actp->pos[X] = ap->pos[X] + 64.0f;
	actp->pos[Y] = ap->pos[Y];
	actp->work1[X] = CLICK_RIGHT;				
	actp->pri = ap->pri;												//�`��̗D��x
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�ړ��L�[��\��( drawfunc���g�p )
//------------------------------------------------------------------------------------------------------------------------------------------------------
void movement_key_ui_drawfunc( TASK *ap )
{
	TASK spr;
	SINT32 key_box[ 4 ] = { DIK_W, DIK_A, DIK_S, DIK_D };				//�ړ��L�[�Ɏg�p���Ă镨���g�p
	SINT32 i;															//for���p�̕ϐ�
	ANGLE  ang_box[ 4 ] = { 0x0000, 0xc000, 0x8000, 0x4000 };			//�p�x���i�[

	TASK_init_member_pointer( &spr );									//�܂��̓������̏�����

//���W
	spr.pos[X] = ap->pos[X];											//��ƂȂ���W��ݒ�
	spr.pos[Y] = ap->pos[Y];											//��ƂȂ���W��ݒ�

//�O���t�B�b�N�̐ݒ�
	spr.uv_rect = move_ment_font_rect;									//�L�[�̃A�C�R���̋�`��ݒ�
	spr.tex_no  = TEX_UI_FONT;											//��������̃O���t�B�b�N
	spr.pri     = ap->pri;												//�`��̗D��x

	spr.scale[X] = ap->scale[X];
	spr.scale[Y] = spr.scale[X];

	for( i = 0; i < 4; i++ )											//�ړ��L�[�̐�������
	{
		spr.anime_no = i;												//�A�j���i���o�[��i�Ɠ���
		spr.pos[Y] += 80.0f;											//�c�ɕ��ׂ�
		if( SOZ_Inkey_DAT( key_box[ i ] ) != 0 )						//�����̎��ʔԍ��Ɠ����L�[��������Ă�����
		{
			spr.base_color[ 0 ][ 2 ] = BASE_COLOR;						//�����𗎂Ƃ�
			spr.base_color[ 0 ][ 3 ] = BASE_COLOR;						//�����΂𗎂Ƃ�
		}
		else
		{
			spr.base_color[ 0 ][ 2 ] = 0xff;							//�����ɖ߂�
			spr.base_color[ 0 ][ 3 ] = 0xff;							//�΂����ɖ߂�
		}
		SOZ_sprite_draw( &spr );										//�ŏI�I�ɂ����ŕ`�悷��
	}
}

void movement_key_ui_exec( TASK *ap )
{

}

void movement_key_ui_start( void )
{
	TASK *ap;
	ap = TASK_start_DRAWFUNC( movement_key_ui_exec, movement_key_ui_drawfunc, UI_GROUP, "�L�[�̐���" );
	ap->pos[X] = 70.0f;													//��ƂȂ���W��ݒ�
	ap->pos[Y] = KEY_POS_Y;												//��ƂȂ���W��ݒ�
	ap->scale[X] = 1.5f;
	ap->scale[Y] = ap->scale[X];
	ap->pri = UI_PRI * WP;												//�`��̗D��x
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//����`��
//------------------------------------------------------------------------------------------------------------------------------------------------------
void arrow_drawfunc( TASK *ap )
{
	TASK spr;													
	SINT32 key_box[ 4 ] = { DIK_W, DIK_A, DIK_S, DIK_D };				//�ړ��L�[�Ɏg�p���Ă镨���g�p
	SINT32 i;															//for���p�̕ϐ�
	ANGLE  ang_box[ 4 ] = { 0x0000, 0xc000, 0x8000, 0x4000 };			//���̊p�x��ݒ�
	TASK_init_member_pointer( &spr );									//�܂��̓������̏�����

//���W
	spr.pos[X] = ap->pos[X];											//��ƂȂ���W��ݒ�
	spr.pos[Y] = ap->pos[Y];											//��ƂȂ���W��ݒ�

//�p�x
	spr.ang[Z] = 0x0;													//�p�x��������

//�O���t�B�b�N�̐ݒ�
	spr.uv_rect = arrow_rect;											//�L�[�̃A�C�R���̋�`��ݒ�
	spr.tex_no  = TEX_UI_FONT;											//��������̃O���t�B�b�N
	spr.anime_no = 0;													//�A�j���i���o�[��i�Ɠ���
	spr.pri     = ap->pri;												//�`��̗D��x
	spr.scale[X] = ap->scale[X];
	spr.scale[Y] = spr.scale[X];

	for( i = 0; i < 4; i++ )											//�ړ��L�[�̐�������
	{
		spr.ID = i;														//���ʔԍ���ݒ�
		spr.pos[Y] += 80.0f;											//�c�ɕ��ׂ�
		spr.ang[Z] = ang_box[ i ];										//45�x�ɉ񂷕�����������
		if( SOZ_Inkey_DAT( key_box[ i ] ) != 0 )						//�����̎��ʔԍ��Ɠ����L�[��������Ă�����
		{
			spr.base_color[ 0 ][ 2 ] = BASE_COLOR;						//�����𗎂Ƃ�
			spr.base_color[ 0 ][ 3 ] = BASE_COLOR;						//�����΂𗎂Ƃ�
		}
		else
		{
			spr.base_color[ 0 ][ 2 ] = 0xff;							//�����ɖ߂�
			spr.base_color[ 0 ][ 3 ] = 0xff;							//�΂����ɖ߂�
		}
		SOZ_sprite_draw( &spr );										//�ŏI�I�ɂ����ŕ`�悷��
	}	
}

void arrow_exec( TASK *ap )
{

}

void arrow_start( void )
{
	TASK *ap;
	ap = TASK_start_DRAWFUNC( arrow_exec, arrow_drawfunc, UI_GROUP, "���" );
	ap->pos[X] = 180.0f;												//��ƂȂ���W��ݒ�
	ap->pos[Y] = KEY_POS_Y;												//��ƂȂ���W��ݒ�
	ap->pri = UI_PRI * WP;												//�`��̗D��x
	ap->scale[X] = 1.5f;
	ap->scale[Y] = ap->scale[X];
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�S�̂Ŏg��UI���܂Ƃ߂Ă���
//------------------------------------------------------------------------------------------------------------------------------------------------------
void common_ui_set( void )
{
	hand_ui_start();													//��̏󋵂�`����
	mouse_ui_start();													//�}�E�X�̑������
	movement_key_ui_start();											//�ړ��L�[�̕\��
	arrow_start();														//���̕\��
}







//----------------------------------------------------------------------------------------------
//�Q�[���I�[�o�[�ł��N���A�ł��\������UI�����
//----------------------------------------------------------------------------------------------]
void score_drawfunc( TASK *ap )
{
	TASK spr;
	SINT32 i;
	SINT8 str[16];

	//������ɕύX����
	sprintf( str, "%8d", *ap->work_p[X] ); 					//�������̒��ɕۑ�����
	
	TASK_init_member_pointer( &spr );						//������spr��������

	spr.pos[X] = ap->pos[X];								//���W�̐ݒ�
	spr.pos[Y] = ap->pos[Y];								//���W�̐ݒ�
	spr.scale[X] = ap->scale[X];							//�傫����ݒ�
	spr.scale[Y] = spr.scale[X];							//�傫����ݒ�
	spr.tex_no = TEX_UI_FONT;								//�e�N�X�`���i���o�[�͎����̃��c
	spr.uv_rect = number_rect;								//�����̋�`�������
	spr.pri = ap->pri;										//�`��D��x��ݒ�

	for ( i = 0; i < 8 ;i++ )							//�\����������������
	{
		if( str[ i ] >= '0' && str[ i ] <= '9' )			//�X�R�A�̂��炢��0�`9�Ȃ�
		{
			spr.base_color[0][1] = 0xff;					//R( �͂�����ƃX�R�A���o�� )
			spr.base_color[0][2] = 0xff;					//G( �͂�����ƃX�R�A���o�� )
			spr.base_color[0][3] = 0xff;					//B( �͂�����ƃX�R�A���o�� )
			spr.anime_no = str[ i ] - '0';					//�������0���當�����0�������Ɛ�����0�ɂȂ�
		}

		else
		{
			spr.base_color[0][1] = 120;						//R( �������Â����� )
			spr.base_color[0][2] = 120;						//G( �������Â����� )
			spr.base_color[0][3] = 120;						//B( �������Â����� )
			spr.anime_no = 0;								//�v�Z���ʂ�0
		}

		SOZ_sprite_draw( &spr );							//�����ŕ`�悷��
		spr.pos[X] += ( 52.0f * spr.scale[X] );				//���ɂ��炷
	}
}

void score_exec( TASK *ap )
{
	
}

void socre_start( FLOAT x, FLOAT y, FLOAT scale, SINT32 *score_p )
{
	TASK *ap;
	ap = TASK_start_DRAWFUNC( score_exec, score_drawfunc, UI_GROUP, "�X�R�A" );
	ap->pos[X] = x;
	ap->pos[Y] = y;
	ap->scale[X] = scale;									//�傫����ݒ�
	ap->scale[Y] = ap->scale[X];							//�傫����ݒ�
	ap->work_p[X] = score_p;								//�X�R�A��n�C�X�R�A������邽�߂Ƀ|�C���^�[�ɂ���
	ap->pri = UI_PRI * WP;
}




