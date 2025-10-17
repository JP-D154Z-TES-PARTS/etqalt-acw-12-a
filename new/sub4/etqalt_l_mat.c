/* etqalt-pcw00-1100-a-M4 */
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
/* ヘッダファイルのインクルード                                      */
/*-------------------------------------------------------------------*/
#include <../inc/common.h>
#include <../inc/gllib.h>
#include <engsrc/espc/ejcc.h>               /* JEALTCNT,JEFAN,JEELS2,JEELS3,JEELS4,JEPS,JEAI,JEPTCHT_E */
#include <engsrc/inc/elsb.h>
#include <engsrc/inc/elib.h>

#include <aps/cpowif.h>                     /* s2g_cpowif_b */

#if JEFAN != u1g_EJCC_NOT_USE               /*【電動ﾌｧﾝ有】*/
#include <sac/afanif.h>                     /* u1g_afanif_get_outmnt(),u1g_AFANIF_LO,u1g_AFANIF_HI */
                                            /* s2g_afanif_get_voltage() */
#endif /* JEFAN */
#if JEPS == u1g_EJCC_EPS                    /*【電動PS】*/
#include <sac/aonoffinif.h>                 /* big_apsswif_xpssw */
#endif /* JEPS */

#include <obd/wfd/wbatt_fdi.h>              /* big_wbatt_fdi_xbattClFt */

#include <yaux/yaltmng/yaltinfo.h>          /* s2g_yaltinfo_yalttrq,u1g_yaltinfo_yaltif */
#if JEALTCNT == u1g_EJCC_USE                /*【充電制御有】*/
#include <yaux/yaltmng/yaltlmp.h>           /* u1g_yaltlmp_yxbattlo */
#include <yaux/ysoc/ysocpublic.h>           /* big_ysocpublic_yxaltldinc */
#endif /* JEALTCNT */

#if JEAI == u1g_EJCC_USE                    /*【AI制御有】*/
#include <eng/eels/eai.h>                   /* big_eai_exaprly */
#endif /* JEAI */

#if JEPTCHT_E == u1g_EJCC_USE               /*【PTCﾋｰﾀ有】*/
#include <engsrc/efunc/edrblty/estblcomb/eptchctrl.h>   /* s2g_eptchctrl_epwrptc */
#endif /* JEPTCHT_E */

#include <engsrc/efunc/efuncmedi/emnet.h>   /* s2g_emnet_enet */
#include <engsrc/estate/estepin/exst.h>     /* s2g_exst_ecast_16m,u1g_exst_exastefi */
#include <engsrc/estate/estepin/exdly.h>    /* u1g_exdly_exels,u1g_exdly_exels2,u1g_exdly_exels3,u1g_exdly_exels4 */
                                            /* u1g_exdly_exelsh1,u1g_exdly_exelsh2,u1g_exdly_exelsh3,u1g_exdly_exelsh4,u1g_exdly_exelsh5 */
#include <engsrc/estate/estepin/eacstate.h> /* u1g_eacstate_exac */
#include <engsrc/estate/esin/ene.h>         /* s2g_ene_ene */

#include <engsrc/etranfwd/etemp/ethw.h>     /* u2g_ethw_emthw,s2g_ethw_ethwst */

#include <engsrc/etranfwd/etrq/etqalt.h>

/*-------------------------------------------------------------------*/
/* コンパイラバージョン定義                                          */
/*-------------------------------------------------------------------*/
#define MK32_ID                         (0x00000080)             /* M4コンパイル時使用 */

#ifdef __GHS_VERSION_NUMBER
 #if ( ( __GHS_VERSION_NUMBER >= 201714 ) \
    && ( __GHS_VERSION_NUMBER < 201800 ) )
 #else
  #error "コンパイルされるコンパイラが異なっています。"
 #endif
#endif

/*-------------------------------------------------------------------*/
/* コンパイルSW未定義チェック                                        */
/*-------------------------------------------------------------------*/
#if !defined JEALTCNT
#error "JEALTCNT is undeclared"
#endif

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

#if !defined JEPTCHT_E
#error "JEPTCHT_E is undeclared"
#endif

/*-------------------------------------------------------------------*/
/* 型定義                                                            */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* macro定義                                                         */
/*-------------------------------------------------------------------*/
/* $$$マクロ定数_標準_v4.11 */
/* $$$マクロ定数_標準_v4.11 */

/*-------------------------------------------------------------------*/
/* 変数定義                                                          */
/*-------------------------------------------------------------------*/
s2 s2g_etqalt_etqalt;               /* m=etqalt,lsb=1024/128/256,unit=Nm :現在ｵﾙﾀﾄﾙｸ */
f4 f4g_etqalt_etqalt;               /* m=etqalt,unit=Nm :現在ｵﾙﾀﾄﾙｸ */
s2 s2g_etqalt_etqaltisc[2];         /* m=etqalt,lsb=1024/128/256,unit=Nm :ISCｵﾙﾀﾄﾙｸ(0:将来)／(1:直近) */
f4 f4g_etqalt_etqaltisc[2];         /* m=etqalt,unit=Nm :ISCｵﾙﾀﾄﾙｸ(0:将来)／(1:直近) */
f4 f4g_etqalt_epwralt;              /* m=etqalt,unit=kW :ｵﾙﾀﾊﾟﾜｰ */

