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
#include    "../../include.h"


//--------------------------------------------------------------------------------------
//スフィアの情報のボックスを初期化
//--------------------------------------------------------------------------------------
OBJECT_SPHIRE	object_sphire[ OBJ_MAX ];				//当たり判定の実装
OBJECT_DATA		object_data[ OBJ_MAX ]=					//オブジェクトのデータ
{
/*00*/{/*     name			   group		model_no			tex_no				break_model_no		break_tex_no		grp_flag			pow		specular_r	specular_g specular_b  hp	 atk	エフェクトの数	エフェクトのモデル  エフェクトのテクスチャー	効果音			音量	フラグ			アイコン	スコア*/},
/*01*/{"ただのビル"			, BILL_GROUP,	MODEL_SUB_BILL,		TEX_BILL,			MODEL_BLEAK_BILL,	TEX_BILL,			SUB_BILL_GRP_FLAG,  4.6f,		1.3f,      1.3f,    1.3f,		260, 4500,		16,			MODEL_BILL_EFE,		TEX_BILL_EFE,				SE_BILL_BREAK,	1.7f,	NO_FLAG			,	1,		10000	},
/*02*/{"緑の車"				, CAR_GROUP,	MODEL_CAR,			TEX_CAR,			MODEL_CAR,			TEX_CAR,			CAR_GRP_FLAG,		1.0f,       1.3f,      1.3f,    1.3f,		260, 3800,		 4,			MODEL_CAR_EFE,		TEX_CAR_EFE ,				SE_KLAXON_1,	1.0f,	CAR_FLAG		,	3,		13000	},
/*03*/{"黒の車"				, CAR_GROUP,	MODEL_CAR,			TEX_CAR_B,			MODEL_CAR,			TEX_CAR_B,			CAR_GRP_FLAG,		1.0f,       1.3f,      1.3f,    1.3f,		260, 3500,		 4,			MODEL_CAR_EFE,		TEX_CAR_EFE ,				SE_KLAXON_1,	1.0f,	CAR_FLAG		,	3,		13000	},
/*04*/{"白の車"				, CAR_GROUP,	MODEL_CAR,			TEX_CAR_W,			MODEL_CAR,			TEX_CAR_W,			CAR_GRP_FLAG,		1.0f,       1.3f,      1.3f,    1.3f,		260, 3500,		 4,			MODEL_CAR_EFE,		TEX_CAR_EFE ,				SE_KLAXON_1,	1.0f,	CAR_FLAG		,	3,		13000	},
/*05*/{"赤スター"			, CAR_GROUP,	MODEL_ROADSTAR,		TEX_ROADSTAR_R,		MODEL_ROADSTAR,		TEX_ROADSTAR_R,		CAR_GRP_FLAG,		6.5f,       2.1f,      2.1f,    2.1f,		260, 3500,		 4,			MODEL_CAR_EFE,		TEX_CAR_EFE ,				SE_KLAXON_2,	1.0f,	CAR_FLAG		,	4,		15000	},
/*06*/{"黒スター"			, CAR_GROUP,	MODEL_ROADSTAR,		TEX_ROADSTAR_B,		MODEL_ROADSTAR,		TEX_ROADSTAR_B,		CAR_GRP_FLAG,		6.5f,       2.1f,      2.1f,    2.1f,		260, 3500,		 4,			MODEL_CAR_EFE,		TEX_CAR_EFE ,				SE_KLAXON_2,	1.0f,	CAR_FLAG		,	4,		15000	},
/*07*/{"白スター"			, CAR_GROUP,	MODEL_ROADSTAR,		TEX_ROADSTAR_W,		MODEL_ROADSTAR,		TEX_ROADSTAR_W,		CAR_GRP_FLAG,		4.6f,       1.9f,      2.1f,    1.9f,		260, 3500,		 4,			MODEL_CAR_EFE,		TEX_CAR_EFE ,				SE_KLAXON_2,	1.0f,	CAR_FLAG		,	4,		15000	},
/*08*/{"謎のタワー"			, BILL_GROUP,	MODEL_TOWER,		TEX_TOWER,			MODEL_TOWER,		TEX_TOWER,			SUB_BILL_GRP_FLAG,	4.6f,       1.9f,      2.1f,    1.9f,		260, 3500,		 4,			MODEL_BILL_EFE,		TEX_BILL_EFE,				SE_BILL_BREAK,	2.0f,	ID_CHENGE_FLAG	,	2,		10000	},
/*09*/{"テント"				, BILL_GROUP,	MODEL_TENTO,		TEX_TENTO,			MODEL_TENTO,		TEX_TENTO,			SUB_BILL_GRP_FLAG,	4.6f,       1.9f,      2.1f,    1.9f,		260, 3500,		 4,			MODEL_BILL_EFE,		TEX_BILL_EFE,				SE_BILL_BREAK,	2.0f,	ID_CHENGE_FLAG	,	11,		10000	},
/*10*/{"モニター機械"		, MEKA_GROUP,	MODEL_SCREEN_MEKA,	TEX_SCREEN_MEKA,	MODEL_SCREEN_MEKA,	TEX_SCREEN_MEKA,	SUB_BILL_GRP_FLAG,	4.6f,       1.9f,      2.1f,    1.9f,		260, 3500,		 4,			NULL,				NULL,						SE_BILL_BREAK,	2.0f,	WOOD_FLAG		,	7,		0		},
/*11*/{"ボタン付き機械"		, MEKA_GROUP,	MODEL_BUTTON_MEKA,	TEX_BUTTON_MEKA,	MODEL_BUTTON_MEKA,	TEX_BUTTON_MEKA,	SUB_BILL_GRP_FLAG,	4.6f,       1.9f,      2.1f,    1.9f,		260, 3500,		 4,			NULL,				NULL,						SE_BILL_BREAK,	2.0f,	WOOD_FLAG		,	6,		0		},
/*12*/{"木"					, MEKA_GROUP,	MODEL_WOOD,			TEX_WOOD,			MODEL_WOOD_EFE,		TEX_WOOD_EFE,		SUB_BILL_GRP_FLAG,	4.6f,       1.9f,      2.1f,    1.9f,		260, 5000,		16,			MODEL_WOOD_EFE,		TEX_WOOD_EFE,				SE_BILL_BREAK,	2.0f,	WOOD_FLAG		,	8,		11000	},
/*13*/{"カツオのオブジェ"	, FISH_GROUP,	MODEL_BONITO,		TEX_BONITO,			MODEL_BONITO,		TEX_BONITO,			SUB_BILL_GRP_FLAG,	4.6f,       1.9f,      2.1f,    1.9f,		260, 5500,		 8,			MODEL_BONITO,		TEX_BONITO	,				SE_FISH,		1.5f,	BONITO_FLAG		,	5,		15000	},
/*14*/{"学校"				, SCHOOL_GROUP,	MODEL_SCHOOL,		TEX_SCHOOL,			MODEL_BREAK_SCHOOL,	TEX_SCHOOL,			SCHOOL_GRP_FLAG,	0.0f,       1.0f,      1.0f,    1.0f,		840, 6000,		32,			MODEL_BILL_EFE,		TEX_SCHOOL,					SE_BILL_BREAK,	2.0f,	NO_FLAG	,			12,		30000	},
/*15*/{"ロゴのマンション"	, HOUSE_GROUP,	MODEL_LOGO_HOUSE,	TEX_LOGO_HOUSE,		MODEL_LOGO_HOUSE,	TEX_LOGO_HOUSE,		SCHOOL_GRP_FLAG,	0.0f,       1.0f,      1.0f,    1.0f,		840, 6000,		16,			MODEL_BILL_EFE,		TEX_SCHOOL,					SE_BILL_BREAK,	2.0f,	LOGO_HOUSE_FLAG	,	13,		20000	},
/*16*/{"駐車場"				, HOUSE_GROUP,	MODEL_PARKING,		TEX_PARKING,		MODEL_PARKING,		TEX_PARKING,		MAIN_BILL_GRP_FLAG,	1.0f,       1.0f,      1.0f,    1.0f,		840, 5500,		16,			MODEL_BILL_EFE,		TEX_SCHOOL,					SE_BILL_BREAK,	2.0f,	LOGO_HOUSE_FLAG	,	1,		20000	},
/*17*/{"ヘリ"				, HERI_GROUP,	MODEL_HERI,			TEX_HERI,			MODEL_HERI,			TEX_HERI,			MAIN_BILL_GRP_FLAG,	1.0f,       1.0f,      1.0f,    1.0f,		540, 6500,		 1,			MODEL_PROPELLER,	TEX_HERI,					SE_BILL_BREAK,	2.0f,	ID_CHENGE_FLAG	,	9,		20000	},
/*18*/{"ネコ山"				, CAT_GROUP,	MODEL_CAT_MOUNTEN,	TEX_CAT_MOUNTEN,	MODEL_CAT_MOUNTEN,	TEX_CAT_MOUNTEN,	MAIN_BILL_GRP_FLAG,	1.0f,       1.0f,      1.0f,    1.0f,		1240, 8500,		 16,			MODEL_CAT,			TEX_CAT_GRY,				SE_BILL_BREAK,	2.0f,	ID_CHENGE_FLAG	,	10,		40000	},
																																																																													
/*18*/{"メインビル"			, BILL_GROUP,	MODEL_MAIN_BILL,	TEX_BILL,			MODEL_MAIN_BILL,	TEX_BILL,			SUB_BILL_GRP_FLAG,	4.6f,       1.9f,      2.1f,    1.9f,		40,  1800,		 4,			MODEL_BILL_EFE,		TEX_BILL_EFE,				SE_BILL_BREAK,	2.0f,	NO_FLAG			,	1,		1000	},
};



