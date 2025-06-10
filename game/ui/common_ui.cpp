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
//---------------タイトルでもゲーム画面でも使えるUIのソースファイル------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define	BASE_COLOR			0x70
#define	ICON_MAX			30

ICON_DATA icon_box[ ICON_MAX ];													//掴んでいるオブジェクト
SINT32 score = 0, hi_score = 0, icon_num = 0;


//------------------------------------------------------------------------------------------------------------------------------------------------------
//アイコンのボックスを全て初期化する
//------------------------------------------------------------------------------------------------------------------------------------------------------
void icon_box_all_init( void )
{
	SINT32 i;
	for( i = 0; i < ICON_MAX; i++ )										//
	{
		icon_box[ i ].unique_id = 0;									//ユニークIDの中身を0にする
		icon_box[ i ].id = 0;											//IDの中身を0にする
	}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//アイコンのボックスを1つ初期化する
//------------------------------------------------------------------------------------------------------------------------------------------------------
void icon_box_init( TASK *ap )
{ 
	SINT32 i;
	for( i = 0; i < ICON_MAX; i++ )										//
	{
		if( icon_box[ i ].unique_id == ap->unique_id )					//アイコンとタスクが一緒なら
			break;														//見つけた場所でforを止める
	}

	icon_box[ i ].unique_id = 0;										//ユニークIDの中身を0にする
	icon_box[ i ].id = 0;												//IDの中身を0にする
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//アイコンの情報を入れる
//------------------------------------------------------------------------------------------------------------------------------------------------------
void icon_param_get( TASK *ap )
{
	SINT32 i;

	for( i = 0; i < ICON_MAX; i++ )										//
		if( icon_box[ i ].unique_id == ap->unique_id )					//
			return;														//

	for( i = 0; i < ICON_MAX; i++ )										//
		if( icon_box[ i ].id == 0 )										//アイコンが0なら
			break;														//見つけた場所でforを止める

	if( icon_box[ ICON_MAX - 1 ].unique_id != NULL )					//配列が満タンなら
		return;															//中身を入れないようにする

	icon_box[ i ].unique_id = ap->unique_id;							//ユニークIDの中身を0にする
	icon_box[ i ].id = ap->ID;											//IDの中身を0にする
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//アイコンの重複を防ぐ
//------------------------------------------------------------------------------------------------------------------------------------------------------
void icon_box_check_exec( TASK *ap )
{
	SINT32 i, check, num;

	num = 0;

	check = 0;

	for( i = 0; i < ICON_MAX; i++ )
	{
		if( check > 4 )
		{
			check = 0;
			num++;
		}

		if( icon_box[ i ].id == NULL )
			break;

		check++;
	}

	icon_num = num;


	for( i = 0; i < ICON_MAX; i++ )												//基盤となる配列の番号
		for( check = i; check < ICON_MAX; check++ )								//
			if( icon_box[ i ].unique_id == icon_box[ check ].unique_id )		//
			{
				icon_box[ check ].unique_id = 0;
				icon_box[ check ].id = 0; 
			}


	
}

void icon_box_check_start( void )
{
	TASK *ap;
	ap = TASK_start( icon_box_check_exec, UI_GROUP, "アイコンが重複してたら消す" );
}



//------------------------------------------------------------------------------------------------------------------------------------------------------
//アイコンのタスク
//------------------------------------------------------------------------------------------------------------------------------------------------------
void icon_exec( TASK *ap )
{
	OBJECT_DATA * op;
	ICON_DATA *ip;
	ip = &icon_box[ ap->ID ];
	ap->task_id = TASK_GRP;												//先にグラフィックを描画するようにする
	if( ip->id == 0 )													//識別番号がなければ
	{
		ap->task_id = TASK_PROGRAM;										//描画をしない
		return;															//ここから先を実行しない
	}

//オブジェクトを掴んでいたときのアイコン
	op = &object_data[ ip->id ];										//オブジェクトの構造体にアクセスする
	ap->anime_no = op->icon;											//アイコンを表示
}

void frame_exec( TASK *ap )
{
	ICON_DATA *ip;
	ip = &icon_box[ ap->parent->ID ];
	ap->task_id = TASK_GRP;												//先にグラフィックを描画するようにする
	if( ip->id == 0 )													//識別番号がなければ
	{
		ap->task_id = TASK_PROGRAM;										//描画をしない
		return;															//ここから先を実行しない
	}
}

void icon_start( FLOAT x, FLOAT y,SINT32 id )
{
	TASK *ap, *actp;
	ap = TASK_start_GRP( icon_exec, UI_GROUP, TEX_OBJECT_ICON, object_icon_rect, 0, "アイコン" );
	ap->pos[X] = WINDOW_WIDTH - ( 72.0f * x );
	ap->pos[Y] = WINDOW_HEIGHT_QUARTER + ( 90.0f * y ) + 45.0f;
	ap->pri = UI_PRI * WP;
	ap->ID = id;														//識別番号を保存

	actp = TASK_start_GRP( frame_exec, UI_GROUP, TEX_OBJECT_ICON, object_icon_rect, 0, "アイコン" );
	actp->pos[X] = ap->pos[X];
	actp->pos[Y] = ap->pos[Y];
	actp->pri = ap->pri - 1;
	ap->child[0] = actp;
	actp->parent = ap;

}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//アイコンのタスクを出現させる
//------------------------------------------------------------------------------------------------------------------------------------------------------
void icon_set( void )
{
	SINT32 i;
	FLOAT pos_x, pos_y;
	pos_y = ICON_MAX / 5;
	pos_x = 0;
	for( i = 0; i < ICON_MAX; i++ )
	{
		if( i % 5 == 0 )
		{
			pos_x = 1;
			pos_y--;												//ここでどんどん左に移動させる
		}

		icon_start( pos_x, pos_y, i );											//アイコンのタスクを出現
		pos_x++;
	}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//手の状況
//------------------------------------------------------------------------------------------------------------------------------------------------------
void hand_ui_exec( TASK *ap )
{
	if( catch_switch == 0 )												//もし何も掴んでいなかったら
		ap->anime_no = 0;												//手のひらを広げてる
	else																//なにか掴んでいたら
		ap->anime_no = 1;												//掴んでるグラフィック

	ap->pos[Y] = WINDOW_HEIGHT_HALF + 86 - ( 90.0f * icon_num );
}

void hand_ui_start( void )
{
	TASK*ap;
	ap = TASK_start_GRP( hand_ui_exec, UI_GROUP, TEX_OBJECT_ICON, hand_ui_rect, 0, "手の状況" );
	ap->pos[X] = WINDOW_WIDTH - 200.0f;
	ap->pos[Y] = WINDOW_HEIGHT_HALF - 370.0f;
	ap->scale[X] = 2.0f;
	ap->scale[Y] = ap->scale[X];
	ap->pri = UI_PRI * WP;												//描画の優先度
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//マウスの操作説明のUI
//------------------------------------------------------------------------------------------------------------------------------------------------------
void mouse_font_ui_exec( TASK *ap )										//マウス説明の実行部
{
	if( ap->work1[ X ] == CLICK_RIGHT )									//右クリックの場合
	{
		ap->anime_no = 0;												//最初から0にしておく

		if( catch_switch != 0 )											//もし掴んでいたら
			ap->anime_no = 1;											//投げるに変える

		if( ap->anime_no == 1 )											//もし投げるになっていたら
		{
			ap->TIMER++;												//フレームを計測

			if( ap->TIMER % 15 == 0 )									//数フレームに一度
			{
				if( ap->base_color[ 0 ][ 2 ] == 0xff )					//もし青と緑がマックスなら
				{
					ap->base_color[ 0 ][ 2 ] = BASE_COLOR;				//少し青を落とす
					ap->base_color[ 0 ][ 3 ] = BASE_COLOR;				//少し緑を落とす
				}
				else													//もし青と緑がマックスではないなら
				{
					ap->base_color[0][2] = 0xff;						//青を元に戻す
					ap->base_color[0][3] = 0xff;						//緑を元に戻す
				}
			}
		}
		else															//フォントが「 掴む 」	に戻ったら
		{
			ap->base_color[0][2] = 0xff;								//青を元に戻す
			ap->base_color[0][3] = 0xff;								//緑を元に戻す
		}
	}
}


void mouse_ui_exec( TASK *ap )											//マウスの実行部
{
	ap->shader_pass = SOZ_UNCLEAR;										//初期化する

	if( ap->work1[X] == CLICK_LEFT )									//左クリックの場合
	{
		if( SOZ_Mouse_Button( 0 ) % BEAM_TIME == 0 && SOZ_Mouse_Button( 0 ) != 0 || SOZ_Mouse_Button( 0 ) == 1 )		//右クリックすると	
			ap->shader_pass = 101;										//赤をより赤くする
	}

	if( ap->work1[X] == CLICK_RIGHT  )									//右クリックの場合
	{
		if( SOZ_Mouse_Button( 1 ) != 0 )								//手を発射したとき
			ap->shader_pass = 101;										//赤をより赤くする
	}
}


void mouse_ui_start( void )
{
	TASK *ap, *actp;
	//------------右クリックの説明----------//
	ap = TASK_start_GRP( mouse_ui_exec, UI_GROUP, TEX_OBJECT_ICON, mouse_ui_rect, 0, "左クリックの説明" );
	ap->pos[X] = WINDOW_WIDTH  - 256.0f;
	ap->pos[Y] = WINDOW_HEIGHT - 236.0f;
	ap->scale[X] = 2.0f;
	ap->scale[Y] = ap->scale[X];
	ap->work1[X] = CLICK_LEFT;											//左クリックの場合
	ap->shader_param1 = 3.0f;											//赤をより赤くするシェーダーにわたすパラメーター
	ap->pri = UI_PRI * WP;												//描画の優先度

	actp = TASK_start_GRP( mouse_font_ui_exec, UI_GROUP, TEX_UI_FONT, shot_ui_rect, 0, "攻撃の説明" );
	actp->pos[X] = ap->pos[X] + 64.0f;
	actp->pos[Y] = ap->pos[Y];
	actp->work1[X] = CLICK_LEFT;				
	actp->pri = ap->pri;												//描画の優先度

	//------------左クリックの説明----------//
	ap = TASK_start_GRP( mouse_ui_exec, UI_GROUP, TEX_OBJECT_ICON, mouse_ui_rect, 1, "右クリックの説明" );
	ap->pos[X] = WINDOW_WIDTH  - 256.0f;
	ap->pos[Y] = WINDOW_HEIGHT - 100.0f;
	ap->scale[X] = 2.0f;
	ap->scale[Y] = ap->scale[X];
	ap->work1[X] = CLICK_RIGHT;											//右クリックの場合
	ap->shader_param1 = 3.0f;											//赤をより赤くするシェーダーにわたすパラメーター
	ap->pri = UI_PRI * WP;												//描画の優先度

	actp = TASK_start_GRP( mouse_font_ui_exec, UI_GROUP, TEX_UI_FONT, catch_font_rect, 0, "掴むや投げるの説明" );
	actp->pos[X] = ap->pos[X] + 64.0f;
	actp->pos[Y] = ap->pos[Y];
	actp->work1[X] = CLICK_RIGHT;				
	actp->pri = ap->pri;												//描画の優先度
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//移動キーを表示( drawfuncを使用 )
//------------------------------------------------------------------------------------------------------------------------------------------------------
void movement_key_ui_drawfunc( TASK *ap )
{
	TASK spr;
	SINT32 key_box[ 4 ] = { DIK_W, DIK_A, DIK_S, DIK_D };				//移動キーに使用してる物を使用
	SINT32 i;															//for文用の変数
	ANGLE  ang_box[ 4 ] = { 0x0000, 0xc000, 0x8000, 0x4000 };			//角度を格納

	TASK_init_member_pointer( &spr );									//まずはメモリの初期化

//座標
	spr.pos[X] = ap->pos[X];											//基準となる座標を設定
	spr.pos[Y] = ap->pos[Y];											//基準となる座標を設定

//グラフィックの設定
	spr.uv_rect = move_ment_font_rect;									//キーのアイコンの矩形を設定
	spr.tex_no  = TEX_UI_FONT;											//操作説明のグラフィック
	spr.pri     = ap->pri;												//描画の優先度

	spr.scale[X] = ap->scale[X];
	spr.scale[Y] = spr.scale[X];

	for( i = 0; i < 4; i++ )											//移動キーの数だけ回す
	{
		spr.anime_no = i;												//アニメナンバーはiと同じ
		spr.pos[Y] += 80.0f;											//縦に並べる
		if( SOZ_Inkey_DAT( key_box[ i ] ) != 0 )						//自分の識別番号と同じキーが押されていたら
		{
			spr.base_color[ 0 ][ 2 ] = BASE_COLOR;						//少し青を落とす
			spr.base_color[ 0 ][ 3 ] = BASE_COLOR;						//少し緑を落とす
		}
		else
		{
			spr.base_color[ 0 ][ 2 ] = 0xff;							//青を元に戻す
			spr.base_color[ 0 ][ 3 ] = 0xff;							//緑を元に戻す
		}
		SOZ_sprite_draw( &spr );										//最終的にここで描画する
	}
}

void movement_key_ui_exec( TASK *ap )
{

}

void movement_key_ui_start( void )
{
	TASK *ap;
	ap = TASK_start_DRAWFUNC( movement_key_ui_exec, movement_key_ui_drawfunc, UI_GROUP, "キーの説明" );
	ap->pos[X] = 70.0f;													//基準となる座標を設定
	ap->pos[Y] = KEY_POS_Y;												//基準となる座標を設定
	ap->scale[X] = 1.5f;
	ap->scale[Y] = ap->scale[X];
	ap->pri = UI_PRI * WP;												//描画の優先度
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//矢印を描画
//------------------------------------------------------------------------------------------------------------------------------------------------------
void arrow_drawfunc( TASK *ap )
{
	TASK spr;													
	SINT32 key_box[ 4 ] = { DIK_W, DIK_A, DIK_S, DIK_D };				//移動キーに使用してる物を使用
	SINT32 i;															//for文用の変数
	ANGLE  ang_box[ 4 ] = { 0x0000, 0xc000, 0x8000, 0x4000 };			//矢印の角度を設定
	TASK_init_member_pointer( &spr );									//まずはメモリの初期化

//座標
	spr.pos[X] = ap->pos[X];											//基準となる座標を設定
	spr.pos[Y] = ap->pos[Y];											//基準となる座標を設定

//角度
	spr.ang[Z] = 0x0;													//角度を初期化

//グラフィックの設定
	spr.uv_rect = arrow_rect;											//キーのアイコンの矩形を設定
	spr.tex_no  = TEX_UI_FONT;											//操作説明のグラフィック
	spr.anime_no = 0;													//アニメナンバーはiと同じ
	spr.pri     = ap->pri;												//描画の優先度
	spr.scale[X] = ap->scale[X];
	spr.scale[Y] = spr.scale[X];

	for( i = 0; i < 4; i++ )											//移動キーの数だけ回す
	{
		spr.ID = i;														//識別番号を設定
		spr.pos[Y] += 80.0f;											//縦に並べる
		spr.ang[Z] = ang_box[ i ];										//45度に回す分だけかける
		if( SOZ_Inkey_DAT( key_box[ i ] ) != 0 )						//自分の識別番号と同じキーが押されていたら
		{
			spr.base_color[ 0 ][ 2 ] = BASE_COLOR;						//少し青を落とす
			spr.base_color[ 0 ][ 3 ] = BASE_COLOR;						//少し緑を落とす
		}
		else
		{
			spr.base_color[ 0 ][ 2 ] = 0xff;							//青を元に戻す
			spr.base_color[ 0 ][ 3 ] = 0xff;							//緑を元に戻す
		}
		SOZ_sprite_draw( &spr );										//最終的にここで描画する
	}	
}

void arrow_exec( TASK *ap )
{

}

void arrow_start( void )
{
	TASK *ap;
	ap = TASK_start_DRAWFUNC( arrow_exec, arrow_drawfunc, UI_GROUP, "矢印" );
	ap->pos[X] = 180.0f;												//基準となる座標を設定
	ap->pos[Y] = KEY_POS_Y;												//基準となる座標を設定
	ap->pri = UI_PRI * WP;												//描画の優先度
	ap->scale[X] = 1.5f;
	ap->scale[Y] = ap->scale[X];
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//全体で使うUIをまとめている
//------------------------------------------------------------------------------------------------------------------------------------------------------
void common_ui_set( void )
{
	hand_ui_start();													//手の状況を伝える
	mouse_ui_start();													//マウスの操作説明
	movement_key_ui_start();											//移動キーの表示
	arrow_start();														//矢印の表示
}







//----------------------------------------------------------------------------------------------
//ゲームオーバーでもクリアでも表示するUIを作る
//----------------------------------------------------------------------------------------------]
void score_drawfunc( TASK *ap )
{
	TASK spr;
	SINT32 i;
	SINT8 str[16];

	//文字列に変更する
	sprintf( str, "%8d", *ap->work_p[X] ); 					//メモリの中に保存する
	
	TASK_init_member_pointer( &spr );						//ここでsprを初期化

	spr.pos[X] = ap->pos[X];								//座標の設定
	spr.pos[Y] = ap->pos[Y];								//座標の設定
	spr.scale[X] = ap->scale[X];							//大きさを設定
	spr.scale[Y] = spr.scale[X];							//大きさを設定
	spr.tex_no = TEX_UI_FONT;								//テクスチャナンバーは自分のヤツ
	spr.uv_rect = number_rect;								//数字の矩形をいれる
	spr.pri = ap->pri;										//描画優先度を設定

	for ( i = 0; i < 8 ;i++ )							//表示したい桁分を回す
	{
		if( str[ i ] >= '0' && str[ i ] <= '9' )			//スコアのくらいが0～9なら
		{
			spr.base_color[0][1] = 0xff;					//R( はっきりとスコアを出す )
			spr.base_color[0][2] = 0xff;					//G( はっきりとスコアを出す )
			spr.base_color[0][3] = 0xff;					//B( はっきりとスコアを出す )
			spr.anime_no = str[ i ] - '0';					//文字列の0から文字列の0を引くと数字の0になる
		}

		else
		{
			spr.base_color[0][1] = 120;						//R( すこし暗くする )
			spr.base_color[0][2] = 120;						//G( すこし暗くする )
			spr.base_color[0][3] = 120;						//B( すこし暗くする )
			spr.anime_no = 0;								//計算結果は0
		}

		SOZ_sprite_draw( &spr );							//ここで描画する
		spr.pos[X] += ( 52.0f * spr.scale[X] );				//横にずらす
	}
}

void score_exec( TASK *ap )
{
	
}

void socre_start( FLOAT x, FLOAT y, FLOAT scale, SINT32 *score_p )
{
	TASK *ap;
	ap = TASK_start_DRAWFUNC( score_exec, score_drawfunc, UI_GROUP, "スコア" );
	ap->pos[X] = x;
	ap->pos[Y] = y;
	ap->scale[X] = scale;									//大きさを設定
	ap->scale[Y] = ap->scale[X];							//大きさを設定
	ap->work_p[X] = score_p;								//スコアやハイスコアを入れれるためにポインターにする
	ap->pri = UI_PRI * WP;
}




