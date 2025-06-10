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
#include    "include.h"


PRIM_POLY ring_data[ 1024 ][ 1024 ];	//���_���i�[
SINT32 ring_data_index[ 1024 ];			//���_�̐����J�E���g


//-----------------------------------------------------------------------------------------------------------------------
//�X�t�B�A������������
//-----------------------------------------------------------------------------------------------------------------------
void sphire_debug_drawfunc( TASK *ap )
{
	SINT32 i;
	SOZ_ResetClipping();
	SOZ_reset_fog();
	SOZ_set_model_param( ZBUF_OFF, BILINEAR_OFF, LIGHTING_OFF, SPECULAR_OFF );
	SOZ_set_culling( D3DCULL_NONE ); //NONE�͕\�ł����ł��\��
	SOZ_set_texture( 0, NULL);   //�e�N�X�`���[���Ȃ����Ƃ�錾


	SOZ_render_start();
	for( i = 0; ring_data_index[i] == NULL; i++ )
		SOZ_primitive_draw( D3DPT_TRIANGLESTRIP, ring_data_index[i] - 2, ring_data, sizeof( PRIM_POLY ), FVF_POLY );
	SOZ_render_end();	
}

void sphire_debug_exec( TASK *ap )
{
	TASK *actp;
	ANGLE angle;
	SINT32 i, index;
	i = 0;
	for( actp = ap_start; actp != NULL; actp = actp->next )		//�S��������
	{
		index = 0;
		if( actp->sphire != 0.0f )						//�X�t�B�A�̐ݒ肪����Ȃ�
		{
			for( angle = 0x0; angle < 0xffff; angle += 0x800 )
			{
				// �����O�̓��p
				ring_data[ i ][ index ].x = actp->pos[ X ] + SOZ_get_sin( angle ) *  actp->sphire - 10;
				ring_data[ i ][ index ].y = ( actp->pos[ Y ] ) + SOZ_get_cos( angle ) *  actp->sphire - 10;
				ring_data[ i ][ index ].z = actp->pos[Z];
				ring_data[ i ][ index ].rhw = 1.0f;
				ring_data[ i ][ index ].diffuse = 0xffff0000;
				ring_data[ i ][ index ].x = ring_data[ i ][ index ].x;
				ring_data[ i ][ index ].y = ring_data[ i ][ index ].y;
				index++;
				//�����O�̊O�p
				ring_data[ i ][ index ].x = actp->pos[ X ] + SOZ_get_sin( angle ) * actp->sphire;
				ring_data[ i ][ index ].y = actp->pos[ Y ] + SOZ_get_cos( angle ) * actp->sphire;
				ring_data[ i ][ index ].z = actp->pos[Z];
				ring_data[ i ][ index ].rhw = 1.0f;
				ring_data[ i ][ index ].diffuse = 0xffff0000;
				ring_data[ i ][ index ].x = ring_data[ i ][ index ].x;
				ring_data[ i ][ index ].y = ring_data[ i ][ index ].y;
				index++;
			}
		}
		else if( actp->task_group == OBJECT_GROUP )
		{
			OBJECT_SPHIRE *op;
			op = &object_sphire[ ap->ID ];							//�ǂ��̃A�h���X�ɓ���邩��������
			if( op->sphire[ 0 ] != NULL )				//�����X�t�B�A�̒��g�����łɓ����Ă�����		
			{
				ring_data[ i ][ index ].x = actp->pos[ X ] + SOZ_get_sin( angle ) *  actp->sphire - 10;
				ring_data[ i ][ index ].y = ( actp->pos[ Y ] ) + SOZ_get_cos( angle ) *  actp->sphire - 10;
				ring_data[ i ][ index ].z = actp->pos[Z];
				ring_data[ i ][ index ].rhw = 1.0f;
				ring_data[ i ][ index ].diffuse = 0xffff0000;
				ring_data[ i ][ index ].x = ring_data[ i ][ index ].x;
				ring_data[ i ][ index ].y = ring_data[ i ][ index ].y;
				index++;
				//�����O�̊O�p
				ring_data[ i ][ index ].x = actp->pos[ X ] + SOZ_get_sin( angle ) * actp->sphire;
				ring_data[ i ][ index ].y = actp->pos[ Y ] + SOZ_get_cos( angle ) * actp->sphire;
				ring_data[ i ][ index ].z = actp->pos[Z];
				ring_data[ i ][ index ].rhw = 1.0f;
				ring_data[ i ][ index ].diffuse = 0xffff0000;
				ring_data[ i ][ index ].x = ring_data[ i ][ index ].x;
				ring_data[ i ][ index ].y = ring_data[ i ][ index ].y;
				index++;
			}
		}
		ring_data_index[ i ] = index;		//�J�E���g
		i++;

		
	}
}

void sphire_debug_start( void )
{
//#if DEBUG
	TASK *ap;
	ap = TASK_start_DRAWFUNC( sphire_debug_exec, sphire_debug_drawfunc , NO_GROUP, "�X�t�B�A������������" );
	ap->pri = 9999 * WP;
//#endif
}


void particle_num_exec( TASK *ap )
{
	TASK *actp;
	SINT32 particle_num;
	particle_num = 0;												//������	
	for( actp = ap_start; actp != NULL; actp = actp->next )
		if( actp->task_group == BREAK_EFFECTS_GROUP )
			particle_num++;

	SOZ_locate_print( 64, 8, "particle%5d", particle_num );
}

void particle_num_start( void )
{
	TASK *ap;
	ap = TASK_start( particle_num_exec, NO_GROUP, "�p�[�e�B�N���̐��𐔂���" );
}


void viwe_clip_num_exec( TASK *ap )
{
	TASK *actp;
	SINT32 view_clip_num, clip_obj;
	view_clip_num = 0;												//������
	clip_obj = 0;													//������
	for( actp = ap_start; actp != NULL; actp = actp->next )
	{
		if( actp->task_group == BREAK_EFFECTS_GROUP )
			if( actp->task_id == TASK_PROGRAM )
				view_clip_num++;

		if( actp->task_group == OBJECT_GROUP )
			if( actp->task_id == TASK_PROGRAM )
				clip_obj++;													//������++;
	}

	SOZ_locate_print( 64, 9, "view_clip_p%5d", view_clip_num );
	SOZ_locate_print( 64, 10, "view_clip_o%5d", clip_obj );
}

void viwe_clip_num_start( void )
{
	TASK *ap;
	ap = TASK_start( viwe_clip_num_exec, NO_GROUP, "������J�����O�̐�" );
}



