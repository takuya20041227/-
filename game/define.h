//-----------------------------------------------------------------------------------------------------------------------
//�S�̂��g����define
//-----------------------------------------------------------------------------------------------------------------------
#define	GROUND				-500
#define	ON					1
#define	OFF					0
#define	RESET				0
#define	WINDOW_WIDTH_HALF	( WINDOW_WIDTH  / 2 )
#define	WINDOW_HEIGHT_HALF	( WINDOW_HEIGHT / 2 )
#define	WINDOW_WIDTH_QUARTER	( WINDOW_WIDTH  / 4 )
#define	WINDOW_HEIGHT_QUARTER	( WINDOW_HEIGHT / 4 )
#define	DEFAULT_ARGUMENT	FLOAT x, FLOAT y, FLOAT z, FLOAT vec_x, FLOAT vec_y, FLOAT vec_z


//-----------------------------------------------------------------------------------------------------------------------
//���Ԃ̃f�t�@�C��
//-----------------------------------------------------------------------------------------------------------------------
#define	TIME_S			60				//60�t���[����1�b
#define	TIME_M			( TIME_S * 60 )	//1��
#define	TIME_H			( TIME_M * 60 )	//1����


//-----------------------------------------------------------------------------------------------------------------------
//���[�N��define
//-----------------------------------------------------------------------------------------------------------------------
#define	TIMER			work9[X]	//���Ԍv��
#define	COUNT			work9[Y]	//�������J�E���g����
#define	SCENE			work9[Z]	//switch���Ŏg����ʐi�s�̃��[�N
#define	ID				work9[P]	//���ʔԍ�
#define	FLAG			work9[D]	//�t���O

#define	HP				work8[X]	//�̗�
#define	ATK				work8[Y]	//�U����
#define	DEF				work8[Z]	//�h���
#define	GROUP			work8[P]	//�O���[�v
#define	SWITCH			work8[D]	//�Ȃɂ��̃X�C�b�`
#define	SUB_SWITCH		work8[E]	//�Ȃɂ��̃X�C�b�`

//-----------------------------------------------------------------------------------------------------------------------
//���[�N��define
//-----------------------------------------------------------------------------------------------------------------------
#define	TITLE_SCENE				   5	//�^�C�g�����
#define	TUTORIAL			  10	//�`���[�g���A�����
#define	GAME				 100	//�Q�[���{��
#define	GAME_CLERE			 110	//�Q�[���N���A
#define	GAME_OVER			 120	//�Q�[���I�[�o�[
#define	REPLYE				 500	//���v���C
#define	GAME_EDITORE		1000	//�Q�[����ʂ̃G�f�B�^�[
#define	TUTORIAL_EDITORE	2000	//�`���[�g���A���̃G�f�B�^�[


