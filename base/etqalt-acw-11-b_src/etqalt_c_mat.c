/* etqalt-pcw00-1100-b-M3 */
/*********************************************************************/
/*  Copyright Toyota Motor Corporation                               */
/*********************************************************************/

/*********************************************************************/
/*  オブジェクト名 | 電気負荷トルク                                  */
/*  注意事項       |【ｵﾙﾀﾏﾈｰｼﾞｬ有】                                  */
/*-------------------------------------------------------------------*/
/*     個別変更履歴 （個別変更時は以下に変更日、内容を記入すること） */
/*********************************************************************/

/*-------------------------------------------------------------------*/
/* 適合用セクション定義                                              */
/*-------------------------------------------------------------------*/
#pragma ghs section rozdata = ".mat_etqalt"

/*-------------------------------------------------------------------*/
/* ヘッダファイルのインクルード                                      */
/*-------------------------------------------------------------------*/
#include <../inc/common.h>
#include <../inc/gllib.h>
#include <engsrc/espc/ejcc.h>               /* JEFAN,JEELS2,JEELS3,JEELS4,JEPS,JEAI,JEALTCNT */
#include <engsrc/inc/elsb.h>

#include <engsrc/etranfwd/etrq/etqalt.h>

/*-------------------------------------------------------------------*/
/* コンパイラバージョン定義                                          */
/*-------------------------------------------------------------------*/
#define MK32_ID                         (0x00000040)             /* R9コンパイラを使用 */

#ifdef __GHS_VERSION_NUMBER
 #if ( ( __GHS_VERSION_NUMBER >= 201355 ) \
    && ( __GHS_VERSION_NUMBER < 201400 ) )
 #else
  #error "コンパイルされるコンパイラが異なっています。"
 #endif
#endif

/*-------------------------------------------------------------------*/
/* コンパイルSW未定義チェック                                        */
/*-------------------------------------------------------------------*/
#if !defined JEFAN
#error "JEFAN is undeclared"
#endif

#if !defined JEELS2
#error "JEELS2 is undeclared"
#endif

#if !defined JEELS3
#error "JEELS3 is undeclared"
#endif

#if !defined JEELS4
#error "JEELS4 is undeclared"
#endif

#if !defined JEPS
#error "JEPS is undeclared"
#endif

#if !defined JEAI
#error "JEAI is undeclared"
#endif

#if !defined JEALTCNT
#error "JEALTCNT is undeclared"
#endif

/*-------------------------------------------------------------------*/
/* 適合定数                                                          */
/*-------------------------------------------------------------------*/
/* $$$適合定数_標準_v4.11 */
volatile const s2 s2s_etqalt_NEGD = s2g_ELSB_NE(200.);                  /* m=etqalt,lsb=(12800*2)/128/256,ofs=,unit=rpm :NE下限ｶﾞｰﾄﾞ値 */
volatile const s2 s2s_etqalt_CDECHYS = s2g_ELSB_16MS(500.);             /* m=etqalt,lsb=536870.912/128/256,ofs=,unit=ms :要求値変化経過時間 */
volatile const s2 s2s_etqalt_DLTQABSH = s2g_ELSB_TRQ(0.5);              /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :要求値偏差量判定値HI */
volatile const s2 s2s_etqalt_DLTQABSL = s2g_ELSB_TRQ(0.125);            /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :要求値偏差量判定値 */
volatile const s2 s2s_etqalt_BATINT = s2g_ELSB_BAT(12.);                /* m=etqalt,lsb=(20*2)/128/256,ofs=,unit=V :ﾊﾞｯﾃﾘ電圧初期値 */
volatile const s2 s2s_etqalt_BATB = s2g_ELSB_BAT(13.5);                 /* m=etqalt,lsb=(20*2)/128/256,ofs=,unit=V :基準電圧 */
volatile const s2 s2s_etqalt_DLGDMNL = s2g_ELSB_TRQ(0.03125);           /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :偏差小時の徐変量(減少) */
volatile const s2 s2s_etqalt_DLGDMNH = s2g_ELSB_TRQ(0.03125);           /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :偏差小時の徐変量(増加) */
volatile const s2 s2s_etqalt_DLGDMXL = s2g_ELSB_TRQ(20.);               /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :偏差大時の徐変量(減少) */
volatile const s2 s2s_etqalt_DLGDMXH = s2g_ELSB_TRQ(20.);               /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :偏差大時の徐変量(増加) */
/* etqalt_DLGDMNL, etqalt_DLGDMNH, etqalt_DLGDMXL, etqalt_DLGDMXHは正の値とすること */
volatile const s2 s2s_etqalt_TQNSM = s2g_ELSB_NSM(131.072/16.384);      /* m=etqalt,lsb=256/128/256,ofs=,unit=回 :ｵﾙﾀﾄﾙｸなまし定数 */
volatile const s2 s2s_etqalt_TQHYS = s2g_ELSB_TRQ(0.3);                 /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :ｵﾙﾀﾄﾙｸﾋｽ */
volatile const s2 s2s_etqalt_TQINT = s2g_ELSB_TRQ(3.);                  /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :ｵﾙﾀﾄﾙｸ初期値 */
volatile const s2 s2s_etqalt_CDECDLY = s2g_ELSB_16MS(150.);             /* m=etqalt,lsb=536870.912/128/256,ofs=,unit=ms :徐変開始ﾃﾞｨﾚｰ時間 */
volatile const s2 s2s_etqalt_DLPWR = s2g_ELSB_PWR(0.);                  /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :ﾍﾞｰｽ要求値増加判定値 */
volatile const s2 s2s_etqalt_DECRTO = s2g_glround((0.975)/(2./128./256.));  /* m=etqalt,lsb=2/128/256,ofs=,unit=倍 :徐変率 */
/* eqels_DECRTOは、時定数 640(ms)相当値としておく。 */
volatile const s2 s2s_etqalt_PWRELSGD = s2g_ELSB_PWR(1.5);              /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :電気負荷上限ｶﾞｰﾄﾞ値 */
/* 注意事項：etqalt_PWRELSGDを変更する際は、演算監視部品に影響があるため定数設定部署に確認の上で */
/* esimtqrqmnt_TQALTISCUG、esimtqrqmnt_TQALTUGも変更すること */
volatile const s2 s2s_etqalt_PWRELS = s2g_ELSB_PWR(0.);                 /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :電気負荷1 */

