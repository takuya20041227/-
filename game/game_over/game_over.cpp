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
SINT32 red_efe_case = 1;

PRIM_POLY background_poly[]=										//地球の後ろで使うポリゴン
{
	{        0.0f,          0.0f, 1.0f, 1.0f, 0x60ff0000},			//
	{WINDOW_WIDTH,          0.0f, 1.0f, 1.0f, 0x60ff0000},			//
	{        0.0f, WINDOW_HEIGHT, 1.0f, 1.0f, 0x60ff0000},			//
	{WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 1.0f, 0x60ff0000},			//
};

PRIM_POLY shutdown_up_poly[]=										//
{
	{        0.0f, 0.0f, 1.0f, 1.0f, 0xff000000},			//
	{WINDOW_WIDTH, 0.0f, 1.0f, 1.0f, 0xff000000},			//
	{        0.0f, 0.0f, 1.0f, 1.0f, 0xff000000},			//
	{WINDOW_WIDTH, 0.0f, 1.0f, 1.0f, 0xff000000},			//
};

PRIM_POLY shutdown_down_poly[]=										//
{
	{        0.0f, WINDOW_HEIGHT, 1.0f, 1.0f, 0xff000000},			//
	{WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 1.0f, 0xff000000},			//
	{        0.0f, WINDOW_HEIGHT, 1.0f, 1.0f, 0xff000000},			//
	{WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 1.0f, 0xff000000},			//
};


//------------------------------------------------------------------------------------------------------------------------------------------------------
//ミサイルが自機に当たった時に赤い画面が出てくる
//------------------------------------------------------------------------------------------------------------------------------------------------------
void shut_down_drawfubc( TASK *ap )
{
	SOZ_set_texture( 0, NULL );
	SOZ_set_culling( D3DCULL_NONE );

	//プリミティブ転送
	SOZ_render_start();
	SOZ_primitive_draw( D3DPT_TRIANGLESTRIP, 2, shutdown_up_poly, sizeof( PRIM_POLY ), FVF_POLY );
	SOZ_primitive_draw( D3DPT_TRIANGLESTRIP, 2, shutdown_down_poly, sizeof( PRIM_POLY ), FVF_POLY );
	SOZ_render_end();
}

void shut_down_exec(TASK *ap)
{
	PRIM_POLY *pp, *actpp;
	SINT32 i;
	pp = &shutdown_up_poly[ 2 ];
	actpp = &shutdown_down_poly[ 2 ];

	
	if( shutdown_up_poly[2].y >= WINDOW_HEIGHT_HALF )
	{
		ap->TIMER++;
		if( ap->TIMER > 40 )
		{
			shutdown_up_poly[2].y = 0.0f;
			shutdown_up_poly[3].y = 0.0f;
			shutdown_down_poly[2].y = WINDOW_HEIGHT;
			shutdown_down_poly[3].y = WINDOW_HEIGHT;
			game_type = TITLE_SCENE;
			TASK_all_init();							//タスクを全て消す
			return;										//
		}
	}
	else
	{
		for( i = 0; i < 2; i++ )
		{
			pp->y += 15.0f;
			actpp->y -= 15.0f;
			pp++;
			actpp++;
		}
	}
}

