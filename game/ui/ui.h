#define	KEY_POS_Y		WINDOW_HEIGHT - 380.0f

extern SINT32 hi_score;								//�n�C�X�R�A

extern void main_bill_hp_start( void );				//���C���r���̃A�C�R���Ƒ̗͕\��
extern void common_ui_set( void );					//�S�̂Ŏg����UI�������Ă���
extern void icon_box_all_init( void );					//�A�C�R�����i�[����
extern void show_game_goal_start( void );
extern void game_start_purpose_start( void );
extern void timer_start( void );					//�^�C�}�[
extern void icon_set( void );						//�A�C�R�����Z�b�g����
extern void icon_param_get( TASK *ap );				//�A�C�R���̏��������
extern void icon_box_check_start( void );


extern void socre_start( FLOAT x, FLOAT y, FLOAT scale, SINT32 *score_p );
extern void title_return_start( SINT32 delay );