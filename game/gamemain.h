//------------------------------------------------------------------------------------------------------------------------------------------------------
//                systemOZ Ver3.5
//				サイバーアニマル！　ガーディアンズ！
//						programed by R-TOHYA
//------------------------------------------------------------------------------------------------------------------------------------------------------

#undef CHAR_MAX



#define	GRP_LOWEND			//ローエンド、　スマホ切り替え用
#define	GRP_LOW_LEVEL			0			//ローエンド スマホ
#define	GRP_MIDDLE_LEVEL		1			//ミドルレベル
#define	GRP_HIGH_LEVEL			2			//ハイレベル



//現在の最後のステージ
#define	LAST_STAGE		20 

//マップの大きさ
#define	MAPMAX_X		7
#define	MAPMAX_Y		32

#define	CHAR_MAX				16
#define	STAGE_MAX				260
#define	MANABERU_KUN_START		38					//まなべるくん使用可能ステージ


//#define	ITEM_USE_START_STAGE	28				//必要なくなった。とてもいいこと。


#define	GAMELEVEL_NORMAL			0
#define	GAMELEVEL_TUTORIAL			1


#define	CONTROL_TYPE_DIRECT			0				//押したら反応する
#define	CONTROL_TYPE_HOLD			1				//押してキャラクタを


//時間帯や天候の設定（会話シーンで行う）
#define	CONDITION_AFTERNOON		0
#define	CONDITION_EVENING		1
#define	CONDITION_NIGHT			2
#define	CONDITION_RAIN			3

#define	CONDITION_FACT_GRAY		10
#define	CONDITION_FACT_BLUE		11
#define	CONDITION_FACT_GREEN	12
#define	CONDITION_FACT_BLOWN	13
#define	CONDITION_FACT_RED		14

#define	CONDITION_LAKE				15
#define	CONDITION_LAKE_SUNSET		16
#define	CONDITION_LAKE_NIGHT		17

#define	CONDITION_MOUNTAIN			18
#define	CONDITION_MOUNTAIN_SUNSET	19
#define	CONDITION_MOUNTAIN_NIGHT	20

#define	CONDITION_SANDLAND			21
#define	CONDITION_SANDLAND_SUNSET	22
#define	CONDITION_SANDLAND_NIGHT	23

#define	CONDITION_SANDTOWN			24
#define	CONDITION_SANDTOWN_SUNSET	25
#define	CONDITION_SANDTOWN_NIGHT	26

#define	CONDITION_TERRY				27
#define	CONDITION_TERRY_SUNSET		28
#define	CONDITION_TERRY_NIGHT		29

#define	CONDITION_TOWN001			30




#define	NAKAMA_UNKNOWN			0
#define	NAKAMA_BREAKTIME		-1
#define	NAKAMA_IN				1





extern	SINT32 platform_PC;
extern	SINT8	name_box[][16];
extern	SINT16	name_string_box[32][8];
extern	SINT32	mouse_x, mouse_y, mouse_old_x, mouse_old_y;
extern	SINT32	select_char;
extern	SINT32	now_stage;
extern	SINT32	max_nakama_num, nakama_num;

extern	SINT32 get_item_number, get_item_id;
extern	SINT32 game_lose_clear;

extern	ANIME_TABLE back_button_anime[];
extern	PARTS_RECT gameinter_whitechip_rect[];

extern	SINT32	now_stage;

//extern	SINT32	now_condition;




//------------------------------------------------------------------------------------------------------------------------------------------------------
//各ステージのスコアデータ
//------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{	SINT32 hiscore_stage;
	SINT32 weapon_data[63];
} SCORE_DATA;



//------------------------------------------------------------------------------------------------------------------------------------------------------
//ジュエルのパラメータ
//------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
	SINT32 exp;				//経験値	
	SINT16 atk;
	SINT16 def;
	SINT16 hp;
	SINT16 spd;
	UINT16 skill;
	SINT8 type;
	SINT8 level_max;		
	UINT8 modify;			//改造回数
	SINT8 char_id;			//誰の宝石
	SINT8 drivers;			//トライバーズジュエル？
} JEWEL_PARAM;


