/* etqalt-pcw00-1100-a-M4 */
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
/* �w�b�_�t�@�C���̃C���N���[�h                                      */
/*-------------------------------------------------------------------*/
#include <../inc/common.h>
#include <../inc/gllib.h>
#include <engsrc/espc/ejcc.h>               /* JEALTCNT,JEFAN,JEELS2,JEELS3,JEELS4,JEPS,JEAI,JEPTCHT_E */
#include <engsrc/inc/elsb.h>
#include <engsrc/inc/elib.h>

#include <aps/cpowif.h>                     /* s2g_cpowif_b */

#if JEFAN != u1g_EJCC_NOT_USE               /*�y�d��̧ݗL�z*/
#include <sac/afanif.h>                     /* u1g_afanif_get_outmnt(),u1g_AFANIF_LO,u1g_AFANIF_HI */
                                            /* s2g_afanif_get_voltage() */
#endif /* JEFAN */
#if JEPS == u1g_EJCC_EPS                    /*�y�d��PS�z*/
#include <sac/aonoffinif.h>                 /* big_apsswif_xpssw */
#endif /* JEPS */

#include <obd/wfd/wbatt_fdi.h>              /* big_wbatt_fdi_xbattClFt */

#include <yaux/yaltmng/yaltinfo.h>          /* s2g_yaltinfo_yalttrq,u1g_yaltinfo_yaltif */
#if JEALTCNT == u1g_EJCC_USE                /*�y�[�d����L�z*/
#include <yaux/yaltmng/yaltlmp.h>           /* u1g_yaltlmp_yxbattlo */
#include <yaux/ysoc/ysocpublic.h>           /* big_ysocpublic_yxaltldinc */
#endif /* JEALTCNT */

#if JEAI == u1g_EJCC_USE                    /*�yAI����L�z*/
#include <eng/eels/eai.h>                   /* big_eai_exaprly */
#endif /* JEAI */

#if JEPTCHT_E == u1g_EJCC_USE               /*�yPTC˰��L�z*/
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
/* �R���p�C���o�[�W������`                                          */
/*-------------------------------------------------------------------*/
#define MK32_ID                         (0x00000080)             /* M4�R���p�C�����g�p */

#ifdef __GHS_VERSION_NUMBER
 #if ( ( __GHS_VERSION_NUMBER >= 201714 ) \
    && ( __GHS_VERSION_NUMBER < 201800 ) )
 #else
  #error "�R���p�C�������R���p�C�����قȂ��Ă��܂��B"
 #endif
#endif

/*-------------------------------------------------------------------*/
/* �R���p�C��SW����`�`�F�b�N                                        */
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
/* �^��`                                                            */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* macro��`                                                         */
/*-------------------------------------------------------------------*/
/* $$$�}�N���萔_�W��_v4.11 */
/* $$$�}�N���萔_�W��_v4.11 */

/*-------------------------------------------------------------------*/
/* �ϐ���`                                                          */
/*-------------------------------------------------------------------*/
s2 s2g_etqalt_etqalt;               /* m=etqalt,lsb=1024/128/256,unit=Nm :���ݵ���ٸ */
f4 f4g_etqalt_etqalt;               /* m=etqalt,unit=Nm :���ݵ���ٸ */
s2 s2g_etqalt_etqaltisc[2];         /* m=etqalt,lsb=1024/128/256,unit=Nm :ISC����ٸ(0:����)�^(1:����) */
f4 f4g_etqalt_etqaltisc[2];         /* m=etqalt,unit=Nm :ISC����ٸ(0:����)�^(1:����) */
f4 f4g_etqalt_epwralt;              /* m=etqalt,unit=kW :�����ܰ */

static s2 s2s_etqalt_ebattsm;       /* lsb=(20*2)/128/256,unit=V :�ޯ�ؓd�� */
static s2 s2s_etqalt_ealtifsm;      /* m=etqalt,lsb=12.8/128/256,unit=A :����㎥�d�� */

/* ���̒�`(stflag8 sts_etqalt_flagi)�́Avdg_etqalt_16msl_seq()���ɒ�` */
#define bis_etqalt_expwrdec    (sts_etqalt_flagi.b0)    /* �������s�׸� */
#if JEALTCNT == u1g_EJCC_USE                            /*�y�[�d����L�z*/
#define bis_etqalt_yxaltldinco (sts_etqalt_flagi.b1)    /* ������ב����׸ޑO��l */
#endif /* JEALTCNT */

