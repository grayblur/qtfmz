/******************************************************************************
* Copyright (c) 2007, Shangdong Fisherman Information Technology Co., Ltd.
* All rights reserved.
* �ļ�����: fm_sic_cmd_def.h
* �ļ�����: ������������Կ���������ļ�
* ��ǰ�汾: 1.0
* ��    ��:
* ����ʱ��: 2007-01-08
* �޸ļ�¼:
* ----------------------------------------------
*    ʱ��    ����     ����
******************************************************************************/

/******** API֧�ֵ��豸��Ŀ ********/
#define SIC_UKEY_NUM           24
#define FM_SCSI_CMD_LEN        12

//����
#define U_KEY_IOCTL_test CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define U_KEY_IOCTL_SETEVENT CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*******************������************************/
#define CONFIGVER       0X00

#define VERIFYPIN       0x20
#define CHANGEPIN       0x21
#define LOGOUTCLEAR     0x24
#define SETAUTH         0x25
#define GETGDBAUTH      0x27


#define UKEY_CMD        0xb6
#define UD_SRNUM        0xb7
#define UKEYTEST        0xff

#define DOWMTEST        0x30

#define GETFILETREE     0x3b    // get file tree
#define FILESYSINIT     0x3e    // file system init

#define DESENDECRYPT    0x64

#define GETCHALLENGE    0x84    // get challenge

#define SELECTFILE      0xA4    // select file
#define READBINARY      0xB0    // read binary
#define READRECORD      0xB2    // read record

#define WRITEBINARY     0xD0    // write binary
#define WRITEKEY        0xD4    // write key
#define UPDATEBINARY    0xD6    // update binary
#define UPDATERECORD    0xDC    // update record

#define CREATEFILE      0xE0    // creat file
#define APPENDRECORD    0xE2    // append record
#define DELETEFILE      0xE4    // delete file

#define DELSYMKEY		0x90
#define EXPORTSYMKEY    0x9F

#define RWTEST          0xF1
#define CREATEDIR       0xF2
#define DELETEDIR       0xF3
#define ENUMDIR         0xF4
#define ENUMFILE        0xF5
#define READFILE        0XC6
#define WRITEFILE       0XC7

#define IMPORTSYMKEY    0x98

#define SYMINIT         0XE9
#define SYMUPDATE       0XEB
#define SYMFINAL        0XEC
#define SYMENCYPT       0X9A

#define SYMINIT_NEW         0XF9
#define SYMUPDATE_NEW       0XFB

#define HASHINIT        0X94
#define HASH            0X02
#define HASHUPDATE      0X95
#define HASHFINAL       0X96
#define HASHINIT_256    0x91
#define HASHUPDATE_256  0x92
#define HASHFINAL_256   0x93

#define GETFILEINFO     0x05

#define INITDEVINO		0x40
#define GETDEVINO		0x41
#define SICINTAUTH  	0x52
#define SICEXTAUTH 		0x53
#define SICAUTHRAND     0x54

#define GENERATERSAKEY 	0x44
#define RSASIGNDATA 	0x45
#define RSAVERIFY	    0x4E
#define GETRSABIT	    0x4F
#define CARDWR          0x47
#define CARDRD          0x48

#define DELRSAKEY       0x49
#define IMPORTRSAKEY    0x4D
#define EXPORTRSAKEY    0x4B

#define CMD_RDBACK      0x8F
#define CMD_USERID_GET  0x61
#define CMD_USERID_INIT 0x62
#define CMD_DEVSER_INIT 0x64
#define KCW_SIGN        0xa5
#define KSW_SIGN        0x5a

#define RSA_FUNC        0x71    // RSA ��ʾ
#define ECC_FUNC        0x72    // ECC ��ʾ
#define RNG_FUNC        0x73    // RNG ��ʾ
#define USB_FUNC        0x74    // USB ��ʾ
#define SSF33_FUNC      0x75    // 33 ��ʾ
#define INT_FUNC        0x76    // �ж� ��ʾ
#define BOOT_MODE       0x77    // �ָ���COS����ģʽ

#define ECC_INIT            0x70
#define ECC_KEY_GENERATE    0x78
#define ECC_SIGNDATA        0x79
#define ECC_VERIFY          0x7A
#define ECC_ENCRYPT         0x7B
#define ECC_DECRYPT         0x7C
#define ECC_KEY_DEL         0x7D
#define ECC_KEY_IMPORT      0x7E
#define ECC_KEY_EXPORT      0x7F

