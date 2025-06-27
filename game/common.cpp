//------------------------------------------------------------------------------------------------------------------------------------------------------
//                systemOZ Ver3
//			�Q�[�����C���v���O����
//						programed by TEAM_TAKUYA
//------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef WINDOWS_PC
#include    "../../../libs/systemOZ_v4/soz.h"
#else
//#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/town_break/src/game/game_include.h"
#include    "include.h"


//-------------------------------------------------------------
//�^�X�N�̃��C�e�B���O�ݒ�
//-------------------------------------------------------------
void specular_status_set( TASK *ap, FLOAT pow, FLOAT sp_r, FLOAT sp_g, FLOAT sp_b )
{
	ap->pow = pow;						//���̉e�����ǂꂭ�炢�󂯂邩�̐ݒ�
	ap->specular[0] = sp_r;				//�X�y�L�����[�̐Ԃ�ݒ�
	ap->specular[1] = sp_g;				//�X�y�L�����[�̗΂�ݒ�
	ap->specular[2] = sp_b;				//�X�y�L�����[�̐�ݒ�
}

//-------------------------------------------------------------
//�\���̂ɓ����Ă�����̂̃��C�e�B���O�ݒ�
//-------------------------------------------------------------
void specular_sturct_set( TASK *ap, OBJECT_DATA * op )
{
	specular_status_set( ap, op->pow, op->specular_r, op->specular_g, op->specular_b );
}


//-----------------------------------------------------------------------------------------
//HP���Ȃ��Ȃ����Ƃ��̍s��
//-----------------------------------------------------------------------------------------
void no_hp_move( TASK *ap, OBJECT_DATA *op,SINT32 cool_time )
{
	SINT32 fren;														//�����畷�����鉹
	FLOAT vol, pan, length, range_max;												//�E���畷�����鉹�ƃ{�����[���ƃ����O�X
	FLOAT sphire;
	OBJECT_SPHIRE *sp;
	sp = &object_sphire[ ap->ID ];
	sphire = sp->sphire[0] * 15;
	if( sphire < 4096.0f )
		sphire = 8192.0f;

	if( ap->HP <= 0 )
	{
		if( ap->SWITCH != 0 )								//��ꂽ�I�u�W�F�N�g���o���Ă�����
			ap->TIMER++;									//���Ԃ��v��
		else												//��ꂽ�I�u�W�F�N�g���o���Ă��Ȃ��̂Ȃ�
		{
			object_id++;									//��ꂽ�I�u�W�F�N�g�̐��𐔂��Ă���
			break_effect_occurrence( ap, 40.0f );			//�G�t�F�N�g�̔���
			if( range_sphire( ap, sphire, jiki ) != 0 )						//����͈̔͂Ɏ��@������Ɖ����Ȃ�
			{
				length = length_return( ap, sphire, jiki );	//�����O�X�����߂�
				length /= 512.0f;								//�����O�X������
				range_max = ( sphire ) / 256.0f;		//�͈͂̍ő�̐������߂�
				vol = range_vol( op->se_vol, range_max, length );				//���ʂ����߂�
				fren = ( SINT32 )ang_pan( ap, jiki, 1.0f, ap->work1[ Y ], 1 );			//�����̉���
				pan = ang_pan( ap, jiki, 1.0f, ap->work1[ Y ], 0 );				//�E���̉���
				SOZ_play_se( op->se_no, vol, fren, pan );
			}
			break_object_start( ap->pos[X], ap->pos[Y], ap->pos[Z], ap->vec[X], ap->vec[Y], ap->vec[Z],ap->fwork8[Y], ap->ID );
			ap->model_no = op->break_model_no;
			ap->tex_no = op->break_tex_no;
			ap->task_group = NO_GROUP;						//��莞�ԓ����蔻����������߂ɃO���[�v��ς���
			ap->SWITCH = ON;
		}

		if( ap->TIMER >= cool_time )
		{
			ap->model_no = op->model_no;
			ap->tex_no = op->tex_no;
			ap->task_group = OBJECT_GROUP;
			ap->HP = ( SINT32 )( op->hp * ap->fwork8[X] );	//HP����( ���Ƃ��Ƃ�HP�ƕۑ����Ă����{���������� ) 
			ap->TIMER = RESET;
			ap->SWITCH = OFF;
		}
	}
}


