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
//#define	OBJECT_SEQ	""

//-----------------------------------------------------------------------------------------------------------------------
//外部変数
//-----------------------------------------------------------------------------------------------------------------------
SINT32	page = 0, select_no = 1;				//オブジェクトのページ数とどこを選択しているかを格納する変数
FLOAT	sequence_box[ SEQ_SAVE_MAX ];			//シーケンス
FLOAT	temporary_sequence_box[ SEQ_SAVE_MAX ];	//一時的に保存しておく箱( コントロールZを押して一つ前に戻れるようにするため )
FLOAT	magnification_hp = 1.0f, magnification_atk = 1.0f;	//倍率
//SINT8	click_check = 0;						//char型の方が小さく済む？( 3バイトの空きを埋める必要あり？ )
//SINT8	catch_switch = 0;						//char型の方が小さく済む？(x )
bool	select_switch = FALSE;					//オブジェクト選択を出したり消したりする( 本当にブール型でいいのか？ 2025/2/21 )
bool	click_check = FALSE, catch_switch = FALSE;
PARTS_RECT selsect_arrow_rect[]=
{
	{    1,     1,    62,    62,    62,    24 },
};

PARTS_RECT	status_rect[]=
{
	{  129,     1,   126,    62,    63,    31},	//HPの矩形
	{  273,     1,   190,    62,    95,    31},	//ATKの矩形
	{  129,   161,   206,    62,   103,    31},	//SIZEの矩形
};


//----------------------------------------------------------------------------------------------------
//設置するオブジェクトをケースで判別させる
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
//構造体の中身がないと
//----------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
//オブジェクトを選ばせる
//-----------------------------------------------------------------------------------------------------------------------
void object_select_exec( TASK *ap )
{
	SINT32 elements;							//要素数を格納する
	FLOAT  width, y, height;					//横幅を格納する
	CHAR   box[ 256 ];							//
	elements = 0;								//
	while( ap->task_name[ elements ] != NULL )	//
	{
		box[ elements ] = ap->task_name[ elements ];	//
		elements++;								//
	}
	//elements = sizeof ap->task_name / sizeof ap->task_name[0];	//要素数を計算する 
	width = 42.0f * ( (FLOAT)elements / 2 );	//要素数と文字サイズを乗算する
	width = ap->pos[ X ] + width;				//座標を基点に横幅を設定
	y = ap->pos[ Y ];							//上を設定
	height = ap->pos[ Y ] + 32.0f;				//下を設定
	if( mouse2d_range_check( ap->pos[ X ],width, y, height ) != 0 )		//マウスが範囲に入っていたら
		select_no = ap->ID;						//IDを入れる

	if( ap->ID == select_no + ( SELECT_MAX * page ) )					//一緒なら
	{
		ap->base_color[0][2] = 0x0;				//緑を抜く
		ap->base_color[0][3] = 0x0;				//青を抜く
	}
	else
	{
		ap->base_color[0][2] = 0xff;			//緑を戻す
		ap->base_color[0][3] = 0xff;			//青を戻す
	}
	
}

void object_select_start( FLOAT x, FLOAT y, SINT32 id, SINT32 group )
{
	TASK *ap;
	OBJECT_DATA *op;
	op = &object_data[ id ]; 
	if( op->name[0] == NULL )					//もしオブジェクトの中身が無かったら
		return;									//これ以上実行しない( タスクの登録してないから行けるはず )
	ap = TASK_start_FONT( object_select_exec, group, op->name, 3 );
	ap->pos[X] = x;
	ap->pos[Y] = y;
	ap->ID = id;
	ap->pri = 9999 * WP;
}


//----------------------------------------------------------------------------------------------------
//矢印が重なっていないかを調べる
//----------------------------------------------------------------------------------------------------
void arrow_check( void )
{
	TASK *actp;
	click_check = 0;							//まず0にする

	for( actp = ap_start; actp != NULL; actp = actp->next )
		if( actp->task_group == ARROW_GROUP )	//矢印なら
			if( actp->SWITCH != 0 )				//重なっていた時に値の変わるworkが0以外なら
				click_check = 1;				//重なっていたら1にする
}

