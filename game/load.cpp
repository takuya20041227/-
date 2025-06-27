//------------------------------------------------------------------------------------------------------------------------------------------------------
//                systemOZ Ver3
//			�Q�[�����C���v���O����
//						programed by TEAM_TAKUYA
//------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef WINDOWS_PC
#include    "../../../libs/systemOZ_v4/soz.h"
#else
#include    "C:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/town_break/src/game/game_include.h"
#include    "include.h"


//-----------------------------------------------------------------------------------------------------------------------
//�ǂ��ł��g�����ʂ̃e�N�X�`���[�̐ݒ�
//-----------------------------------------------------------------------------------------------------------------------
void common_tex_load( void )
{
	SOZ_load_texture( TEX_JIKI,				"grp/jiki/ufo" );					//UFO�̎��@
	SOZ_load_texture( TEX_BEAM,				"grp/bram" );						//�r�[��
	SOZ_load_texture( TEX_HAND,				"grp/hand" );						//��
	SOZ_load_texture( TEX_UI_FONT,			"grp/ui/ui_font" );					//��������⃋�[��������������Ă�
	SOZ_load_texture( TEX_BOM,				"grp/bomb" );						//����
	SOZ_load_texture( TEX_OBJECT_ICON,		"grp/ui/object_icon" );				//�I�u�W�F�N�g�̃A�C�R��
	SOZ_load_texture( TEX_FLOWER,			"grp/flower" );						//�Ԃ̃O���t�B�b�N
}


void common_model_load(void)
{
	SOZ_load_model( MODEL_JIKI,				"grp/smd/ufo" );					//���@
	SOZ_load_model( MODEL_BEAM,				"grp/smd/Beam" );					//�r�[��
	SOZ_load_model( MODEL_HAND,				"grp/smd/hand" );					//��
	SOZ_load_model( MODEL_HAND_EFE,			"grp/smd/hand_efe" );				//��̃G�t�F�N�g���f��
}


//-----------------------------------------------------------------------------------------------------------------------
//�Q�[���{�҂Ŏg���e�N�X�`���[�̐ݒ�
//-----------------------------------------------------------------------------------------------------------------------
void tex_game_load( void )
{
	SOZ_load_texture( TEX_BILL,			"grp/map_grp/bill" );				//�r��
	SOZ_load_texture( TEX_GROUND,		"grp/map_grp/ground" );					//�n��
	SOZ_load_texture( TEX_SKY,			"grp/map_grp/sora" );					//��
	SOZ_load_texture( TEX_CAR,			"grp/car/car" );						//�΂̎�
	SOZ_load_texture( TEX_CAR_B,		"grp/car/car_b" );						//���̎�
	SOZ_load_texture( TEX_CAR_W,		"grp/car/car_w" );						//���̎�
	//SOZ_load_texture( TEX_DEBUG_PARAM,	"grp/debug_param" );					//�G�f�B�^�[�Ŏg���f�o�b�O�t�H���g�������Ă�O���t�B�b�N
	SOZ_load_texture( TEX_ROADSTAR_R,	"grp/car/roadster" );					//�Ԃ̎�
	SOZ_load_texture( TEX_ROADSTAR_B,	"grp/car/roadster_b" );					//���̎�
	SOZ_load_texture( TEX_ROADSTAR_W,	"grp/car/roadster_w" );					//���̎�
	SOZ_load_texture( TEX_TOWER,		"grp/map_grp/tower" );					//��̃^���[
	SOZ_load_texture( TEX_TENTO,		"grp/tento" );							//�e���g
	SOZ_load_texture( TEX_CAR_EFE,		"grp/car/tiya" );						//�^�C��
	SOZ_load_texture( TEX_WOOD,			"grp/map_grp/wood" );
	SOZ_load_texture( TEX_BONITO,		"grp/map_grp/bonito" );
	SOZ_load_texture( TEX_WOOD_EFE,		"grp/break_effect/wood/wood_efe" );
	SOZ_load_texture( TEX_GLAS,			"grp/break_effect/bill/glas_efe" );		//�K���X�̔j��
	SOZ_load_texture( TEX_SCHOOL,		"grp/map_grp/school" );					//�w�Z�̃O���t�B�b�N( 3D�p )
	SOZ_load_texture( TEX_LOGO_HOUSE,	"grp/map_grp/house" );					//�^�C�g�����S�̃}���V����
	SOZ_load_texture( TEX_BET,			"grp/map_grp/bet" );					//�ӂƂ�ƃx�b�g
	SOZ_load_texture( TEX_TANSU,		"grp/map_grp/tansu" );					//�^���X
	SOZ_load_texture( TEX_PARKING,		"grp/map_grp/parking" );				//���ԏ�
	SOZ_load_texture( TEX_CAT_MOUNTEN,	"grp/map_grp/cat/cat_mountain" );
	SOZ_load_texture( TEX_CAT_TYA,		"grp/map_grp/cat/cat_tya" );			//���F�̃l�R
	SOZ_load_texture( TEX_CAT_GRY,		"grp/map_grp/cat/cat_gry" );			//�D�F�̃l�R
	SOZ_load_texture( TEX_CAT_PEL,		"grp/map_grp/cat/cat_pel" );			//�y�[���̃l�R
	SOZ_load_texture( TEX_MISSILE,		"grp/missile" );						//�~�T�C��
	SOZ_load_texture( TEX_RAINDOW,		"grp/rainbow" );
	SOZ_load_texture( TEX_GAME_OVER_EFE,"grp/jiki/game_over_efe" );				//���̃O���t�B�b�N
	SOZ_load_texture( TEX_ARCHER_FISH,  "grp/map_grp/fish" );
}


