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


//-----------------------------------------------------------------------------------------------------------------------
//外部変数
//-----------------------------------------------------------------------------------------------------------------------
TASK *jiki;
PARTS_RECT bom_rect[]=								//爆発の矩形
{
	{    1,     1,   126,   126,    63,    63},		//0
	{  129,     1,   126,   126,    63,    63},		//1
	{  257,     1,   126,   126,    63,    63},		//2
	{  385,     1,   126,   126,    63,    63},		//3
	{    1,   129,   126,   126,    63,    63},		//4
	{  129,   129,   126,   126,    63,    63},		//5
	{  257,   129,   126,   126,    63,    63},		//6
	{  385,   129,   126,   126,    63,    63},		//7
	{    1,   257,   126,   126,    63,    63},		//8
	{  129,   257,   126,   126,    63,    63},		//9
	{  257,   257,   126,   126,    63,    63},		//10
	{  385,   257,   126,   126,    63,    63},		//11
	{    1,   385,   126,   126,    63,    63},		//12
	{  129,   385,   126,   126,    63,    63},		//13
	{  273,   385,   126,   126,    63,    63},		//14
	{  385,   385,   126,   126,    63,    63},		//15
};

RECORD jiki_record[ TIME_M * 3 + 1 ];
RECORD *rp;
SINT32 record_fram = 0;;

SINT32 push_flag = 0;

//-----------------------------------------------------------------------------------------------------------------------
//ビームの爆発
//-----------------------------------------------------------------------------------------------------------------------
void beam_bom_exec( TASK *ap )
{
	ap->ang[Y] = SOZ_atan2( ap->pos[X], ap->pos[Y], camera_x[0], camera_y[0] );
	ap->TIMER++;
	if( ap->TIMER % 8 == 0 )
		ap->anime_no++;

	if( ap->anime_no == 16 )
	{
		TASK_end( ap );
		return;
	}
}

void beam_bom_start( FLOAT x, FLOAT y, FLOAT z, FLOAT scale )
{
	TASK *ap;
	ap = TASK_start_GRP( beam_bom_exec, NO_GROUP, TEX_BOM,  bom_rect, 0, "爆発のエフェクト" );
	ap->grp_mode = USE_3DPOS | TEST_ZBUFFER | WRITE_ZBUFFER;
	ap->pos[X] = x;			//画面に映る座標に変換
	ap->pos[Y] = y;			//画面に映る座標に変換
	ap->pos[Z] = z;			//画面に映る座標に変換
	ap->cam_number = 0;
	ap->scale[X] = scale;
	ap->scale[Y] = ap->scale[X];
	ap->pri = OBJECT_PRI * WP;

}

//-----------------------------------------------------------------------------------------------------------------------
//自機のビーム
//-----------------------------------------------------------------------------------------------------------------------
void beam_exec( TASK *ap )
{
	TASK *actp;
	OBJECT_DATA *op;
	for( actp = ap_start; actp != NULL; actp = actp->next )
		if( actp->task_group == OBJECT_GROUP || actp->task_group == MAIN_BILL_GROUP )
			if( kawa_3d_hit_check( ap, actp ) != 0 )
			{
				op = &object_data[ actp->ID ];
				if( actp->task_group == MAIN_BILL_GROUP )
				{
					hit_particle_occurrence( ap );
					actp->HP -= ap->ATK;						//メインビルに対してのダメージを弱くする
				}
				else
				{
					actp->HP -= ap->ATK;
				}

				score += 11;

				if( actp->HP <= 0 )
					score += op->score;								//スコアを加算

				SOZ_locate_print( 64, 5, "enemy_hp%5d", actp->HP );
				beam_bom_start( ap->pos[X], ap->pos[Y], ap->pos[Z], F_Rand2( 3.0f, 6.0f ) );
				TASK_end( ap );
				return;
			}

	task_id_checge( ap, 0 );					//視錐台カリング( チェックを外しとく )

	ap->pos[X] += ap->vec[X];
	ap->pos[Y] += ap->vec[Y];
	ap->pos[Z] += ap->vec[Z];

	if( ap->pos[ Y ] <= ( GROUND - 256.0f ) || ap->pos[Z] > 50000  )
	{
		//beam_bom_start( ap->pos[X], ap->pos[Y], ap->pos[Z], F_Rand2( 2.0f, 5.0f ) );
		TASK_end( ap );
		return;
	}
}