//----------------------------------------------------------------------------------------------------
//現在のモデルの名前と一つずつなら変更できるようにする( 矢印の実行部 )
//----------------------------------------------------------------------------------------------------
void selsect_arrow_exec( TASK *ap )
{
	FLOAT x, width, y, height;
	ap->SWITCH = 0;								//常に初期化しておく
	if( ( ap->grp_mode & FLIP_LR ) == 0 )		//左向きなら( 中心点は右 )
	{ 
		x = ap->pos[X] - 64.0f;					//左向きに合わせてxを計算
		width = ap->pos[X];						//左向きに合わせて横幅を計算
	}

	else										//右向きなら( 中心点は左 )
	{
		x = ap->pos[X];							//右向きに合わせてxを計算
		width = ap->pos[X] + 64.0f;				//右向きに合わせて横幅を計算
	}

	y = ap->pos[Y] - 32.0f;						//高さを計算
	height = ap->pos[Y] + 32.0f;				//縦幅を計算

	if( mouse2d_range_check( x, width, y, height ) != 0 )		//マウスが範囲に入っていたら
	{
		ap->SWITCH = 1;							//値を1にする( これが1のときはクリックでオブジェクトを設置できないようにする )
		ap->shader_pass = SHADER_RED;			//赤くシェーダーをかける
		if( SOZ_Mouse_Button( 0 ) != 0  )		//まず0じゃないかを計算
			if( SOZ_Mouse_Button( 0 ) == 1 || SOZ_Mouse_Button( 0 ) % 12 == 0 )	//単押しまたは長押しで少しずつ上がる
			{
				if( (ap->grp_mode & FLIP_LR) == 0 )		//左向きなら( 中心点は右 )
					select_no--;				//減算する
				else							//右向きなら
					select_no++;				//加算する

				select_and_page_write( "data/select_data.bn", &select_no );	//セレクトを保存
				select_and_page_write( "data/page_data.bn", &page );		//ページを保存
			}

//-----ページが更新されたときセレクトが変な値にならないように制御する-----//
		if( select_no <= 0 )
		{
			select_no = SELECT_MAX;					//ナンバーを1にする( 次のページの1番目 )
			page--;									//ページを減算			
		}
		
		else if( select_no % ( SELECT_MAX + 1 ) == 0 )//選択数のマックスに一つ加算したあまりが0なら
		{
			select_no = SELECT_MIN;					//ナンバーを1にする( 次のページの1番目 )
			page++;									//ページを加算
		}
		

//ページがオブジェクトの構造体の数を超えないように　制御する
		if( page > PAGE_MAX )						//ページの最大を超えたら
		{
			select_no = SELECT_MAX;
			page = PAGE_MAX;						//ページの最大で固定
		}
		else if( page < PAGE_MIN )					//ページの最小を下回ったら
		{
			select_no = SELECT_MIN;
			page = PAGE_MIN;						//ページを最小で固定
		}
	}

	else											//マウスが範囲に入っていなかったら
	{
		ap->SWITCH = 0;								//値を下げる
		ap->shader_pass = SOZ_UNCLEAR;				//シェーダーも切る
	}
}

//----------------------------------------------------------------------------------------------------
//現在のモデルの名前と一つずつなら変更できるようにする
//----------------------------------------------------------------------------------------------------
void model_name_exec( TASK *ap )
{
	SINT32 elements, id;							//要素数を格納する
	FLOAT  width;									//横幅を格納する
	CHAR   box[ 256 ];								//
	elements = 0;									//
	id = select_no + ( SELECT_MAX * page );			//ページも加味したIDが入る
	OBJECT_DATA *op;
	op = &object_data[ id ];						//選ばれてるIDの構造体を格納
	if( op->name[ 0 ] == NULL )
	{
		select_no--;
		return;
	}
	switch( ap->SCENE )
	{
		case 0:
			while( ap->task_name[ elements ] != NULL )	//タスクの文字がないところまで回す
			{
				box[ elements ] = ap->task_name[ elements ];	//
				elements++;							//使ってる配列の数を数えてる	
			}
			width = 42.0f * ( ( FLOAT )elements / 2 );	//要素数と文字サイズを乗算する
			width = WINDOW_WIDTH_HALF - width / 5;		//座標を基点に左にずらす
			object_select_start( width, 21.0f, id, MODEL_NAME_GROUP );	//フォントを出す
			ap->SCENE = 10;							//待機に移動する
			break;

		case 10:
			if( ap->work1[ X ] != select_no )
			{
				ap->SCENE = 0;						//もう一度出現させる
				TASK_end_group( MODEL_NAME_GROUP );	//メイン文字を消す				
				ap->work1[ X ] = select_no;			//ページを保存
				return;
			}
			break;
				
	}
	
}