static s2 s2s_etqalt_ebattsm;       /* lsb=(20*2)/128/256,unit=V :ﾊﾞｯﾃﾘ電圧 */
static s2 s2s_etqalt_ealtifsm;      /* m=etqalt,lsb=12.8/128/256,unit=A :ｵﾙﾀ励磁電流 */

/* 実体定義(stflag8 sts_etqalt_flagi)は、vdg_etqalt_16msl_seq()内に定義 */
#define bis_etqalt_expwrdec    (sts_etqalt_flagi.b0)    /* 減衰実行ﾌﾗｸﾞ */
#if JEALTCNT == u1g_EJCC_USE                            /*【充電制御有】*/
#define bis_etqalt_yxaltldinco (sts_etqalt_flagi.b1)    /* ｵﾙﾀ負荷増大ﾌﾗｸﾞ前回値 */
#endif /* JEALTCNT */

/*-------------------------------------------------------------------*/
/* 関数のprototype宣言                                               */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* 関数                                                              */
/*-------------------------------------------------------------------*/
/*********************************************************************/
/*  関数名        | vdg_etqalt_pwon_seq( )                           */
/*  処理内容      | 初期化処理                                       */
/*  制御タイミング| pwon                                             */
/*  引数          | なし                                             */
/*  戻り値        | なし                                             */
/*  注意事項      |                                                  */
/*********************************************************************/
void
vdg_etqalt_pwon_seq(void)
{
    s2s_etqalt_ebattsm = s2s_etqalt_BATINT;
    s2s_etqalt_ealtifsm = s2s_etqalt_IFINT;
}