//-----------------------------------------------------------------------------------------------------------------------
//�Q�[���{�҂Ŏg�����f���̐ݒ�
//-----------------------------------------------------------------------------------------------------------------------
void model_game_load( void )
{
	SOZ_load_model( MODEL_MAIN_BILL,	"grp/smd/bill" );
	SOZ_load_model( MODEL_BILL_EFE,		"grp/break_effect/bill/bill_effect" );
	SOZ_load_model( MODEL_SKY,			"grp/smd/sky" );	
	SOZ_load_model( MODEL_CAR,			"grp/smd/car" );
	SOZ_load_model( MODEL_SUB_BILL,		"grp/smd/mobu_bill" );
	SOZ_load_model( MODEL_ROADSTAR,		"grp/smd/roadster" );
	SOZ_load_model( MODEL_TOWER,		"grp/smd/tower" );
	SOZ_load_model( MODEL_TENTO,		"grp/smd/tento" );
	SOZ_load_model( MODEL_BLEAK_BILL,	"grp/break_smd/break_bill" );
	SOZ_load_model( MODEL_CAR_EFE,		"grp/smd/taiya" );							//�^�C��
	SOZ_load_model( MODEL_WOOD,			"grp/smd/wood" );
	SOZ_load_model( MODEL_BONITO,		"grp/smd/bonito" );
	SOZ_load_model( MODEL_WOOD_EFE,		"grp/break_effect/wood/wood_efe" );
	SOZ_load_model( MODEL_SCHOOL,		"grp/smd/school" );							//�w�Z
	SOZ_load_model( MODEL_SCHOOL_CHAIR,	"grp/break_effect/school/school_chair" );	//�w�Z�̃C�X
	SOZ_load_model( MODEL_SCHOOL_TABLE,	"grp/break_effect/school/school_table" );	//�w�Z�̊�
	SOZ_load_model( MODEL_BREAK_SCHOOL, "grp/break_effect/school/break_school" );	//��ꂽ�w�Z
	SOZ_load_model( MODEL_LOGO_HOUSE,	"grp/smd/logo_house" );						//�^�C�g�����S�̃}���V����
	SOZ_load_model( MODEL_BET,			"grp/break_effect/logo_house/bet" );		//�x�b�g
	SOZ_load_model( MODEL_HUTON,		"grp/break_effect/logo_house/huton" );		//�ӂƂ�
	SOZ_load_model( MODEL_TANSU,		"grp/break_effect/logo_house/tansu" );		//�^���X
	SOZ_load_model( MODEL_PARKING,		"grp/smd/parking" );						//���ԏ�
	SOZ_load_model( MODEL_CAT_MOUNTEN,	"grp/smd/cat/cat_mountain" );				//�l�R�R
	SOZ_load_model( MODEL_CAT,			"grp/smd/cat/cat" );						//�l�R�̃��f��
	SOZ_load_model( MODEL_MISSILE,		"grp/smd/missile" );						//�y�[���̃l�R
	SOZ_load_model( MODEL_HERI,			"grp/smd/heri/heri" );						//�w���{�̂̃��f��
	SOZ_load_model( MODEL_PROPELLER,	"grp/smd/heri/propeller" );					//�w���ɂ��Ă�v���y���̃��f��
	SOZ_load_model( MODEL_ARCHER_FISH,	"grp/smd//archer_fish" );					//�w���ɂ��Ă�v���y���̃��f��
}