void model_name_start( void )
{
	TASK *ap;
	ap = TASK_start( model_name_exec, MANE_GROUP, "現在のモデルを表示" );
	ap->work1[X] = select_no + ( PAGE_MAX * page );
	ap->pri = 9999 * WP;
	
	ap = TASK_start_GRP( selsect_arrow_exec, ARROW_GROUP, TEX_DEBUG_PARAM, selsect_arrow_rect, 0, "左向きの矢印" );
	ap->pos[X] = WINDOW_WIDTH_HALF / 2.0f;
	ap->pos[Y] = 32.0f;
	ap->pri = 9999 * WP;

	ap = TASK_start_GRP( selsect_arrow_exec, ARROW_GROUP, TEX_DEBUG_PARAM, selsect_arrow_rect, 0, "右向きの矢印" );
	ap->pos[X] = WINDOW_WIDTH_HALF + ( WINDOW_WIDTH_HALF / 2.0f );		//右半分くらいに行く
	ap->pos[Y] = 32.0f;
	ap->grp_mode |= FLIP_LR;											//反転して右向きにする
	ap->pri = 9999 * WP;
}


//----------------------------------オブジェクトモデル----------------------------------//

//-----------------------------------------------------------------------------------------------------------------------
//オブジェクトの設置を右クリックで確定する
//-----------------------------------------------------------------------------------------------------------------------
SINT32 end_code_check( void )
{
	SINT32 i;											//中身を回す
	i = 1;												//回す初期値を設定( 0がNULLなら値が返るので1からスタート )
	if( sequence_box[0] == NULL )						//もし中身がなにもないのなら
		return 0;										//0番を返す

	do
	{
		i++;
	} while( sequence_box[i] != -999.0f );				//エンコードが見つかるまで回す

	return i;											//エンコードの番号を渡す
}


//----------------------------------------------------------------------------------------------------
//設置するオブジェクトをケースで判別させる( 模型 )
//----------------------------------------------------------------------------------------------------
void object_set_case( TASK *ap )
{
	switch( ap->ID )
	{
		case 2: case 3: case 4: case 5: case 6:	case 7: //テクスチャーの違う車たち
			car_start( ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X], ap->ang[Y], ap->scale[X], NO_HP, NO_ATK, ap->ID );
			break;

		case 16:
			parking_start( ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X], ap->ang[Y], ap->scale[X], NO_HP, NO_ATK, ap->ID );
			break;

		case 17:
			heri_start( ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X], ap->ang[Y], ap->scale[X], NO_HP, NO_ATK, ap->ID );
			break;

		case 20:
			alien_start( ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X], ap->ang[Y], ap->scale[X], NO_HP, NO_ATK, ap->ID );
			break;

		default:
			object_start( ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X], ap->ang[Y], ap->scale[X], NO_HP, NO_ATK, ap->ID );
			break;
	}
}



void page_cheng_func( TASK *ap )
{
	if( SOZ_Inkey_TRG( DIK_LEFT ) != 0 )
		if( page > PAGE_MIN )
			page--;
	
	if( SOZ_Inkey_TRG( DIK_RIGHT ) != 0 )
		if( page < PAGE_MAX )
			page++;

}