#define GET_KEY_INFO         0x87
#define ECC_ALG_GEN_KEY_DATA 0x8A
#define ECC_ALG_GEN_KEY      0x8B

#define SM3_INIT_SOFT        0x8C
#define SM3_UPDATE_SOFT      0x8D
#define SM3_FINAL_SOFT       0x8E

#define SYM_EN 0
#define SYM_DE 1
#define SM4_EN 10
#define SM4_DE 11

#define SYM_DES              0xe6
#define SYM_TDES             0xe7
#define SYM_SM1              0xe8
#define SYM_SSF33            0xe9
#define SYM_SM4              0xea

/**********������**********/
/******** 32 bit error code stucture*******
+++++++++++++++++++++++++++++++++++++++++
|    9b     |      12b     |    11b     |
+++++++++++++++++++++++++++++++++++++++++*/
#define SETERR(f, l, e) (((f) << 23) | (((l) & 0xfff) << 11) | ((e) & 0x7ff))

/************************ RSA ************************/
//RSA��Կ�洢����
#define SIC_RSA_KEYLEN_512       512
#define SIC_RSA_KEYLEN_1024      1024
#define SIC_RSA_KEYLEN_2048      2048

#define SIC_RSA_KEYTYPE_512      1
#define SIC_RSA_KEYTYPE_1024     2
#define SIC_RSA_KEYTYPE_2048     3

/************************ �Գ��㷨���� ************************/
#define SIC_SYMKEY_NUM_LKEY     17  //17 /* �Գ���Կ�洢�������Կ�洢��Ŀ */
#define SIC_SYMKEY_NUM          128 //1024 /* �Գ���Կ�洢�������Կ�洢��Ŀ */
#define SIC_SYMKEY_NUM_TF       256

/************************  �ǶԳƶԳ��㷨���� ************************/
#define SIC_ASYMKEY_NUM_LKEY    6
#define SIC_ASYMKEY_NUM         32
#define SIC_ASYMKEY_NUM_TF      128

#define SIC_SYMKEY_LEN          16  /* ���뻺�����ֽڳ��� ���16*8=128bit */
#define SIC_DES_KEY_LEN         8
#define SIC_3DES_KEY_LEN        24
#define SIC_MAX_SYM_KEY_LEN     32

#define SIC_SM1_IV_LEN 16
#define SIC_DES_IV_LEN 8
#define SIC_3DES_IV_LEN 8
#define SIC_MAX_IV_LEN 16

/************************ HASH�㷨���� ************************/
// SHA1����������
#define SIC_SHA_SIV_BUF_LEN      20  /* SHA��ʼ�����������ֽڳ��� */

// ���Ŀ¼��
#define SIC_MAX_DIR_NUM          64

//����ļ���
#define SIC_MAX_FILE_NUM_LKEY   32
#define SIC_MAX_FILE_NUM        256

/******************���ݻ�����**********************/
#define SIC_GENERAL_BOLOCK_LEN 16
#define SIC_MAX_EXCHANGE_LEN 1024
#define SIC_MAX_EXCHANGE_LEN_NEW_3040 3040
#define SIC_MAX_EXCHANGE_LEN_NEW_3072 3072
#define SIC_MAX_EXCHANGE_LEN_NEW_4096 4096

#define SIC_MAX_RANDOM_LEN_LKEY   255
#define SIC_MAX_RANDOM_LEN_TF     9216//10224 //4080
#define SIC_MAX_RANDOM_LEN        SIC_MAX_EXCHANGE_LEN

#define SIC_MAX_RWFILE_LEN        SIC_MAX_EXCHANGE_LEN
#define SIC_MAX_SYMEN_LEN         SIC_MAX_EXCHANGE_LEN
#define SIC_MAX_HASH_LEN          SIC_MAX_EXCHANGE_LEN

#define SIC_MAX_RWFILE_LEN_TF     9216//10132 //3988
#define SIC_MAX_SYMEN_LEN_TF      9216//10144 //4000
#define SIC_MAX_HASH_LEN_TF       9216//10124 //3980
//RSA��ʱ��Կ
#define SIC_RSA_MAX_ELEN          256

#define FM_SIC_PUBLICKEY_ENABLE   1
#define FM_SIC_PRIVATEKEY_ENABLE  2
#define FM_SIC_BOTH_ENABLE        3
#define FM_SIC_INVALID            0xffffffff

