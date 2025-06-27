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
#include    "../../include.h"

SINT32 break_flag;

#define	CAR_LEN		5600
//-----------------------------------------------------------------------------------------------------------
//車のオブジェクトを設置
//-----------------------------------------------------------------------------------------------------------
void move_car_exec( TASK *ap )
{
	SINT32 check;
	ANGLE ang;
	OBJECT_DATA *op;				//オブジェクトのポインター
	op = &object_data[ ap->ID ];		//アドレスを渡す
	//ang = ap->angle[Y] & 0xffff;
	//if( ang > 0x8000 )
	//	ap->ang[Y] -= 0x100;
	//else
		//ap->ang[Y] += 0x100;

	ap->vec[ X ] = SOZ_get_sin( ap->angle[ Y ] ) * 35.0f;
	ap->vec[ Z ] = SOZ_get_cos( ap->angle[ Y ] ) * 35.0f;
	check = no_hp_task_id_chenge( ap, op );			//
	no_hp_move( ap, op, TIME_S * 25 );	//HPがなくなったとき
	task_id_checge( ap, check );					//視錐台カリング
	ap->angle[ Y ] += 0x10;
	ap->pos[ X ] = 25000 + SOZ_get_sin( ap->angle[ Y ] ) * CAR_LEN;
	ap->pos[ Z ] = 25500 + SOZ_get_cos( ap->angle[ Y ] ) * CAR_LEN;
	ang = ap->angle[ Y ] + 0xff;
	ap->ang[ Y ] = SOZ_atan2( ap->pos[ X ], ap->pos[ Z ], 25000, 25000 );
}

void move_car_start( SINT32 id )
{
	TASK *ap;
	OBJECT_DATA *op;				//オブジェクトのポインター
	op = &object_data[ id ];		//アドレスを渡す
	ap = TASK_start_MODEL( move_car_exec, OBJECT_GROUP, MODEL_CAR, TEX_CAR, "車のモデル" );
	ap->grp_mode =  op->grp_flag;	//
	specular_sturct_set( ap, op );	//構造体からスペキュラーを持ってくる
	common_ambient( ap );
	ap->pos[X] = 25000 + SOZ_get_sin( ap->angle[Y] ) * 500.0f;	//座標
	ap->pos[Y] = GROUND + 64.0f;			//座標
	ap->pos[Z] = 25000 + SOZ_get_cos( ap->angle[Y] ) * 500.0f;	//座標
	ap->vec[Y] = 25.0f;
	ap->sphire = 512.0f;
	ap->GROUP  = op->object_group;					//どのグループか伝える
	ap->HP  = ( SINT32 )op->hp;						//ヒットポイント
	ap->ATK = 5000;									//攻撃力
	ap->ID  = id;									//識別番号
	ap->fwork8[X] = 1.0f;							//HP倍率を保存しておく
	ap->fwork8[Y] =	0.6f;							//一応ATK倍率も保存しておく	ap->ID  = id;							//識別番号
}


void car_exec( TASK *ap )
{
	OBJECT_DATA *op;								//オブジェクトのポインター
	op = &object_data[ ap->ID ];					//アドレスを渡す
	SINT32 check;
	ap->sphire = sphire_get( ap );					//
	if( ap->SWITCH != 0 )							//
		ap->task_id = TASK_PROGRAM;					//
	else											//
		ap->task_id = TASK_MODEL;					//
	check = no_hp_task_id_chenge( ap, op );			//
	no_hp_move( ap, op, TIME_S * 15 );				//
	task_id_checge( ap, check );					//視錐台カリング
}

void car_start( FLOAT x, FLOAT y, FLOAT z, ANGLE ang_x, ANGLE ang_y, FLOAT scale, FLOAT hp, FLOAT atk,SINT32 id )
{
	TASK *ap;
	OBJECT_DATA *op;				//オブジェクトのポインター
	op = &object_data[ id ];		//アドレスを渡す
	ap = TASK_start_MODEL( car_exec, OBJECT_GROUP, op->model_no, op->tex_no,"ただのビル" );
	ap->grp_mode =  op->grp_flag;	//フラグを入れる
	ap->ID  = id;					//識別番号6
	object_sphire_set( id, 0, 256.0f, 0.0f, 256.0f );
	specular_sturct_set( ap, op );					//光に関するステータスを入れる
	common_ambient( ap );
	ap->pos[X] = x;									//座標
	ap->pos[Y] = y;									//座標
	ap->pos[Z] = z;									//座標
	ap->vec[X] = 0.0f;								//ベクトル
	ap->vec[Y] = 20.0f;								//ベクトル
	ap->vec[Z] = 0.0f;								//ベクトル
	ap->ang[X] = ang_x;								//角度
	ap->ang[Y] = ang_y;								//角度
	ap->scale[X] = scale;							//大きさ
	ap->scale[Y] = scale;							//大きさ
	ap->scale[Z] = scale;							//大きさ
	object_sphire_set( id, 0, 64.0f, 0, 64.0f );	//スフィアをセット
	ap->GROUP  = op->object_group;					//どのグループか伝える
	ap->HP  = ( SINT32 )( op->hp * hp );			//ヒットポイント
	ap->ATK = ( SINT32 )( op->atk * atk );			//攻撃力
	ap->ID  = id;									//識別番号
	ap->fwork8[X] = hp;								//HP倍率を保存しておく
	ap->fwork8[Y] =	atk;							//一応ATK倍率も保存しておく
	ap->pri = OBJECT_PRI * WP;
}


