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
#include    "include.h"


//-------------------------------------------------------------
//タスクのライティング設定
//-------------------------------------------------------------
void specular_status_set( TASK *ap, FLOAT pow, FLOAT sp_r, FLOAT sp_g, FLOAT sp_b )
{
	ap->pow = pow;						//光の影響をどれくらい受けるかの設定
	ap->specular[0] = sp_r;				//スペキュラーの赤を設定
	ap->specular[1] = sp_g;				//スペキュラーの緑を設定
	ap->specular[2] = sp_b;				//スペキュラーの青を設定
}

//-------------------------------------------------------------
//構造体に入っているもののライティング設定
//-------------------------------------------------------------
void specular_sturct_set( TASK *ap, OBJECT_DATA * op )
{
	specular_status_set( ap, op->pow, op->specular_r, op->specular_g, op->specular_b );
}


//-----------------------------------------------------------------------------------------
//HPがなくなったときの行動
//-----------------------------------------------------------------------------------------
void no_hp_move( TASK *ap, OBJECT_DATA *op,SINT32 cool_time )
{
	SINT32 fren;														//左から聞こえる音
	FLOAT vol, pan, length, range_max;												//右から聞こえる音とボリュームとレングス
	FLOAT sphire;
	OBJECT_SPHIRE *sp;
	sp = &object_sphire[ ap->ID ];
	sphire = sp->sphire[0] * 15;
	if( sphire < 4096.0f )
		sphire = 8192.0f;

	if( ap->HP <= 0 )
	{
		if( ap->SWITCH != 0 )								//壊れたオブジェクトを出していたら
			ap->TIMER++;									//時間を計測
		else												//壊れたオブジェクトを出していないのなら
		{
			object_id++;									//壊れたオブジェクトの数を数えている
			break_effect_occurrence( ap, 40.0f );			//エフェクトの発生
			if( range_sphire( ap, sphire, jiki ) != 0 )						//特定の範囲に自機が入ると音がなる
			{
				length = length_return( ap, sphire, jiki );	//レングスを求める
				length /= 512.0f;								//レングスを割る
				range_max = ( sphire ) / 256.0f;		//範囲の最大の数を求める
				vol = range_vol( op->se_vol, range_max, length );				//音量を求める
				fren = ( SINT32 )ang_pan( ap, jiki, 1.0f, ap->work1[ Y ], 1 );			//左耳の音量
				pan = ang_pan( ap, jiki, 1.0f, ap->work1[ Y ], 0 );				//右耳の音量
				SOZ_play_se( op->se_no, vol, fren, pan );
			}
			break_object_start( ap->pos[X], ap->pos[Y], ap->pos[Z], ap->vec[X], ap->vec[Y], ap->vec[Z],ap->fwork8[Y], ap->ID );
			ap->model_no = op->break_model_no;
			ap->tex_no = op->break_tex_no;
			ap->task_group = NO_GROUP;						//一定時間当たり判定をけすためにグループを変える
			ap->SWITCH = ON;
		}

		if( ap->TIMER >= cool_time )
		{
			ap->model_no = op->model_no;
			ap->tex_no = op->tex_no;
			ap->task_group = OBJECT_GROUP;
			ap->HP = ( SINT32 )( op->hp * ap->fwork8[X] );	//HPを回復( もともとのHPと保存していた倍率をかける ) 
			ap->TIMER = RESET;
			ap->SWITCH = OFF;
		}
	}
}


//-------------------------------------------------------------
//ベクトルをすべて0にする
//-------------------------------------------------------------
void vec_all_init( TASK *ap )
{
	ap->vec[X] = 0.0f;										//ベクトルを0にする( 横 )
	ap->vec[Y] = 0.0f;										//ベクトルを0にする( 縦 )
	ap->vec[Z] = 0.0f;										//ベクトルを0にする( 前後 )
}


//-------------------------------------------------------------
//マウスのx座標から角度を返す
//-------------------------------------------------------------
ANGLE mouse_view_ang( FLOAT mouse_pos_x )
{
	return mouse_ang_box[ ( SINT32 )mouse_pos_x ];	//座標から格納されてる値を見つけて渡す
}


//-------------------------------------------------------------
//タスクの角度からxとzのどっちで計算するかを返す( X版 )
//-------------------------------------------------------------
SINT32 x_check( TASK *ap )
{
	if( ap->work1[ Y ] > 0x0000 && 0x2000 >= ap->work1[ Y ] || ap->work1[ Y ] > 0xd000 )
		return X;		//特定の角度にいたらXを返す
	else if( ap->work1[ Y ] > 0x2000 && 0x6000 >= ap->work1[ Y ] )
		return Z;		//特定の角度にいたらZを返す
	else if( ap->work1[ Y ] > 0x6000 && 0xa000 >= ap->work1[ Y ] )
		return X;		//特定の角度にいたらXを返す
	else if( ap->work1[ Y ] > 0xa000 && 0xd000 >= ap->work1[ Y ] )
		return Z;		//特定の角度にいたらZを返す

	return X;
}