/**********************���������ݽṹ********************************/
typedef struct tag_FileAttribute_St
{
    FM_S8 as8FileName[SIC_FILE_NAME_LEN];
    FM_U32 u32Createsize;
    FM_U32 u32FileID;
    FM_U32 u32Usedspace;
    FM_U32 u32AccessControl;
}FILEATTRIBUTE;

/* ˫����֤��Կ����Կͷ */
typedef struct tag_KeyHead_St
{
    FM_U8  u8ApplicationType;   // ��֤��Կ��Ӧ������
    FM_U8  u8KeyLen;            // ��Կֵ���ȣ����ֽڼ���
    FM_U8  u8ErrCnt;            // �������������4λΪ�������������4λΪʣ�ೢ�Դ���
/*ǰ����淶�涨����ΪӦ����ʹ��*/
    FM_U8  u8AccCtl;            // ��Կ���ʿ���Ȩ�ޣ���4λΪʹ��Ȩ�ޣ���4λΪ�޸�Ȩ�ޡ�
    FM_U8  u8SubState;          // ��Կ��֤ͨ����İ�ȫ״̬����4λ�����壬��4λΪ����״̬��
                                // �ڲ���֤��Կ���ⲿ��֤��Կֻ�����豸���˫����֤��ֻ��
                                // ֤�豸�Ϸ��ԣ�һ�㲻����������ȫ״̬��
}KEYHEAD;

typedef struct tag_FileOpe_St
{
    FM_U32 u32DirNameLen;
    FM_S8 as8DirName[(SIC_FILE_NAME_LEN + 1) * SIC_FILE_DIRDEPTH + 1];
    FM_U32 u32FileNameLen;
    FM_S8 as8FileName[SIC_FILE_NAME_LEN];
    FM_U32 u32FileSize;
    FM_U32 u32AccCond;
    FM_U32 u32Offset;
    FM_U32 u32Size;
}FILEOPE;

typedef struct tag_Card_St
{
    FM_U32 u32Offset;
    FM_U32 u32Size;
}CARDST;

typedef struct tag_EnumList_St
{
    FM_U32 u32Num;  //ö�ٵ��ļ���Ŀ¼��Ŀ
    FM_U32 u32Len;  //ʵ��ʹ�õ�ö�ٵĻ��������ȡ��ļ���Ŀ¼��\0�ָ�������һ��\0

    //�˴�SIC_MAX_DIR_NUMӦ��ΪSIC_MAX_FILE_NUM��ͬʱCOS��Ҳ��Ҫ�޸�
    FM_S8 as8FileName[SIC_MAX_DIR_NUM * (SIC_FILE_NAME_LEN + 1)];
}ENUMLIST;

typedef struct tag_EnumList_tf_St
{
    FM_U32 u32Num;  //ö�ٵ��ļ���Ŀ¼��Ŀ
    FM_U32 u32Len;  //ʵ��ʹ�õ�ö�ٵĻ��������ȡ��ļ���Ŀ¼��\0�ָ�������һ��\0

    FM_S8 as8FileName[SIC_MAX_FILE_NUM * (SIC_FILE_NAME_LEN + 1)];
}ENUMLIST_TF;


typedef struct tag_AuthPin_St
{
    FM_U32 u32UserType;
    FM_U8 au8UserPIN[16];
    FM_U8 au8AdminPIN[16];
    FM_U8 u8UserPINLen;
    FM_U8 u8AdminPINLen;
}AUTHPIN;

typedef struct tag_SicRsaKeyInfo_St
{
	FM_U32 u32KeyBits;    //RSAλ��
	FM_U32 u32KeyFlag;    //��2�ֽڱ�ʾ��Կ������ �����ֽڱ�ʾ˽Կ������
	FM_U32 u32EBitLen;    //������Կʱ
	FM_U32 u32KeyIndex;
	FM_U32 u32E;
}SICRSAKEYINFO;

