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
//#define	OBJECT_SEQ	""

//-----------------------------------------------------------------------------------------------------------------------
//�O���ϐ�
//-----------------------------------------------------------------------------------------------------------------------
SINT32	page = 0, select_no = 1;				//�I�u�W�F�N�g�̃y�[�W���Ƃǂ���I�����Ă��邩���i�[����ϐ�
FLOAT	sequence_box[ SEQ_SAVE_MAX ];			//�V�[�P���X
FLOAT	temporary_sequence_box[ SEQ_SAVE_MAX ];	//�ꎞ�I�ɕۑ����Ă�����( �R���g���[��Z�������Ĉ�O�ɖ߂��悤�ɂ��邽�� )
FLOAT	magnification_hp = 1.0f, magnification_atk = 1.0f;	//�{��
//SINT8	click_check = 0;						//char�^�̕����������ςށH( 3�o�C�g�̋󂫂𖄂߂�K�v����H )
//SINT8	catch_switch = 0;						//char�^�̕����������ςށH(x )
bool	select_switch = FALSE;					//�I�u�W�F�N�g�I�����o������������肷��( �{���Ƀu�[���^�ł����̂��H 2025/2/21 )
bool	click_check = FALSE, catch_switch = FALSE;
PARTS_RECT selsect_arrow_rect[]=
{
	{    1,     1,    62,    62,    62,    24 },
};

PARTS_RECT	status_rect[]=
{
	{  129,     1,   126,    62,    63,    31},	//HP�̋�`
	{  273,     1,   190,    62,    95,    31},	//ATK�̋�`
	{  129,   161,   206,    62,   103,    31},	//SIZE�̋�`
};


//----------------------------------------------------------------------------------------------------
//�ݒu����I�u�W�F�N�g���P�[�X�Ŕ��ʂ�����
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
//�\���̂̒��g���Ȃ���
//----------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
//�I�u�W�F�N�g��I�΂���
//-----------------------------------------------------------------------------------------------------------------------
void object_select_exec( TASK *ap )
{
	SINT32 elements;							//�v�f�����i�[����
	FLOAT  width, y, height;					//�������i�[����
	CHAR   box[ 256 ];							//
	elements = 0;								//
	while( ap->task_name[ elements ] != NULL )	//
	{
		box[ elements ] = ap->task_name[ elements ];	//
		elements++;								//
	}
	//elements = sizeof ap->task_name / sizeof ap->task_name[0];	//�v�f�����v�Z���� 
	width = 42.0f * ( (FLOAT)elements / 2 );	//�v�f���ƕ����T�C�Y����Z����
	width = ap->pos[ X ] + width;				//���W����_�ɉ�����ݒ�
	y = ap->pos[ Y ];							//���ݒ�
	height = ap->pos[ Y ] + 32.0f;				//����ݒ�
	if( mouse2d_range_check( ap->pos[ X ],width, y, height ) != 0 )		//�}�E�X���͈͂ɓ����Ă�����
		select_no = ap->ID;						//ID������

	if( ap->ID == select_no + ( SELECT_MAX * page ) )					//�ꏏ�Ȃ�
	{
		ap->base_color[0][2] = 0x0;				//�΂𔲂�
		ap->base_color[0][3] = 0x0;				//�𔲂�
	}
	else
	{
		ap->base_color[0][2] = 0xff;			//�΂�߂�
		ap->base_color[0][3] = 0xff;			//��߂�
	}
	
}

void object_select_start( FLOAT x, FLOAT y, SINT32 id, SINT32 group )
{
	TASK *ap;
	OBJECT_DATA *op;
	op = &object_data[ id ]; 
	if( op->name[0] == NULL )					//�����I�u�W�F�N�g�̒��g������������
		return;									//����ȏ���s���Ȃ�( �^�X�N�̓o�^���ĂȂ�����s����͂� )
	ap = TASK_start_FONT( object_select_exec, group, op->name, 3 );
	ap->pos[X] = x;
	ap->pos[Y] = y;
	ap->ID = id;
	ap->pri = 9999 * WP;
}


//----------------------------------------------------------------------------------------------------
//��󂪏d�Ȃ��Ă��Ȃ����𒲂ׂ�
//----------------------------------------------------------------------------------------------------
void arrow_check( void )
{
	TASK *actp;
	click_check = 0;							//�܂�0�ɂ���

	for( actp = ap_start; actp != NULL; actp = actp->next )
		if( actp->task_group == ARROW_GROUP )	//���Ȃ�
			if( actp->SWITCH != 0 )				//�d�Ȃ��Ă������ɒl�̕ς��work��0�ȊO�Ȃ�
				click_check = 1;				//�d�Ȃ��Ă�����1�ɂ���
}

