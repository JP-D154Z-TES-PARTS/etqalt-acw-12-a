/* etqalt-pcw00-1200-a-M3 */
/*********************************************************************/
/*  Copyright Toyota Motor Corporation                               */
/*********************************************************************/

/*********************************************************************/
/*  �I�u�W�F�N�g�� | �d�C���׃g���N                                  */
/*  ���ӎ���       |�y����Ȱ�ެ�L�z                                  */
/*-------------------------------------------------------------------*/
/* I/F�ύX����     | -11 �S�̃R���p�C��SW�y����Ȱ�ެ�L�z�ǉ�         */
/*-------------------------------------------------------------------*/
/*  �t�@�C���\��   | etqalt_l_mat.c, etqalt_c_mat.c                  */
/*-------------------------------------------------------------------*/
/*     �ʕύX���� �i�ʕύX���͈ȉ��ɕύX���A���e���L�����邱�Ɓj */
/*********************************************************************/

#ifndef ETQALT_H
#define ETQALT_H

/*-------------------------------------------------------------------*/
/* �w�b�_�t�@�C���̃C���N���[�h                                      */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* �^��`                                                            */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* �}�N����`                                                        */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* �֐�                                                              */
/*-------------------------------------------------------------------*/
void vdg_etqalt_pwon_seq( void );          /* ���������� */
                                           /* �R�[���� : vdg_etranfwdmng_pwon() */
                                           /* ���O������ : ���� */

void vdg_etqalt_16msl_seq( void );         /* �d�C���׃g���N�̎Z�o */
                                           /* �R�[���� : vdg_etranfwdmng_16msl() */

void vdg_etqalt_65msl_seq( void );         /* �o�b�e���d���̎Z�o */
                                           /* �R�[���� : vdg_etranfwdmng_65msl() */

/*-------------------------------------------------------------------*/
/* ���J�ϐ�                                                          */
/*-------------------------------------------------------------------*/
extern s2 s2g_etqalt_etqalt;               /* m=etqalt,lsb=1024/128/256,unit=Nm :���ݵ���ٸ */
                                           /* �X�V�^�C�~���O : 16msl */

extern f4 f4g_etqalt_etqalt;               /* m=etqalt,unit=Nm :���ݵ���ٸ */
                                           /* �X�V�^�C�~���O : 16msl */

extern f4 f4g_etqalt_etqaltisc[2];         /* m=etqalt,unit=Nm :ISC����ٸ(0:����)�^(1:����) */
                                           /* ���ӎ��� : etqaltisc[0] = ISC�ڕW����ٸ(����) */
                                           /*            etqaltisc[1] = ISC���ݵ���ٸ(����) */
                                           /* �X�V�^�C�~���O : 16msl */

extern f4 f4g_etqalt_epwralt;              /* m=etqalt,unit=kW :�����ܰ */
                                           /* �X�V�^�C�~���O : 16msl */
extern s2 s2g_etqalt_etqaltisc[2];         /* m=etqalt,lsb=1024/128/256,unit=Nm :ISC����ٸ(0:����)�^(1:����) */
                                           /* ���ӎ��� : etqaltisc[0] = ISC�ڕW����ٸ(����) */
                                           /*            etqaltisc[1] = ISC���ݵ���ٸ(����) */
                                           /* �X�V�^�C�~���O : 16msl */

