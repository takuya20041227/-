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


//--------------------------------------------------------------------------------------------
//ガラスの割れる演出につかうポリゴン
//--------------------------------------------------------------------------------------------
PRIM_POLY3D_TEX glas_poly[]=   
{
	{      0.0f,	0.0f,     0.0f,		0x70ffffff,  0.0f, 0.0f },
	{     64.0f,	0.0f,     0.0f,		0x70ffffff,  1.0f, 0.0f },
	{      0.0f,   32.0f,     0.0f,		0x70ffffff,  0.0f, 1.0f },
};


//--------------------------------------------------------------------------------------------
//パーティクルが増えすぎたときに消す
//--------------------------------------------------------------------------------------------
void particle_safety_exec( TASK *ap )
{
	TASK *actp;
	SINT32 particle, rand_end;
	particle = 0;

//-----------------------パーティクルの数を計測---------------------//
	for( actp = ap_start; actp != NULL; actp = actp->next )
		if( actp->task_group == BREAK_EFFECTS_GROUP )
			particle++;

//----------------パーティクルの数が一定を超えていたら-----------------//
	if( particle > 800 )
		for( actp = ap_start; actp != NULL; actp = actp->next )
			if( actp->task_group == BREAK_EFFECTS_GROUP )
			{
				if( actp->task_id == TASK_PROGRAM )				//描画していないなら
				{
					TASK_end( actp );							//タスクを消す
					continue;									//次の処理へ
				}

				rand_end = Rand2( 0, 101 );
				if( rand_end % 2 == 0 )
				{
					TASK_end( actp );
					continue;
				}
			}
}

void particle_safety_start( void )
{
	TASK *ap;
	ap = TASK_start( particle_safety_exec, MANE_GROUP, "パーティクルが増えすぎるときに消す" );
}



void glas_efe_drawfunc( TASK *ap )
{
	SOZ_set_model_param( ZBUF_TEST | ZBUF_WRITE, BILINEAR_ON, LIGHTING_OFF, SPECULAR_OFF );
	SOZ_ResetClipping();
	SOZ_reset_fog();           //fogをリセット
	SOZ_set_culling( D3DCULL_NONE );					//両面表示する
	SOZ_blend_setting( BLEND_NORMAL );
	SOZ_set_texture( 0, TEX_GLAS );							//ガラスの破片のテクスチャー

	//プリミティブ転送
	SOZ_matrix_model_maker( 0, ap->pos[X], ap->pos[Y], ap->pos[Z], ap->ang[X],  ap->ang[Y], ap->ang[Z], ap->scale[X], ap->scale[Y], ap->scale[Z] );
	SOZ_render_start();
	SOZ_primitive_draw( D3DPT_TRIANGLESTRIP, 1, glas_poly, sizeof( PRIM_POLY3D_TEX ), FVF_POLY3D_TEX );
	SOZ_render_end();
}

void glas_efe_exec( TASK *ap )
{
	ap->pos[X] += ap->vec[X];								//動かす
	ap->pos[Y] += ap->vec[Y];								//動かす
	ap->pos[Z] += ap->vec[Z];								//動かす

	ap->vec[Y] -= ap->acc[Y];								//落下させる

	ap->ang[X] += ap->ang_spd[X];							//適当に回す
	ap->ang[Y] += ap->ang_spd[Y];							//適当に回す
	ap->ang[Z] += ap->ang_spd[Z];							//適当に回す

	ap->task_id = TASK_GRP;
	//-----視錐台カリング-----/
	if( SOZ_viewclip_checker( ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ], 16.0f, CHECK_VIEW_LEFT | CHECK_VIEW_RIGHT | CHECK_VIEW_FRONT | CHECK_VIEW_BACK ) )
	{
		ap->task_id = TASK_PROGRAM;
	}

	if( ap->pos[ Y ] <= GROUND )								//地面についてると
	{
		TASK_end( ap );
		return;
	}
}

