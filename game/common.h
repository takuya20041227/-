extern void no_hp_move( TASK *ap, OBJECT_DATA *op,SINT32 cool_time );
extern SINT32 sa_check_smaller( FLOAT ap_value, FLOAT actp_value, FLOAT sa_max );
extern SINT32 sa_check_bigger( FLOAT ap_value, FLOAT actp_value, FLOAT sa_max );
extern void vec_all_init( TASK *ap );							//�x�N�g����xyz���ׂĂ�0�ɂ���

extern SINT32 F_excepting( FLOAT  target_a, FLOAT  target_b );	//( float�^ )�������m����v���Ȃ����ɒl���Ԃ�
extern SINT32 excepting(   SINT32 target_a, SINT32 target_b );	//( int�^ )�������m����v���Ȃ����ɒl���Ԃ�

extern void task_id_checge( TASK *ap, SINT32 check );
extern void alpha_chenge( TASK *ap, SINT32 alp_max, SINT32 alp_min );


extern void geme_over_heri_start( FLOAT x );
extern void game_ovre_start( void );
extern void flower_start( FLOAT x, FLOAT y, FLOAT z, FLOAT vec_x, FLOAT vec_y, FLOAT vec_z, SINT32 pos_flag );
extern void efe_red_window_mane_start( void );
extern void shut_down_start( void );


extern FLOAT ang_pan( TASK *ap, TASK *actp, FLOAT lr_max, ANGLE angle, SINT32 lr );
extern FLOAT range_vol( FLOAT vol_max, FLOAT vol_rang_max, FLOAT len_num );
extern SINT32 not_range( FLOAT min, FLOAT max );
extern void common_ambient( TASK *ap );
extern void scale_all_chenge( TASK *ap, FLOAT scale );