//-----------------------------------------------------------------------------------------------------------------------
//�^�C�g���Ŏg���e�N�X�`���[�̐ݒ�
//-----------------------------------------------------------------------------------------------------------------------
void tex_title_load( void )
{	
	SOZ_load_texture( TEX_UFO_ROOM,			"grp/ufo_room" );					//UFO�̒�( �^�C�g���ł��� )
	SOZ_load_texture( TEX_COMPUTER,			"grp/ufo_room/main_computer" );		//UFO�̒�( �^�C�g���ł��� )
	SOZ_load_texture( TEX_EARTH,			"grp/ufo_room/earth" );				//�n��	
	SOZ_load_texture( TEX_UFO_GROUND,		"grp/ufo_room/ufo_ground" );		//�^�C�g���̒n��
	SOZ_load_texture( TEX_SCREEN_MEKA,		"grp/ufo_room/ufo_meka" );			//���j�^�[�t���@�B
	SOZ_load_texture( TEX_BUTTON_MEKA,		"grp/ufo_room/ufo_button" );		//�{�^���t���̋@�B
	SOZ_load_texture( TEX_TITLE,			"grp/ufo_room/town_break_title" );	//�^�C�g�����S
	SOZ_load_texture( TEX_EARTH_BREAK,		"grp/ufo_room/earth_break" );		//�Q�[���N���A��̒n��( �r�p )
	SOZ_load_texture( TEX_HERI,				"grp/heri" );						//�w���̃O���t�B�b�N
	SOZ_load_texture( TEX_ALIEN_NOMAL,		"grp/jiki/alien_nomal" );			//�ʏ��G�C���A���̃O���t�B�b�N
	SOZ_load_texture( TEX_ALIEN_SURPRISE,	"grp/jiki/alien_surprise" );		//�������G�C���A���̃O���t�B�b�N
	SOZ_load_texture( TEX_ALIEN_SMILE,		"grp/jiki/alien_smile" );			//�Ί�̃G�C���A���̃O���t�B�b�N
	SOZ_load_texture( TEX_ALIEN_SAD,		"grp/jiki/alien_sad" );				//�߂�����̃O���t�B�b�N
	SOZ_load_texture( TEX_UFO_TABLE,		"grp/ufo_room/ufo_table" );			//�e�[�u���̃O���t�B�b�N
	SOZ_load_texture( TEX_GEAR,				"grp/ufo_room/gear" );				//���F�̎��Ԃ̃O���t�B�b�N
	SOZ_load_texture( TEX_GEAR_GRY,			"grp/ufo_room/gear_gry" );			//�D�F�̎��Ԃ̃O���t�B�b�N
	SOZ_load_texture( TEX_GEAR_RED,			"grp/ufo_room/gear_red" );			//�ԐF�̎��Ԃ̃O���t�B�b�N
	SOZ_load_texture( TEX_ALIEN_WEAPON,		"grp/jiki/alien_weapon" );			//�G�C���A���̃s�X�g���̃O���t�B�b�N
	SOZ_load_texture( TEX_UFO_FOOD,			"grp/ufo_room/table_efe" );			//�G�C���A���̃s�X�g���̃O���t�B�b�N
}


