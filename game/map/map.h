//------------------------------------------------------------------------------------------
//define
//------------------------------------------------------------------------------------------
#define	MAIN_BILL_HP_MAX				200000			//メインビルのHPの上限




//------------------------------------------------------------------------------------------
//extern
//------------------------------------------------------------------------------------------
extern SINT32 clear_flag;				//ここの値が変わると地球が荒廃する
extern SINT32 geme_over_flag;			//ここの値が変わると宇宙人の表情が変わる
extern SINT32 main_bill_hp;				//HPを保管する


extern void ground_start( SINT32 tex_no );
extern void main_bill_start( void );
extern void sky_start( SINT32 model_no, SINT32 tex_no,  FLOAT y, FLOAT scale_x, FLOAT scale_y, FLOAT scale_z, SINT32 game_or_title );
extern void ud_wall_start( FLOAT z );
extern void lr_wall_start( FLOAT x );

extern void mobu_ufo_generator_start( void );		//クリアすると飛んでくるUFOのジェネレーター
extern void geme_resurt_start( SINT32 anime_no );
extern void screen_shutdown_start( void );