/*-------------------------------------------------------------------*/
/* �K���萔                                                          */
/*-------------------------------------------------------------------*/
/* ����J(���i�����̂�) */
extern volatile const s2 s2s_etqalt_NEGD;             /* lsb=(12800*2)/128/256,unit=rpm :NE�����ް�ޒl */
extern volatile const s2 s2s_etqalt_CDECHYS;          /* lsb=536870.912/128/256,unit=ms :�v���l�ω��o�ߎ��� */
extern volatile const s2 s2s_etqalt_DLTQABSH;         /* lsb=1024/128/256,unit=Nm :�v���l�΍��ʔ���lHI */
extern volatile const s2 s2s_etqalt_DLTQABSL;         /* lsb=1024/128/256,unit=Nm :�v���l�΍��ʔ���l */
extern volatile const s2 s2s_etqalt_BATINT;           /* lsb=(20*2)/128/256,unit=V :�ޯ�ؓd�������l */
extern volatile const s2 s2s_etqalt_BATB;             /* lsb=(20*2)/128/256,unit=V :��d�� */
extern volatile const s2 s2s_etqalt_DLGDMNL;          /* lsb=1024/128/256,unit=Nm :�΍������̏��ϗ�(����) */
extern volatile const s2 s2s_etqalt_DLGDMNH;          /* lsb=1024/128/256,unit=Nm :�΍������̏��ϗ�(����) */
extern volatile const s2 s2s_etqalt_DLGDMXL;          /* lsb=1024/128/256,unit=Nm :�΍��厞�̏��ϗ�(����) */
extern volatile const s2 s2s_etqalt_DLGDMXH;          /* lsb=1024/128/256,unit=Nm :�΍��厞�̏��ϗ�(����) */
extern volatile const s2 s2s_etqalt_TQNSM;            /* lsb=256/128/256,unit=�� :����ٸ�Ȃ܂��萔 */
extern volatile const s2 s2s_etqalt_TQHYS;            /* lsb=1024/128/256,unit=Nm :����ٸ˽ */
extern volatile const s2 s2s_etqalt_TQINT;            /* lsb=1024/128/256,unit=Nm :����ٸ�����l */
extern volatile const s2 s2s_etqalt_CDECDLY;          /* lsb=536870.912/128/256,unit=ms :���ϊJ�n�ިڰ���� */
extern volatile const s2 s2s_etqalt_DLPWR;            /* lsb=512/128/256,unit=kW :�ް��v���l��������l */
extern volatile const s2 s2s_etqalt_DECRTO;           /* lsb=2/128/256,unit=�{ :���ϗ� */
extern volatile const s2 s2s_etqalt_PWRELSGD;         /* lsb=512/128/256,unit=kW :�d�C���׏���ް�ޒl */
extern volatile const s2 s2s_etqalt_PWRELS;           /* lsb=512/128/256,unit=kW :�d�C����1 */
extern volatile const s2 s2s_etqalt_PWRELS2;          /* lsb=512/128/256,unit=kW :�d�C����2�yELS2�L�z */
extern volatile const s2 s2s_etqalt_PWRELS3;          /* lsb=512/128/256,unit=kW :�d�C����3 */
extern volatile const s2 s2s_etqalt_PWRELS4;          /* lsb=512/128/256,unit=kW :�d�C����4 */
extern volatile const s2 s2s_etqalt_PWRELSH1;         /* lsb=512/128/256,unit=kW :���d�C����1�yELS3�L�z */
extern volatile const s2 s2s_etqalt_PWRELSH2;         /* lsb=512/128/256,unit=kW :���d�C����2�yELS4�L�z */
extern volatile const s2 s2s_etqalt_PWRELSH3;         /* lsb=512/128/256,unit=kW :���d�C����3 */
extern volatile const s2 s2s_etqalt_PWRELSH4;         /* lsb=512/128/256,unit=kW :���d�C����4 */
extern volatile const s2 s2s_etqalt_PWRELSH5;         /* lsb=512/128/256,unit=kW :���d�C����5 */
extern volatile const s2 s2s_etqalt_PWRELSPS;         /* lsb=512/128/256,unit=kW :�d����ܽÕ��ׁy�d��PS�z */
extern volatile const s2 s2s_etqalt_FANLO;            /* lsb=512/128/256,unit=kW :�d��̧�LO���ׁyON/OFF�d��̧ݕ����z */
extern volatile const s2 s2s_etqalt_FANHI;            /* lsb=512/128/256,unit=kW :�d��̧�HI���ׁyON/OFF�d��̧ݕ����z */
extern volatile const s2 s2s_etqalt_PWRELSAI;         /* lsb=512/128/256,unit=kW :�d��������ߕ��ׁyAI����L�z */
extern volatile const s2 s2s_etqalt_PWRAC;            /* lsb=512/128/256,unit=kW :���ݕ��� */
extern volatile const s2 s2s_etqalt_PWALTSOCGD;       /* lsb=512/128/256,unit=kW :�ڕW�d���㏸����C�����x��␳�ʏ���ް�ޒl�y�[�d����L�z */
extern volatile const s2 s2s_etqalt_CASTALTDLY;       /* lsb=536870.912/128/256,unit=ms :�n���㎞�Ԕ���l�y�[�d����L�z */
extern volatile const s2 s2s_etqalt_DECALT;           /* lsb=512/128/256,unit=kW :�ڕW�d���㏸����C�����x�ꌸ���ʁy�[�d����L�z */
extern volatile const s2 s2s_etqalt_BATNSM;           /* lsb=256/128/256,unit=�� :�ޯ�ؓd���Ȃ܂��萔 */
extern volatile const s2 s2s_etqalt_ALTISM;           /* m=etqalt,lsb=256/128/256,ofs=,unit=�� :�㎥�d�����׋}�ώ��Ȃ܂���(LIN) */
extern volatile const s2 s2s_etqalt_IFINT;            /* m=etqalt,lsb=12.8/128/256,ofs=,unit=A :����㎥�d�������l */
extern volatile const u1 u1s_etqalt_XKNE_USE;         /* m=etqalt,lsb=-,ofs=,unit=- :��]���␳�g�pSW */

/*-------------------------------------------------------------------*/
/* �K���}�b�v                                                        */
/*-------------------------------------------------------------------*/
/* ����J(���i�����̂�) */
#pragma ghs startdata
extern volatile const s2 s2s_etqalt_ektqalt_map[];    /* m=etqalt,�ڕW����ٸ��]���␳ϯ�� */
extern volatile const u1 u1s_etqalt_ecaltst_map[];    /* �n����o�ߎ��Ԕ���lϯ�� */
extern volatile const u1 u1s_etqalt_epwrfan_map[];    /* �d��̧ݕ���ϯ�߁yPWM�d��̧ݕ����z */
extern volatile const u1 u1s_etqalt_epwaltsocb_map[]; /* �ڕW�d���㏸����C�����x���ް��␳��ϯ�߁y�[�d����L�z */
extern volatile const s2 s2s_etqalt_eifint_map[];     /* m=etqalt,����㎥�d��ϯ�� */
#pragma ghs enddata

/*-------------------------------------------------------------------*/
/* �I�[�g�J�E���^                                                    */
/*-------------------------------------------------------------------*/
extern s2 s2g_etqalt_ecdecdly_16m;           /* ����J lsb=536870.912/128/256,unit=ms :�����ިڰ���� */
extern s2 s2g_etqalt_ecrqbchg_16m;           /* ����J lsb=536870.912/128/256,unit=ms :�ް��v���l�ω����� */

#endif  /* ETQALT_H */
/**** End of File ****************************************************/