typedef struct tag_SicRsaKeyBody_St
{
	FM_U32 u32ELen;
	FM_U32 au32E[FM_RSA_MAX_LEN/4+1];
	FM_U32 u32NLen;
	FM_U32 au32N[FM_RSA_MAX_LEN/4+1];
	FM_U32 u32PLen;
	FM_U32 au32P[FM_RSA_MAX_PLEN/4+1];
	FM_U32 u32QLen;
	FM_U32 au32Q[FM_RSA_MAX_PLEN/4+1];
	FM_U32 u32QinvLen;
	FM_U32 au32Qinv[FM_RSA_MAX_PLEN/4+1];
	FM_U32 u32DPLen;
	FM_U32 au32DP[FM_RSA_MAX_PLEN/4+1];
	FM_U32 u32DQLen;
	FM_U32 au32DQ[FM_RSA_MAX_PLEN/4+1];
	FM_U32 u32DLen;
	FM_U32 au32D[FM_RSA_MAX_LEN/4];
	SICRSAKEYINFO stRsaKeyInfo;
}SICRSAKEYBODY; //1488�ֽ�

typedef struct tag_RsaEncrypt_St
{
	FM_U32 u32KeyIndex;
	FM_U32 u32RsaBits;
	FM_U32 u32Inlen;
	FM_U32 au32Inbuf[FM_RSA_MAX_LEN / 4 + 1];
	FM_U32 u32Elen;
	FM_U32 au32E[FM_RSA_MAX_LEN / 4 + 1];
	FM_U32 u32Nlen;
	FM_U32 au32N[FM_RSA_MAX_LEN / 4 + 1];
}RSAENCYPT;

typedef struct tag_RsaDecrypt_St
{
	FM_U32 u32KeyIndex;
	FM_U32 u32RsaBits;
	FM_U32 u32Inlen;
	FM_U32 au32Inbuf[FM_RSA_MAX_LEN / 4 + 1];
	FM_U32 u32PLen;
	FM_U32 au32P[FM_RSA_MAX_LEN / 4 + 1];
	FM_U32 u32QLen;
	FM_U32 au32Q[FM_RSA_MAX_LEN / 4 + 1];
	FM_U32 u32QinvLen;
	FM_U32 au32Qinv[FM_RSA_MAX_LEN / 4 + 1];
	FM_U32 u32DPLen;
	FM_U32 au32DP[FM_RSA_MAX_LEN / 4 + 1];
	FM_U32 u32DQLen;
	FM_U32 au32DQ[FM_RSA_MAX_LEN / 4 + 1];
}RSADECRYPT;

/*********************�Գ��㷨************************/
typedef struct tag_SicSymKeyBody_St
{
    FM_U32 u32Index;
    FM_U32 u32Alg;
    FM_U32 u32SymKeyLen;
    FM_U32 au32SymKeyData[SIC_MAX_SYM_KEY_LEN / 4];
}SICSYMKEYBODY; //44�ֽ�

typedef struct tag_SymInitMode_St
{
	FM_U32 u32Flag;
	FM_U32 u32Alg;
	FM_U32 u32Mode;
	FM_U32 u32KeyLen;
	FM_U32 au32KeyData[SIC_MAX_SYM_KEY_LEN / 4];
	FM_U32 u32IvLen;
    FM_U32 au32IvData[SIC_MAX_IV_LEN / 4];
}SYMINITMODE;

typedef struct tag_SymInitModeEx_St
{
	FM_U32 u32Flag;
	FM_U32 u32Alg;
	FM_U32 u32Mode;
	FM_U32 u32KeyLen;
	FM_U32 au32KeyData[SIC_MAX_SYM_KEY_LEN / 4];
}SYMINITMODEEX, *PSYMINITMODEEX;

typedef struct tag_SymData_St
{
	FM_U32 au32InBuf[SIC_MAX_SYMEN_LEN / 4];
	FM_U32 u32InLen;
	SYMINITMODE stSymInit;
}SYMDATA;

typedef struct tag_SymDataEx_St
{
    FM_U32 au32IvBuf[SIC_MAX_IV_LEN / 4];
    FM_U32 u32IvLen;
    FM_U32 u32DataLen;
    FM_U32 au32DataBuf[1];
}SYMDATAEX, *PSYMDATAEX;

typedef struct tag_SymData_tf_St
{
	FM_U32 au32InBuf[SIC_MAX_SYMEN_LEN_TF / 4];
	FM_U32 u32InLen;
	SYMINITMODE stSymInit;
}SYMDATA_TF;

