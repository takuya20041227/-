//------------------------------------------------------------------------------------------------------------------------------------------------------
//                systemOZ Ver3
//			ゲームメインプログラム
//						programed by TEAM_TAKUYA
//------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef WINDOWS_PC
#include    "../../../libs/systemOZ_v4/soz.h"
#else
#include    "C:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/town_break/src/game/game_include.h"
#include    "include.h"


//-----------------------------------------------------------------------------------------------------------------------
//ゲーム本編で使うテクスチャーの設定
//-----------------------------------------------------------------------------------------------------------------------
void tex_game_load( void )
{
	SOZ_load_texture( TEX_GROUND,		"grp/map_grp/ground" );					//地面
	SOZ_load_texture( TEX_BILL,			"grp/map_grp/bill" );					//ビル
	SOZ_load_texture( TEX_SKY,			"grp/map_grp/sora" );					//空
	SOZ_load_texture( TEX_CAR,			"grp/car/car" );						//緑の車
	SOZ_load_texture( TEX_CAR_B,		"grp/car/car_b" );						//黒の車
	SOZ_load_texture( TEX_CAR_W,		"grp/car/car_w" );						//白の車
	SOZ_load_texture( TEX_DEBUG_PARAM,	"grp/debug_param" );					//エディターで使うデバッグフォントが入ってるグラフィック
	SOZ_load_texture( TEX_ROADSTAR_R,	"grp/car/roadster" );					//赤の車
	SOZ_load_texture( TEX_ROADSTAR_B,	"grp/car/roadster_b" );					//黒の車
	SOZ_load_texture( TEX_ROADSTAR_W,	"grp/car/roadster_w" );					//黒の車
	SOZ_load_texture( TEX_TOWER,		"grp/map_grp/tower" );					//謎のタワー
	SOZ_load_texture( TEX_TENTO,		"grp/tento" );							//テント
	SOZ_load_texture( TEX_CAR_EFE,		"grp/car/tiya" );						//タイヤ
	SOZ_load_texture( TEX_WOOD,			"grp/map_grp/wood" );
	SOZ_load_texture( TEX_BONITO,		"grp/map_grp/bonito" );
	SOZ_load_texture( TEX_WOOD_EFE,		"grp/break_effect/wood/wood_efe" );
	SOZ_load_texture( TEX_GLAS,			"grp/break_effect/bill/glas_efe" );		//ガラスの破片
	SOZ_load_texture( TEX_SCHOOL,		"grp/map_grp/school" );					//学校のグラフィック( 3D用 )
	SOZ_load_texture( TEX_LOGO_HOUSE,	"grp/map_grp/house" );					//タイトルロゴのマンション
	SOZ_load_texture( TEX_BET,			"grp/map_grp/bet" );					//ふとんとベット
	SOZ_load_texture( TEX_TANSU,		"grp/map_grp/tansu" );					//タンス
	SOZ_load_texture( TEX_PARKING,		"grp/map_grp/parking" );				//駐車場
	SOZ_load_texture( TEX_CAT_MOUNTEN,	"grp/map_grp/cat/cat_mountain" );
	SOZ_load_texture( TEX_CAT_TYA,		"grp/map_grp/cat/cat_tya" );			//茶色のネコ
	SOZ_load_texture( TEX_CAT_GRY,		"grp/map_grp/cat/cat_gry" );			//灰色のネコ re
	SOZ_load_texture( TEX_CAT_PEL,		"grp/map_grp/cat/cat_pel" );			//ペールのネコ
	SOZ_load_texture( TEX_MISSILE,		"grp/missile" );						//ペールのネコ
}