//-------------------------------------------------------------
//タスクの角度からxとzのどっちで計算するかを返す( Z版 )
//-------------------------------------------------------------
SINT32 z_check( TASK *ap )
{
	if( ap->work1[ Y ] > 0x0000 && 0x2000 >= ap->work1[ Y ] || ap->work1[ Y ] > 0xd000 )
		return Z;		//特定の角度にいたらXを返す
	else if( ap->work1[ Y ] > 0x2000 && 0x6000 >= ap->work1[ Y ] )
		return X;		//特定の角度にいたらZを返す
	else if( ap->work1[ Y ] > 0x6000 && 0xa000 >= ap->work1[ Y ] )
		return Z;		//特定の角度にいたらXを返す
	else if( ap->work1[ Y ] > 0xa000 && 0xd000 >= ap->work1[ Y ] )
		return X;		//特定の角度にいたらZを返す

	return Z;
}


//-------------------------------------------------------------
//マウスが範囲に入ったら0と1を返す( マウス座標が2D )
//-------------------------------------------------------------
SINT32 mouse2d_range_check( FLOAT x, FLOAT width, FLOAT y, FLOAT height )
{
	if( x < mouse_x && width > mouse_x )		//横が範囲に入っていたら
		if( y < mouse_y && height > mouse_y )	//次に縦が範囲に入っていたら
			return 1;							//範囲に入っていたら1を返す

	return 0;									//何もなかったら0を返す
}


//-------------------------------------------------------------
//攻撃力を計算して返す
//-------------------------------------------------------------
SINT32 atk_set( TASK *ap, OBJECT_DATA *op,FLOAT atk )
{
	SINT32 power;
	power = ( SINT32 )( op->atk * atk );	//攻撃力
	ap->fwork8[Y] =	atk;					//一応ATK倍率も保存しておく

	return power;							//攻撃力を保存 
}


//-------------------------------------------------------------
//ヒットポイントを計算して返す
//-------------------------------------------------------------
SINT32 hp_set( TASK *ap, OBJECT_DATA *op, FLOAT hp )
{
	SINT32 hit_point;
	hit_point  = ( SINT32 )( op->hp * hp );	//ヒットポイント
	ap->fwork8[X] = hp;						//HP倍率を保存しておく

	return hit_point;
}


//--------------------------------------------------------------------------------------------------------------------------------
//HPが0になったときモデルの描画をするかどうかを判別する( 値が返るようになっているのは視錐台カリングとの兼ね合いの為 )
//--------------------------------------------------------------------------------------------------------------------------------
SINT32 no_hp_task_id_chenge( TASK *ap, OBJECT_DATA *op )
{
	if( ( op->flag & ID_CHENGE_FLAG) != 0 )			//このフラグが立っていたら
	{
		if( ap->HP <= 0 )							//HPが0のとき
		{
			ap->task_id = TASK_PROGRAM;				//モデルの描画を止める
			return 1;								//視錐台カリングと競合しないようにするために値を返す
		}
		else										//HPが0より上なら
		{
			ap->task_id = TASK_MODEL;				//モデルの描画をする
		}
	}

	return 0;
}


SINT32 F_excepting( FLOAT target_a, FLOAT target_b  )//( float型 )引数同士が一致しない時に値が返る
{
	if( target_a != target_b )						//一致しなかったら
		return 1;									//1を返す

	return 0;										//なにもないと0を返す
}



SINT32 excepting( SINT32 target_a, SINT32 target_b  )//( int型 )引数同士が一致しない時に値が返る
{
	if( target_a != target_b )						//一致しなかったら
		return 1;									//1を返す

	return 0;										//なにもないと0を返す
}


