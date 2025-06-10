#define	KEY_POS_Y		WINDOW_HEIGHT - 380.0f

extern SINT32 hi_score;								//ハイスコア

extern void main_bill_hp_start( void );				//メインビルのアイコンと体力表示
extern void common_ui_set( void );					//全体で使えるUIが入っている
extern void icon_box_all_init( void );					//アイコンを格納する
extern void show_game_goal_start( void );
extern void game_start_purpose_start( void );
extern void timer_start( void );					//タイマー
extern void icon_set( void );						//アイコンをセットする
extern void icon_param_get( TASK *ap );				//アイコンの情報をいれる
extern void icon_box_check_start( void );


extern void socre_start( FLOAT x, FLOAT y, FLOAT scale, SINT32 *score_p );
extern void title_return_start( SINT32 delay );