//----------------------------------------------------------------------------------------------------
//���݂̃��f���̖��O�ƈ���Ȃ�ύX�ł���悤�ɂ���( ���̎��s�� )
//----------------------------------------------------------------------------------------------------
void selsect_arrow_exec( TASK *ap )
{
	FLOAT x, width, y, height;
	ap->SWITCH = 0;								//��ɏ��������Ă���
	if( ( ap->grp_mode & FLIP_LR ) == 0 )		//�������Ȃ�( ���S�_�͉E )
	{ 
		x = ap->pos[X] - 64.0f;					//�������ɍ��킹��x���v�Z
		width = ap->pos[X];						//�������ɍ��킹�ĉ������v�Z
	}

	else										//�E�����Ȃ�( ���S�_�͍� )
	{
		x = ap->pos[X];							//�E�����ɍ��킹��x���v�Z
		width = ap->pos[X] + 64.0f;				//�E�����ɍ��킹�ĉ������v�Z
	}

	y = ap->pos[Y] - 32.0f;						//�������v�Z
	height = ap->pos[Y] + 32.0f;				//�c�����v�Z

	if( mouse2d_range_check( x, width, y, height ) != 0 )		//�}�E�X���͈͂ɓ����Ă�����
	{
		ap->SWITCH = 1;							//�l��1�ɂ���( ���ꂪ1�̂Ƃ��̓N���b�N�ŃI�u�W�F�N�g��ݒu�ł��Ȃ��悤�ɂ��� )
		ap->shader_pass = SHADER_RED;			//�Ԃ��V�F�[�_�[��������
		if( SOZ_Mouse_Button( 0 ) != 0  )		//�܂�0����Ȃ������v�Z
			if( SOZ_Mouse_Button( 0 ) == 1 || SOZ_Mouse_Button( 0 ) % 12 == 0 )	//�P�����܂��͒������ŏ������オ��
			{
				if( (ap->grp_mode & FLIP_LR) == 0 )		//�������Ȃ�( ���S�_�͉E )
					select_no--;				//���Z����
				else							//�E�����Ȃ�
					select_no++;				//���Z����

				select_and_page_write( "data/select_data.bn", &select_no );	//�Z���N�g��ۑ�
				select_and_page_write( "data/page_data.bn", &page );		//�y�[�W��ۑ�
			}

//-----�y�[�W���X�V���ꂽ�Ƃ��Z���N�g���ςȒl�ɂȂ�Ȃ��悤�ɐ��䂷��-----//
		if( select_no <= 0 )
		{
			select_no = SELECT_MAX;					//�i���o�[��1�ɂ���( ���̃y�[�W��1�Ԗ� )
			page--;									//�y�[�W�����Z			
		}
		
		else if( select_no % ( SELECT_MAX + 1 ) == 0 )//�I�𐔂̃}�b�N�X�Ɉ���Z�������܂肪0�Ȃ�
		{
			select_no = SELECT_MIN;					//�i���o�[��1�ɂ���( ���̃y�[�W��1�Ԗ� )
			page++;									//�y�[�W�����Z
		}
		

//�y�[�W���I�u�W�F�N�g�̍\���̂̐��𒴂��Ȃ��悤�Ɂ@���䂷��
		if( page > PAGE_MAX )						//�y�[�W�̍ő�𒴂�����
		{
			select_no = SELECT_MAX;
			page = PAGE_MAX;						//�y�[�W�̍ő�ŌŒ�
		}
		else if( page < PAGE_MIN )					//�y�[�W�̍ŏ������������
		{
			select_no = SELECT_MIN;
			page = PAGE_MIN;						//�y�[�W���ŏ��ŌŒ�
		}
	}

	else											//�}�E�X���͈͂ɓ����Ă��Ȃ�������
	{
		ap->SWITCH = 0;								//�l��������
		ap->shader_pass = SOZ_UNCLEAR;				//�V�F�[�_�[���؂�
	}
}

