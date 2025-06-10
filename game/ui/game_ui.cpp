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

#define	BAR_SCALE		1.0f

//------------------------------------------------------------------------------------------------------------------------------------------------------
//ビルのHPを表示
//------------------------------------------------------------------------------------------------------------------------------------------------------
void hp_bar_exec( TASK *ap )
{
	FLOAT hp_scale;
	SINT32 hp;										//HPの差分を確認する
	hp = MAIN_BILL_HP_MAX - main_bill_hp;			//HPのマックス値と現在のHPの差分を見る
	hp_scale = hp * ap->fwork1[X];					//差に乗算してサイズを減らす
	ap->scale[Y] = BAR_SCALE  - hp_scale;				//HPに合わせてサイズが変動
	if( main_bill_hp <= 0 )							//HPが0になったら
		ap->base_color[0][0] = 0x00;				//透明にする
}

void main_bill_hp_exec( TASK *ap )
{

}

void main_bill_hp_start( void )
{
	TASK *ap, *actp;
	ap = TASK_start_GRP( main_bill_hp_exec, UI_GROUP, TEX_OBJECT_ICON, main_bill_rect, 0, "メインビルのアイコン" );
	ap->pos[X] = 140.0f;
	ap->pos[Y] = WINDOW_HEIGHT_HALF;
	ap->pri = UI_PRI * WP;
	ap->scale[X] = 2.0f;
	ap->scale[Y] = ap->scale[X];

	ap = TASK_start_GRP( main_bill_hp_exec, UI_GROUP, TEX_OBJECT_ICON, hp_bar_rect, 0, "メインビルのHP表示" );
	ap->pos[X] = 20;
	ap->pos[Y] = WINDOW_HEIGHT_HALF + 42.0f;
	ap->scale[Y] = BAR_SCALE + 0.02f;									//横バーを短くする
	ap->scale[X] = 1.3f;									//少し太くする
	ap->ang[Z] = 0x4000;									//横にする
	ap->base_color[ 0 ][ 1 ] = 0x0;							//黒にするために色を抜く
	ap->base_color[ 0 ][ 2 ] = 0x0;							//黒にするために色を抜く
	ap->base_color[ 0 ][ 3 ] = 0x0;							//黒にするために色を抜く
	ap->pri = UI_PRI * WP;									//描画優先度

	actp = TASK_start_GRP( hp_bar_exec, UI_GROUP, TEX_OBJECT_ICON, hp_bar_rect, 0, "メインビルのHP表示" );
	actp->pos[X] = ap->pos[X] + 2;							//
	actp->pos[Y] = ap->pos[Y];								//
	actp->scale[Y] = BAR_SCALE;								//横バーを短くする
	actp->ang[Z] = 0x4000;									//横にする
	actp->fwork1[X] = BAR_SCALE / ( FLOAT )MAIN_BILL_HP_MAX;//HPが1つ減るとどこまでサイズが落ちるか計算する
	actp->pri = ap->pri + 1;

}


//--------------------------------------------------------------------------------------------------------------------------
//ゲームクリアの条件を表示する
//--------------------------------------------------------------------------------------------------------------------------
void show_game_goal_exec( TASK *ap )
{
	alpha_chenge( ap, 0xff, 0xa0 );
	if( ap->TIMER > TIME_S * 10 )
	{
		TASK_end( ap );
		return;
	}
}

void show_game_goal_start( void )
{
	TASK *ap;
	ap = TASK_start_GRP( show_game_goal_exec, UI_GROUP, TEX_UI_FONT, game_goal_rect, 0, "ゲームのクリア条件" );
	ap->pos[X] = WINDOW_WIDTH_HALF;						//横
	ap->pos[Y] = WINDOW_HEIGHT_HALF +60.0f;			//縦
	ap->scale[X] = 1.5f;
	ap->scale[Y] = ap->scale[X];
	ap->pri = UI_PRI * WP;								//描画優先度

	ap = TASK_start_GRP( show_game_goal_exec, UI_GROUP, TEX_UI_FONT, game_goal_rect, 1, "ゲームのクリア条件" );
	ap->pos[X] = WINDOW_WIDTH_HALF;						//横
	ap->pos[Y] = WINDOW_HEIGHT_HALF - 40.0f;			//縦
	ap->scale[X] = 1.5f;
	ap->scale[Y] = ap->scale[X];
	ap->pri = UI_PRI * WP;								//描画優先度
}


