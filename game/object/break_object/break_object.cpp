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

//--------------------------------------------------------------------------------
//外部変数
//--------------------------------------------------------------------------------
SINT32 object_id = 1;									//ユニークナンバーを計測するのに使う( 初期化必須 )

//--------------------------------------------------------------------------------
//オブジェクト同士のヒットを確認する
//--------------------------------------------------------------------------------
void attack_hit_check( TASK *ap, OBJECT_DATA *op )
{
	TASK *actp;
	SINT32 group_box[ 3 ] = { MAIN_BILL_GROUP, MAIN_COMP_GROUP };
	SINT32 i;
	for( actp = ap_start; actp != NULL; actp = actp->next )
		if( jiki_hit_check( ap, actp ) != 0 )			//今回は直接ヒット確認する
			for( i = 0; i < 2; i++ )
				if( actp->task_group == group_box[ i ] )
				{
					actp->HP -= ap->ATK;
					score += op->score;
					switch( op->object_group )
					{
						case CAR_GROUP:
							SOZ_play_se( SE_BILL_BREAK, op->se_vol, 1, 1.0f );
							break;

						default:
							SOZ_play_se( op->se_no, op->se_vol, 1, 1.0f );
							break;
					}

					if( ap->ID == 20 )
						alien_start( ap->fwork1[X], ap->fwork1[Y], ap->fwork1[Z], ap->ang[X], ap->angle[Y], ap->scale[X], ap->fwork8[X], ap->fwork8[Y], ap->ID );

					beam_bom_start( ap->pos[X], ap->pos[Y], ap->pos[Z], F_Rand2( 3.0f, 6.0f ) );
					hit_particle_occurrence( ap );
					TASK_end( ap );
					return;
				}
}


void break_object_exec( TASK *ap )
{
	OBJECT_DATA *op;
	op = &object_data[ ap->ID ];
	ap->sphire = sphire_get( ap );
	if( ap->SWITCH == 0 )
		ap->vec[Y] -= ap->acc[Y];
	ap->pos[X] += ap->vec[X];
	ap->pos[Y] += ap->vec[Y];
	ap->pos[Z] += ap->vec[Z];
	if( ap->pos[ Y ] <= GROUND )
	{
		ap->pos[ Y ] = GROUND;
		ap->ang[Z] &= 0x4000;
		ap->vec[X] = 0.0f;
		ap->vec[Y] = 0.0f;
		ap->vec[Z] = 0.0f;
	}
	else
	{
		ap->ang[X] += 0x40;									//浮いてる間はうねうね回る
		ap->ang[ Z ] += 0x80;								//浮いてる間はうねうね回る
	}

	if( game_type != 101 && game_type != 11 && game_type != 501 )				//ゲームでもタイトル画面でも無ければ
	{
		ap->TIMER++;
		if( ap->TIMER > TIME_S * 4  )
			if( ap->TIMER % 8 == 0 )
				ap->base_color[0][0] -= 0x4;

		if( ap->base_color[ 0 ][ 0 ] <= 0 )
		{
			TASK_end( ap );
			return;
		}
		ap->pri++;
	}

	if( ap->SWITCH != 0 )									//ここが0以外なら
		attack_hit_check( ap, op );							//メインビルに当たる

	task_id_checge( ap, ap->SWITCH );								//視錐台カリング
		
}

void break_object_start( DEFAULT_ARGUMENT, FLOAT atk, SINT32 id )
{
	TASK *ap;
	OBJECT_DATA *op;
	op = &object_data[ id ];
	ap = TASK_start_MODEL( break_object_exec, BREAK_OBJECT_GROUP, op->model_no, op->tex_no, "壊れたオブジェクト" );
	ap->grp_mode =  op->grp_flag;	//フラグを入れる
	specular_sturct_set( ap, op );	//光に関するステータスを入れる
	common_ambient( ap );
	scale_all_chenge( ap, op->scale );
	ap->emissive[0] = 0.35f;
	ap->emissive[1] = 0.35f;
	ap->emissive[2] = 0.35f;
	ap->pos[X] = x;					//座標(x
	ap->pos[Y] = y;					//座標(y
	ap->pos[Z] = z;					//座標(z
	ap->vec[X] = vec_x;				//ベクトル(x
	ap->vec[Y] = vec_y;				//ベクトル(y
	ap->vec[Z] = vec_z;				//ベクトル(z
	ap->acc[Y] = 0.35f;				//
	ap->sphire = 128.0f;			//スフィアの大きさを確定させる
	ap->unique_id = object_id;		//オブジェクト数への識別番号
	ap->GROUP  = op->object_group;	//どのグループか伝える
	ap->ATK = ( SINT32 )( op->atk * atk );	//攻撃力
	ap->ID  = id;					//識別番号
	ap->pri = OBJECT_PRI * WP;
}