void object_exec( TASK *ap )
{
	OBJECT_DATA *op;								//オブジェクトのポインター
	op = &object_data[ ap->ID ];					//アドレスを渡す
	SINT32 check;
	check = 0;										//初期化
	ap->sphire = sphire_get( ap );

	check = no_hp_task_id_chenge( ap, op );
	no_hp_move( ap, op, TIME_S * 15 );				//HPがなくなったとき
	task_id_checge( ap, check );					//視錐台カリング
}

void object_start( FLOAT x, FLOAT y, FLOAT z, ANGLE ang_x, ANGLE ang_y, FLOAT scale, FLOAT hp, FLOAT atk,SINT32 id )
{
	TASK *ap;
	OBJECT_DATA *op;				//オブジェクトのポインター
	op = &object_data[ id ];		//アドレスを渡す
	ap = TASK_start_MODEL( object_exec, OBJECT_GROUP, op->model_no, op->tex_no,"ただのビル" );
	ap->grp_mode =  op->grp_flag;	//フラグを入れる
	ap->ID  = id;					//識別番号
	sphire_set_case( ap );
	specular_sturct_set( ap, op );	//光に関するステータスを入れる
	ap->pos[X] = x;					//座標
	ap->pos[Y] = y;					//座標
	ap->pos[Z] = z;					//座標
	ap->vec[X] = 0.0f;				//ベクトル
	ap->vec[Y] = 20.0f;				//ベクトル
	ap->vec[Z] = 0.0f;				//ベクトル
	ap->ang[X] = ang_x;				//角度
	ap->ang[Y] = ang_y;				//角度
	scale_all_chenge( ap, op->scale );
	common_ambient( ap );
	ap->GROUP  = op->object_group;	//どのグループか伝える
	ap->HP  = ( SINT32 )( op->hp * hp );	//ヒットポイント
	ap->ATK = ( SINT32 )( op->atk * atk );	//攻撃力
	ap->fwork8[X] = hp;				//HP倍率を保存しておく
	ap->fwork8[Y] =	atk;			//一応ATK倍率も保存しておく
	ap->pri = OBJECT_PRI * WP;
}


//駐車場
void parking_exec( TASK *ap )
{
	//当たり判定も何も無い壊れることのないオブジェクト
}

void parking_start( FLOAT x, FLOAT y, FLOAT z, ANGLE ang_x, ANGLE ang_y, FLOAT scale, FLOAT hp, FLOAT atk, SINT32 id )
{
	TASK *ap;
	OBJECT_DATA *op;				//オブジェクトのポインター
	op = &object_data[ id ];		//アドレスを渡す
	ap = TASK_start_MODEL( parking_exec, NO_GROUP, op->model_no, op->tex_no,"ただのビル" );
	ap->grp_mode =  op->grp_flag;	//フラグを入れる
	ap->ID  = id;					//識別番号
	specular_sturct_set( ap, op );	//光に関するステータスを入れる
	ap->pos[X] = x;					//座標
	ap->pos[Y] = y;					//座標
	ap->pos[Z] = z;					//座標
	ap->ang[X] = ang_x;				//角度
	ap->ang[Y] = ang_y;				//角度
	ap->scale[X] = scale;			//大きさ
	ap->scale[Y] = scale;			//大きさ
	ap->scale[Z] = scale;			//大きさ
	ap->emissive[0] = 1.5f;
	ap->emissive[1] = 1.5f;
	ap->emissive[2] = 1.5f;
	common_ambient( ap );
	ap->GROUP  = op->object_group;	//どのグループか伝える
	ap->HP  = ( SINT32 )( op->hp * hp );	//ヒットポイント
	ap->ATK = ( SINT32 )( op->atk * atk );	//攻撃力
	ap->fwork8[X] = hp;				//HP倍率を保存しておく
	ap->fwork8[Y] =	atk;			//一応ATK倍率も保存しておく
	ap->pri = OBJECT_PRI * WP;
}


