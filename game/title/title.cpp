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
#include    "../include.h"



PRIM_POLY3D_TEX title_logo[]=		//�^�C�g�����S��
{
	{      0.0f,    0.0f,  0.0f, 0xffffffff,  0.0f, 0.0f },
	{   2048.0f,    0.0f,  0.0f, 0xffffffff,  1.0f, 0.0f },
	{      0.0f, 1024.0f,  0.0f, 0xffffffff,  0.0f, 1.0f },
	{   2048.0f, 1024.0f,  0.0f, 0xffffffff,  1.0f, 1.0f },
};



//------------------------------------------------------------------------------------------------------------------------------------------------------
//�^�C�g�����S�̕\��
//------------------------------------------------------------------------------------------------------------------------------------------------------
void title_logo_drawfunc( TASK *ap )
{
	SOZ_set_model_param( ZBUF_TEST | ZBUF_WRITE, BILINEAR_ON, LIGHTING_OFF, SPECULAR_OFF );
	SOZ_ResetClipping();
	SOZ_reset_fog();           //fog�����Z�b�g
	SOZ_set_culling( D3DCULL_NONE ); 
	SOZ_blend_setting( BLEND_NORMAL );
	SOZ_set_texture( 0, TEX_TITLE );

	//�v���~�e�B�u�]��
	SOZ_matrix_model_maker( 0, ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X],  ap->ang[Y], ap->ang[Z], ap->scale[X], ap->scale[Y], ap->scale[Z] );
	SOZ_render_start();
	SOZ_primitive_draw( D3DPT_TRIANGLESTRIP, 2, title_logo, sizeof( PRIM_POLY3D_TEX ), FVF_POLY3D_TEX );
	SOZ_render_end();
}

void title_logo_exec( TASK *ap )
{
	SINT32 i;										//for���p�̕ϐ�
	FLOAT sa, abs_sa;								//��Βl�����߂�
	FLOAT pos_box[6][2] =							//���W�̕ۑ��̔z��
	{
		{ ap->fwork1[X], jiki->pos[X] },			//���@�̉�
		{ ap->fwork1[Y], jiki->pos[Y] },			//���@�̏c
		{ ap->fwork1[Z], jiki->pos[Z] },			//���@�̑O��
		{ ap->fwork2[X], camera_x[0]  },			//�J�����̉�
		{ ap->fwork2[Y], camera_y[0]  },			//�J�����̏c
		{ ap->fwork2[Z], camera_z[0]  },			//�J�����̑O��
	};

	if( ap->timer >= 15 )							//�J������1�t���[�������Ă��܂��̂Ő��t���[���x�点��
	{
		if( ap->SWITCH != 0 )						//�����Ă��邱�Ƃ��m�F������
		{
			if( ap->TIMER == 0 )					//�v���̍ŏ��̃t���[����
				ap->base_color[ 0 ][ 0 ] = 0x0;		//�����ɂ���
			ap->fwork1[ X ] = jiki->pos[ X ];		//���@�̉���ۑ�
			ap->fwork1[ Y ] = jiki->pos[ Y ];		//���@�̏c��ۑ�
			ap->fwork1[ Z ] = jiki->pos[ Z ];		//���@�̑O���ۑ�
			ap->fwork2[ X ] = camera_x[ 0 ];		//�J�����̉���ۑ�
			ap->fwork2[ Y ] = camera_y[ 0 ];		//�J�����̏c��ۑ�
			ap->fwork2[ Z ] = camera_z[ 0 ];		//�J�����̑O���ۑ�
			ap->TIMER++;							//�^�C�}�[�v��
		}

		for( i = 0; i < 6; i++ )					//�z�񕪉�
		{
			sa = pos_box[ i ][ 0 ] - pos_box[ i ][ 1 ];
			abs_sa = (FLOAT)fabs( (DOUBLE)sa );		//��Βl������
			if( abs_sa > 10 )						//���@���J��������������( �������]�������� )
			{
				ap->TIMER = 0;						//�����Ȏ��ɓ������Ƃ��p�ɏ�����
				ap->SWITCH = 1;						//���S�𓧖��ɂ���
				break;								//�񂷂̂����߂�
			}
		}

		for( i = 0; i < 3; i++ )
			if( SOZ_Mouse_Button( i ) != 0 )
			{
				ap->TIMER = 0;						//�����Ȏ��ɓ������Ƃ��p�ɏ�����
				ap->SWITCH = 1;						//���S�𓧖��ɂ���
				break;								//�񂷂̂����߂�
			}


		if( ap->TIMER >= TIME_S * 5 )				//����̎��Ԃ𒴂���
			if( ap->TIMER % 4 == 0 )				//���t���[������
				ap->base_color[ 0 ][ 0 ] += 0x8;	//���񂾂�A���t�@�l���グ�Ă���

		if( ap->base_color[ 0 ][ 0 ] > 0xff )		//�A���t�@�l���}�b�N�X�ɂȂ��
			ap->base_color[ 0 ][ 0 ] = 0xff;		//�Œ肷��
	}
	else
	{
		ap->fwork2[X] = camera_x[0];				//�J�����̉���ۑ�
		ap->fwork2[Y] = camera_y[0];				//�J�����̏c��ۑ�
		ap->fwork2[Z] = camera_z[0];				//�J�����̑O���ۑ�
	}

	
}

void title_logo_start( void )
{
	TASK *ap;
	ap = TASK_start_GRP( title_logo_exec, NO_GROUP, TEX_TITLE, logo_rect, 0, "�^�C�g�����S" );
	ap->pos[X] = WINDOW_WIDTH_HALF;
	ap->pos[Y] = 400.0f;
	ap->scale[X] = 0.6f;
	ap->scale[Y] = ap->scale[X]; 
	ap->fwork1[X] = jiki->pos[X];		//���@�̉���ۑ�
	ap->fwork1[Y] = jiki->pos[Y];		//���@�̏c��ۑ�
	ap->fwork1[Z] = jiki->pos[Z];		//���@�̑O���ۑ�
	ap->pri = 999 * WP;
	ap->exe_pri = 0;
	
}


#if 0
//------------------------------------------------------------------------------------------------------------------------------------------------------
//�^�C�g�����S�̃|���S���̒l���Z�b�g����
//------------------------------------------------------------------------------------------------------------------------------------------------------
void logo_pri_set( TASK *ap, SINT32 num, FLOAT x, FLOAT y, FLOAT u, FLOAT v )
{
	PRIM_POLY3D_TEX *pp;
	pp = &title_logo[ num ];
	pp->x = ap->pos[X] + x;
	pp->y = ap->pos[Y] + y;
	pp->z = ap->pos[Z];
	pp->diffuse = 0xffffffff;
	pp->u = u;
	pp->v = v; 
}
#endif