//-----------------------------------------------------------------------------------------------------------------------
//define
//-----------------------------------------------------------------------------------------------------------------------
#define	NORMAL_EDITOR_SPEED_X	 60.0f				//���E�ړ��̃X�s�[�h
#define	NORMAL_EDITOR_SPEED_Z	120.0f				//�O��̃X�s�[�h
#define	SEQ_SAVE_MAX	0x1000						//�V�[�P���X�̃T�C�Y
#define	SELECT_MIN		1							//�Z���N�g�̍ŏ�
#define	SELECT_MAX		10							//�Z���N�g�̍ő�
#define	PAGE_MIN		0							//�y�[�W�̍ŏ�
#define	PAGE_MAX		( OBJ_MAX / SELECT_MAX )	//�y�[�W�̍ő�( �Z���N�g�̍ő�ƃI�u�W�F�N�g�̍ő������


extern	SINT32	page, select_no;					//�I�u�W�F�N�g�̃y�[�W���Ƃǂ���I�����Ă��邩���i�[����ϐ�
extern	FLOAT	sequence_box[ SEQ_SAVE_MAX ];		//�V�[�P���X����ꍞ��

extern	void object_editor_start( void );			//�G�f�B�^�[�ƑI���ƃ��f�����o��
extern	void sequence_set_object_start( void );		//�V�[�P���X�̒��g����I�u�W�F�N�g��ݒu����
extern	void model_name_start( void );				//���f���̖��O���펞�o��
extern	void arrow_check( void );
extern	void seq_delete( SINT32 id );