//----------------------------------------------------------------------------------------------------
//���݂̃��f���̖��O�ƈ���Ȃ�ύX�ł���悤�ɂ���
//----------------------------------------------------------------------------------------------------
void model_name_exec( TASK *ap )
{
	SINT32 elements, id;							//�v�f�����i�[����
	FLOAT  width;									//�������i�[����
	CHAR   box[ 256 ];								//
	elements = 0;									//
	id = select_no + ( SELECT_MAX * page );			//�y�[�W����������ID������
	OBJECT_DATA *op;
	op = &object_data[ id ];						//�I�΂�Ă�ID�̍\���̂��i�[
	if( op->name[ 0 ] == NULL )
	{
		select_no--;
		return;
	}
	switch( ap->SCENE )
	{
		case 0:
			while( ap->task_name[ elements ] != NULL )	//�^�X�N�̕������Ȃ��Ƃ���܂ŉ�
			{
				box[ elements ] = ap->task_name[ elements ];	//
				elements++;							//�g���Ă�z��̐��𐔂��Ă�	
			}
			width = 42.0f * ( ( FLOAT )elements / 2 );	//�v�f���ƕ����T�C�Y����Z����
			width = WINDOW_WIDTH_HALF - width / 5;		//���W����_�ɍ��ɂ��炷
			object_select_start( width, 21.0f, id, MODEL_NAME_GROUP );	//�t�H���g���o��
			ap->SCENE = 10;							//�ҋ@�Ɉړ�����
			break;

		case 10:
			if( ap->work1[ X ] != select_no )
			{
				ap->SCENE = 0;						//������x�o��������
				TASK_end_group( MODEL_NAME_GROUP );	//���C������������				
				ap->work1[ X ] = select_no;			//�y�[�W��ۑ�
				return;
			}
			break;
				
	}
	
}

void model_name_start( void )
{
	TASK *ap;
	ap = TASK_start( model_name_exec, MANE_GROUP, "���݂̃��f����\��" );
	ap->work1[X] = select_no + ( PAGE_MAX * page );
	ap->pri = 9999 * WP;
	
	ap = TASK_start_GRP( selsect_arrow_exec, ARROW_GROUP, TEX_DEBUG_PARAM, selsect_arrow_rect, 0, "�������̖��" );
	ap->pos[X] = WINDOW_WIDTH_HALF / 2.0f;
	ap->pos[Y] = 32.0f;
	ap->pri = 9999 * WP;

	ap = TASK_start_GRP( selsect_arrow_exec, ARROW_GROUP, TEX_DEBUG_PARAM, selsect_arrow_rect, 0, "�E�����̖��" );
	ap->pos[X] = WINDOW_WIDTH_HALF + ( WINDOW_WIDTH_HALF / 2.0f );		//�E�������炢�ɍs��
	ap->pos[Y] = 32.0f;
	ap->grp_mode |= FLIP_LR;											//���]���ĉE�����ɂ���
	ap->pri = 9999 * WP;
}


//----------------------------------�I�u�W�F�N�g���f��----------------------------------//

//-----------------------------------------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̐ݒu���E�N���b�N�Ŋm�肷��
//-----------------------------------------------------------------------------------------------------------------------
SINT32 end_code_check( void )
{
	SINT32 i;											//���g����
	i = 1;												//�񂷏����l��ݒ�( 0��NULL�Ȃ�l���Ԃ�̂�1����X�^�[�g )
	if( sequence_box[0] == NULL )						//�������g���Ȃɂ��Ȃ��̂Ȃ�
		return 0;										//0�Ԃ�Ԃ�

	do
	{
		i++;
	} while( sequence_box[i] != -999.0f );				//�G���R�[�h��������܂ŉ�

	return i;											//�G���R�[�h�̔ԍ���n��
}


//----------------------------------------------------------------------------------------------------
//�ݒu����I�u�W�F�N�g���P�[�X�Ŕ��ʂ�����( �͌^ )
//----------------------------------------------------------------------------------------------------
void object_set_case( TASK *ap )
{
	switch( ap->ID )
	{
		case 2: case 3: case 4: case 5: case 6:	case 7: //�e�N�X�`���[�̈Ⴄ�Ԃ���
			car_start( ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X], ap->ang[Y], ap->scale[X], NO_HP, NO_ATK, ap->ID );
			break;

		case 16:
			parking_start( ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X], ap->ang[Y], ap->scale[X], NO_HP, NO_ATK, ap->ID );
			break;

		case 17:
			heri_start( ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X], ap->ang[Y], ap->scale[X], NO_HP, NO_ATK, ap->ID );
			break;

		case 20:
			alien_start( ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X], ap->ang[Y], ap->scale[X], NO_HP, NO_ATK, ap->ID );
			break;

		default:
			object_start( ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X], ap->ang[Y], ap->scale[X], NO_HP, NO_ATK, ap->ID );
			break;
	}
}



void page_cheng_func( TASK *ap )
{
	if( SOZ_Inkey_TRG( DIK_LEFT ) != 0 )
		if( page > PAGE_MIN )
			page--;
	
	if( SOZ_Inkey_TRG( DIK_RIGHT ) != 0 )
		if( page < PAGE_MAX )
			page++;

}