//--------------------------------------------------------------------------------------------------------------------------
//時間を計測する
//--------------------------------------------------------------------------------------------------------------------------
void timer_drawfunc( TASK *ap )
{
	TASK spr;
	SINT8 str[4];												

	TASK_init_member_pointer( &spr );						//まずはタスクメモリの初期化
	sprintf( str, "%2d", ap->work1[Y] );		 			//秒をメモリに保存する
	spr.uv_rect = number_rect;								//数字の矩形を格納
	spr.tex_no  = TEX_UI_FONT;								//数字があるテクスチャーを格納
	
	spr.pos[X] = ap->pos[X] - 96.0f;						//座標を入れる
	spr.pos[Y] = ap->pos[Y] + 1.0f;								//座標を入れる

	spr.scale[X] = 2.0f;
	spr.scale[Y] = spr.scale[X];

	spr.base_color[0][2] = ap->base_color[0][2];			//ベースカラーの緑を
	spr.base_color[0][3] = ap->base_color[0][2];			//
	spr.pri = ap->pri;

//分の描画
	spr.anime_no = ap->work1[X];						 	//分を表示
	SOZ_sprite_draw( &spr );								//ここで描画する

	spr.pos[X] += 96.0f  * spr.scale[X];								
//秒の描画
	if( str[ 0 ] >= '0' && str[ 0 ] <= '9' )			//
	{
		spr.anime_no = str[ 0 ] - '0'; 					//文字列の0から文字列の0を引くと数字の0になる
		if( spr.anime_no == 6 )
			spr.anime_no = 0;
		SOZ_sprite_draw( &spr );						//ここで描画
	}
	else
	{
		spr.anime_no = 0;		//計算結果は0
		SOZ_sprite_draw( &spr );			
	}

	spr.pos[X] += 64.0f * spr.scale[X];
	if( str[ 1 ] >= '0' && str[ 1 ] <= '9' )			//
	{
		spr.anime_no = str[ 1 ] - '0'; 					//文字列の0から文字列の0を引くと数字の0になる
		SOZ_sprite_draw( &spr );						//ここで描画
	}
	

}

void timer_exec( TASK *ap )
{
#if DEBUG
	if( SOZ_Inkey_TRG(DIK_I) != 0 )
	{
		ap->work1[Y] = 0;											//秒を0に
		ap->work1[X] = 0;											//分も0に
	}
#endif

	if( game_type == 101 )											//ゲーム中なら
	{
		SINT32 color_gb_box[ 2 ] = {0xff, 0x60};					//緑と青の値
		ap->TIMER++;												//フレームを計測
		if( ap->TIMER % TIME_S == 0 )								//もし一秒経ったら
			if( ap->work1[ Y ] > 0 )								//0より大きいなら
				ap->work1[ Y ]--;									//秒数を減らす

		if( ap->work1[ X ] > 0 )									//もし0分じゃなければ
		{
			if( ap->TIMER % TIME_M == 0 )							//もしも一分経ったら
				ap->work1[ Y ] = 60;								//秒数もリセット

			if( ap->work1[ Y ] == 59 && ap->TIMER % TIME_S == 0 )
				ap->work1[ X ]--;									//分を加算
		}

		if( ap->work1[ X ] <= 0 && ap->work1[ Y ] <= 30 )			//残り時間が30秒なら
		{
			if( ap->TIMER % ap->work2[ Z ] == 0 )					//特定のフレーム経つと
				ap->work2[ Y ]++;									//加算する

			if( ap->TIMER % (TIME_S * 7) == 0 )
				if( ap->work1[ Y ] > 0 )							//0秒でないなら
					ap->work2[ Z ] -= 2;									//点滅までの時間を早くする
		}

		if( ap->work1[ X ] <= 0 && ap->work1[ Y ] <= 0 )			//0分0秒になったら
		{
			game_type = 120;										//ゲームオーバーに移動
			game_over_flag = 1;										//フラグを
			TASK_end_group( BREAK_OBJECT_GROUP );					//オブジェクトを消す
			TASK_end( ap );
			return;
		}

		ap->work2[ Y ] %= 2;											//0と1を交互に行くようにする

		ap->base_color[ 0 ][ 2 ] = color_gb_box[ ap->work2[ Y ] ];		//赤と白を交互に行く
		ap->base_color[ 0 ][ 3 ] = color_gb_box[ ap->work2[ Y ] ];		//赤と白を交互に行く
	}
}

void timer_start( void )
{
	TASK *ap;
	ap = TASK_start_DRAWFUNC( timer_exec, timer_drawfunc, UI_GROUP, "ゲームの時間を計測" );
	ap->pos[X] = WINDOW_WIDTH_HALF - 92.0f;
	ap->pos[Y] = 72.0f;
	ap->work1[X] = 3;										//分
	ap->work1[Y] = 60;										//秒
	ap->work2[Z] = 15;
	ap->pri = UI_PRI;
}