//------------------------------------------------------------------------------------------------------------------------------------------------------
//セーブデータ
//------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
	SINT8	savedata_ver;				//セーブデータバージョン
	SINT8	use_flag;					//このセーブデータが使用されているかどうかを示す。
	SINT8	now_condition;
	SINT8	game_level;					//0:ノーマル 1:イージー
	SINT8	nakama[ CHAR_MAX ];			//仲間になったか。
	SINT8	select_weapon[ CHAR_MAX ];					//現在選択している武器
	SINT8	shot_level[CHAR_MAX][2];
	SINT8	hp_level[CHAR_MAX];
	SINT8	skill_level[CHAR_MAX];
	SINT8	surport_level[CHAR_MAX];
	SINT8	name_off[ CHAR_MAX ];		//ステータス画面やジュエル画面で名前を伏せる
	SINT8	talk_end[STAGE_MAX][4];		//キャラ戦闘途中の会話を追加	3 -> 4	に変更
	SINT8	stage_clear_flag[STAGE_MAX];
	SINT16	item[ 16 ];					//16種類のアイテムの取得数
	SINT16	stage_exp[CHAR_MAX][STAGE_MAX];				//稼いだ経験値。上位2ビットに階級 を入れる
	SINT16	last_play_stage;
	SINT32	exp[CHAR_MAX];
	SINT32	last_battle_use;			//最後に遊んだストーリーステージのキャラ（ビット管理）
	SINT32	buster_count_of_jewel;		//倒したネットバイキンの数、ジュエルゲットごとにリセット。
	SINT32	buster_backup;				//倒したネットバイキンのバックアップ
	SINT32	blast_level;
	SINT32	blast_count;
	SINT32	manabel_power;				//まなべるくん使用エネルギー
	FLOAT	leveling_level;				//レベリングレベル 0.0 ～ -0.25
	SINT32	controler_type;				//操作タイプ
	SINT32	equip_jewel[ CHAR_MAX ][ 2 ];					//装備している宝石
	JEWEL_PARAM jewel[ 3 ][ 1024 ];		//持っている宝石（オフェンス、ディフェンス、ドライバーズ）				
	SINT8	item_get[ 16 ];				//アイテムを取得したことがあるか？
	SINT32  hensei_music;				//編成画面で指定された音楽のナンバー
	SINT8	dummy[ 1024 ];

} SAVEDATA;



typedef struct
{
	SINT32 char_id;
	FLOAT x;
	FLOAT y;
	SINT32 select_weapon;
} PLAYER_SETXY;




//------------------------------------------------------------------------------------------------------------------------------------------------------
// 武器ID
//------------------------------------------------------------------------------------------------------------------------------------------------------

//デジタル
#define	SHOT_DIGITAL_STRAIGHT		0		//真っ直ぐ進む
#define	SHOT_DIGITAL_CROSSSHOT		1		//ヘルファイアーのようなクロス状
#define	SHOT_DIGITAL_WITH_BOMB		2		//当たり判定が広がる


//セキュア
#define	SHOT_SECURE_3WAY			3		//３WAY
#define	SHOT_SECURE_5WAY			4		//
#define	SHOT_SECURE_2WAY			5		//

//アドミン
#define	SHOT_ADMIN_SLANT			6		//地上キャラの斜め上攻撃
#define	SHOT_ADMIN_TOP				7		//地上キャラの斜め上攻撃２WAY
#define	SHOT_ADMIN_FRONT			8		//地上キャラの斜め上攻撃２WAY（角度低い）

//センサー
#define	SHOT_SENSER_SLANT		9
#define	SHOT_SENSER_TOP			10
#define	SHOT_SENSER_FRONT		11

//アイピー
#define	SHOT_IP_WAVE			12
#define	SHOT_IP_LASER			13
#define	SHOT_IP_3				14


//エポック
#define	SHOT_EPOC_ROCK				15
#define	SHOT_EPOC_ROCK_CLASH		16
#define	SHOT_EPOC_ROCK_BOUND		17

//パッチ
#define	SHOT_PATCH_1			18
#define	SHOT_PATCH_2			19
#define	SHOT_PATCH_3			20

//コネクト
#define	SHOT_CONNECT_1				21	//36
#define	SHOT_CONNECT_2				22	//37
#define	SHOT_CONNECT_3				23	//38


//テクノ
#define	SHOT_TECHNO_1				24
#define	SHOT_TECHNO_2				25
#define	SHOT_TECHNO_3				26


//リテラ
#define	SHOT_LITERA_1				27	//33
#define	SHOT_LITERA_2				28	//34
#define	SHOT_LITERA_3				29	//35

//パケット
#define	SHOT_PACKET_1		30
#define	SHOT_PACKET_2		31
#define	SHOT_PACKET_3		32



//キー
#define	SHOT_KEY_1					33
#define	SHOT_KEY_2					34
#define	SHOT_KEY_3					35


