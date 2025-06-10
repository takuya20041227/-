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


//-----------------------------------------------------------------------------------------------------------------------
//外部変数
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
//手から出るモヤのエフェクト
//-----------------------------------------------------------------------------------------------------------------------
void hand_efe_exec( TASK *ap )
{
	ap->TIMER++;
	ap->angle[X] += 0x400;
	ap->fwork2[X] += 6.0f;
	ap->pos[Y] += ap->vec[Y];
	ap->pos[X] = ap->fwork1[X] + SOZ_get_sin( ap->angle[X]) * ap->fwork2[X];
	ap->pos[Z] = ap->fwork1[Z] + SOZ_get_sin( ap->angle[X]) * ap->fwork2[X];

	ap->fwork1[X] += ap->fwork1[P];
	ap->fwork1[Z] += ap->fwork1[E];

	ap->ang[X] += 0x200;
	ap->ang[Y] += 0x200;
	ap->ang[Z] += 0x200;

	ap->vec[Y] += 0.25f;

	if( ap->TIMER % 4 == 0 )
		ap->base_color[0][0] -= 0x8;

	task_id_checge( ap ,0 );

	if( ap->base_color[ 0 ][ 0 ] <= 0 )
	{
		TASK_end( ap );
		return;
	}
}

void hand_efe_start( FLOAT x, FLOAT y, FLOAT z, FLOAT scale )
{
	TASK *ap;
	ap = TASK_start_MODEL( hand_efe_exec, HAND_GROUP, MODEL_HAND_EFE, TEX_HAND, "手のエフェクト" );
	
	ap->grp_mode = ap->grp_mode = TEST_ZBUFFER | WRITE_ZBUFFER  | NO_SHADOW | USE_LIGHTING;

	ap->pos[X] = x;
	ap->pos[Y] = y;
	ap->pos[Z] = z;

	ap->fwork1[X] = x;
	ap->fwork1[Z] = z;

	ap->fwork1[P] = F_Rand2( -6.0f, 6.0f );
	ap->fwork1[E] = F_Rand2( -6.0f, 6.0f );

	ap->fwork2[X] = 0.0f;

	ap->vec[Y] = -F_Rand2( 4.0f, 8.0f );
	
	

	ap->scale[X] = scale;
	ap->scale[Y] = ap->scale[X];
	ap->scale[Z] = ap->scale[Y];
}

//-----------------------------------------------------------------------------------------------------------------------
//差が設定より大きいと値を返す
//-----------------------------------------------------------------------------------------------------------------------
SINT32 sa_check_bigger( FLOAT ap_value, FLOAT actp_value, FLOAT sa_max )
{
	FLOAT sa, abs_sa;
	sa = ap_value - actp_value;						//差を調べる
	abs_sa = ( FLOAT )fabs( ( DOUBLE )sa );			//絶対値を調べる
	if( abs_sa > sa_max )							//差が特定の値を
		return 1;									//

	return 0;										//
}


//-----------------------------------------------------------------------------------------------------------------------
//差が設定より小さいと値を返す
//-----------------------------------------------------------------------------------------------------------------------
SINT32 sa_check_smaller( FLOAT ap_value, FLOAT actp_value, FLOAT sa_max )
{
	FLOAT sa, abs_sa;
	sa = ap_value - actp_value;						//差を調べる
	abs_sa = ( FLOAT )fabs( ( DOUBLE )sa );			//絶対値を調べる
	if( abs_sa < sa_max )							//差が特定の値を
		return 1;									//

	return 0;										//
}






//-----------------------------------------------------------------------------------------------------------------------
//座標が重なったら
//-----------------------------------------------------------------------------------------------------------------------
SINT32 pos_check( TASK *ap, TASK *actp, FLOAT sa )
{
	if( sa_check_smaller( ap->pos[X], actp->pos[X], sa ) != 0 )			//横軸の差が縮まる
		if( sa_check_smaller( ap->pos[Y], actp->pos[Y], sa ) != 0 )		//縦軸の差が縮まる
			if( sa_check_smaller( ap->pos[Z], actp->pos[Z], sa ) != 0 )	//前後軸の差が縮まる
				return 1;												//全部差が特定の位置まで近づいたら

	return 0;															//それ以外は0を返す
}


//-----------------------------------------------------------------------------------------------------------------------
//当たったオブジェクトを掴む
//-----------------------------------------------------------------------------------------------------------------------
void catch_check( TASK *ap )
{
	TASK *actp;
#if DEBUG
	OBJECT_DATA *op;
	SINT32 y;
	y = 3;
#endif
	for( actp = ap_start; actp != NULL; actp = actp->next )
		if( actp->task_group == BREAK_OBJECT_GROUP )
			if( kawa_3d_hit_check( ap, actp ) != 0 )			
			{	
				catch_switch = ON;
				actp->vec[X] = RESET;
				actp->vec[Y] = RESET;
				actp->vec[Z] = RESET;
				actp->pos[X] = ap->pos[X];
				actp->pos[Y] = ap->pos[Y];
				actp->pos[Z] = ap->pos[Z];
				actp->SWITCH = 1;				//これを立てるとメインビルに当たるようにする
				icon_param_get( actp );			//譲歩をいれる
				if( ap->SCENE == 20 )			//自機のところまで来ると
					actp->task_id = TASK_PROGRAM;	//一時的にモデルの描画を辞める

#if DEBUG
				op = &object_data[ actp->ID ];			//掴んでるモデルを見分けるために使う
#endif
			}
}