//-----------------------------------------------------------------------------------------------------------------------
//�e�N�X�`���[�i���o�[
//-----------------------------------------------------------------------------------------------------------------------
#define	TEX_GROUND			1		//�n��
#define	TEX_BILL			2		//�r��
#define	TEX_SKY				3		//��
#define	TEX_JIKI			4		//UFO�̎��@
#define	TEX_CAR				5		//�΂̎�
#define	TEX_CAR_B			6		//���̎�
#define	TEX_CAR_W			7		//���̎�
#define	TEX_BEAM			8		//�r�[��
#define	TEX_BOM				9		//����
#define	TEX_HAND			10		//��̖͗l
#define	TEX_DEBUG_PARAM		11		//�G�f�B�^�[�Ŏg���f�o�b�O�t�H���g�������Ă�O���t�B�b�N
#define	TEX_ROADSTAR_R		12		//�Ȃ񂿂���ă��[�h�X�^�[( �� )
#define	TEX_ROADSTAR_B		13		//�Ȃ񂿂���ă��[�h�X�^�[( �� )
#define	TEX_ROADSTAR_W		14		//�Ȃ񂿂���ă��[�h�X�^�[( �� )
#define	TEX_TOWER			15		//��̃^���[
#define	TEX_TENTO			16		//�e���g
#define	TEX_UFO_ROOM		17		//UFO�̒�( �^�C�g���ł��� )
#define	TEX_COMPUTER		18		//�^�񒆂ɗ����Ă���
#define	TEX_EARTH			20		//�n��
#define	TEX_TITLE			21		//
#define	TEX_UFO_GROUND		22		//
#define	TEX_SCREEN_MEKA		23		//���j�^�[�݂̂��Ă�@�B
#define	TEX_BUTTON_MEKA		24		//�{�^���̂��Ă���@�B
#define	TEX_CAR_EFE			25		//�^�C��
#define	TEX_BILL_EFE		26		//�r���̊��I
#define	TEX_WOOD			29		//��
#define	TEX_BONITO			30		//�J�c�I�̃I�u�W�F
#define	TEX_WOOD_EFE		31		//�d
#define	TEX_EARTH_BREAK		32		//�n��
#define	TEX_OBJECT_ICON		33		//�͂񂾃I�u�W�F�N�g�̃A�C�R��
#define	TEX_UI_FONT			34		//��������⃋�[����
#define	TEX_GLAS			35		//�K���X�̔j��
#define	TEX_SCHOOL			36		//�w�Z�̃O���t�B�b�N
#define	TEX_HERI			38		//�w���̃O���t�B�b�N
#define	TEX_LOGO_HOUSE		39		//�^�C�g�����S�̃}���V����
#define	TEX_BET				40		//�x�b�g�ƂӂƂ�̃O���t�B�b�N�������Ă�
#define	TEX_TANSU			41		//�^���X�̃e�N�X�`���[
#define	TEX_PARKING			42		//���ԏ�
#define	TEX_CAT_MOUNTEN		43		//�L�R
#define	TEX_CAT_TYA			44		//���F�̃l�R
#define	TEX_CAT_GRY			45		//�D�F�̃l�R
#define	TEX_CAT_PEL			46		//�y�[���l�R
#define	TEX_MISSILE			47		//�~�T�C��
#define	TEX_FLOWER			48		//���Ԃ���
#define	TEX_ALIEN_NOMAL		49		//���ʂ̃G�C���A��
#define	TEX_ALIEN_SURPRISE	50		//�����Ă�G�C���A��
#define	TEX_ALIEN_SMILE		51		//�Ί�̃G�C���A��
#define	TEX_ALIEN_SAD		52		//�߂����炵���G�C���A��
#define	TEX_DROP			53		//������
#define	TEX_UFO_TABLE		54		//UFO�̒��̏����ɐF�X�����Ă���
#define	TEX_GEAR			57		//���F�̎���( �M�A )
#define	TEX_GEAR_GRY		58		//�D�F�̎���( �M�A )
#define	TEX_GEAR_RED		59		//�ԐF�̎���( �M�A )
#define	TEX_ALIEN_WEAPON	60		//�G�C���A���̃s�X�g��
#define	TEX_UFO_FOOD		61		//�т̃O���t�B�b�N
#define	TEX_RAINDOW			62		//���̃O���t�B�b�N
#define	TEX_GAME_OVER_EFE	63		//�Q�[���I�[�o�[�̃G�t�F�N�g( ������� )
#define	TEX_ARCHER_FISH		64		//�S�C��


//-----------------------------------------------------------------------------------------------------------------------
//���f���i���o�[
//-----------------------------------------------------------------------------------------------------------------------
#define	MODEL_MAIN_BILL		1		//�傫�����C���r���̃��f��
#define	MODEL_SKY			2		//��̃h�[���̃��f��
#define	MODEL_JIKI			3		//UFO�̎��@�̃��f��
#define	MODEL_CAR			4		//�Ԃ̃��f��
#define	MODEL_BEAM			5		//�r�[���̃��f��
#define	MODEL_SUB_BILL		6		//�����̎l�p���r���̃��f��
#define	MODEL_HAND			7		//��̃��f��
#define	MODEL_ROADSTAR		8		//�Ȃ񂿂���ă��[�h�X�^�[
#define	MODEL_TOWER			9		//��̃^���[
#define	MODEL_TENTO			10		//�e���g
#define	MODEL_BLEAK_BILL	11		//��ꂽ�r��
#define	MODEL_UFO_ROOM		12		//UFO�̒�( �^�C�g���ł��� )
#define	MODEL_COMPUTER		13		//�^�񒆂ɗ����Ă���
#define	MODEL_SUB_PARTS		14		//�^�񒆂ŉ���Ă���ւ���
#define	MODEL_EARTH			15		//�n��
#define	MODEL_SCREEN_MEKA	16		//���j�^�[�t���̃��J
#define	MODEL_BUTTON_MEKA	17		//�{�^���̂��Ă���@�B
#define	MODEL_CAR_EFE		18		//��ꂽ�Ƃ��̎Ԃ̃G�t�F�N�g
#define	MODEL_BILL_EFE		19		//�r��
#define	MODEL_WOOD			20		//��
#define	MODEL_BONITO		21		//�J�c�I�̃I�u�W�F
#define	MODEL_WOOD_EFE		22		//�d
#define	MODEL_SCHOOL		23		//�w�Z
#define	MODEL_SCHOOL_CHAIR	24		//�w�Z�̃C�X
#define	MODEL_SCHOOL_TABLE	25		//�w�Z�̊�
#define	MODEL_BREAK_SCHOOL	26		//��ꂽ�w�Z
#define	MODEL_HERI			27		//�w���{��
#define	MODEL_PROPELLER		28		//�v���y������
#define	MODEL_LOGO_HOUSE	29		//�^�C�g�����S�̃}���V����
#define	MODEL_BET			30		//��ꂽ�G�t�F�N�g�Ɏg���x�b�g
#define	MODEL_HUTON			31		//��ꂽ�G�t�F�N�g�Ɏg���ӂƂ�
#define	MODEL_TANSU			32		//�^���X�̃��f��
#define	MODEL_PARKING		33		//���ԏ�
#define	MODEL_HAND_EFE		34		//��̃G�t�F�N�g
#define	MODEL_BOATD			35		//�X�R�A�{�[�h
#define	MODEL_CAT_MOUNTEN	36		//�l�R�R
#define	MODEL_CAT			38		//�l�R
#define	MODEL_MISSILE		39		//�~�T�C��
#define	MODEL_ALIEN			40		//�G�C���A��
#define	MODEL_GEAR			41		//�M�A
#define	MODEL_UFO_TABLE		42		//UFO�e�[�u��
#define	MODEL_UFO_CHAIR		43		//UFO�̒��ɂ���֎q
#define	MODEL_ARM_MEKA		44		//�A�[���̕t�������J
#define	MODEL_ALIEN_WEAPON	45		//�G�C���A���̃s�X�g��
#define	MODEL_UFO_FOOD		46		//�e�[�u���̃G�t�F�N�g
#define	MODEL_ARCHER_FISH	47		//


