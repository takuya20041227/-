//------------------------------------------------------------------------------------------
//define
//------------------------------------------------------------------------------------------
#define	MAIN_BILL_HP_MAX				200000			//���C���r����HP�̏��




//------------------------------------------------------------------------------------------
//extern
//------------------------------------------------------------------------------------------
extern SINT32 clear_flag;				//�����̒l���ς��ƒn�����r�p����
extern SINT32 geme_over_flag;			//�����̒l���ς��ƉF���l�̕\��ς��
extern SINT32 main_bill_hp;				//HP��ۊǂ���


extern void ground_start( SINT32 tex_no );
extern void main_bill_start( void );
extern void sky_start( SINT32 model_no, SINT32 tex_no,  FLOAT y, FLOAT scale_x, FLOAT scale_y, FLOAT scale_z, SINT32 game_or_title );
extern void ud_wall_start( FLOAT z );
extern void lr_wall_start( FLOAT x );

extern void mobu_ufo_generator_start( void );		//�N���A����Ɣ��ł���UFO�̃W�F�l���[�^�[
extern void geme_resurt_start( SINT32 anime_no );
extern void screen_shutdown_start( void );

