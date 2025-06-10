//------------------------------------------------------------------------------------------------------------------------------------------------------
//                systemOZ Ver3
//			ゲームメインプログラム
//						programed by TEAM_TAKUYA
//------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef WINDOWS_PC
#include    "../../../libs/systemOZ_v4/soz.h"
#else
//#include    "D:/project/guardians_2dx/proj.win32/src/systemOZ/soz.h"
#endif

#include    "C:/project/town_break/src/game/game_include.h"
#include    "include.h"


//----------------------------------------------------------------------------------------------------
//シーケンスを解読してマップに設置する
//----------------------------------------------------------------------------------------------------
void object_seq_set( TASK *ap )
{
	SINT32	id;
	FLOAT	x, y, z, scale, magni_hp, magni_atk;
	ANGLE	ang_x, ang_y;
	x = *ap->f_table++;						//横の座標を取り出す
	y = *ap->f_table++;						//縦の座標を取り出す
	z = *ap->f_table++;						//前後の座標を取り出す
	ang_x = ( ANGLE )*ap->f_table++;		//角度を入れるを取り出す
	ang_y = ( ANGLE )*ap->f_table++;		//角度を入れるを取り出す
	scale = *ap->f_table++;					//サイズを取り出す
	magni_hp  = *ap->f_table++;				//ヒットポイントの倍率を取り出す
	magni_atk = *ap->f_table++;				//攻撃の倍率を取り出す
	id = ( SINT32 )*ap->f_table++;			//識別番号を取り出す
	object_start( x, y, z, ang_x, ang_y, scale, magni_hp, magni_hp, id );	//ビル
}

void car_seq_set( TASK *ap )
{
	SINT32	id;								//識別番号の変数
	FLOAT	x, y, z, scale, magni_hp, magni_atk;	//座標とサイズと倍率の変数
	ANGLE	ang_x, ang_y;					//角度の変数
	//id = ( SINT32 )*ap->f_table++;		//識別番号を取り出す
	x = *ap->f_table++;						//横の座標を取り出す
	y = *ap->f_table++;						//縦の座標を取り出す
	z = *ap->f_table++;						//前後の座標を取り出す
	ang_x = ( ANGLE )*ap->f_table++;		//角度を入れるを取り出す
	ang_y = ( ANGLE )*ap->f_table++;		//角度を入れるを取り出す
	scale = *ap->f_table++;					//サイズを取り出す
	magni_hp  = *ap->f_table++;				//ヒットポイントの倍率を取り出す
	magni_atk = *ap->f_table++;				//攻撃の倍率を取り出す
	id = ( SINT32 )*ap->f_table++;			//識別番号を取り出す
	car_start( x, y, z, ang_x, ang_y, scale, magni_hp, magni_hp, id );		//車
}


void parking_seq_set( TASK *ap )
{
	SINT32	id;								//識別番号の変数
	FLOAT	x, y, z, scale, magni_hp, magni_atk;	//座標とサイズと倍率の変数
	ANGLE	ang_x, ang_y;					//角度の変数
	//id = ( SINT32 )*ap->f_table++;		//識別番号を取り出す
	x = *ap->f_table++;						//横の座標を取り出す
	y = *ap->f_table++;						//縦の座標を取り出す
	z = *ap->f_table++;						//前後の座標を取り出す
	ang_x = ( ANGLE )*ap->f_table++;		//角度を入れるを取り出す
	ang_y = ( ANGLE )*ap->f_table++;		//角度を入れるを取り出す
	scale = *ap->f_table++;					//サイズを取り出す
	magni_hp  = *ap->f_table++;				//ヒットポイントの倍率を取り出す
	magni_atk = *ap->f_table++;				//攻撃の倍率を取り出す
	id = ( SINT32 )*ap->f_table++;			//識別番号を取り出す
	parking_start( x, y, z, ang_x, ang_y, scale, magni_hp, magni_hp, id );		//車
}

void heri_seq_set( TASK *ap )
{
	SINT32	id;								//識別番号の変数
	FLOAT	x, y, z, scale, magni_hp, magni_atk;	//座標とサイズと倍率の変数
	ANGLE	ang_x, ang_y;					//角度の変数
	//id = ( SINT32 )*ap->f_table++;		//識別番号を取り出す
	x = *ap->f_table++;						//横の座標を取り出す
	y = *ap->f_table++;						//縦の座標を取り出す
	z = *ap->f_table++;						//前後の座標を取り出す
	ang_x = ( ANGLE )*ap->f_table++;		//角度を入れるを取り出す
	ang_y = ( ANGLE )*ap->f_table++;		//角度を入れるを取り出す
	scale = *ap->f_table++;					//サイズを取り出す
	magni_hp  = *ap->f_table++;				//ヒットポイントの倍率を取り出す
	magni_atk = *ap->f_table++;				//攻撃の倍率を取り出す
	id = ( SINT32 )*ap->f_table++;			//識別番号を取り出す
	heri_start( x, y, z, ang_x, ang_y, scale, magni_hp, magni_hp, id );		//車
}


//----------------------------------------------------------------------------------------------------
//シーケンスを解読してマップに設置する
//----------------------------------------------------------------------------------------------------
void sequence_set_object_exec( TASK *ap )
{
	if( *ap->f_table != NULL )
		switch( ( SINT32 )*ap->f_table++ )							//シーケンスの中からケースを取得する
		{
			case 1:	 case 8: case 9: case 10:case 11: case 12: case 13: case 14: case 15: case 18:
				object_seq_set( ap );	break;						//オブジェクト

			case 2: case 3: case 4:	case 5: case 6: case 7:
				car_seq_set( ap );		break;						//車( 緑, 白, 黒 )

			case 16:
				parking_seq_set( ap );	break;

			case 17:
				heri_seq_set( ap );		break;
		}

	if( *ap->f_table == -999 )
		TASK_end( ap );
}

void sequence_set_object_start( void )
{
	TASK* ap;
	ap = TASK_start( sequence_set_object_exec, MANE_GROUP, "マップにオブジェクトを設置" );
	ap->f_table = sequence_box;			//シーケンス
}


