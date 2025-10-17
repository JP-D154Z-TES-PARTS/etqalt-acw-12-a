/* etqalt-pcw00-1100-b-M3 */
/*********************************************************************/
/*  Copyright Toyota Motor Corporation                               */
/*********************************************************************/

/*********************************************************************/
/*  �I�u�W�F�N�g�� | �d�C���׃g���N                                  */
/*  ���ӎ���       |�y����Ȱ�ެ�L�z                                  */
/*-------------------------------------------------------------------*/
/*     �ʕύX���� �i�ʕύX���͈ȉ��ɕύX���A���e���L�����邱�Ɓj */
/*********************************************************************/

/*-------------------------------------------------------------------*/
/* �K���p�Z�N�V������`                                              */
/*-------------------------------------------------------------------*/
#pragma ghs section rozdata = ".mat_etqalt"

/*-------------------------------------------------------------------*/
/* �w�b�_�t�@�C���̃C���N���[�h                                      */
/*-------------------------------------------------------------------*/
#include <../inc/common.h>
#include <../inc/gllib.h>
#include <engsrc/espc/ejcc.h>               /* JEFAN,JEELS2,JEELS3,JEELS4,JEPS,JEAI,JEALTCNT */
#include <engsrc/inc/elsb.h>

#include <engsrc/etranfwd/etrq/etqalt.h>

/*-------------------------------------------------------------------*/
/* �R���p�C���o�[�W������`                                          */
/*-------------------------------------------------------------------*/
#define MK32_ID                         (0x00000040)             /* R9�R���p�C�����g�p */

#ifdef __GHS_VERSION_NUMBER
 #if ( ( __GHS_VERSION_NUMBER >= 201355 ) \
    && ( __GHS_VERSION_NUMBER < 201400 ) )
 #else
  #error "�R���p�C�������R���p�C�����قȂ��Ă��܂��B"
 #endif
#endif

/*-------------------------------------------------------------------*/
/* �R���p�C��SW����`�`�F�b�N                                        */
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
/* �K���萔                                                          */
/*-------------------------------------------------------------------*/
/* $$$�K���萔_�W��_v4.11 */
volatile const s2 s2s_etqalt_NEGD = s2g_ELSB_NE(200.);                  /* m=etqalt,lsb=(12800*2)/128/256,ofs=,unit=rpm :NE�����ް�ޒl */
volatile const s2 s2s_etqalt_CDECHYS = s2g_ELSB_16MS(500.);             /* m=etqalt,lsb=536870.912/128/256,ofs=,unit=ms :�v���l�ω��o�ߎ��� */
volatile const s2 s2s_etqalt_DLTQABSH = s2g_ELSB_TRQ(0.5);              /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :�v���l�΍��ʔ���lHI */
volatile const s2 s2s_etqalt_DLTQABSL = s2g_ELSB_TRQ(0.125);            /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :�v���l�΍��ʔ���l */
volatile const s2 s2s_etqalt_BATINT = s2g_ELSB_BAT(12.);                /* m=etqalt,lsb=(20*2)/128/256,ofs=,unit=V :�ޯ�ؓd�������l */
volatile const s2 s2s_etqalt_BATB = s2g_ELSB_BAT(13.5);                 /* m=etqalt,lsb=(20*2)/128/256,ofs=,unit=V :��d�� */
volatile const s2 s2s_etqalt_DLGDMNL = s2g_ELSB_TRQ(0.03125);           /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :�΍������̏��ϗ�(����) */
volatile const s2 s2s_etqalt_DLGDMNH = s2g_ELSB_TRQ(0.03125);           /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :�΍������̏��ϗ�(����) */
volatile const s2 s2s_etqalt_DLGDMXL = s2g_ELSB_TRQ(20.);               /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :�΍��厞�̏��ϗ�(����) */
volatile const s2 s2s_etqalt_DLGDMXH = s2g_ELSB_TRQ(20.);               /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :�΍��厞�̏��ϗ�(����) */
/* etqalt_DLGDMNL, etqalt_DLGDMNH, etqalt_DLGDMXL, etqalt_DLGDMXH�͐��̒l�Ƃ��邱�� */
volatile const s2 s2s_etqalt_TQNSM = s2g_ELSB_NSM(131.072/16.384);      /* m=etqalt,lsb=256/128/256,ofs=,unit=�� :����ٸ�Ȃ܂��萔 */
volatile const s2 s2s_etqalt_TQHYS = s2g_ELSB_TRQ(0.3);                 /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :����ٸ˽ */
volatile const s2 s2s_etqalt_TQINT = s2g_ELSB_TRQ(3.);                  /* m=etqalt,lsb=1024/128/256,ofs=,unit=Nm :����ٸ�����l */
volatile const s2 s2s_etqalt_CDECDLY = s2g_ELSB_16MS(150.);             /* m=etqalt,lsb=536870.912/128/256,ofs=,unit=ms :���ϊJ�n�ިڰ���� */
volatile const s2 s2s_etqalt_DLPWR = s2g_ELSB_PWR(0.);                  /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :�ް��v���l��������l */
volatile const s2 s2s_etqalt_DECRTO = s2g_glround((0.975)/(2./128./256.));  /* m=etqalt,lsb=2/128/256,ofs=,unit=�{ :���ϗ� */
/* eqels_DECRTO�́A���萔 640(ms)�����l�Ƃ��Ă����B */
volatile const s2 s2s_etqalt_PWRELSGD = s2g_ELSB_PWR(1.5);              /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :�d�C���׏���ް�ޒl */
/* ���ӎ����Fetqalt_PWRELSGD��ύX����ۂ́A���Z�Ď����i�ɉe�������邽�ߒ萔�ݒ蕔���Ɋm�F�̏�� */
/* esimtqrqmnt_TQALTISCUG�Aesimtqrqmnt_TQALTUG���ύX���邱�� */
volatile const s2 s2s_etqalt_PWRELS = s2g_ELSB_PWR(0.);                 /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :�d�C����1 */