//-----------------------------------------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̑I����ʂ��o������������肷��
//-----------------------------------------------------------------------------------------------------------------------
void object_window_set_exec( TASK *ap )
{
	SINT32 i, id;
	FLOAT y;
	y = 0;
	id = 1;

	if( ap->work1[Z] != select_no )
	{
		select_and_page_write( "data/select_data.bn", &select_no );	//�Z���N�g��ۑ�
		ap->work1[Z] = select_no;					//�i���o�[��ۑ�
	}

	if( SOZ_Mouse_Button( 1 ) == 1 )				//�I�u�W�F�N�g���J��( �E�N���b�N )
	{
		if( select_switch == TRUE )					//����ture�Ȃ�
			select_switch = FALSE;					//false�ɕς���
		else										//����ture�ȊO�Ȃ�
			select_switch = TRUE;					//ture�ɕς���
	}

	if( SOZ_Inkey_REP( DIK_UP ) != 0 )
		select_no--;

	if( SOZ_Inkey_REP( DIK_DOWN ) != 0 )
		select_no++;

	if( select_no >= 10 )
		select_no = 10;
	else if( select_no <= 1 )
		select_no = 1;


	switch( ap->SCENE )								//�����Ƀ^�X�N���o�����薈��^�X�N���������肵�Ȃ��悤�ɃX�C�b�`���ɂ���( 2025/2/21 )
	{
		case 0:
			//if( ap->work1[X] == FALSE )			//�X�C�b�`��0�Ȃ�
			//	ap->SCENE = 10;						//��ʂɉf���Ȃ��悤�ɂ��郋�[�`���ɔ�΂�
			if( select_switch == TRUE )				//��ʑI�����I�΂���
				ap->SCENE = 20;						//�I����ʂ��o��
			break;

		case 20:									//��u�����o��
			for( i = 1; i < SELECT_MAX; i++ )		//10�I�����o��
			{
				id = i + ( SELECT_MAX * page );		//���ʔԍ���ݒ�
				object_select_start( 32, y, id, FONT_GROUP );	//���f����I�������镶�����o��
				y += 64.0f;							//���ɂ��炷
			}
			ap->work1[Y] = page;					//�y�[�W��ۑ����Ă���
			ap->SCENE++;							//���̃P�[�X�Ɉړ�
			break;

		case 21:									//�y�[�W���ς������I����ʂ�����肵�Ă��邩�����Ă�
			if(select_switch == FALSE || ap->work1[ Y ] != page )				//�����I����ʂ������������̓y�[�W�ړ��������
			{
				TASK_end_group( FONT_GROUP );								//�t�H���g������
				select_and_page_write( "data/select_data.bn", &select_no );	//�Z���N�g��ۑ�
				select_and_page_write( "data/page_data.bn", &page );		//�y�[�W��ۑ�
				ap->SCENE = 0;												//�P�[�X��0�ɖ߂�
				ap->work1[Y] = page;										//�y�[�W��ۑ�
			}
			page_cheng_func( ap );
			break;
	}
}