//-----------------------------------------------------------------------------------------------------------------------
//���ʉ���define
//-----------------------------------------------------------------------------------------------------------------------
#define	SE_FISH				1		//�������˂鉹
#define	SE_KLAXON_1			2		//�N���N�V����( �Z�� )
#define	SE_KLAXON_2			3		//�N���N�V����( ���� )
#define	SE_BILL_BREAK		4		//�r���̉��鉹
#define	SE_PROPELLER		5		//�w���̉�
#define	SE_HERI				6		//�w������ԉ�
#define	SE_UFO_MOVEMENT		7		//���@�̈ړ�


//-----------------------------------------------------------------------------------------------------------------------
//�^�X�N�̃O���[�v�i���o�[
//-----------------------------------------------------------------------------------------------------------------------
#define	NO_GROUP			0		//�����蔻��Ȃǂ������Ȃ��O���[�v( �G�t�F�N�g�Ȃ� )
#define	JIKI_GROUP			1		//���@�̃O���[�v
#define	MAP_GROUP			2		//�}�b�v�̃O���[�v
#define	OBJECT_GROUP		3		//�I�u�W�F�N�g�̃O���[�v
#define	MANE_GROUP			4		//�}�l�[�W���[�̃O���[�v
#define	EDITOR_GROUP		5		//�G�f�B�^�[�̃O���[�v
#define	FONT_GROUP			6		//�t�H���g�̃O���[�v
#define	MODEL_NAME_GROUP	7		//���f���̖��O
#define	ARROW_GROUP			8		//���̃O���[�v
#define	HAND_GROUP			9		//��̃O���t�B�b�N
#define	BREAK_OBJECT_GROUP	10		//��ꂽ�I�u�W�F�N�g�̃O���[�v
#define	MAIN_BILL_GROUP		11		//���C���̃r��
#define	SHOT_GROUP			12		//�V���b�g�̃O���[�v
#define	BREAK_EFFECTS_GROUP	13		//��юU��G�t�F�N�g�̃O���[�v
#define	UI_GROUP			14		//UI�̃O���[�v
#define	MAIN_COMP_GROUP		15		//���C���R���s���[�^�̃O���[�v
#define	FEED_BACK_GROUP		16		//�i�C�X��p�[�t�F�N�g�����Ǘ�����O���[�v


//-----------------------------------------------------------------------------------------------------------------------
//�v���C�I���e�B
//-----------------------------------------------------------------------------------------------------------------------
#define	JIKI_PRI			1000
#define	SHOT_PRI			500
#define	OBJECT_PRI			0
#define	UI_PRI				9999




extern	void move_car_start( SINT32 id );			//�܂���
extern	void car_start( FLOAT x, FLOAT y, FLOAT z, ANGLE ang_x, ANGLE ang_y, FLOAT scale, FLOAT hp, FLOAT atk,SINT32 id );		//��Ԃ��Ă��
extern	void object_start( FLOAT x, FLOAT y, FLOAT z, ANGLE ang_x, ANGLE ang_y, FLOAT scale, FLOAT hp, FLOAT atk,SINT32 id );
extern	void parking_start( FLOAT x, FLOAT y, FLOAT z, ANGLE ang_x, ANGLE ang_y, FLOAT scale, FLOAT hp, FLOAT atk, SINT32 id );
extern	void heri_start( FLOAT x, FLOAT y, FLOAT z, ANGLE ang_x, ANGLE ang_y, FLOAT scale, FLOAT hp, FLOAT atk, SINT32 id );
extern	void alien_start( FLOAT x, FLOAT y, FLOAT z, ANGLE ang_x, ANGLE ang_y, FLOAT scale, FLOAT hp, FLOAT atk,SINT32 id );
