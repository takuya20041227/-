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
#include    "../../include.h"


//--------------------------------------------------------------------------------------
//�X�t�B�A�̏��̃{�b�N�X��������
//--------------------------------------------------------------------------------------
OBJECT_SPHIRE	object_sphire[ OBJ_MAX ];				//�����蔻��̎���
OBJECT_DATA		object_data[ OBJ_MAX ]=					//�I�u�W�F�N�g�̃f�[�^
{
/*00*/{/*     name			   group		model_no			tex_no				break_model_no		break_tex_no		grp_flag			pow		specular_r	specular_g specular_b  hp	 atk	�G�t�F�N�g�̐�	�G�t�F�N�g�̃��f��  �G�t�F�N�g�̃e�N�X�`���[	���ʉ�			����	�t���O			�A�C�R��	�X�R�A*/},
/*01*/{"�����̃r��"			, BILL_GROUP,	MODEL_SUB_BILL,		TEX_BILL,			MODEL_BLEAK_BILL,	TEX_BILL,			SUB_BILL_GRP_FLAG,  4.6f,		1.3f,      1.3f,    1.3f,		260, 4500,		16,			MODEL_BILL_EFE,		TEX_BILL_EFE,				SE_BILL_BREAK,	1.7f,	NO_FLAG			,	1,		10000	},
/*02*/{"�΂̎�"				, CAR_GROUP,	MODEL_CAR,			TEX_CAR,			MODEL_CAR,			TEX_CAR,			CAR_GRP_FLAG,		1.0f,       1.3f,      1.3f,    1.3f,		260, 3800,		 4,			MODEL_CAR_EFE,		TEX_CAR_EFE ,				SE_KLAXON_1,	1.0f,	CAR_FLAG		,	3,		13000	},
/*03*/{"���̎�"				, CAR_GROUP,	MODEL_CAR,			TEX_CAR_B,			MODEL_CAR,			TEX_CAR_B,			CAR_GRP_FLAG,		1.0f,       1.3f,      1.3f,    1.3f,		260, 3500,		 4,			MODEL_CAR_EFE,		TEX_CAR_EFE ,				SE_KLAXON_1,	1.0f,	CAR_FLAG		,	3,		13000	},
/*04*/{"���̎�"				, CAR_GROUP,	MODEL_CAR,			TEX_CAR_W,			MODEL_CAR,			TEX_CAR_W,			CAR_GRP_FLAG,		1.0f,       1.3f,      1.3f,    1.3f,		260, 3500,		 4,			MODEL_CAR_EFE,		TEX_CAR_EFE ,				SE_KLAXON_1,	1.0f,	CAR_FLAG		,	3,		13000	},
/*05*/{"�ԃX�^�["			, CAR_GROUP,	MODEL_ROADSTAR,		TEX_ROADSTAR_R,		MODEL_ROADSTAR,		TEX_ROADSTAR_R,		CAR_GRP_FLAG,		6.5f,       2.1f,      2.1f,    2.1f,		260, 3500,		 4,			MODEL_CAR_EFE,		TEX_CAR_EFE ,				SE_KLAXON_2,	1.0f,	CAR_FLAG		,	4,		15000	},
/*06*/{"���X�^�["			, CAR_GROUP,	MODEL_ROADSTAR,		TEX_ROADSTAR_B,		MODEL_ROADSTAR,		TEX_ROADSTAR_B,		CAR_GRP_FLAG,		6.5f,       2.1f,      2.1f,    2.1f,		260, 3500,		 4,			MODEL_CAR_EFE,		TEX_CAR_EFE ,				SE_KLAXON_2,	1.0f,	CAR_FLAG		,	4,		15000	},
/*07*/{"���X�^�["			, CAR_GROUP,	MODEL_ROADSTAR,		TEX_ROADSTAR_W,		MODEL_ROADSTAR,		TEX_ROADSTAR_W,		CAR_GRP_FLAG,		4.6f,       1.9f,      2.1f,    1.9f,		260, 3500,		 4,			MODEL_CAR_EFE,		TEX_CAR_EFE ,				SE_KLAXON_2,	1.0f,	CAR_FLAG		,	4,		15000	},
/*08*/{"��̃^���["			, BILL_GROUP,	MODEL_TOWER,		TEX_TOWER,			MODEL_TOWER,		TEX_TOWER,			SUB_BILL_GRP_FLAG,	4.6f,       1.9f,      2.1f,    1.9f,		260, 3500,		 4,			MODEL_BILL_EFE,		TEX_BILL_EFE,				SE_BILL_BREAK,	2.0f,	ID_CHENGE_FLAG	,	2,		10000	},
/*09*/{"�e���g"				, BILL_GROUP,	MODEL_TENTO,		TEX_TENTO,			MODEL_TENTO,		TEX_TENTO,			SUB_BILL_GRP_FLAG,	4.6f,       1.9f,      2.1f,    1.9f,		260, 3500,		 4,			MODEL_BILL_EFE,		TEX_BILL_EFE,				SE_BILL_BREAK,	2.0f,	ID_CHENGE_FLAG	,	11,		10000	},
/*10*/{"���j�^�[�@�B"		, MEKA_GROUP,	MODEL_SCREEN_MEKA,	TEX_SCREEN_MEKA,	MODEL_SCREEN_MEKA,	TEX_SCREEN_MEKA,	SUB_BILL_GRP_FLAG,	4.6f,       1.9f,      2.1f,    1.9f,		260, 3500,		 4,			NULL,				NULL,						SE_BILL_BREAK,	2.0f,	WOOD_FLAG		,	7,		0		},
/*11*/{"�{�^���t���@�B"		, MEKA_GROUP,	MODEL_BUTTON_MEKA,	TEX_BUTTON_MEKA,	MODEL_BUTTON_MEKA,	TEX_BUTTON_MEKA,	SUB_BILL_GRP_FLAG,	4.6f,       1.9f,      2.1f,    1.9f,		260, 3500,		 4,			NULL,				NULL,						SE_BILL_BREAK,	2.0f,	WOOD_FLAG		,	6,		0		},
/*12*/{"��"					, MEKA_GROUP,	MODEL_WOOD,			TEX_WOOD,			MODEL_WOOD_EFE,		TEX_WOOD_EFE,		SUB_BILL_GRP_FLAG,	4.6f,       1.9f,      2.1f,    1.9f,		260, 5000,		16,			MODEL_WOOD_EFE,		TEX_WOOD_EFE,				SE_BILL_BREAK,	2.0f,	WOOD_FLAG		,	8,		11000	},
/*13*/{"�J�c�I�̃I�u�W�F"	, FISH_GROUP,	MODEL_BONITO,		TEX_BONITO,			MODEL_BONITO,		TEX_BONITO,			SUB_BILL_GRP_FLAG,	4.6f,       1.9f,      2.1f,    1.9f,		260, 5500,		 8,			MODEL_BONITO,		TEX_BONITO	,				SE_FISH,		1.5f,	BONITO_FLAG		,	5,		15000	},
/*14*/{"�w�Z"				, SCHOOL_GROUP,	MODEL_SCHOOL,		TEX_SCHOOL,			MODEL_BREAK_SCHOOL,	TEX_SCHOOL,			SCHOOL_GRP_FLAG,	0.0f,       1.0f,      1.0f,    1.0f,		840, 6000,		32,			MODEL_BILL_EFE,		TEX_SCHOOL,					SE_BILL_BREAK,	2.0f,	NO_FLAG	,			12,		30000	},
/*15*/{"���S�̃}���V����"	, HOUSE_GROUP,	MODEL_LOGO_HOUSE,	TEX_LOGO_HOUSE,		MODEL_LOGO_HOUSE,	TEX_LOGO_HOUSE,		SCHOOL_GRP_FLAG,	0.0f,       1.0f,      1.0f,    1.0f,		840, 6000,		16,			MODEL_BILL_EFE,		TEX_SCHOOL,					SE_BILL_BREAK,	2.0f,	LOGO_HOUSE_FLAG	,	13,		20000	},
/*16*/{"���ԏ�"				, HOUSE_GROUP,	MODEL_PARKING,		TEX_PARKING,		MODEL_PARKING,		TEX_PARKING,		MAIN_BILL_GRP_FLAG,	1.0f,       1.0f,      1.0f,    1.0f,		840, 5500,		16,			MODEL_BILL_EFE,		TEX_SCHOOL,					SE_BILL_BREAK,	2.0f,	LOGO_HOUSE_FLAG	,	1,		20000	},
/*17*/{"�w��"				, HERI_GROUP,	MODEL_HERI,			TEX_HERI,			MODEL_HERI,			TEX_HERI,			MAIN_BILL_GRP_FLAG,	1.0f,       1.0f,      1.0f,    1.0f,		540, 6500,		 1,			MODEL_PROPELLER,	TEX_HERI,					SE_BILL_BREAK,	2.0f,	ID_CHENGE_FLAG	,	9,		20000	},
/*18*/{"�l�R�R"				, CAT_GROUP,	MODEL_CAT_MOUNTEN,	TEX_CAT_MOUNTEN,	MODEL_CAT_MOUNTEN,	TEX_CAT_MOUNTEN,	MAIN_BILL_GRP_FLAG,	1.0f,       1.0f,      1.0f,    1.0f,		1240, 8500,		 16,			MODEL_CAT,			TEX_CAT_GRY,				SE_BILL_BREAK,	2.0f,	ID_CHENGE_FLAG	,	10,		40000	},
																																																																													
/*18*/{"���C���r��"			, BILL_GROUP,	MODEL_MAIN_BILL,	TEX_BILL,			MODEL_MAIN_BILL,	TEX_BILL,			SUB_BILL_GRP_FLAG,	4.6f,       1.9f,      2.1f,    1.9f,		40,  1800,		 4,			MODEL_BILL_EFE,		TEX_BILL_EFE,				SE_BILL_BREAK,	2.0f,	NO_FLAG			,	1,		1000	},
};



