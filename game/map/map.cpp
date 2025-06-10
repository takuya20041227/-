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


//------------------------------------------�}�b�v���쐬����cpp--------------------------------------------------------//
//-----------------------------------
//�|���S���̋�`���
//-----------------------------------
PRIM_POLY3D_TEX ground_poly[]=   
{
	{      0.0f,  0,     0.0f, 0xffffffff,  0.0f, 0.0f },
	{  50000.0f,  0,     0.0f, 0xffffffff,  1.0f, 0.0f },
	{      0.0f,  0, 50000.0f, 0xffffffff,  0.0f, 1.0f },
	{  50000.0f,  0, 50000.0f, 0xffffffff,  1.0f, 1.0f },
};


SINT32 clear_flag = 0;				//�����̒l���ς��ƒn�����r�p����
SINT32 main_bill_hp = 100;			//���C���r����HP���i�[����( �ꉞ0���ƕ|���̂�0�ȊO�����Ă��� )

//-----------------------------------------------------------------------------------------------------------------------
//�n�ʂ�y���W���^�X�N�̈ʒu�ɑ������֐�
//-----------------------------------------------------------------------------------------------------------------------
void ground_y_set( TASK *ap )
{
	PRIM_POLY3D_TEX * wp;
	SINT32 i;
	for( i = 0; i < 4; i++ )
	{
		wp = &ground_poly[i];
		wp->y = ap->pos[X];
	}
}


//-----------------------------------------------------------------------------------------------------------------------
//�n�ʂ�`�ʂ�����^�X�N
//-----------------------------------------------------------------------------------------------------------------------
void ground_drawfunc( TASK *ap )
{
	SOZ_set_model_param( ZBUF_TEST | ZBUF_WRITE, BILINEAR_ON, LIGHTING_OFF, SPECULAR_OFF );
	SOZ_ResetClipping();
	SOZ_reset_fog();           //fog�����Z�b�g
	SOZ_set_culling( D3DCULL_NONE ); 
	SOZ_blend_setting( BLEND_NORMAL );
	SOZ_set_texture( 0, ap->tex_no );

	//�v���~�e�B�u�]��
	SOZ_matrix_model_maker( 0, ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X],  ap->ang[Y], ap->ang[Z], ap->scale[X], ap->scale[Y], ap->scale[Z] );
	SOZ_render_start();
	SOZ_primitive_draw( D3DPT_TRIANGLESTRIP, 2, ground_poly, sizeof( PRIM_POLY3D_TEX ), FVF_POLY3D_TEX );
	SOZ_render_end();
}

void ground_exec( TASK *ap )
{
	//ground_y_set( ap );
}

void ground_start( SINT32 tex_no )
{
	TASK *ap;
	ap = TASK_start_DRAWFUNC( ground_exec, ground_drawfunc, MAP_GROUP, "�n��" );
	ap->pos[X] = 0.0f;
	ap->pos[Y] = GROUND;
	ap->pos[Z] = 0.0f;
	ap->grp_mode |= USE_2DMODEL_POS;
	ap->pri = -999 * WP;
	ap->tex_no = tex_no;
	ap->cam_number = 1;
}


//-----------------------------------------------------------------------------------------------------------------------
//���C���̃r���̃��f���̃^�X�N
//-----------------------------------------------------------------------------------------------------------------------
void main_bill_exec( TASK *ap )
{
	ANGLE ang;
	SINT32 i;
	FLOAT x, y, z;
	//ap->ang[Y] += 0x10;
	//ap->task_id = TASK_PROGRAM;
	ap->sphire = sphire_get( ap );
	if( ap->HP <= 0 )
	{
		ap->TIMER++;
		if( ap->TIMER == 1 )
		{
			if( game_type != 501 )
			{
				clear_flag = 1;							//�n�����r�p������
				game_type = 110;						//�Q�[���N���A��ʂɈړ�����
				return;
			}
		}

		if( ap->TIMER % 12 == 0 )
		{
			for( i = 0; i < Rand2( 5, 15 ); i++ )
			{
				ang = Rand2( 0x0, 0xffff );
				x = ap->pos[X] + SOZ_get_sin( ang ) * 256.0f;
				y = ap->pos[Y] + F_Rand2( GROUND, 4444.0f );
				z = ap->pos[Z] + SOZ_get_cos( ang ) * 256.0f ;
				beam_bom_start( x, y, z, F_Rand2( 15.0f, 20.0f ) );
			}
			ap->pos[X] = 25000.0f + F_Rand2( -512, 512 );
			ap->pos[Z] = 25000.0f + F_Rand2( -512, 512 );
			ap->ang[X] = Rand2( -0x1000, 0x1000 );
			ap->ang[Z] = Rand2( -0x1000, 0x1000 );
		}
		ap->pos[Y] -= 20.0f;

		if( ap->pos[Y] <= GROUND - 5000.0f )
		{
			TASK_end( ap );
			return;
		}
	}
	main_bill_hp = ap->HP;							//HP���i�[
#if DEBUG											//�f�o�b�O�p
	if( SOZ_Inkey_TRG( DIK_O ) != 0 )
		ap->HP = 0;
#endif
}