//--------------------------------------------------------------------------------------------------------------------------------
//視錐台カリングする値を決める
//--------------------------------------------------------------------------------------------------------------------------------
FLOAT viwe_case( TASK *ap )
{
	switch( ap->ID )
	{ 
		case 14: case 16:			//学校と駐車場
			return 2100;
			break;

		default:
			return 700;		//基本はこの大きさで大丈夫
			break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//視錐台カリングを使って画面に写っていないときにモデルを描画しない
//--------------------------------------------------------------------------------------------------------------------------------
void task_id_checge( TASK *ap, SINT32 check )
{
	if( check == 0 )			//HPが0でモデルが消えていなければ
	{
		ap->task_id = TASK_MODEL;
		//-----視錐台カリング-----/
		if( SOZ_viewclip_checker( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ], viwe_case( ap ), CHECK_VIEW_LEFT | CHECK_VIEW_RIGHT | CHECK_VIEW_FRONT | CHECK_VIEW_BACK ) )
			ap->task_id = TASK_PROGRAM;
	}
}



//--------------------------------------------------------------------------------------------------------------------------------
//特定のフレームを超えたら透明度を交互に変える
//--------------------------------------------------------------------------------------------------------------------------------
void alpha_chenge( TASK *ap, SINT32 alp_max, SINT32 alp_min )
{
	SINT32 alp_box[ 2 ] = { alp_max, alp_min };				//透明度の最大と最小を格納する
	ap->TIMER++;											//フレームを計測
	if( ap->TIMER % 16 == 0 )								//特定のフレームを超えたら
		ap->work1[X]++;										//加算する

	ap->work1[X] %= 2;										//1を超えないようにする
	ap->base_color[0][0] = alp_box[ ap->work1[X] ];			//透明度を変更
}


//-------------------------------------------------------------------------------------------------------------------------------
//範囲の外に出たら値を返す
//-------------------------------------------------------------------------------------------------------------------------------
SINT32 not_range( FLOAT min, FLOAT max )
{
	if( min < max )
		return 1;

	return 0;
}


//-------------------------------------------------------------------------------------------------------------------------------
//距離に応じて音量を変える
//-------------------------------------------------------------------------------------------------------------------------------
FLOAT range_vol( FLOAT vol_max, FLOAT vol_rang_max, FLOAT len_num )
{
	FLOAT vol_min, vol, flip_vol;										//分割したときの音量と返す音量
	vol_min = vol_max / vol_rang_max;									//分割したときの音量を算出
	flip_vol = vol_rang_max - len_num;									//ここで反転させる( 遠くのほうがはっきり聞こえたため )
	vol = vol_min * flip_vol;											//割ったレングスの値と分割した音量と乗算

	return vol;															//算出した音量を返す
}

SINT32 ang_lr_check( TASK *ap, ANGLE ang_y, ANGLE target )
{
	if( ang_y > 0x0000 && 0x2000 >= ang_y || ang_y > 0xd000 )					//正面
		return 0;
	else if( ang_y > 0x2000 && 0x6000 >= ang_y )								//右
		return 2;															
	else if( ang_y > 0x6000 && 0xa000 >= ang_y )								//後ろ
		return 0;
	else if( ang_y > 0xa000 && 0xd000 >= ang_y )								//左
		return 1;

	return 0;
}

FLOAT ang_pan( TASK *ap, TASK *actp, FLOAT lr_max, ANGLE angle, SINT32 lr )
{
	ANGLE ang, ang_y, range, angle_y, target_ang, range_y;
	ang = SOZ_atan2( ap->pos[ X ], ap->pos[ Z ], actp->pos[ X ], actp->pos[ Z ] );		//角度を出す
	ang_y = angle - ang;																//物体との角度との角度を出す( 加算なのはangleが0度の役割をしているから )
	ang_y = ang_y % 0xffff;																//ここで0にする
	if( ang_lr_check( ap, ang_y, ang ) == 0 )
		return 1.0f;

	if( lr == 0 )																		//0は右
	{
		if( ang_lr_check( ap, ang_y, ang ) == 2 )
		{
			range = 0x4000 - 0x2000;													//範囲を算出( 90どまで )
			angle_y = range / 0x1000;													//1つあたりの音量を算出
			range_y = ang_y - 0x2000;													//何度か調べる( 正面の角度を減算した角度を )
			range_y = range_y / 0x1000;													//今の角度を分割していくつか調べる
			target_ang = angle_y * range_y;												//1つあたりの角度に分割した値を乗算

			return ( FLOAT )target_ang;													//右を返す
		}
	}

	if( lr == 1 )																		//1は左耳
	{
		if( ang_lr_check( ap, ang_y, ang ) == 1 )										//左耳なら
			return 1;																	//左耳は整数型なので1だけ返す
	}

	return 1.0f;
}




void common_ambient( TASK *ap )
{
	ap->ambient[0] = 0.31f;
	ap->ambient[1] = 0.31f;
	ap->ambient[2] = 0.31f;
	ap->ambient[3] = 1.0f;
}



void scale_all_chenge( TASK *ap, FLOAT scale )
{
	ap->scale[X] = scale;
	ap->scale[Y] = ap->scale[X];
	ap->scale[Z] = ap->scale[Y];
}