void glas_efe_start( DEFAULT_ARGUMENT )
{
	TASK *ap;
	ap = TASK_start_DRAWFUNC( glas_efe_exec, glas_efe_drawfunc, BREAK_EFFECTS_GROUP, "ガラスの破片" );
	ap->pos[X] = x;
	ap->pos[Y] = y;
	ap->pos[Z] = z;
	ap->vec[X] = vec_x;
	ap->vec[Y] = vec_y;
	ap->vec[Z] = vec_z;
	ap->acc[Y] = 0.98f;
	common_ambient( ap );
	ap->scale[X] = F_Rand2( 1.0f, 1.5f );
	ap->scale[Y] = ap->scale[X];

	ap->ang_spd[X] = Rand2( -0x200, 0x200 );
	ap->ang_spd[Y] = Rand2( -0x200, 0x200 );
	ap->ang_spd[Z] = Rand2( -0x200, 0x200 );
}


//--------------------------------------------------------------------------------
//ケースによってはエフェクトを散りばめる関数
//--------------------------------------------------------------------------------
void case_object_efe_model( TASK *ap, OBJECT_DATA *op  )
{
	SINT32 r_model;						//ランダムな値を入れる
	switch( op->object_group )				//
	{
		case SCHOOL_GROUP:					//もし学校なら
			r_model = Rand2( 0, 100 );
			if( r_model % 2 == 0 )			//もし偶数なら
				ap->model_no = MODEL_SCHOOL_CHAIR;		//イスのエフェクト
			else
				ap->model_no = MODEL_SCHOOL_TABLE;		//テーブルのエフェクト
			break;

		case HOUSE_GROUP:
			r_model = Rand2( 0, 100 );
			if( r_model % 2 == 0 )
			{
				ap->model_no = MODEL_TANSU;
				ap->tex_no   = TEX_TANSU;
			}
			else
			{
				ap->model_no = MODEL_HUTON;
				ap->tex_no = TEX_BET;
				if( r_model > 50 )
				{
					ap->model_no = MODEL_BET;
					ap->tex_no = TEX_BET;
				}
			}
			break;

		case FISH_GROUP:
			ap->scale[X] = F_Rand2( 0.5f, 0.76f );
			ap->scale[Y] = ap->scale[X];
			ap->scale[Z] = ap->scale[Y];
			break;

		default:							//基本は何もしない
			//何もしない
			break;
	}

	if( ap->ID == 21 || ap->ID == 10 || ap->ID == 11 || ap->ID == 23 )						//アームメカなら
	{
		r_model = Rand2( 0, 100 );
		if( r_model % 2 == 0 )
			ap->tex_no = TEX_GEAR;
		else
		{
			ap->tex_no = TEX_GEAR_GRY;
			if( r_model > 50 )
				ap->tex_no = TEX_GEAR_RED;
		}
		ap->pow = 1.5f;
		ap->specular[0] = 2.75f;
		ap->specular[1] = 2.75f;
		ap->specular[2] = 2.75f;
	}
}

//--------------------------------------------------------------------------------
//オブジェクトに当たると跳ねる
//--------------------------------------------------------------------------------
void obj_hit_check( TASK *ap )
{
	TASK *actp;
	for( actp = ap_start; actp != NULL; actp = actp->next )
		if( actp->task_group == OBJECT_GROUP )
			if( ap->HP > 0 )
				if( kawa_3d_hit_check( ap, actp ) != 0 )
				{
					ap->vec[X] = 0.0f;
					ap->vec[Z] = 0.0f;
				}

	
}

