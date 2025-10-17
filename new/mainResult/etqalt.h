/* etqalt-pcw00-1200-a-M3 */
/*********************************************************************/
/*  Copyright Toyota Motor Corporation                               */
/*********************************************************************/

/*********************************************************************/
/*  オブジェクト名 | 電気負荷トルク                                  */
/*  注意事項       |【ｵﾙﾀﾏﾈｰｼﾞｬ有】                                  */
/*-------------------------------------------------------------------*/
/* I/F変更履歴     | -11 全体コンパイルSW【ｵﾙﾀﾏﾈｰｼﾞｬ有】追加         */
/*-------------------------------------------------------------------*/
/*  ファイル構成   | etqalt_l_mat.c, etqalt_c_mat.c                  */
/*-------------------------------------------------------------------*/
/*     個別変更履歴 （個別変更時は以下に変更日、内容を記入すること） */
/*********************************************************************/

#ifndef ETQALT_H
#define ETQALT_H

/*-------------------------------------------------------------------*/
/* ヘッダファイルのインクルード                                      */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* 型定義                                                            */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* マクロ定義                                                        */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* 関数                                                              */
/*-------------------------------------------------------------------*/
void vdg_etqalt_pwon_seq( void );          /* 初期化処理 */
                                           /* コール元 : vdg_etranfwdmng_pwon() */
                                           /* 事前初期化 : 無し */

void vdg_etqalt_16msl_seq( void );         /* 電気負荷トルクの算出 */
                                           /* コール元 : vdg_etranfwdmng_16msl() */

void vdg_etqalt_65msl_seq( void );         /* バッテリ電圧の算出 */
                                           /* コール元 : vdg_etranfwdmng_65msl() */

/*-------------------------------------------------------------------*/
/* 公開変数                                                          */
/*-------------------------------------------------------------------*/
extern s2 s2g_etqalt_etqalt;               /* m=etqalt,lsb=1024/128/256,unit=Nm :現在ｵﾙﾀﾄﾙｸ */
                                           /* 更新タイミング : 16msl */

extern f4 f4g_etqalt_etqalt;               /* m=etqalt,unit=Nm :現在ｵﾙﾀﾄﾙｸ */
                                           /* 更新タイミング : 16msl */

extern f4 f4g_etqalt_etqaltisc[2];         /* m=etqalt,unit=Nm :ISCｵﾙﾀﾄﾙｸ(0:将来)／(1:直近) */
                                           /* 注意事項 : etqaltisc[0] = ISC目標ｵﾙﾀﾄﾙｸ(将来) */
                                           /*            etqaltisc[1] = ISC現在ｵﾙﾀﾄﾙｸ(直近) */
                                           /* 更新タイミング : 16msl */

extern f4 f4g_etqalt_epwralt;              /* m=etqalt,unit=kW :ｵﾙﾀﾊﾟﾜｰ */
                                           /* 更新タイミング : 16msl */
extern s2 s2g_etqalt_etqaltisc[2];         /* m=etqalt,lsb=1024/128/256,unit=Nm :ISCｵﾙﾀﾄﾙｸ(0:将来)／(1:直近) */
                                           /* 注意事項 : etqaltisc[0] = ISC目標ｵﾙﾀﾄﾙｸ(将来) */
                                           /*            etqaltisc[1] = ISC現在ｵﾙﾀﾄﾙｸ(直近) */
                                           /* 更新タイミング : 16msl */

