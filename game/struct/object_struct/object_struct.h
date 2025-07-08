//--------------------------------------------------------------------------------------
//define
//--------------------------------------------------------------------------------------
#define	OBJECT_DATA_MAX		4			//なるべく二進数
#define	OBJ_SPHIRE_MAX		8			//判定のマックス値
#define	OBJ_MAX				128			//オブジェクトの実装できる上限( スフィアを初期化する関係上 )
#define	NO_ATK				1.0f		//ATKの引数に入れるDEBUG用
#define	NO_HP				1.0f		//HPの引数に入れるDEBUG用


//--------------------------------------------------------------------------------------
//オブジェクトのフラグに関するdefine
//--------------------------------------------------------------------------------------
#define	ID_CHENGE_FLAG		0x1


//--------------------------------------------------------------------------------------
//オブジェクトのフラグに関するdefine
//--------------------------------------------------------------------------------------
#define	NO_FLAG				0x0
#define	CAR_FLAG			ID_CHENGE_FLAG
#define	WOOD_FLAG			ID_CHENGE_FLAG
#define	BONITO_FLAG			ID_CHENGE_FLAG
#define	LOGO_HOUSE_FLAG		ID_CHENGE_FLAG

//--------------------------------------------------------------------------------------
//オブジェクトの識別番号のdefine
//--------------------------------------------------------------------------------------

#define	CAR_GREEN			2			//緑の車
#define	SUB_BILL			3			//ただの四角いビル
#define	MAIN_BILL			12			//メインの大きいビル



//--------------------------------------------------------------------------------------
//オブジェクトのグループdefine
//--------------------------------------------------------------------------------------
#define	CAR_GROUP			1
#define	BILL_GROUP			2
#define	MEKA_GROUP			3
#define	FISH_GROUP			4
#define	SCHOOL_GROUP		5
#define	HOUSE_GROUP			6
#define	HERI_GROUP			7
#define	CAT_GROUP			8						//ネコ
#define	UFO_ROOM_GROUP		9


#define	MAIN_BILL_GRP_FLAG	TEST_ZBUFFER | WRITE_ZBUFFER  | NO_SHADOW	 | USE_LIGHTING | USE_SPECULAR
#define	SUB_BILL_GRP_FLAG	TEST_ZBUFFER | WRITE_ZBUFFER  | NO_SHADOW	 | USE_LIGHTING | USE_SPECULAR
#define	CAR_GRP_FLAG		TEST_ZBUFFER | WRITE_ZBUFFER  | USE_SPECULAR | USE_LIGHTING
#define	SCHOOL_GRP_FLAG		TEST_ZBUFFER | WRITE_ZBUFFER  | USE_LIGHTING


//--------------------------------------------------------------------------------------
//関数のエクスターン
//--------------------------------------------------------------------------------------
extern void object_sphire_init( void );
extern FLOAT sphire_get( TASK *ap );
extern void sphire_set_case( TASK *ap );


//--------------------------------------------------------------------------------------
//構造体
//--------------------------------------------------------------------------------------
typedef struct
{
	CHAR	name[32];					//名前を入れる( 入れてるとウォッチで調べやすくなる )
	SINT32	object_group;				//オブジェクトの中でもどのオブジェクトか見分ける為に作成
	SINT32	model_no;					//最初のモデルのナンバー
	SINT32	tex_no;						//最初のテクスチャーのナンバー
	SINT32	break_model_no;				//壊れたときのモデルナンバー
	SINT32	break_tex_no;				//壊れたときのテクスチャーのナンバー
	SINT32	grp_flag;					//スペキュラーなどの設定を入れる
	FLOAT	pow;						//光の影響の受け具合
	FLOAT	specular_r;					//スペキュラー( 赤 )
	FLOAT	specular_g;					//スペキュラー( 緑 )
	FLOAT	specular_b;					//スペキュラー( 青 )
	FLOAT	hp;							//ヒットポイント
	FLOAT	atk;						//攻撃力
	SINT32	particle_num;				//パーティクルの数
	SINT32	particle_model;				//パーティクルのモデル
	SINT32	particle_tex;				//パーティクルのテクスチャー
	SINT32	se_no;						//効果音の番号
	FLOAT	se_vol;						//効果音の音量
	SINT32	flag;						//ステータスのフラグ
	SINT32	icon;						//手が掴んだときの
	SINT32	score;						//スコアの上昇量
	FLOAT	scale;						//大きさ
}	OBJECT_DATA;

//extern OBJECT_DATA object_data[ ];		//オブジェクトの構造体


//関数の中で値を入れる
typedef struct
{
	FLOAT sphire[ OBJ_SPHIRE_MAX ];				//当たり判定を複数個入れるための箱
	FLOAT sphire_height_min[ OBJ_SPHIRE_MAX ];	//高さによってスフィアの大きさを変える最小値
	FLOAT sphire_height_max[ OBJ_SPHIRE_MAX ];	//高さによってスフィアの大きさを変える最大値
}	OBJECT_SPHIRE;


typedef struct
{
	SINT32 unique_id;
	SINT32 id;
}	ICON_DATA;

extern  OBJECT_SPHIRE object_sphire[ OBJ_MAX ];	//当たり判定を設定する
extern	OBJECT_DATA	  object_data[ OBJ_MAX ];		//色々なオブジェクトの設定が入っている
extern	void object_sphire_set( SINT32 id, SINT32 sphire_no, FLOAT sphire, FLOAT height_min, FLOAT height_max );		//スフィアを入れる
extern	SINT32 kawa_3d_hit_check( TASK * ap, TASK * actp );
extern	SINT32 jiki_hit_check( TASK *ap, TASK *actp );

extern	SINT32 range_sphire( TASK *ap, FLOAT sphire, TASK *actp );
extern	FLOAT length_return( TASK *ap, FLOAT sphire, TASK *actp );