//--------------------------------------------------------------------------------------------------------------------------------------------------
//				�Q�[�����̃J�X�^���t�@�C��
//--------------------------------------------------------------------------------------------------------------------------------------------------

#define	RECT_C(x, y, w, h)	{ x, y, w, h, w / 2, h / 2 }


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�Q�[�����[�h
//------------------------------------------------------------------------------------------------------------------------------------------------------

#define	GAMEMODE_NORMAL		0
#define	GAMEMODE_WATCH		1


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�L�����i���o�[
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define	CHAR_DIGITAL		0				//�f�W�^��
#define	CHAR_SECURE			1				//�Z�L���A
#define	CHAR_ADMIN			2				//�A�h�~��
#define	CHAR_SENSER			3				//�Z���T�[
#define	CHAR_IP				4				//�A�C�s�[
#define	CHAR_EPOC			5				//�G�|�b�N
#define	CHAR_PATCH			6				//�p�b�`
#define	CHAR_CONNECT		7				//�R�l�N�g
#define	CHAR_TECHNO			8				//�e�N�m
#define	CHAR_LITERA			9				//���e��
#define	CHAR_PACKET			10				//�p�P�b�g
#define	CHAR_KAMISAMA		11				//�J�~�T�}
#define	CHAR_INFO			12				//�C���t�H
#define	CHAR_ATSUO			13				//�A�c�I
#define	CHAR_TASHIMARU		14				//�^�V�}��
#define	CHAR_TRYLL			15				//�g����
#define	CHAR_UNKNOWN		16				
#define	CHAR_UNTEN			17				//����Ă񂵂�
#define	CHAR_NETBAIKIN		18				//�l�b�g�o�C�L��
#define	CHAR_MIRROR			19				//�~��
#define	CHAR_CUMIN			20				//�N�~��
#define	CHAR_ROXY			21				//���L�V�[
#define	CHAR_FUSE			22				//�q���[�Y
#define	CHAR_JYUUMIN1		30
#define	CHAR_JYUUMIN2		31
#define	CHAR_JYUUMIN3		32
#define	CHAR_JYUUMIN4		33
#define	CHAR_JYUUMIN5		34
#define	CHAR_JYUUMIN6		35
#define	CHAR_JYUUMIN7		36
#define	CHAR_JYUUMIN8		37
#define	CHAR_JYUUMIN9		38
#define	CHAR_JYUUMIN10		39
#define	CHAR_MAXI			99


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�e�N�X�`���i���o�[
//------------------------------------------------------------------------------------------------------------------------------------------------------

















//------------------------------------------------------------------------------------------------------------------------------------------------------
//���s�v���C�I���e�B
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define	EXEPRI_LAST			0			//�Ō�ɏ���

#define	EXEPRI_BG				1
#define	EXEPRI_QUICK_SHOT		2
#define	EXEPRI_SHOT				6
#define	EXEPRI_MYCHAR			9
#define	EXEPRI_SPHERE			10
#define	EXEPRI_BOSS				12
#define	EXEPRI_MIDDLE			15
#define	EXEPRI_ENEMY_FACE		18	
#define	EXEPRI_ENEMY			19
#define	EXEPRI_BALETTE			20
#define	EXEPRI_ENEMY_GENE		23		
#define	EXEPRI_MULTI_NUMNBER	26		
#define	EXEPRI_SEQUENCE			27		
#define	EXEPRI_MOUSE			30


#define	EXEPRI_STORYSEQ		27
#define	EXEPRI_JEWEL_DRAW	27



//------------------------------------------------------------------------------------------------------------------------------------------------------
//�\���v���C�I���e�B
//------------------------------------------------------------------------------------------------------------------------------------------------------

#define	PRI_SKY					-95000 * WP		//��w�i
#define	PRI_SKYOBJECT			-92000 * WP		//��ɒu������
#define	PRI_MOUNT				-90000 * WP		//�R
#define	PRI_MOUNT_BEFORE		-80000 * WP		//�R�̑O
#define	PRI_UNDERGROUND			-70000 * WP		//�n��
#define	PRI_ROAD				-60000 * WP
#define	PRI_ROAD_PUT			-59000 * WP		//�n��
#define	PRI_BIRD				-55000 * WP		//��
#define	PRI_BG_LEVEL5			-50400 * WP
#define	PRI_BG_LEVEL4			-50300 * WP
#define	PRI_BG_LEVEL3			-50200 * WP
#define	PRI_BG_LEVEL2			-50100 * WP
#define	PRI_BG					-50000 * WP
#define	PRI_HOUSE				-14000 * WP		//�n�ʂɒu�����R�c����
#define	PRI_IRONPOLE			-11000 * WP		//�S�̒��̉�
#define	PRI_IRONPOLE_TOP		-10900 * WP		//�S�̒���̃p�[�c
#define	PRI_SPECIAL_BG			-10000 * WP		//�Ŕ���ʔw�i�Ȃ�
#define	PRI_FENCE				-8000 * WP		//�����ɂ���t�F���X�Ȃ�
#define	PRI_ANIMAL				-7000 * WP		//��������
#define	PRI_SPECIAL_BG_FRONT	-5000 * WP		//����w�i�i��������O�j
#define	PRI_GLASS				-999 * WP		//�n�ʂɐ����鑐��
#define	PRI_KIRI_BACK		    -600 * WP		//���̃O���t�B�b�N�i������j		




#define	PRI_BG_AIR				 5000 * WP		//�󒆂ɏo����Q���̋�`�i�u���b�N�Ƃ��j
#define	PRI_KIRI_BEFORE			 5500 * WP		//���̃O���t�B�N
#define	PRI_BOSS			     8000 * WP
#define	PRI_CORE_BACK			10000 * WP
#define	PRI_CORE				11000 * WP
#define	PRI_CORE_WALL			12000 * WP
#define	PRI_BOSS_COREFRONT		15000 * WP

#define	PRI_LENZ_FLERA			16000 * WP
#define	PRI_ENEMY_MIDDLE_BREAK	20000 * WP
#define	PRI_RESULECTION_EFFECT	21000 * WP
#define	PRI_TUTORIAL_MESSAGE	22000 * WP
#define	PRI_POWER_UP_MESSAGE	23000 * WP
#define	PRI_BOOST_EFFECT		24000 * WP
#define	PRI_HP_GAUGE_DISP		25000 * WP
#define	PRI_SHOT_2NDLAYER		26000 * WP
#define	PRI_BAIKIN_SMOKE		26500 * WP
#define	PRI_BAIKIN_BREAK_PER	26800 * WP
#define	PRI_SHOT_BOMB			27000 * WP
#define	PRI_MEKA_HAHEN			28000 * WP		//���J�n�̓G�̔j��
#define	PRI_GAUGE				29000 * WP		//�Q�[�W
#define	PRI_ENEMY_MIDDLE		30000 * WP		//���^�̓G
#define	PRI_WEAPON_BOMB			31000 * WP		//
#define	PRI_ENEMY				33000 * WP		//�l�b�g�o�C�L���ȂǁA���^�̓G�̕\��
#define	PRI_MOVE_POINTER		34000 * WP
#define	PRI_COREHP_INFO			37000 * WP
#define	PRI_MYCHAR_SHOT			38000 * WP		//�����̃L�����̍U��
#define	PRI_SHOTDUST			39000 * WP		//�����̃L�����̍U���̃_�X�g
#define	PRI_ITEMCHIP			40000 * WP		//�A�C�e���`�b�v
#define	PRI_MONEY				40500 * WP		//�A�C�e���`�b�v
#define	PRI_DAMAGE				40700 * WP		//�A�C�e���`�b�v
#define	PRI_MYCHAR				41000 * WP		//�����̃L����
#define	PRI_REFRECT				42000 * WP		//���t���N�^�[
#define	PRI_BALETTE				43000 * WP		//�G�̒e
#define	PRI_BALETTE_BREAK		44000 * WP		//�󂹂�G�̒e
#define	PRI_ENEMY_FRONT_MAX		45000 * WP		//��O�ɒu���G�i��O���悬��Ȃǂ̉��o�p�j
#define	PRI_KIRI				50000 * WP		//�L�����N�^�[���������x���̖�
#define	PRI_INFO_MESSAGE		60000 * WP
#define PRI_IRONPOLE_FORNT		75000 * WP
#define	PRI_KIRI_BLIND			80000 * WP
#define	PRI_MASK				81000 * WP

#define	PRI_STILL				100500 * WP


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�^�X�N�O���[�v
//------------------------------------------------------------------------------------------------------------------------------------------------------
#define	GROUP_SYSTEM_CORE				0
#define	GROUP_SYSTEM					1