#if JEELS2 == u1g_EJCC_USE                                              /* 【ELS2有】 */
volatile const s2 s2s_etqalt_PWRELS2 = s2g_ELSB_PWR(0.);                /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :電気負荷2 */
#endif                                                                  /* JEELS2 */

volatile const s2 s2s_etqalt_PWRELS3 = s2g_ELSB_PWR(0.);                /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :電気負荷3 */
volatile const s2 s2s_etqalt_PWRELS4 = s2g_ELSB_PWR(0.);                /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :電気負荷4 */

#if JEELS3 == u1g_EJCC_USE                                              /* 【ELS3有】 */
volatile const s2 s2s_etqalt_PWRELSH1 = s2g_ELSB_PWR(0.);               /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :高電気負荷1 */
#endif                                                                  /* JEELS3 */

#if JEELS4 == u1g_EJCC_USE                                              /* 【ELS4有】 */
volatile const s2 s2s_etqalt_PWRELSH2 = s2g_ELSB_PWR(0.);               /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :高電気負荷2 */
#endif                                                                  /* JEELS4 */

volatile const s2 s2s_etqalt_PWRELSH3 = s2g_ELSB_PWR(0.);               /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :高電気負荷3 */
volatile const s2 s2s_etqalt_PWRELSH4 = s2g_ELSB_PWR(0.);               /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :高電気負荷4 */
volatile const s2 s2s_etqalt_PWRELSH5 = s2g_ELSB_PWR(0.);               /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :高電気負荷5 */

#if JEPS == u1g_EJCC_EPS                                                /* 【電動PS】 */
volatile const s2 s2s_etqalt_PWRELSPS = s2g_ELSB_PWR(0.19);             /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :電動ﾊﾟﾜｽﾃ負荷 */
#endif                                                                  /* JEPS */

#if JEFAN == u1g_EJCC_ONOFF_FAN                                         /* 【ON/OFF電動ﾌｧﾝ方式】 */
volatile const s2 s2s_etqalt_FANLO = s2g_ELSB_PWR(0.);                  /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :電動ﾌｧﾝLO負荷 */
volatile const s2 s2s_etqalt_FANHI = s2g_ELSB_PWR(0.);                  /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :電動ﾌｧﾝHI負荷 */
#endif                                                                  /* JEFAN */

#if JEAI == u1g_EJCC_USE                                                /* 【AI制御有】 */
volatile const s2 s2s_etqalt_PWRELSAI = s2g_ELSB_PWR(1.0);              /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :電動ｴｱﾎﾟﾝﾌﾟ負荷 */
#endif                                                                  /* JEAI */