//-------------------------------------------------------------
//�x�N�g�������ׂ�0�ɂ���
//-------------------------------------------------------------
void vec_all_init( TASK *ap )
{
	ap->vec[X] = 0.0f;										//�x�N�g����0�ɂ���( �� )
	ap->vec[Y] = 0.0f;										//�x�N�g����0�ɂ���( �c )
	ap->vec[Z] = 0.0f;										//�x�N�g����0�ɂ���( �O�� )
}


//-------------------------------------------------------------
//�}�E�X��x���W����p�x��Ԃ�
//-------------------------------------------------------------
ANGLE mouse_view_ang( FLOAT mouse_pos_x )
{
	return mouse_ang_box[ ( SINT32 )mouse_pos_x ];	//���W����i�[����Ă�l�������ēn��
}


//-------------------------------------------------------------
//�^�X�N�̊p�x����x��z�̂ǂ����Ōv�Z���邩��Ԃ�( X�� )
//-------------------------------------------------------------
SINT32 x_check( TASK *ap )
{
	if( ap->work1[ Y ] > 0x0000 && 0x2000 >= ap->work1[ Y ] || ap->work1[ Y ] > 0xd000 )
		return X;		//����̊p�x�ɂ�����X��Ԃ�
	else if( ap->work1[ Y ] > 0x2000 && 0x6000 >= ap->work1[ Y ] )
		return Z;		//����̊p�x�ɂ�����Z��Ԃ�
	else if( ap->work1[ Y ] > 0x6000 && 0xa000 >= ap->work1[ Y ] )
		return X;		//����̊p�x�ɂ�����X��Ԃ�
	else if( ap->work1[ Y ] > 0xa000 && 0xd000 >= ap->work1[ Y ] )
		return Z;		//����̊p�x�ɂ�����Z��Ԃ�

	return X;
}


//-------------------------------------------------------------
//�^�X�N�̊p�x����x��z�̂ǂ����Ōv�Z���邩��Ԃ�( Z�� )
//-------------------------------------------------------------
SINT32 z_check( TASK *ap )
{
	if( ap->work1[ Y ] > 0x0000 && 0x2000 >= ap->work1[ Y ] || ap->work1[ Y ] > 0xd000 )
		return Z;		//����̊p�x�ɂ�����X��Ԃ�
	else if( ap->work1[ Y ] > 0x2000 && 0x6000 >= ap->work1[ Y ] )
		return X;		//����̊p�x�ɂ�����Z��Ԃ�
	else if( ap->work1[ Y ] > 0x6000 && 0xa000 >= ap->work1[ Y ] )
		return Z;		//����̊p�x�ɂ�����X��Ԃ�
	else if( ap->work1[ Y ] > 0xa000 && 0xd000 >= ap->work1[ Y ] )
		return X;		//����̊p�x�ɂ�����Z��Ԃ�

	return Z;
}


//-------------------------------------------------------------
//�}�E�X���͈͂ɓ�������0��1��Ԃ�( �}�E�X���W��2D )
//-------------------------------------------------------------
SINT32 mouse2d_range_check( FLOAT x, FLOAT width, FLOAT y, FLOAT height )
{
	if( x < mouse_x && width > mouse_x )		//�����͈͂ɓ����Ă�����
		if( y < mouse_y && height > mouse_y )	//���ɏc���͈͂ɓ����Ă�����
			return 1;							//�͈͂ɓ����Ă�����1��Ԃ�

	return 0;									//�����Ȃ�������0��Ԃ�
}


//-------------------------------------------------------------
//�U���͂��v�Z���ĕԂ�
//-------------------------------------------------------------
SINT32 atk_set( TASK *ap, OBJECT_DATA *op,FLOAT atk )
{
	SINT32 power;
	power = ( SINT32 )( op->atk * atk );	//�U����
	ap->fwork8[Y] =	atk;					//�ꉞATK�{�����ۑ����Ă���

	return power;							//�U���͂�ۑ� 
}


