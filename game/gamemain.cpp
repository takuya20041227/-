//------------------------------------------------------------------------------------------------------------------------------------------------------
//                systemOZ Ver3
//			ゲームメインプログラム
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
//外部変数定義
//------------------------------------------------------------------------------------------------------------------------------------------------------
SINT32	platform_PC = 1;
SINT32	game_type = 0, game_type2 = 0, game_type3 = 0, game_mode = 0, game_type_old = 0;	//ゲームの進行度
FLOAT   z_box[ WINDOW_HEIGHT_HALF ];        //画面のマックス値
ANGLE   mouse_ang_box[ WINDOW_WIDTH_HALF ]; //field　of viewと同じ角度が入ってる( 片面45度 )


PARTS_RECT human_rect[]=
{
    {  369,     1,   286,   510,   143,   255 },
};


PARTS_RECT hito_rect[] =                    //矩形
{
    { 0, 0, 128, 128, 64, 64 },
};


//---------------------------------------------------------------------------------
//マウスの角度を入れてた
//---------------------------------------------------------------------------------
void z_box_set( void )
{
    SINT32  i;
    FLOAT   z_sub, z;
    z_sub = 30000.0f / WINDOW_HEIGHT_HALF;          //割った数を格納
    z = 30000.0f;
    for( i = 0; i < WINDOW_HEIGHT_HALF; i++ )       //縦画面の半分の値を回す
    {
        z_box[i] = z;                               //値をいれる
        z -= z_sub;                                 //値を減算する
    }
}


