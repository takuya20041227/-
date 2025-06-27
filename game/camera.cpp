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


SINT32 mouse_x = 0, mouse_y = 0;				//�}�E�X�̍��W������ϐ�
FLOAT mouse_3d_x = 0.0f, mouse_3d_y = 0.0f;		//3D���W�ɕϊ������}�E�X���W
FLOAT world_mouse_x = 0.0f, world_mouse_y = 0.0f;	//���[���h���W�ɕϊ������}�E�X



void mouse_get_cursor_exec( TASK *ap )
{
	SOZ_Mouse( &mouse_x, &mouse_y );			//�}�E�X�̍��W������
	mouse_3d_x = ( FLOAT )mouse_x - WINDOW_WIDTH_HALF;	//��ʃT�C�Y�̔����Ō��Z( ����Œ��S��0�ɂȂ�͂� )	
	mouse_3d_y = ( FLOAT )-mouse_y;				//�}�E�X�𔽓]������
	mouse_3d_y = mouse_3d_y + WINDOW_HEIGHT_HALF;	//���]�����l�ɉ�ʔ��������Z
	world_mouse_x = mouse_3d_x + camera_x[0];	//3D�}�E�X���W�ɃJ�����̒l�����Z����
	world_mouse_y = mouse_3d_y + camera_y[0];	//3D�}�E�X���W�ɃJ�����̒l�����Z����
}


void mouse_get_cursor_start( void )
{
	TASK *ap;
	ap = TASK_start( mouse_get_cursor_exec, MANE_GROUP, "�}�E�X�̍��W���擾����" );
}

//-----------------------------------------------------------------------------------------------------------------------
//�L�[�ŃJ�����𓮂���
//-----------------------------------------------------------------------------------------------------------------------
void camera_angle_chenge( TASK *ap )
{
	SINT32 sa_x, sa_y;
	SINT32 mx, my;
	ap->TIMER++;
	mx = mouse_x;
	my = mouse_y;
	sa_x = ap->work1[X] - mouse_x;			//���̍����v��
	sa_y = ap->work1[Y] - mouse_y;			//�c�̍����v��
	if( ap->work1[ X ] != mouse_x || ap->work1[ Y ] != mouse_y )	//�c�����̂ǂ��炩����������	
	{
		if( sa_x > 0 )		//��������0���傫�����( ���ɐi�� )
		{
			ap->ang_spd[ Y ] += 0x100;
			jiki->angle[ Y ] += ap->ang_spd[ Y ];
			
		}
		else if( sa_x < 0 )
		{
			ap->ang_spd[Y] += 0x100;
			jiki->angle[Y] -= ap->ang_spd[Y];
				
		}

		if( sa_y > 3 )		//��������20���傫�����( ���ɐi�� )
		{
			ap->ang_spd[X] += 0x100;
			jiki->angle[X] -= ap->ang_spd[X];
		}
		else if( sa_y < -3 )
		{
			ap->ang_spd[X] += 0x100;	
			jiki->angle[X] += ap->ang_spd[X];
		}
		if( mouse_x == mx )
		{
			ap->work1[Y]   = mouse_y;
			ap->work1[X]   = mouse_x;
			ap->ang_spd[Y] = 0x0;
			ap->ang_spd[X] = 0x0;
			ap->SCENE = 0;
		}
	}

	if( ap->TIMER > 1 )										//�ʂ̃^�X�N�Ń}�E�X���W������Ă���̂�1�t���[���������W�Q�Ƃ���߂�
	{
		ap->TIMER = 10;										//�����ŌŒ艻����( ���u���Ă�32�r�b�g�����Ȃ����߂� )
		if( mx >= WINDOW_WIDTH - 1 )						//
			SetCursorPos( 2, mouse_y );						//���[�ɔ�΂�
		if( mx < 1 )										//
			SetCursorPos( WINDOW_WIDTH - 2, mouse_y );		//�E�[�ɔ�΂�

		if( my >= WINDOW_HEIGHT - 1 )						//
			SetCursorPos( mouse_x, 2 );						//���[�ɔ�΂�
		if( my < 1 )										//
			SetCursorPos( mouse_x, WINDOW_HEIGHT - 2 );		//�E�[�ɔ�΂�
	}
}


void mouse_control( TASK *ap )
{
	
}


//-----------------------------------------------------------------------------------------------------------------------
//�}�E�X�ŃJ�����𓮂���
//-----------------------------------------------------------------------------------------------------------------------
void mouse_camera_control_exec( TASK *ap )
{
	if( game_type == 1001 || game_type == 2001 )//�G�f�B�^�[�Ȃ�
	{
		if( SOZ_Inkey_DAT( DIK_LSHIFT ) != 0 || SOZ_Inkey_DAT( DIK_RSHIFT ) != 0 )//�V�t�g�������Ă�����
		{
			ap->work1[Y] = mouse_y;		//�}�E�X�̍��W��ۑ����Ă���
			ap->work1[X] = mouse_x;		//�}�E�X�̍��W��ۑ����Ă���
		}
		else if( SOZ_Inkey_DAT( DIK_LSHIFT ) == 0 || SOZ_Inkey_DAT( DIK_RSHIFT ) == 0 )				//�V�t�g�������Ă��Ȃ����
		{
			if( SOZ_Mouse_Button( 2 ) )
				camera_angle_chenge( ap );
		}
	}
	else
	{
		camera_angle_chenge( ap );
	}
	if( game_type != 1001 && game_type != 2001 )					//�G�f�B�^�[����Ȃ��Ȃ�
	{
		if( SOZ_Mouse_Button( 2 ) == 1 )
		{
			camera_ang_y[ MAIN_CAMERA ] = 0xff;
			camera_ang_x[ MAIN_CAMERA ] = 0xff;
			SetCursorPos( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 );
			ap->work1[ X ] = mouse_x;		//�������
			ap->work1[ Y ] = mouse_y;
		}
	}
}


