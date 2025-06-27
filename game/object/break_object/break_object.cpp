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
#include    "../../include.h"

//--------------------------------------------------------------------------------
//�O���ϐ�
//--------------------------------------------------------------------------------
SINT32 object_id = 1;									//���j�[�N�i���o�[���v������̂Ɏg��( �������K�{ )

//--------------------------------------------------------------------------------
//�I�u�W�F�N�g���m�̃q�b�g���m�F����
//--------------------------------------------------------------------------------
void attack_hit_check( TASK *ap, OBJECT_DATA *op )
{
	TASK *actp;
	SINT32 group_box[ 3 ] = { MAIN_BILL_GROUP, MAIN_COMP_GROUP };
	SINT32 i;
	for( actp = ap_start; actp != NULL; actp = actp->next )
		if( jiki_hit_check( ap, actp ) != 0 )			//����͒��ڃq�b�g�m�F����
			for( i = 0; i < 2; i++ )
				if( actp->task_group == group_box[ i ] )
				{
					actp->HP -= ap->ATK;
					score += op->score;
					switch( op->object_group )
					{
						case CAR_GROUP:
							SOZ_play_se( SE_BILL_BREAK, op->se_vol, 1, 1.0f );
							break;

						default:
							SOZ_play_se( op->se_no, op->se_vol, 1, 1.0f );
							break;
					}

					if( ap->ID == 20 )
						alien_start( ap->fwork1[X], ap->fwork1[Y], ap->fwork1[Z], ap->ang[X], ap->angle[Y], ap->scale[X], ap->fwork8[X], ap->fwork8[Y], ap->ID );

					beam_bom_start( ap->pos[X], ap->pos[Y], ap->pos[Z], F_Rand2( 3.0f, 6.0f ) );
					hit_particle_occurrence( ap );
					TASK_end( ap );
					return;
				}
}


void break_object_exec( TASK *ap )
{
	OBJECT_DATA *op;
	op = &object_data[ ap->ID ];
	ap->sphire = sphire_get( ap );
	if( ap->SWITCH == 0 )
		ap->vec[Y] -= ap->acc[Y];
	ap->pos[X] += ap->vec[X];
	ap->pos[Y] += ap->vec[Y];
	ap->pos[Z] += ap->vec[Z];
	if( ap->pos[ Y ] <= GROUND )
	{
		ap->pos[ Y ] = GROUND;
		ap->ang[Z] &= 0x4000;
		ap->vec[X] = 0.0f;
		ap->vec[Y] = 0.0f;
		ap->vec[Z] = 0.0f;
	}
	else
	{
		ap->ang[X] += 0x40;									//�����Ă�Ԃ͂��˂��ˉ��
		ap->ang[ Z ] += 0x80;								//�����Ă�Ԃ͂��˂��ˉ��
	}

	if( game_type != 101 && game_type != 11 && game_type != 501 )				//�Q�[���ł��^�C�g����ʂł��������
	{
		ap->TIMER++;
		if( ap->TIMER > TIME_S * 4  )
			if( ap->TIMER % 8 == 0 )
				ap->base_color[0][0] -= 0x4;

		if( ap->base_color[ 0 ][ 0 ] <= 0 )
		{
			TASK_end( ap );
			return;
		}
		ap->pri++;
	}

	if( ap->SWITCH != 0 )									//������0�ȊO�Ȃ�
		attack_hit_check( ap, op );							//���C���r���ɓ�����

	task_id_checge( ap, ap->SWITCH );								//������J�����O
		
}

void break_object_start( DEFAULT_ARGUMENT, FLOAT atk, SINT32 id )
{
	TASK *ap;
	OBJECT_DATA *op;
	op = &object_data[ id ];
	ap = TASK_start_MODEL( break_object_exec, BREAK_OBJECT_GROUP, op->model_no, op->tex_no, "��ꂽ�I�u�W�F�N�g" );
	ap->grp_mode =  op->grp_flag;	//�t���O������
	specular_sturct_set( ap, op );	//���Ɋւ���X�e�[�^�X������
	common_ambient( ap );
	scale_all_chenge( ap, op->scale );
	ap->emissive[0] = 0.35f;
	ap->emissive[1] = 0.35f;
	ap->emissive[2] = 0.35f;
	ap->pos[X] = x;					//���W(x
	ap->pos[Y] = y;					//���W(y
	ap->pos[Z] = z;					//���W(z
	ap->vec[X] = vec_x;				//�x�N�g��(x
	ap->vec[Y] = vec_y;				//�x�N�g��(y
	ap->vec[Z] = vec_z;				//�x�N�g��(z
	ap->acc[Y] = 0.35f;				//
	ap->sphire = 128.0f;			//�X�t�B�A�̑傫�����m�肳����
	ap->unique_id = object_id;		//�I�u�W�F�N�g���ւ̎��ʔԍ�
	ap->GROUP  = op->object_group;	//�ǂ̃O���[�v���`����
	ap->ATK = ( SINT32 )( op->atk * atk );	//�U����
	ap->ID  = id;					//���ʔԍ�
	ap->pri = OBJECT_PRI * WP;
}