/*********************************************************************/
/*  関数名        |  vdg_etqalt_16msl_seq( )                         */
/*  処理内容      |  電気負荷トルクの算出                            */
/*  制御タイミング|  16msl                                           */
/*  引数          |  なし                                            */
/*  戻り値        |  なし                                            */
/*  注意事項      |                                                  */
/*********************************************************************/
void
vdg_etqalt_16msl_seq(void)
{
    volatile static s2 s2s_etqalt_etqalttb;      /* lsb=1024/128/256,unit=Nm :目標ｵﾙﾀﾄﾙｸﾍﾞｰｽ */
    volatile static s2 s2s_etqalt_etqaltt;       /* lsb=1024/128/256,unit=Nm :目標ｵﾙﾀﾄﾙｸ */
    volatile static s2 s2s_etqalt_ecast;         /* lsb=536870.912/128/256,unit=ms :始動後経過時間判定値 */
    volatile static s2 s2s_etqalt_epwrelsrq;     /* lsb=512/128/256,unit=kW :SW入力の電気負荷動力 */
    volatile static s2 s2s_etqalt_etqelst;       /* lsb=1024/128/256,unit=Nm :目標電気負荷ﾄﾙｸ */
    volatile static s2 s2s_etqalt_etqelstb;      /* lsb=1024/128/256,unit=Nm :目標電気負荷ﾄﾙｸﾍﾞｰｽ値 */
    volatile static s2 s2s_etqalt_epwrels;       /* lsb=512/128/256,unit=kW :電気負荷動力 */
    volatile static s2 s2s_etqalt_epwrelsrqb;    /* lsb=512/128/256,unit=kW :電気負荷動力ﾍﾞｰｽ値 */
    volatile static stflag8 sts_etqalt_flagi;    /* ﾌﾗｸﾞ構造体(時間同期低ﾀｽｸ用) */
#if JEALTCNT == u1g_EJCC_USE               /*【充電制御有】*/
    volatile static s2 s2s_etqalt_epwaltsoc;     /* lsb=512/128/256,unit=kW :目標電圧上昇時空気応答遅れ補正量 */
    volatile static s2 s2s_etqalt_epwaltsocb;    /* lsb=512/128/256,unit=kW :目標電圧上昇時空気応答遅れﾍﾞｰｽ補正量 */
#endif /* JEALTCNT */
#if JEFAN != u1g_EJCC_NOT_USE              /*【電動ﾌｧﾝ有】*/
    volatile static s2 s2s_etqalt_epwrfan;       /* lsb=512/128/256,unit=kW :電動ﾌｧﾝ電力 */
#endif /* JEFAN */

    s2 s2t_net;                            /* lsb=(12800*2)/128/256,unit=rpm :最終目標回転数 */
    s4 s4t_tqalttb;                        /* lsb=1024/128/256,unit=Nm :回転数補正ｵﾙﾀﾄﾙｸ */
    s4 s4t_tqaltt;                         /* lsb=1024/128/256,unit=Nm :目標オルタトルク */
    s4 s4t_etqalt;                         /* lsb=1024/128/256,unit=Nm :現在オルタトルク */
    s4 s4t_dltqalttb;                      /* lsb=1024/128/256,unit=Nm :目標ｵﾙﾀﾄﾙｸﾍﾞｰｽ変化量 */
    s4 s4t_tqelst;                         /* lsb=1024/128/256,unit=Nm :目標電気負荷トルク */
    s4 s4t_dltqelst;                       /* lsb=1024/128/256,unit=Nm :補正量と要求値との偏差 */
    s4 s4t_tqgdlo;                         /* lsb=1024/128/256,unit=Nm :トルク下限ガード値 */
    s4 s4t_tqgdhi;                         /* lsb=1024/128/256,unit=Nm :トルク上限ガード値 */
    s4 s4t_tqelsswrq;                      /* lsb=1024/128/256,unit=Nm :SW入力の電気負荷ﾄﾙｸ */
    s4 s4t_tqelstb;                        /* lsb=1024/128/256,unit=Nm :目標電気負荷ﾄﾙｸﾍﾞｰｽ値 */
    s4 s4t_ne;                             /* lsb=(12800*2)/128/256,unit=rpm :下限ｶﾞｰﾄﾞ後ｴﾝｼﾞﾝ回転数 */
    s4 s4t_dlpwrrqb;                       /* lsb=512/128/256,unit=kW :ﾍﾞｰｽ要求値変化量 */
    s4 s4t_pwrelsrqb;                      /* lsb=512/128/256,unit=kW :電気負荷動力ﾍﾞｰｽ値 */
    s4 s4t_pwralt;                         /* lsb=512/128/256,unit=kW :ｵﾙﾀﾊﾟﾜｰ */
    s4 s4t_epwrelsrq;                      /* lsb=512/128/256,unit=kW :SW入力の電気負荷動力 */
    s4 s4t_pwrelsrq;                       /* lsb=512/128/256,unit=kW :減衰前SW入力電気負荷動力 */
    s4 s4t_pwraltadd;                      /* lsb=512/128/256,unit=kW :ｵﾙﾀﾊﾟﾜｰ補正値 */
    s4 s4t_pwrels;                         /* lsb=512/128/256,unit=kW :電気負荷動力 */
    s2 s2t_dlgdl;                          /* lsb=(12800*2)/128/256,unit=rpm :トルク下限ガード値算出用ワーク */
    s2 s2t_dlgdh;                          /* lsb=(12800*2)/128/256,unit=rpm :トルク上限ガード値算出用ワーク */
    s2 s2t_nettq;                          /* lsb=12800/128/256,unit=rpm :トルク変換用目標回転数変換値 */
    s2 s2t_tqelsto;                        /* lsb=1024/128/256,unit=Nm :前回etqelst */
    s2 s2t_dltrqabs;                       /* lsb=1024/128/256,unit=Nm :要求値偏差量判定値 */
    s2 s2t_cast_16m;                       /* lsb=536870.912/128/256,unit=ms :始動後ｶｳﾝﾀ */
    s2 s2t_crqbchg_16m;                    /* lsb=536870.912/128/256,unit=ms :ﾍﾞｰｽ要求値変化ｶｳﾝﾀ */
    s2 s2t_pwrelsrqbo;                     /* lsb=512/128/256,unit=kW :電気負荷動力ﾍﾞｰｽ値前回値 */
    s2 s2t_battsm;                         /* lsb=(20*2)/128/256,unit=V :ﾊﾞｯﾃﾘ電圧 */
    s2 s2t_altifsm;                        /* lsb=12.8/128/256,unit=A :ｵﾙﾀ励磁電流 */
    s2 s2t_altifsmo;                       /* lsb=12.8/128/256,unit=A :ｵﾙﾀ励磁電流前回値 */
    s2 s2t_ktqalt;                         /* lsb=8/128/256,unit=倍 :ｵﾙﾀﾄﾙｸ補正係数 */
    s2 s2t_cast;                           /* lsb=536870.912/128/256,unit=ms :始動後経過時間判定値 */
    s2 s2t_ne_l;                           /* lsb=(12800*2)/128/256,unit=rpm :ｴﾝｼﾞﾝ回転数 */
    s2 s2t_etqalttb;                       /* lsb=1024/128/256,unit=Nm :目標ｵﾙﾀﾄﾙｸﾍﾞｰｽ値 */
    u2 u2t_cast;                           /* lsb=536870.912/128/256,unit=ms :始動後経過時間判定値 */
    u2 u2t_yaltif;                         /* lsb=12.8/128/256,unit=A :励磁電流 */
    u1 u1t_xels;                           /* lsb=1 :電気負荷1判定ﾌﾗｸﾞ */
    u1 u1t_xac;                            /* lsb=1 :AC判定ﾌﾗｸﾞ */
    u1 u1t_xpwrdec;                        /* lsb=1 :減衰実行ﾌﾗｸﾞ */
    u1 u1t_xbattClFt;                      /* lsb=1 :Circuit Low F/S情報(Test Failed) */
    u1 u1t_xkne_use_c;                     /* lsb=1 :回転数補正使用SW */
#if JEALTCNT == u1g_EJCC_USE               /*【充電制御有】*/
    s4 s4t_mpwralt;                        /* lsb=16/256/256,unit=kW :ｵﾙﾀﾊﾟﾜｰ */
    s4 s4t_pwaltsocb;                      /* lsb=512/128/256,unit=kW :目標電圧上昇時空気応答遅れﾍﾞｰｽ補正量 */
    s4 s4t_pwaltsoc;                       /* lsb=512/128/256,unit=kW :目標電圧上昇時空気応答遅れ補正量 */
    u4 u4t_pwaltsocb;                      /* lsb=512/128/256,unit=kW :目標電圧上昇時空気応答遅れﾍﾞｰｽ補正量 */
    u1 u1t_yxaltldinc;                     /* lsb=1 :ｵﾙﾀ負荷増大ﾌﾗｸﾞ */
    u1 u1t_yxaltldinco;                    /* lsb=1 :ｵﾙﾀ負荷増大ﾌﾗｸﾞ前回値 */
#endif /* JEALTCNT */
#if JEELS2 == u1g_EJCC_USE                 /*【ELS2有】*/
    u1 u1t_xels2;                          /* lsb=1 :電気負荷2判定ﾌﾗｸﾞ */
#endif /* JEELS2 */
    u1 u1t_xels3;                          /* lsb=1 :電気負荷3判定ﾌﾗｸﾞ */
    u1 u1t_xels4;                          /* lsb=1 :電気負荷4判定ﾌﾗｸﾞ */
#if JEELS3 == u1g_EJCC_USE                 /*【ELS3有】*/
    u1 u1t_xelsh1;                         /* lsb=1 :高電気負荷1判定ﾌﾗｸﾞ */
#endif /* JEELS3 */
#if JEELS4 == u1g_EJCC_USE                 /*【ELS4有】*/
    u1 u1t_xelsh2;                         /* lsb=1 :高電気負荷2判定ﾌﾗｸﾞ */
#endif /* JEELS4 */
    u1 u1t_xelsh3;                         /* lsb=1 :高電気負荷3判定ﾌﾗｸﾞ */
    u1 u1t_xelsh4;                         /* lsb=1 :高電気負荷4判定ﾌﾗｸﾞ */
    u1 u1t_xelsh5;                         /* lsb=1 :高電気負荷5判定ﾌﾗｸﾞ */
#if JEPS == u1g_EJCC_EPS                   /*【電動PS】*/
    u1 u1t_xpssw;                          /* lsb=1 :ﾊﾟﾜｽﾃSW */
#endif /* JEPS */
#if JEAI == u1g_EJCC_USE                   /*【AI制御有】*/
    u1 u1t_xaprly;                         /* lsb=1 :ｴｱﾎﾟﾝﾌﾟ作動ﾌﾗｸﾞ(ﾊﾞﾝｸ統合) */
#endif /* JEAI */
#if (JEFAN == u1g_EJCC_ONOFF_FAN) || (JEFAN == u1g_EJCC_PWM_FAN)    /*【ON/OFF電動ﾌｧﾝ方式】OR【PWM電動ﾌｧﾝ方式】*/
    s2 s2t_pwrfan;                         /* lsb=512/128/256,unit=kW :電動ﾌｧﾝ電力 */
#endif /* JEFAN */
#if JEFAN == u1g_EJCC_ONOFF_FAN            /*【ON/OFF電動ﾌｧﾝ方式】*/
    u1 u1t_outmnt;                         /* lsb=1 :ｸｰﾘﾝｸﾞﾌｧﾝ出力状態取得処理要求 */
#elif JEFAN == u1g_EJCC_PWM_FAN            /*【PWM電動ﾌｧﾝ方式】*/
    u4 u4t_pwrfan;                         /* lsb=512/128/256,unit=kW :電動ﾌｧﾝ電力 */
    s4 s4t_mvoltage;                       /* lsb=20/256/256,unit=V :ﾏｯﾌﾟ用ﾊﾞｯﾃﾘ電圧 */
    s2 s2t_voltage;                        /* lsb=(20*2)/128/256,unit=V :ﾊﾞｯﾃﾘ電圧 */
#endif /* JEFAN */

    /* epwrfan（電動ファン電力）の算出 */
#if JEFAN == u1g_EJCC_ONOFF_FAN                 /*【ON/OFF電動ﾌｧﾝ方式】*/
    u1t_outmnt = u1g_afanif_get_outmnt();

    if ( u1t_outmnt == u1g_AFANIF_LO )          /* 電動ファンＬＯ */
    {
        s2t_pwrfan = s2s_etqalt_FANLO;
    }
    else if ( u1t_outmnt == u1g_AFANIF_HI )     /* 電動ファンＨＩ */
    {
        s2t_pwrfan = s2s_etqalt_FANHI;
    }
    else                                        /* 電動ファンＯＦＦ */
    {
        s2t_pwrfan = (s2)(((0.)/(512./128./256.))+0.5);
    }
#elif JEFAN == u1g_EJCC_PWM_FAN                 /*【PWM電動ﾌｧﾝ方式】*/
    s2t_voltage = s2g_afanif_get_voltage();
    ELIB_MAPU2_HILOGD( s2t_voltage, 2U, s4t_mvoltage );
                                        /* lsb=(20*2)/128/256(V) → 20/256/256(V) */
    u4t_pwrfan = (u4)u2g_glmap1b_u2pt( (u2)s4t_mvoltage, &u1s_etqalt_epwrfan_map[0] ) >> 6;
                                        /* lsb=16/256/256(kW) → 512/128/256(kW) */
    s2t_pwrfan = (s2)u4t_pwrfan;
#endif /* JEFAN */
#if (JEFAN == u1g_EJCC_ONOFF_FAN) || (JEFAN == u1g_EJCC_PWM_FAN)    /*【ON/OFF電動ﾌｧﾝ方式】OR【PWM電動ﾌｧﾝ方式】*/
    s2s_etqalt_epwrfan = s2t_pwrfan;
#endif /* JEFAN */

    /* epwrelsrqb（電気負荷動力ベース値）の算出 */
    s2t_pwrelsrqbo = s2s_etqalt_epwrelsrqb;
    s4t_pwrelsrqb =  (s4)(((0.)/(512./128./256.))+0.5);

    u1t_xels = u1g_exdly_exels;
    if ( u1t_xels == (u1)ON )   /* 電気負荷1判定ﾌﾗｸﾞ */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELS;
    }

