//--------------------------------------------------------------------------------------------------------------------------------------------------
//				ゲーム部のカスタムファイル
//--------------------------------------------------------------------------------------------------------------------------------------------------

#define	RECT_C(x, y, w, h)	{ x, y, w, h, w / 2, h / 2 }


//------------------------------------------------------------------------------------------------------------------------------------------------------
//ゲームモード
//------------------------------------------------------------------------------------------------------------------------------------------------------

#define	GAMEMODE_NORMAL		0
#define	GAMEMODE_WATCH		1


//------------------------------------------------------------------------------------------------------------------------------------------------------
//キャラナンバー
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define	CHAR_DIGITAL		0				//デジタル
#define	CHAR_SECURE			1				//セキュア
#define	CHAR_ADMIN			2				//アドミン
#define	CHAR_SENSER			3				//センサー
#define	CHAR_IP				4				//アイピー
#define	CHAR_EPOC			5				//エポック
#define	CHAR_PATCH			6				//パッチ
#define	CHAR_CONNECT		7				//コネクト
#define	CHAR_TECHNO			8				//テクノ
#define	CHAR_LITERA			9				//リテラ
#define	CHAR_PACKET			10				//パケット
#define	CHAR_KAMISAMA		11				//カミサマ
#define	CHAR_INFO			12				//インフォ
#define	CHAR_ATSUO			13				//アツオ
#define	CHAR_TASHIMARU		14				//タシマル
#define	CHAR_TRYLL			15				//トリル
#define	CHAR_UNKNOWN		16				
#define	CHAR_UNTEN			17				//うんてんしゅ
#define	CHAR_NETBAIKIN		18				//ネットバイキン
#define	CHAR_MIRROR			19				//ミラ
#define	CHAR_CUMIN			20				//クミン
#define	CHAR_ROXY			21				//ロキシー
#define	CHAR_FUSE			22				//ヒューズ
#define	CHAR_JYUUMIN1		30
#define	CHAR_JYUUMIN2		31
#define	CHAR_JYUUMIN3		32
#define	CHAR_JYUUMIN4		33
#define	CHAR_JYUUMIN5		34
#define	CHAR_JYUUMIN6		35
#define	CHAR_JYUUMIN7		36
#define	CHAR_JYUUMIN8		37
#define	CHAR_JYUUMIN9		38
#define	CHAR_JYUUMIN10		39
#define	CHAR_MAXI			99


//------------------------------------------------------------------------------------------------------------------------------------------------------
//テクスチャナンバー
//------------------------------------------------------------------------------------------------------------------------------------------------------

















//------------------------------------------------------------------------------------------------------------------------------------------------------
//実行プライオリティ
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define	EXEPRI_LAST			0			//最後に処理

#define	EXEPRI_BG				1
#define	EXEPRI_QUICK_SHOT		2
#define	EXEPRI_SHOT				6
#define	EXEPRI_MYCHAR			9
#define	EXEPRI_SPHERE			10
#define	EXEPRI_BOSS				12
#define	EXEPRI_MIDDLE			15
#define	EXEPRI_ENEMY_FACE		18	
#define	EXEPRI_ENEMY			19
#define	EXEPRI_BALETTE			20
#define	EXEPRI_ENEMY_GENE		23		
#define	EXEPRI_MULTI_NUMNBER	26		
#define	EXEPRI_SEQUENCE			27		
#define	EXEPRI_MOUSE			30


#define	EXEPRI_STORYSEQ		27
#define	EXEPRI_JEWEL_DRAW	27



//------------------------------------------------------------------------------------------------------------------------------------------------------
//表示プライオリティ
//------------------------------------------------------------------------------------------------------------------------------------------------------