/*-------------------------------------------------------------------*/
/* 適合定数                                                          */
/*-------------------------------------------------------------------*/
/* 非公開(部品内部のみ) */
extern volatile const s2 s2s_etqalt_NEGD;             /* lsb=(12800*2)/128/256,unit=rpm :NE下限ｶﾞｰﾄﾞ値 */
extern volatile const s2 s2s_etqalt_CDECHYS;          /* lsb=536870.912/128/256,unit=ms :要求値変化経過時間 */
extern volatile const s2 s2s_etqalt_DLTQABSH;         /* lsb=1024/128/256,unit=Nm :要求値偏差量判定値HI */
extern volatile const s2 s2s_etqalt_DLTQABSL;         /* lsb=1024/128/256,unit=Nm :要求値偏差量判定値 */
extern volatile const s2 s2s_etqalt_BATINT;           /* lsb=(20*2)/128/256,unit=V :ﾊﾞｯﾃﾘ電圧初期値 */
extern volatile const s2 s2s_etqalt_BATB;             /* lsb=(20*2)/128/256,unit=V :基準電圧 */
extern volatile const s2 s2s_etqalt_DLGDMNL;          /* lsb=1024/128/256,unit=Nm :偏差小時の徐変量(減少) */
extern volatile const s2 s2s_etqalt_DLGDMNH;          /* lsb=1024/128/256,unit=Nm :偏差小時の徐変量(増加) */
extern volatile const s2 s2s_etqalt_DLGDMXL;          /* lsb=1024/128/256,unit=Nm :偏差大時の徐変量(減少) */
extern volatile const s2 s2s_etqalt_DLGDMXH;          /* lsb=1024/128/256,unit=Nm :偏差大時の徐変量(増加) */
extern volatile const s2 s2s_etqalt_TQNSM;            /* lsb=256/128/256,unit=回 :ｵﾙﾀﾄﾙｸなまし定数 */
extern volatile const s2 s2s_etqalt_TQHYS;            /* lsb=1024/128/256,unit=Nm :ｵﾙﾀﾄﾙｸﾋｽ */
extern volatile const s2 s2s_etqalt_TQINT;            /* lsb=1024/128/256,unit=Nm :ｵﾙﾀﾄﾙｸ初期値 */
extern volatile const s2 s2s_etqalt_CDECDLY;          /* lsb=536870.912/128/256,unit=ms :徐変開始ﾃﾞｨﾚｰ時間 */
extern volatile const s2 s2s_etqalt_DLPWR;            /* lsb=512/128/256,unit=kW :ﾍﾞｰｽ要求値増加判定値 */
extern volatile const s2 s2s_etqalt_DECRTO;           /* lsb=2/128/256,unit=倍 :徐変率 */
extern volatile const s2 s2s_etqalt_PWRELSGD;         /* lsb=512/128/256,unit=kW :電気負荷上限ｶﾞｰﾄﾞ値 */
extern volatile const s2 s2s_etqalt_PWRELS;           /* lsb=512/128/256,unit=kW :電気負荷1 */
extern volatile const s2 s2s_etqalt_PWRELS2;          /* lsb=512/128/256,unit=kW :電気負荷2【ELS2有】 */
extern volatile const s2 s2s_etqalt_PWRELS3;          /* lsb=512/128/256,unit=kW :電気負荷3 */
extern volatile const s2 s2s_etqalt_PWRELS4;          /* lsb=512/128/256,unit=kW :電気負荷4 */
extern volatile const s2 s2s_etqalt_PWRELSH1;         /* lsb=512/128/256,unit=kW :高電気負荷1【ELS3有】 */
extern volatile const s2 s2s_etqalt_PWRELSH2;         /* lsb=512/128/256,unit=kW :高電気負荷2【ELS4有】 */
extern volatile const s2 s2s_etqalt_PWRELSH3;         /* lsb=512/128/256,unit=kW :高電気負荷3 */
extern volatile const s2 s2s_etqalt_PWRELSH4;         /* lsb=512/128/256,unit=kW :高電気負荷4 */
extern volatile const s2 s2s_etqalt_PWRELSH5;         /* lsb=512/128/256,unit=kW :高電気負荷5 */
extern volatile const s2 s2s_etqalt_PWRELSPS;         /* lsb=512/128/256,unit=kW :電動ﾊﾟﾜｽﾃ負荷【電動PS】 */
extern volatile const s2 s2s_etqalt_FANLO;            /* lsb=512/128/256,unit=kW :電動ﾌｧﾝLO負荷【ON/OFF電動ﾌｧﾝ方式】 */
extern volatile const s2 s2s_etqalt_FANHI;            /* lsb=512/128/256,unit=kW :電動ﾌｧﾝHI負荷【ON/OFF電動ﾌｧﾝ方式】 */
extern volatile const s2 s2s_etqalt_PWRELSAI;         /* lsb=512/128/256,unit=kW :電動ｴｱﾎﾟﾝﾌﾟ負荷【AI制御有】 */
extern volatile const s2 s2s_etqalt_PWRAC;            /* lsb=512/128/256,unit=kW :ｴｱｺﾝ負荷 */
extern volatile const s2 s2s_etqalt_PWALTSOCGD;       /* lsb=512/128/256,unit=kW :目標電圧上昇時空気応答遅れ補正量上限ｶﾞｰﾄﾞ値【充電制御有】 */
extern volatile const s2 s2s_etqalt_CASTALTDLY;       /* lsb=536870.912/128/256,unit=ms :始動後時間判定値【充電制御有】 */
extern volatile const s2 s2s_etqalt_DECALT;           /* lsb=512/128/256,unit=kW :目標電圧上昇時空気応答遅れ減衰量【充電制御有】 */
extern volatile const s2 s2s_etqalt_BATNSM;           /* lsb=256/128/256,unit=回 :ﾊﾞｯﾃﾘ電圧なまし定数 */
extern volatile const s2 s2s_etqalt_ALTISM;           /* m=etqalt,lsb=256/128/256,ofs=,unit=回 :励磁電流負荷急変時なまし回数(LIN) */
extern volatile const s2 s2s_etqalt_IFINT;            /* m=etqalt,lsb=12.8/128/256,ofs=,unit=A :ｵﾙﾀ励磁電流初期値 */
extern volatile const u1 u1s_etqalt_XKNE_USE;         /* m=etqalt,lsb=-,ofs=,unit=- :回転数補正使用SW */