void sphire_set_case( TASK *ap )
{
	switch( ap->ID )
	{
		case 1:				//�����̃r��
			object_sphire_set( ap->ID, 0, 356.0f, 0.0f, 356.0f );		//�X�t�B�A�̃Z�b�g
			break;

		case 8:
			object_sphire_set( ap->ID, 0, 356.0f, 0.0f, 356.0f );		//�X�t�B�A�̃Z�b�g
			break;

		case 9:
			object_sphire_set( ap->ID, 0, 356.0f, 0.0f, 356.0f );		//�X�t�B�A�̃Z�b�g
			break;

		case 10:		//���j�^�[�t���@�B
			object_sphire_set( ap->ID, 0, 356.0f, 0.0f, 356.0f );		//�X�t�B�A�̃Z�b�g
			break;

		case 11:		//�{�^���t���@�B
			object_sphire_set( ap->ID, 0, 356.0f, 0.0f, 64.0f );		//�X�t�B�A�̃Z�b�g
			break;

		case 12:			//��
			object_sphire_set( ap->ID, 0,  512.0f, 0.0f, 256.0f );		//�X�t�B�A�̃Z�b�g
			object_sphire_set( ap->ID, 1, 256.0f, 256.0f, 512.0f );		//�X�t�B�A�̃Z�b�g
			break;

		case 13:			//�J�c�I
			object_sphire_set( ap->ID, 0, 340.0f, 0.0f, 340.0f );		//�X�t�B�A�̃Z�b�g
			break;

		case 14:
			object_sphire_set( ap->ID, 0, 2048.0f, 0.0f, 2048.0f );		//�X�t�B�A�̃Z�b�g
			break;

		case 15:
			object_sphire_set( ap->ID, 0, 800.0f, 0.0f, 800.0f );		//�X�t�B�A�̃Z�b�g
			break;

		case 17:
			object_sphire_set( ap->ID, 0, 256.0f, 0.0f, 256.0f );		//�X�t�B�A�̃Z�b�g
			break;

		case 18:			//�l�R�R
			object_sphire_set( ap->ID, 0, 2048.0f, 0.0f, 2048.0f );		//�X�t�B�A�̃Z�b�g
			break;
	}

}