//---------------------------------------------------------------------------------------------------------------------------
//ヘリコプターのタスク( ヘリの実行部はオブジェクトを使いまわす )
//---------------------------------------------------------------------------------------------------------------------------
void propeller_exec( TASK *ap )
{
	OBJECT_DATA *op;
	SINT32 fren;														//左から聞こえる音
	FLOAT vol, pan, length, range_max;												//右から聞こえる音とボリュームとレングス
	
	op = &object_data[ ap->parent->ID ];

	ap->pos[X] = ap->parent->pos[X]  + SOZ_get_sin( ap->parent->ang[Z] ) * 512.0f;
	ap->pos[Y] = ( ap->parent->pos[Y] ) + SOZ_get_cos( ap->parent->ang[Z] ) * 462.0f;
	ap->pos[Z] = ap->parent->pos[Z] + SOZ_get_sin( ap->parent->ang[X] ) * 512.0f;
	ap->task_id = ap->parent->task_id;
	if( ap->parent->HP > 0 )
	{
		if( range_sphire( ap, ap->sphire, jiki ) != 0 )						//特定の範囲に自機が入ると音がなる
		{
			ap->TIMER++;
			if( ap->TIMER > TIME_S * 12 )
			{
				length = length_return( ap, ap->sphire, jiki );					//レングスを求める
				length /= 512.0f;												//レングスを割る
				range_max = ap->sphire / 256.0f;								//範囲の最大の数を求める
				vol = range_vol( op->se_vol, range_max, length );				//音量を求める
				fren = ( SINT32 )ang_pan( ap, jiki, 1.0f, ap->work1[ Y ], 1 );				//左耳の音量
				pan  = ang_pan( ap, jiki, 1.0f, ap->work1[ Y ], 0 );				//右耳の音量
				SOZ_play_se( SE_PROPELLER, vol, fren, pan );
				ap->TIMER = RESET;
			}
		}
		else
		{
			ap->TIMER = TIME_S * 12;
		}

		ap->ang[ Y ] += Rand2( 0x50, 0x100 );
	}
}

void heri_start( FLOAT x, FLOAT y, FLOAT z, ANGLE ang_x, ANGLE ang_y, FLOAT scale, FLOAT hp, FLOAT atk, SINT32 id )
{
	TASK *ap, *actp;
	OBJECT_DATA *op;				//オブジェクトのポインター
	op = &object_data[ id ];		//アドレスを渡す
	ap = TASK_start_MODEL( object_exec, OBJECT_GROUP, op->model_no, op->tex_no,"ただのビル" );
	ap->grp_mode =  op->grp_flag;	//フラグを入れる
	ap->ID  = id;					//識別番号
	sphire_set_case( ap );
	specular_sturct_set( ap, op );	//光に関するステータスを入れる
	common_ambient( ap );
	ap->pos[X] = x;					//座標
	ap->pos[Y] = y;					//座標
	ap->pos[Z] = z;					//座標
	ap->vec[X] = 0.0f;				//ベクトル
	ap->vec[Y] = 20.0f;				//ベクトル
	ap->vec[Z] = 0.0f;				//ベクトル
	ap->ang[X] = ang_x;				//角度
	ap->ang[Y] = ang_y;				//角度
	ap->scale[X] = scale;			//大きさ
	ap->scale[Y] = scale;			//大きさ
	ap->scale[Z] = scale;			//大きさ

	ap->GROUP  = op->object_group;	//どのグループか伝える
	ap->HP  = ( SINT32 )( op->hp * hp );	//ヒットポイント
	ap->ATK = ( SINT32 )( op->atk * atk );	//攻撃力
	ap->fwork8[X] = hp;				//HP倍率を保存しておく
	ap->fwork8[Y] =	atk;			//一応ATK倍率も保存しておく
	ap->pri = OBJECT_PRI * WP;

	actp = TASK_start_MODEL( propeller_exec, NO_GROUP, MODEL_PROPELLER, TEX_HERI, "プロペラ" );
	actp->grp_mode = TEST_ZBUFFER | WRITE_ZBUFFER  | NO_SHADOW | USE_LIGHTING | USE_SPECULAR;
	actp->pos[X] = ap->pos[X] + SOZ_get_sin( ap->ang[Y] ) * 128.0f;
	actp->pos[Y] = ( ap->pos[Y] + 462.0f ) + SOZ_get_sin( ap->ang[X] ) * 256.0f;
	actp->pos[Z] = ( ap->pos[Z] ) + SOZ_get_sin( ap->ang[Y] ) * 512.0f;
	actp->sphire = 2048.0f;
	actp->parent = ap;
	actp->pri = OBJECT_PRI * WP;
	ap->child[ 0 ] = actp;
}