//-----------------------------------------------------------------------------------------------------------------------
//ゲーム本編で使うモデルの設定
//-----------------------------------------------------------------------------------------------------------------------
void model_game_load( void )
{
	SOZ_load_model( MODEL_MAIN_BILL,	"grp/smd/bill" );
	SOZ_load_model( MODEL_SKY,			"grp/smd/sky" );	
	SOZ_load_model( MODEL_CAR,			"grp/smd/car" );
	SOZ_load_model( MODEL_SUB_BILL,		"grp/smd/mobu_bill" );
	SOZ_load_model( MODEL_ROADSTAR,		"grp/smd/roadster" );
	SOZ_load_model( MODEL_TOWER,		"grp/smd/tower" );
	SOZ_load_model( MODEL_TENTO,		"grp/smd/tento" );
	SOZ_load_model( MODEL_BLEAK_BILL,	"grp/break_smd/break_bill" );
	SOZ_load_model( MODEL_CAR_EFE,		"grp/smd/taiya" );							//タイヤ
	SOZ_load_model( MODEL_BILL_EFE,		"grp/break_effect/bill/bill_effect" );
	SOZ_load_model( MODEL_WOOD,			"grp/smd/wood" );
	SOZ_load_model( MODEL_BONITO,		"grp/smd/bonito" );
	SOZ_load_model( MODEL_WOOD_EFE,		"grp/break_effect/wood/wood_efe" );
	SOZ_load_model( MODEL_SCHOOL,		"grp/smd/school" );							//学校
	SOZ_load_model( MODEL_SCHOOL_CHAIR,	"grp/break_effect/school/school_chair" );	//学校のイス
	SOZ_load_model( MODEL_SCHOOL_TABLE,	"grp/break_effect/school/school_table" );	//学校の机
	SOZ_load_model( MODEL_BREAK_SCHOOL, "grp/break_effect/school/break_school" );	//壊れた学校
	SOZ_load_model( MODEL_LOGO_HOUSE,	"grp/smd/logo_house" );						//タイトルロゴのマンション
	SOZ_load_model( MODEL_BET,			"grp/break_effect/logo_house/bet" );		//ベット
	SOZ_load_model( MODEL_HUTON,		"grp/break_effect/logo_house/huton" );		//ふとん
	SOZ_load_model( MODEL_TANSU,		"grp/break_effect/logo_house/tansu" );		//タンス
	SOZ_load_model( MODEL_PARKING,		"grp/smd/parking" );						//駐車場
	SOZ_load_model( MODEL_CAT_MOUNTEN,	"grp/smd/cat/cat_mountain" );				//ネコ山
	SOZ_load_model( MODEL_CAT,			"grp/smd/cat/cat" );						//ネコのモデル
	SOZ_load_model( MODEL_MISSILE,		"grp/smd/missile" );						//ペールのネコ
}


//-----------------------------------------------------------------------------------------------------------------------
//タイトルで使うテクスチャーの設定
//-----------------------------------------------------------------------------------------------------------------------
void tex_title_load( void )
{
	SOZ_load_texture( TEX_JIKI,			"grp/jiki/ufo" );					//UFOの自機
	SOZ_load_texture( TEX_BEAM,			"grp/bram" );						//ビーム
	SOZ_load_texture( TEX_UFO_ROOM,		"grp/ufo_room" );					//UFOの中( タイトルでつかう )
	SOZ_load_texture( TEX_COMPUTER,		"grp/ufo_room/main_computer" );		//UFOの中( タイトルでつかう )
	SOZ_load_texture( TEX_EARTH,		"grp/ufo_room/earth" );				//地球
	SOZ_load_texture( TEX_HAND,			"grp/hand" );						//手
	SOZ_load_texture( TEX_UFO_GROUND,	"grp/ufo_room/ufo_ground" );		//タイトルの地面
	SOZ_load_texture( TEX_SCREEN_MEKA,	"grp/ufo_room/ufo_meka" );			//モニター付き機械
	SOZ_load_texture( TEX_BUTTON_MEKA,	"grp/ufo_room/ufo_button" );		//ボタン付きの機械
	SOZ_load_texture( TEX_TITLE,		"grp/ufo_room/town_break_title" );	//タイトルロゴ
	SOZ_load_texture( TEX_EARTH_BREAK,	"grp/ufo_room/earth_break" );		//ゲームクリア後の地球( 荒廃 )
	SOZ_load_texture( TEX_OBJECT_ICON,	"grp/ui/object_icon" );				//オブジェクトのアイコン
	SOZ_load_texture( TEX_UI_FONT,		"grp/ui/ui_font" );					//操作説明やルール説明が書かれてる
	SOZ_load_texture( TEX_BOM,			"grp/bomb" );						//爆発
	SOZ_load_texture( TEX_HERI,			"grp/heri" );						//ヘリのグラフィック
}


//-----------------------------------------------------------------------------------------------------------------------
//タイトルで使うモデルの設定
//-----------------------------------------------------------------------------------------------------------------------
void model_title_load( void )
{
	SOZ_load_model( MODEL_JIKI,			"grp/smd/ufo" );					//自機
	SOZ_load_model( MODEL_BEAM,			"grp/smd/Beam" );					//ビーム
	SOZ_load_model( MODEL_UFO_ROOM,		"grp/smd/ufo_room" );				//UFOの中( タイトルでつかう )
	SOZ_load_model( MODEL_HAND,			"grp/smd/hand" );					//手
	SOZ_load_model( MODEL_COMPUTER,		"grp/smd/main_computer" );			//ゲームスタートするときに撃つ大きな機械
	SOZ_load_model( MODEL_SUB_PARTS,	"grp/smd/sub_parts" );				//
	SOZ_load_model( MODEL_EARTH,		"grp/smd/earth" );					//
	SOZ_load_model( MODEL_SCREEN_MEKA,	"grp/smd/meka2" );					//
	SOZ_load_model( MODEL_BUTTON_MEKA,	"grp/smd/meka1" );					//
	SOZ_load_model( MODEL_HERI,			"grp/smd/heri/heri" );				//ヘリ本体のモデル
	SOZ_load_model( MODEL_PROPELLER,	"grp/smd/heri/propeller" );			//ヘリについてるプロペラのモデル
	SOZ_load_model( MODEL_HAND_EFE,		"grp/smd/hand_efe" );				//手のエフェクトモデル
	SOZ_load_model( MODEL_BOATD,		"grp/smd/score_board" );			//スコアボード
}