//--------------------------------------------------------------------------------------
//�X�t�B�A�̏��̃{�b�N�X��������
//--------------------------------------------------------------------------------------
void object_sphire_init( void )
{
	SINT32 i, fi;									//�z����񂷕ϐ��ƃ|�C���^�[�ƃX�t�B�A�̒��g���񂷕ϐ�
	OBJECT_SPHIRE *op;								//�I�u�W�F�N�g�̃|�C���^�[
	op = object_sphire;
	for( i = 0; i < OBJ_MAX; i++ )					//�����蔻��̃}�b�N�X�܂ŉ�
	{
		for( fi = 0; fi < OBJ_SPHIRE_MAX; fi++ )	//�X�t�B�A�̔z�񕪉�
		{
			op->sphire[ fi ] = NULL;				//�X�t�B�A�̑傫����������
			op->sphire_height_min[ fi ] = NULL;		//�X�t�B�A�̍����̍ŏ��l��������
			op->sphire_height_max[ fi ] = NULL;		//�X�t�B�A�̍����̍ő�l��������
		}
		op++;										//���̃A�h���X�Ɉړ�
	}
}


//--------------------------------------------------------------------------------------
//�X�t�B�A�̏�����������
//--------------------------------------------------------------------------------------
void object_sphire_set( SINT32 id, SINT32 sphire_no, FLOAT sphire, FLOAT height_min, FLOAT height_max )
{
	OBJECT_SPHIRE *op;
	op = &object_sphire[ id ];							//�ǂ��̃A�h���X�ɓ���邩��������
	FLOAT min, max;
	if( op->sphire[ sphire_no ] != 0.0f )				//�����X�t�B�A�̒��g�����łɓ����Ă�����		
		return;											//����ȏ���s���Ȃ��悤�ɂ���

	min = height_min;
	max = height_max;
	if( op->sphire[ 0 ] != NULL )						//����0�Ԃɂ��łɐݒ肳��Ă���c��͏���ɐݒ肷��
	{
		min = op->sphire_height_max[sphire_no - 1];		//�ŏ��͈�O�̍ő�
		max = op->sphire_height_max[sphire_no - 1] + sphire;		//��O�̍ő�ɃX�t�B�A�����Z
	}

	op->sphire[ sphire_no ] = sphire;					//�X�t�B�A��ݒ�
	op->sphire_height_min[ sphire_no ] = min;	//�X�t�B�A�̍����Ƃ����ݒ�
	op->sphire_height_max[ sphire_no ] = max;	//�X�t�B�A�̒Ⴂ�Ƃ����ݒ�
}

