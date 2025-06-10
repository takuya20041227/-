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


//----------------------------------------------------------------------------------------------------
//�V�[�P���X����ǂ��ă}�b�v�ɐݒu����
//----------------------------------------------------------------------------------------------------
void object_seq_set( TASK *ap )
{
	SINT32	id;
	FLOAT	x, y, z, scale, magni_hp, magni_atk;
	ANGLE	ang_x, ang_y;
	x = *ap->f_table++;						//���̍��W�����o��
	y = *ap->f_table++;						//�c�̍��W�����o��
	z = *ap->f_table++;						//�O��̍��W�����o��
	ang_x = ( ANGLE )*ap->f_table++;		//�p�x����������o��
	ang_y = ( ANGLE )*ap->f_table++;		//�p�x����������o��
	scale = *ap->f_table++;					//�T�C�Y�����o��
	magni_hp  = *ap->f_table++;				//�q�b�g�|�C���g�̔{�������o��
	magni_atk = *ap->f_table++;				//�U���̔{�������o��
	id = ( SINT32 )*ap->f_table++;			//���ʔԍ������o��
	object_start( x, y, z, ang_x, ang_y, scale, magni_hp, magni_hp, id );	//�r��
}

void car_seq_set( TASK *ap )
{
	SINT32	id;								//���ʔԍ��̕ϐ�
	FLOAT	x, y, z, scale, magni_hp, magni_atk;	//���W�ƃT�C�Y�Ɣ{���̕ϐ�
	ANGLE	ang_x, ang_y;					//�p�x�̕ϐ�
	//id = ( SINT32 )*ap->f_table++;		//���ʔԍ������o��
	x = *ap->f_table++;						//���̍��W�����o��
	y = *ap->f_table++;						//�c�̍��W�����o��
	z = *ap->f_table++;						//�O��̍��W�����o��
	ang_x = ( ANGLE )*ap->f_table++;		//�p�x����������o��
	ang_y = ( ANGLE )*ap->f_table++;		//�p�x����������o��
	scale = *ap->f_table++;					//�T�C�Y�����o��
	magni_hp  = *ap->f_table++;				//�q�b�g�|�C���g�̔{�������o��
	magni_atk = *ap->f_table++;				//�U���̔{�������o��
	id = ( SINT32 )*ap->f_table++;			//���ʔԍ������o��
	car_start( x, y, z, ang_x, ang_y, scale, magni_hp, magni_hp, id );		//��
}


void parking_seq_set( TASK *ap )
{
	SINT32	id;								//���ʔԍ��̕ϐ�
	FLOAT	x, y, z, scale, magni_hp, magni_atk;	//���W�ƃT�C�Y�Ɣ{���̕ϐ�
	ANGLE	ang_x, ang_y;					//�p�x�̕ϐ�
	//id = ( SINT32 )*ap->f_table++;		//���ʔԍ������o��
	x = *ap->f_table++;						//���̍��W�����o��
	y = *ap->f_table++;						//�c�̍��W�����o��
	z = *ap->f_table++;						//�O��̍��W�����o��
	ang_x = ( ANGLE )*ap->f_table++;		//�p�x����������o��
	ang_y = ( ANGLE )*ap->f_table++;		//�p�x����������o��
	scale = *ap->f_table++;					//�T�C�Y�����o��
	magni_hp  = *ap->f_table++;				//�q�b�g�|�C���g�̔{�������o��
	magni_atk = *ap->f_table++;				//�U���̔{�������o��
	id = ( SINT32 )*ap->f_table++;			//���ʔԍ������o��
	parking_start( x, y, z, ang_x, ang_y, scale, magni_hp, magni_hp, id );		//��
}

void heri_seq_set( TASK *ap )
{
	SINT32	id;								//���ʔԍ��̕ϐ�
	FLOAT	x, y, z, scale, magni_hp, magni_atk;	//���W�ƃT�C�Y�Ɣ{���̕ϐ�
	ANGLE	ang_x, ang_y;					//�p�x�̕ϐ�
	//id = ( SINT32 )*ap->f_table++;		//���ʔԍ������o��
	x = *ap->f_table++;						//���̍��W�����o��
	y = *ap->f_table++;						//�c�̍��W�����o��
	z = *ap->f_table++;						//�O��̍��W�����o��
	ang_x = ( ANGLE )*ap->f_table++;		//�p�x����������o��
	ang_y = ( ANGLE )*ap->f_table++;		//�p�x����������o��
	scale = *ap->f_table++;					//�T�C�Y�����o��
	magni_hp  = *ap->f_table++;				//�q�b�g�|�C���g�̔{�������o��
	magni_atk = *ap->f_table++;				//�U���̔{�������o��
	id = ( SINT32 )*ap->f_table++;			//���ʔԍ������o��
	heri_start( x, y, z, ang_x, ang_y, scale, magni_hp, magni_hp, id );		//��
}


//----------------------------------------------------------------------------------------------------
//�V�[�P���X����ǂ��ă}�b�v�ɐݒu����
//----------------------------------------------------------------------------------------------------
void sequence_set_object_exec( TASK *ap )
{
	if( *ap->f_table != NULL )
		switch( ( SINT32 )*ap->f_table++ )							//�V�[�P���X�̒�����P�[�X���擾����
		{
			case 1:	 case 8: case 9: case 10:case 11: case 12: case 13: case 14: case 15: case 18:
				object_seq_set( ap );	break;						//�I�u�W�F�N�g

			case 2: case 3: case 4:	case 5: case 6: case 7:
				car_seq_set( ap );		break;						//��( ��, ��, �� )

			case 16:
				parking_seq_set( ap );	break;

			case 17:
				heri_seq_set( ap );		break;
		}

	if( *ap->f_table == -999 )
		TASK_end( ap );
}

void sequence_set_object_start( void )
{
	TASK* ap;
	ap = TASK_start( sequence_set_object_exec, MANE_GROUP, "�}�b�v�ɃI�u�W�F�N�g��ݒu" );
	ap->f_table = sequence_box;			//�V�[�P���X
}