//-----------------------------------------------------------------------------------------------------------------------
//�I�u�W�F�N�g�G�f�B�^�[�̈ړ��̊֐�
//-----------------------------------------------------------------------------------------------------------------------
void editor_movement_get_key( TASK *ap )
{
	SINT32 sa_x, sa_y;
	SINT32 mx, my;

	mx = mouse_x;
	my = mouse_y;
	sa_x = ap->work2[X] - mouse_x;			//���̍����v��
	sa_y = ap->work2[Y] - mouse_y;			//�c�̍����v��
	ap->vec[X] = SOZ_get_sin( -ap->work1[Y] ) * ap->fwork2[X];
	ap->vec[Y] = SOZ_get_sin(  ap->angle[ X ] ) * ap->fwork2[X];
	ap->vec[Z] = SOZ_get_cos( -ap->work1[Y] ) * ap->fwork2[X];
	//-----------�L�[����-----------//
	if( SOZ_Inkey_DAT( DIK_LSHIFT ) != 0 || SOZ_Inkey_DAT( DIK_RSHIFT ) != 0 )//�V�t�g�������Ă�����
	{
		if( SOZ_Mouse_Button( 2 ) )
		{
//-----------�p�x�ɂ���Ĉړ����ς��-----------//
		if( sa_y > 5 )		//��������20���傫�����( ���ɐi�� )
		{
			ap->pos[Y] += 120.0f;
		}
		else if( sa_y < -5 )
		{
			ap->pos[Y] -= 120.0f;
		}
			if( sa_x > 0 )
			{
				if( ap->work1[ Y ] > 0x0000 && 0x2000 >= ap->work1[ Y ] || ap->work1[ Y ] > 0xd000 )
					ap->pos[ X ] -= ap->fwork1[X];		//����̊p�x�ɂ����獶�ɐi��
				else if( ap->work1[ Y ] > 0x2000 && 0x6000 >= ap->work1[ Y ] )
					ap->pos[ Z ] -= ap->fwork1[X];		//����̊p�x�ɂ������O�ɐi��
				else if( ap->work1[ Y ] > 0x6000 && 0xa000 >= ap->work1[ Y ] )
					ap->pos[ X ] += ap->fwork1[X];		//����̊p�x�ɂ�����E�ɐi��
				else if( ap->work1[ Y ] > 0xa000 && 0xd000 >= ap->work1[ Y ] )
					ap->pos[ Z ] += ap->fwork1[X];		//����̊p�x�ɂ����牜�ɐi��

			}
//-----------�p�x�ɂ���Ĉړ����ς��-----------//
			if( sa_x < 0 )
			{
				if( ap->work1[ Y ] > 0x0000 && 0x2000 >= ap->work1[ Y ] || ap->work1[ Y ] > 0xd000 )
					ap->pos[ X ] += ap->fwork1[X];
				else if( ap->work1[ Y ] > 0x2000 && 0x6000 >= ap->work1[ Y ] )
					ap->pos[ Z ] += ap->fwork1[X];
				else if( ap->work1[ Y ] > 0x6000 && 0xa000 >= ap->work1[ Y ] )
					ap->pos[ X ] -= ap->fwork1[X];
				else if( ap->work1[ Y ] > 0xa000 && 0xd000 >= ap->work1[ Y ] )
					ap->pos[ Z ] -= ap->fwork1[X];
			}

			if( mouse_x == mx )					//�����J�[�\�����~�܂�����
			{
				ap->work2[Y]   = mouse_y;		//�J�[�\����ۑ�
				ap->work2[X]   = mouse_x;		//�J�[�\����ۑ�
			}
		}
	}

	else if( SOZ_Inkey_DAT( DIK_LSHIFT ) == 0 && SOZ_Inkey_DAT( DIK_RSHIFT ) == 0 )				//�V�t�g�������Ă��Ȃ����
	{
		ap->work2[Y]   = mouse_y;		//�}�E�X�̍��W��ۑ����Ă���
		ap->work2[X]   = mouse_x;		//�}�E�X�̍��W��ۑ����Ă���
	}

	if( SOZ_Inkey_DAT( DIK_LCONTROL ) == 0 && SOZ_Inkey_DAT( DIK_RCONTROL ) == 0 )
	{
		if( SOZ_MouseZ() > 10 )
		{
			ap->pos[ X ] += -ap->vec[ X ];			//���ׂĂ̊p�x�ɉ��Z
			ap->pos[ Y ] += -ap->vec[ Y ];			//���ׂĂ̊p�x�ɉ��Z
			ap->pos[ Z ] += -ap->vec[ Z ];			//���ׂĂ̊p�x�ɉ��Z
		}

		if( SOZ_MouseZ() < -10 )
		{
			ap->pos[ X ] += ap->vec[ X ];			//���ׂĂ̊p�x�ɉ��Z
			ap->pos[ Y ] += ap->vec[ Y ];			//���ׂĂ̊p�x�ɉ��Z
			ap->pos[ Z ] += ap->vec[ Z ];			//���ׂĂ̊p�x�ɉ��Z
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------
//����̃L�[�������ƈړ����x��ς���֐�
//-----------------------------------------------------------------------------------------------------------------------
void movement_speed_chenge( TASK *ap )
{
	if( SOZ_Inkey_DAT( DIK_Z ) != 0 )
	{
		ap->fwork1[X] = NORMAL_EDITOR_SPEED_X * 2;	//�ʏ�̂Q�{�̑��x
		ap->fwork2[X] = NORMAL_EDITOR_SPEED_Z * 2;	//�ʏ�̂Q�{�̑��x
		ap->fwork3[X] = NORMAL_EDITOR_SPEED_X * 2;	//�ʏ�̂Q�{�̑��x
	}
	else if( SOZ_Inkey_DAT( DIK_X ) != 0 )
	{
		ap->fwork1[X] = NORMAL_EDITOR_SPEED_X / 2;	//�ʏ�̂Q����1�̑��x
		ap->fwork2[X] = NORMAL_EDITOR_SPEED_Z / 2;	//�ʏ�̂Q����1�̑��x
		ap->fwork3[X] = NORMAL_EDITOR_SPEED_Z / 2;	//�ʏ�̂Q����1�̑��x
	}
	else if( SOZ_Inkey_DAT( DIK_Z ) == 0 || SOZ_Inkey_DAT( DIK_X ) == 0 )
	{
		ap->fwork1[X] = NORMAL_EDITOR_SPEED_X;		//�ʏ�̑��x
		ap->fwork2[X] = NORMAL_EDITOR_SPEED_Z;		//�ʏ�̑��x
		ap->fwork3[X] = NORMAL_EDITOR_SPEED_X;		//�ʏ�̑��x
	}
}


#if 1
void model_movement_key( TASK *ap )
{
	if( SOZ_Inkey_DAT( DIK_LCONTROL ) != 0 && SOZ_Inkey_DAT( DIK_RCONTROL ) != 0 )
	{
		if( SOZ_MouseZ() > 20 )
			ap->fwork1[ Y ] += 40.0f;
		else if( SOZ_MouseZ() < -20 )
			ap->fwork1[ Y ] -= 40.0f;
	}
	ap->vec[X] = SOZ_get_sin( -ap->parent->work1[Y] ) * ap->parent->fwork2[X];
	ap->vec[Y] = SOZ_get_sin(  ap->parent->angle[ X ] ) * ap->parent->fwork2[X];
	ap->vec[Z] = SOZ_get_cos( -ap->parent->work1[Y] ) * ap->parent->fwork2[X];
	//-----------�L�[����-----------//
	if( SOZ_Inkey_DAT( DIK_D ) != 0 )
	{
		if( ap->parent->work1[Y] > 0x0000 && 0x2000 >= ap->parent->work1[Y] || ap->parent->work1[Y] > 0xd000 )
			ap->fwork1[X] -= ap->parent->fwork1[X];
		else if( ap->parent->work1[Y] > 0x2000 && 0x6000 >= ap->parent->work1[Y] )
			ap->fwork1[Z] -= ap->parent->fwork1[X];
		else if( ap->parent->work1[Y] > 0x6000 && 0xa000 >= ap->parent->work1[Y] )
			ap->fwork1[X] += ap->parent->fwork1[X];
		else if( ap->parent->work1[Y] > 0xa000 && 0xd000 >= ap->parent->work1[Y] )
			ap->fwork1[Z] += ap->parent->fwork1[X];

	}

	if( SOZ_Inkey_DAT( DIK_A ) != 0 )
	{
		if( ap->parent->work1[Y] > 0x0000 && 0x2000 >= ap->parent->work1[Y] || ap->parent->work1[Y] > 0xd000 )
			ap->fwork1[X] += ap->parent->fwork1[X];
		else if( ap->parent->work1[Y] > 0x2000 && 0x6000 >= ap->parent->work1[Y] )
			ap->fwork1[Z] += ap->parent->fwork1[X];
		else if( ap->parent->work1[Y] > 0x6000 && 0xa000 >= ap->parent->work1[Y] )
			ap->fwork1[X] -= ap->parent->fwork1[X];
		else if( ap->parent->work1[ Y ] > 0xa000 && 0xd000 >= ap->parent->work1[Y] )
			ap->fwork1[Z] -= ap->parent->fwork1[X];
	}

	
	if( SOZ_Inkey_DAT( DIK_W ) != 0 )
	{
		ap->fwork1[ X ] += -ap->vec[ X ];
		//ap->fwork1[ Y ] += -ap->vec[ Y ];
		ap->fwork1[ Z ] += -ap->vec[ Z ];
	}

	if( SOZ_Inkey_DAT( DIK_S ) != 0 )
	{
		ap->fwork1[ X ] += ap->vec[ X ];
		//ap->fwork1[ Y ] += ap->vec[ Y ];
		ap->fwork1[ Z ] += ap->vec[ Z ];
	}

	if( SOZ_Inkey_DAT( DIK_F ) != 0 )
	{
		ap->fwork2[ X ] = ap->parent->pos[ X ];
		ap->pos[ Y ] = GROUND;
		ap->fwork2[ Z ] = ap->parent->pos[ Z ];
	}

	if( SOZ_Inkey_REP( DIK_T ) != 0 )
		ap->pos[Y] += ap->parent->fwork3[X];
	else if( SOZ_Inkey_REP( DIK_G ) != 0 )
		ap->pos[Y] -= ap->parent->fwork3[X];
	
	if( SOZ_Inkey_REP( DIK_B ) != 0 )
		ap->pos[Y] = GROUND;

	ap->pos[ X ] = ap->fwork2[ X ] + ap->fwork1[ X ];
	ap->pos[ Z ] = ap->fwork2[ Z ] + ap->fwork1[ Z ];
}
#endif


//-----------------------------------------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̃��f���̉�]( ���s�[�g )
//-----------------------------------------------------------------------------------------------------------------------
void model_ang_key( TASK *ap )
{
	if( SOZ_Inkey_REP( DIK_Q ) != 0 )
		ap->ang[Y] -= 0x400;
	else if( SOZ_Inkey_REP( DIK_E ) != 0 )
		ap->ang[Y] += 0x400;
	else if( SOZ_Inkey_REP( DIK_R ) != 0 )
		ap->ang[Y] = 0x0;
}

//-----------------------------------------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̐ݒu���E�N���b�N�Ŋm�肷��
//-----------------------------------------------------------------------------------------------------------------------
void object_set_key( TASK *ap )
{
	FLOAT *point;												//�|�C���^�[
	point = sequence_box;										//�ǂ̔z�񂩂�������
	if( SOZ_Mouse_Button( 0 ) == 1 )							//���ɃJ�[�\�����d�Ȃ��Ă��Ȃ����
		if( SOZ_Mouse_Button( 0 ) <=  1 )
			if( click_check == 0 )
			{
				point = &sequence_box[ end_code_check() ];		//�G���h�R�[�h�̏ꏊ��T���ăA�h���X��n��
				*point++ = (FLOAT)ap->ID;						//�܂��P�[�X�ԍ�������( �P�[�X���Ŏg�p����� )
				*point++ = ap->pos[ X ];						//���W������( x )
				*point++ = ap->pos[ Y ];						//���W������( y )
				*point++ = ap->pos[ Z ];						//���W������( z )
				*point++ = (FLOAT)ap->ang[ X ];					//�p�x������( �Ƃ肠�������������ۑ����Ă��� )
				*point++ = (FLOAT)ap->ang[ Y ];					//�p�x������
				*point++ = ap->scale[ X ];						//�傫��������( x )(���͈�̑傫�������ł����Ǝv��( 2025/2/27 )
				//*point++ = ap->scale[Y];						//�傫��������( y )
				//*point++ = ap->scale[Z];						//�傫��������( z )
				*point++ = magnification_hp;					//HP�̔{��������
				*point++ = magnification_atk;					//�U���͂̔{��������
				*point++ = (FLOAT)ap->ID;						//ID������
				*point++ = -999.0f;								//�Ō�ɃG���R�[�h������
				sequence_write( "data/" SAVE_FILE ".bn", sequence_box );		//�V�[�P���X�ɕۑ�
				object_set_case( ap );							//�I�u�W�F�G�N�g��ݒu����
				return;
			}
}


//-----------------------------------------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̃��f��
//-----------------------------------------------------------------------------------------------------------------------
void object_model_exec( TASK *ap )
{
	SINT32 id;
	OBJECT_DATA *op;
	id = select_no + ( SELECT_MAX * page );
	op = &object_data[ id ];								//�I�΂ꂽID�������
	if( op == NULL )
		return;

	ap->model_no = op->model_no;							//�\���̂̒��̃��f���i���o�[����
	ap->tex_no = op->tex_no;								//�\���̂̒��̃e�N�X�`���[�i���o�[����
	ap->pow = op->pow;										//���̉e�����ǂ�قǎ󂯂邩�̒l
	ap->specular[0] = op->specular_r;						//�X�y�L�����[�̐�
	ap->specular[1] = op->specular_g;						//�X�y�L�����[�̗�
	ap->specular[2] = op->specular_b;						//�X�y�L�����[�̐�
	ap->grp_mode = op->grp_flag;							//�O���t�B�b�N�֌W�̃t���O�𗧂Ă�
	scale_all_chenge( ap, op->scale );
	ap->ID = id;				//ID��ݒ�
	model_ang_key( ap );									//�L�[���͂Ŋp�x���ς��
	model_movement_key( ap );								//�L�[�ړ�������
	object_set_key( ap );									//�I�u�W�F�N�g��ݒu����
	//model_click_set( ap );								//�}�E�X�ŃN���b�N����Ƃ����ɃI�u�W�F�N�g��ݒu������
	ap->fwork1[Y] = ap->parent->pos[Y];						//�e�̏c���W��ۑ����Ă���

	SOZ_locate_print( 24, 1, "%2d", ap->ID ); 
}


//-----------------------------------------------------------------------------------------------------------------------
//�I�u�W�F�N�g��z�u����G�f�B�^�[���쐬
//-----------------------------------------------------------------------------------------------------------------------
void object_editor_exec( TASK *ap )
{
	
	FLOAT pos_x, pos_y, pos_z;
	pos_x =  ap->pos[X];									//���̍��W��ۑ�
	pos_y =  ap->pos[Y];									//�c�̍��W��ۑ�
	ap->work1[Y] =  ap->angle[ Y ];							//�ړ��Ɏg���p�x���擾���Ă�
	pos_z =  ap->pos[Z];									//�O��̍��W��ۑ�
	ap->work1[Y] =  ap->work1[Y] + 0x8000;					//32768( 180�x )��( �ڋʂ̖��c
	ap->work1[Y] %= 0xffff;									//65535( 360�x )�𒴂��Ȃ��悤�ɂ���
	if( SOZ_Inkey_DAT( DIK_LCONTROL ) == 0 && SOZ_Inkey_DAT( DIK_RCONTROL ) == 0 )
		movement_speed_chenge( ap );						//���x���グ��
	editor_movement_get_key( ap );
	check_range_restriction( ap, pos_x, pos_y, pos_z );		//���@�̈ړ��͈͂𐧌�����
}

void object_editor_start( void )
{
	TASK *ap, *actp, *omp;
	ap = TASK_start( object_editor_exec, EDITOR_GROUP, "�I�u�W�F�N�g��z�u����" );
	ap->pos[Y] = JIKI_Y;									//���@�̍��W�ɍ��킹��
	ap->pos[X] = JIKI_X;									//���@�̍��W�ɍ��킹��
	ap->pos[Z] = JIKI_Z;									//���@�̍��W�ɍ��킹��

	ap->fwork1[X] = NORMAL_EDITOR_SPEED_X;					//���E�ړ��̃X�s�[�h
	ap->fwork2[X] = NORMAL_EDITOR_SPEED_Z;					//�O��ړ��̃X�s�[�h
	common_ambient( ap );
	jiki = ap;												//�������J�����ɒǏ]������@

	actp = TASK_start( object_model_exec, OBJECT_GROUP, "���f���̃I�u�W�F�N�g" );
	actp->task_id = TASK_MODEL;								//�^�X�N��ID�����f���ɕς���( ���s���̕��ł��낢��ݒ肷�� )
	actp->fwork2[ X ] = ap->pos[ X ];
	actp->pos[ Y ] = GROUND;
	actp->fwork2[ Z ] = ap->pos[ Z ];
	actp->parent = ap;										//�e�q�֌W�Ōq���ł���
	ap->child[0] = actp;									//�e�q�֌W�Ōq���ł���

	omp = TASK_start( object_window_set_exec, MANE_GROUP, "�I�u�W�F�N�g�I���̏o���Ǘ��^�X�N" );
	omp->work1[Y] = page;									//�y�[�W��ۑ����Ă���
	omp->parent = ap;										//�e�q�֌W�Ōq���ł���
	ap->child[1] = omp;										//�e�q�֌W�Ōq���ł���
}




void seq_delete( SINT32 id )
{
	SINT32 i, index;
	i = 0;
	do
		i++;
	while( id != sequence_box[ i ] );						//�w�肵��ID�Ɠ����ɂȂ�܂ŉ�
	index = i + 10;
	
	while( i < index )
	{
		sequence_box[ i ] = -999;
		i++;
	}
	sequence_write( "data/" SAVE_FILE ".bn", sequence_box );		//�V�[�P���X�ɕۑ�
}

#if 0			//��΂ɐ���������( 2025/2/26 )
//-----------------------------------------------------------------------------------------------------------------------
//�I�u�W�F�N�g���f���̈ړ�( �}�E�X�̏ꏊ�Ō��߂� )
//-----------------------------------------------------------------------------------------------------------------------
void model_click_set( TASK *ap )
{
	FLOAT	pos_x, pos_y;						//�J���������������}�E�X�̒l���i�[����ϐ�
	ANGLE	mouse_angle;						//�}�E�X�̍��W�ƃJ�����̍��W����p�x���o���Ċi�[����ϐ�
	FLOAT	pos_z;
	FLOAT	abs_x;
	if( SOZ_Mouse_Button( 0 ) == 1 )			//���N���b�N�Ȃ�
	{
		abs_x = fabs( ( DOUBLE )mouse_3d_x );
		pos_z = z_box[ ( SINT32 )-mouse_3d_y ];	//
		//pos_x = world_mouse_x / pos_z;	//2D���W�ɂ���
		pos_y = world_mouse_y / pos_z;	//2D���W�ɂ���
//--------------����-----------------//
		if( mouse_3d_x > 0 )
		{
			ap->fwork1[ x_check( ap ) ] = world_mouse_x + SOZ_get_sin( jiki->angle[ Y ] ) * (pos_z / 2);
			ap->fwork1[ x_check( ap ) ] = ap->fwork1[ x_check( ap ) ] + SOZ_get_sin( mouse_view_ang( abs_x ) ) * (pos_z / 2);
		}
		else
		{
			ap->fwork1[ x_check( ap ) ] = world_mouse_x - SOZ_get_sin( jiki->angle[ Y ] ) * (pos_z / 2);
			ap->fwork1[ x_check( ap ) ] = ap->fwork1[ x_check( ap ) ] - SOZ_get_sin( mouse_view_ang( abs_x ) ) * (pos_z / 2);
		}
		//ap->pos[Y] = pos_y;
//-------------�O�㎲----------------//
		ap->fwork1[ z_check( ap ) ] = pos_z + SOZ_get_sin( jiki->angle[Y] );
		ap->pos[X] = ap->fwork1[X];	//
		ap->pos[Y] = GROUND;
		ap->pos[Z] = ap->fwork1[Z];	
	}
}
#endif





