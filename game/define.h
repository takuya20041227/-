//-----------------------------------------------------------------------------------------------------------------------
//全体が使えるdefine
//-----------------------------------------------------------------------------------------------------------------------
#define	GROUND				-500
#define	ON					1
#define	OFF					0
#define	RESET				0
#define	WINDOW_WIDTH_HALF	( WINDOW_WIDTH  / 2 )
#define	WINDOW_HEIGHT_HALF	( WINDOW_HEIGHT / 2 )
#define	WINDOW_WIDTH_QUARTER	( WINDOW_WIDTH  / 4 )
#define	WINDOW_HEIGHT_QUARTER	( WINDOW_HEIGHT / 4 )
#define	DEFAULT_ARGUMENT	FLOAT x, FLOAT y, FLOAT z, FLOAT vec_x, FLOAT vec_y, FLOAT vec_z


//-----------------------------------------------------------------------------------------------------------------------
//時間のデファイン
//-----------------------------------------------------------------------------------------------------------------------
#define	TIME_S			60				//60フレームで1秒
#define	TIME_M			( TIME_S * 60 )	//1分
#define	TIME_H			( TIME_M * 60 )	//1時間


//-----------------------------------------------------------------------------------------------------------------------
//ワークのdefine
//-----------------------------------------------------------------------------------------------------------------------
#define	TIMER			work9[X]	//時間計測
#define	COUNT			work9[Y]	//何かをカウントする
#define	SCENE			work9[Z]	//switch文で使う場面進行のワーク
#define	ID				work9[P]	//識別番号
#define	FLAG			work9[D]	//フラグ

#define	HP				work8[X]	//体力
#define	ATK				work8[Y]	//攻撃力
#define	DEF				work8[Z]	//防御力
#define	GROUP			work8[P]	//グループ
#define	SWITCH			work8[D]	//なにかのスイッチ
#define	SUB_SWITCH		work8[E]	//なにかのスイッチ

//-----------------------------------------------------------------------------------------------------------------------
//ワークのdefine
//-----------------------------------------------------------------------------------------------------------------------
#define	TITLE_SCENE				   5	//タイトル画面
#define	TUTORIAL			  10	//チュートリアル画面
#define	GAME				 100	//ゲーム本編
#define	GAME_CLERE			 110	//ゲームクリア
#define	GAME_OVER			 120	//ゲームオーバー
#define	REPLYE				 500	//リプレイ
#define	GAME_EDITORE		1000	//ゲーム画面のエディター
#define	TUTORIAL_EDITORE	2000	//チュートリアルのエディター