#if JEELS2 == u1g_EJCC_USE      /*【ELS2有】*/
    u1t_xels2 = u1g_exdly_exels2;
    if ( u1t_xels2 == (u1)ON )  /* 電気負荷2判定ﾌﾗｸﾞ */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELS2;
    }
#endif /* JEELS2 */

    u1t_xels3 = u1g_exdly_exels3;
    if ( u1t_xels3 == (u1)ON )  /* 電気負荷3判定ﾌﾗｸﾞ */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELS3;
    }

    u1t_xels4 = u1g_exdly_exels4;
    if ( u1t_xels4 == (u1)ON )  /* 電気負荷4判定ﾌﾗｸﾞ */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELS4;
    }

#if JEELS3 == u1g_EJCC_USE      /*【ELS3有】*/
    u1t_xelsh1 = u1g_exdly_exelsh1;
    if ( u1t_xelsh1 == (u1)ON ) /* 高電気負荷1判定ﾌﾗｸﾞ */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELSH1;
    }
#endif /* JEELS3 */

#if JEELS4 == u1g_EJCC_USE      /*【ELS4有】*/
    u1t_xelsh2 = u1g_exdly_exelsh2;
    if ( u1t_xelsh2 == (u1)ON ) /* 高電気負荷2判定ﾌﾗｸﾞ */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELSH2;
    }
