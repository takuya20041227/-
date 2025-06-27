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

PRIM_POLY3D_TEX ring_data[ 1024 ];																	//頂点を格納
SINT32 ring_data_index;

//虹を出す
void screen_shutdown_drawfunc( TASK *ap )														//見えなくする部分
{
	SOZ_set_model_param( ZBUF_TEST | ZBUF_WRITE, BILINEAR_ON, LIGHTING_OFF, SPECULAR_OFF );
	SOZ_ResetClipping();
	SOZ_reset_fog();           //fogをリセット
	SOZ_set_culling( D3DCULL_NONE ); 
	SOZ_blend_setting( BLEND_ADD );
	SOZ_set_texture( 0, TEX_RAINDOW );																	//テクスチャーがないことを宣言
	SOZ_matrix_model_maker( 0, ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X],  ap->ang[Y], ap->ang[Z], ap->scale[X], ap->scale[Y], ap->scale[Z] );

	SOZ_render_start();																			//ビデオカードに送信する
	SOZ_primitive_draw( D3DPT_TRIANGLESTRIP, ring_data_index - 2, ring_data, sizeof( PRIM_POLY3D_TEX ), FVF_POLY3D_TEX );	//ビデオカードにポリゴンの頂点などの情報を送る
	SOZ_render_end();																			//ビデオカードの送信を終わる
	//lpDEVICE->BeginScene();      //ビデオカードに転送開始
	//lpDEVICE->DrawPrimitiveUP(  );         //矢印の軸の縦部分
	//lpDEVICE->EndScene();	
}
void screen_shutdown_exec( TASK *ap )
{
	SINT32 angle, index;
	FLOAT x, y, vec_x, vec_y;
	index = 0;
	for( angle = 0; angle <= 0x10000; angle += 0x400 )
	{
		// リングの内角
		ring_data[ index ].x = ap->pos[X] + SOZ_get_sin( angle ) *  10000;	//サインをまわす
		ring_data[ index ].y = ap->pos[Y] + SOZ_get_cos( angle ) *  8000;//コサイン
		ring_data[ index ].z = ap->pos[Z];																//奥行きは0
		//ring_data[ index ].r = 1.0f;																//テクスチャーのどこまでを切り取るか
		ring_data[ index ].diffuse = 0x80ffffff;													//色を設定ffは透明度00は赤00は緑00は青がくっついてる
		ring_data[ index ].x = ring_data[ index ].x;												
		ring_data[ index ].y = ring_data[ index ].y;				
		ring_data[ index ].u = 1.0f;
		ring_data[ index ].v = 1.0f;
		index++;

		//リングの外角
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
	ring_data_index = index;																		//カウント
}
void screen_shutdown_start( void )
{
	TASK * ap;
	ap  =TASK_start_DRAWFUNC( screen_shutdown_exec, screen_shutdown_drawfunc, NO_GROUP, "画面を狭める" );
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

void clear_start( PARTS_RECT *pp )
{
	TASK *ap;
	ap = TASK_start_GRP( clear_exec, UI_GROUP, TEX_UI_FONT, pp, 0, "ゲームクリア" );
	ap->pos[X] = WINDOW_WIDTH_HALF;								//真ん中
	ap->pos[Y] = WINDOW_HEIGHT_HALF;							//真ん中
}		


void game_resurt_exec( TASK* ap )
{
	alpha_chenge( ap, 0xff, 0xa0 );
}

void geme_resurt_start( SINT32 anime_no )
{
	TASK *ap;
	ap = TASK_start_GRP( game_resurt_exec, NO_GROUP, TEX_UI_FONT, resurt_rect, anime_no, " ゲームの結果を表示 " );
	ap->pos[X] = WINDOW_WIDTH_HALF;
	ap->pos[Y] = WINDOW_HEIGHT_HALF + 128.0f;
	ap->scale[X] = 1.5f;
	ap->scale[Y] = ap->scale[X];
	ap->pri = 9999 * WP;

	ap = TASK_start_GRP( game_resurt_exec, NO_GROUP, TEX_UI_FONT, resurt_rect, 2, " ゲームの結果を表示 " );
	ap->pos[X] = WINDOW_WIDTH_HALF;
	ap->pos[Y] = WINDOW_HEIGHT_HALF + 256.0f;
	ap->scale[X] = 1.5f;
	ap->scale[Y] = ap->scale[X];
	ap->pri = 9999 * WP;
}