#if JEELS2 == u1g_EJCC_USE                                              /* �yELS2�L�z */
volatile const s2 s2s_etqalt_PWRELS2 = s2g_ELSB_PWR(0.);                /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :�d�C����2 */
#endif                                                                  /* JEELS2 */

volatile const s2 s2s_etqalt_PWRELS3 = s2g_ELSB_PWR(0.);                /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :�d�C����3 */
volatile const s2 s2s_etqalt_PWRELS4 = s2g_ELSB_PWR(0.);                /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :�d�C����4 */

#if JEELS3 == u1g_EJCC_USE                                              /* �yELS3�L�z */
volatile const s2 s2s_etqalt_PWRELSH1 = s2g_ELSB_PWR(0.);               /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :���d�C����1 */
#endif                                                                  /* JEELS3 */

#if JEELS4 == u1g_EJCC_USE                                              /* �yELS4�L�z */
volatile const s2 s2s_etqalt_PWRELSH2 = s2g_ELSB_PWR(0.);               /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :���d�C����2 */
#endif                                                                  /* JEELS4 */

volatile const s2 s2s_etqalt_PWRELSH3 = s2g_ELSB_PWR(0.);               /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :���d�C����3 */
volatile const s2 s2s_etqalt_PWRELSH4 = s2g_ELSB_PWR(0.);               /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :���d�C����4 */
volatile const s2 s2s_etqalt_PWRELSH5 = s2g_ELSB_PWR(0.);               /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :���d�C����5 */

#if JEPS == u1g_EJCC_EPS                                                /* �y�d��PS�z */
volatile const s2 s2s_etqalt_PWRELSPS = s2g_ELSB_PWR(0.19);             /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :�d����ܽÕ��� */
#endif                                                                  /* JEPS */

#if JEFAN == u1g_EJCC_ONOFF_FAN                                         /* �yON/OFF�d��̧ݕ����z */
volatile const s2 s2s_etqalt_FANLO = s2g_ELSB_PWR(0.);                  /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :�d��̧�LO���� */
volatile const s2 s2s_etqalt_FANHI = s2g_ELSB_PWR(0.);                  /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :�d��̧�HI���� */
#endif                                                                  /* JEFAN */

#if JEAI == u1g_EJCC_USE                                                /* �yAI����L�z */
volatile const s2 s2s_etqalt_PWRELSAI = s2g_ELSB_PWR(1.0);              /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :�d��������ߕ��� */
#endif                                                                  /* JEAI */

volatile const s2 s2s_etqalt_PWRAC = s2g_ELSB_PWR(0.);                  /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :���ݕ��� */

#if JEALTCNT == u1g_EJCC_USE                                            /* �y�[�d����L�z */
volatile const s2 s2s_etqalt_PWALTSOCGD = s2g_ELSB_PWR(0.8);            /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :�ڕW�d���㏸����C�����x��␳�ʏ���ް�ޒl */
volatile const s2 s2s_etqalt_CASTALTDLY = s2g_ELSB_16MS(2000.);         /* m=etqalt,lsb=536870.912/128/256,ofs=,unit=ms :�n���㎞�Ԕ���l */
volatile const s2 s2s_etqalt_DECALT = s2g_ELSB_PWR(0.015);              /* m=etqalt,lsb=512/128/256,ofs=,unit=kW :�ڕW�d���㏸����C�����x�ꌸ���� */
#endif                                                                  /* JEALTCNT */