//シール
#define	SHOT_SHEAL_THUNDER		36
#define	SHOT_SHEAL_FIRE			37
#define	SHOT_SHEAL_BOMB			38


//スクル
#define	SHOT_SQUL_THUNDER		39
#define	SHOT_SQUL_FIRE			40
#define	SHOT_SQUL_BOMB			41



//インフォ
#define	SHOT_INFO_1		45
#define	SHOT_INFO_2		46
#define	SHOT_INFO_3		47







//------------------------------------------------------------------------------------------------------------------------------------------------------
// アイテムの定義
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define ITEM_AMEDAMA				0
#define ITEM_BIG_AMEDAMA			1
#define ITEM_RESETER				2












//------------------------------------------------------------------------------------------------------------------------------------------------------
// 地面の高さ
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define	GROUND_HEIGHT	1000.0f				//地面の高さ








//------------------------------------------------------------------------------------------------------------------------------------------------------
// 各キャラクタのパラメタ
//------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
	SINT32	hp;				//体力
	FLOAT	hp_mul;			//レベルによって増加するHPの加速度増加率
//	SINT32	hp_easy;		//イージーモードHP
	SINT32	air;			//空中判定
	FLOAT	speed;			//移動スピード倍率
//	ANGLE	a_speed;		//回転周期速度
//	SINT32	sphire_type;	//スフィアのタイプ
} MYCHAR_PARAM;




//------------------------------------------------------------------------------------------------------------------------------------------------------
// セーブデーターの数
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define	SAVEDATA_MAX			10








//ゲームの進行状況
#define	BATTLE_INIT					0
#define	BATTLE_INIT2				10
#define	BATTLE_START_STORY			50
#define	BATTLE_RINGSYSTEM			100
#define	BATTLE_RINGSYSTEM_NOUSE		190
#define	BATTLE_INGAME				200
#define	BATTLE_INGAME_CORE			300
#define	BATTLE_INGAME_CORE_LIMIT	499
#define	BATTLE_DEMO_OUT				500
#define	BATTLE_GAMEOVER				1000
#define	BATTLE_GAMEOVER2			1200
#define	BATTLE_HINT_DISP			1400

#define	BATTLE_GAMECLEAR			8000
#define	BATTLE_FORCED_END			8900

#define	BATTLE_EXITGAME				9000







//------------------------------------------------------------------------------------------------------------------------------------------------------
//ゲーム進行度
//------------------------------------------------------------------------------------------------------------------------------------------------------
extern	SINT32	game_type, game_type2, game_type3, game_mode, game_type_old, invincible;	
extern	SINT32	score, bonus, left_bomb, left_myship;
extern	SINT32	core_hp;				//コアHP
extern	SINT32	stage_exp, stage_avg_exp, buster_exp, guard_exp, core_hp_start; 
extern	SINT32	buster_avg_exp, guard_avg_exp; 
extern	SINT32	buster_parsent, buster_all_parsent;


extern	TASK	*myship[16];
extern	SINT32	battle_play_type;
extern	SINT32 demonstration;					//デモプレイかどうか
extern	SINT32 game_mouse_button, game_mouse_button2, game_mouse_button3, game_mouse_button4;

extern	SINT32 stage_of_enemy;
extern	SINT32 x7_buster;
extern	SINT32 x5_buster;
extern	SINT32 x3_buster;
extern	SINT32 x2_buster;
extern	SINT32 x1_buster;

extern	SINT32 enemy_shot_pow;

extern	SINT32 to_map_flag;				//0 通常 1:クリア後 2:オープニング後
extern	SINT32	game_exec_timer;
extern	SINT32	pick_now;


//------------------------------------------------------------------------------------------------------------------------------------------------------
//プロトタイプ宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------

extern	SAVEDATA savedata[ SAVEDATA_MAX ];
extern	SINT32   save_id;
extern	PLAYER_SETXY char_set_data[16][ 256 ][ 16 ];

extern	void GAMEMAIN_Routine( void );
extern	void GAMEMAIN_mouse_cursor( void );
extern	SINT32 GAMEMAIN_make_core_hp( void );
extern	void MOUSE_pos_recode_start( void );
extern	void GAMEMAIN_enemy_lib_mode( void );
extern	SINT32 GRPLEVEL_check( void );
extern	void BATTLE_goback_button( SINT32 x, SINT32 y, SINT32 prio, SINT32 group, SINT32 id );
extern	void GAMEMAIN_tutorial_make_savedata( void );


