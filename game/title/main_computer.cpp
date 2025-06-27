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


//-----------------------------------------------------------------------------------------------------------------------
//���C���R���s���[�^�[
//-----------------------------------------------------------------------------------------------------------------------
void earth_exec( TASK *ap )
{
	ap->ang[Y] -= 0x80;
}
void sub_parts_exec( TASK *ap )
{
	ap->ang[Y] += ap->ang_spd[Y];
}

void main_computer_exec( TASK *ap )
{
	ap->sphire = sphire_get( ap );
	if( ap->work1[X] != 0 )											//���@�ƂԂ�������0�ȊO�ɂȂ�	
	{
		tex_title_reset();                                          //�^�C�g���ł����g���ĂȂ��e�N�X�`���[������
        model_title_reset();                                        //�^�C�g���ł����g���ĂȂ����f��������
		game_type = 100;
		record_fram = 0;											//���R�[�h�̃t���[��������������
		TASK_all_init();
		return;
	}
}

void main_computer_start( void )
{
	TASK *ap, *op, *ep;		//�e�Ɨւ����ƒn��
	ap = TASK_start_MODEL( main_computer_exec, MAIN_COMP_GROUP, MODEL_COMPUTER, TEX_COMPUTER, "�@�B" );		//���C���̋@�B
	ap->grp_mode = MAIN_BILL_GRP_FLAG;
	ap->ID = OBJ_MAX - 2;						//���C���r���̈�O�ɐݒ肵�Ă���
	object_sphire_set( ap->ID, 0, 3024.0f, 0.0f, 1024.0f );
	object_sphire_set( ap->ID, 1, 1024.0f, 1024.0f, 2048.0f );
	object_sphire_set( ap->ID, 2, 1024.0f, 2048.0f, 3072.0f );
	ap->pos[ X ] = 25000.0f;
	ap->pos[ Y ] = GROUND;
	ap->pos[ Z ] = 25500.0f;
	ap->HP = 1;
	ap->pri = OBJECT_PRI * WP;
	common_ambient( ap );
	
	op = TASK_start_MODEL( sub_parts_exec, MAIN_COMP_GROUP, MODEL_SUB_PARTS, TEX_COMPUTER, "�ւ���" );		//
	op->grp_mode = MAIN_BILL_GRP_FLAG;
	op->ang_spd[Y] = -0xc0;
	op->pos[ X ] = ap->pos[X];
	op->pos[ Y ] = ap->pos[Y] + 600.0f;
	op->pos[ Z ] = ap->pos[Z];
	common_ambient( op );
	//op->pri = -1 * WP;

	op = TASK_start_MODEL( sub_parts_exec, MAIN_COMP_GROUP, MODEL_SUB_PARTS, TEX_COMPUTER, "�ւ���" );		//
	op->grp_mode = MAIN_BILL_GRP_FLAG;
	op->ang_spd[Y] = 0xc0;
	op->pos[ X ] = ap->pos[X];
	op->pos[ Y ] = ap->pos[Y] + 1400.0f;
	op->pos[ Z ] = ap->pos[Z];
	op->pri = -1 * WP;
	common_ambient( op );

	ep = TASK_start_MODEL( earth_exec, MAIN_COMP_GROUP, MODEL_EARTH, TEX_EARTH, "�n��" );		//�n��
	ep->grp_mode = TEST_ZBUFFER | WRITE_ZBUFFER  | NO_SHADOW	 | USE_LIGHTING;
	if( clear_flag != 0 )
		ep->tex_no = TEX_EARTH_BREAK;

	ep->pos[ X ] = ap->pos[ X ];
	ep->pos[ Y ] = 5000.0f;
	ep->pos[ Z ] = ap->pos[ X ];
	ep->ambient[0] = 1.0f;
	ep->ambient[1] = 1.0f;
	ep->ambient[2] = 1.0f;
	ep->ambient[3] = 1.0f;
	//ep->emissive[0] = 5.0f;
	//ep->emissive[1] = 5.0f;
	//ep->emissive[2] = 5.0f;
	ep->diffuse[0]  = 0x40;
	ep->sphire = 1524.0f;
}