void sphire_set_sub( SINT32 id, SINT32 sphire_no, FLOAT sphire )
{
	object_sphire_set( id, sphire_no, sphire, 0.0f, 0.0f );
}


//--------------------------------------------------------------------------------------
//�I�u�W�F�N�g���ǂ������ׂ�
//--------------------------------------------------------------------------------------
SINT32 object_check( TASK *ap )
{
	if( ap->ID == 0 )		//ID��0�Ȃ炠����x�X�t�B�A�����Ă���
		return 1;			//�����I�u�W�F�N�g����Ȃ��Ȃ�1��Ԃ�
		
	return 0;				//�����I�u�W�F�N�g�Ȃ�0��Ԃ�
}


//--------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̃X�t�B�A�𒲂ׂ�
//--------------------------------------------------------------------------------------
SINT32 sphire_set( TASK *ap, TASK *actp )
{
	SINT32 i, sphire_id;					//for���p�̕ϐ��Ƃǂ̔z����g�������i�[����ϐ�
	OBJECT_SPHIRE * os;						//�X�t�B�A�̃|�C���^�[
	sphire_id = 0;							//���������Ă���
	os = &object_sphire[ actp->ID ];		//�A�h���X��������	
	for( i = 0; i < OBJ_SPHIRE_MAX; i++ )	//�z����Ԃ��
		if( os->sphire_height_min[ i ] < ap->pos[Y] && ap->pos[Y] < os->sphire_height_max[ i ] )		//���ɓ����Ă�����
		{
			sphire_id = i;					//�ǂ��̃X�t�B�A���g�������܂�
			break;							//����ȏ�񂳂Ȃ��悤�ɂ���
		}
	return sphire_id;						//�g���ꏊ�𑗂��Ă�����
}