//-----------------------------------------------------------------------------------------------------------------------
//オブジェクトの選択画面を出したり消したりする
//-----------------------------------------------------------------------------------------------------------------------
void object_window_set_exec( TASK *ap )
{
	SINT32 i, id;
	FLOAT y;
	y = 0;
	id = 1;

	if( ap->work1[Z] != select_no )
	{
		select_and_page_write( "data/select_data.bn", &select_no );	//セレクトを保存
		ap->work1[Z] = select_no;					//ナンバーを保存
	}

	if( SOZ_Mouse_Button( 1 ) == 1 )				//オブジェクトを開く( 右クリック )
	{
		if( select_switch == TRUE )					//もしtureなら
			select_switch = FALSE;					//falseに変える
		else										//もしture以外なら
			select_switch = TRUE;					//tureに変える
	}

	if( SOZ_Inkey_REP( DIK_UP ) != 0 )
		select_no--;

	if( SOZ_Inkey_REP( DIK_DOWN ) != 0 )
		select_no++;

	if( select_no >= 10 )
		select_no = 10;
	else if( select_no <= 1 )
		select_no = 1;


	switch( ap->SCENE )								//無限にタスクを出したり毎回タスクを消したりしないようにスイッチ文にする( 2025/2/21 )
	{
		case 0:
			//if( ap->work1[X] == FALSE )			//スイッチが0なら
			//	ap->SCENE = 10;						//画面に映さないようにするルーチンに飛ばす
			if( select_switch == TRUE )				//画面選択が選ばれると
				ap->SCENE = 20;						//選択画面を出す
			break;

		case 20:									//一瞬だけ出す
			for( i = 1; i < SELECT_MAX; i++ )		//10個選択を出す
			{
				id = i + ( SELECT_MAX * page );		//識別番号を設定
				object_select_start( 32, y, id, FONT_GROUP );	//モデルを選択させる文字を出す
				y += 64.0f;							//下にずらす
			}
			ap->work1[Y] = page;					//ページを保存しておく
			ap->SCENE++;							//次のケースに移動
			break;

		case 21:									//ページが変わったり選択画面を閉じたりしているかを見てる
			if(select_switch == FALSE || ap->work1[ Y ] != page )				//もし選択画面を閉じたらもしくはページ移動があれば
			{
				TASK_end_group( FONT_GROUP );								//フォントを消す
				select_and_page_write( "data/select_data.bn", &select_no );	//セレクトを保存
				select_and_page_write( "data/page_data.bn", &page );		//ページを保存
				ap->SCENE = 0;												//ケースを0に戻す
				ap->work1[Y] = page;										//ページを保存
			}
			page_cheng_func( ap );
			break;
	}
}


