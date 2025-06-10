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


//-----------------------------------------------------------------------------------------------------------------------
//�O���ϐ�
//-----------------------------------------------------------------------------------------------------------------------
SINT32 mouse_x = 0, mouse_y = 0;			//�}�E�X�̍��W������ϐ�


//-----------------------------------------------------------------------------------------------------------------------
//�L�[�ŃJ�����𓮂���
//-----------------------------------------------------------------------------------------------------------------------
void mouse_camera_control_exec( TASK *ap )
{
	FLOAT sa_x, sa_y;
	SINT32 mx, my;
	mx = mouse_x;
	my = mouse_y;
	sa_x = ap->work1[X] - mouse_x;			//���̍����v��
	sa_y = ap->work1[Y] - mouse_y;			//�c�̍����v��
	SOZ_Mouse( &mouse_x, &mouse_y );		//�}�E�X�̍��W������
	if( ap->work1[ X ] != mouse_x || ap->work1[ Y ] != mouse_y )	//�c�����̂ǂ��炩����������	
	{
		switch( ap->SCENE )
		{
			case 0:
				if( sa_x > 0 )		//��������20���傫�����( ���ɐi�� )
				{
					jiki->keep += 
				//	jiki->angle[ Y ] += ap->ang_spd[ Y ];
				//	ap->ang_spd[ Y ] += 0x40;
				}
				else if( sa_x < 0 )
				{
				//	jiki->angle[Y] -= ap->ang_spd[Y];
				//	ap->ang_spd[Y] += 0x40;	
				}
				break;

			case 10:
			//	ap->pos[X] += 5.0f;
				//camera_ang_y[ 0 ] += ap->ang_spd[Y];
				
				break;

			case 20:
			//	ap->pos[X] += 5.0f;
			//	camera_ang_y[ 0 ] -= ap->ang_spd[Y];
				
				break;
		}
		
		if( mouse_x == mx )
		{
			ap->work1[ X ] = mouse_x;
			ap->ang_spd[Y] = 0x0;
			ap->SCENE = 0;
		}

		/*if( sa_y > 20 )		//��������20���傫�����( ���ɐi�� )
		{
			camera_ang_x [ 0 ] += 0xff + sa_y * 4;
			ap->work1[Y] = mouse_y;		//�������
		}
		else if( sa_y < -20 )
		{
			camera_ang_x[ 0 ] -= 0xff + sa_y * 4;
			ap->work1[Y] = mouse_y;		//�������
		}*/
	}
	if( SOZ_Mouse_Button( 2 ) != 0 )
	{
		camera_ang_y[ 0 ] = 0xff;
		camera_ang_x[ 0 ] = 0xff;
		SetCursorPos( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 );
		ap->work1[ X ] = mouse_x;		//�������
		ap->work1[Y] = mouse_y;
	}
}


//-----------------------------------------------------------------------------------------------------------------------
//�L�[�ŃJ�����𓮂���
//-----------------------------------------------------------------------------------------------------------------------
void key_camera_control_exec( TASK *ap )
{
	//ap->angle[Y] += 0x400;
	FLOAT x,y,z, cx, cy, cz;
	if( jiki != NULL )
	{
		x = fabs( jiki->pos[X] );
		y = fabs( jiki->pos[Y] );
		z = fabs( jiki->pos[Z] );
		cx = jiki->pos[X] + ap->child[0]->pos[X]; 
		cy = jiki->pos[Y] + ap->child[0]->pos[Y]; 
		cx = jiki->pos[Z] + ap->child[0]->pos[Z];

		camera_x[0] =   jiki->pos[X] + SOZ_get_sin( jiki->angle[Y] ) * 512;
		camera_y[0] =   jiki->pos[Y];
		camera_z[0] =  -jiki->pos[Z] + SOZ_get_cos( jiki->angle[Y] ) * 512;

		camera_at_x[0] =  jiki->pos[X];//  + SOZ_get_sin( ap->angle[Y] ) * 512;		//
		camera_at_y[0] =  jiki->pos[Y];
		camera_at_z[0] =  -jiki->pos[Z];// + SOZ_get_cos( ap->angle[Y] ) * 512;		// 
		//camera_ang_x[0] = SOZ_atan2( camera_x[0], camera_y[0], jiki->pos[X], jiki->pos[Y] );
		//camera_ang_z[0] = SOZ_atan2( camera_x[0], camera_z[0], jiki->pos[X], jiki->pos[Z] );
	}
#if DEBUG
	else
	{
		if( SOZ_Inkey_DAT( DIK_D ) != 0 )
			camera_x[0] +=  50;
		else if( SOZ_Inkey_DAT( DIK_A ) != 0 )
			camera_x[0] += -50;
		else if( SOZ_Inkey_DAT( DIK_W ) != 0 )
			camera_z[0] +=  50;
		else if( SOZ_Inkey_DAT( DIK_S ) != 0 )
			camera_z[0] += -50;
	}
#endif
	//SOZ_camera_move( 0 );
	SOZ_camera_set_at_move( 0 );
}

void camera_control_start( void )
{
	TASK *ap, *actp;
	ap = TASK_start( key_camera_control_exec, NO_GROUP, "�L�[�ŃJ�������R���g���[��" );
	ap->work1[X] = mouse_x;
	ap->work1[Y] = mouse_y;
	ap->ang_spd[Y] = 0x0; 

	actp = TASK_start( mouse_camera_control_exec, NO_GROUP, "�}�E�X�ŃJ�������R���g���[��" );
	actp->parent = ap;				//�e�q�֌W������
	ap->child[0] = actp;			//�e�q�֌W������
}