//--------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̃X�t�B�A������
//--------------------------------------------------------------------------------------
FLOAT sphire_point( TASK *ap, TASK *actp )
{
	SINT32 point;							//�ǂ̃X�t�B�A���g�������߂�
	OBJECT_SPHIRE * os;						//�X�t�B�A�̃|�C���^�[

	os = &object_sphire[ actp->ID ];		//�A�h���X��������	
	point =  sphire_set( ap, actp );		//�ǂ��̔z�񂪓K���Ă��邩���ׂ�
	if( os->sphire[ point ] == 0.0f || actp->ID == 0 )	//�X�t�B�A��ID��0�Ȃ�
		return 0.0f;						//�����͒ʂ��Ȃ�
	
	return os->sphire[ point ];				//�X�t�B�A��Ԃ�
}


FLOAT sphire_get( TASK *ap )
{
	FLOAT sa_z, sa_x, abs_sax, abs_saz;
	sa_x = ap->pos[X] - jiki->pos[X]; 
	sa_z = ap->pos[Z] - jiki->pos[Z];
	abs_sax = ( FLOAT )fabs( ( DOUBLE )sa_x );			//��Βl�𒲂ׂ�
	abs_saz = ( FLOAT )fabs( ( DOUBLE )sa_z );			//��Βl�𒲂ׂ�
	//for( actp = ap_start; actp != NULL; actp = actp->next )
	//	if( actp->task_group == SHOT_GROUP || actp->task_group == HAND_GROUP || actp->task_group == BREAK_OBJECT_GROUP )
	//		if( sa_check_smaller( ap->pos[X], actp->pos[X], abs_sax ) != 0 && sa_check_smaller( ap->pos[Z], actp->pos[Z], abs_saz ) != 0 )		//���������@��菬����������
	//			return sphire_point( actp, ap );		//�r�[���̋����ŃX�t�B�A��Ԃ�

	return sphire_point( jiki, ap );					//���@�̋����ŃX�t�B�A��Ԃ�
}


//--------------------------------------------------------------------------------------
//���@�p�̔���`�F�b�N
//--------------------------------------------------------------------------------------
SINT32 jiki_hit_check( TASK *ap, TASK *actp )
{
	SINT32 point;							//�ǂ̃X�t�B�A���g�������߂�
	FLOAT sa_x, sa_y, sa_z;					//�݂��̍��𑪂�
	FLOAT length;							//���̍����烌���O�X���o��
	FLOAT sphire_pos_y, min_hight;						//�g���X�t�B�A�̍��W������					
	OBJECT_SPHIRE * os;						//�X�t�B�A�̃|�C���^�[

	os = &object_sphire[ actp->ID ];		//�A�h���X��������	
	point =  sphire_set( ap, actp );		//�ǂ��̔z�񂪓K���Ă��邩���ׂ�
	if( os->sphire[ point ] == 0.0f || actp->ID == 0 )	//�X�t�B�A��ID��0�Ȃ�
		return 0;							//�����͒ʂ��Ȃ�

	min_hight = ( os->sphire_height_max[ point ] - os->sphire_height_min[ point ] ) / 2;		//�����̐^�񒆂𒲂ׂ�	
	min_hight = min_hight / 2;
	sphire_pos_y = os->sphire_height_min[ point ] + min_hight;
	sa_x = ap->pos[X] - actp->pos[X];		//���̍��𒲂ׂ�
	sa_y = ap->pos[Y] - ( actp->pos[Y] + sphire_pos_y );		//�c�̍��𒲂ׂ�
	sa_z = ap->pos[Z] - actp->pos[Z];		//�O��̍��𒲂ׂ�

	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );	//���������o��

	if( length <= ( ap->sphire + os->sphire[ point ] ) )		//���������O�X���l����Ȃ�
		return 1;			//�q�b�g��Ԃ�

	return 0;				//0��Ԃ�
}