void beam_start( FLOAT x, FLOAT y, FLOAT z,FLOAT vec_x, FLOAT vec_y, FLOAT vec_z, ANGLE ang_y )
{
	TASK *ap;
	ap = TASK_start_MODEL( beam_exec, SHOT_GROUP, MODEL_BEAM, TEX_BEAM, "ビーム" );
	ap->grp_mode =  TEST_ZBUFFER | WRITE_ZBUFFER | NO_SHADOW | USE_LIGHTING;
	ap->blend_type = BLEND_ADD;
	ap->pos[X] = x;
	ap->pos[Y] = y;
	ap->pos[Z] = z;
	ap->vec[X] = vec_x;
	ap->vec[Y] = vec_y;
	ap->vec[Z] = vec_z;
	ap->ang[Y] = ang_y;
	ap->ATK = 50;
	ap->sphire = 30.0f;
	ap->pri = SHOT_PRI * WP;
}



//-----------------------------------------------------------------------------------------------------------------------
//自機の移動
//-----------------------------------------------------------------------------------------------------------------------
void movement_get_key( TASK *ap )
{
	SINT32 key_box[] = { DIK_A, DIK_W, DIK_S, DIK_D };	//
	ANGLE ang_y, ang_x;									//
	SINT32 se_flag;
	SINT32 i;

	ang_y = ap->work1[Y] %= 0xffff;						//直接ap->work1[Y]をいじると都合が悪くなったため内部変数を挟む
	ang_x = ap->angle[X] %= 0xffff;
	if( SOZ_MouseZ() > 20 )
		ap->pos[Y] += 40.0f;
	else if( SOZ_MouseZ() < -20 )
		ap->pos[Y] -= 40.0f;

	ap->vec[X] = SOZ_get_sin( -ang_y ) * 40.0f;
	ap->vec[Y] = SOZ_get_sin( ang_x ) * 40.0f;
	ap->vec[Z] = SOZ_get_cos( -ang_y ) * 40.0f;
	//-----------キー入力-----------//
	if( SOZ_Inkey_DAT( DIK_D ) != 0 )
	{
		if( ang_y > 0x0000 && 0x2000 >= ang_y || ang_y > 0xd000 )
			ap->pos[X] -= 20.0f;
		else if( ang_y > 0x2000 && 0x6000 >= ang_y )
			ap->pos[Z] -= 20.0f;
		else if( ang_y > 0x6000 && 0xa000 >= ang_y )
			ap->pos[X] += 20.0f;
		else if( ang_y > 0xa000 && 0xd000 >= ang_y )
			ap->pos[Z] += 20.0f;

	}

	if( SOZ_Inkey_DAT( DIK_A ) != 0 )
	{
		if( ang_y > 0x0000 && 0x2000 >= ang_y || ang_y > 0xd000 )
			ap->pos[X] += 20.0f;
		else if( ang_y > 0x2000 && 0x6000 >= ang_y )
			ap->pos[Z] += 20.0f;
		else if( ang_y > 0x6000 && 0xa000 >= ang_y )
			ap->pos[X] -= 20.0f;
		else if( ang_y > 0xa000 && 0xd000 >= ang_y )
			ap->pos[Z] -= 20.0f;
	}

	if( SOZ_Inkey_DAT( DIK_W ) != 0 )
	{
		ap->pos[ X ] += -ap->vec[X];
		//ap->pos[ Y ] += -ap->vec[Y];
		ap->pos[ Z ] += -ap->vec[Z];
	}

	if( SOZ_Inkey_DAT( DIK_S ) != 0 )
	{
		ap->pos[ X ] +=  ap->vec[X];
		//ap->pos[ Y ] +=  ap->vec[Y];
		ap->pos[ Z ] +=  ap->vec[Z];
	}

	
	se_flag = 0;										//押されていたときに立つフラグを初期化する
	for( i = 0; i < 4; i++ )
	{
		if( SOZ_Inkey_DAT( key_box[ i ] ) != 0 )		//移動キーのどれかが押されていたら
			se_flag = 1;								//押されていたのでフラグを立てる
	}
	
	if( push_flag == 0 && se_flag != 0 )				//すでに一度流れていなくてキーが押されていなかったら
	{
		SOZ_Music_Load( 2, "grp/se/ufo_movement", 1 );	//SEを流す( 移動をやめたとき消せるようにoggで流す )
		push_flag = 1;									//現在流れていることを伝える
	}
	else if( se_flag == 0 )								//もしキーが押されていなかったら
	{
		SOZ_Music_Stop( 2 );							//移動の音を消す
		push_flag = 0;									//流れていることを伝えるフラグを下げる
	}

}


