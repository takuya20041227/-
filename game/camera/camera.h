#define	MAIN_CAMERA			0



extern SINT32 mouse_x, mouse_y;						//マウスの座標を入れる変数
extern FLOAT mouse_3d_x, mouse_3d_y;				//3D座標に変換したマウス座標
extern FLOAT world_mouse_x, world_mouse_y;			//ワールド座標に変換したマウス
extern FLOAT z_box[ WINDOW_HEIGHT_HALF ];
extern ANGLE mouse_ang_box[ WINDOW_WIDTH_HALF ];
extern void sphire_debug_start( void );
extern void mouse_get_cursor_start( void );