typedef struct tag_SymInitMode_St_OldVer
{
	FM_U32 u32Flag;
	FM_U32 u32Alg;
	FM_U32 u32Mode;
	FM_U32 u32KeyLen;
	FM_U32 au32KeyData[SIC_SYMKEY_LEN / 4];
	FM_U32 u32IvLen;
    FM_U32 au32IvData[SIC_MAX_IV_LEN / 4];
}SYMINITMODE_OLDVER;

typedef struct tag_SymData_St_OldVer
{
	FM_U32 au32InBuf[SIC_MAX_SYMEN_LEN / 4];
	FM_U32 u32InLen;
	SYMINITMODE_OLDVER stSymInit;
}SYMDATA_OLDVER;

typedef struct tag_SicEccKeyBody_St
{
    FM_ECC_PublicKey stEccPublicKey;
    FM_ECC_PrivateKey stEccPrivateKey;
    FM_U32 u32Index;
    FM_U32 u32Flag;
}SICECCKEYBODY; //112�ֽ�

typedef struct tag_EccEncrypt_St
{
	FM_U32 u32Index;
    FM_ECC_PublicKey stEccPublicKey;
	FM_U32 u32Inlen;
    FM_U32 au32Inbuf[FM_ECC_MAX_INBUF_LEN / 4];
}SICECCENCYPT;

typedef struct tag_EccDecrypt_St
{
	FM_U32 u32Index;
    FM_ECC_PrivateKey stEccPrivateKey;
    FM_ECC_Cipher stEccCipher;
}SICECCDECYPT;

typedef struct tag_EccSign_St
{
	FM_U32 u32Index;
	FM_U32 u32Inlen;
	FM_U32 au32Inbuf[FM_ECC_MAX_LEN/4];
    FM_ECC_PrivateKey stEccPrivateKey;
}SICECCSIGN;

typedef struct tag_EccVerify_St
{
	FM_U32 u32Index;
	FM_U32 u32Inlen;
	FM_U32 au32Inbuf[FM_ECC_MAX_LEN/4];
    FM_ECC_PublicKey stEccPublicKey;
    FM_ECC_Signature stEccSignature;
}SICECCVERIFY;

typedef struct tag_SM3Init_St
{
	FM_U32 u32IDlen;
	FM_U8 au8IDbuf[FM_ECC_MAX_LEN];
    FM_ECC_PublicKey stEccPublicKey;
}SICSM3INIT;

typedef struct tag_EccGenKey_St
{
    FM_U32            u32Alg;
    FM_U32            u32KeyBits;

    FM_U8             au8SponsorID[FM_ECC_MAX_LEN];
    FM_U32            u32SponsorIDLen;

    FM_U32            hSponsorKey;
    FM_ECC_PublicKey  stSponsorPubKey;
    FM_ECC_PublicKey  stSponsorTmpPubKey;

    FM_U8             au8ResponseID[FM_ECC_MAX_LEN];
    FM_U32            u32ResponseIDLen;

    FM_U32            hResponseKey;
    FM_ECC_PublicKey  stResponsePubKey;
    FM_ECC_PublicKey  stResponseTmpPubKey;

    FM_U32            hKeyHandle;
}ECCGENAKEY;

// sizeof = 108byte
typedef struct
{
    FM_U8  u8TempData[64];  //ʣ������
    FM_U32 u32TempDataLen;  //ʣ�����ݴ�С
    FM_U8  au8IV[32];        //IV,len=32
    FM_U32 Nl,Nh;           //�����ܳ��ȣ�Nl Nh�ֱ�Ϊ��32λ�͸�32λ
}SM3_CTX, *PSM3_CTX;

typedef struct
{
    SM3_CTX stSM3Ctx;
    FM_U8  u8ID[128];
    FM_U32 u32IDLen;
    FM_ECC_PublicKey EccPubkey;
}SICSM3CTX, *PSICSM3CTX;

typedef struct
{
    FM_U32 h0,h1,h2,h3,h4;
    FM_U32 Nl,Nh;
    FM_U32 data[16];
    FM_U32 num;
    FM_U32 len;
    FM_U8  hash[32];
}CPC_SHA_CTX, *PCPC_SHA_CTX;

typedef struct
{
    FM_U32   u32Alg;
    FM_HKEY  hKey;
    FM_U32   u32WorkMode;
    FM_U8    au8Key[32];
    FM_U32   u32KeyLen;
    FM_U8    au8IV[32];
    FM_U32   u32IVLen;
}SIC_SYM_CTX, *PSIC_SYM_CTX;


