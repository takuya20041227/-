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


//-----------------------------------------------------------------------------------------------------------------------
//メインコンピューター
//-----------------------------------------------------------------------------------------------------------------------
void earth_exec( TASK *ap )
{
	ap->ang[Y] -= 0x80;
}
void sub_parts_exec( TASK *ap )
{
	ap->ang[Y] += ap->ang_spd[Y];
}

void main_computer_exec( TASK *ap )
{
	ap->sphire = sphire_get( ap );
	if( ap->work1[X] != 0 )											//自機とぶつかったら0以外になる	
	{
		tex_title_reset();                                          //タイトルでしか使ってないテクスチャーを消去
        model_title_reset();                                        //タイトルでしか使ってないモデルを消去
		game_type = 100;
		record_fram = 0;											//レコードのフレームを初期化する
		TASK_all_init();
		return;
	}
}

void main_computer_start( void )
{
	TASK *ap, *op, *ep;		//親と輪っかと地球
	ap = TASK_start_MODEL( main_computer_exec, MAIN_COMP_GROUP, MODEL_COMPUTER, TEX_COMPUTER, "機械" );		//メインの機械
	ap->grp_mode = MAIN_BILL_GRP_FLAG;
	ap->ID = OBJ_MAX - 2;						//メインビルの一つ前に設定しておく
	object_sphire_set( ap->ID, 0, 3024.0f, 0.0f, 1024.0f );
	object_sphire_set( ap->ID, 1, 1024.0f, 1024.0f, 2048.0f );
	object_sphire_set( ap->ID, 2, 1024.0f, 2048.0f, 3072.0f );
	ap->pos[ X ] = 25000.0f;
	ap->pos[ Y ] = GROUND;
	ap->pos[ Z ] = 25500.0f;
	ap->HP = 1;
	ap->pri = OBJECT_PRI * WP;
	common_ambient( ap );
	
	op = TASK_start_MODEL( sub_parts_exec, MAIN_COMP_GROUP, MODEL_SUB_PARTS, TEX_COMPUTER, "輪っか" );		//
	op->grp_mode = MAIN_BILL_GRP_FLAG;
	op->ang_spd[Y] = -0xc0;
	op->pos[ X ] = ap->pos[X];
	op->pos[ Y ] = ap->pos[Y] + 600.0f;
	op->pos[ Z ] = ap->pos[Z];
	common_ambient( op );
	//op->pri = -1 * WP;

	op = TASK_start_MODEL( sub_parts_exec, MAIN_COMP_GROUP, MODEL_SUB_PARTS, TEX_COMPUTER, "輪っか" );		//
	op->grp_mode = MAIN_BILL_GRP_FLAG;
	op->ang_spd[Y] = 0xc0;
	op->pos[ X ] = ap->pos[X];
	op->pos[ Y ] = ap->pos[Y] + 1400.0f;
	op->pos[ Z ] = ap->pos[Z];
	op->pri = -1 * WP;
	common_ambient( op );

	ep = TASK_start_MODEL( earth_exec, MAIN_COMP_GROUP, MODEL_EARTH, TEX_EARTH, "地球" );		//地球
	ep->grp_mode = TEST_ZBUFFER | WRITE_ZBUFFER  | NO_SHADOW	 | USE_LIGHTING;
	if( clear_flag != 0 )
		ep->tex_no = TEX_EARTH_BREAK;

	ep->pos[ X ] = ap->pos[ X ];
	ep->pos[ Y ] = 5000.0f;
	ep->pos[ Z ] = ap->pos[ X ];
	ep->ambient[0] = 1.0f;
	ep->ambient[1] = 1.0f;
	ep->ambient[2] = 1.0f;
	ep->ambient[3] = 1.0f;
	//ep->emissive[0] = 5.0f;
	//ep->emissive[1] = 5.0f;
	//ep->emissive[2] = 5.0f;
	ep->diffuse[0]  = 0x40;
	ep->sphire = 1524.0f;
}


