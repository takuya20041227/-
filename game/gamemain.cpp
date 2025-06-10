//------------------------------------------------------------------------------------------------------------------------------------------------------
//                systemOZ Ver3
//			�Q�[�����C���v���O����
//						programed by TEAM_TAKUYA
//------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef WINDOWS_PC
#include    "../../../libs/systemOZ_v4/soz.h"
#else
#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/town_break/src/game/game_include.h"
#include    "include.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------
//�O���ϐ���`
//------------------------------------------------------------------------------------------------------------------------------------------------------
SINT32	platform_PC = 1;
SINT32	game_type = 0, game_type2 = 0, game_type3 = 0, game_mode = 0, game_type_old = 0;	//�Q�[���̐i�s�x
FLOAT   z_box[ WINDOW_HEIGHT_HALF ];        //��ʂ̃}�b�N�X�l
ANGLE   mouse_ang_box[ WINDOW_WIDTH_HALF ]; //field�@of view�Ɠ����p�x�������Ă�( �Ж�45�x )


PARTS_RECT human_rect[]=
{
    {  369,     1,   286,   510,   143,   255 },
};


PARTS_RECT hito_rect[] =                    //��`
{
    { 0, 0, 128, 128, 64, 64 },
};


//---------------------------------------------------------------------------------
//�}�E�X�̊p�x�����Ă�
//---------------------------------------------------------------------------------
void z_box_set( void )
{
    SINT32  i;
    FLOAT   z_sub, z;
    z_sub = 30000.0f / WINDOW_HEIGHT_HALF;          //�����������i�[
    z = 30000.0f;
    for( i = 0; i < WINDOW_HEIGHT_HALF; i++ )       //�c��ʂ̔����̒l����
    {
        z_box[i] = z;                               //�l�������
        z -= z_sub;                                 //�l�����Z����
    }
}


void mouse_ang_box_set( void )
{
    SINT32  i;
    ANGLE   ang_add, ang;                           //���������l�ƃ{�b�N�X�Ɋi�[����l�������Ă�
    ang_add = 0x2000 / WINDOW_WIDTH_HALF;           //�����������i�[
    ang = 0x0;
    for( i = 0; i < WINDOW_WIDTH_HALF; i++ )        //����ʂ̔����̒l����
    {
        mouse_ang_box[i] = ang;                     //0�x����l�������
        ang += ang_add;                             //�l�����Z����
    }
}



void replay_exec( TASK *ap )
{
    SINT32 key_box[] = { DIK_A, DIK_W, DIK_S, DIK_D };	//
    SINT32 i, index;
    ap->TIMER++;
    index = 0;
    for( i = 0; i < 4; i++ )
        if( SOZ_Inkey_DAT( key_box[i] ) != 0 )
            index++;

    for( i = 0; i < 3; i++ )
        if( SOZ_Mouse_Button( i ) == 1 )
            index++;

    if( index != 0 )
        ap->TIMER = RESET;

    if( ap->TIMER >= TIME_S * 20 )
    {
        record_fram = 0;
        game_type = 500;
        TASK_all_init();
        return;
    }
}

