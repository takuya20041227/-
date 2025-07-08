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
//タイトルからチュートリアルに飛ばす
//------------------------------------------------------------------------------------------------------------------------------------------------------
void tutorial_skep_mane_exec(TASK *ap)
{
	SINT32 i, index;
    index = 0;
    if( SOZ_Inkey_TRG( DIK_Z ) != 0 )
		    index++;
    for( i = 0; i < 3; i++ )
        if( SOZ_Mouse_Button( i ) == 1 )
            index++;

    if( index != 0 )
    {
        game_type = TUTORIAL;
        TASK_all_init();
        return;
    }
}

void tutorial_skep_mane_start( void )
{
	TASK *ap;
	ap = TASK_start( tutorial_skep_mane_exec, MANE_GROUP, "チュートリアルに飛ばす" );
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//タイトルからゲームに行くための説明文を出す
//------------------------------------------------------------------------------------------------------------------------------------------------------
void game_start_purpose_exec( TASK *ap )
{
	alpha_chenge( ap, 0xff, 0xa0 );														//透明度を維持る
}

void game_start_child_exec( TASK *ap )
{
	ap->base_color[0][0] = ap->parent->base_color[0][0];								//親の透明度を代入させる
}

void game_start_purpose_start( void )
{
	TASK *ap, *actp;
	ap = TASK_start_GRP( game_start_purpose_exec, UI_GROUP, TEX_UI_FONT, title_proposal_rect, 0, "攻撃をするオブジェクトの説明" );
	ap->pos[ X ] = WINDOW_WIDTH_HALF;													//
	ap->pos[ Y ] = WINDOW_HEIGHT - 300.0f;												//
	ap->pri = UI_PRI * WP;																//描画優先度
	ap->scale[X] = 1.5f;
	ap->scale[Y] = ap->scale[X];

	actp = TASK_start_GRP( game_start_purpose_exec, UI_GROUP, TEX_UI_FONT, title_proposal_rect, 1, "ゲームスタートの文字" );
	actp->pos[ X ] = WINDOW_WIDTH_HALF;													//
	actp->pos[ Y ] = ap->pos[Y] + 100.0f;												//攻撃をするオブジェクトの説明の下に来るくらいの高さに変える
	actp->scale[X] = ap->scale[X];
	actp->scale[Y] = actp->scale[X];
	actp->parent   = ap;
	ap->child[ 0 ] = actp;
	actp->pri = UI_PRI * WP;															//描画優先度
}