//-----------------------------------------------------------------------------------------------------------------------
//自機の移動を制限( 関数を入れる順に注意 )
//-----------------------------------------------------------------------------------------------------------------------
void check_range_restriction( TASK *ap, FLOAT pos_x, FLOAT pos_y, FLOAT pos_z )
{
//----------移動の制御----------//
	if( ap->pos[X] >= 50000.0f )			//特定の座標を超えたら
		ap->pos[X] = 50000.0f;				//それ以上進めないようにする
	else if( ap->pos[X] <= 10000.0f )		//特定の座標より小さくなったら
		ap->pos[X] = 10000.0f;				//それ以上進めないようにする

	if( ap->pos[Z] >= 50000.0f )			//特定の座標を超えたら
		ap->pos[Z] = 50000.0f;				//それ以上進めないようにする
	else if( ap->pos[Z] <= 10000.0f )		//特定の座標より小さくなったら
		ap->pos[Z] = 10000.0f;				//それ以上進めないようにする
	
	if( ap->pos[Y] >= 10000.0f )			//特定の座標を超えたら
		ap->pos[Y] = 10000.0f;				//それ以上進めないようにする
	else if( ap->pos[Y] <= GROUND )			//特定の座標より小さくなったら
		ap->pos[Y] = GROUND;				//それ以上進めないようにする
}


//-----------------------------------------------------------------------------------------------------------------------
//自機
//-----------------------------------------------------------------------------------------------------------------------
void shot_move_jiki( TASK *ap )
{
	ANGLE rand_ang;
	FLOAT bullet_vec_x, bullet_vec_y, bullet_vec_z;			//弾のベクトル
	rand_ang = Rand2( -0x100, 0x100 );
	bullet_vec_x = SOZ_get_sin( -ap->work1[Y] + rand_ang ) * BEAM_SPEED;	//弾の飛ぶベクトルを角度から計算
	bullet_vec_y = SOZ_get_sin( -ap->angle[X] + Rand2( -0x100, 0x100 ) ) * BEAM_SPEED;	//弾の飛ぶベクトルを角度から計算
	bullet_vec_z = SOZ_get_cos( -ap->work1[Y] + rand_ang ) * BEAM_SPEED;	//弾の飛ぶベクトルを角度から計算
	
	//----------マウス入力-----------//
	
	//----------ショット----------//
	if( SOZ_Mouse_Button( 0 ) % BEAM_TIME == 0 && SOZ_Mouse_Button( 0 ) != 0 || SOZ_Mouse_Button( 0 ) == 1  || game_type == 501 && rp->click[0] != 0 )		//右クリックすると	
	{
		beam_start( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ], -bullet_vec_x, bullet_vec_y, -bullet_vec_z, -ap->work1[ Y ] + rand_ang );
		rp->click[0] = 1;
	}
	
	//----------つかみ-----------//
	if( SOZ_Mouse_Button( 1 ) == 1 && catch_switch == FALSE  || game_type == 501 && rp->click[1] != 0 && catch_switch == FALSE  )
	{
		TASK_end_group( HAND_GROUP );							//飛んでる手を消す
		catch_switch = FALSE;									//つかみのフラグを一応初期化
		hand_start( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ], -bullet_vec_x * 2, bullet_vec_y * 2, -bullet_vec_z * 2, ap->angle[ X ], ap->work1[ Y ] );			//手を飛ばす
		rp->click[1] = 1;
	}

	if( SOZ_Inkey_TRG( DIK_P ) != 0 )							//なにかあったとき用の座標リセットボタン
	{
		ap->pos[X] = JIKI_X;									//初期位置を代入
		ap->pos[Y] = JIKI_Y;									//初期位置を代入
		ap->pos[Z] = JIKI_Z;									//初期位置を代入
		ap->angle[ Y ] = 0x00;									//角度も0にする
	}
}