volatile const s2 s2s_etqalt_BATNSM = s2g_ELSB_NSM(131.072/65.536);     /* m=etqalt,lsb=256/128/256,ofs=,unit=�� :�ޯ�ؓd���Ȃ܂��萔 */
volatile const s2 s2s_etqalt_ALTISM = s2g_ELSB_NSM(65.536/16.384);      /* m=etqalt,lsb=256/128/256,ofs=,unit=�� :�㎥�d�����׋}�ώ��Ȃ܂���(LIN) */
volatile const s2 s2s_etqalt_IFINT = s2g_glround((1.0)/(12.8/128./256.));   /* m=etqalt,lsb=12.8/128/256,ofs=,unit=A :����㎥�d�������l */
volatile const u1 u1s_etqalt_XKNE_USE = (u1)(ON);                       /* m=etqalt,lsb=,ofs=,unit=- :��]���␳�g�pSW */
/* $$$�K���萔_�W��_v4.11 */

/*-------------------------------------------------------------------*/
/* �K���}�b�v                                                        */
/*-------------------------------------------------------------------*/
#pragma ghs startdata
/* $$$�K���}�b�v_�W��_v4.11 */
/*---- etqalt_ektqalt_map ------------------------------------------*/
#define X(x) (s2g_ELSB_NE(x))                                           /* m=etqalt,lsb=(12800*2)/128/256,ofs=,unit=rpm :ene_ene */
#define Y(y) (s2g_glround((y)/(12.8/128./256.)))                        /* m=etqalt,lsb=12.8/128/256,ofs=,unit=A :ealtifsm */
#define Z(z) (s2g_ELSB_BAT(z))                                          /* m=etqalt,lsb=(20*2)/128/256,ofs=,unit=V :ebattsm= */
#define W(w) (s2g_glround((w)/(8./128./256.)))                          /* m=etqalt,lsb=8/128/256,ofs=,unit=�{ : */
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
#define X(x) (u1g_ELSB_THW(x))                                          /* m=etqalt,lsb=160/256,ofs=-40,unit=�� :ethw_ethw */
#define Y(y) (u1g_ELSB_16MS(y))                                         /* m=etqalt,lsb=4194.304/256,ofs=,unit=ms :ecast */
volatile const u1 u1s_etqalt_ecaltst_map[] =
{
    7U,
    X(-30.),  X(-10.),  X(10.),   X(30.),   X(50.), X(70.), X(90.),
    Y(1000.), Y(1000.), Y(1000.), Y(1000.), Y(0.),  Y(0.),  Y(0.)
};
#undef X
#undef Y

#if JEFAN == u1g_EJCC_PWM_FAN                                           /* �yPWM�d��̧ݕ����z */
/*---- etqalt_epwrfan_map ------------------------------------------*/
#define X(x) ((u1)(((x)/(20./256.))+0.5))                               /* m=etqalt,lsb=20/256,ofs=,unit=V :afanif_get_voltage() */
#define Y(y) ((u1)(((y)/(16./256.))+0.5))                               /* m=etqalt,lsb=16/256,ofs=,unit=kW :t_pwrfan */
volatile const u1 u1s_etqalt_epwrfan_map[] =                            /* �yPWM�d��̧ݕ����z */
{
    4U,
    X(0.), X(4.), X(8.), X(12.),
    Y(0.), Y(0.), Y(0.), Y(0.)
};
#undef X
#undef Y

#endif                                                                  /* JEFAN */

#if JEALTCNT == u1g_EJCC_USE                                            /* �y�[�d����L�z */
/*---- etqalt_epwaltsocb_map ---------------------------------------*/
#define X(x) ((u1)(((x)/(16./256.))+0.5))                               /* m=etqalt,lsb=16/256,ofs=,unit=kW :epwralt */
#define Y(y) ((u1)(((y)/(4./256.))+0.5))                                /* m=etqalt,lsb=4/256,ofs=,unit=kW :epwaltsocb */
volatile const u1 u1s_etqalt_epwaltsocb_map[] =                         /* �y�[�d����L�z */
{
    6U,
    X(0.6), X(0.8), X(1.),  X(1.2), X(1.4), X(1.6),
    Y(0.8), Y(0.8), Y(0.8), Y(0.4), Y(0.2), Y(0.)
};
#undef X
#undef Y

#endif                                                                  /* JEALTCNT */

/*---- etqalt_eifint_map -------------------------------------------*/
#define X(x) (s2g_ELSB_THW(x))                                          /* m=etqalt,lsb=(160*128)/128/256,ofs=,unit=�� :ethw_ethwst */
#define Y(y) (s2g_glround((y)/(12.8/128./256.)))                        /* m=etqalt,lsb=12.8/128/256,ofs=,unit=A :ealtifsm */
volatile const s2 s2s_etqalt_eifint_map[] =
{
    7,0,
    X(-30.), X(-10.), X(10.), X(20.), X(50.), X(70.), X(90.),
    Y(1.),   Y(1.),   Y(1.),  Y(1.),  Y(1.),  Y(1.),  Y(1.)
};
#undef X
#undef Y

/* $$$�K���}�b�v_�W��_v4.11 */
#pragma ghs enddata

/**** End of File ****************************************************/