void sphire_set_case( TASK *ap )
{
	switch( ap->ID )
	{
		case 1:				//ただのビル
			object_sphire_set( ap->ID, 0, 356.0f, 0.0f, 356.0f );		//スフィアのセット
			break;

		case 8:
			object_sphire_set( ap->ID, 0, 356.0f, 0.0f, 356.0f );		//スフィアのセット
			break;

		case 9:
			object_sphire_set( ap->ID, 0, 356.0f, 0.0f, 356.0f );		//スフィアのセット
			break;

		case 10:		//モニター付き機械
			object_sphire_set( ap->ID, 0, 356.0f, 0.0f, 356.0f );		//スフィアのセット
			break;

		case 11:		//ボタン付き機械
			object_sphire_set( ap->ID, 0, 356.0f, 0.0f, 64.0f );		//スフィアのセット
			break;

		case 12:			//木
			object_sphire_set( ap->ID, 0,  512.0f, 0.0f, 256.0f );		//スフィアのセット
			object_sphire_set( ap->ID, 1, 256.0f, 256.0f, 512.0f );		//スフィアのセット
			break;

		case 13:			//カツオ
			object_sphire_set( ap->ID, 0, 340.0f, 0.0f, 340.0f );		//スフィアのセット
			break;

		case 14:
			object_sphire_set( ap->ID, 0, 2048.0f, 0.0f, 2048.0f );		//スフィアのセット
			break;

		case 15:
			object_sphire_set( ap->ID, 0, 800.0f, 0.0f, 800.0f );		//スフィアのセット
			break;

		case 17:
			object_sphire_set( ap->ID, 0, 256.0f, 0.0f, 256.0f );		//スフィアのセット
			break;

		case 18:			//ネコ山
			object_sphire_set( ap->ID, 0, 2048.0f, 0.0f, 2048.0f );		//スフィアのセット
			break;
	}

}