//-------------------------------------------------------------
//�q�b�g�|�C���g���v�Z���ĕԂ�
//-------------------------------------------------------------
SINT32 hp_set( TASK *ap, OBJECT_DATA *op, FLOAT hp )
{
	SINT32 hit_point;
	hit_point  = ( SINT32 )( op->hp * hp );	//�q�b�g�|�C���g
	ap->fwork8[X] = hp;						//HP�{����ۑ����Ă���

	return hit_point;
}


//--------------------------------------------------------------------------------------------------------------------------------
//HP��0�ɂȂ����Ƃ����f���̕`������邩�ǂ����𔻕ʂ���( �l���Ԃ�悤�ɂȂ��Ă���͎̂�����J�����O�Ƃ̌��ˍ����̈� )
//--------------------------------------------------------------------------------------------------------------------------------
SINT32 no_hp_task_id_chenge( TASK *ap, OBJECT_DATA *op )
{
	if( ( op->flag & ID_CHENGE_FLAG) != 0 )			//���̃t���O�������Ă�����
	{
		if( ap->HP <= 0 )							//HP��0�̂Ƃ�
		{
			ap->task_id = TASK_PROGRAM;				//���f���̕`����~�߂�
			return 1;								//������J�����O�Ƌ������Ȃ��悤�ɂ��邽�߂ɒl��Ԃ�
		}
		else										//HP��0����Ȃ�
		{
			ap->task_id = TASK_MODEL;				//���f���̕`�������
		}
	}

	return 0;
}


SINT32 F_excepting( FLOAT target_a, FLOAT target_b  )//( float�^ )�������m����v���Ȃ����ɒl���Ԃ�
{
	if( target_a != target_b )						//��v���Ȃ�������
		return 1;									//1��Ԃ�

	return 0;										//�Ȃɂ��Ȃ���0��Ԃ�
}



SINT32 excepting( SINT32 target_a, SINT32 target_b  )//( int�^ )�������m����v���Ȃ����ɒl���Ԃ�
{
	if( target_a != target_b )						//��v���Ȃ�������
		return 1;									//1��Ԃ�

	return 0;										//�Ȃɂ��Ȃ���0��Ԃ�
}