//--------------------------------------------------------------------------------------
//�I�u�W�F�N�g���m�̔���
//--------------------------------------------------------------------------------------
SINT32 object_hit_check( TASK *ap, TASK *actp )
{
	SINT32 point, act_point;				//�ǂ̃X�t�B�A���g�������߂�
	FLOAT sa_x, sa_y, sa_z;					//�݂��̍��𑪂�
	FLOAT length;							//���̍����烌���O�X���o��
	FLOAT sphire_pos_y, act_pos_y;			//�g���X�t�B�A�̍��W������					
	OBJECT_SPHIRE * os, *actos;				//�X�t�B�A�̃|�C���^�[

	os = &object_sphire[ actp->ID ];		//�A�h���X��������	
	point =  sphire_set( ap, actp );		//�ǂ��̔z�񂪓K���Ă��邩���ׂ�
	if( os->sphire[ point ] == 0.0f || actp->ID == 0 )	//�X�t�B�A��ID��0�Ȃ�
		return 0;							//�����͒ʂ��Ȃ�

	actos = &object_sphire[ ap->ID ];		//�A�h���X��������	
	act_point =  sphire_set( ap, actp );	//�ǂ��̔z�񂪓K���Ă��邩���ׂ�
	if( actos->sphire[ point ] == 0.0f || ap->ID == 0 )	//�X�t�B�A��ID��0�Ȃ�
		return 0;							//�����͒ʂ��Ȃ�

	sphire_pos_y = ( os->sphire_height_max[ point ] - os->sphire_height_min[ point ] ) / 2;		//�����̐^�񒆂𒲂ׂ�	
	sphire_pos_y = os->sphire_height_max[ point ];

	act_pos_y = ( actos->sphire_height_max[ act_point ] - actos->sphire_height_min[ act_point ] ) / 2;		//�����̐^�񒆂𒲂ׂ�	
	act_pos_y = os->sphire_height_max[ point ];

	sa_x = ap->pos[X] - actp->pos[X];		//���̍��𒲂ׂ�
	sa_y = ( ap->pos[Y] + act_pos_y ) - ( actp->pos[Y] + sphire_pos_y );		//�c�̍��𒲂ׂ�
	sa_z = ap->pos[Z] - actp->pos[Z];		//�O��̍��𒲂ׂ�

	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );	//���������o��

	if( length <= ( actos->sphire[ act_point ] + os->sphire[ point ] ) )		//���������O�X���l����Ȃ�
		return 1;			//�q�b�g��Ԃ�

	return 0;				//0��Ԃ�
}

SINT32 sphire_hit_check( TASK *ap, TASK *actp )
{
	FLOAT sa_x, sa_y, sa_z;																		//�݂��̍��𑪂�
	FLOAT length;																				//���̍����烌���O�X���o��
	FLOAT sphire_pos_y, min_hight;																//�g���X�t�B�A�̍��W������
	sa_x = ap->pos[X] - actp->pos[X];															//���̍��𒲂ׂ�
	sa_y = ap->pos[Y] - actp->pos[Y];														//�c�̍��𒲂ׂ�
	sa_z = ap->pos[Z] - actp->pos[Z];															//�O��̍��𒲂ׂ�
	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );				//���������o��

	if( length <= ( ap->sphire + actp->sphire ) )												//���������O�X���l����Ȃ�
		return 1;																				//�q�b�g��Ԃ�

	return 0;																					//0��Ԃ�
}


