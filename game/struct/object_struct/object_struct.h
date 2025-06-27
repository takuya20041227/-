//--------------------------------------------------------------------------------------
//define
//--------------------------------------------------------------------------------------
#define	OBJECT_DATA_MAX		4			//�Ȃ�ׂ���i��
#define	OBJ_SPHIRE_MAX		8			//����̃}�b�N�X�l
#define	OBJ_MAX				128			//�I�u�W�F�N�g�̎����ł�����( �X�t�B�A������������֌W�� )
#define	NO_ATK				1.0f		//ATK�̈����ɓ����DEBUG�p
#define	NO_HP				1.0f		//HP�̈����ɓ����DEBUG�p


//--------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̃t���O�Ɋւ���define
//--------------------------------------------------------------------------------------
#define	ID_CHENGE_FLAG		0x1


//--------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̃t���O�Ɋւ���define
//--------------------------------------------------------------------------------------
#define	NO_FLAG				0x0
#define	CAR_FLAG			ID_CHENGE_FLAG
#define	WOOD_FLAG			ID_CHENGE_FLAG
#define	BONITO_FLAG			ID_CHENGE_FLAG
#define	LOGO_HOUSE_FLAG		ID_CHENGE_FLAG

//--------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̎��ʔԍ���define
//--------------------------------------------------------------------------------------

#define	CAR_GREEN			2			//�΂̎�
#define	SUB_BILL			3			//�����̎l�p���r��
#define	MAIN_BILL			12			//���C���̑傫���r��



//--------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̃O���[�vdefine
//--------------------------------------------------------------------------------------
#define	CAR_GROUP			1
#define	BILL_GROUP			2
#define	MEKA_GROUP			3
#define	FISH_GROUP			4
#define	SCHOOL_GROUP		5
#define	HOUSE_GROUP			6
#define	HERI_GROUP			7
#define	CAT_GROUP			8						//�l�R
#define	UFO_ROOM_GROUP		9


#define	MAIN_BILL_GRP_FLAG	TEST_ZBUFFER | WRITE_ZBUFFER  | NO_SHADOW	 | USE_LIGHTING | USE_SPECULAR
#define	SUB_BILL_GRP_FLAG	TEST_ZBUFFER | WRITE_ZBUFFER  | NO_SHADOW	 | USE_LIGHTING | USE_SPECULAR
#define	CAR_GRP_FLAG		TEST_ZBUFFER | WRITE_ZBUFFER  | USE_SPECULAR | USE_LIGHTING
#define	SCHOOL_GRP_FLAG		TEST_ZBUFFER | WRITE_ZBUFFER  | USE_LIGHTING


//--------------------------------------------------------------------------------------
//�֐��̃G�N�X�^�[��
//--------------------------------------------------------------------------------------
extern void object_sphire_init( void );
extern FLOAT sphire_get( TASK *ap );
extern void sphire_set_case( TASK *ap );


//--------------------------------------------------------------------------------------
//�\����
//--------------------------------------------------------------------------------------
typedef struct
{
	CHAR	name[32];					//���O������( ����Ă�ƃE�H�b�`�Œ��ׂ₷���Ȃ� )
	SINT32	object_group;				//�I�u�W�F�N�g�̒��ł��ǂ̃I�u�W�F�N�g����������ׂɍ쐬
	SINT32	model_no;					//�ŏ��̃��f���̃i���o�[
	SINT32	tex_no;						//�ŏ��̃e�N�X�`���[�̃i���o�[
	SINT32	break_model_no;				//��ꂽ�Ƃ��̃��f���i���o�[
	SINT32	break_tex_no;				//��ꂽ�Ƃ��̃e�N�X�`���[�̃i���o�[
	SINT32	grp_flag;					//�X�y�L�����[�Ȃǂ̐ݒ������
	FLOAT	pow;						//���̉e���̎󂯋
	FLOAT	specular_r;					//�X�y�L�����[( �� )
	FLOAT	specular_g;					//�X�y�L�����[( �� )
	FLOAT	specular_b;					//�X�y�L�����[( �� )
	FLOAT	hp;							//�q�b�g�|�C���g
	FLOAT	atk;						//�U����
	SINT32	particle_num;				//�p�[�e�B�N���̐�
	SINT32	particle_model;				//�p�[�e�B�N���̃��f��
	SINT32	particle_tex;				//�p�[�e�B�N���̃e�N�X�`���[
	SINT32	se_no;						//���ʉ��̔ԍ�
	FLOAT	se_vol;						//���ʉ��̉���
	SINT32	flag;						//�X�e�[�^�X�̃t���O
	SINT32	icon;						//�肪�͂񂾂Ƃ���
	SINT32	score;						//�X�R�A�̏㏸��
	FLOAT	scale;						//�傫��
}	OBJECT_DATA;

//extern OBJECT_DATA object_data[ ];		//�I�u�W�F�N�g�̍\����


//�֐��̒��Œl������
typedef struct
{
	FLOAT sphire[ OBJ_SPHIRE_MAX ];				//�����蔻��𕡐�����邽�߂̔�
	FLOAT sphire_height_min[ OBJ_SPHIRE_MAX ];	//�����ɂ���ăX�t�B�A�̑傫����ς���ŏ��l
	FLOAT sphire_height_max[ OBJ_SPHIRE_MAX ];	//�����ɂ���ăX�t�B�A�̑傫����ς���ő�l
}	OBJECT_SPHIRE;


typedef struct
{
	SINT32 unique_id;
	SINT32 id;
}	ICON_DATA;

extern  OBJECT_SPHIRE object_sphire[ OBJ_MAX ];	//�����蔻���ݒ肷��
extern	OBJECT_DATA	  object_data[ OBJ_MAX ];		//�F�X�ȃI�u�W�F�N�g�̐ݒ肪�����Ă���
extern	void object_sphire_set( SINT32 id, SINT32 sphire_no, FLOAT sphire, FLOAT height_min, FLOAT height_max );		//�X�t�B�A������
extern	SINT32 kawa_3d_hit_check( TASK * ap, TASK * actp );
extern	SINT32 jiki_hit_check( TASK *ap, TASK *actp );

extern	SINT32 range_sphire( TASK *ap, FLOAT sphire, TASK *actp );
extern	FLOAT length_return( TASK *ap, FLOAT sphire, TASK *actp );