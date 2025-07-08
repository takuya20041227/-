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
#include    "include.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
//キーを押したらタイトルに戻る
//------------------------------------------------------------------------------------------------------------------------------------------------------
void title_return_exce( TASK *ap )
{
	SINT32 i;
	bool flag;										//何かを押されたら0以外になる
	flag = 0;										//初期化

	if( SOZ_Inkey_TRG( DIK_Z ) != 0 )				//キーが押されていたら
		flag = TRUE;								//1になる

	for( i = 0; i < 3; i++ )						//右クリック, 左クリック, ホイールの押し込みを感知
		if( SOZ_Mouse_Button( i ) == 1 )			//マウスが押されたら
			flag = TRUE;							//1になる

	if( flag == TRUE )								//フラグが立っていたら
	{
		if( game_type == GAME_CLERE + 1 )						//ゲームタイプがクリア画面なら
		{
			if( score > hi_score )					//スコアがハイスコアを超えていたら
			{
				hi_score = score;					//ハイスコアを更新
				select_and_page_write( "data/hi_score_data.bn", &hi_score );	//ハイスコアを保存
			}
				game_type = TITLE_SCENE;								//タイトルに戻る
				TASK_all_init();							//タスクを全て消す
				return;										//
		}
		else if( game_type == GAME_OVER + 1 )
		{
			shut_down_start();
			TASK_end( ap );
			return;
		}
	}
}

void title_return_start( SINT32 delay )
{
	TASK *ap;
	ap = TASK_start( title_return_exce, MANE_GROUP, "タイトルに戻す" );
	ap->delay = delay;
}