//-----------------------------------------------------------------------------------------------------------------------
//自機
//-----------------------------------------------------------------------------------------------------------------------
void jiki_exec( TASK *ap )
{
	FLOAT pos_x, pos_y, pos_z;
	if( game_type != 501 )
	{
		//ANGLE ang_y;
		pos_x = ap->pos[ X ];									//横の座標を保存
		pos_y = ap->pos[ Y ];									//縦の座標を保存
		ap->work1[ Y ] = ap->angle[ Y ];							//
		pos_z = ap->pos[ Z ];									//前後の座標を保存
		ap->work1[ Y ] = ap->work1[ Y ] + 0x8000;					//32768( 180度 )回す( 目玉の名残
		//ap->work1[Y] %= 0xffff;									//65535( 360度 )を超えないようにする
		//ap->angle[Y] %= 0xffff;
		ap->ang[ Y ] += 0xff;										//自機がくるくる回る
		//SOZ_point_setting( ap );

		shot_move_jiki( ap );									//ショットを出す
		movement_get_key( ap );									//キーの移動
		check_range_restriction( ap, pos_x, pos_y, pos_z );		//自機の移動範囲を制限する

		TASK *actp;
		for( actp = ap_start; actp != NULL; actp = actp->next )
			if( actp->task_group == OBJECT_GROUP || actp->task_group == MAIN_BILL_GROUP )
				if( kawa_3d_hit_check( ap, actp ) != 0 )
				{
					ap->pos[ X ] = pos_x;
					ap->pos[ Y ] = pos_y;
					ap->pos[ Z ] = pos_z;
				}

		rp->pos[ X ] = ap->pos[ X ];
		rp->pos[ Y ] = ap->pos[ Y ];
		rp->pos[ Z ] = ap->pos[ Z ];
		rp->ang[ X ] = ap->angle[ X ];
		rp->ang[ Y ] = ap->work1[ Y ];
	}
	else
	{
		ap->pos[X] = rp->pos[X];
		ap->pos[Y] = rp->pos[Y];
		ap->pos[Z] = rp->pos[Z];
		ap->work1[Y] = rp->ang[Y];
		ap->angle[ X ] = rp->ang[X];

		shot_move_jiki( ap );									//ショットを出す
	}
	

	SOZ_locate_print( 2, 2, "xは%5f", ap->pos[X] );
	SOZ_locate_print( 2, 3, "yは%5f", ap->pos[Y] );
	SOZ_locate_print( 2, 4, "zは%5f", ap->pos[Z] );
	SOZ_locate_print( 2, 5, "work1[Y]は%5d", ap->work1[Y] );		//移動に大事な角度が入っている				<-|
	SOZ_locate_print( 2, 6, "angle[Y]は%5d", ap->angle[Y] );		//カメラの移動に大事な角度が入っている		<-|ここが90度の差ならいい
}

void jiki_start( void )
{
	TASK *ap;
	ap = TASK_start_MODEL( jiki_exec, JIKI_GROUP, MODEL_JIKI, TEX_JIKI, "自機" );
	ap->grp_mode =  TEST_ZBUFFER | WRITE_ZBUFFER  | NO_SHADOW | USE_LIGHTING | USE_SPECULAR;//| USE_2DMODEL_POS
	ap->pos[X] = JIKI_X;	
	ap->pos[Y] = JIKI_Y;	
	ap->pos[Z] = JIKI_Z;	
	specular_status_set( ap, 2.0f, 1.3f,1.3f,1.3f );
	ap->scale[X] = 0.5f;
	ap->scale[Y] = ap->scale[X];
	ap->scale[Z] = ap->scale[Y];
	ap->sphire = 45.0f;
	ap->ang[Y] = 0x8000;
	ap->pri = 100 * WP;
	ap->pri = JIKI_PRI * WP;
	jiki = ap;
}

void record_exec( TASK *ap )
{
	rp = &jiki_record[ record_fram ];
	record_fram++;

	if( record_fram > TIME_M * 3 )
		record_fram = TIME_M * 3;
}

void record_mane_start( void )
{
	TASK *ap;
	ap = TASK_start( record_exec, MANE_GROUP, "レコード" );
	ap->exe_pri = 31;
	rp = &jiki_record[ record_fram ];
}