#define	PRI_SKY					-95000 * WP		//空背景
#define	PRI_SKYOBJECT			-92000 * WP		//空に置く物体
#define	PRI_MOUNT				-90000 * WP		//山
#define	PRI_MOUNT_BEFORE		-80000 * WP		//山の前
#define	PRI_UNDERGROUND			-70000 * WP		//地面
#define	PRI_ROAD				-60000 * WP
#define	PRI_ROAD_PUT			-59000 * WP		//地面
#define	PRI_BIRD				-55000 * WP		//鳥
#define	PRI_BG_LEVEL5			-50400 * WP
#define	PRI_BG_LEVEL4			-50300 * WP
#define	PRI_BG_LEVEL3			-50200 * WP
#define	PRI_BG_LEVEL2			-50100 * WP
#define	PRI_BG					-50000 * WP
#define	PRI_HOUSE				-14000 * WP		//地面に置かれる３Ｄ物体
#define	PRI_IRONPOLE			-11000 * WP		//鉄の柱の奥
#define	PRI_IRONPOLE_TOP		-10900 * WP		//鉄の柱上のパーツ
#define	PRI_SPECIAL_BG			-10000 * WP		//看板や特別背景など
#define	PRI_FENCE				-8000 * WP		//町中にあるフェンスなど
#define	PRI_ANIMAL				-7000 * WP		//動物たち
#define	PRI_SPECIAL_BG_FRONT	-5000 * WP		//特殊背景（動物より手前）
#define	PRI_GLASS				-999 * WP		//地面に生える草や
#define	PRI_KIRI_BACK		    -600 * WP		//霧のグラフィック（奥がわ）		




#define	PRI_BG_AIR				 5000 * WP		//空中に出す障害物の矩形（ブロックとか）
#define	PRI_KIRI_BEFORE			 5500 * WP		//霧のグラフィク
#define	PRI_BOSS			     8000 * WP
#define	PRI_CORE_BACK			10000 * WP
#define	PRI_CORE				11000 * WP
#define	PRI_CORE_WALL			12000 * WP
#define	PRI_BOSS_COREFRONT		15000 * WP

#define	PRI_LENZ_FLERA			16000 * WP
#define	PRI_ENEMY_MIDDLE_BREAK	20000 * WP
#define	PRI_RESULECTION_EFFECT	21000 * WP
#define	PRI_TUTORIAL_MESSAGE	22000 * WP
#define	PRI_POWER_UP_MESSAGE	23000 * WP
#define	PRI_BOOST_EFFECT		24000 * WP
#define	PRI_HP_GAUGE_DISP		25000 * WP
#define	PRI_SHOT_2NDLAYER		26000 * WP
#define	PRI_BAIKIN_SMOKE		26500 * WP
#define	PRI_BAIKIN_BREAK_PER	26800 * WP
#define	PRI_SHOT_BOMB			27000 * WP
#define	PRI_MEKA_HAHEN			28000 * WP		//メカ系の敵の破片
#define	PRI_GAUGE				29000 * WP		//ゲージ
#define	PRI_ENEMY_MIDDLE		30000 * WP		//中型の敵
#define	PRI_WEAPON_BOMB			31000 * WP		//
#define	PRI_ENEMY				33000 * WP		//ネットバイキンなど、小型の敵の表示
#define	PRI_MOVE_POINTER		34000 * WP
#define	PRI_COREHP_INFO			37000 * WP
#define	PRI_MYCHAR_SHOT			38000 * WP		//自分のキャラの攻撃
#define	PRI_SHOTDUST			39000 * WP		//自分のキャラの攻撃のダスト
#define	PRI_ITEMCHIP			40000 * WP		//アイテムチップ
#define	PRI_MONEY				40500 * WP		//アイテムチップ
#define	PRI_DAMAGE				40700 * WP		//アイテムチップ
#define	PRI_MYCHAR				41000 * WP		//自分のキャラ
#define	PRI_REFRECT				42000 * WP		//リフレクター
#define	PRI_BALETTE				43000 * WP		//敵の弾
#define	PRI_BALETTE_BREAK		44000 * WP		//壊せる敵の弾
#define	PRI_ENEMY_FRONT_MAX		45000 * WP		//手前に置く敵（手前をよぎるなどの演出用）
#define	PRI_KIRI				50000 * WP		//キャラクターを消すレベルの霧
#define	PRI_INFO_MESSAGE		60000 * WP
#define PRI_IRONPOLE_FORNT		75000 * WP
#define	PRI_KIRI_BLIND			80000 * WP
#define	PRI_MASK				81000 * WP

#define	PRI_STILL				100500 * WP


//------------------------------------------------------------------------------------------------------------------------------------------------------
//タスクグループ
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define	GROUP_SYSTEM_CORE				0
#define	GROUP_SYSTEM					1