void shut_down_start( void )
{
	TASK *ap;
	ap = TASK_start_DRAWFUNC( shut_down_exec, shut_down_drawfubc, NO_GROUP, "暗くなる" );
	ap->pri = 10000 * WP;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//ミサイルが自機に当たった時に赤い画面が出てくる
//------------------------------------------------------------------------------------------------------------------------------------------------------
void red_hit_efe_drawfubc( TASK *ap )
{
	SOZ_set_texture( 0, NULL );
	SOZ_set_culling( D3DCULL_NONE );

	//プリミティブ転送
	SOZ_render_start();
	SOZ_primitive_draw( D3DPT_TRIANGLESTRIP, 2, background_poly, sizeof( PRIM_POLY ), FVF_POLY );
	SOZ_render_end();
}

void red_hit_efe_exec(TASK *ap)
{
	ap->TIMER++;
	if( ap->TIMER > 10 )
	{
		red_efe_case = 0;
		TASK_end( ap );
		return;
	}
}

void red_hit_efe_start( void )
{
	TASK *ap;
	ap = TASK_start_DRAWFUNC( red_hit_efe_exec, red_hit_efe_drawfubc, NO_GROUP, "赤くなる" );
	ap->pri = 9999 * WP;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//ずっと赤いと雰囲気ないので定期的に赤い画面を出すように制御してくれるタスク
//------------------------------------------------------------------------------------------------------------------------------------------------------
void efe_red_window_mane_exec( TASK *ap ) 
{
	switch( red_efe_case )
	{
		case 0:
			ap->TIMER++;
			if( ap->TIMER > 20 )
				red_efe_case = 1;
			break;

		case 1:
			//自機にあたるとred_efe_caseの値が変わる
			break;

		case 2:
			red_hit_efe_start();						//赤い画面を出す
			red_efe_case = 3;
			break;

		case 3:
			ap->TIMER = RESET;							//タイマーを初期化しておく
			//値は赤い画面のタスクで初期化する
			break;
	}
}

void efe_red_window_mane_start( void )
{
	TASK *ap;
	ap = TASK_start( efe_red_window_mane_exec, MANE_GROUP, "赤い画面をだす" );
}



//------------------------------------------------------------------------------------------------------------------------------------------------------
//ミサイルが自機以外に当たった時に花に当たる 
//------------------------------------------------------------------------------------------------------------------------------------------------------
void flower_exec( TASK *ap )
{
	FLOAT sa;
	ap->pos[X] += ap->vec[X];					//
	ap->pos[Y] += ap->vec[Y];					//
	ap->pos[Z] += ap->vec[Z];					//
	ap->ang[Z] += 0x200;						//
	if( ( ap->grp_mode & USE_3DPOS ) != 0 )
	{
		ap->vec[Y] += ap->acc[Y];					//
		//task_id_checge( ap, 0 );					//視錐台カリング
		if( ap->pos[ Y ] <= GROUND )				//
		{
			TASK_end( ap );							//
			return;
		}
	}
	else
	{
		sa = 64.0f * ap->scale[X];
		if( not_range( WINDOW_WIDTH + sa, ap->pos[X] ) || not_range( ap->pos[X], -sa ) )
			if( not_range( WINDOW_HEIGHT + sa, ap->pos[Y] ) || not_range( ap->pos[Y], -sa ) )
			{
				TASK_end( ap );
				return;
			}
	}
}

void flower_start( FLOAT x, FLOAT y, FLOAT z, FLOAT vec_x, FLOAT vec_y, FLOAT vec_z, SINT32 pos_flag )
{
	TASK *ap;
	ap = TASK_start_GRP( flower_exec, NO_GROUP, TEX_FLOWER, flower_rect, Rand2( 0, 8 ), "花たち" );
	ap->grp_mode |= pos_flag;																				//3D座標に変換する
	ap->pos[X] = x;
	ap->pos[Y] = y;
	ap->pos[Z] = z;
	ap->vec[X] = vec_x;
	ap->vec[Y] = vec_y;
	ap->vec[Z] = vec_z;
	ap->acc[Y] = -0.35f;
	ap->scale[X] = F_Rand2( 1.0f, 2.0f );
	ap->scale[Y] = ap->scale[X];
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//ヘリのミサイルの当たり判定
//------------------------------------------------------------------------------------------------------------------------------------------------------
void missile_hit_check( TASK *ap )
{
	TASK *actp;
	ANGLE ang;
	FLOAT vec_x, vec_y; 
	for( actp = ap_start; actp != NULL; actp = actp->next )
	{
		if( kawa_3d_hit_check( ap, actp ) != 0 )
		{
			if( actp->task_group == JIKI_GROUP )
				if( red_efe_case == 1 )							//もし赤い画面を出せる状態なら
				{
					red_efe_case = 2;							//赤い画面をだすケースに飛ばす
					actp->SCENE = 100;
				}

			if( actp->task_group == JIKI_GROUP || actp->task_group == OBJECT_GROUP )
			{
				beam_bom_start( ap->pos[X], ap->pos[Y], ap->pos[Z], F_Rand2( 0.75f, 2.25f ) );
				TASK_end(ap);
				return;
			}
		}
	}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//ヘリのミサイルタスク
//------------------------------------------------------------------------------------------------------------------------------------------------------
void missile_exec(TASK *ap)
{
	SINT32 max;
	ap->pos[X] -= ap->vec[X];
	ap->pos[Y] -= ap->vec[Y];
	ap->pos[Z] -= ap->vec[Z];
	//ap->ang[Z] += 0x400;
	missile_hit_check( ap );

	//----------移動の制御----------//
	max = 0;
	if( ap->pos[X] >= 50000.0f )			//特定の座標を超えたら
		max = 1;							//超えたことを伝える
	else if( ap->pos[X] <= 10000.0f )		//特定の座標より小さくなったら
		max = 1;							//超えたことを伝える

	if( ap->pos[Z] >= 50000.0f )			//特定の座標を超えたら
		max = 1;							//超えたことを伝える
	else if( ap->pos[Z] <= 10000.0f )		//特定の座標より小さくなったら
		max = 1;							//超えたことを伝える
	
	if( ap->pos[Y] >= 10000.0f )			//特定の座標を超えたら
		max = 1;							//超えたことを伝える
	else if( ap->pos[Y] <= GROUND )			//特定の座標より小さくなったら
		max = 1;							//超えたことを伝える

	if( max != 0 )
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
	ap->ang[Y] = SOZ_atan2( jiki->pos[Z], jiki->pos[X], ap->pos[Z], ap->pos[X] );
	ap->ang[X] = SOZ_atan2( jiki->pos[Z], jiki->pos[Y], ap->pos[Z], ap->pos[Y] );
	//ap->ang[Z] = 0x8000;
	ap->vec[X] = SOZ_get_sin( ap->ang[Y] + Rand2( 0x0, 0x200 ) ) * 120.0f;
	ap->vec[Y] = SOZ_get_sin( ap->ang[X] + Rand2( 0x0, 0x200 ) ) * 120.0f;
	ap->vec[Z] = SOZ_get_cos( ap->ang[Y] + Rand2( 0x0, 0x200 ) ) * 120.0f;
	//ap->ang[X] *= -1;
	ap->ang[Y] *= -1;
	ap->sphire = 128.0f;
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
	if( ap->TIMER % 40 == 0 )
		if( Rand2( 0, 100 ) % 3 == 0 )
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
	
	actp = TASK_start_MODEL( game_over_propera_exec, NO_GROUP, MODEL_PROPELLER, TEX_HERI, "ゲームオーバのプロペラ" );
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