//-----------------------------------------------------------------------------------------------------------------------
//オブジェクトエディターの移動の関数
//-----------------------------------------------------------------------------------------------------------------------
void editor_movement_get_key( TASK *ap )
{
	SINT32 sa_x, sa_y;
	SINT32 mx, my;

	mx = mouse_x;
	my = mouse_y;
	sa_x = ap->work2[X] - mouse_x;			//横の差を計測
	sa_y = ap->work2[Y] - mouse_y;			//縦の差を計測
	ap->vec[X] = SOZ_get_sin( -ap->work1[Y] ) * ap->fwork2[X];
	ap->vec[Y] = SOZ_get_sin(  ap->angle[ X ] ) * ap->fwork2[X];
	ap->vec[Z] = SOZ_get_cos( -ap->work1[Y] ) * ap->fwork2[X];
	//-----------キー入力-----------//
	if( SOZ_Inkey_DAT( DIK_LSHIFT ) != 0 || SOZ_Inkey_DAT( DIK_RSHIFT ) != 0 )//シフトを押していたら
	{
		if( SOZ_Mouse_Button( 2 ) )
		{
//-----------角度によって移動が変わる-----------//
		if( sa_y > 5 )		//もし差が20より大きければ( 左に進んだ )
		{
			ap->pos[Y] += 120.0f;
		}
		else if( sa_y < -5 )
		{
			ap->pos[Y] -= 120.0f;
		}
			if( sa_x > 0 )
			{
				if( ap->work1[ Y ] > 0x0000 && 0x2000 >= ap->work1[ Y ] || ap->work1[ Y ] > 0xd000 )
					ap->pos[ X ] -= ap->fwork1[X];		//特定の角度にいたら左に進む
				else if( ap->work1[ Y ] > 0x2000 && 0x6000 >= ap->work1[ Y ] )
					ap->pos[ Z ] -= ap->fwork1[X];		//特定の角度にいたら手前に進む
				else if( ap->work1[ Y ] > 0x6000 && 0xa000 >= ap->work1[ Y ] )
					ap->pos[ X ] += ap->fwork1[X];		//特定の角度にいたら右に進む
				else if( ap->work1[ Y ] > 0xa000 && 0xd000 >= ap->work1[ Y ] )
					ap->pos[ Z ] += ap->fwork1[X];		//特定の角度にいたら奥に進む

			}
//-----------角度によって移動が変わる-----------//
			if( sa_x < 0 )
			{
				if( ap->work1[ Y ] > 0x0000 && 0x2000 >= ap->work1[ Y ] || ap->work1[ Y ] > 0xd000 )
					ap->pos[ X ] += ap->fwork1[X];
				else if( ap->work1[ Y ] > 0x2000 && 0x6000 >= ap->work1[ Y ] )
					ap->pos[ Z ] += ap->fwork1[X];
				else if( ap->work1[ Y ] > 0x6000 && 0xa000 >= ap->work1[ Y ] )
					ap->pos[ X ] -= ap->fwork1[X];
				else if( ap->work1[ Y ] > 0xa000 && 0xd000 >= ap->work1[ Y ] )
					ap->pos[ Z ] -= ap->fwork1[X];
			}

			if( mouse_x == mx )					//もしカーソルが止まったら
			{
				ap->work2[Y]   = mouse_y;		//カーソルを保存
				ap->work2[X]   = mouse_x;		//カーソルを保存
			}
		}
	}

	else if( SOZ_Inkey_DAT( DIK_LSHIFT ) == 0 && SOZ_Inkey_DAT( DIK_RSHIFT ) == 0 )				//シフトを押していなければ
	{
		ap->work2[Y]   = mouse_y;		//マウスの座標を保存しておく
		ap->work2[X]   = mouse_x;		//マウスの座標を保存しておく
	}

	if( SOZ_Inkey_DAT( DIK_LCONTROL ) == 0 && SOZ_Inkey_DAT( DIK_RCONTROL ) == 0 )
	{
		if( SOZ_MouseZ() > 10 )
		{
			ap->pos[ X ] += -ap->vec[ X ];			//すべての角度に加算
			ap->pos[ Y ] += -ap->vec[ Y ];			//すべての角度に加算
			ap->pos[ Z ] += -ap->vec[ Z ];			//すべての角度に加算
		}

		if( SOZ_MouseZ() < -10 )
		{
			ap->pos[ X ] += ap->vec[ X ];			//すべての角度に加算
			ap->pos[ Y ] += ap->vec[ Y ];			//すべての角度に加算
			ap->pos[ Z ] += ap->vec[ Z ];			//すべての角度に加算
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------
//特定のキーを押すと移動速度を変える関数
//-----------------------------------------------------------------------------------------------------------------------
void movement_speed_chenge( TASK *ap )
{
	if( SOZ_Inkey_DAT( DIK_Z ) != 0 )
	{
		ap->fwork1[X] = NORMAL_EDITOR_SPEED_X * 2;	//通常の２倍の速度
		ap->fwork2[X] = NORMAL_EDITOR_SPEED_Z * 2;	//通常の２倍の速度
		ap->fwork3[X] = NORMAL_EDITOR_SPEED_X * 2;	//通常の２倍の速度
	}
	else if( SOZ_Inkey_DAT( DIK_X ) != 0 )
	{
		ap->fwork1[X] = NORMAL_EDITOR_SPEED_X / 2;	//通常の２分の1の速度
		ap->fwork2[X] = NORMAL_EDITOR_SPEED_Z / 2;	//通常の２分の1の速度
		ap->fwork3[X] = NORMAL_EDITOR_SPEED_Z / 2;	//通常の２分の1の速度
	}
	else if( SOZ_Inkey_DAT( DIK_Z ) == 0 || SOZ_Inkey_DAT( DIK_X ) == 0 )
	{
		ap->fwork1[X] = NORMAL_EDITOR_SPEED_X;		//通常の速度
		ap->fwork2[X] = NORMAL_EDITOR_SPEED_Z;		//通常の速度
		ap->fwork3[X] = NORMAL_EDITOR_SPEED_X;		//通常の速度
	}
}


#if 1
void model_movement_key( TASK *ap )
{
	if( SOZ_Inkey_DAT( DIK_LCONTROL ) != 0 && SOZ_Inkey_DAT( DIK_RCONTROL ) != 0 )
	{
		if( SOZ_MouseZ() > 20 )
			ap->fwork1[ Y ] += 40.0f;
		else if( SOZ_MouseZ() < -20 )
			ap->fwork1[ Y ] -= 40.0f;
	}
	ap->vec[X] = SOZ_get_sin( -ap->parent->work1[Y] ) * ap->parent->fwork2[X];
	ap->vec[Y] = SOZ_get_sin(  ap->parent->angle[ X ] ) * ap->parent->fwork2[X];
	ap->vec[Z] = SOZ_get_cos( -ap->parent->work1[Y] ) * ap->parent->fwork2[X];
	//-----------キー入力-----------//
	if( SOZ_Inkey_DAT( DIK_D ) != 0 )
	{
		if( ap->parent->work1[Y] > 0x0000 && 0x2000 >= ap->parent->work1[Y] || ap->parent->work1[Y] > 0xd000 )
			ap->fwork1[X] -= ap->parent->fwork1[X];
		else if( ap->parent->work1[Y] > 0x2000 && 0x6000 >= ap->parent->work1[Y] )
			ap->fwork1[Z] -= ap->parent->fwork1[X];
		else if( ap->parent->work1[Y] > 0x6000 && 0xa000 >= ap->parent->work1[Y] )
			ap->fwork1[X] += ap->parent->fwork1[X];
		else if( ap->parent->work1[Y] > 0xa000 && 0xd000 >= ap->parent->work1[Y] )
			ap->fwork1[Z] += ap->parent->fwork1[X];

	}

	if( SOZ_Inkey_DAT( DIK_A ) != 0 )
	{
		if( ap->parent->work1[Y] > 0x0000 && 0x2000 >= ap->parent->work1[Y] || ap->parent->work1[Y] > 0xd000 )
			ap->fwork1[X] += ap->parent->fwork1[X];
		else if( ap->parent->work1[Y] > 0x2000 && 0x6000 >= ap->parent->work1[Y] )
			ap->fwork1[Z] += ap->parent->fwork1[X];
		else if( ap->parent->work1[Y] > 0x6000 && 0xa000 >= ap->parent->work1[Y] )
			ap->fwork1[X] -= ap->parent->fwork1[X];
		else if( ap->parent->work1[ Y ] > 0xa000 && 0xd000 >= ap->parent->work1[Y] )
			ap->fwork1[Z] -= ap->parent->fwork1[X];
	}

	
	if( SOZ_Inkey_DAT( DIK_W ) != 0 )
	{
		ap->fwork1[ X ] += -ap->vec[ X ];
		//ap->fwork1[ Y ] += -ap->vec[ Y ];
		ap->fwork1[ Z ] += -ap->vec[ Z ];
	}

	if( SOZ_Inkey_DAT( DIK_S ) != 0 )
	{
		ap->fwork1[ X ] += ap->vec[ X ];
		//ap->fwork1[ Y ] += ap->vec[ Y ];
		ap->fwork1[ Z ] += ap->vec[ Z ];
	}

	if( SOZ_Inkey_DAT( DIK_F ) != 0 )
	{
		ap->fwork2[ X ] = ap->parent->pos[ X ];
		ap->pos[ Y ] = GROUND;
		ap->fwork2[ Z ] = ap->parent->pos[ Z ];
	}

	if( SOZ_Inkey_REP( DIK_T ) != 0 )
		ap->pos[Y] += ap->parent->fwork3[X];
	else if( SOZ_Inkey_REP( DIK_G ) != 0 )
		ap->pos[Y] -= ap->parent->fwork3[X];
	
	if( SOZ_Inkey_REP( DIK_B ) != 0 )
		ap->pos[Y] = GROUND;

	ap->pos[ X ] = ap->fwork2[ X ] + ap->fwork1[ X ];
	ap->pos[ Z ] = ap->fwork2[ Z ] + ap->fwork1[ Z ];
}
#endif


//-----------------------------------------------------------------------------------------------------------------------
//オブジェクトのモデルの回転( リピート )
//-----------------------------------------------------------------------------------------------------------------------
void model_ang_key( TASK *ap )
{
	if( SOZ_Inkey_REP( DIK_Q ) != 0 )
		ap->ang[Y] -= 0x400;
	else if( SOZ_Inkey_REP( DIK_E ) != 0 )
		ap->ang[Y] += 0x400;
	else if( SOZ_Inkey_REP( DIK_R ) != 0 )
		ap->ang[Y] = 0x0;
}

//-----------------------------------------------------------------------------------------------------------------------
//オブジェクトの設置を右クリックで確定する
//-----------------------------------------------------------------------------------------------------------------------
void object_set_key( TASK *ap )
{
	FLOAT *point;												//ポインター
	point = sequence_box;										//どの配列かを教える
	if( SOZ_Mouse_Button( 0 ) == 1 )							//矢印にカーソルが重なっていなければ
		if( SOZ_Mouse_Button( 0 ) <=  1 )
			if( click_check == 0 )
			{
				point = &sequence_box[ end_code_check() ];		//エンドコードの場所を探してアドレスを渡す
				*point++ = (FLOAT)ap->ID;						//まずケース番号を入れる( ケース文で使用する為 )
				*point++ = ap->pos[ X ];						//座標を入れる( x )
				*point++ = ap->pos[ Y ];						//座標を入れる( y )
				*point++ = ap->pos[ Z ];						//座標を入れる( z )
				*point++ = (FLOAT)ap->ang[ X ];					//角度を入れる( とりあえずこっちも保存しておく )
				*point++ = (FLOAT)ap->ang[ Y ];					//角度を入れる
				*point++ = ap->scale[ X ];						//大きさを入れる( x )(今は一つの大きさだけでいいと思う( 2025/2/27 )
				//*point++ = ap->scale[Y];						//大きさを入れる( y )
				//*point++ = ap->scale[Z];						//大きさを入れる( z )
				*point++ = magnification_hp;					//HPの倍率を入れる
				*point++ = magnification_atk;					//攻撃力の倍率を入れる
				*point++ = (FLOAT)ap->ID;						//IDを入れる
				*point++ = -999.0f;								//最後にエンコードを入れる
				sequence_write( "data/" SAVE_FILE ".bn", sequence_box );		//シーケンスに保存
				object_set_case( ap );							//オブジェエクトを設置する
				return;
			}
}


//-----------------------------------------------------------------------------------------------------------------------
//オブジェクトのモデル
//-----------------------------------------------------------------------------------------------------------------------
void object_model_exec( TASK *ap )
{
	SINT32 id;
	OBJECT_DATA *op;
	id = select_no + ( SELECT_MAX * page );
	op = &object_data[ id ];								//選ばれたIDをいれる
	if( op == NULL )
		return;

	ap->model_no = op->model_no;							//構造体の中のモデルナンバーを代入
	ap->tex_no = op->tex_no;								//構造体の中のテクスチャーナンバーを代入
	ap->pow = op->pow;										//光の影響をどれほど受けるかの値
	ap->specular[0] = op->specular_r;						//スペキュラーの赤
	ap->specular[1] = op->specular_g;						//スペキュラーの緑
	ap->specular[2] = op->specular_b;						//スペキュラーの青
	ap->grp_mode = op->grp_flag;							//グラフィック関係のフラグを立てる
	scale_all_chenge( ap, op->scale );
	ap->ID = id;				//IDを設定
	model_ang_key( ap );									//キー入力で角度が変わる
	model_movement_key( ap );								//キー移動させる
	object_set_key( ap );									//オブジェクトを設置する
	//model_click_set( ap );								//マウスでクリックするとそこにオブジェクトを設置させる
	ap->fwork1[Y] = ap->parent->pos[Y];						//親の縦座標を保存しておく

	SOZ_locate_print( 24, 1, "%2d", ap->ID ); 
}


//-----------------------------------------------------------------------------------------------------------------------
//オブジェクトを配置するエディターを作成
//-----------------------------------------------------------------------------------------------------------------------
void object_editor_exec( TASK *ap )
{
	
	FLOAT pos_x, pos_y, pos_z;
	pos_x =  ap->pos[X];									//横の座標を保存
	pos_y =  ap->pos[Y];									//縦の座標を保存
	ap->work1[Y] =  ap->angle[ Y ];							//移動に使う角度を取得してる
	pos_z =  ap->pos[Z];									//前後の座標を保存
	ap->work1[Y] =  ap->work1[Y] + 0x8000;					//32768( 180度 )回す( 目玉の名残
	ap->work1[Y] %= 0xffff;									//65535( 360度 )を超えないようにする
	if( SOZ_Inkey_DAT( DIK_LCONTROL ) == 0 && SOZ_Inkey_DAT( DIK_RCONTROL ) == 0 )
		movement_speed_chenge( ap );						//速度を上げる
	editor_movement_get_key( ap );
	check_range_restriction( ap, pos_x, pos_y, pos_z );		//自機の移動範囲を制限する
}

void object_editor_start( void )
{
	TASK *ap, *actp, *omp;
	ap = TASK_start( object_editor_exec, EDITOR_GROUP, "オブジェクトを配置する" );
	ap->pos[Y] = JIKI_Y;									//自機の座標に合わせる
	ap->pos[X] = JIKI_X;									//自機の座標に合わせる
	ap->pos[Z] = JIKI_Z;									//自機の座標に合わせる

	ap->fwork1[X] = NORMAL_EDITOR_SPEED_X;					//左右移動のスピード
	ap->fwork2[X] = NORMAL_EDITOR_SPEED_Z;					//前後移動のスピード
	common_ambient( ap );
	jiki = ap;												//こいつをカメラに追従させる　

	actp = TASK_start( object_model_exec, OBJECT_GROUP, "モデルのオブジェクト" );
	actp->task_id = TASK_MODEL;								//タスクのIDをモデルに変える( 実行部の方でいろいろ設定する )
	actp->fwork2[ X ] = ap->pos[ X ];
	actp->pos[ Y ] = GROUND;
	actp->fwork2[ Z ] = ap->pos[ Z ];
	actp->parent = ap;										//親子関係で繋いでおく
	ap->child[0] = actp;									//親子関係で繋いでおく

	omp = TASK_start( object_window_set_exec, MANE_GROUP, "オブジェクト選択の出現管理タスク" );
	omp->work1[Y] = page;									//ページを保存しておく
	omp->parent = ap;										//親子関係で繋いでおく
	ap->child[1] = omp;										//親子関係で繋いでおく
}




void seq_delete( SINT32 id )
{
	SINT32 i, index;
	i = 0;
	do
		i++;
	while( id != sequence_box[ i ] );						//指定したIDと同じになるまで回す
	index = i + 10;
	
	while( i < index )
	{
		sequence_box[ i ] = -999;
		i++;
	}
	sequence_write( "data/" SAVE_FILE ".bn", sequence_box );		//シーケンスに保存
}

#if 0			//絶対に成功させる( 2025/2/26 )
//-----------------------------------------------------------------------------------------------------------------------
//オブジェクトモデルの移動( マウスの場所で決める )
//-----------------------------------------------------------------------------------------------------------------------
void model_click_set( TASK *ap )
{
	FLOAT	pos_x, pos_y;						//カメラも加味したマウスの値を格納する変数
	ANGLE	mouse_angle;						//マウスの座標とカメラの座標から角度を出して格納する変数
	FLOAT	pos_z;
	FLOAT	abs_x;
	if( SOZ_Mouse_Button( 0 ) == 1 )			//左クリックなら
	{
		abs_x = fabs( ( DOUBLE )mouse_3d_x );
		pos_z = z_box[ ( SINT32 )-mouse_3d_y ];	//
		//pos_x = world_mouse_x / pos_z;	//2D座標にする
		pos_y = world_mouse_y / pos_z;	//2D座標にする
//--------------横軸-----------------//
		if( mouse_3d_x > 0 )
		{
			ap->fwork1[ x_check( ap ) ] = world_mouse_x + SOZ_get_sin( jiki->angle[ Y ] ) * (pos_z / 2);
			ap->fwork1[ x_check( ap ) ] = ap->fwork1[ x_check( ap ) ] + SOZ_get_sin( mouse_view_ang( abs_x ) ) * (pos_z / 2);
		}
		else
		{
			ap->fwork1[ x_check( ap ) ] = world_mouse_x - SOZ_get_sin( jiki->angle[ Y ] ) * (pos_z / 2);
			ap->fwork1[ x_check( ap ) ] = ap->fwork1[ x_check( ap ) ] - SOZ_get_sin( mouse_view_ang( abs_x ) ) * (pos_z / 2);
		}
		//ap->pos[Y] = pos_y;
//-------------前後軸----------------//
		ap->fwork1[ z_check( ap ) ] = pos_z + SOZ_get_sin( jiki->angle[Y] );
		ap->pos[X] = ap->fwork1[X];	//
		ap->pos[Y] = GROUND;
		ap->pos[Z] = ap->fwork1[Z];	
	}
}
#endif