//--------------------------------------------------------------------------------------
//スフィアの情報のボックスを初期化
//--------------------------------------------------------------------------------------
void object_sphire_init( void )
{
	SINT32 i, fi;									//配列を回す変数とポインターとスフィアの中身を回す変数
	OBJECT_SPHIRE *op;								//オブジェクトのポインター
	op = object_sphire;
	for( i = 0; i < OBJ_MAX; i++ )					//当たり判定のマックスまで回す
	{
		for( fi = 0; fi < OBJ_SPHIRE_MAX; fi++ )	//スフィアの配列分回す
		{
			op->sphire[ fi ] = NULL;				//スフィアの大きさを初期化
			op->sphire_height_min[ fi ] = NULL;		//スフィアの高さの最小値を初期化
			op->sphire_height_max[ fi ] = NULL;		//スフィアの高さの最大値を初期化
		}
		op++;										//次のアドレスに移動
	}
}


//--------------------------------------------------------------------------------------
//スフィアの情報を一つずつ入れる
//--------------------------------------------------------------------------------------
void object_sphire_set( SINT32 id, SINT32 sphire_no, FLOAT sphire, FLOAT height_min, FLOAT height_max )
{
	OBJECT_SPHIRE *op;
	op = &object_sphire[ id ];							//どこのアドレスに入れるかを教える
	FLOAT min, max;
	if( op->sphire[ sphire_no ] != 0.0f )				//もしスフィアの中身がすでに入っていたら		
		return;											//これ以上実行しないようにする

	min = height_min;
	max = height_max;
	if( op->sphire[ 0 ] != NULL )						//もし0番にすでに設定されてたら残りは勝手に設定する
	{
		min = op->sphire_height_max[sphire_no - 1];		//最小は一つ前の最大
		max = op->sphire_height_max[sphire_no - 1] + sphire;		//一つ前の最大にスフィアを加算
	}

	op->sphire[ sphire_no ] = sphire;					//スフィアを設定
	op->sphire_height_min[ sphire_no ] = min;	//スフィアの高いところを設定
	op->sphire_height_max[ sphire_no ] = max;	//スフィアの低いところを設定
}