//-----------------------------------------------------------------------------------------------------------------------
//�^�C�g���Ŏg�����f���̐ݒ�
//-----------------------------------------------------------------------------------------------------------------------
void model_title_load( void )
{	
	SOZ_load_model( MODEL_UFO_ROOM,			"grp/smd/ufo_room" );				//UFO�̒�( �^�C�g���ł��� )
	SOZ_load_model( MODEL_COMPUTER,			"grp/smd/main_computer" );			//�Q�[���X�^�[�g����Ƃ��Ɍ��傫�ȋ@�B
	SOZ_load_model( MODEL_SUB_PARTS,		"grp/smd/sub_parts" );				//
	SOZ_load_model( MODEL_EARTH,			"grp/smd/earth" );					//
	SOZ_load_model( MODEL_SCREEN_MEKA,		"grp/smd/meka2" );					//
	SOZ_load_model( MODEL_BUTTON_MEKA,		"grp/smd/meka1" );					//
	SOZ_load_model( MODEL_BOATD,			"grp/smd/score_board" );			//�X�R�A�{�[�h
	SOZ_load_model( MODEL_ALIEN,			"grp/smd/alien" );					//�G�C���A���̃��f��
	SOZ_load_model( MODEL_ARM_MEKA,			"grp/smd/arm_meka" );				//�A�[�����J�̃��f��
	SOZ_load_model( MODEL_GEAR,				"grp/smd/gear" );					//���Ԃ̃��f��
	SOZ_load_model( MODEL_UFO_TABLE,		"grp/smd/ufo_table" );				//�e�[�u���̃��f��
	SOZ_load_model( MODEL_UFO_CHAIR,		"grp/smd/ufo_chair" );				//�֎q�̃��f��
	SOZ_load_model( MODEL_ALIEN_WEAPON,		"grp/smd/alien_weapon" );			//�G�C���A���̃s�X�g��
	SOZ_load_model( MODEL_UFO_FOOD,			"grp/smd/ufo_table_efe" );			//�e�[�u���̃G�t�F�N�g
}


//-----------------------------------------------------------------------------------------------------------------------
//SE�̃��[�h
//-----------------------------------------------------------------------------------------------------------------------
void se_load( void )
{
	SOZ_load_se( SE_FISH,					"grp/se/fish_01" );			//���̉�
	SOZ_load_se( SE_KLAXON_1,				"grp/se/carhorn_01" );		//���̉�
	SOZ_load_se( SE_KLAXON_2,				"grp/se/carhorn_02" );		//���̉�
	SOZ_load_se( SE_BILL_BREAK,				"grp/se/bill_break_01" );	//���̉�
	SOZ_load_se( SE_PROPELLER,				"grp/se/buranko" );			//�w���̉�鉹
	SOZ_load_se( SE_HERI,					"grp/se/heri" );			//�w���̉�鉹
}




//-----------------------���[�h����Ă���̂Ŏg���Ă��Ȃ����̂�����-------------------------//
// ���������������������������������������������������������������������������������������� //

//----------------------------------------------------------------------------------------------------
//�ǂݍ���ł��e�N�X�`���[�Ŏg���Ă��Ȃ����̂�����( �^�C�g���œǂݍ��񂾂��� )
//----------------------------------------------------------------------------------------------------
void tex_title_reset( void )
{
	SOZ_release_texture( TEX_EARTH );								//�n��
	SOZ_release_texture( TEX_EARTH_BREAK );							//�r�p�����n��
	SOZ_release_texture( TEX_UFO_GROUND );							//�^�C�g���̒n��
	SOZ_release_texture( TEX_SCREEN_MEKA );
	SOZ_release_texture( TEX_BUTTON_MEKA );
	SOZ_release_texture( TEX_UFO_ROOM );
	SOZ_release_texture( TEX_COMPUTER );
	SOZ_release_texture( TEX_TITLE );			
	SOZ_release_texture( TEX_UFO_ROOM		);
	SOZ_release_texture( TEX_COMPUTER		);
	SOZ_release_texture( TEX_ALIEN_NOMAL	);
	SOZ_release_texture( TEX_ALIEN_SMILE	);
	SOZ_release_texture( TEX_ALIEN_SAD		);
	SOZ_release_texture( TEX_ALIEN_SURPRISE );
	SOZ_release_texture( TEX_ALIEN_WEAPON	);
	SOZ_release_texture( TEX_UFO_TABLE		);//
	SOZ_release_texture( TEX_GEAR			);
	SOZ_release_texture( TEX_GEAR_GRY		);
	SOZ_release_texture( TEX_GEAR_RED		);
	SOZ_release_texture( TEX_UFO_FOOD		);
	SOZ_release_texture( TEX_UFO_FOOD );
	//SOZ_release_texture(  );
}