volatile const s2 s2s_etqalt_PWRAC = s2g_ELSB_PWR(0.);                  /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :ｴｱｺﾝ負荷 */

#if JEALTCNT == u1g_EJCC_USE                                            /* 【充電制御有】 */
volatile const s2 s2s_etqalt_PWALTSOCGD = s2g_ELSB_PWR(0.8);            /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :目標電圧上昇時空気応答遅れ補正量上限ｶﾞｰﾄﾞ値 */
volatile const s2 s2s_etqalt_CASTALTDLY = s2g_ELSB_16MS(2000.);         /* m=etqalt,lsb=536870.912/128/256,ofs=,unit=ms :始動後時間判定値 */
volatile const s2 s2s_etqalt_DECALT = s2g_ELSB_PWR(0.015);              /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :目標電圧上昇時空気応答遅れ減衰量 */
#endif                                                                  /* JEALTCNT */

volatile const s2 s2s_etqalt_BATNSM = s2g_ELSB_NSM(131.072/65.536);     /* m=etqalt,lsb=256/128/256,ofs=,unit=回 :ﾊﾞｯﾃﾘ電圧なまし定数 */
volatile const s2 s2s_etqalt_ALTISM = s2g_ELSB_NSM(65.536/16.384);      /* m=etqalt,lsb=256/128/256,ofs=,unit=回 :励磁電流負荷急変時なまし回数(LIN) */
volatile const s2 s2s_etqalt_IFINT = s2g_glround((1.0)/(12.8/128./256.));   /* m=etqalt,lsb=12.8/128/256,ofs=,unit=A :ｵﾙﾀ励磁電流初期値 */
volatile const u1 u1s_etqalt_XKNE_USE = (u1)(ON);                       /* m=etqalt,lsb=,ofs=,unit=- :回転数補正使用SW */
/* $$$適合定数_標準_v4.11 */

/*-------------------------------------------------------------------*/
/* 適合マップ                                                        */
/*-------------------------------------------------------------------*/
#pragma ghs startdata
/* $$$適合マップ_標準_v4.11 */
/*---- etqalt_ektqalt_map ------------------------------------------*/
#define X(x) (s2g_ELSB_NE(x))                                           /* m=etqalt,lsb=(12800*2)/128/256,ofs=,unit=rpm :ene_ene */
#define Y(y) (s2g_glround((y)/(12.8/128./256.)))                        /* m=etqalt,lsb=12.8/128/256,ofs=,unit=A :ealtifsm */
#define Z(z) (s2g_ELSB_BAT(z))                                          /* m=etqalt,lsb=(20*2)/128/256,ofs=,unit=V :ebattsm= */
#define W(w) (s2g_glround((w)/(8./128./256.)))                          /* m=etqalt,lsb=8/128/256,ofs=,unit=倍 : */
volatile const s2 s2s_etqalt_ektqalt_map[] =
{
    8,4,3,0,

    X(400.),X(500.),X(600.),X(800.),X(1000.),X(2000.),X(3000.),X(10000.),
    Y(3.2),Y(6.4),Y(9.6),Y(12.7),
    Z(12.5),Z(13.5),Z(14.5),

    /* Z(12.5) */
                /* X(400.), X(500.), X(600.), X(800.), X(1000.), X(2000.), X(3000.), X(10000.), */
    /* Y(3.2),  */ W(1.),   W(1.),   W(1.),   W(1.),   W(1.),    W(1.),    W(1.),    W(1.),
    /* Y(6.4),  */ W(1.),   W(1.),   W(1.),   W(1.),   W(1.),    W(1.),    W(1.),    W(1.),
    /* Y(9.6),  */ W(1.),   W(1.),   W(1.),   W(1.),   W(1.),    W(1.),    W(1.),    W(1.),
    /* Y(12.7), */ W(1.),   W(1.),   W(1.),   W(1.),   W(1.),    W(1.),    W(1.),    W(1.),

    /* Z(13.5) */
                /* X(400.), X(500.), X(600.), X(800.), X(1000.), X(2000.), X(3000.), X(10000.), */
    /* Y(3.2),  */ W(1.),   W(1.),   W(1.),   W(1.),   W(1.),    W(1.),    W(1.),    W(1.),
    /* Y(6.4),  */ W(1.),   W(1.),   W(1.),   W(1.),   W(1.),    W(1.),    W(1.),    W(1.),
    /* Y(9.6),  */ W(1.),   W(1.),   W(1.),   W(1.),   W(1.),    W(1.),    W(1.),    W(1.),
    /* Y(12.7), */ W(1.),   W(1.),   W(1.),   W(1.),   W(1.),    W(1.),    W(1.),    W(1.),

    /* Z(14.5) */
                /* X(400.), X(500.), X(600.), X(800.), X(1000.), X(2000.), X(3000.), X(10000.), */
    /* Y(3.2),  */ W(1.),   W(1.),   W(1.),   W(1.),   W(1.),    W(1.),    W(1.),    W(1.),
    /* Y(6.4),  */ W(1.),   W(1.),   W(1.),   W(1.),   W(1.),    W(1.),    W(1.),    W(1.),
    /* Y(9.6),  */ W(1.),   W(1.),   W(1.),   W(1.),   W(1.),    W(1.),    W(1.),    W(1.),
    /* Y(12.7), */ W(1.),   W(1.),   W(1.),   W(1.),   W(1.),    W(1.),    W(1.),    W(1.)
};
#undef X
#undef Y
#undef Z
#undef W