//-----------------------------------------------------------------------------------------------------------------------
//掴んだオブジェクトをとばす
//-----------------------------------------------------------------------------------------------------------------------
void catch_shot( TASK *ap )
{
	TASK *actp;
	for( actp = ap_start; actp != NULL; actp = actp->next )
		if( kawa_3d_hit_check( ap, actp ) != 0 )
			if( actp->task_group == BREAK_OBJECT_GROUP )
			{
				actp->task_id = TASK_MODEL;
				actp->vec[X] = -SOZ_get_sin( -jiki->work1[Y] ) * 130.0f;	//弾の飛ぶベクトルを角度から計算
				actp->vec[Y] = SOZ_get_sin( -jiki->angle[ X ] ) * 130.0f;	//弾の飛ぶベクトルを角度から計算
				actp->vec[Z] = -SOZ_get_cos( -jiki->work1[Y] ) * 130.0f;	//弾の飛ぶベクトルを角度から計算
			}
}



//-----------------------------------------------------------------------------------------------------------------------
//掴む手
//-----------------------------------------------------------------------------------------------------------------------
void hand_exec( TASK *ap )
{            
	ANGLE	ang_x, ang_y, ang_z;
	switch( ap->SCENE )			
	{
		case 0:								//地面に当たるまで飛ぶ
			if( ap->TIMER % 4 == 0 )
				hand_efe_start( ap->pos[X], ap->pos[Y], ap->pos[Z], F_Rand2( 0.5f, 1.0f ) );

			ap->TIMER++;					//フレームを計測
			ap->pos[X] += ap->vec[X];		//座標にベクトルを加算する( x
			ap->pos[Y] += ap->vec[Y];		//座標にベクトルを加算する( y
			ap->pos[Z] += ap->vec[Z];		//座標にベクトルを加算する( z
			if( ap->pos[ Y ] <= GROUND || ap->TIMER > TIME_S * 2 )		//地面についたら
			{
				ap->vec[X] = -ap->vec[X];
				ap->vec[Y] = -ap->vec[Y];
				ap->vec[Z] = -ap->vec[Z];
				if( ap->pos[ Y ] <= GROUND )
					ap->pos[Y] = GROUND;
				ap->TIMER = RESET;
				ap->SCENE = 10;

			}
			break;

		case 10:							//自機に戻っていく
			ap->TIMER++;					//一応数を数えとく
			ang_x = SOZ_atan2( jiki->pos[X], jiki->pos[Y], ap->pos[X], ap->pos[Y] );
			ang_y = SOZ_atan2( jiki->pos[Z], jiki->pos[X], ap->pos[Z], ap->pos[X] );
			ang_z = SOZ_atan2( jiki->pos[X], jiki->pos[Z], ap->pos[X], ap->pos[Z] );
			//ap->ang[X] = -ang_x;
			ap->ang[Y] = ang_y;
			ap->vec[X] = SOZ_get_sin( ang_y ) * HAND_SPEED;	//ベクトルの計算
			ap->vec[Y] = SOZ_get_sin( ang_x ) * HAND_SPEED;	//ベクトルの計算
			ap->vec[Z] = SOZ_get_sin( ang_z ) * HAND_SPEED;	//ベクトルの計算
			ap->pos[X] -= ap->vec[X];		//自機の方に戻っていく
			ap->pos[Y] -= ap->vec[Y];		//自機の方に戻っていく
			ap->pos[Z] -= ap->vec[Z];		//自機の方に戻っていく
			if( pos_check( ap, jiki, 128.0f ) != 0 )
			{
				if( catch_switch == 0 )		//なにも捕まえていなかったら
				{
					TASK_end( ap );
					return;
				}
				ap->task_id = TASK_PROGRAM;
				ap->TIMER = RESET;
				ap->SCENE = 20;
			}
			break;

		case 20:
			ANGLE	ang_y;
			ang_y = SOZ_atan2( jiki->pos[Z], jiki->pos[X], ap->pos[Z], ap->pos[X] ); 
			ap->ang[Y] = ang_y;
			ap->pos[X] = jiki->pos[X];		//自機の方に戻っていく
			ap->pos[Y] = jiki->pos[Y];		//自機の方に戻っていく
			ap->pos[Z] = jiki->pos[Z];		//自機の方に戻っていく
			if( SOZ_Mouse_Button( 1 ) == 1 || game_type == 501 && rp->click[1] != 0 )
			{
				rp->click[1] = 1;
				catch_switch = 0;
				catch_shot( ap );
				icon_box_all_init();
				TASK_end( ap );
				return;
			}
			break;
	}  

	catch_check( ap );
}

void hand_start( DEFAULT_ARGUMENT, ANGLE ang_x, ANGLE ang_y )
{
	TASK *ap;
	ap = TASK_start_MODEL( hand_exec, HAND_GROUP, MODEL_HAND, TEX_HAND, "手のモデル" );
	ap->grp_mode = TEST_ZBUFFER | WRITE_ZBUFFER  | NO_SHADOW | USE_LIGHTING;
	ap->pos[X] = x;			//座標( x
	ap->pos[Y] = y;			//座標( y
	ap->pos[Z] = z;			//座標( z
	ap->vec[X] = vec_x;		//ベクトル( x
	ap->vec[Y] = vec_y;		//ベクトル( y
	ap->vec[Z] = vec_z;		//ベクトル( z
	ap->ang[X] = ang_x;		//
	ap->ang[Y] = ang_y;		//
	ap->sphire = 240.0f;
	ap->pri = JIKI_PRI * WP - 1;
}