//--------------------------------------------------------------------------------------
//�X�t�B�A�̓����蔻����`�F�b�N���Ēl��Ԃ�
//--------------------------------------------------------------------------------------
SINT32 kawa_3d_hit_check( TASK * ap, TASK * actp )
{
	SINT32 scene, ob;
	ob = object_check( ap ) + object_check( actp );
	switch( ob )
	{
		case 0: scene =  0; break;								//�ǂ�����\���̂ɃX�t�B�A������

		case 1: scene = 10; break;								//�ǂ��炩�ɃX�t�B�A������

		case 2: scene = 20; break;								//���݂��ɃX�t�B�A������
	}
	switch( scene )													
	{																
		case 0:													//�ǂ������X�t�B�A���\���̂ɓ����Ă���
			if( object_hit_check( ap, actp ) != 0 )					
				return 1;											
			break;													
																	
		case 10:												//�Е����X�t�B�A�������Ă���悤
			if( jiki_hit_check( ap, actp ) != 0 )				//�������Ă��邩�ǂ�����Ԃ�
				return 1;
			break;

		case 20:
			if( sphire_hit_check( ap, actp ) != 0 )				//�X�t�B�A�[���ݒ肳��Ă��铯�m�Ȃ�
				return 1;
			break;
	}
	
	return 0;
}


//-------------------------------------------------------------------------------------------------------------------------
//�X�t�B�A�ō�������
//-------------------------------------------------------------------------------------------------------------------------
SINT32 range_sphire( TASK *ap, FLOAT sphire, TASK *actp )
{
	FLOAT sa_x, sa_y, sa_z;					//�݂��̍��𑪂�
	FLOAT length;							//���̍����烌���O�X���o��

	sa_x = ap->pos[X] - actp->pos[X];		//���̍��𒲂ׂ�
	sa_y = ap->pos[Y] - actp->pos[Y];		//�c�̍��𒲂ׂ�
	sa_z = ap->pos[Z] - actp->pos[Z];		//�O��̍��𒲂ׂ�

	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );	//���������o��

	if( length <= actp->sphire + sphire )		//���������O�X���l����Ȃ�
		return 1;			//�q�b�g��Ԃ�

	return 0;				//0��Ԃ�
}

//-------------------------------------------------------------------------------------------------------------------------
//�X�t�B�A�ō�������( object_data�� )
//-------------------------------------------------------------------------------------------------------------------------
SINT32 object_range_sphire( TASK *ap, FLOAT sphire, TASK *actp )
{
	FLOAT sa_x, sa_y, sa_z;					//�݂��̍��𑪂�
	FLOAT length;							//���̍����烌���O�X���o��

	sa_x = ap->pos[X] - actp->pos[X];		//���̍��𒲂ׂ�
	sa_y = ap->pos[Y] - actp->pos[Y];		//�c�̍��𒲂ׂ�
	sa_z = ap->pos[Z] - actp->pos[Z];		//�O��̍��𒲂ׂ�

	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );	//���������o��

	if( length <= actp->sphire + sphire )		//���������O�X���l����Ȃ�
		return 1;			//�q�b�g��Ԃ�

	return 0;				//0��Ԃ�
}
//-------------------------------------------------------------------------------------------------------------------------
//�����O�X��n��
//-------------------------------------------------------------------------------------------------------------------------
FLOAT length_return( TASK *ap, FLOAT sphire, TASK *actp )
{
	FLOAT sa_x, sa_y, sa_z;					//�݂��̍��𑪂�
	FLOAT length;							//���̍����烌���O�X���o��

	sa_x = ap->pos[X] - actp->pos[X];		//���̍��𒲂ׂ�
	sa_y = ap->pos[Y] - actp->pos[Y];		//�c�̍��𒲂ׂ�
	sa_z = ap->pos[Z] - actp->pos[Z];		//�O��̍��𒲂ׂ�
	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );	//���������o��

	return length;							//�����O�X��Ԃ�
}


#if 0
FLOAT sa_x, sa_y, sa_z;					//�݂��̍��𑪂�
	FLOAT length;							//���̍����烌���O�X���o��

	sa_x = ap->pos[X] - actp->pos[X];		//���̍��𒲂ׂ�
	sa_y = ap->pos[Y] - actp->pos[Y];		//�c�̍��𒲂ׂ�
	sa_z = ap->pos[Z] - actp->pos[Z];		//�O��̍��𒲂ׂ�

	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );	//���������o��
	if( length <= ( ap->sphire + actp->sphire ) )	//���������O�X���l����Ȃ�
		return 1;			//�q�b�g��Ԃ�

	return 0;
#endif