//-----------------------------------------------------------------------------------------------------------------------
//�L�[�ŃJ�����𓮂���
//-----------------------------------------------------------------------------------------------------------------------
void key_camera_control_exec( TASK *ap )
{
	//ap->angle[Y] += 0x400;
	//FLOAT x,y,z, cx, cy, cz;
	FLOAT camera_pos_y;
	ANGLE ang_x, ang_y;
	ang_x = jiki->angle[X] %= 0xffff;
	ang_y = jiki->angle[Y] %= 0xffff;
	camera_pos_y = camera_y[ MAIN_CAMERA ];				//�J�����̍��W��ۑ����Ă���
	if( jiki != NULL && game_type != 501 )
	{
		//x = fabs( jiki->pos[X] );
		//y = fabs( jiki->pos[Y] );
		//z = fabs( jiki->pos[Z] );
		//cx = jiki->pos[X] + ap->child[0]->pos[X]; 
		//cy = jiki->pos[Y] + ap->child[0]->pos[Y]; 
		//cz = jiki->pos[Z] + ap->child[0]->pos[Z];

		camera_x[ MAIN_CAMERA ] =   jiki->pos[X] + SOZ_get_sin( ang_y ) * 512;
		camera_y[ MAIN_CAMERA ] =   jiki->pos[Y] + SOZ_get_sin( ang_x ) * 512;
		camera_z[ MAIN_CAMERA ] =  -jiki->pos[Z] + SOZ_get_cos( ang_y ) * 512;

		camera_at_x[ MAIN_CAMERA ] =  jiki->pos[X];//  + SOZ_get_sin( ap->angle[Y] ) * 512;		//
		camera_at_y[ MAIN_CAMERA ] =  jiki->pos[Y];
		camera_at_z[ MAIN_CAMERA ] =  -jiki->pos[Z];// + SOZ_get_cos( ap->angle[Y] ) * 512;		// 


		if( camera_y[ MAIN_CAMERA ] <= GROUND + 64.0f )
		{
			camera_y[ MAIN_CAMERA ] = camera_pos_y;
			jiki->angle[X] = ang_x;
		}

		if( game_type == 101 )
		{
			rp->camera[ X ] = camera_x[ MAIN_CAMERA ];
			rp->camera[ Y ] = camera_y[ MAIN_CAMERA ];
			rp->camera[ Z ] = camera_z[ MAIN_CAMERA ];
		}
		//camera_ang_x[0] = SOZ_atan2( camera_x[0], camera_y[0], jiki->pos[X], jiki->pos[Y] );
		//camera_ang_z[0] = SOZ_atan2( camera_x[0], camera_z[0], jiki->pos[X], jiki->pos[Z] );
	}

	else if( jiki != NULL && game_type == 501 )
	{
		camera_x[ MAIN_CAMERA ] =  rp->camera[X];
		camera_y[ MAIN_CAMERA ] =  rp->camera[Y];
		camera_z[ MAIN_CAMERA ] =  rp->camera[Z];

		camera_at_x[ MAIN_CAMERA ] =  jiki->pos[X];//  + SOZ_get_sin( ap->angle[Y] ) * 512;		//
		camera_at_y[ MAIN_CAMERA ] =  jiki->pos[Y];
		camera_at_z[ MAIN_CAMERA ] =  -jiki->pos[Z];// + SOZ_get_cos( ap->angle[Y] ) * 512;		// 
	}
#if DEBUG
	else
	{
		if( SOZ_Inkey_DAT( DIK_D ) != 0 )
			camera_x[ MAIN_CAMERA ] +=  50;
		else if( SOZ_Inkey_DAT( DIK_A ) != 0 )
			camera_x[ MAIN_CAMERA ] += -50;
		else if( SOZ_Inkey_DAT( DIK_W ) != 0 )
			camera_z[ MAIN_CAMERA ] +=  50;
		else if( SOZ_Inkey_DAT( DIK_S ) != 0 )
			camera_z[ MAIN_CAMERA ] += -50;
	}
#endif
	//SOZ_camera_move( 0 );
	SOZ_camera_set_at_move( MAIN_CAMERA );
}

void camera_control_start( void )
{
	TASK *ap, *actp;
	ANGLE ang_x, ang_y;
	ang_x = jiki->angle[X] %= 0xffff;
	ang_y = jiki->angle[Y] %= 0xffff;
	ap = TASK_start( key_camera_control_exec, NO_GROUP, "�L�[�ŃJ�������R���g���[��" );
	camera_x[ MAIN_CAMERA ] =   jiki->pos[X] + SOZ_get_sin( ang_y ) * 512;
	camera_y[ MAIN_CAMERA ] =   jiki->pos[Y] + SOZ_get_sin( ang_x ) * 512;
	camera_z[ MAIN_CAMERA ] =  -jiki->pos[Z] + SOZ_get_cos( ang_y ) * 512;
	ap->work1[X] = mouse_x;			//
	ap->work1[Y] = mouse_y;			//
	ap->ang_spd[Y] = 0x0;			//
	ap->exe_pri = 0;				//
	if( game_type != 500 )
	{
		actp = TASK_start( mouse_camera_control_exec, NO_GROUP, "�}�E�X�ŃJ�������R���g���[��" );
		actp->parent = ap;				//�e�q�֌W������
		ap->child[ 0 ] = actp;			//�e�q�֌W������
	}

}