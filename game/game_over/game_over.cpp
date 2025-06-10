//------------------------------------------------------------------------------------------------------------------------------------------------------
//                systemOZ Ver3
//			ゲームメインプログラム
//						programed by TEAM_TAKUYA
//------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef WINDOWS_PC
#include    "../../../libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/town_break/src/game/game_include.h"
#include    "../include.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------
//ヘリのタスク
//------------------------------------------------------------------------------------------------------------------------------------------------------
SINT32 game_over_flag = 0;


//------------------------------------------------------------------------------------------------------------------------------------------------------
//ヘリのミサイルタスク
//------------------------------------------------------------------------------------------------------------------------------------------------------
void missile_exec(TASK *ap)
{
	ap->pos[X] += ap->vec[X];
	ap->pos[Y] += ap->vec[Y];
	ap->pos[Z] += ap->vec[Z];
	ap->ang[Z] += 0x400;
	if( kawa_3d_hit_check( ap, jiki ) != 0 )
	{
		beam_bom_start( ap->pos[X], ap->pos[Y], ap->pos[Z], F_Rand2( 0.25f, 1.25f ) );
		TASK_end( ap );
		return;
	}
	if( ap->pos[ Y ] < GROUND )
	{
		TASK_end( ap );
		return;
	}
}

void missile_start( FLOAT x, FLOAT y,  FLOAT z )
{
	TASK *ap;
	ap = TASK_start_MODEL( missile_exec, NO_GROUP, MODEL_MISSILE, TEX_MISSILE, "ミサイル" );
	ap->pos[X] = x;
	ap->pos[Y] = y;
	ap->pos[Z] = z;
	ap->ang[Y] = SOZ_atan2( ap->pos[X], ap->pos[Z], jiki->pos[X], jiki->pos[Z] );
	ap->ang[X] = SOZ_atan2( ap->pos[X], ap->pos[Y], jiki->pos[X], jiki->pos[Y] );
	ap->vec[X] = SOZ_get_sin( ap->ang[Y] ) * 120.0f;
	ap->vec[Y] = SOZ_get_sin( ap->ang[X] ) * 120.0f;
	ap->vec[Z] = SOZ_get_cos( ap->ang[Y] ) * 120.0f;
	ap->sphire = 256.0f;
}
		

//------------------------------------------------------------------------------------------------------------------------------------------------------
//ヘリのタスク
//------------------------------------------------------------------------------------------------------------------------------------------------------
void game_over_propera_exec( TASK *ap )
{
	ap->pos[X] = ap->parent->pos[X]  + SOZ_get_sin( ap->parent->ang[Z] ) * 512.0f;
	ap->pos[Y] = ( ap->parent->pos[Y] ) + SOZ_get_cos( ap->parent->ang[Z] ) * 462.0f;
	ap->pos[Z] = ap->parent->pos[Z] + SOZ_get_sin( ap->parent->ang[X] ) * 512.0f;
	ap->ang[Y] += 0x1000;
	ap->TIMER++;
	if( ap->TIMER % 15 == 0 )
		missile_start( ap->pos[X], ap->pos[Y], ap->pos[Z] );
}
 
void game_over_heri_exec( TASK *ap )
{
	ap->pos[Z] -= 120.0f;

	ap->TIMER++;
	//if( ap->TIMER > TIME_S * 2 )
	if( ap->pos[ Z ] <= 0 )
	{
		TASK_end( ap->child[0] );
		TASK_end( ap );
		return;
	}
}

void geme_over_heri_start( FLOAT x )
{
	TASK *ap, *actp;
	ap = TASK_start_MODEL( game_over_heri_exec, NO_GROUP, MODEL_HERI, TEX_HERI, "ヘリ" );
	ap->grp_mode = TEST_ZBUFFER | WRITE_ZBUFFER  | NO_SHADOW | USE_LIGHTING | USE_SPECULAR;
	ap->pos[X] = x;
	ap->pos[Y] = 2000.0f + F_Rand2( -256.0f, 256.0f );
	ap->pos[Z] = 50000.0f;

	ap->TIMER = TIME_H;
	
	actp = TASK_start_MODEL( game_over_propera_exec, NO_GROUP, MODEL_PROPELLER, TEX_HERI, "プロペラ" );
	actp->grp_mode = TEST_ZBUFFER | WRITE_ZBUFFER  | NO_SHADOW | USE_LIGHTING | USE_SPECULAR;
	actp->pos[X] = ap->pos[X] + SOZ_get_sin( ap->ang[Y] ) * 128.0f;
	actp->pos[Y] = ( ap->pos[Y] + 462.0f ) + SOZ_get_sin( ap->ang[X] ) * 256.0f;
	actp->pos[Z] = ( ap->pos[Z] ) + SOZ_get_sin( ap->ang[Y] ) * 512.0f;
	actp->parent = ap;
	ap->child[ 0 ] = actp;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//ゲームオーバーになると大量にヘリを飛ばす
//------------------------------------------------------------------------------------------------------------------------------------------------------
void game_over_exec( TASK *ap )
{
	SINT32 i;
	FLOAT x;
	ap->TIMER++;

	ap->work1[X]++;
	if( ap->work1[ X ] > TIME_S * 2 + 30 )
	{
		SOZ_play_se( SE_HERI, 2.0f, 1, 1.0f );
		ap->work1[X] = 0;
	}
	if( ap->timer % 15 == 0 )
	{
		for( i = 0; i < Rand2( 2, 4 ); i++ )
		{
			x = jiki->pos[ X ] + F_Rand2( -10000, 10000 );	//自機の近くから出るようにする
			geme_over_heri_start( x );
		}
	}
}

void game_ovre_start( void )
{
	TASK *ap;
	ap = TASK_start( game_over_exec, MANE_GROUP, "ヘリを出す" );
	
}