/*-------------------------------------------------------------------*/
/* �֐���prototype�錾                                               */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* �֐�                                                              */
/*-------------------------------------------------------------------*/
/*********************************************************************/
/*  �֐���        | vdg_etqalt_pwon_seq( )                           */
/*  �������e      | ����������                                       */
/*  ����^�C�~���O| pwon                                             */
/*  ����          | �Ȃ�                                             */
/*  �߂�l        | �Ȃ�                                             */
/*  ���ӎ���      |                                                  */
/*********************************************************************/
void
vdg_etqalt_pwon_seq(void)
{
    s2s_etqalt_ebattsm = s2s_etqalt_BATINT;
    s2s_etqalt_ealtifsm = s2s_etqalt_IFINT;
}

/*********************************************************************/
/*  �֐���        |  vdg_etqalt_16msl_seq( )                         */
/*  �������e      |  �d�C���׃g���N�̎Z�o                            */
/*  ����^�C�~���O|  16msl                                           */
/*  ����          |  �Ȃ�                                            */
/*  �߂�l        |  �Ȃ�                                            */
/*  ���ӎ���      |                                                  */
/*********************************************************************/
void
vdg_etqalt_16msl_seq(void)
{
    volatile static s2 s2s_etqalt_etqalttb;      /* lsb=1024/128/256,unit=Nm :�ڕW����ٸ�ް� */
    volatile static s2 s2s_etqalt_etqaltt;       /* lsb=1024/128/256,unit=Nm :�ڕW����ٸ */
    volatile static s2 s2s_etqalt_ecast;         /* lsb=536870.912/128/256,unit=ms :�n����o�ߎ��Ԕ���l */
    volatile static s2 s2s_etqalt_epwrelsrq;     /* lsb=512/128/256,unit=kW :SW���͂̓d�C���ד��� */
    volatile static s2 s2s_etqalt_etqelst;       /* lsb=1024/128/256,unit=Nm :�ڕW�d�C�����ٸ */
    volatile static s2 s2s_etqalt_etqelstb;      /* lsb=1024/128/256,unit=Nm :�ڕW�d�C�����ٸ�ް��l */
    volatile static s2 s2s_etqalt_epwrels;       /* lsb=512/128/256,unit=kW :�d�C���ד��� */
    volatile static s2 s2s_etqalt_epwrelsrqb;    /* lsb=512/128/256,unit=kW :�d�C���ד����ް��l */
    volatile static stflag8 sts_etqalt_flagi;    /* �׸ލ\����(���ԓ���������p) */
#if JEALTCNT == u1g_EJCC_USE               /*�y�[�d����L�z*/
    volatile static s2 s2s_etqalt_epwaltsoc;     /* lsb=512/128/256,unit=kW :�ڕW�d���㏸����C�����x��␳�� */
    volatile static s2 s2s_etqalt_epwaltsocb;    /* lsb=512/128/256,unit=kW :�ڕW�d���㏸����C�����x���ް��␳�� */
#endif /* JEALTCNT */
#if JEFAN != u1g_EJCC_NOT_USE              /*�y�d��̧ݗL�z*/
    volatile static s2 s2s_etqalt_epwrfan;       /* lsb=512/128/256,unit=kW :�d��̧ݓd�� */
#endif /* JEFAN */

    s2 s2t_net;                            /* lsb=(12800*2)/128/256,unit=rpm :�ŏI�ڕW��]�� */
    s4 s4t_tqalttb;                        /* lsb=1024/128/256,unit=Nm :��]���␳����ٸ */
    s4 s4t_tqaltt;                         /* lsb=1024/128/256,unit=Nm :�ڕW�I���^�g���N */
    s4 s4t_etqalt;                         /* lsb=1024/128/256,unit=Nm :���݃I���^�g���N */
    s4 s4t_dltqalttb;                      /* lsb=1024/128/256,unit=Nm :�ڕW����ٸ�ް��ω��� */
    s4 s4t_tqelst;                         /* lsb=1024/128/256,unit=Nm :�ڕW�d�C���׃g���N */
    s4 s4t_dltqelst;                       /* lsb=1024/128/256,unit=Nm :�␳�ʂƗv���l�Ƃ̕΍� */
    s4 s4t_tqgdlo;                         /* lsb=1024/128/256,unit=Nm :�g���N�����K�[�h�l */
    s4 s4t_tqgdhi;                         /* lsb=1024/128/256,unit=Nm :�g���N����K�[�h�l */
    s4 s4t_tqelsswrq;                      /* lsb=1024/128/256,unit=Nm :SW���͂̓d�C�����ٸ */
    s4 s4t_tqelstb;                        /* lsb=1024/128/256,unit=Nm :�ڕW�d�C�����ٸ�ް��l */
    s4 s4t_ne;                             /* lsb=(12800*2)/128/256,unit=rpm :�����ް�ތ�ݼ�݉�]�� */
    s4 s4t_dlpwrrqb;                       /* lsb=512/128/256,unit=kW :�ް��v���l�ω��� */
    s4 s4t_pwrelsrqb;                      /* lsb=512/128/256,unit=kW :�d�C���ד����ް��l */
    s4 s4t_pwralt;                         /* lsb=512/128/256,unit=kW :�����ܰ */
    s4 s4t_epwrelsrq;                      /* lsb=512/128/256,unit=kW :SW���͂̓d�C���ד��� */
    s4 s4t_pwrelsrq;                       /* lsb=512/128/256,unit=kW :�����OSW���͓d�C���ד��� */
    s4 s4t_pwraltadd;                      /* lsb=512/128/256,unit=kW :�����ܰ�␳�l */
    s4 s4t_pwrels;                         /* lsb=512/128/256,unit=kW :�d�C���ד��� */
    s2 s2t_dlgdl;                          /* lsb=(12800*2)/128/256,unit=rpm :�g���N�����K�[�h�l�Z�o�p���[�N */
    s2 s2t_dlgdh;                          /* lsb=(12800*2)/128/256,unit=rpm :�g���N����K�[�h�l�Z�o�p���[�N */
    s2 s2t_nettq;                          /* lsb=12800/128/256,unit=rpm :�g���N�ϊ��p�ڕW��]���ϊ��l */
    s2 s2t_tqelsto;                        /* lsb=1024/128/256,unit=Nm :�O��etqelst */
    s2 s2t_dltrqabs;                       /* lsb=1024/128/256,unit=Nm :�v���l�΍��ʔ���l */
    s2 s2t_cast_16m;                       /* lsb=536870.912/128/256,unit=ms :�n���㶳�� */
    s2 s2t_crqbchg_16m;                    /* lsb=536870.912/128/256,unit=ms :�ް��v���l�ω����� */
    s2 s2t_pwrelsrqbo;                     /* lsb=512/128/256,unit=kW :�d�C���ד����ް��l�O��l */
    s2 s2t_battsm;                         /* lsb=(20*2)/128/256,unit=V :�ޯ�ؓd�� */
    s2 s2t_altifsm;                        /* lsb=12.8/128/256,unit=A :����㎥�d�� */
    s2 s2t_altifsmo;                       /* lsb=12.8/128/256,unit=A :����㎥�d���O��l */
    s2 s2t_ktqalt;                         /* lsb=8/128/256,unit=�{ :����ٸ�␳�W�� */
    s2 s2t_cast;                           /* lsb=536870.912/128/256,unit=ms :�n����o�ߎ��Ԕ���l */
    s2 s2t_ne_l;                           /* lsb=(12800*2)/128/256,unit=rpm :�ݼ�݉�]�� */
    s2 s2t_etqalttb;                       /* lsb=1024/128/256,unit=Nm :�ڕW����ٸ�ް��l */
    u2 u2t_cast;                           /* lsb=536870.912/128/256,unit=ms :�n����o�ߎ��Ԕ���l */
    u2 u2t_yaltif;                         /* lsb=12.8/128/256,unit=A :�㎥�d�� */
    u1 u1t_xels;                           /* lsb=1 :�d�C����1�����׸� */
    u1 u1t_xac;                            /* lsb=1 :AC�����׸� */
    u1 u1t_xpwrdec;                        /* lsb=1 :�������s�׸� */
    u1 u1t_xbattClFt;                      /* lsb=1 :Circuit Low F/S���(Test Failed) */
    u1 u1t_xkne_use_c;                     /* lsb=1 :��]���␳�g�pSW */
#if JEALTCNT == u1g_EJCC_USE               /*�y�[�d����L�z*/
    s4 s4t_mpwralt;                        /* lsb=16/256/256,unit=kW :�����ܰ */
    s4 s4t_pwaltsocb;                      /* lsb=512/128/256,unit=kW :�ڕW�d���㏸����C�����x���ް��␳�� */
    s4 s4t_pwaltsoc;                       /* lsb=512/128/256,unit=kW :�ڕW�d���㏸����C�����x��␳�� */
    u4 u4t_pwaltsocb;                      /* lsb=512/128/256,unit=kW :�ڕW�d���㏸����C�����x���ް��␳�� */
    u1 u1t_yxaltldinc;                     /* lsb=1 :������ב����׸� */
    u1 u1t_yxaltldinco;                    /* lsb=1 :������ב����׸ޑO��l */
#endif /* JEALTCNT */
#if JEELS2 == u1g_EJCC_USE                 /*�yELS2�L�z*/
    u1 u1t_xels2;                          /* lsb=1 :�d�C����2�����׸� */
#endif /* JEELS2 */
    u1 u1t_xels3;                          /* lsb=1 :�d�C����3�����׸� */
    u1 u1t_xels4;                          /* lsb=1 :�d�C����4�����׸� */
#if JEELS3 == u1g_EJCC_USE                 /*�yELS3�L�z*/
    u1 u1t_xelsh1;                         /* lsb=1 :���d�C����1�����׸� */
#endif /* JEELS3 */
#if JEELS4 == u1g_EJCC_USE                 /*�yELS4�L�z*/
    u1 u1t_xelsh2;                         /* lsb=1 :���d�C����2�����׸� */
#endif /* JEELS4 */
    u1 u1t_xelsh3;                         /* lsb=1 :���d�C����3�����׸� */
    u1 u1t_xelsh4;                         /* lsb=1 :���d�C����4�����׸� */
    u1 u1t_xelsh5;                         /* lsb=1 :���d�C����5�����׸� */
#if JEPS == u1g_EJCC_EPS                   /*�y�d��PS�z*/
    u1 u1t_xpssw;                          /* lsb=1 :��ܽ�SW */
#endif /* JEPS */
#if JEAI == u1g_EJCC_USE                   /*�yAI����L�z*/
    u1 u1t_xaprly;                         /* lsb=1 :������ߍ쓮�׸�(��ݸ����) */
#endif /* JEAI */
#if (JEFAN == u1g_EJCC_ONOFF_FAN) || (JEFAN == u1g_EJCC_PWM_FAN)    /*�yON/OFF�d��̧ݕ����zOR�yPWM�d��̧ݕ����z*/
    s2 s2t_pwrfan;                         /* lsb=512/128/256,unit=kW :�d��̧ݓd�� */
#endif /* JEFAN */
#if JEFAN == u1g_EJCC_ONOFF_FAN            /*�yON/OFF�d��̧ݕ����z*/
    u1 u1t_outmnt;                         /* lsb=1 :���ݸ�̧ݏo�͏�Ԏ擾�����v�� */
#elif JEFAN == u1g_EJCC_PWM_FAN            /*�yPWM�d��̧ݕ����z*/
    u4 u4t_pwrfan;                         /* lsb=512/128/256,unit=kW :�d��̧ݓd�� */
    s4 s4t_mvoltage;                       /* lsb=20/256/256,unit=V :ϯ�ߗp�ޯ�ؓd�� */
    s2 s2t_voltage;                        /* lsb=(20*2)/128/256,unit=V :�ޯ�ؓd�� */
#endif /* JEFAN */

    /* epwrfan�i�d���t�@���d�́j�̎Z�o */
#if JEFAN == u1g_EJCC_ONOFF_FAN                 /*�yON/OFF�d��̧ݕ����z*/
    u1t_outmnt = u1g_afanif_get_outmnt();

    if ( u1t_outmnt == u1g_AFANIF_LO )          /* �d���t�@���k�n */
    {
        s2t_pwrfan = s2s_etqalt_FANLO;
    }
    else if ( u1t_outmnt == u1g_AFANIF_HI )     /* �d���t�@���g�h */
    {
        s2t_pwrfan = s2s_etqalt_FANHI;
    }
    else                                        /* �d���t�@���n�e�e */
    {
        s2t_pwrfan = (s2)(((0.)/(512./128./256.))+0.5);
    }
#elif JEFAN == u1g_EJCC_PWM_FAN                 /*�yPWM�d��̧ݕ����z*/
    s2t_voltage = s2g_afanif_get_voltage();
    ELIB_MAPU2_HILOGD( s2t_voltage, 2U, s4t_mvoltage );
                                        /* lsb=(20*2)/128/256(V) �� 20/256/256(V) */
    u4t_pwrfan = (u4)u2g_glmap1b_u2pt( (u2)s4t_mvoltage, &u1s_etqalt_epwrfan_map[0] ) >> 6;
                                        /* lsb=16/256/256(kW) �� 512/128/256(kW) */
    s2t_pwrfan = (s2)u4t_pwrfan;
#endif /* JEFAN */
#if (JEFAN == u1g_EJCC_ONOFF_FAN) || (JEFAN == u1g_EJCC_PWM_FAN)    /*�yON/OFF�d��̧ݕ����zOR�yPWM�d��̧ݕ����z*/
    s2s_etqalt_epwrfan = s2t_pwrfan;
#endif /* JEFAN */

    /* epwrelsrqb�i�d�C���ד��̓x�[�X�l�j�̎Z�o */
    s2t_pwrelsrqbo = s2s_etqalt_epwrelsrqb;
    s4t_pwrelsrqb =  (s4)(((0.)/(512./128./256.))+0.5);

    u1t_xels = u1g_exdly_exels;
    if ( u1t_xels == (u1)ON )   /* �d�C����1�����׸� */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELS;
    }