void sphire_set_sub( SINT32 id, SINT32 sphire_no, FLOAT sphire )
{
	object_sphire_set( id, sphire_no, sphire, 0.0f, 0.0f );
}


//--------------------------------------------------------------------------------------
//オブジェクトかどうか調べる
//--------------------------------------------------------------------------------------
SINT32 object_check( TASK *ap )
{
	if( ap->ID == 0 )		//IDが0ならある程度スフィアがついている
		return 1;			//もしオブジェクトじゃないなら1を返す
		
	return 0;				//もしオブジェクトなら0を返す
}


//--------------------------------------------------------------------------------------
//オブジェクトのスフィアを調べる
//--------------------------------------------------------------------------------------
SINT32 sphire_set( TASK *ap, TASK *actp )
{
	SINT32 i, sphire_id;					//for分用の変数とどの配列を使うかを格納する変数
	OBJECT_SPHIRE * os;						//スフィアのポインター
	sphire_id = 0;							//初期化しておく
	os = &object_sphire[ actp->ID ];		//アドレスを教える	
	for( i = 0; i < OBJ_SPHIRE_MAX; i++ )	//配列をぶん回す
		if( os->sphire_height_min[ i ] < ap->pos[Y] && ap->pos[Y] < os->sphire_height_max[ i ] )		//中に入っていたら
		{
			sphire_id = i;					//どこのスフィアを使うか決まる
			break;							//これ以上回さないようにする
		}
	return sphire_id;						//使う場所を送ってあげる
}

//--------------------------------------------------------------------------------------
//オブジェクトのスフィアを入れる
//--------------------------------------------------------------------------------------
FLOAT sphire_point( TASK *ap, TASK *actp )
{
	SINT32 point;							//どのスフィアを使うか決める
	OBJECT_SPHIRE * os;						//スフィアのポインター

	os = &object_sphire[ actp->ID ];		//アドレスを教える	
	point =  sphire_set( ap, actp );		//どこの配列が適しているか調べる
	if( os->sphire[ point ] == 0.0f || actp->ID == 0 )	//スフィアやIDが0なら
		return 0.0f;						//ここは通さない
	
	return os->sphire[ point ];				//スフィアを返す
}


FLOAT sphire_get( TASK *ap )
{
	FLOAT sa_z, sa_x, abs_sax, abs_saz;
	sa_x = ap->pos[X] - jiki->pos[X]; 
	sa_z = ap->pos[Z] - jiki->pos[Z];
	abs_sax = ( FLOAT )fabs( ( DOUBLE )sa_x );			//絶対値を調べる
	abs_saz = ( FLOAT )fabs( ( DOUBLE )sa_z );			//絶対値を調べる
	//for( actp = ap_start; actp != NULL; actp = actp->next )
	//	if( actp->task_group == SHOT_GROUP || actp->task_group == HAND_GROUP || actp->task_group == BREAK_OBJECT_GROUP )
	//		if( sa_check_smaller( ap->pos[X], actp->pos[X], abs_sax ) != 0 && sa_check_smaller( ap->pos[Z], actp->pos[Z], abs_saz ) != 0 )		//距離が自機より小さかったら
	//			return sphire_point( actp, ap );		//ビームの距離でスフィアを返す

	return sphire_point( jiki, ap );					//自機の距離でスフィアを返す
}