#endif /* JEELS4 */

    u1t_xelsh3 = u1g_exdly_exelsh3;
    if ( u1t_xelsh3 == (u1)ON ) /* 高電気負荷3判定ﾌﾗｸﾞ */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELSH3;
    }

    u1t_xelsh4 = u1g_exdly_exelsh4;
    if ( u1t_xelsh4 == (u1)ON ) /* 高電気負荷4判定ﾌﾗｸﾞ */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELSH4;
    }

    u1t_xelsh5 = u1g_exdly_exelsh5;
    if ( u1t_xelsh5 == (u1)ON ) /* 高電気負荷5判定ﾌﾗｸﾞ */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELSH5;
    }

#if JEPS == u1g_EJCC_EPS        /*【電動PS】*/
    u1t_xpssw = (u1)big_apsswif_xpssw;
    if ( u1t_xpssw == (u1)ON )  /* 電動PS信号 */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELSPS;
    }
#endif /* JEPS */

#if JEFAN != u1g_EJCC_NOT_USE   /*【電動ﾌｧﾝ有】*/
    s4t_pwrelsrqb += (s4)s2t_pwrfan;
#endif /* JEFAN */

    u1t_xac = u1g_eacstate_exac;
    if ( u1t_xac == (u1)ON )    /* ｴｱｺﾝ(ﾌﾞﾛｱ) */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRAC;
    }

#if JEAI == u1g_EJCC_USE        /*【AI制御有】*/
    u1t_xaprly = (u1)big_eai_exaprly;
    if ( u1t_xaprly == (u1)ON ) /* 電動ｴｱﾎﾟﾝﾌﾟ負荷 */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELSAI;
    }
#endif /* JEAI */

#if JEPTCHT_E == u1g_EJCC_USE   /*【PTCﾋｰﾀ有】*/
    s4t_pwrelsrqb += (s4)s2g_eptchctrl_epwrptc;
