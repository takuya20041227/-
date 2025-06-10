//------------------------------------------------------------------------------------------------------------------------------------------------------
//                systemOZ Ver3
//			ゲームメインプログラム
//						programed by TEAM_TAKUYA
//------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef WINDOWS_PC
#include    "../../../libs/systemOZ_v4/soz.h"
#else
//#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/town_break/src/game/game_include.h"
#include    "../include.h"



PRIM_POLY3D_TEX title_logo[]=		//タイトルロゴを
{
	{      0.0f,    0.0f,  0.0f, 0xffffffff,  0.0f, 0.0f },
	{   2048.0f,    0.0f,  0.0f, 0xffffffff,  1.0f, 0.0f },
	{      0.0f, 1024.0f,  0.0f, 0xffffffff,  0.0f, 1.0f },
	{   2048.0f, 1024.0f,  0.0f, 0xffffffff,  1.0f, 1.0f },
};



//------------------------------------------------------------------------------------------------------------------------------------------------------
//タイトルロゴの表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void title_logo_drawfunc( TASK *ap )
{
	SOZ_set_model_param( ZBUF_TEST | ZBUF_WRITE, BILINEAR_ON, LIGHTING_OFF, SPECULAR_OFF );
	SOZ_ResetClipping();
	SOZ_reset_fog();           //fogをリセット
	SOZ_set_culling( D3DCULL_NONE ); 
	SOZ_blend_setting( BLEND_NORMAL );
	SOZ_set_texture( 0, TEX_TITLE );

	//プリミティブ転送
	SOZ_matrix_model_maker( 0, ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X],  ap->ang[Y], ap->ang[Z], ap->scale[X], ap->scale[Y], ap->scale[Z] );
	SOZ_render_start();
	SOZ_primitive_draw( D3DPT_TRIANGLESTRIP, 2, title_logo, sizeof( PRIM_POLY3D_TEX ), FVF_POLY3D_TEX );
	SOZ_render_end();
}

void title_logo_exec( TASK *ap )
{
	SINT32 i;										//for分用の変数
	FLOAT sa, abs_sa;								//絶対値を求める
	FLOAT pos_box[6][2] =							//座標の保存の配列
	{
		{ ap->fwork1[X], jiki->pos[X] },			//自機の横
		{ ap->fwork1[Y], jiki->pos[Y] },			//自機の縦
		{ ap->fwork1[Z], jiki->pos[Z] },			//自機の前後
		{ ap->fwork2[X], camera_x[0]  },			//カメラの横
		{ ap->fwork2[Y], camera_y[0]  },			//カメラの縦
		{ ap->fwork2[Z], camera_z[0]  },			//カメラの前後
	};

	if( ap->timer >= 15 )							//カメラが1フレーム動いてしまうので数フレーム遅らせる
	{
		if( ap->SWITCH != 0 )						//動いていることを確認したら
		{
			if( ap->TIMER == 0 )					//計測の最初のフレームは
				ap->base_color[ 0 ][ 0 ] = 0x0;		//透明にする
			ap->fwork1[ X ] = jiki->pos[ X ];		//自機の横を保存
			ap->fwork1[ Y ] = jiki->pos[ Y ];		//自機の縦を保存
			ap->fwork1[ Z ] = jiki->pos[ Z ];		//自機の前後を保存
			ap->fwork2[ X ] = camera_x[ 0 ];		//カメラの横を保存
			ap->fwork2[ Y ] = camera_y[ 0 ];		//カメラの縦を保存
			ap->fwork2[ Z ] = camera_z[ 0 ];		//カメラの前後を保存
			ap->TIMER++;							//タイマー計測
		}

		for( i = 0; i < 6; i++ )					//配列分回す
		{
			sa = pos_box[ i ][ 0 ] - pos_box[ i ][ 1 ];
			abs_sa = (FLOAT)fabs( (DOUBLE)sa );		//絶対値を見る
			if( abs_sa > 10 )						//自機かカメラが動いたら( すこし余白を入れる )
			{
				ap->TIMER = 0;						//透明な時に動いたとき用に初期化
				ap->SWITCH = 1;						//ロゴを透明にする
				break;								//回すのを辞める
			}
		}

		for( i = 0; i < 3; i++ )
			if( SOZ_Mouse_Button( i ) != 0 )
			{
				ap->TIMER = 0;						//透明な時に動いたとき用に初期化
				ap->SWITCH = 1;						//ロゴを透明にする
				break;								//回すのを辞める
			}


		if( ap->TIMER >= TIME_S * 5 )				//特定の時間を超えて
			if( ap->TIMER % 4 == 0 )				//数フレーム立つと
				ap->base_color[ 0 ][ 0 ] += 0x8;	//だんだんアルファ値を上げていく

		if( ap->base_color[ 0 ][ 0 ] > 0xff )		//アルファ値がマックスになると
			ap->base_color[ 0 ][ 0 ] = 0xff;		//固定する
	}
	else
	{
		ap->fwork2[X] = camera_x[0];				//カメラの横を保存
		ap->fwork2[Y] = camera_y[0];				//カメラの縦を保存
		ap->fwork2[Z] = camera_z[0];				//カメラの前後を保存
	}

	
}

void title_logo_start( void )
{
	TASK *ap;
	ap = TASK_start_GRP( title_logo_exec, NO_GROUP, TEX_TITLE, logo_rect, 0, "タイトルロゴ" );
	ap->pos[X] = WINDOW_WIDTH_HALF;
	ap->pos[Y] = 400.0f;
	ap->scale[X] = 0.6f;
	ap->scale[Y] = ap->scale[X]; 
	ap->fwork1[X] = jiki->pos[X];		//自機の横を保存
	ap->fwork1[Y] = jiki->pos[Y];		//自機の縦を保存
	ap->fwork1[Z] = jiki->pos[Z];		//自機の前後を保存
	ap->pri = 999 * WP;
	ap->exe_pri = 0;
	
}


#if 0
//------------------------------------------------------------------------------------------------------------------------------------------------------
//タイトルロゴのポリゴンの値をセットする
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