/*-------------------------------------------------------------------*/
/* 適合マップ                                                        */
/*-------------------------------------------------------------------*/
/* 非公開(部品内部のみ) */
#pragma ghs startdata
extern volatile const s2 s2s_etqalt_ektqalt_map[];    /* m=etqalt,目標ｵﾙﾀﾄﾙｸ回転数補正ﾏｯﾌﾟ */
extern volatile const u1 u1s_etqalt_ecaltst_map[];    /* 始動後経過時間判定値ﾏｯﾌﾟ */
extern volatile const u1 u1s_etqalt_epwrfan_map[];    /* 電動ﾌｧﾝ負荷ﾏｯﾌﾟ【PWM電動ﾌｧﾝ方式】 */
extern volatile const u1 u1s_etqalt_epwaltsocb_map[]; /* 目標電圧上昇時空気応答遅れﾍﾞｰｽ補正量ﾏｯﾌﾟ【充電制御有】 */
extern volatile const s2 s2s_etqalt_eifint_map[];     /* m=etqalt,ｵﾙﾀ励磁電流ﾏｯﾌﾟ */
#pragma ghs enddata

/*-------------------------------------------------------------------*/
/* オートカウンタ                                                    */
/*-------------------------------------------------------------------*/
extern s2 s2g_etqalt_ecdecdly_16m;           /* 非公開 lsb=536870.912/128/256,unit=ms :徐変ﾃﾞｨﾚｰｶｳﾝﾀ */
extern s2 s2g_etqalt_ecrqbchg_16m;           /* 非公開 lsb=536870.912/128/256,unit=ms :ﾍﾞｰｽ要求値変化ｶｳﾝﾀ */

#endif  /* ETQALT_H */
/**** End of File ****************************************************/