void main_bill_start( void )
{
	TASK *ap;
	ap = TASK_start_MODEL( main_bill_exec, MAIN_BILL_GROUP, MODEL_MAIN_BILL, TEX_BILL, "���C���̃r��" );
	ap->grp_mode =  TEST_ZBUFFER | WRITE_ZBUFFER  | NO_SHADOW | USE_LIGHTING | USE_SPECULAR;
	ap->ID = OBJ_MAX - 1;						//�z��̍Ō���ɓ����蔻�������
	object_sphire_set( ap->ID, 0, 1024.0f, 0.0f,	1024.0f );		//
	object_sphire_set( ap->ID, 1, 1024.0f, 2048.0f, 3072.0f );	//
	object_sphire_set( ap->ID, 2, 1024.0f, 3072.0f, 4192.0f );	//
	object_sphire_set( ap->ID, 3, 1024.0f, 4192.0f, 5316.0f );	//
	object_sphire_set( ap->ID, 4, 1024.0f, 5316.0f, 6240.0f );	//
	common_ambient( ap );
	ap->pos[ X ] = 25000.0f;					//���W
	ap->pos[ Y ] = GROUND;						//���W
	ap->pos[ Z ] = 25500.0f;					//���W
	ap->ang[Y] = 0x4000;						//
	                 
	ap->pow = 4.6f;								//
	ap->specular[0] = 1.9f;						//
	ap->specular[1] = 2.1f;						//
	ap->specular[2] = 1.9f;						//
	ap->cam_number = 1;							//
	ap->sphire = 2500.0f;						//
	ap->HP = MAIN_BILL_HP_MAX;					//�r�[���������ł��肬�莀�ȂȂ����炢
	main_bill_hp = ap->HP;
	ap->pri = OBJECT_PRI * WP;
	//ap->sphire = 128.0f;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�h�[����̋�( 3D )
//------------------------------------------------------------------------------------------------------------------------------------------------------
void sky_exec( TASK *ap )
{
	//ap->pos[Y] += 0x1;
	ap->pos[X] = jiki->pos[X];
	//ap->pos[Y] = ;
	ap->pos[Z] = jiki->pos[Z];
	ap->ang[Y] += 0xc;
	//ap->ang[X] += 0xff;
//	ap->tex_no = 35;
	//ap->ang[X] = -camera_ang_x[0];
}


void sky_start( SINT32 model_no, SINT32 tex_no,  FLOAT y, FLOAT scale_x, FLOAT scale_y, FLOAT scale_z )
{
	TASK *ap;
	ap = TASK_start_MODEL( sky_exec, 0, model_no, tex_no, "�h�[����̋�" );
	ap->grp_mode =  TEST_ZBUFFER |USE_2DMODEL_POS | NO_SHADOW | USE_LIGHTING;// | USE_SPECULAR;
	ap->pos[X] = 15000;
	ap->pos[Y] = y;
	ap->pos[Z] = 15000;
	ap->scale[X] = scale_x;
	ap->scale[Y] = scale_y;
	ap->scale[Z] = scale_z;
	ap->pri = -9999 * WP;
	ap->ambient[0] = 1.0f;
	ap->ambient[1] = ap->ambient[0];
	ap->ambient[2] = ap->ambient[1];
	ap->ambient[3] = ap->ambient[2];
	//ap->emissive[0] = 3.0f;
	//ap->emissive[1] = 3.0f;
	//ap->emissive[2] = 3.0f;
	SOZ_set_light_pos( 0.0f, 0.0f, 0.0f, -3000, 2000, 19340 );
	ap->cam_number = 1;
}