//--------------------------------------------------------------------------------
//オブジェクトが壊れたときのエフェクトのタスク
//--------------------------------------------------------------------------------
void break_effect_exec( TASK *ap )
{
	OBJECT_DATA *op;
	op = &object_data[ ap->ID ];
	obj_hit_check( ap );
	ap->pos[X] += ap->vec[X];			//ベクトルを加算させる
	ap->pos[Y] += ap->vec[Y];			//ベクトルを加算させる
	ap->pos[Z] += ap->vec[Z];			//ベクトルを加算させる
	ap->vec[Y] -= ap->acc[Y];				//落下させる
	if( ap->pos[ Y ] <= GROUND )		//地面についたら
	{
		if( ap->SWITCH == 0 )
		//	SOZ_play_se( op->se_no, 5.0f, 1.0f, 1.0f );
		ap->SWITCH = 1;

		vec_all_init( ap );							//ベクトルをすべて初期化
		ap->TIMER++;								//時間を計測
		if( ap->TIMER >= 40 )				//3秒経ったら
		{
			if( ap->TIMER % 4 == 0 )				//8フレームに一回
				ap->base_color[0][0] -= 0x8;		//だんだん透明にしていく

			if( ap->base_color[0][0] <= 0 )			//0を下回ったら
			{
				TASK_end( ap );			//タスクを消す
				return;					//これより下は実行しないようにする
			}
		}
	}
	else
	{
		switch( op->object_group )
		{
			case FISH_GROUP:
				ap->ang[X] = SOZ_get_atan( ap->vec[ x_check( ap ) ], ap->vec[Y] );
				ap->angle[Y] = SOZ_get_atan( ap->vec[ x_check( ap ) ], ap->vec[ z_check( ap ) ] );
				ap->ang[Y] = ap->angle[Y] - 0x4000; 
				break;

			default:							
				ap->ang[X] += ap->ang_spd[X];	//回転( 縦 )
				ap->ang[Y] += ap->ang_spd[Y];	//回転( 横 )
				ap->ang[Z] += ap->ang_spd[Z];	//回転( 回る )
				break;
		}
	}
	task_id_checge( ap, 0 );					//視錐台カリング
}

void break_effect_start( OBJECT_DATA * op, DEFAULT_ARGUMENT, FLOAT acc_y, FLOAT sphire, SINT32 id )
{
	TASK *ap;
	
	ap = TASK_start_MODEL( break_effect_exec, BREAK_EFFECTS_GROUP, op->particle_model, op->particle_tex, "エフェクト" );
	ap->grp_mode = op->grp_flag;		//
	common_ambient( ap );
	//ap->grp_mode &= ~WRITE_ZBUFFER;		//
	ap->scale[X] = ap->scale[Y] = ap->scale[Z] = F_Rand2( 0.7f, 1.3f );
	ap->pos[X] = x;
	ap->pos[Y] = y;
	ap->pos[Z] = z;
	ap->vec[X] = vec_x;
	ap->vec[Y] = vec_y;
	ap->vec[Z] = vec_z;
	ap->acc[Y] = acc_y;
	ap->ang_spd[X] = Rand2( -0x400, 0x400 );
	ap->ang_spd[Y] = Rand2( -0x400, 0x400 );
	ap->ang_spd[Z] = Rand2( -0x400, 0x400 );
	ap->sphire = sphire;
	ap->ID = id;
	case_object_efe_model( ap, op );					//場合によってはモデルを変える
	ap->pri = OBJECT_PRI * WP;
}


//--------------------------------------------------------------------------------
//猫用のエフェクト
//--------------------------------------------------------------------------------
void cat_effect_exec( TASK *ap )
{
	obj_hit_check( ap );
	ap->pos[X] += ap->vec[X];			//ベクトルを加算させる
	ap->pos[Y] += ap->vec[Y];			//ベクトルを加算させる
	ap->pos[Z] += ap->vec[Z];			//ベクトルを加算させる
	ap->vec[Y] -= ap->acc[Y];			//落下させる
	if( ap->pos[ Y ] <= GROUND )		//地面についたら
	{
		ap->vec[Y] = 0.0f;
		if( ap->SWITCH == 0 )
		//	SOZ_play_se( op->se_no, 5.0f, 1.0f, 1.0f );
		ap->SWITCH = 1;

		
		ap->TIMER++;								//時間を計測
		if( ap->TIMER >= 40 )				//3秒経ったら
		{
			if( ap->TIMER % 4 == 0 )				//8フレームに一回
				ap->base_color[0][0] -= 0x8;		//だんだん透明にしていく

			if( ap->base_color[0][0] <= 0 )			//0を下回ったら
			{
				TASK_end( ap );			//タスクを消す
				return;					//これより下は実行しないようにする
			}
		}
	}
	else
	{
		ap->ang[Y] = SOZ_get_atan( ap->vec[X], ap->vec[Z] );
	}
	task_id_checge( ap, 0 );					//視錐台カリング
}