#endif /* JEPTCHT_E */

    ELIB_HILOGD2( s4t_pwrelsrqb, (s4)s2s_etqalt_PWRELSGD, (s4)s2g_S2MIN, s4t_pwrelsrqb );
    s2s_etqalt_epwrelsrqb = (s2)s4t_pwrelsrqb;

    s2t_battsm = s2s_etqalt_ebattsm;
    /* t_dlpwrrqb（ベース要求値変化量）の算出 */
    s4t_dlpwrrqb = s4t_pwrelsrqb - (s4)s2t_pwrelsrqbo;
    s4t_dlpwrrqb = s4g_glmulst_s4s4u2( s4t_dlpwrrqb, (s4)s2t_battsm, (u2)0U );
                    /* lsb=512/128/256(kW) * (20*2)/128/256(V) → ((512/128/256)*((20*2)/128/256))((kW)*(V)) */
    s4t_dlpwrrqb = s4g_gldiv_s4s4( s4t_dlpwrrqb, (s4)s2s_etqalt_BATB );
                    /* lsb=((512/128/256)*((20*2)/128/256))((kW)*(V)) / (20*2)/128/256(V) → 512/128/256(kW) */

    /* ecast（始動後経過時間判定値）の算出 */
    s2t_cast = s2s_etqalt_ecast;
    if ( u1g_exst_exastefi == (u1)OFF ) /* 始動時 */
    {
        u2t_cast = u2g_glmap1b_u2pt( u2g_ethw_emthw, &u1s_etqalt_ecaltst_map[0] ) >> 8;
                        /* lsb=4194.304/256/256(ms) → 536870.912/128/256(ms) */
        s2t_cast = (s2)u2t_cast;
        s2s_etqalt_ecast = s2t_cast;
    }

    s2t_ne_l = s2g_ene_ene;
    s2t_net = s2g_emnet_enet;
    s2t_cast_16m = s2g_exst_ecast_16m;

    u1t_xkne_use_c = u1s_etqalt_XKNE_USE;
    /* ealtifsm（オルタ励磁電流）の算出 */
    /* etqalttb（目標オルタトルクベース値）の算出 */
    s2t_etqalttb = s2s_etqalt_TQINT;
    u1t_xbattClFt = (u1)big_wbatt_fdi_xbattClFt;
    if ( ( s2t_cast_16m >= s2t_cast )                /* 始動後、所定以上経過 */
      && ( u1t_xbattClFt == (u1)OFF )                /* バッテリ入力信号異常でない */
#if JEALTCNT == u1g_EJCC_USE   /*【充電制御有】*/
      && ( u1g_yaltlmp_yxbattlo == (u1)OFF )         /* バッテリ電圧低下でない */
#endif /* JEALTCNT */
       )
    {
        s2t_altifsmo = s2s_etqalt_ealtifsm;
        u2t_yaltif = (u2)u1g_yaltinfo_yaltif << 7U;
                        /* lsb= 12.8/256(A) → 12.8/128/256(A) */
        s2t_altifsm = s2g_glsmth_s2s2s2( s2t_altifsmo, (s2)u2t_yaltif, s2s_etqalt_ALTISM );

        if ( u1t_xkne_use_c == (u1)ON )              /* 回転数補正使用時 */
        {
            s4t_tqalttb = s4g_glmul_s2s2( s2g_yaltinfo_yalttrq, s2t_ne_l );
                        /* lsb= 1024/128/256(Nm) * (12800*2)/128/256(rpm) -> 800/128/256(Nm*rpm) */
            s4t_tqalttb = (s4)s2g_gldiv_s4s2( s4t_tqalttb, s2t_net );
                        /* lsb= 800/128/256(Nm*rpm) / (12800*2)/128/256(rpm) -> 1024/128/256(Nm) */
        }
        else                                         /* 回転数補正使用時でない */
        {
            s4t_tqalttb = (s4)s2g_yaltinfo_yalttrq;
        }

        s2t_etqalttb = s2s_etqalt_etqalttb;
        s4t_dltqalttb = s4t_tqalttb - (s4)s2t_etqalttb;
        if ( s4t_dltqalttb < (s4)(((0.)/(1024./128./256.))+0.5) )
        {
            s4t_dltqalttb = -s4t_dltqalttb;
        }

        if ( s4t_dltqalttb >= (s4)s2s_etqalt_TQHYS ) /* 仕様書と逆条件 */
        {
            s2t_etqalttb = s2g_glsmth_s2s2s2( s2t_etqalttb, (s2)s4t_tqalttb, s2s_etqalt_TQNSM );
        }
    }
    else
    {
        s2t_altifsm = s2g_glmap1h_s2pt( s2g_ethw_ethwst, &s2s_etqalt_eifint_map[0] );
    }
    s2s_etqalt_ealtifsm = s2t_altifsm;
    s2s_etqalt_etqalttb = s2t_etqalttb;

    /* etqaltt（目標オルタトルク）の算出 */
    s2t_ktqalt = s2g_glmap3hs_s2s2s2pt( s2t_ne_l, s2t_altifsm, s2t_battsm, &s2s_etqalt_ektqalt_map[0] );
    s4t_tqaltt = (s4)s2g_glmulst_s2s2u2( s2t_etqalttb, s2t_ktqalt, (u2)12U );
                           /* lsb= 1024/128/256(Nm) * 8/128/256(倍) -> 1024/128/256(Nm) */
    s2s_etqalt_etqaltt = (s2)s4t_tqaltt;

    s2t_nettq = s2g_glmulst_s2s2u2( s2t_net, (s2)2, (u2)0U );     /* シフト処理 */
                           /* lsb=(12800*2)/128/256(rpm) → 12800/128/256(rpm) */

    /* epwralt（オルタパワー）の算出 */
    ELIB_CONV_TTOP( (s2)s4t_tqaltt, s2t_nettq, s4t_pwralt );     /* トルクをパワーに変換 */
    f4g_etqalt_epwralt = (f4)s4t_pwralt * (f4)(512./128./256.);

