//-----------------------------------------------------------------------------------------------------------------------
//define
//-----------------------------------------------------------------------------------------------------------------------
#define	SAVE_FILE		"game_map"		


//-----------------------------------------------------------------------------------------------------------------------
//extern
//-----------------------------------------------------------------------------------------------------------------------
extern SINT32 dimension_write_the_file( CHAR *file_name, const void *buf, size_t size, size_t n );

extern SINT32 dimension_read_the_file( CHAR *file_name, void *buf, size_t size, size_t n );

extern	void select_and_page_write( CHAR *file_name, const void *buf );		//書き込み

extern	void select_and_page_read( CHAR *file_name, void *buf );			//読み込み

extern	void sequence_write( CHAR *file_name, const void *buf );			//シーケンスの書き込み

extern	void sequence_read( CHAR *file_name, void *buf );					//シーケンスの読み込み