//-----------------------------------------------------------------------------------------------------------------------
//テクスチャーナンバー
//-----------------------------------------------------------------------------------------------------------------------
#define	TEX_GROUND			1		//地面
#define	TEX_BILL			2		//ビル
#define	TEX_SKY				3		//空
#define	TEX_JIKI			4		//UFOの自機
#define	TEX_CAR				5		//緑の車
#define	TEX_CAR_B			6		//黒の車
#define	TEX_CAR_W			7		//白の車
#define	TEX_BEAM			8		//ビーム
#define	TEX_BOM				9		//爆発
#define	TEX_HAND			10		//手の模様
#define	TEX_DEBUG_PARAM		11		//エディターで使うデバッグフォントが入ってるグラフィック
#define	TEX_ROADSTAR_R		12		//なんちゃってロードスター( 赤 )
#define	TEX_ROADSTAR_B		13		//なんちゃってロードスター( 黒 )
#define	TEX_ROADSTAR_W		14		//なんちゃってロードスター( 白 )
#define	TEX_TOWER			15		//謎のタワー
#define	TEX_TENTO			16		//テント
#define	TEX_UFO_ROOM		17		//UFOの中( タイトルでつかう )
#define	TEX_COMPUTER		18		//真ん中に立っている
#define	TEX_EARTH			20		//地球
#define	TEX_TITLE			21		//
#define	TEX_UFO_GROUND		22		//
#define	TEX_SCREEN_MEKA		23		//モニターのみついてる機械
#define	TEX_BUTTON_MEKA		24		//ボタンのついている機械
#define	TEX_CAR_EFE			25		//タイヤ
#define	TEX_BILL_EFE		26		//ビルの瓦礫
#define	TEX_WOOD			29		//木
#define	TEX_BONITO			30		//カツオのオブジェ
#define	TEX_WOOD_EFE		31		//薪
#define	TEX_EARTH_BREAK		32		//地球
#define	TEX_OBJECT_ICON		33		//掴んだオブジェクトのアイコン
#define	TEX_UI_FONT			34		//操作説明やルールの
#define	TEX_GLAS			35		//ガラスの破片
#define	TEX_SCHOOL			36		//学校のグラフィック
#define	TEX_HERI			38		//ヘリのグラフィック
#define	TEX_LOGO_HOUSE		39		//タイトルロゴのマンション
#define	TEX_BET				40		//ベットとふとんのグラフィックが入ってる
#define	TEX_TANSU			41		//タンスのテクスチャー
#define	TEX_PARKING			42		//駐車場
#define	TEX_CAT_MOUNTEN		43		//猫山
#define	TEX_CAT_TYA			44		//茶色のネコ
#define	TEX_CAT_GRY			45		//灰色のネコ
#define	TEX_CAT_PEL			46		//ペールネコ
#define	TEX_MISSILE			47		//ミサイル
#define	TEX_FLOWER			48		//お花たち
#define	TEX_ALIEN_NOMAL		49		//普通のエイリアン
#define	TEX_ALIEN_SURPRISE	50		//驚いてるエイリアン
#define	TEX_ALIEN_SMILE		51		//笑顔のエイリアン
#define	TEX_ALIEN_SAD		52		//悲しい顔したエイリアン
#define	TEX_DROP			53		//しずく
#define	TEX_UFO_TABLE		54		//UFOの中の小物に色々つかっている
#define	TEX_GEAR			57		//黄色の歯車( ギア )
#define	TEX_GEAR_GRY		58		//灰色の歯車( ギア )
#define	TEX_GEAR_RED		59		//赤色の歯車( ギア )
#define	TEX_ALIEN_WEAPON	60		//エイリアンのピストル
#define	TEX_UFO_FOOD		61		//飯のグラフィック
#define	TEX_RAINDOW			62		//虹のグラフィック
#define	TEX_GAME_OVER_EFE	63		//ゲームオーバーのエフェクト( 煙が飛ぶ )
#define	TEX_ARCHER_FISH		64		//鉄砲魚


//-----------------------------------------------------------------------------------------------------------------------
//モデルナンバー
//-----------------------------------------------------------------------------------------------------------------------
#define	MODEL_MAIN_BILL		1		//大きいメインビルのモデル
#define	MODEL_SKY			2		//空のドームのモデル
#define	MODEL_JIKI			3		//UFOの自機のモデル
#define	MODEL_CAR			4		//車のモデル
#define	MODEL_BEAM			5		//ビームのモデル
#define	MODEL_SUB_BILL		6		//ただの四角いビルのモデル
#define	MODEL_HAND			7		//手のモデル
#define	MODEL_ROADSTAR		8		//なんちゃってロードスター
#define	MODEL_TOWER			9		//謎のタワー
#define	MODEL_TENTO			10		//テント
#define	MODEL_BLEAK_BILL	11		//壊れたビル
#define	MODEL_UFO_ROOM		12		//UFOの中( タイトルでつかう )
#define	MODEL_COMPUTER		13		//真ん中に立っている
#define	MODEL_SUB_PARTS		14		//真ん中で回っている輪っか
#define	MODEL_EARTH			15		//地球
#define	MODEL_SCREEN_MEKA	16		//モニター付きのメカ
#define	MODEL_BUTTON_MEKA	17		//ボタンのついている機械
#define	MODEL_CAR_EFE		18		//壊れたときの車のエフェクト
#define	MODEL_BILL_EFE		19		//ビル
#define	MODEL_WOOD			20		//木
#define	MODEL_BONITO		21		//カツオのオブジェ
#define	MODEL_WOOD_EFE		22		//薪
#define	MODEL_SCHOOL		23		//学校
#define	MODEL_SCHOOL_CHAIR	24		//学校のイス
#define	MODEL_SCHOOL_TABLE	25		//学校の机
#define	MODEL_BREAK_SCHOOL	26		//壊れた学校
#define	MODEL_HERI			27		//ヘリ本体
#define	MODEL_PROPELLER		28		//プロペラ部分
#define	MODEL_LOGO_HOUSE	29		//タイトルロゴのマンション
#define	MODEL_BET			30		//壊れたエフェクトに使うベット
#define	MODEL_HUTON			31		//壊れたエフェクトに使うふとん
#define	MODEL_TANSU			32		//タンスのモデル
#define	MODEL_PARKING		33		//駐車場
#define	MODEL_HAND_EFE		34		//手のエフェクト
#define	MODEL_BOATD			35		//スコアボード
#define	MODEL_CAT_MOUNTEN	36		//ネコ山
#define	MODEL_CAT			38		//ネコ
#define	MODEL_MISSILE		39		//ミサイル
#define	MODEL_ALIEN			40		//エイリアン
#define	MODEL_GEAR			41		//ギア
#define	MODEL_UFO_TABLE		42		//UFOテーブル
#define	MODEL_UFO_CHAIR		43		//UFOの中にある椅子
#define	MODEL_ARM_MEKA		44		//アームの付いたメカ
#define	MODEL_ALIEN_WEAPON	45		//エイリアンのピストル
#define	MODEL_UFO_FOOD		46		//テーブルのエフェクト
#define	MODEL_ARCHER_FISH	47		//