void mouse_ang_box_set( void )
{
    SINT32  i;
    ANGLE   ang_add, ang;                           //分割した値とボックスに格納する値が入ってる
    ang_add = 0x2000 / WINDOW_WIDTH_HALF;           //割った数を格納
    ang = 0x0;
    for( i = 0; i < WINDOW_WIDTH_HALF; i++ )        //横画面の半分の値を回す
    {
        mouse_ang_box[i] = ang;                     //0度から値をいれる
        ang += ang_add;                             //値を加算する
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
    ap = TASK_start( replay_exec, MANE_GROUP, "リプレイに飛ばす" );
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//   メインルーチン		1/60秒に一回呼ばれている
//------------------------------------------------------------------------------------------------------------------------------------------------------
void GAMEMAIN_Routine( void )
{
    SINT32 key_box[] = { DIK_A, DIK_W, DIK_S, DIK_D, DIK_Z, DIK_X, DIK_C };
    switch( game_type )
    {
		case 0:
            object_sphire_init();                                       //スフィアをすべて初期化
            z_box_set();                                                //一度だけセット
            mouse_ang_box_set();
            se_load();                                                  //効果音を読み込む
            //曲の再生
            SOZ_Music_Load( 1 , "grp/bgm/game_main" , 1 );
            SOZ_set_fog_param( 0xffffffff, 0.0f, 30000.0f, 0.1f );
            game_type = 10;                                             //タイトル画面
#if KAWAGUCHI
            game_type = 10;                                             //タイトル画面
            //game_type = 100;                                          //ゲーム画面
            //game_type = 500;
            //game_type = 1000;                                         //ゲーム画面のエディター
            //game_type = 2000;                                         //タイトルのエディター
			break;
#endif
        case 1:
            //何もなし
           break;

//------------------------タイトル画面-------------------------------//
        case 10:                                                        //タイトル画面
//ファイルの読み込みやマウス位置の設定
            record_mane_start();
            SOZ_Music_Stop( 1 );
            SetCursorPos( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 );        //最初にマウスを中心に移動させる
            tex_game_reset();                                           //ゲーム本編で使う
            model_game_reset();                                         //
            tex_title_load();                                           //テクスチャーのロード
            model_title_load();                                         //モデルのロード
            sequence_read( "data/title.bn", sequence_box );             //シーケンスを読み込み
            select_and_page_read( "data/hi_score_data.bn", &hi_score );	//スコアの読み込み
            score = RESET;                                              //スコアを初期化

//タスクを発生させる
            socre_start( 32.0f, 72.0f, 1.2f, &hi_score );
            sequence_set_object_start();                                //シーケンスでオブジェクトを出す
            ground_start( TEX_UFO_GROUND );                             //地面
            sky_start( MODEL_UFO_ROOM, TEX_UFO_ROOM, 4000.0f,1.0f, 1.0f, 1.0f );        //UFOの中
            main_computer_start();
            jiki_start();                                               //
            camera_control_start();                                     //カメラのコントロール
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
            catch_switch = RESET;                                       //つかみを初期化
            game_type++;
            break;

        case 11:
             SOZ_viewclip_maker( 0 );
            //何もなし
           break;

//-----------------------------ゲーム画面---------------------------//
        case 100:                                                       //ゲーム本編
//ファイルの読み込みやマウス位置の設定
            SetCursorPos( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 );        //最初にマウスを中心に移動させる
            tex_game_load();                                            //テクスチャーのロード
            model_game_load();                                          //モデルのロード
            sequence_read( "data/game_map.bn", sequence_box );          //シーケンスを読み込み
            sequence_set_object_start();                                //シーケンスでオブジェクトを出す
            select_and_page_read( "data/hi_score_data.bn", &hi_score );	//スコアの読み込み
            score = RESET;                                              //スコアを初期化

//デバッグ
#if DEBUG
            particle_num_start();                                       //パーティクルの数を確認
            viwe_clip_num_start();                                      //視錐台カリングの数を確認
#endif

//曲の再生
            SOZ_Music_Load( 1 , "grp/bgm/game_main" , 1 );

//タスクを発生させる
            record_mane_start();
            socre_start( 32.0f, 52.0f, 1.2f, &score );
            socre_start( 32.0f, 128.0f, 1.2f, &hi_score );
            mouse_get_cursor_start();
            //object_select_start( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 3 );
            jiki_start();                                               //
            camera_control_start();                                     //カメラのコントロール
            main_bill_start();                                          //メインのビル
            ground_start( TEX_GROUND );                                 //地面
            sky_start( MODEL_SKY, TEX_SKY, -256.0f, 1.0f, 3.0f, 1.0f );                                                //空のドーム
            move_car_start( 2 );                                        //回る車
            common_ui_set();
            main_bill_hp_start();
            show_game_goal_start();
            timer_start();
            icon_set();
            icon_box_check_start();
            particle_safety_start();
            object_id = 0;
            //sphire_debug_start();                                    //スフィアの円を可視化させる(未実装
            catch_switch = RESET;                                       //つかみを初期化
            game_type++;
            break;

        case 101:
            SOZ_set_light_pos( camera_x[0], camera_y[0], camera_z[0], 25000, GROUND, 25000 );         //ライティングを設定
            SOZ_viewclip_maker( 0 );
            //何もなし
            break;

//-----------------------------ゲームクリア---------------------------//
        case 110:
            mobu_ufo_generator_start();                                 //UFOが出現する
            title_return_start( TIME_S + 30 );                          //キーをなにか押すとタイトル画面に行く
            dimension_write_the_file( "data/record.br", jiki_record, sizeof( RECORD ), TIME_M * 3 +1 );
            game_type++;                                                //次に移動
            break;

        case 111:
             SOZ_set_light_pos( camera_x[0], camera_y[0], camera_z[0], 25000, GROUND, 25000 );         //ライティングを設定
             SOZ_viewclip_maker( 0 );
            break;

//-------------------------- ゲームオーバー --------------------------//
        case 120:
            game_ovre_start();                                          //ヘリが飛んでくる
            title_return_start( TIME_S + 30 );                                   //キーをなにか押すとタイトル画面に行く
            dimension_write_the_file( "data/record.br", jiki_record, sizeof( RECORD ), TIME_M * 3 +1 );
            game_type++;                                                //次に移動
            break;

        case 121:
            SOZ_set_light_pos( camera_x[0], camera_y[0], camera_z[0], 25000, GROUND, 25000 );         //ライティングを設定
            SOZ_viewclip_maker( 0 );
            break;

        case 500:
            //ファイルの読み込みやマウス位置の設定
            dimension_read_the_file( "data/record.br", jiki_record, sizeof( RECORD ), TIME_M * 3 +1 );
            SetCursorPos( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 );        //最初にマウスを中心に移動させる
            tex_game_load();                                            //テクスチャーのロード
            model_game_load();                                          //モデルのロード
            tex_title_load();                                           //テクスチャーのロード
            model_title_load();                                         //モデルのロード
            sequence_read( "data/game_map.bn", sequence_box );          //シーケンスを読み込み
            sequence_set_object_start();                                //シーケンスでオブジェクトを出す
            select_and_page_read( "data/hi_score_data.bn", &hi_score );	//スコアの読み込み
            score = RESET;                                              //スコアを初期化
//曲の再生
            SOZ_Music_Load( 1 , "grp/bgm/game_main" , 1 );

//タスクを発生させる
            socre_start( 32.0f, 52.0f, 1.2f, &score );
            socre_start( 32.0f, 128.0f, 1.2f, &hi_score );
            //object_select_start( WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 3 );
            jiki_start();                                               //
            camera_control_start();                                     //カメラのコントロール
            main_bill_start();                                          //メインのビル
            ground_start( TEX_GROUND );                                 //地面
            sky_start( MODEL_SKY, TEX_SKY, -256.0f, 1.0f, 3.0f, 1.0f );                                                //空のドーム
            move_car_start( 2 );                                        //回る車
            common_ui_set();
            main_bill_hp_start();
            show_game_goal_start();
            timer_start();
            icon_set();
            icon_box_check_start();
            particle_safety_start();
            record_mane_start();
            object_id = 0;
            //sphire_debug_start();                                    //スフィアの円を可視化させる(未実装
            catch_switch = RESET;                                       //つかみを初期化
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

             SOZ_set_light_pos( camera_x[0], camera_y[0], camera_z[0], 25000, GROUND, 25000 );         //ライティングを設定
             SOZ_viewclip_maker( 0 );
            break;
        case 1000:                                                      //ゲーム画面のエディター
//------データをロード                                                 
            select_and_page_read( "data/select_data.bn", &select_no );	//セレクトを読み込み
			select_and_page_read( "data/page_data.bn", &page );		    //ページを読み込み
            sequence_read( "data/" SAVE_FILE ".bn", sequence_box );     //シーケンスを読み込み
            tex_title_load();                                           //テクスチャーのロード
            model_title_load();                                         //モデルのロード
            tex_game_load();                                            //テクスチャーのロード
            model_game_load();                                          //モデルのロード
//------タスク関係
            model_name_start();                                         //モデルの名前を出す
            sequence_set_object_start();                                //シーケンスでオブジェクトを出す
            mouse_get_cursor_start();                                   //カーソルを手に入れる
            object_editor_start();                                      //エディター
            camera_control_start();                                     //カメラのコントロール
            main_bill_start();                                          //メインのビル
            ground_start( TEX_GROUND );                     //地面    
            sky_start( MODEL_SKY, TEX_SKY, -256.0f, 1.0f, 3.0f, 1.0f );          //空のドーム
            move_car_start( 1 );                                        //回る車
            record_mane_start();
            //seq_delete( 18 );
            //sphire_debug_start();                                       //スフィアの円を可視化させる(未実装
            game_type++;
            break;

        case 1001:
            SOZ_viewclip_maker( 0 );
            arrow_check();                                              //毎フレーム調べる
            break;

        case 2000:
             select_and_page_read( "data/select_data.bn", &select_no );	//セレクトを読み込み
			select_and_page_read( "data/page_data.bn", &page );		    //ページを読み込み
            sequence_read( "data/" SAVE_FILE ".bn", sequence_box );           //シーケンスを読み込み
            tex_title_load();                 //テクスチャーのロード
            model_title_load();               //モデルのロード
            tex_game_load();                                            //テクスチャーのロード
            model_game_load();                                          //モデルのロード
            //------タスク関係
            model_name_start();                                         //モデルの名前を出す
            sequence_set_object_start();                                //シーケンスでオブジェクトを出す
            mouse_get_cursor_start();                                   //カーソルを手に入れる
            object_editor_start();                                      //エディター
            camera_control_start();                                     //カメラのコントロール
            ground_start( TEX_UFO_GROUND );                 //地面
            sky_start( MODEL_UFO_ROOM, TEX_UFO_ROOM, 15000.0f, 1.0f, 1.0f, 1.0f );                       //UFOの中
            main_computer_start();
            //sphire_debug_start();                                       //スフィアの円を可視化させる(未実装
            game_type++;
            break;

        case 2001:
            arrow_check();                                              //毎フレーム調べる
            break;
    }
    game_type_old = game_type;
}