//--------------------------------------------------------------------------------------
//自機用の判定チェック
//--------------------------------------------------------------------------------------
SINT32 jiki_hit_check( TASK *ap, TASK *actp )
{
	SINT32 point;							//どのスフィアを使うか決める
	FLOAT sa_x, sa_y, sa_z;					//互いの差を測る
	FLOAT length;							//その差からレングスを出す
	FLOAT sphire_pos_y, min_hight;						//使うスフィアの座標を入れる					
	OBJECT_SPHIRE * os;						//スフィアのポインター

	os = &object_sphire[ actp->ID ];		//アドレスを教える	
	point =  sphire_set( ap, actp );		//どこの配列が適しているか調べる
	if( os->sphire[ point ] == 0.0f || actp->ID == 0 )	//スフィアやIDが0なら
		return 0;							//ここは通さない

	min_hight = ( os->sphire_height_max[ point ] - os->sphire_height_min[ point ] ) / 2;		//高さの真ん中を調べる	
	min_hight = min_hight / 2;
	sphire_pos_y = os->sphire_height_min[ point ] + min_hight;
	sa_x = ap->pos[X] - actp->pos[X];		//横の差を調べる
	sa_y = ap->pos[Y] - ( actp->pos[Y] + sphire_pos_y );		//縦の差を調べる
	sa_z = ap->pos[Z] - actp->pos[Z];		//前後の差を調べる

	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );	//平方根を出す

	if( length <= ( ap->sphire + os->sphire[ point ] ) )		//もしレングスより値が上なら
		return 1;			//ヒットを返す

	return 0;				//0を返す
}


//--------------------------------------------------------------------------------------
//オブジェクト同士の判定
//--------------------------------------------------------------------------------------
SINT32 object_hit_check( TASK *ap, TASK *actp )
{
	SINT32 point, act_point;				//どのスフィアを使うか決める
	FLOAT sa_x, sa_y, sa_z;					//互いの差を測る
	FLOAT length;							//その差からレングスを出す
	FLOAT sphire_pos_y, act_pos_y;			//使うスフィアの座標を入れる					
	OBJECT_SPHIRE * os, *actos;				//スフィアのポインター

	os = &object_sphire[ actp->ID ];		//アドレスを教える	
	point =  sphire_set( ap, actp );		//どこの配列が適しているか調べる
	if( os->sphire[ point ] == 0.0f || actp->ID == 0 )	//スフィアやIDが0なら
		return 0;							//ここは通さない

	actos = &object_sphire[ ap->ID ];		//アドレスを教える	
	act_point =  sphire_set( ap, actp );	//どこの配列が適しているか調べる
	if( actos->sphire[ point ] == 0.0f || ap->ID == 0 )	//スフィアやIDが0なら
		return 0;							//ここは通さない

	sphire_pos_y = ( os->sphire_height_max[ point ] - os->sphire_height_min[ point ] ) / 2;		//高さの真ん中を調べる	
	sphire_pos_y = os->sphire_height_max[ point ];

	act_pos_y = ( actos->sphire_height_max[ act_point ] - actos->sphire_height_min[ act_point ] ) / 2;		//高さの真ん中を調べる	
	act_pos_y = os->sphire_height_max[ point ];

	sa_x = ap->pos[X] - actp->pos[X];		//横の差を調べる
	sa_y = ( ap->pos[Y] + act_pos_y ) - ( actp->pos[Y] + sphire_pos_y );		//縦の差を調べる
	sa_z = ap->pos[Z] - actp->pos[Z];		//前後の差を調べる

	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );	//平方根を出す

	if( length <= ( actos->sphire[ act_point ] + os->sphire[ point ] ) )		//もしレングスより値が上なら
		return 1;			//ヒットを返す

	return 0;				//0を返す
}

SINT32 sphire_hit_check( TASK *ap, TASK *actp )
{
	FLOAT sa_x, sa_y, sa_z;																		//互いの差を測る
	FLOAT length;																				//その差からレングスを出す
	FLOAT sphire_pos_y, min_hight;																//使うスフィアの座標を入れる
	sa_x = ap->pos[X] - actp->pos[X];															//横の差を調べる
	sa_y = ap->pos[Y] - actp->pos[Y];														//縦の差を調べる
	sa_z = ap->pos[Z] - actp->pos[Z];															//前後の差を調べる
	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );				//平方根を出す

	if( length <= ( ap->sphire + actp->sphire ) )												//もしレングスより値が上なら
		return 1;																				//ヒットを返す

	return 0;																					//0を返す
}