//-----------------------------------------------------------------------------------------------------------------------
//�n�C�X�R�A��\������X�R�A�{�[�h�̃^�X�N
//-----------------------------------------------------------------------------------------------------------------------
void score_board_drawfunc( TASK *ap )
{
	if( ap->pos[ Z ] > jiki->pos[ Z ] || ap->parent->HP > 0 )
	{
		TASK spr;
		SINT32 i;
		SINT8 str[ 16 ];

		//������ɕύX����
		sprintf( str, "%8d", hi_score ); 						//�������̒��ɕۑ�����

		TASK_init_member_pointer( &spr );						//������spr��������
		spr.grp_mode = ap->grp_mode | FLIP_LR;
		spr.pos[ X ] = ap->pos[ X ];							//���W�̐ݒ�
		spr.pos[ Y ] = ap->pos[ Y ];							//���W�̐ݒ�
		spr.pos[ Z ] = ap->pos[ Z ];							//���W�̐ݒ�
		spr.scale[ X ] = ap->parent->scale[ X ];				//�傫����ݒ�
		spr.scale[ Y ] = spr.scale[ X ];						//�傫����ݒ�
		spr.tex_no = TEX_UI_FONT;								//�e�N�X�`���i���o�[�͎����̃��c
		spr.uv_rect = number_rect;								//�����̋�`�������
		spr.pri = ( OBJECT_PRI ) * WP;
		//spr.pri = UI_PRI * WP;								//�`��D��x��ݒ�

		for( i = 0; i < 8 ; i++ )								//�\����������������
		{
			if( str[ i ] >= '0' && str[ i ] <= '9' )			//�X�R�A�̂��炢��0�`9�Ȃ�
			{
				spr.base_color[ 0 ][ 1 ] = 0xff;					//R( �͂�����ƃX�R�A���o�� )
				spr.base_color[ 0 ][ 2 ] = 0xff;					//G( �͂�����ƃX�R�A���o�� )
				spr.base_color[ 0 ][ 3 ] = 0xff;					//B( �͂�����ƃX�R�A���o�� )
				spr.anime_no = str[ i ] - '0';					//�������0���當�����0�������Ɛ�����0�ɂȂ�
			}

			else
			{
				spr.base_color[ 0 ][ 1 ] = 120;						//R( �������Â����� )
				spr.base_color[ 0 ][ 2 ] = 120;						//G( �������Â����� )
				spr.base_color[ 0 ][ 3 ] = 120;						//B( �������Â����� )
				spr.anime_no = 0;								//�v�Z���ʂ�0
			}

			SOZ_sprite_draw( &spr );							//�����ŕ`�悷��
			spr.pos[ X ] += (ap->fwork1[ X ] * spr.scale[ X ]);		//���ɂ��炷
		}
	}
}

void hiscore_board_exec( TASK *ap )
{

}

void score_board_exec( TASK *ap )
{
	if( ap->HP <= 0 )
	{
		TASK_end_group( SHOT_GROUP );
		TASK_end( ap->child[0] );
		TASK_end( ap );
	}
}

void score_board_start( FLOAT x, FLOAT y, FLOAT z )
{
	TASK *ap, *actp;
	ap = TASK_start_MODEL( score_board_exec, OBJECT_GROUP, MODEL_BOATD, TEX_SCREEN_MEKA, "�X�R�A�{�[�h" );
	ap->ID = OBJ_MAX - 3;						//���C���R���s���[�^�[�̈�O�ɐݒ肵�Ă���
	object_sphire_set( ap->ID, 0, 512.0f, 0.0f, 700.0f );
	ap->grp_mode = TEST_ZBUFFER | WRITE_ZBUFFER | USE_LIGHTING;
	ap->pos[X] = x;
	ap->pos[Y] = y;
	ap->pos[Z] = z;
	ap->scale[X] = 4.0f;
	ap->scale[Y] = ap->scale[X];
	ap->HP = 500;
	ap->pri = OBJECT_PRI * WP;
	common_ambient( ap );

	/*
	actp = TASK_start_DRAWFUNC( hiscore_board_exec, score_board_drawfunc, NO_GROUP, "�{�[�h�Ƀn�C�X�R�A��\��" );
	actp->grp_mode |= USE_3DPOS;
	
	actp->fwork1[Z] = 15.0f;

	actp->pos[X] = ap->pos[X];
	actp->pos[Y] = ap->pos[Y];
	actp->pos[Z] = ap->pos[Z] + actp->fwork1[Z];
	actp->parent = ap;
	*/

	actp = TASK_start_DRAWFUNC( hiscore_board_exec, score_board_drawfunc, NO_GROUP, "�{�[�h�Ƀn�C�X�R�A��\��" );
	actp->grp_mode = USE_3DPOS;
	
	actp->fwork1[Z] = -85.0f;
	actp->fwork1[X] = 64.0f;

	actp->pos[X] = ap->pos[X] - 850.0f;
	actp->pos[Y] = ap->pos[Y];
	actp->pos[Z] = ap->pos[Z] + actp->fwork1[Z];
	actp->pri = 10 * WP;
	ap->child[0] = actp;
	actp->parent = ap;
	
}