void cat_effect_start( OBJECT_DATA * op, DEFAULT_ARGUMENT, FLOAT acc_y, FLOAT sphire, SINT32 id )
{
	TASK *ap;
	SINT32 rand_tex, tex_box[] = { TEX_CAT_GRY, TEX_CAT_TYA, TEX_CAT_PEL };
	ap = TASK_start_MODEL( cat_effect_exec, BREAK_EFFECTS_GROUP, op->particle_model, op->particle_tex, "エフェクト" );
	ap->grp_mode = op->grp_flag;		//
	common_ambient( ap );
	//ap->grp_mode &= ~WRITE_ZBUFFER;		//
	ap->scale[X] = ap->scale[Y] = ap->scale[Z] = F_Rand2( 0.7f, 1.3f );
	ap->pos[X] = x;
	ap->pos[Y] = y;
	ap->pos[Z] = z;
	ap->vec[X] = vec_x * 1.5f;
	ap->vec[Y] = vec_y;
	ap->vec[Z] = vec_z * 1.5f;
	ap->acc[Y] = acc_y;
	ap->sphire = sphire;
	rand_tex = Rand2( 0, 3 );
	ap->tex_no = tex_box[ rand_tex];
	ap->ID = id;
	ap->pri = OBJECT_PRI * WP;
}

//--------------------------------------------------------------------------------
//エフェクトのタスクをケースで分ける
//--------------------------------------------------------------------------------
void effect_case( OBJECT_DATA * op, DEFAULT_ARGUMENT, FLOAT sphire, SINT32 id )
{
	switch( id )
	{
		case 18:
			cat_effect_start( op, x, y, z, vec_x, vec_y, vec_z, 0.65f, sphire, id );
			break; 

		default:
			break_effect_start( op, x, y, z, vec_x, vec_y, vec_z, 0.25f, sphire, id );
			break;
	}
}



//--------------------------------------------------------------------------------
//設定した数エフェクトを出す
//--------------------------------------------------------------------------------
void break_effect_occurrence( TASK *ap, FLOAT sphire )
{
	SINT32	i;
	ANGLE	ang, add_ang;				//
	FLOAT	vec_x, vec_y, vec_z, len;
	OBJECT_DATA *op;
	op = &object_data[ ap->ID ];	
	ang = 0x0;
	add_ang = 0xffff / op->particle_num;
	for( i = 0; i < op->particle_num; i++ )
	{
		len = F_Rand2( 10.0f, 25.0f );
		vec_x = SOZ_get_sin( ang ) * len;
		vec_y = F_Rand2( 20.0f, 30.0f );
		vec_z = SOZ_get_cos( ang ) * len;
		effect_case( op, ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ], vec_x, vec_y, vec_z, sphire, ap->ID );
		ang += add_ang;	
	}
}


//--------------------------------------------------------------------------------
//設定した数エフェクトを出す( メインビルに当たったとき )
//--------------------------------------------------------------------------------
void hit_particle_occurrence( TASK *ap )
{
	SINT32	i, particle_num;
	FLOAT	vec_x, vec_y, vec_z;
	OBJECT_DATA *op;
	op = &object_data[ ap->ID ];	
	particle_num = op->particle_num;				//パーティクルの設定
	if( ap->task_group == SHOT_GROUP )
		particle_num = Rand2( 1, 2	 );

	for( i = 0; i < particle_num; i++ )			//回す
	{
		vec_x = ap->vec[X] + F_Rand2( -25.0f, 25.0f );
		vec_y = ap->vec[Y] + F_Rand2( 2.0f, 15.0f )  * 3.0f;
		vec_z = ap->vec[Z] + F_Rand2( -25.0f, 25.0f );
		//if( ap->task_group == SHOT_GROUP )			//ビームなら
			glas_efe_start( ap->pos[X], ap->pos[Y], ap->pos[Z], -vec_x, vec_y, -vec_z );			//ガラスの破片を出す
		//else										//ビームじゃないなら
			effect_case( op, ap->pos[ X ], ap->pos[ Y ], ap->pos[ Z ], -vec_x, vec_y, -vec_z, 15.0f, ap->ID );
	}
}