/*---- etqalt_ecaltst_map ------------------------------------------*/
#define X(x) (u1g_ELSB_THW(x))                                          /* m=etqalt,lsb=160/256,ofs=-40,unit=℃ :ethw_ethw */
#define Y(y) (u1g_ELSB_16MS(y))                                         /* m=etqalt,lsb=4194.304/256,ofs=,unit=ms :ecast */
volatile const u1 u1s_etqalt_ecaltst_map[] =
{
    7U,
    X(-30.),  X(-10.),  X(10.),   X(30.),   X(50.), X(70.), X(90.),
    Y(1000.), Y(1000.), Y(1000.), Y(1000.), Y(0.),  Y(0.),  Y(0.)
};
#undef X
#undef Y

#if JEFAN == u1g_EJCC_PWM_FAN                                           /* 【PWM電動ﾌｧﾝ方式】 */
/*---- etqalt_epwrfan_map ------------------------------------------*/
#define X(x) ((u1)(((x)/(20./256.))+0.5))                               /* m=etqalt,lsb=20/256,ofs=,unit=V :afanif_get_voltage() */
#define Y(y) ((u1)(((y)/(16./256.))+0.5))                               /* m=etqalt,lsb=16/256,ofs=,unit=kW :t_pwrfan */
volatile const u1 u1s_etqalt_epwrfan_map[] =                            /* 【PWM電動ﾌｧﾝ方式】 */
{
    4U,
    X(0.), X(4.), X(8.), X(12.),
    Y(0.), Y(0.), Y(0.), Y(0.)
};
#undef X
#undef Y

#endif                                                                  /* JEFAN */

#if JEALTCNT == u1g_EJCC_USE                                            /* 【充電制御有】 */
/*---- etqalt_epwaltsocb_map ---------------------------------------*/
#define X(x) ((u1)(((x)/(16./256.))+0.5))                               /* m=etqalt,lsb=16/256,ofs=,unit=kW :epwralt */
#define Y(y) ((u1)(((y)/(4./256.))+0.5))                                /* m=etqalt,lsb=4/256,ofs=,unit=kW :epwaltsocb */
volatile const u1 u1s_etqalt_epwaltsocb_map[] =                         /* 【充電制御有】 */
{
    6U,
    X(0.6), X(0.8), X(1.),  X(1.2), X(1.4), X(1.6),
    Y(0.8), Y(0.8), Y(0.8), Y(0.4), Y(0.2), Y(0.)
};
#undef X
#undef Y

#endif                                                                  /* JEALTCNT */

/*---- etqalt_eifint_map -------------------------------------------*/
#define X(x) (s2g_ELSB_THW(x))                                          /* m=etqalt,lsb=(160*128)/128/256,ofs=,unit=℃ :ethw_ethwst */
#define Y(y) (s2g_glround((y)/(12.8/128./256.)))                        /* m=etqalt,lsb=12.8/128/256,ofs=,unit=A :ealtifsm */
volatile const s2 s2s_etqalt_eifint_map[] =
{
    7,0,
    X(-30.), X(-10.), X(10.), X(20.), X(50.), X(70.), X(90.),
    Y(1.),   Y(1.),   Y(1.),  Y(1.),  Y(1.),  Y(1.),  Y(1.)
};
#undef X
#undef Y

/* $$$適合マップ_標準_v4.11 */
#pragma ghs enddata

/**** End of File ****************************************************/