#if JEELS2 == u1g_EJCC_USE      /*�yELS2�L�z*/
    u1t_xels2 = u1g_exdly_exels2;
    if ( u1t_xels2 == (u1)ON )  /* �d�C����2�����׸� */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELS2;
    }
#endif /* JEELS2 */

    u1t_xels3 = u1g_exdly_exels3;
    if ( u1t_xels3 == (u1)ON )  /* �d�C����3�����׸� */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELS3;
    }

    u1t_xels4 = u1g_exdly_exels4;
    if ( u1t_xels4 == (u1)ON )  /* �d�C����4�����׸� */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELS4;
    }

#if JEELS3 == u1g_EJCC_USE      /*�yELS3�L�z*/
    u1t_xelsh1 = u1g_exdly_exelsh1;
    if ( u1t_xelsh1 == (u1)ON ) /* ���d�C����1�����׸� */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELSH1;
    }
#endif /* JEELS3 */

#if JEELS4 == u1g_EJCC_USE      /*�yELS4�L�z*/
    u1t_xelsh2 = u1g_exdly_exelsh2;
    if ( u1t_xelsh2 == (u1)ON ) /* ���d�C����2�����׸� */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELSH2;
    }
#endif /* JEELS4 */

    u1t_xelsh3 = u1g_exdly_exelsh3;
    if ( u1t_xelsh3 == (u1)ON ) /* ���d�C����3�����׸� */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELSH3;
    }

    u1t_xelsh4 = u1g_exdly_exelsh4;
    if ( u1t_xelsh4 == (u1)ON ) /* ���d�C����4�����׸� */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELSH4;
    }

    u1t_xelsh5 = u1g_exdly_exelsh5;
    if ( u1t_xelsh5 == (u1)ON ) /* ���d�C����5�����׸� */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELSH5;
    }