#if JEALTCNT == u1g_EJCC_USE   /*【充電制御有】*/
    /* epwaltsocb（目標電圧上昇時空気応答遅れベース補正量）の算出 */
    u1t_yxaltldinco = (u1)bis_etqalt_yxaltldinco;
    u1t_yxaltldinc = (u1)big_ysocpublic_yxaltldinc;

    if ( ( s2t_cast_16m >= s2s_etqalt_CASTALTDLY )               /* 始動後所定時間経過 */
      && ( ( u1t_yxaltldinco == (u1)OFF )                        /* オルタ負荷増大へ変化時 */
        && ( u1t_yxaltldinc == (u1)ON ) ) )
    {
        ELIB_MAPU2_HILOGD( s4t_pwralt, 6U, s4t_mpwralt );
                                        /* lsb=512/128/256(kW) → 16/256/256(kW) */
        u4t_pwaltsocb = (u4)u2g_glmap1b_u2pt( (u2)s4t_mpwralt, &u1s_etqalt_epwaltsocb_map[0] ) >> 8;
                                        /* lsb=4/256/256(kW) → 512/128/256(kW) */
        s4t_pwaltsocb = (s4)u4t_pwaltsocb;
    }
    else if ( u1t_yxaltldinc == (u1)ON )                         /* オルタ負荷増大継続時 */
    {
        s4t_pwaltsocb = (s4)s2s_etqalt_epwaltsocb;
        s4t_pwaltsocb -= (s4)s2s_etqalt_DECALT;
        ELIB_HILOGD2( s4t_pwaltsocb, (s4)s2g_S2MAX, (s4)(((0.)/(512./128./256.))+0.5), s4t_pwaltsocb );
    }
    else                                                         /* 上記以外 */
    {
        s4t_pwaltsocb = (s4)(((0.)/(512./128./256.))+0.5);
    }
    s2s_etqalt_epwaltsocb = (s2)s4t_pwaltsocb;
    glbitcp_bibi( u1t_yxaltldinc, bis_etqalt_yxaltldinco );

    /* epwaltsoc（目標電圧上昇時空気応答遅れ補正量）の算出 */
    ELIB_HIGHGD2( s4t_pwaltsocb, (s4)s2s_etqalt_PWALTSOCGD, s4t_pwaltsoc );
    s2s_etqalt_epwaltsoc = (s2)s4t_pwaltsoc;
#endif /* JEALTCNT */

    /* t_pwrelsrq（減衰前ＳＷ入力電気負荷動力）の算出 */
    if ( s4t_pwrelsrqb > (s4)s2t_pwrelsrqbo )                         /* 電気負荷動力ベース値が増加時 */
    {
        s4t_pwrelsrq = (s4)s2s_etqalt_epwrels;
    }
    else                                                              /* 電気負荷動力ベース値が増加時でない */
    {
        s4t_pwrelsrq = (s4)s2s_etqalt_epwrelsrq;
    }
    s4t_pwrelsrq = s4g_gladdst_s4s4( s4t_pwrelsrq, s4t_dlpwrrqb );
    ELIB_LOWGD2( s4t_pwrelsrq, (s4)(((0.)/(512./128./256.))+0.5), s4t_pwrelsrq );

    /* ecdecdly_16m（徐変ディレーカウンタ）の算出 */
    /* expwrdec（減衰実行フラグ）の算出 */
    if ( s4t_dlpwrrqb > (s4)s2s_etqalt_DLPWR )                        /* ﾍﾞｰｽ要求値増加時 */
    {
        u1t_xpwrdec = (u1)OFF;
        s2g_etqalt_ecdecdly_16m = (s2)(((0.)/(536870.912/128./256.))+0.5);
    }
    else if ( ( s2g_etqalt_ecdecdly_16m >= s2s_etqalt_CDECDLY )       /* 所定時間経過 */
           || ( s4t_pwrelsrqb <= (s4)(((0.)/(512./128./256.))+0.5) )  /* ﾍﾞｰｽ電気負荷無し */
           || ( s4t_pwrelsrq <= s4t_pwralt ) )                        /* SW入力の電気負荷がｵﾙﾀﾊﾟﾜｰ以下 */
    {
        u1t_xpwrdec = (u1)ON;
    }
    else
    {
        u1t_xpwrdec = (u1)bis_etqalt_expwrdec;
    }
    glbitcp_bibi( u1t_xpwrdec, bis_etqalt_expwrdec );

    /* epwrelsrq（ＳＷ入力の電気負荷動力）の算出 */
    s4t_epwrelsrq = s4t_pwrelsrq;
    if ( u1t_xpwrdec == (u1)ON )                                      /* 減衰処理実行 */
    {
        s4t_epwrelsrq = s4g_glmulst_s4s4u2( s4t_pwrelsrq, (s4)s2s_etqalt_DECRTO, (u2)14U );
                    /* lsb=512/128/256(kW) * 2/128/256(倍) → 512/128/256(kW) */
    }
    ELIB_HILOGD2( s4t_epwrelsrq, (s4)s2g_S2MAX, (s4)s2g_S2MIN, s4t_epwrelsrq );
    s2s_etqalt_epwrelsrq = (s2)s4t_epwrelsrq;

    /* epwrels（電気負荷動力）の算出 */
#if JEALTCNT == u1g_EJCC_USE   /*【充電制御有】*/
    s4t_pwraltadd = s4t_pwralt + s4t_pwaltsoc;
#else                          /*【充電制御無】*/
    s4t_pwraltadd = s4t_pwralt;
