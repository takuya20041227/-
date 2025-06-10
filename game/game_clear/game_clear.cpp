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



//---------------------------------------------------------------------------------
//当たるとビルを壊す
//---------------------------------------------------------------------------------
void hit_mobu_check( TASK *ap )
{
	TASK *actp;
	for( actp = ap_start; actp != NULL; actp = actp->next )			//タスクの全走査
		if( actp->task_group == OBJECT_GROUP )						//オブジェクトなら
			if( kawa_3d_hit_check( ap, actp ) != 0 )				//当たっていたら
				actp->HP = 0;										//HPを0にする
}

//---------------------------------------------------------------------------------
//ビルの破壊を成功させたときに仲間のUFOが飛んでくる
//---------------------------------------------------------------------------------
void mobu_ufo_exec( TASK *ap )
{
	ap->pos[Z] += ap->vec[Z];
	ap->vec[Z] += ap->acc[Z];
	if( ap->pos[ Z ] > 45000.0f )
	{
		TASK_end( ap );
		return;
	}
	task_id_checge( ap, 0 );										//視錐台カリング
	hit_mobu_check( ap );											//当たったオブジェクトを破壊する
}

void mobu_ufo_start( FLOAT x, FLOAT y )
{
	TASK *ap;
	ap = TASK_start_MODEL( mobu_ufo_exec, NO_GROUP, MODEL_JIKI, TEX_JIKI, "モブのUFO" );
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
//仲間のUFOのジェネレーター
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
			x = jiki->pos[ X ] + F_Rand2( -10000, 10000 );	//自機の近くから出るようにする
			y = camera_y[0] + F_Rand2( -2500, 3000 );		//上下にランダムでいれる
			if( y < GROUND )								//地面より下に行ったら
				y = GROUND;									//地面に固定する

			mobu_ufo_start( x, y );							//UFOを出現させる
		}
		ap->TIMER = RESET;								//初期化
	}
}

void mobu_ufo_generator_start( void )
{
	TASK *ap;
	ap = TASK_start( mobu_ufo_generator_exec, MANE_GROUP, "ジェネレーター" );
	ap->TIMER = TIME_M;
}


//---------------------------------------------------------------------------------
//ゲームクリアの文字を表示する
//---------------------------------------------------------------------------------
void clear_exec( TASK *ap )
{
	
}

void clear_start( void )
{
	TASK *ap;
	ap = TASK_start_GRP( clear_exec, UI_GROUP, TEX_UI_FONT, clear_rect, 0, "ゲームクリア" );
	ap->pos[X] = WINDOW_WIDTH_HALF;								//真ん中
	ap->pos[Y] = WINDOW_HEIGHT_HALF;							//真ん中
}		