//-----------------------------------------------------------------------------------------------------------------------
//効果音のdefine
//-----------------------------------------------------------------------------------------------------------------------
#define	SE_FISH				1		//水が跳ねる音
#define	SE_KLAXON_1			2		//クラクション( 短い )
#define	SE_KLAXON_2			3		//クラクション( 長い )
#define	SE_BILL_BREAK		4		//ビルの壊れる音
#define	SE_PROPELLER		5		//ヘリの音
#define	SE_HERI				6		//ヘリが飛ぶ音
#define	SE_UFO_MOVEMENT		7		//自機の移動


//-----------------------------------------------------------------------------------------------------------------------
//タスクのグループナンバー
//-----------------------------------------------------------------------------------------------------------------------
#define	NO_GROUP			0		//当たり判定などを持たないグループ( エフェクトなど )
#define	JIKI_GROUP			1		//自機のグループ
#define	MAP_GROUP			2		//マップのグループ
#define	OBJECT_GROUP		3		//オブジェクトのグループ
#define	MANE_GROUP			4		//マネージャーのグループ
#define	EDITOR_GROUP		5		//エディターのグループ
#define	FONT_GROUP			6		//フォントのグループ
#define	MODEL_NAME_GROUP	7		//モデルの名前
#define	ARROW_GROUP			8		//矢印のグループ
#define	HAND_GROUP			9		//手のグラフィック
#define	BREAK_OBJECT_GROUP	10		//壊れたオブジェクトのグループ
#define	MAIN_BILL_GROUP		11		//メインのビル
#define	SHOT_GROUP			12		//ショットのグループ
#define	BREAK_EFFECTS_GROUP	13		//飛び散るエフェクトのグループ
#define	UI_GROUP			14		//UIのグループ
#define	MAIN_COMP_GROUP		15		//メインコンピュータのグループ
#define	FEED_BACK_GROUP		16		//ナイスやパーフェクト等を管理するグループ


//-----------------------------------------------------------------------------------------------------------------------
//プライオリティ
//-----------------------------------------------------------------------------------------------------------------------
#define	JIKI_PRI			1000
#define	SHOT_PRI			500
#define	OBJECT_PRI			0
#define	UI_PRI				9999




extern	void move_car_start( SINT32 id );			//まわる車
extern	void car_start( FLOAT x, FLOAT y, FLOAT z, ANGLE ang_x, ANGLE ang_y, FLOAT scale, FLOAT hp, FLOAT atk,SINT32 id );		//停車してる車
extern	void object_start( FLOAT x, FLOAT y, FLOAT z, ANGLE ang_x, ANGLE ang_y, FLOAT scale, FLOAT hp, FLOAT atk,SINT32 id );
extern	void parking_start( FLOAT x, FLOAT y, FLOAT z, ANGLE ang_x, ANGLE ang_y, FLOAT scale, FLOAT hp, FLOAT atk, SINT32 id );
extern	void heri_start( FLOAT x, FLOAT y, FLOAT z, ANGLE ang_x, ANGLE ang_y, FLOAT scale, FLOAT hp, FLOAT atk, SINT32 id );
extern	void alien_start( FLOAT x, FLOAT y, FLOAT z, ANGLE ang_x, ANGLE ang_y, FLOAT scale, FLOAT hp, FLOAT atk,SINT32 id );