#endif /* JEALTCNT */
    ELIB_MAXSLCT2( s4t_epwrelsrq, s4t_pwraltadd, s4t_pwrels );
    ELIB_HIGHGD2( s4t_pwrels, (s4)s2g_S2MAX, s4t_pwrels );
    s2s_etqalt_epwrels = (s2)s4t_pwrels;

    /* t_tqelsswrq（ＳＷ入力の電気負荷トルク）*/
    ELIB_CONV_PTOT( (s2)s4t_epwrelsrq, s2t_nettq, s4t_tqelsswrq );        /* パワーをトルクに変換 */

    /* etqelstb（目標電気負荷トルクベース値）の算出 */
    ELIB_MAXSLCT2( s4t_tqaltt, s4t_tqelsswrq, s4t_tqelstb );
    s2s_etqalt_etqelstb = (s2)s4t_tqelstb;                                /* t_tqaltt, t_tqelsswrq は共にs2範囲内なのでｷｬｽﾄOK */

    /* ecrqbchg_16m（ベース要求値変化カウンタ）のクリア */
    s2t_crqbchg_16m = s2g_etqalt_ecrqbchg_16m;
    if ( s4t_dlpwrrqb != (s4)(((0.)/(512./128./256.))+0.5) )              /* ベース要求値変化時 */
    {
        s2t_crqbchg_16m = (s2)(((0.)/(536870.912/128./256.))+0.5);
        s2g_etqalt_ecrqbchg_16m = s2t_crqbchg_16m;
    }

    /* t_dltrqabs（偏差量判定値）の算出 */
    s2t_dltrqabs = s2s_etqalt_DLTQABSL;
    if ( s2t_crqbchg_16m < s2s_etqalt_CDECHYS )   /* ベース要求値変化後所定時間未満 */
    {
        s2t_dltrqabs = s2s_etqalt_DLTQABSH;
    }

    /* t_tqgdlo（トルク下限ガード値）、t_tqgdhi（トルク上限ガード値）の算出 */
    s2t_tqelsto = s2s_etqalt_etqelst;

    s4t_dltqelst = s4t_tqelstb - (s4)s2t_tqelsto;
    s4t_dltqelst = s4g_glabs_s4( s4t_dltqelst );

    s2t_dlgdl = s2s_etqalt_DLGDMXL;
    s2t_dlgdh = s2s_etqalt_DLGDMXH;
    if ( s4t_dltqelst < (s4)s2t_dltrqabs )        /* 補正量と要求値との偏差小 */
    {
        s2t_dlgdl = s2s_etqalt_DLGDMNL;
        s2t_dlgdh = s2s_etqalt_DLGDMNH;
    }
    s4t_tqgdlo = (s4)s2t_tqelsto - (s4)s2t_dlgdl;
    s4t_tqgdhi = (s4)s2t_tqelsto + (s4)s2t_dlgdh;

    /* etqelst（目標電気負荷トルク）の算出 */
    ELIB_HILOGD2( s4t_tqelstb, s4t_tqgdhi, s4t_tqgdlo, s4t_tqelst );
    ELIB_HILOGD2( s4t_tqelst, (s4)s2g_S2MAX, (s4)s2g_S2MIN, s4t_tqelst );
    s2s_etqalt_etqelst = (s2)s4t_tqelst;

    /* etqaltisc[0]（ISC目標オルタトルク(将来)）、etqaltisc[1]（ISC現在オルタトルク(直近)）の算出 */
    s2g_etqalt_etqaltisc[0] = (s2)s4t_tqelst;    /* 実質s2なのでs2キャスト可 */
    f4g_etqalt_etqaltisc[0] = (f4)s4t_tqelst * (f4)(1024./128./256.);
    s2g_etqalt_etqaltisc[1] = (s2)s4t_tqelst;    /* 算出時にS2ガード済み */
    f4g_etqalt_etqaltisc[1] = (f4)s4t_tqelst * (f4)(1024./128./256.);

    /* etqalt（現在オルタトルク）の算出 */
    s4t_etqalt = s4t_tqaltt;
    if ( u1t_xkne_use_c == (u1)ON )         /* 回転数補正使用時 */
    {
        ELIB_LOWGD2( (s4)s2t_ne_l, (s4)s2s_etqalt_NEGD, s4t_ne );
        s4t_etqalt = s4g_glmul_s2s2( (s2)s4t_tqaltt, s2t_net );
                                /* lsb=1024/128/256(Nm) * (12800*2)/128/256(rpm) */
        s4t_etqalt = (s4)s2g_gldiv_s4s2( s4t_etqalt, (s2)s4t_ne );
                                /* lsb=1024/128/256(Nm) * (12800*2)/128/256(rpm) / (12800*2)/128/256(rpm) -> 1024/128/256(Nm) */
    }

    s2g_etqalt_etqalt = (s2)s4t_etqalt;
    f4g_etqalt_etqalt = (f4)s4t_etqalt * (f4)(1024./128./256.);
}

/*********************************************************************/
/*  関数名        |  vdg_etqalt_65msl_seq( )                         */
/*  処理内容      |  バッテリ電圧の算出                              */
/*  制御タイミング|  65msl                                           */
/*  引数          |  なし                                            */
/*  戻り値        |  なし                                            */
/*  注意事項      |                                                  */
/*********************************************************************/
void
vdg_etqalt_65msl_seq(void)
{
    s2s_etqalt_ebattsm = s2g_glsmth_s2s2s2( s2s_etqalt_ebattsm, s2g_cpowif_b, s2s_etqalt_BATNSM );
}

/**** End of File ****************************************************/
