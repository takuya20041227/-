//-----------------------------------------------------------------------------------------------------------------------
//define
//-----------------------------------------------------------------------------------------------------------------------
#define	NORMAL_EDITOR_SPEED_X	 60.0f				//左右移動のスピード
#define	NORMAL_EDITOR_SPEED_Z	120.0f				//前後のスピード
#define	SEQ_SAVE_MAX	0x1000						//シーケンスのサイズ
#define	SELECT_MIN		1							//セレクトの最小
#define	SELECT_MAX		10							//セレクトの最大
#define	PAGE_MIN		0							//ページの最小
#define	PAGE_MAX		( OBJ_MAX / SELECT_MAX )	//ページの最大( セレクトの最大とオブジェクトの最大を割る


extern	SINT32	page, select_no;					//オブジェクトのページ数とどこを選択しているかを格納する変数
extern	FLOAT	sequence_box[ SEQ_SAVE_MAX ];		//シーケンスを入れ込む

extern	void object_editor_start( void );			//エディターと選択とモデルを出す
extern	void sequence_set_object_start( void );		//シーケンスの中身からオブジェクトを設置する
extern	void model_name_start( void );				//モデルの名前を常時出現
extern	void arrow_check( void );
extern	void seq_delete( SINT32 id );