#if JEPS == u1g_EJCC_EPS        /*�y�d��PS�z*/
    u1t_xpssw = (u1)big_apsswif_xpssw;
    if ( u1t_xpssw == (u1)ON )  /* �d��PS�M�� */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELSPS;
    }
#endif /* JEPS */

#if JEFAN != u1g_EJCC_NOT_USE   /*�y�d��̧ݗL�z*/
    s4t_pwrelsrqb += (s4)s2t_pwrfan;
#endif /* JEFAN */

    u1t_xac = u1g_eacstate_exac;
    if ( u1t_xac == (u1)ON )    /* ����(��۱) */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRAC;
    }

#if JEAI == u1g_EJCC_USE        /*�yAI����L�z*/
    u1t_xaprly = (u1)big_eai_exaprly;
    if ( u1t_xaprly == (u1)ON ) /* �d��������ߕ��� */
    {
        s4t_pwrelsrqb += (s4)s2s_etqalt_PWRELSAI;
    }
#endif /* JEAI */

#if JEPTCHT_E == u1g_EJCC_USE   /*�yPTC˰��L�z*/
    s4t_pwrelsrqb += (s4)s2g_eptchctrl_epwrptc;
#endif /* JEPTCHT_E */

    ELIB_HILOGD2( s4t_pwrelsrqb, (s4)s2s_etqalt_PWRELSGD, (s4)s2g_S2MIN, s4t_pwrelsrqb );
    s2s_etqalt_epwrelsrqb = (s2)s4t_pwrelsrqb;

    s2t_battsm = s2s_etqalt_ebattsm;
    /* t_dlpwrrqb�i�x�[�X�v���l�ω��ʁj�̎Z�o */
    s4t_dlpwrrqb = s4t_pwrelsrqb - (s4)s2t_pwrelsrqbo;
    s4t_dlpwrrqb = s4g_glmulst_s4s4u2( s4t_dlpwrrqb, (s4)s2t_battsm, (u2)0U );
                    /* lsb=512/128/256(kW) * (20*2)/128/256(V) �� ((512/128/256)*((20*2)/128/256))((kW)*(V)) */
    s4t_dlpwrrqb = s4g_gldiv_s4s4( s4t_dlpwrrqb, (s4)s2s_etqalt_BATB );
                    /* lsb=((512/128/256)*((20*2)/128/256))((kW)*(V)) / (20*2)/128/256(V) �� 512/128/256(kW) */

    /* ecast�i�n����o�ߎ��Ԕ���l�j�̎Z�o */
    s2t_cast = s2s_etqalt_ecast;
    if ( u1g_exst_exastefi == (u1)OFF ) /* �n���� */
    {
        u2t_cast = u2g_glmap1b_u2pt( u2g_ethw_emthw, &u1s_etqalt_ecaltst_map[0] ) >> 8;
                        /* lsb=4194.304/256/256(ms) �� 536870.912/128/256(ms) */
        s2t_cast = (s2)u2t_cast;
        s2s_etqalt_ecast = s2t_cast;
    }

    s2t_ne_l = s2g_ene_ene;
    s2t_net = s2g_emnet_enet;
    s2t_cast_16m = s2g_exst_ecast_16m;

    u1t_xkne_use_c = u1s_etqalt_XKNE_USE;
    /* ealtifsm�i�I���^�㎥�d���j�̎Z�o */
    /* etqalttb�i�ڕW�I���^�g���N�x�[�X�l�j�̎Z�o */
    s2t_etqalttb = s2s_etqalt_TQINT;
    u1t_xbattClFt = (u1)big_wbatt_fdi_xbattClFt;
    if ( ( s2t_cast_16m >= s2t_cast )                /* �n����A����ȏ�o�� */
      && ( u1t_xbattClFt == (u1)OFF )                /* �o�b�e�����͐M���ُ�łȂ� */
#if JEALTCNT == u1g_EJCC_USE   /*�y�[�d����L�z*/
      && ( u1g_yaltlmp_yxbattlo == (u1)OFF )         /* �o�b�e���d���ቺ�łȂ� */
#endif /* JEALTCNT */
       )
    {
        s2t_altifsmo = s2s_etqalt_ealtifsm;
        u2t_yaltif = (u2)u1g_yaltinfo_yaltif << 7U;
                        /* lsb= 12.8/256(A) �� 12.8/128/256(A) */
        s2t_altifsm = s2g_glsmth_s2s2s2( s2t_altifsmo, (s2)u2t_yaltif, s2s_etqalt_ALTISM );

        if ( u1t_xkne_use_c == (u1)ON )              /* ��]���␳�g�p�� */
        {
            s4t_tqalttb = s4g_glmul_s2s2( s2g_yaltinfo_yalttrq, s2t_ne_l );
                        /* lsb= 1024/128/256(Nm) * (12800*2)/128/256(rpm) -> 800/128/256(Nm*rpm) */
            s4t_tqalttb = (s4)s2g_gldiv_s4s2( s4t_tqalttb, s2t_net );
                        /* lsb= 800/128/256(Nm*rpm) / (12800*2)/128/256(rpm) -> 1024/128/256(Nm) */
        }
        else                                         /* ��]���␳�g�p���łȂ� */
        {
            s4t_tqalttb = (s4)s2g_yaltinfo_yalttrq;
        }

        s2t_etqalttb = s2s_etqalt_etqalttb;
        s4t_dltqalttb = s4t_tqalttb - (s4)s2t_etqalttb;
        if ( s4t_dltqalttb < (s4)(((0.)/(1024./128./256.))+0.5) )
        {
            s4t_dltqalttb = -s4t_dltqalttb;
        }

        if ( s4t_dltqalttb >= (s4)s2s_etqalt_TQHYS ) /* �d�l���Ƌt���� */
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

    /* etqaltt�i�ڕW�I���^�g���N�j�̎Z�o */
    s2t_ktqalt = s2g_glmap3hs_s2s2s2pt( s2t_ne_l, s2t_altifsm, s2t_battsm, &s2s_etqalt_ektqalt_map[0] );
    s4t_tqaltt = (s4)s2g_glmulst_s2s2u2( s2t_etqalttb, s2t_ktqalt, (u2)12U );
                           /* lsb= 1024/128/256(Nm) * 8/128/256(�{) -> 1024/128/256(Nm) */
    s2s_etqalt_etqaltt = (s2)s4t_tqaltt;

    s2t_nettq = s2g_glmulst_s2s2u2( s2t_net, (s2)2, (u2)0U );     /* �V�t�g���� */
                           /* lsb=(12800*2)/128/256(rpm) �� 12800/128/256(rpm) */

    /* epwralt�i�I���^�p���[�j�̎Z�o */
    ELIB_CONV_TTOP( (s2)s4t_tqaltt, s2t_nettq, s4t_pwralt );     /* �g���N���p���[�ɕϊ� */
    f4g_etqalt_epwralt = (f4)s4t_pwralt * (f4)(512./128./256.);

#if JEALTCNT == u1g_EJCC_USE   /*�y�[�d����L�z*/
    /* epwaltsocb�i�ڕW�d���㏸����C�����x��x�[�X�␳�ʁj�̎Z�o */
    u1t_yxaltldinco = (u1)bis_etqalt_yxaltldinco;
    u1t_yxaltldinc = (u1)big_ysocpublic_yxaltldinc;

    if ( ( s2t_cast_16m >= s2s_etqalt_CASTALTDLY )               /* �n���㏊�莞�Ԍo�� */
      && ( ( u1t_yxaltldinco == (u1)OFF )                        /* �I���^���ב���֕ω��� */
        && ( u1t_yxaltldinc == (u1)ON ) ) )
    {
        ELIB_MAPU2_HILOGD( s4t_pwralt, 6U, s4t_mpwralt );
                                        /* lsb=512/128/256(kW) �� 16/256/256(kW) */
        u4t_pwaltsocb = (u4)u2g_glmap1b_u2pt( (u2)s4t_mpwralt, &u1s_etqalt_epwaltsocb_map[0] ) >> 8;
                                        /* lsb=4/256/256(kW) �� 512/128/256(kW) */
        s4t_pwaltsocb = (s4)u4t_pwaltsocb;
    }
    else if ( u1t_yxaltldinc == (u1)ON )                         /* �I���^���ב���p���� */
    {
        s4t_pwaltsocb = (s4)s2s_etqalt_epwaltsocb;
        s4t_pwaltsocb -= (s4)s2s_etqalt_DECALT;
        ELIB_HILOGD2( s4t_pwaltsocb, (s4)s2g_S2MAX, (s4)(((0.)/(512./128./256.))+0.5), s4t_pwaltsocb );
    }
    else                                                         /* ��L�ȊO */
    {
        s4t_pwaltsocb = (s4)(((0.)/(512./128./256.))+0.5);
    }
    s2s_etqalt_epwaltsocb = (s2)s4t_pwaltsocb;
    glbitcp_bibi( u1t_yxaltldinc, bis_etqalt_yxaltldinco );

    /* epwaltsoc�i�ڕW�d���㏸����C�����x��␳�ʁj�̎Z�o */
    ELIB_HIGHGD2( s4t_pwaltsocb, (s4)s2s_etqalt_PWALTSOCGD, s4t_pwaltsoc );
    s2s_etqalt_epwaltsoc = (s2)s4t_pwaltsoc;
#endif /* JEALTCNT */

    /* t_pwrelsrq�i�����O�r�v���͓d�C���ד��́j�̎Z�o */
    if ( s4t_pwrelsrqb > (s4)s2t_pwrelsrqbo )                         /* �d�C���ד��̓x�[�X�l�������� */
    {
        s4t_pwrelsrq = (s4)s2s_etqalt_epwrels;
    }
    else                                                              /* �d�C���ד��̓x�[�X�l���������łȂ� */
    {
        s4t_pwrelsrq = (s4)s2s_etqalt_epwrelsrq;
    }
    s4t_pwrelsrq = s4g_gladdst_s4s4( s4t_pwrelsrq, s4t_dlpwrrqb );
    ELIB_LOWGD2( s4t_pwrelsrq, (s4)(((0.)/(512./128./256.))+0.5), s4t_pwrelsrq );

    /* ecdecdly_16m�i���σf�B���[�J�E���^�j�̎Z�o */
    /* expwrdec�i�������s�t���O�j�̎Z�o */
    if ( s4t_dlpwrrqb > (s4)s2s_etqalt_DLPWR )                        /* �ް��v���l������ */
    {
        u1t_xpwrdec = (u1)OFF;
        s2g_etqalt_ecdecdly_16m = (s2)(((0.)/(536870.912/128./256.))+0.5);
    }
    else if ( ( s2g_etqalt_ecdecdly_16m >= s2s_etqalt_CDECDLY )       /* ���莞�Ԍo�� */
           || ( s4t_pwrelsrqb <= (s4)(((0.)/(512./128./256.))+0.5) )  /* �ް��d�C���ז��� */
           || ( s4t_pwrelsrq <= s4t_pwralt ) )                        /* SW���͂̓d�C���ׂ������ܰ�ȉ� */
    {
        u1t_xpwrdec = (u1)ON;
    }
    else
    {
        u1t_xpwrdec = (u1)bis_etqalt_expwrdec;
    }
    glbitcp_bibi( u1t_xpwrdec, bis_etqalt_expwrdec );

    /* epwrelsrq�i�r�v���͂̓d�C���ד��́j�̎Z�o */
    s4t_epwrelsrq = s4t_pwrelsrq;
    if ( u1t_xpwrdec == (u1)ON )                                      /* �����������s */
    {
        s4t_epwrelsrq = s4g_glmulst_s4s4u2( s4t_pwrelsrq, (s4)s2s_etqalt_DECRTO, (u2)14U );
                    /* lsb=512/128/256(kW) * 2/128/256(�{) �� 512/128/256(kW) */
    }
    ELIB_HILOGD2( s4t_epwrelsrq, (s4)s2g_S2MAX, (s4)s2g_S2MIN, s4t_epwrelsrq );
    s2s_etqalt_epwrelsrq = (s2)s4t_epwrelsrq;

    /* epwrels�i�d�C���ד��́j�̎Z�o */
#if JEALTCNT == u1g_EJCC_USE   /*�y�[�d����L�z*/
    s4t_pwraltadd = s4t_pwralt + s4t_pwaltsoc;
#else                          /*�y�[�d���䖳�z*/
    s4t_pwraltadd = s4t_pwralt;
#endif /* JEALTCNT */
    ELIB_MAXSLCT2( s4t_epwrelsrq, s4t_pwraltadd, s4t_pwrels );
    ELIB_HIGHGD2( s4t_pwrels, (s4)s2g_S2MAX, s4t_pwrels );
    s2s_etqalt_epwrels = (s2)s4t_pwrels;

    /* t_tqelsswrq�i�r�v���͂̓d�C���׃g���N�j*/
    ELIB_CONV_PTOT( (s2)s4t_epwrelsrq, s2t_nettq, s4t_tqelsswrq );        /* �p���[���g���N�ɕϊ� */

    /* etqelstb�i�ڕW�d�C���׃g���N�x�[�X�l�j�̎Z�o */
    ELIB_MAXSLCT2( s4t_tqaltt, s4t_tqelsswrq, s4t_tqelstb );
    s2s_etqalt_etqelstb = (s2)s4t_tqelstb;                                /* t_tqaltt, t_tqelsswrq �͋���s2�͈͓��Ȃ̂ŷ���OK */

    /* ecrqbchg_16m�i�x�[�X�v���l�ω��J�E���^�j�̃N���A */
    s2t_crqbchg_16m = s2g_etqalt_ecrqbchg_16m;
    if ( s4t_dlpwrrqb != (s4)(((0.)/(512./128./256.))+0.5) )              /* �x�[�X�v���l�ω��� */
    {
        s2t_crqbchg_16m = (s2)(((0.)/(536870.912/128./256.))+0.5);
        s2g_etqalt_ecrqbchg_16m = s2t_crqbchg_16m;
    }

    /* t_dltrqabs�i�΍��ʔ���l�j�̎Z�o */
    s2t_dltrqabs = s2s_etqalt_DLTQABSL;
    if ( s2t_crqbchg_16m < s2s_etqalt_CDECHYS )   /* �x�[�X�v���l�ω��㏊�莞�Ԗ��� */
    {
        s2t_dltrqabs = s2s_etqalt_DLTQABSH;
    }

    /* t_tqgdlo�i�g���N�����K�[�h�l�j�At_tqgdhi�i�g���N����K�[�h�l�j�̎Z�o */
    s2t_tqelsto = s2s_etqalt_etqelst;

    s4t_dltqelst = s4t_tqelstb - (s4)s2t_tqelsto;
    s4t_dltqelst = s4g_glabs_s4( s4t_dltqelst );

    s2t_dlgdl = s2s_etqalt_DLGDMXL;
    s2t_dlgdh = s2s_etqalt_DLGDMXH;
    if ( s4t_dltqelst < (s4)s2t_dltrqabs )        /* �␳�ʂƗv���l�Ƃ̕΍��� */
    {
        s2t_dlgdl = s2s_etqalt_DLGDMNL;
        s2t_dlgdh = s2s_etqalt_DLGDMNH;
    }
    s4t_tqgdlo = (s4)s2t_tqelsto - (s4)s2t_dlgdl;
    s4t_tqgdhi = (s4)s2t_tqelsto + (s4)s2t_dlgdh;

    /* etqelst�i�ڕW�d�C���׃g���N�j�̎Z�o */
    ELIB_HILOGD2( s4t_tqelstb, s4t_tqgdhi, s4t_tqgdlo, s4t_tqelst );
    ELIB_HILOGD2( s4t_tqelst, (s4)s2g_S2MAX, (s4)s2g_S2MIN, s4t_tqelst );
    s2s_etqalt_etqelst = (s2)s4t_tqelst;

    /* etqaltisc[0]�iISC�ڕW�I���^�g���N(����)�j�Aetqaltisc[1]�iISC���݃I���^�g���N(����)�j�̎Z�o */
    s2g_etqalt_etqaltisc[0] = (s2)s4t_tqelst;    /* ����s2�Ȃ̂�s2�L���X�g�� */
    f4g_etqalt_etqaltisc[0] = (f4)s4t_tqelst * (f4)(1024./128./256.);
    s2g_etqalt_etqaltisc[1] = (s2)s4t_tqelst;    /* �Z�o����S2�K�[�h�ς� */
    f4g_etqalt_etqaltisc[1] = (f4)s4t_tqelst * (f4)(1024./128./256.);

    /* etqalt�i���݃I���^�g���N�j�̎Z�o */
    s4t_etqalt = s4t_tqaltt;
    if ( u1t_xkne_use_c == (u1)ON )         /* ��]���␳�g�p�� */
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
/*  �֐���        |  vdg_etqalt_65msl_seq( )                         */
/*  �������e      |  �o�b�e���d���̎Z�o                              */
/*  ����^�C�~���O|  65msl                                           */
/*  ����          |  �Ȃ�                                            */
/*  �߂�l        |  �Ȃ�                                            */
/*  ���ӎ���      |                                                  */
/*********************************************************************/
void
vdg_etqalt_65msl_seq(void)
{
    s2s_etqalt_ebattsm = s2g_glsmth_s2s2s2( s2s_etqalt_ebattsm, s2g_cpowif_b, s2s_etqalt_BATNSM );
}

/**** End of File ****************************************************/
