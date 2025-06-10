extern SINT32 object_id;									//ユニークナンバーを計測するのに使う( 初期化必須 )

extern void break_object_start( DEFAULT_ARGUMENT, FLOAT atk, SINT32 id );
extern void break_effect_occurrence( TASK *ap, FLOAT sphire );
extern void hit_particle_occurrence( TASK *ap );
extern void attack_hit_check( TASK *ap, OBJECT_DATA *op );
extern void particle_safety_start( void );