//-----------------------------------------------------------------------------------------------------------------------
//SEのロード
//-----------------------------------------------------------------------------------------------------------------------
void se_load( void )
{
	SOZ_load_se( SE_FISH,				"grp/se/fish_01" );			//水の音
	SOZ_load_se( SE_KLAXON_1,			"grp/se/carhorn_01" );		//水の音
	SOZ_load_se( SE_KLAXON_2,			"grp/se/carhorn_02" );		//水の音
	SOZ_load_se( SE_BILL_BREAK,			"grp/se/bill_break_01" );	//水の音
	SOZ_load_se( SE_PROPELLER,			"grp/se/buranko" );			//ヘリの回る音
	SOZ_load_se( SE_HERI,				"grp/se/heri" );			//ヘリの回る音
}




//-----------------------ロードされてるもので使っていないものを消す-------------------------//
// ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ //

//----------------------------------------------------------------------------------------------------
//読み込んでたテクスチャーで使っていないものを消す
//----------------------------------------------------------------------------------------------------
void tex_title_reset( void )
{
	SOZ_release_texture( TEX_EARTH );								//地球
	SOZ_release_texture( TEX_EARTH_BREAK );							//荒廃した地球
	SOZ_release_texture( TEX_UFO_GROUND );							//タイトルの地面
	SOZ_release_texture( TEX_SCREEN_MEKA );
	SOZ_release_texture( TEX_BUTTON_MEKA );
	SOZ_release_texture( TEX_UFO_ROOM );
	SOZ_release_texture( TEX_COMPUTER );
	SOZ_release_texture( TEX_TITLE );								//
	//SOZ_release_texture(  );
}


//----------------------------------------------------------------------------------------------------
//読み込んでたモデルで使っていないものを消す
//----------------------------------------------------------------------------------------------------
void model_title_reset( void )
{
	SOZ_MODEL_release( MODEL_EARTH );
	SOZ_MODEL_release( MODEL_SCREEN_MEKA );
	SOZ_MODEL_release( MODEL_BUTTON_MEKA );
	SOZ_MODEL_release( TEX_UFO_ROOM );
	SOZ_MODEL_release( TEX_COMPUTER );
	//SOZ_MODEL_release(  );
}


//----------------------------------------------------------------------------------------------------
//読み込んでたテクスチャーで使っていないものを消す( ゲーム本編 )
//----------------------------------------------------------------------------------------------------
void tex_game_reset( void )
{
	SOZ_release_texture( TEX_GROUND			);				//地面
	SOZ_release_texture( TEX_BILL			);				//ビル
	SOZ_release_texture( TEX_SKY			);				//空
	SOZ_release_texture( TEX_CAR			);				//緑の車
	SOZ_release_texture( TEX_CAR_B			);				//黒の車
	SOZ_release_texture( TEX_CAR_W			);				//白の車
	SOZ_release_texture( TEX_HAND			);				//爆発
	SOZ_release_texture( TEX_DEBUG_PARAM	);				//エディターで使うデバッグフォントが入ってるグラフィック
	SOZ_release_texture( TEX_ROADSTAR_R		);				//赤の車
	SOZ_release_texture( TEX_ROADSTAR_B		);				//黒の車
	SOZ_release_texture( TEX_ROADSTAR_W		);				//黒の車
	SOZ_release_texture( TEX_TOWER			);				//謎のタワー
	SOZ_release_texture( TEX_TENTO			);				//テント
	SOZ_release_texture( TEX_GLAS			);				//ガラスの破片
}


//----------------------------------------------------------------------------------------------------
//読み込んでたモデルで使っていないものを消す( ゲーム本編 )
//----------------------------------------------------------------------------------------------------
void model_game_reset( void )
{
	SOZ_MODEL_release( MODEL_MAIN_BILL  );
	SOZ_MODEL_release( MODEL_SKY		);
	SOZ_MODEL_release( MODEL_CAR		);
	SOZ_MODEL_release( MODEL_HAND		);
	SOZ_MODEL_release( MODEL_SUB_BILL	);
	SOZ_MODEL_release( MODEL_ROADSTAR	);
	SOZ_MODEL_release( MODEL_TOWER	    );
	SOZ_MODEL_release( MODEL_TENTO	    );
	SOZ_MODEL_release( MODEL_BLEAK_BILL );
	//SOZ_MODEL_release(  );
}