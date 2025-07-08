extern void common_tex_load( void );			//共通のグラフィックをロード
extern void common_model_load(void);		//共通のモデルをロード
extern void tex_game_load( void );			//ゲーム本編で使うグラフィックをロード
extern void model_game_load( void );		//ゲーム本編で使うモデルをロード
extern void tex_title_load( void );			//タイトル使うグラフィックをロード
extern void model_title_load( void );		//タイトル使うモデルをロード
extern void se_load( void );				//効果音をロード

extern void tex_title_reset( void );		//タイトルでのみ使うグラフィックを消す
extern void model_title_reset( void );		//タイトルでのみ使うモデルを消す
extern void tex_game_reset( void );			//ゲームでのみ使うグラフィックを消す
extern void model_game_reset( void );		//ゲームでのみ使うモデルを消す


extern void camera_control_start( void );
extern void main_computer_start( void );
extern void title_logo_start( void );
extern void score_board_start( FLOAT x, FLOAT y, FLOAT z );