//-----------------------------------------------------------------------------------------------------------------------
//ハイスコアを表示するスコアボードのタスク
//-----------------------------------------------------------------------------------------------------------------------
void score_board_drawfunc( TASK *ap )
{
	if( ap->pos[ Z ] > jiki->pos[ Z ] || ap->parent->HP > 0 )
	{
		TASK spr;
		SINT32 i;
		SINT8 str[ 16 ];

		//文字列に変更する
		sprintf( str, "%8d", hi_score ); 						//メモリの中に保存する

		TASK_init_member_pointer( &spr );						//ここでsprを初期化
		spr.grp_mode = ap->grp_mode | FLIP_LR;
		spr.pos[ X ] = ap->pos[ X ];							//座標の設定
		spr.pos[ Y ] = ap->pos[ Y ];							//座標の設定
		spr.pos[ Z ] = ap->pos[ Z ];							//座標の設定
		spr.scale[ X ] = ap->parent->scale[ X ];				//大きさを設定
		spr.scale[ Y ] = spr.scale[ X ];						//大きさを設定
		spr.tex_no = TEX_UI_FONT;								//テクスチャナンバーは自分のヤツ
		spr.uv_rect = number_rect;								//数字の矩形をいれる
		spr.pri = ( OBJECT_PRI ) * WP;
		//spr.pri = UI_PRI * WP;								//描画優先度を設定

		for( i = 0; i < 8 ; i++ )								//表示したい桁分を回す
		{
			if( str[ i ] >= '0' && str[ i ] <= '9' )			//スコアのくらいが0～9なら
			{
				spr.base_color[ 0 ][ 1 ] = 0xff;					//R( はっきりとスコアを出す )
				spr.base_color[ 0 ][ 2 ] = 0xff;					//G( はっきりとスコアを出す )
				spr.base_color[ 0 ][ 3 ] = 0xff;					//B( はっきりとスコアを出す )
				spr.anime_no = str[ i ] - '0';					//文字列の0から文字列の0を引くと数字の0になる
			}

			else
			{
				spr.base_color[ 0 ][ 1 ] = 120;						//R( すこし暗くする )
				spr.base_color[ 0 ][ 2 ] = 120;						//G( すこし暗くする )
				spr.base_color[ 0 ][ 3 ] = 120;						//B( すこし暗くする )
				spr.anime_no = 0;								//計算結果は0
			}

			SOZ_sprite_draw( &spr );							//ここで描画する
			spr.pos[ X ] += (ap->fwork1[ X ] * spr.scale[ X ]);		//横にずらす
		}
	}
}

void hiscore_board_exec( TASK *ap )
{

}

void score_board_exec( TASK *ap )
{
	if( ap->HP <= 0 )
	{
		TASK_end_group( SHOT_GROUP );
		TASK_end( ap->child[0] );
		TASK_end( ap );
	}
}

void score_board_start( FLOAT x, FLOAT y, FLOAT z )
{
	TASK *ap, *actp;
	ap = TASK_start_MODEL( score_board_exec, OBJECT_GROUP, MODEL_BOATD, TEX_SCREEN_MEKA, "スコアボード" );
	ap->ID = OBJ_MAX - 3;						//メインコンピューターの一つ前に設定しておく
	object_sphire_set( ap->ID, 0, 512.0f, 0.0f, 700.0f );
	ap->grp_mode = TEST_ZBUFFER | WRITE_ZBUFFER | USE_LIGHTING;
	ap->pos[X] = x;
	ap->pos[Y] = y;
	ap->pos[Z] = z;
	ap->scale[X] = 4.0f;
	ap->scale[Y] = ap->scale[X];
	ap->HP = 500;
	ap->pri = OBJECT_PRI * WP;
	common_ambient( ap );

	/*
	actp = TASK_start_DRAWFUNC( hiscore_board_exec, score_board_drawfunc, NO_GROUP, "ボードにハイスコアを表示" );
	actp->grp_mode |= USE_3DPOS;
	
	actp->fwork1[Z] = 15.0f;

	actp->pos[X] = ap->pos[X];
	actp->pos[Y] = ap->pos[Y];
	actp->pos[Z] = ap->pos[Z] + actp->fwork1[Z];
	actp->parent = ap;
	*/

	actp = TASK_start_DRAWFUNC( hiscore_board_exec, score_board_drawfunc, NO_GROUP, "ボードにハイスコアを表示" );
	actp->grp_mode = USE_3DPOS;
	
	actp->fwork1[Z] = -85.0f;
	actp->fwork1[X] = 64.0f;

	actp->pos[X] = ap->pos[X] - 850.0f;
	actp->pos[Y] = ap->pos[Y];
	actp->pos[Z] = ap->pos[Z] + actp->fwork1[Z];
	actp->pri = 10 * WP;
	ap->child[0] = actp;
	actp->parent = ap;
	
}