//--------------------------------------------------------------------------------------------------------------------------------
//������J�����O����l�����߂�
//--------------------------------------------------------------------------------------------------------------------------------
FLOAT viwe_case( TASK *ap )
{
	switch( ap->ID )
	{ 
		case 14: case 16:			//�w�Z�ƒ��ԏ�
			return 2100;
			break;

		default:
			return 700;		//��{�͂��̑傫���ő��v
			break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//������J�����O���g���ĉ�ʂɎʂ��Ă��Ȃ��Ƃ��Ƀ��f����`�悵�Ȃ�
//--------------------------------------------------------------------------------------------------------------------------------
void task_id_checge( TASK *ap, SINT32 check )
{
	if( check == 0 )			//HP��0�Ń��f���������Ă��Ȃ����
	{
		ap->task_id = TASK_MODEL;
		//-----������J�����O-----/
		if( SOZ_viewclip_checker( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ], viwe_case( ap ), CHECK_VIEW_LEFT | CHECK_VIEW_RIGHT | CHECK_VIEW_FRONT | CHECK_VIEW_BACK ) )
			ap->task_id = TASK_PROGRAM;
	}
}



//--------------------------------------------------------------------------------------------------------------------------------
//����̃t���[���𒴂����瓧���x�����݂ɕς���
//--------------------------------------------------------------------------------------------------------------------------------
void alpha_chenge( TASK *ap, SINT32 alp_max, SINT32 alp_min )
{
	SINT32 alp_box[ 2 ] = { alp_max, alp_min };				//�����x�̍ő�ƍŏ����i�[����
	ap->TIMER++;											//�t���[�����v��
	if( ap->TIMER % 16 == 0 )								//����̃t���[���𒴂�����
		ap->work1[X]++;										//���Z����

	ap->work1[X] %= 2;										//1�𒴂��Ȃ��悤�ɂ���
	ap->base_color[0][0] = alp_box[ ap->work1[X] ];			//�����x��ύX
}


//-------------------------------------------------------------------------------------------------------------------------------
//�͈͂̊O�ɏo����l��Ԃ�
//-------------------------------------------------------------------------------------------------------------------------------
SINT32 not_range( FLOAT min, FLOAT max )
{
	if( min < max )
		return 1;

	return 0;
}


//-------------------------------------------------------------------------------------------------------------------------------
//�����ɉ����ĉ��ʂ�ς���
//-------------------------------------------------------------------------------------------------------------------------------
FLOAT range_vol( FLOAT vol_max, FLOAT vol_rang_max, FLOAT len_num )
{
	FLOAT vol_min, vol, flip_vol;										//���������Ƃ��̉��ʂƕԂ�����
	vol_min = vol_max / vol_rang_max;									//���������Ƃ��̉��ʂ��Z�o
	flip_vol = vol_rang_max - len_num;									//�����Ŕ��]������( �����̂ق����͂����蕷���������� )
	vol = vol_min * flip_vol;											//�����������O�X�̒l�ƕ����������ʂƏ�Z

	return vol;															//�Z�o�������ʂ�Ԃ�
}

SINT32 ang_lr_check( TASK *ap, ANGLE ang_y, ANGLE target )
{
	if( ang_y > 0x0000 && 0x2000 >= ang_y || ang_y > 0xd000 )					//����
		return 0;
	else if( ang_y > 0x2000 && 0x6000 >= ang_y )								//�E
		return 2;															
	else if( ang_y > 0x6000 && 0xa000 >= ang_y )								//���
		return 0;
	else if( ang_y > 0xa000 && 0xd000 >= ang_y )								//��
		return 1;

	return 0;
}

FLOAT ang_pan( TASK *ap, TASK *actp, FLOAT lr_max, ANGLE angle, SINT32 lr )
{
	ANGLE ang, ang_y, range, angle_y, target_ang, range_y;
	ang = SOZ_atan2( ap->pos[ X ], ap->pos[ Z ], actp->pos[ X ], actp->pos[ Z ] );		//�p�x���o��
	ang_y = angle - ang;																//���̂Ƃ̊p�x�Ƃ̊p�x���o��( ���Z�Ȃ̂�angle��0�x�̖��������Ă��邩�� )
	ang_y = ang_y % 0xffff;																//������0�ɂ���
	if( ang_lr_check( ap, ang_y, ang ) == 0 )
		return 1.0f;

	if( lr == 0 )																		//0�͉E
	{
		if( ang_lr_check( ap, ang_y, ang ) == 2 )
		{
			range = 0x4000 - 0x2000;													//�͈͂��Z�o( 90�ǂ܂� )
			angle_y = range / 0x1000;													//1������̉��ʂ��Z�o
			range_y = ang_y - 0x2000;													//���x�����ׂ�( ���ʂ̊p�x�����Z�����p�x�� )
			range_y = range_y / 0x1000;													//���̊p�x�𕪊����Ă��������ׂ�
			target_ang = angle_y * range_y;												//1������̊p�x�ɕ��������l����Z

			return ( FLOAT )target_ang;													//�E��Ԃ�
		}
	}

	if( lr == 1 )																		//1�͍���
	{
		if( ang_lr_check( ap, ang_y, ang ) == 1 )										//�����Ȃ�
			return 1;																	//�����͐����^�Ȃ̂�1�����Ԃ�
	}

	return 1.0f;
}




void common_ambient( TASK *ap )
{
	ap->ambient[0] = 0.31f;
	ap->ambient[1] = 0.31f;
	ap->ambient[2] = 0.31f;
	ap->ambient[3] = 1.0f;
}



void scale_all_chenge( TASK *ap, FLOAT scale )
{
	ap->scale[X] = scale;
	ap->scale[Y] = ap->scale[X];
	ap->scale[Z] = ap->scale[Y];
}