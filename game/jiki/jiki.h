#define	JIKI_X		25000.0f	
#define	JIKI_Y		1000.0f
#define	JIKI_Z		10000.0f

//-----------------------------------------------------------------------------------------------------------------------
//ビームのdefine
//-----------------------------------------------------------------------------------------------------------------------
#define	BEAM_TIME	2					//ビームのショット時間
#define	BEAM_SPEED	80.0f
#define	HAND_SPEED	BEAM_SPEED * 2


//-----------------------------------------------------------------------------------------------------------------------
//マウスのdefine
//-----------------------------------------------------------------------------------------------------------------------
#define	CLICK_RIGHT	0					//右クリック
#define	CLICK_LEFT	1					//左クリック	


typedef struct
{
	FLOAT pos[3];
	FLOAT ang[3];
	FLOAT camera[3];
	FLOAT click[2];
} RECORD;

extern RECORD jiki_record[ TIME_M * 3 + 1 ];
extern RECORD *rp;
extern SINT32 record_fram;

//-----------------------------------------------------------------------------------------------------------------------
//extern 
//-----------------------------------------------------------------------------------------------------------------------
extern	TASK *jiki;
extern	bool click_check, catch_switch;
extern	void movement_get_key( TASK *ap);
extern	void check_range_restriction( TASK *ap, FLOAT pos_x, FLOAT pos_y, FLOAT pos_z );
extern	void jiki_start( void );
extern	void record_mane_start( void );
extern	void hand_start( DEFAULT_ARGUMENT, ANGLE ang_x, ANGLE ang_y );		//壊れたオブジェクトを掴む手
extern	void beam_bom_start( FLOAT x, FLOAT y, FLOAT z, FLOAT scale );					//ボムエフェクト

extern	void specular_status_set( TASK *ap, FLOAT pow, FLOAT sp_r, FLOAT sp_g, FLOAT sp_b );
extern	void specular_sturct_set( TASK *ap, OBJECT_DATA *op );
extern	ANGLE mouse_view_ang( FLOAT mouse_pos_x );
extern	SINT32 x_check( TASK *ap );
extern	SINT32 z_check( TASK *ap );
extern	SINT32 mouse2d_range_check( FLOAT x, FLOAT width, FLOAT y, FLOAT height );	//2D座標のマウスが範囲に入っていたら値を返す関数

extern	SINT32 atk_set( TASK *ap, OBJECT_DATA *op,FLOAT atk );
extern	SINT32 hp_set( TASK *ap, OBJECT_DATA *op,FLOAT hp );
extern	SINT32 no_hp_task_id_chenge( TASK *ap, OBJECT_DATA *op );

extern	SINT32 game_over_flag;