//----------------------------------------------------------------------------------------------------
//�ǂݍ���ł����f���Ŏg���Ă��Ȃ����̂�����
//----------------------------------------------------------------------------------------------------
void model_title_reset( void )
{
	SOZ_MODEL_release( MODEL_EARTH );
	SOZ_MODEL_release( MODEL_SCREEN_MEKA );
	SOZ_MODEL_release( MODEL_BUTTON_MEKA );
	SOZ_MODEL_release( MODEL_COMPUTER );
	SOZ_MODEL_release( MODEL_BUTTON_MEKA );
	SOZ_MODEL_release( MODEL_SCREEN_MEKA );
	SOZ_MODEL_release( MODEL_ALIEN );
	SOZ_MODEL_release( MODEL_ALIEN_WEAPON );
	SOZ_MODEL_release( MODEL_ARM_MEKA );
	SOZ_MODEL_release( MODEL_UFO_CHAIR );
	SOZ_MODEL_release( MODEL_ALIEN );
	SOZ_MODEL_release( MODEL_ALIEN_WEAPON );
	SOZ_MODEL_release( MODEL_UFO_TABLE );
	SOZ_MODEL_release( MODEL_SUB_PARTS );
	SOZ_MODEL_release( MODEL_UFO_ROOM );
	//SOZ_MODEL_release(  );
}


//----------------------------------------------------------------------------------------------------
//�ǂݍ���ł����f���Ŏg���Ă��Ȃ����̂�����( �Q�[���{�҂ł�݂���ł������� )
//----------------------------------------------------------------------------------------------------
void tex_game_reset( void )
{
	SOZ_release_texture( TEX_GROUND			);				//�n��
	SOZ_release_texture( TEX_SKY			);				//��
	SOZ_release_texture( TEX_CAR			);				//�΂̎�
	SOZ_release_texture( TEX_CAR_B			);				//���̎�
	SOZ_release_texture( TEX_CAR_W			);				//���̎�
	SOZ_release_texture( TEX_DEBUG_PARAM	);				//�G�f�B�^�[�Ŏg���f�o�b�O�t�H���g�������Ă�O���t�B�b�N
	SOZ_release_texture( TEX_ROADSTAR_R		);				//�Ԃ̎�
	SOZ_release_texture( TEX_ROADSTAR_B		);				//���̎�
	SOZ_release_texture( TEX_ROADSTAR_W		);				//���̎�
	SOZ_release_texture( TEX_TOWER			);				//��̃^���[
	SOZ_release_texture( TEX_TENTO			);				//�e���g
	SOZ_release_texture( TEX_GLAS			);				//�K���X�̔j��
	SOZ_release_texture( TEX_RAINDOW		);
	SOZ_release_texture( TEX_BILL );
	SOZ_release_texture( TEX_GAME_OVER_EFE );
	//SOZ_release_texture(  );
}


//----------------------------------------------------------------------------------------------------
//�ǂݍ���ł��e�N�X�`���[�Ŏg���Ă��Ȃ����̂�����( �Q�[���{�� )
//----------------------------------------------------------------------------------------------------
void model_game_reset( void )
{
	SOZ_MODEL_release( MODEL_SKY );
	SOZ_MODEL_release( MODEL_MISSILE );
	SOZ_MODEL_release( MODEL_MAIN_BILL );
	SOZ_MODEL_release( MODEL_BLEAK_BILL );
	SOZ_MODEL_release( MODEL_SUB_BILL );
	SOZ_MODEL_release( MODEL_BONITO );
	SOZ_MODEL_release( MODEL_CAR );
	SOZ_MODEL_release( MODEL_ROADSTAR );
	SOZ_MODEL_release( MODEL_BET );
	SOZ_MODEL_release( MODEL_BREAK_SCHOOL );
	SOZ_MODEL_release( MODEL_SCHOOL );
	SOZ_MODEL_release( MODEL_SCHOOL_CHAIR );
	SOZ_MODEL_release( MODEL_SCHOOL_TABLE );
	SOZ_MODEL_release( MODEL_TANSU );
	SOZ_MODEL_release( MODEL_CAR_EFE );
	SOZ_MODEL_release( MODEL_CAT );
	SOZ_MODEL_release( MODEL_CAT_MOUNTEN );
	SOZ_MODEL_release( MODEL_HERI );
	SOZ_MODEL_release( MODEL_PROPELLER );
	SOZ_MODEL_release( MODEL_PARKING );
	SOZ_MODEL_release( MODEL_LOGO_HOUSE );
	SOZ_MODEL_release( MODEL_TENTO );
	SOZ_MODEL_release( MODEL_TOWER );
	SOZ_MODEL_release( MODEL_WOOD );
	SOZ_MODEL_release( MODEL_WOOD_EFE );
	SOZ_MODEL_release( MODEL_HUTON );
	SOZ_MODEL_release( MODEL_BILL_EFE );
	//SOZ_MODEL_release(  );
}