void replay_start( void )
{
    TASK *ap;
    ap = TASK_start( replay_exec, MANE_GROUP, "���v���C�ɔ�΂�" );
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//   ���C�����[�`��		1/60�b�Ɉ��Ă΂�Ă���
//------------------------------------------------------------------------------------------------------------------------------------------------------
void GAMEMAIN_Routine( void )
{
    SINT32 key_box[] = { DIK_A, DIK_W, DIK_S, DIK_D, DIK_Z, DIK_X, DIK_C };
    switch( game_type )
    {
		case 0:
            object_sphire_init();                                       //�X�t�B�A�����ׂď�����
            z_box_set();                                                //��x�����Z�b�g
            mouse_ang_box_set();
            se_load();                                                  //���ʉ���ǂݍ���
            //�Ȃ̍Đ�
            SOZ_Music_Load( 1 , "grp/bgm/game_main" , 1 );
            SOZ_set_fog_param( 0xffffffff, 0.0f, 30000.0f, 0.1f );
            game_type = 10;                                             //�^�C�g�����
#if KAWAGUCHI
            game_type = 10;                                             //�^�C�g�����
            //game_type = 100;                                          //�Q�[�����
            //game_type = 500;
            //game_type = 1000;                                         //�Q�[����ʂ̃G�f�B�^�[
            //game_type = 2000;                                         //�^�C�g���̃G�f�B�^�[
			break;
#endif
        case 1:
            //�����Ȃ�
           break;

//------------------------�^�C�g�����-------------------------------//
        case 10:                                                        //�^�C�g�����
//�t�@�C���̓ǂݍ��݂�}�E�X�ʒu�̐ݒ�
            record_mane_start();
            SOZ_Music_Stop( 1 );
            SetCursorPos( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 );        //�ŏ��Ƀ}�E�X�𒆐S�Ɉړ�������
            tex_game_reset();                                           //�Q�[���{�҂Ŏg��
            model_game_reset();                                         //
            tex_title_load();                                           //�e�N�X�`���[�̃��[�h
            model_title_load();                                         //���f���̃��[�h
            sequence_read( "data/title.bn", sequence_box );             //�V�[�P���X��ǂݍ���
            select_and_page_read( "data/hi_score_data.bn", &hi_score );	//�X�R�A�̓ǂݍ���
            score = RESET;                                              //�X�R�A��������

//�^�X�N�𔭐�������
            socre_start( 32.0f, 72.0f, 1.2f, &hi_score );
            sequence_set_object_start();                                //�V�[�P���X�ŃI�u�W�F�N�g���o��
            ground_start( TEX_UFO_GROUND );                             //�n��
            sky_start( MODEL_UFO_ROOM, TEX_UFO_ROOM, 4000.0f,1.0f, 1.0f, 1.0f );        //UFO�̒�
            main_computer_start();
            jiki_start();                                               //
            camera_control_start();                                     //�J�����̃R���g���[��
            mouse_get_cursor_start();
            title_logo_start();
            common_ui_set();
            game_start_purpose_start();
            icon_set();
            icon_box_check_start();
            score_board_start( JIKI_X, JIKI_Y, 15000.0f );
            icon_box_check_start();
            replay_start();
            record_fram = 0;
            object_id = 0;
            catch_switch = RESET;                                       //���݂�������
            game_type++;
            break;

        case 11:
             SOZ_viewclip_maker( 0 );
            //�����Ȃ�
           break;

//-----------------------------�Q�[�����---------------------------//
        case 100:                                                       //�Q�[���{��
//�t�@�C���̓ǂݍ��݂�}�E�X�ʒu�̐ݒ�
            SetCursorPos( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 );        //�ŏ��Ƀ}�E�X�𒆐S�Ɉړ�������
            tex_game_load();                                            //�e�N�X�`���[�̃��[�h
            model_game_load();                                          //���f���̃��[�h
            sequence_read( "data/game_map.bn", sequence_box );          //�V�[�P���X��ǂݍ���
            sequence_set_object_start();                                //�V�[�P���X�ŃI�u�W�F�N�g���o��
            select_and_page_read( "data/hi_score_data.bn", &hi_score );	//�X�R�A�̓ǂݍ���
            score = RESET;                                              //�X�R�A��������

//�f�o�b�O
#if DEBUG
            particle_num_start();                                       //�p�[�e�B�N���̐����m�F
            viwe_clip_num_start();                                      //������J�����O�̐����m�F
#endif

//�Ȃ̍Đ�
            SOZ_Music_Load( 1 , "grp/bgm/game_main" , 1 );

//�^�X�N�𔭐�������
            record_mane_start();
            socre_start( 32.0f, 52.0f, 1.2f, &score );
            socre_start( 32.0f, 128.0f, 1.2f, &hi_score );
            mouse_get_cursor_start();
            //object_select_start( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 3 );
            jiki_start();                                               //
            camera_control_start();                                     //�J�����̃R���g���[��
            main_bill_start();                                          //���C���̃r��
            ground_start( TEX_GROUND );                                 //�n��
            sky_start( MODEL_SKY, TEX_SKY, -256.0f, 1.0f, 3.0f, 1.0f );                                                //��̃h�[��
            move_car_start( 2 );                                        //����
            common_ui_set();
            main_bill_hp_start();
            show_game_goal_start();
            timer_start();
            icon_set();
            icon_box_check_start();
            particle_safety_start();
            object_id = 0;
            //sphire_debug_start();                                    //�X�t�B�A�̉~������������(������
            catch_switch = RESET;                                       //���݂�������
            game_type++;
            break;

        case 101:
            SOZ_set_light_pos( camera_x[0], camera_y[0], camera_z[0], 25000, GROUND, 25000 );         //���C�e�B���O��ݒ�
            SOZ_viewclip_maker( 0 );
            //�����Ȃ�
            break;

//-----------------------------�Q�[���N���A---------------------------//
        case 110:
            mobu_ufo_generator_start();                                 //UFO���o������
            title_return_start( TIME_S + 30 );                          //�L�[���Ȃɂ������ƃ^�C�g����ʂɍs��
            dimension_write_the_file( "data/record.br", jiki_record, sizeof( RECORD ), TIME_M * 3 +1 );
            game_type++;                                                //���Ɉړ�
            break;

        case 111:
             SOZ_set_light_pos( camera_x[0], camera_y[0], camera_z[0], 25000, GROUND, 25000 );         //���C�e�B���O��ݒ�
             SOZ_viewclip_maker( 0 );
            break;

//-------------------------- �Q�[���I�[�o�[ --------------------------//
        case 120:
            game_ovre_start();                                          //�w�������ł���
            title_return_start( TIME_S + 30 );                                   //�L�[���Ȃɂ������ƃ^�C�g����ʂɍs��
            dimension_write_the_file( "data/record.br", jiki_record, sizeof( RECORD ), TIME_M * 3 +1 );
            game_type++;                                                //���Ɉړ�
            break;

        case 121:
            SOZ_set_light_pos( camera_x[0], camera_y[0], camera_z[0], 25000, GROUND, 25000 );         //���C�e�B���O��ݒ�
            SOZ_viewclip_maker( 0 );
            break;

        case 500:
            //�t�@�C���̓ǂݍ��݂�}�E�X�ʒu�̐ݒ�
            dimension_read_the_file( "data/record.br", jiki_record, sizeof( RECORD ), TIME_M * 3 +1 );
            SetCursorPos( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 );        //�ŏ��Ƀ}�E�X�𒆐S�Ɉړ�������
            tex_game_load();                                            //�e�N�X�`���[�̃��[�h
            model_game_load();                                          //���f���̃��[�h
            tex_title_load();                                           //�e�N�X�`���[�̃��[�h
            model_title_load();                                         //���f���̃��[�h
            sequence_read( "data/game_map.bn", sequence_box );          //�V�[�P���X��ǂݍ���
            sequence_set_object_start();                                //�V�[�P���X�ŃI�u�W�F�N�g���o��
            select_and_page_read( "data/hi_score_data.bn", &hi_score );	//�X�R�A�̓ǂݍ���
            score = RESET;                                              //�X�R�A��������
//�Ȃ̍Đ�
            SOZ_Music_Load( 1 , "grp/bgm/game_main" , 1 );

//�^�X�N�𔭐�������
            socre_start( 32.0f, 52.0f, 1.2f, &score );
            socre_start( 32.0f, 128.0f, 1.2f, &hi_score );
            //object_select_start( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 3 );
            jiki_start();                                               //
            camera_control_start();                                     //�J�����̃R���g���[��
            main_bill_start();                                          //���C���̃r��
            ground_start( TEX_GROUND );                                 //�n��
            sky_start( MODEL_SKY, TEX_SKY, -256.0f, 1.0f, 3.0f, 1.0f );                                                //��̃h�[��
            move_car_start( 2 );                                        //����
            common_ui_set();
            main_bill_hp_start();
            show_game_goal_start();
            timer_start();
            icon_set();
            icon_box_check_start();
            particle_safety_start();
            record_mane_start();
            object_id = 0;
            //sphire_debug_start();                                    //�X�t�B�A�̉~������������(������
            catch_switch = RESET;                                       //���݂�������
            game_type++;
            break;

        case 501:
            SINT32 i, index;
            index = 0;
            for( i = 0; i < 7; i++ )
                if( SOZ_Inkey_TRG( key_box[ i ] ) != 0 )
                    index++;
            for( i = 0; i < 3; i++ )
                if( SOZ_Mouse_Button( i ) == 1 )
                    index++;

            if( index != 0 || rp->pos[X] == 0.0f )
            {
                game_type = 10;
                TASK_all_init();
                return;
            }

             SOZ_set_light_pos( camera_x[0], camera_y[0], camera_z[0], 25000, GROUND, 25000 );         //���C�e�B���O��ݒ�
             SOZ_viewclip_maker( 0 );
            break;
        case 1000:                                                      //�Q�[����ʂ̃G�f�B�^�[
//------�f�[�^�����[�h                                                 
            select_and_page_read( "data/select_data.bn", &select_no );	//�Z���N�g��ǂݍ���
			select_and_page_read( "data/page_data.bn", &page );		    //�y�[�W��ǂݍ���
            sequence_read( "data/" SAVE_FILE ".bn", sequence_box );     //�V�[�P���X��ǂݍ���
            tex_title_load();                                           //�e�N�X�`���[�̃��[�h
            model_title_load();                                         //���f���̃��[�h
            tex_game_load();                                            //�e�N�X�`���[�̃��[�h
            model_game_load();                                          //���f���̃��[�h
//------�^�X�N�֌W
            model_name_start();                                         //���f���̖��O���o��
            sequence_set_object_start();                                //�V�[�P���X�ŃI�u�W�F�N�g���o��
            mouse_get_cursor_start();                                   //�J�[�\������ɓ����
            object_editor_start();                                      //�G�f�B�^�[
            camera_control_start();                                     //�J�����̃R���g���[��
            main_bill_start();                                          //���C���̃r��
            ground_start( TEX_GROUND );                     //�n��    
            sky_start( MODEL_SKY, TEX_SKY, -256.0f, 1.0f, 3.0f, 1.0f );          //��̃h�[��
            move_car_start( 1 );                                        //����
            record_mane_start();
            //seq_delete( 18 );
            //sphire_debug_start();                                       //�X�t�B�A�̉~������������(������
            game_type++;
            break;

        case 1001:
            SOZ_viewclip_maker( 0 );
            arrow_check();                                              //���t���[�����ׂ�
            break;

        case 2000:
             select_and_page_read( "data/select_data.bn", &select_no );	//�Z���N�g��ǂݍ���
			select_and_page_read( "data/page_data.bn", &page );		    //�y�[�W��ǂݍ���
            sequence_read( "data/" SAVE_FILE ".bn", sequence_box );           //�V�[�P���X��ǂݍ���
            tex_title_load();                 //�e�N�X�`���[�̃��[�h
            model_title_load();               //���f���̃��[�h
            tex_game_load();                                            //�e�N�X�`���[�̃��[�h
            model_game_load();                                          //���f���̃��[�h
            //------�^�X�N�֌W
            model_name_start();                                         //���f���̖��O���o��
            sequence_set_object_start();                                //�V�[�P���X�ŃI�u�W�F�N�g���o��
            mouse_get_cursor_start();                                   //�J�[�\������ɓ����
            object_editor_start();                                      //�G�f�B�^�[
            camera_control_start();                                     //�J�����̃R���g���[��
            ground_start( TEX_UFO_GROUND );                 //�n��
            sky_start( MODEL_UFO_ROOM, TEX_UFO_ROOM, 15000.0f, 1.0f, 1.0f, 1.0f );                       //UFO�̒�
            main_computer_start();
            //sphire_debug_start();                                       //�X�t�B�A�̉~������������(������
            game_type++;
            break;

        case 2001:
            arrow_check();                                              //���t���[�����ׂ�
            break;
    }
    game_type_old = game_type;
}