//--------------------------------------------------------------------------------------
//スフィアの当たり判定をチェックして値を返す
//--------------------------------------------------------------------------------------
SINT32 kawa_3d_hit_check( TASK * ap, TASK * actp )
{
	SINT32 scene, ob;
	ob = object_check( ap ) + object_check( actp );
	switch( ob )
	{
		case 0: scene =  0; break;								//どちらも構造体にスフィアがある

		case 1: scene = 10; break;								//どちらかにスフィアがある

		case 2: scene = 20; break;								//お互いにスフィアがある
	}
	switch( scene )													
	{																
		case 0:													//どっちもスフィアが構造体に入っている
			if( object_hit_check( ap, actp ) != 0 )					
				return 1;											
			break;													
																	
		case 10:												//片方がスフィアを持っているよう
			if( jiki_hit_check( ap, actp ) != 0 )				//あったているかどうかを返す
				return 1;
			break;

		case 20:
			if( sphire_hit_check( ap, actp ) != 0 )				//スフィアーが設定されている同士なら
				return 1;
			break;
	}
	
	return 0;
}


//-------------------------------------------------------------------------------------------------------------------------
//スフィアで差を見る
//-------------------------------------------------------------------------------------------------------------------------
SINT32 range_sphire( TASK *ap, FLOAT sphire, TASK *actp )
{
	FLOAT sa_x, sa_y, sa_z;					//互いの差を測る
	FLOAT length;							//その差からレングスを出す

	sa_x = ap->pos[X] - actp->pos[X];		//横の差を調べる
	sa_y = ap->pos[Y] - actp->pos[Y];		//縦の差を調べる
	sa_z = ap->pos[Z] - actp->pos[Z];		//前後の差を調べる

	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );	//平方根を出す

	if( length <= actp->sphire + sphire )		//もしレングスより値が上なら
		return 1;			//ヒットを返す

	return 0;				//0を返す
}

//-------------------------------------------------------------------------------------------------------------------------
//スフィアで差を見る( object_data版 )
//-------------------------------------------------------------------------------------------------------------------------
SINT32 object_range_sphire( TASK *ap, FLOAT sphire, TASK *actp )
{
	FLOAT sa_x, sa_y, sa_z;					//互いの差を測る
	FLOAT length;							//その差からレングスを出す

	sa_x = ap->pos[X] - actp->pos[X];		//横の差を調べる
	sa_y = ap->pos[Y] - actp->pos[Y];		//縦の差を調べる
	sa_z = ap->pos[Z] - actp->pos[Z];		//前後の差を調べる

	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );	//平方根を出す

	if( length <= actp->sphire + sphire )		//もしレングスより値が上なら
		return 1;			//ヒットを返す

	return 0;				//0を返す
}
//-------------------------------------------------------------------------------------------------------------------------
//レングスを渡す
//-------------------------------------------------------------------------------------------------------------------------
FLOAT length_return( TASK *ap, FLOAT sphire, TASK *actp )
{
	FLOAT sa_x, sa_y, sa_z;					//互いの差を測る
	FLOAT length;							//その差からレングスを出す

	sa_x = ap->pos[X] - actp->pos[X];		//横の差を調べる
	sa_y = ap->pos[Y] - actp->pos[Y];		//縦の差を調べる
	sa_z = ap->pos[Z] - actp->pos[Z];		//前後の差を調べる
	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );	//平方根を出す

	return length;							//レングスを返す
}


#if 0
FLOAT sa_x, sa_y, sa_z;					//互いの差を測る
	FLOAT length;							//その差からレングスを出す

	sa_x = ap->pos[X] - actp->pos[X];		//横の差を調べる
	sa_y = ap->pos[Y] - actp->pos[Y];		//縦の差を調べる
	sa_z = ap->pos[Z] - actp->pos[Z];		//前後の差を調べる

	length = ( FLOAT )sqrt( ( sa_x * sa_x ) + ( sa_y * sa_y ) + ( sa_z * sa_z ) );	//平方根を出す
	if( length <= ( ap->sphire + actp->sphire ) )	//もしレングスより値が上なら
		return 1;			//ヒットを返す

	return 0;
#endif