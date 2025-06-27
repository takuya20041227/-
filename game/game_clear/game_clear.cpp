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

PRIM_POLY3D_TEX ring_data[ 1024 ];																	//���_���i�[
SINT32 ring_data_index;

//�����o��
void screen_shutdown_drawfunc( TASK *ap )														//�����Ȃ����镔��
{
	SOZ_set_model_param( ZBUF_TEST | ZBUF_WRITE, BILINEAR_ON, LIGHTING_OFF, SPECULAR_OFF );
	SOZ_ResetClipping();
	SOZ_reset_fog();           //fog�����Z�b�g
	SOZ_set_culling( D3DCULL_NONE ); 
	SOZ_blend_setting( BLEND_ADD );
	SOZ_set_texture( 0, TEX_RAINDOW );																	//�e�N�X�`���[���Ȃ����Ƃ�錾
	SOZ_matrix_model_maker( 0, ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X],  ap->ang[Y], ap->ang[Z], ap->scale[X], ap->scale[Y], ap->scale[Z] );

	SOZ_render_start();																			//�r�f�I�J�[�h�ɑ��M����
	SOZ_primitive_draw( D3DPT_TRIANGLESTRIP, ring_data_index - 2, ring_data, sizeof( PRIM_POLY3D_TEX ), FVF_POLY3D_TEX );	//�r�f�I�J�[�h�Ƀ|���S���̒��_�Ȃǂ̏��𑗂�
	SOZ_render_end();																			//�r�f�I�J�[�h�̑��M���I���
	//lpDEVICE->BeginScene();      //�r�f�I�J�[�h�ɓ]���J�n
	//lpDEVICE->DrawPrimitiveUP(  );         //���̎��̏c����
	//lpDEVICE->EndScene();	
}
void screen_shutdown_exec( TASK *ap )
{
	SINT32 angle, index;
	FLOAT x, y, vec_x, vec_y;
	index = 0;
	for( angle = 0; angle <= 0x10000; angle += 0x400 )
	{
		// �����O�̓��p
		ring_data[ index ].x = ap->pos[X] + SOZ_get_sin( angle ) *  10000;	//�T�C�����܂킷
		ring_data[ index ].y = ap->pos[Y] + SOZ_get_cos( angle ) *  8000;//�R�T�C��
		ring_data[ index ].z = ap->pos[Z];																//���s����0
		//ring_data[ index ].r = 1.0f;																//�e�N�X�`���[�̂ǂ��܂ł�؂��邩
		ring_data[ index ].diffuse = 0x80ffffff;													//�F��ݒ�ff�͓����x00�͐�00�͗�00�͐��������Ă�
		ring_data[ index ].x = ring_data[ index ].x;												
		ring_data[ index ].y = ring_data[ index ].y;				
		ring_data[ index ].u = 1.0f;
		ring_data[ index ].v = 1.0f;
		index++;

		//�����O�̊O�p
		ring_data[ index ].x = ap->pos[X] + SOZ_get_sin( angle ) * 15000;
		ring_data[ index ].y = ap->pos[Y] + SOZ_get_cos( angle ) * 13000;
		ring_data[ index ].z = ap->pos[Z];
		//ring_data[ index ].rhw = 1.0f;
		ring_data[ index ].diffuse = 0x80ffffff;
		ring_data[ index ].x = ring_data[ index ].x;
		ring_data[ index ].y = ring_data[ index ].y;
		ring_data[ index ].u = 0.0f;
		ring_data[ index ].v = 0.0f;
		index++;
	}

/*	if( SOZ_Inkey_DAT( DIK_UP ) != 0 )
		ap->pos[Y] += 100.0f;
	if( SOZ_Inkey_DAT( DIK_DOWN ) != 0 )
		ap->pos[Y] -= 100.0f;
	if( SOZ_Inkey_DAT( DIK_RIGHT ) != 0 )
		ap->pos[X] += 100.0f;
	if( SOZ_Inkey_DAT( DIK_LEFT ) != 0 )
		ap->pos[X] -= 100.0f;
*/
	ring_data_index = index;																		//�J�E���g
}
void screen_shutdown_start( void )
{
	TASK * ap;
	ap  =TASK_start_DRAWFUNC( screen_shutdown_exec, screen_shutdown_drawfunc, NO_GROUP, "��ʂ����߂�" );
	ap->pos[X] = 12500.0f;
	ap->pos[Y] = 1500.0f;
	ap->pos[Z] = 12500.0f;
	ap->pri = 9999 * WP;
	ap->fwork1[X] = 128.0f;
	ap->vec[X] = 30.0f;
	ap->acc[X] = 12.45f;
	ap->grp_mode |= USE_3DPOS;
	ap->pri = SHOT_PRI * WP;
}

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
	SINT32 i, rand_max;
	FLOAT pos_x, pos_z, vec_x, vec_y;
	ap->pos[Z] += ap->vec[Z];
	ap->vec[Z] += ap->acc[Z];
	if( ap->pos[Y] > jiki->pos[Y] )
		if( ap->timer % 60 == 0 )
			for( i = -0xc000; i < 0x4000; i += 0x4000 )
			{
				pos_x = ap->pos[ X ];
				pos_z = ap->pos[ Z ];
				vec_x = SOZ_get_sin( i ) * 10.0f;
				vec_y = SOZ_get_cos( i ) * 10.0f;
				flower_start( pos_x, ap->pos[ Y ], pos_z, vec_x, vec_y, vec_y, USE_3DPOS );
			}
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

void clear_start( PARTS_RECT *pp )
{
	TASK *ap;
	ap = TASK_start_GRP( clear_exec, UI_GROUP, TEX_UI_FONT, pp, 0, "�Q�[���N���A" );
	ap->pos[X] = WINDOW_WIDTH_HALF;								//�^��
	ap->pos[Y] = WINDOW_HEIGHT_HALF;							//�^��
}		


void game_resurt_exec( TASK* ap )
{
	alpha_chenge( ap, 0xff, 0xa0 );
}

void geme_resurt_start( SINT32 anime_no )
{
	TASK *ap;
	ap = TASK_start_GRP( game_resurt_exec, NO_GROUP, TEX_UI_FONT, resurt_rect, anime_no, " �Q�[���̌��ʂ�\�� " );
	ap->pos[X] = WINDOW_WIDTH_HALF;
	ap->pos[Y] = WINDOW_HEIGHT_HALF + 128.0f;
	ap->scale[X] = 1.5f;
	ap->scale[Y] = ap->scale[X];
	ap->pri = 9999 * WP;

	ap = TASK_start_GRP( game_resurt_exec, NO_GROUP, TEX_UI_FONT, resurt_rect, 2, " �Q�[���̌��ʂ�\�� " );
	ap->pos[X] = WINDOW_WIDTH_HALF;
	ap->pos[Y] = WINDOW_HEIGHT_HALF + 256.0f;
	ap->scale[X] = 1.5f;
	ap->scale[Y] = ap->scale[X];
	ap->pri = 9999 * WP;
}

