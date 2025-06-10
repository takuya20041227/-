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
#include    "include.h"


PRIM_POLY ring_data[ 1024 ][ 1024 ];	//頂点を格納
SINT32 ring_data_index[ 1024 ];			//頂点の数をカウント


//-----------------------------------------------------------------------------------------------------------------------
//スフィアを可視化させる
//-----------------------------------------------------------------------------------------------------------------------
void sphire_debug_drawfunc( TASK *ap )
{
	SINT32 i;
	SOZ_ResetClipping();
	SOZ_reset_fog();
	SOZ_set_model_param( ZBUF_OFF, BILINEAR_OFF, LIGHTING_OFF, SPECULAR_OFF );
	SOZ_set_culling( D3DCULL_NONE ); //NONEは表でも裏でも表示
	SOZ_set_texture( 0, NULL);   //テクスチャーがないことを宣言


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
	for( actp = ap_start; actp != NULL; actp = actp->next )		//全走査する
	{
		index = 0;
		if( actp->sphire != 0.0f )						//スフィアの設定があるなら
		{
			for( angle = 0x0; angle < 0xffff; angle += 0x800 )
			{
				// リングの内角
				ring_data[ i ][ index ].x = actp->pos[ X ] + SOZ_get_sin( angle ) *  actp->sphire - 10;
				ring_data[ i ][ index ].y = ( actp->pos[ Y ] ) + SOZ_get_cos( angle ) *  actp->sphire - 10;
				ring_data[ i ][ index ].z = actp->pos[Z];
				ring_data[ i ][ index ].rhw = 1.0f;
				ring_data[ i ][ index ].diffuse = 0xffff0000;
				ring_data[ i ][ index ].x = ring_data[ i ][ index ].x;
				ring_data[ i ][ index ].y = ring_data[ i ][ index ].y;
				index++;
				//リングの外角
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
			op = &object_sphire[ ap->ID ];							//どこのアドレスに入れるかを教える
			if( op->sphire[ 0 ] != NULL )				//もしスフィアの中身がすでに入っていたら		
			{
				ring_data[ i ][ index ].x = actp->pos[ X ] + SOZ_get_sin( angle ) *  actp->sphire - 10;
				ring_data[ i ][ index ].y = ( actp->pos[ Y ] ) + SOZ_get_cos( angle ) *  actp->sphire - 10;
				ring_data[ i ][ index ].z = actp->pos[Z];
				ring_data[ i ][ index ].rhw = 1.0f;
				ring_data[ i ][ index ].diffuse = 0xffff0000;
				ring_data[ i ][ index ].x = ring_data[ i ][ index ].x;
				ring_data[ i ][ index ].y = ring_data[ i ][ index ].y;
				index++;
				//リングの外角
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
		ring_data_index[ i ] = index;		//カウント
		i++;

		
	}
}

void sphire_debug_start( void )
{
//#if DEBUG
	TASK *ap;
	ap = TASK_start_DRAWFUNC( sphire_debug_exec, sphire_debug_drawfunc , NO_GROUP, "スフィアを可視化させる" );
	ap->pri = 9999 * WP;
//#endif
}


void particle_num_exec( TASK *ap )
{
	TASK *actp;
	SINT32 particle_num;
	particle_num = 0;												//初期化	
	for( actp = ap_start; actp != NULL; actp = actp->next )
		if( actp->task_group == BREAK_EFFECTS_GROUP )
			particle_num++;

	SOZ_locate_print( 64, 8, "particle%5d", particle_num );
}

void particle_num_start( void )
{
	TASK *ap;
	ap = TASK_start( particle_num_exec, NO_GROUP, "パーティクルの数を数える" );
}


void viwe_clip_num_exec( TASK *ap )
{
	TASK *actp;
	SINT32 view_clip_num, clip_obj;
	view_clip_num = 0;												//初期化
	clip_obj = 0;													//初期化
	for( actp = ap_start; actp != NULL; actp = actp->next )
	{
		if( actp->task_group == BREAK_EFFECTS_GROUP )
			if( actp->task_id == TASK_PROGRAM )
				view_clip_num++;

		if( actp->task_group == OBJECT_GROUP )
			if( actp->task_id == TASK_PROGRAM )
				clip_obj++;													//初期化++;
	}

	SOZ_locate_print( 64, 9, "view_clip_p%5d", view_clip_num );
	SOZ_locate_print( 64, 10, "view_clip_o%5d", clip_obj );
}

void viwe_clip_num_start( void )
{
	TASK *ap;
	ap = TASK_start( viwe_clip_num_exec, NO_GROUP, "視錐台カリングの数" );
}