void ang_hit_smile( TASK *ap )
{
	ANGLE ang, angle;
	FLOAT sa_x, sa_z, all_sa;
	sa_x = sa_return( ap->pos[X], jiki->pos[X] );
	sa_z = sa_return( ap->pos[Z], jiki->pos[Z] );
	all_sa = sa_x + sa_z;
	angle = ap->ang[Y] + 0xc000;								//モデルの見た目の実際の値が180度違ったため補正
	if( all_sa < 5120.0f )
	{
		ang = SOZ_atan2( ap->pos[X], ap->pos[Z], jiki->pos[X], jiki->pos[Z] );
		if( SOZ_angle_diff( angle, ang ) >= 0x400 )
			ap->ang[Y] += 0x100;
		else if( SOZ_angle_diff( angle, ang ) <= -0x400 )
			ap->ang[Y] -= 0x100;
	}
	else
	{
		if( SOZ_angle_diff( ap->ang[Y], ap->angle[Y] ) >= 0x200 )
			ap->ang[Y] += 0x400;
		else if( SOZ_angle_diff( ap->ang[Y], ap->angle[Y] ) <= -0x200 )
			ap->ang[Y] -= 0x400;
	}
}


void alien_exec( TASK *ap )
{
	SINT32 check;
	FLOAT sa_x, sa_y, sa_z, all_sa;
	OBJECT_DATA *op;												//オブジェクトのポインター
	op = &object_data[ ap->ID ];									//アドレスを渡す
	if( clear_flag != 0 )									//前の試合がゲームクリアなら
		ap->tex_no = TEX_ALIEN_SMILE;						//笑顔の表情
	else if( game_over_flag != 0 )							//前の試合がゲームオーバーなら
		ap->tex_no = TEX_ALIEN_SAD;							//悲しい表情

	if( jiki != NULL )
		ang_hit_smile( ap );

	check = 0;										//初期化
	ap->sphire = sphire_get( ap );

	check = no_hp_task_id_chenge( ap, op );
	no_hp_move( ap, op, TIME_S * 15 );				//HPがなくなったとき
	task_id_checge( ap, check );					//視錐台カリング
	
}

void alien_start( FLOAT x, FLOAT y, FLOAT z, ANGLE ang_x, ANGLE ang_y, FLOAT scale, FLOAT hp, FLOAT atk,SINT32 id )
{
	TASK *ap;
	OBJECT_DATA *op;												//オブジェクトのポインター
	op = &object_data[ id ];										//アドレスを渡す
	ap = TASK_start_MODEL( alien_exec, OBJECT_GROUP, op->model_no, op->tex_no,"ただのビル" );
	ap->grp_mode =  op->grp_flag;									//フラグを入れる
	ap->ID  = id;													//識別番号
	sphire_set_case( ap );											//スフィアをいれる
	specular_sturct_set( ap, op );									//光に関するステータスを入れる
	ap->pos[X] = x;													//座標
	ap->pos[Y] = y;													//座標
	ap->pos[Z] = z;													//座標
	ap->vec[X] = 0.0f;												//ベクトル
	ap->vec[Y] = 20.0f;												//ベクトル
	ap->vec[Z] = 0.0f;												//ベクトル
	ap->ang[X] = ang_x;												//角度
	ap->ang[Y] = ang_y;												//角度
	ap->angle[Y] = ap->ang[Y];										//角度を保存しておく
	scale_all_chenge( ap, op->scale );
	common_ambient( ap );
	ap->GROUP  = op->object_group;									//どのグループか伝える
	ap->HP  = ( SINT32 )( op->hp * hp );							//ヒットポイント
	ap->ATK = ( SINT32 )( op->atk * atk );							//攻撃力
	ap->fwork8[X] = hp;												//HP倍率を保存しておく
	ap->fwork8[Y] =	atk;											//一応ATK倍率も保存しておく
	ap->pri = OBJECT_PRI * WP;										//描画優先度

	ap->fwork1[X] = ap->pos[X];
	ap->fwork1[Y] = ap->pos[Y];
	ap->fwork1[Z] = ap->pos[Z];
}


void jiki_death_exec(TASK *ap)
{
	//if( ap->timer % 4 == 0 )
	//	game_over_efe_start( ap->pos[X], ap->pos[Y], ap->pos[Z], ap->scale[X] / 2 );
}


void jiki_death_start( FLOAT x, FLOAT y, FLOAT z )
{
	TASK *ap;
	ap = TASK_start_MODEL( jiki_death_exec, NO_GROUP, MODEL_JIKI, TEX_JIKI, "壊れた自機" );
	ap->grp_mode =  TEST_ZBUFFER | WRITE_ZBUFFER  | NO_SHADOW | USE_LIGHTING;
	ap->ambient[0] = 0.11f;
	ap->ambient[1] = 0.11f;
	ap->ambient[2] = 0.11f;
	ap->ang[X] = 0x7000;
	ap->pos[X] = x;
	ap->pos[Y] = y + 32.0f * 15.0f;
	ap->pos[Z] = z;
	scale_all_chenge( ap, 15.0f );
}