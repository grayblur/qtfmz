/******************************************************************************
* Copyright (c) 2007, Shandong Fisherman Information Technology Co., Ltd.
* All rights reserved.
* �ļ�����: fm_sic_pub.h
* �ļ�����: ������������Կ��SIC���������ӿ�
* ��ǰ�汾: 1.0
* ��    ��: LJ
* ����ʱ��: 2007-01-07
* �޸ļ�¼:
* ----------------------------------------------
*    ʱ��    ����     ����
******************************************************************************/
#ifndef FM_SIC_PUB_H
#define FM_SIC_PUB_H

#ifdef  __cplusplus
    extern "C" {
#endif
#define FM_OPEN_SEREL		  0x00000040  //�Ƿ������к���ʽ���豸
#define FM_OPEN_DEVID		  0x00000080  //�Ƿ����豸����ʽ���豸

#define FM_INFO_SETDEVID    0x0105
#define FM_DEV_ID_LEN       64
#define FM_DEV_SER_LEN		16

//--cert---------------------
#define FM_CONT_RSA     1
#define FM_CONT_ECC     2

#define FM_CERT_ENC    1
#define FM_CERT_SIGN   2
#define FM_KEYNUM_ENC  3
#define FM_KEYNUM_SIGN 4
#define FM_CONT_TYPE   5
/************************ �ļ�ϵͳ ************************/
// �����ļ�������
#define SIC_FILE_NAME_LEN       4
// ���·����� \root\abcd\ef\gab\hijk���������Ϊ5
#define SIC_FILE_DEPTH          16
// ���Ŀ¼�������·����ȼ�1
#define SIC_FILE_DIRDEPTH       (SIC_FILE_DEPTH-1)
// ���·������
#define SIC_FILE_MAXPATH        ((SIC_FILE_NAME_LEN+1)*SIC_FILE_DEPTH)
// �ļ��ռ��С
#define SIC_FILE_MAXSIZE        (128 * 1024)
#define SIC_FILE_MAXSIZE_TF     (640 * 1024)
#define SIC_FILE_MAXSIZE_TF3302     (192 * 1024)


// �ļ���Ϣ�ṹ
typedef struct tagFileInfoSt
{
    FM_S8  as8FileName[SIC_FILE_NAME_LEN];
    FM_U32 u32FileSize;
    FM_U32 u32FileID;
}SIC_FILE_INFO, *PSIC_FILE_INFO;

/* ������ */
typedef struct tag_KeyCount_St
{
    FM_U8 au8CountData[16];
    FM_U32 u32CountNum;
}KEYCOUNT;



/************************ �û����� ************************/
// �û����
#define CPC_USER_ADMIN          1   /* ����Ա */
#define CPC_USER_OPER           2   /* ����Ա */
// �û���Ŀ
#define CPC_USER_MAXADMIN       5   /* ������Ա��Ŀ */
#define CPC_USER_MAXOPER        5   /* ������Ա��Ŀ */
#define CPC_USER_MAXUSER        (CPC_USER_MAXADMIN + CPC_USER_MAXOPER) /* ����û��� */
// �û�����
#define CPC_USER_ADDADMIN       1   /* ��ӹ���Ա */
#define CPC_USER_ADDOPER        2   /* ��Ӳ���Ա */
#define CPC_USER_DELADMIN       3   /* ɾ������Ա */
#define CPC_USER_DELOPER        4   /* ɾ������Ա */
// �û����ݹ���
#define CPC_USER_BAK            1   /* ���� */
#define CPC_USER_RES            2   /* �ָ� */
#define CPC_USER_BAKINIT        3   /* ���ݳ�ʼ�� */
#define CPC_USER_RESINIT        4   /* �ָ���ʼ�� */
// ��֤״̬
#define CPC_USER_AUTHPASS       1   /* ��֤ͨ�� */
#define CPC_USER_AUTHNOPASS     0   /* ��֤δͨ�� */

typedef struct tagUserInfoSt
{
    FM_U8 au8Serial[FM_DEVINFO_SERIAL_LEN];     // ���к�
    FM_U8 u8Flag;                               // ������� CPC_USER_ADMIN / CPC_USER_OPER */
    FM_U8 u8IsAuthed;                           // �Ƿ��¼     1�ѵ�¼
    FM_U8 u8Reserve1;                           // ����
    FM_U8 u8Reserve2;                           // ����
    FM_ECC_PublicKey ECCPublicKey;
}CPC_USER_INFO, *PCPC_USER_INFO;

/****************************������Ҫ�Ĺ����ṹ********************************/
// ��������
#define CPC_BK_TYPE_ALL     1   // ������������
#define CPC_BK_TYPE_FILEALL 2   // �����ļ�ϵͳ
#define CPC_BK_TYPE_WKALL   3   // �������й�����Կ
#define CPC_BK_TYPE_RSAALL  4   // ��������RSA��Կ
#define CPC_BK_TYPE_ECCALL  5   // ��������ECC��Կ


// ������Ϣ�洢���豸����
#define CPC_BK_STORE_HOST   1    // ������Ϣ�洢�������ļ�
#define CPC_BK_STORE_DEVKEY 2    // ������Ϣ�洢���豸������IC������USBKey �ݲ�֧��

// ���ݹ����ʼ��ʱ�����ýṹ
typedef struct stBkConifg
{
    FM_U32      u32Type;               // ��������
    FM_U32      u32StoreDev;           // ����
    FM_U8       u8StoreFile[128];      // ������Ϣ�洢���ļ���
    FM_U32      u32ThresholdKeyID;     // ����Կ(������Կ)ID [0-99]
    FM_U32      u32HKey;               // ����
    FM_U8       u8FullPath[128];       // ����
    FM_U32      u32Resvered[16];       // ����
} CPC_BK_CONFIG, *PCPC_BK_CONFIG;


/****************************** API �������� *********************************/
FM_RET FM_SIC_ReDownLoad
(
    FM_I FM_HANDLE hDev
);

FM_RET FM_SIC_OpenDeviceEx
(
    FM_I FM_U8      *pu8Id,
    FM_O FM_HANDLE  *phDev
);

FM_RET FM_SIC_InitSeril
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32BufLen,
    FM_I FM_U8     *pu8Buf
);

FM_RET FM_SIC_SetPackageName
(
    FM_I FM_U8  *pu8Package
);

FM_RET FM_SIC_OpenDevice
(
    FM_I FM_U8     *pu8Id,
    FM_I FM_U32     u32Type,
    FM_I FM_U32     u32Flag,
    FM_O FM_HANDLE *phDev
);

FM_RET FM_SIC_OpenDevice2
(
    FM_I FM_U8      *pu8Id,
    FM_I FM_U32     u32Type,
    FM_I FM_U32     u32Flag,
    FM_O FM_HANDLE  *phDev,
    FM_I FM_U32  u32fd,
    FM_I FM_U8 *pu8DevPath
);

FM_RET FM_SIC_CloseDeviceEx
(
    FM_I FM_HANDLE  hDev
);

FM_RET FM_SIC_CloseDevice
(
    FM_I FM_HANDLE  hDev
);

FM_RET FM_SIC_CloseAllDevice
(
 FM_I FM_HANDLE  hDev
);

FM_RET FM_SIC_GetDeviceInfo
(
    FM_I FM_HANDLE  hDev,
    FM_O FM_DEV_INFO  *pDevInfo
);

FM_RET FM_SIC_GetDevType
(
    FM_I FM_HANDLE  hDev,
    FM_O FM_U32     *pu32DevType
);

FM_RET FM_SIC_GenRandom
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Len,
    FM_O FM_U8     *pu8Random
);

FM_RET FM_SIC_GetInfo
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Flag,
    FM_B FM_U32    *pu32Len,
    FM_O FM_U8     *pu8OutBuf
);

FM_RET FM_SIC_GetErrInfo
(
    FM_I FM_U32     u32LanFlag,
    FM_I FM_U32     u32ErrCode,
    FM_B FM_U32    *pu32Len,
    FM_O FM_S8     *ps8Info
);

FM_RET FM_SIC_OpenByName
(
    FM_I FM_U8     *pu8Id,
    FM_I FM_U32     u32Type,
    FM_I FM_U8     u8DevIndex,
    FM_O FM_HANDLE *phDev
);

FM_RET FM_SIC_OpenBySerial
(
    FM_I FM_U8     *pu8Id,
    FM_I FM_U32     u32Type,
    FM_I FM_U8     u8DevIndex,
    FM_O FM_HANDLE *phDev
);

FM_RET FM_SIC_EnumDevice
(
    FM_I FM_U32    u32EnumType,
    FM_O FM_U8     *pu8ResultBuf,
    FM_B FM_U32    *u32ResultBufLen
);

FM_RET FM_SIC_EnumDeviceSerialNum
(
    FM_O FM_U8     *pu8ResultBuf,
    FM_B FM_U32    *u32ResultBufLen
);

FM_RET FM_SIC_GenRSAKeypair
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32KeyBits,
    FM_B FM_HKEY   *phKey,
    FM_O FM_RSA_PublicKey  *pPubkey,
    FM_O FM_RSA_PrivateKey *pPrikey
);

FM_RET FM_SIC_DelRSAKeypair
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_HKEY    hKey
);

FM_RET FM_SIC_ImportRSAKeypair
(
    FM_I FM_HANDLE  hDev,
    FM_B FM_HKEY   *phKey,
    FM_I FM_RSA_PublicKey  *pPubkey,
    FM_I FM_RSA_PrivateKey *pPrikey
);

FM_RET FM_SIC_ExportRSAKeypair
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_HKEY    hKey,
    FM_O FM_RSA_PublicKey  *pPubkey,
    FM_O FM_RSA_PrivateKey *pPrikey
);

FM_RET FM_SIC_RSAEncrypt
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_HKEY    hKey,
    FM_I FM_U8     *pu8InBuf,
    FM_I FM_U32     u32InLen,
    FM_O FM_U8     *pu8OutBuf,
    FM_O FM_U32    *pu32OutLen,
    FM_I FM_RSA_PublicKey *pPubkey
);

FM_RET FM_SIC_RSADecrypt
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_HKEY    hKey,
    FM_I FM_U8     *pu8InBuf,
    FM_I FM_U32     u32InLen,
    FM_O FM_U8     *pu8OutBuf,
    FM_O FM_U32    *pu32OutLen,
    FM_I FM_RSA_PrivateKey *pPrikey
);

FM_RET FM_SIC_RSASign
(
	FM_I	FM_HANDLE	hDev,
	FM_I	FM_HKEY		hKey,
	FM_I	FM_U32		u32Alg,
	FM_I	FM_U8		*pu8DataBuf,
	FM_I	FM_U32		u32DataLen,
	FM_O	FM_U8		*pu8SignBuf,
	FM_O 	FM_U32		*pu32SignLen,
	FM_I 	FM_RSA_PrivateKey *pPrikey
);

FM_RET FM_SIC_RSAVerify
(
	FM_I	FM_HANDLE	hDev,
	FM_I	FM_HKEY		hKey,
	FM_I	FM_U32		u32Alg,
	FM_I	FM_U8		*pu8DataBuf,
	FM_I	FM_U32		u32DataLen,
	FM_I	FM_U8		*pu8SignBuf,
	FM_I	FM_U32		u32SignLen,
	FM_I	FM_RSA_PublicKey	*pPubkey
);

FM_RET FM_SIC_GenECCKeypair
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Alg,
    FM_B FM_HKEY   *phKey,
    FM_O FM_ECC_PublicKey  *pPubkey,
    FM_O FM_ECC_PrivateKey *pPrikey
);

FM_RET FM_SIC_DelECCKeypair
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_HKEY    hKey
);

FM_RET FM_SIC_ImportECCKeypair
(
    FM_I FM_HANDLE  hDev,
    FM_B FM_HKEY   *phKey,
    FM_I FM_ECC_PublicKey  *pPubkey,
    FM_I FM_ECC_PrivateKey *pPrikey
);

FM_RET FM_SIC_ExportECCKeypair
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_HKEY    hKey,
    FM_O FM_ECC_PublicKey  *pPubkey,
    FM_O FM_ECC_PrivateKey *pPrikey
);

FM_RET FM_SIC_ECCEncrypt
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Alg,
    FM_I FM_HKEY    hKey,
    FM_I FM_U8     *pu8InBuf,
    FM_I FM_U32     u32InLen,
    FM_I FM_ECC_PublicKey *pPubkey,
    FM_O FM_ECC_Cipher    *pECCCipher
);

FM_RET FM_SIC_ECCDecrypt
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Alg,
    FM_I FM_HKEY    hKey,
    FM_I FM_ECC_Cipher     *pECCCipher,
    FM_I FM_ECC_PrivateKey *pPrikey,
    FM_O FM_U8     *pu8OutBuf,
    FM_O FM_U32    *pu32OutLen
);

FM_RET FM_SIC_ECCSign
(
    FM_I FM_HANDLE             hDev,
    FM_I FM_U32                u32Alg,
    FM_I FM_HKEY               hKey,
    FM_I FM_U8                *pu8InBuf,
    FM_I FM_U32                u32InLen,
    FM_I FM_ECC_PrivateKey    *pPrikey,
    FM_O FM_ECC_Signature     *pSignature
);

FM_RET FM_SIC_ECCVerify
(
    FM_I FM_HANDLE         hDev,
    FM_I FM_U32            u32Alg,
    FM_I FM_HKEY           hKey,
    FM_I FM_ECC_PublicKey *pPubkey,
    FM_I FM_U8            *pu8InBuf,
    FM_I FM_U32            u32InLen,
    FM_I FM_ECC_Signature *pSignature
);

FM_RET FM_SIC_GenerateAgreementDataWithECC
(
    FM_I FM_HANDLE         hDev,
    FM_I FM_U32            u32Alg,
    FM_I FM_HKEY           hKey,
    FM_I FM_U32            u32KeyBits,
    FM_I FM_U8            *pu8SponsorID,
    FM_I FM_U32            u32SponsorIDLen,
    FM_O FM_ECC_PublicKey *pSponsorPubKey,
    FM_O FM_ECC_PublicKey *pSponsorTmpPubKey,
    FM_O FM_HANDLE        *phAgreementHandle
);

FM_RET FM_SIC_GenerateAgreementDataAndKeyWithECC
(
    FM_I FM_HANDLE         hDev,
    FM_I FM_U32            u32Alg,
    FM_I FM_HKEY           hKey,
    FM_I FM_U32            u32KeyBits,
    FM_I FM_U8            *pu8ResponseID,
    FM_I FM_U32            u32ResponseIDLen,
    FM_I FM_U8            *pu8SponsorID,
    FM_I FM_U32            u32SponsorIDLen,
    FM_I FM_ECC_PublicKey *pSponsorPubKey,
    FM_I FM_ECC_PublicKey *pSponsorTmpPubKey,
    FM_O FM_ECC_PublicKey *pResponsePubKey,
    FM_O FM_ECC_PublicKey *pResponseTmpPubKey,
    FM_O FM_HKEY          *phKeyHandle
);

FM_RET FM_SIC_GenerateKeyWithECC
(
    FM_I FM_HANDLE         hDev,
    FM_I FM_U8            *pu8ResponseID,
    FM_I FM_U32            u32ResponseIDLen,
    FM_I FM_ECC_PublicKey *pResponsePubKey,
    FM_I FM_ECC_PublicKey *pResponseTmpPubKey,
    FM_I FM_HANDLE         hAgreementHandle,
    FM_O FM_HKEY          *phKeyHandle
);

FM_RET FM_SIC_GenKey
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Alg,
    FM_I FM_U32     u32InLen,
    FM_B FM_HKEY   *phKey,
	FM_O FM_U8     *pu8Key
);

FM_RET FM_SIC_DelKey
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_HKEY    hKey
);

FM_RET FM_SIC_ImportKey
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Alg,
    FM_I FM_U8     *pu8Key,
    FM_I FM_U32     u32KeyLen,
    FM_B FM_HKEY   *phKey
);

FM_RET FM_SIC_ExportKey
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_HKEY    hKey,
    FM_O FM_U8     *pu8Key,
    FM_B FM_U32    *pu32Len
);

FM_RET FM_SIC_EncryptInit
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_HKEY    hKey,
    FM_I FM_U32     u32Alg,
    FM_I FM_U32     u32WorkMode,
    FM_I FM_U8     *pu8Key,
    FM_I FM_U32     u32KeyLen,
    FM_I FM_U8     *pu8IV,
    FM_I FM_U32     u32IVLen
);

FM_RET FM_SIC_EncryptUpdate
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Alg,
    FM_I FM_U8     *pu8InBuf,
    FM_I FM_U32     u32InLen,
    FM_O FM_U8     *pu8OutBuf,
    FM_O FM_U32    *pu32OutLen
);

FM_RET FM_SIC_EncryptFinal
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Alg
);

FM_RET FM_SIC_Encrypt
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_HKEY    hKey,
    FM_I FM_U32     u32Alg,
    FM_I FM_U32     u32WorkMode,
    FM_I FM_U8     *pu8InBuf,
    FM_I FM_U32     u32InLen,
    FM_O FM_U8     *pu8OutBuf,
    FM_O FM_U32    *pu32OutLen,
    FM_I FM_U8     *pu8Key,
    FM_I FM_U32     u32KeyLen,
    FM_I FM_U8     *pu8IV,
    FM_I FM_U32     u32IVLen
);

FM_RET FM_SIC_DecryptInit
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_HKEY    hKey,
    FM_I FM_U32     u32Alg,
    FM_I FM_U32     u32WorkMode,
    FM_I FM_U8     *pu8Key,
    FM_I FM_U32     u32KeyLen,
    FM_I FM_U8     *pu8IV,
    FM_I FM_U32     u32IVLen
);

FM_RET FM_SIC_DecryptUpdate
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Alg,
    FM_I FM_U8     *pu8InBuf,
    FM_I FM_U32     u32InLen,
    FM_O FM_U8     *pu8OutBuf,
    FM_O FM_U32    *pu32OutLen
);

FM_RET FM_SIC_DecryptFinal
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Alg
);

FM_RET FM_SIC_Decrypt
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_HKEY    hKey,
    FM_I FM_U32     u32Alg,
    FM_I FM_U32     u32WorkMode,
    FM_I FM_U8     *pu8InBuf,
    FM_I FM_U32     u32InLen,
    FM_O FM_U8     *pu8OutBuf,
    FM_O FM_U32    *pu32OutLen,
    FM_I FM_U8     *pu8Key,
    FM_I FM_U32     u32KeyLen,
    FM_I FM_U8     *pu8IV,
    FM_I FM_U32     u32IVLen
);

FM_RET FM_SIC_HashInit
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Alg,
    FM_I FM_U8     *pu8IV,
    FM_I FM_U32     u32IVLen
);

FM_RET FM_SIC_HashUpdate
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Alg,
    FM_I FM_U8     *pu8InBuf,
    FM_I FM_U32     u32InLen
);

FM_RET FM_SIC_HashFinal
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Alg,
    FM_O FM_U8     *pu8OutMACBuf,
    FM_B FM_U32    *pu32OutMACLen
);

FM_RET FM_SIC_SM3Init
(
    FM_I FM_HANDLE         hDev,
    FM_I FM_ECC_PublicKey *pPubkey,
    FM_I FM_U8            *pu8ID,
    FM_I FM_U32            u32IDLen
);

FM_RET FM_SIC_SM3Update
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U8     *pu8InBuf,
    FM_I FM_U32     u32InLen
);

FM_RET FM_SIC_SM3Final
(
    FM_I FM_HANDLE  hDev,
    FM_O FM_U8     *pu8HashBuf,
    FM_B FM_U32    *pu32HashLen
);

FM_RET FM_SIC_HashInit_Hard
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Alg,
    FM_I FM_U8     *pu8IV,
    FM_I FM_U32     u32IVLen
);

FM_RET FM_SIC_HashUpdate_Hard
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Alg,
    FM_I FM_U8     *pu8InBuf,
    FM_I FM_U32     u32InLen
);

FM_RET FM_SIC_HashFinal_Hard
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Alg,
    FM_O FM_U8     *pu8OutMACBuf,
    FM_B FM_U32    *pu32OutMACLen
);


FM_RET FM_SIC_SM3Init_Hard
(
    FM_I FM_HANDLE         hDev,
    FM_I FM_ECC_PublicKey *pPubkey,
    FM_I FM_U8            *pu8ID,
    FM_I FM_U32            u32IDLen
);

FM_RET FM_SIC_SM3Update_Hard
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U8     *pu8InBuf,
    FM_I FM_U32     u32InLen
);

FM_RET FM_SIC_SM3Final_Hard
(
    FM_I FM_HANDLE  hDev,
    FM_O FM_U8     *pu8HashBuf,
    FM_B FM_U32    *pu32HashLen
);


FM_RET FM_SIC_USER_Login
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Type,
    FM_I FM_U8     *pu8PinBuf,
    FM_I FM_U32     u32PinLen,
    FM_O FM_HUSER  *phUser,
    FM_O FM_U32    *pu32RetryNum
);

FM_RET FM_SIC_USER_Logout
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_HUSER   hUser
);

FM_RET FM_SIC_USER_ChangePin
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Flag,
    FM_I FM_U8     *pu8OldPinBuf,
    FM_I FM_U32     u32OldPinLen,
    FM_I FM_U8     *pu8NewPinBuf,
    FM_I FM_U32     u32NewPinLen,
    FM_O FM_U32    *pu32RetryNum
);

FM_RET FM_SIC_IntAuthenticate
(
    FM_I FM_HANDLE hDev,
    FM_I FM_U8 *pu8Random,
	FM_I FM_U32 u32RndLen,
    FM_O FM_U8 *pu8Encrypt,
	FM_O FM_U32 *pu32EncLen
);

FM_RET FM_SIC_ExtAuthenticate
(
    FM_I FM_HANDLE hDev,
    FM_I FM_U8 *pu8Encrypt,
	FM_I FM_U32 u32EncLen,
	FM_O FM_U32 *pu32RetryNum
);

FM_RET FM_SIC_FILE_Init
(
    FM_I FM_HANDLE  hDev
);

FM_RET FM_SIC_FILE_CreateDir
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_S8     *ps8FullDir,
    FM_I FM_U32     u32AccCond
);

FM_RET FM_SIC_FILE_DeleteDir
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_S8     *ps8FullDir
);

FM_RET FM_SIC_FILE_CreateFile
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_S8     *ps8DirName,
    FM_I FM_S8     *ps8FileName,
    FM_I FM_U32     u32FileSize,
    FM_I FM_U32     u32AccCond
);

FM_RET FM_SIC_FILE_ReadFile
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_S8     *ps8DirName,
    FM_I FM_S8     *ps8FileName,
    FM_I FM_U32     u32Offset,
    FM_I FM_U32     u32Size,
    FM_O FM_U8     *pu8Buf
);

FM_RET FM_SIC_FILE_WriteFile
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_S8     *ps8DirName,
    FM_I FM_S8     *ps8FileName,
    FM_I FM_U32     u32Offset,
    FM_I FM_U32     u32Size,
    FM_I FM_U8     *pu8Buf
);

FM_RET FM_SIC_FILE_DeleteFile
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_S8     *ps8DirName,
    FM_I FM_S8     *ps8FileName
);

FM_RET FM_SIC_FILE_EnmuDir
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_S8     *ps8DirName,
    FM_B FM_U32    *pu32BufLen,
    FM_O FM_U8     *pu8Buf,
    FM_O FM_U32    *pu32DirNum
);

FM_RET FM_SIC_FILE_EnmuFile
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_S8     *ps8DirName,
    FM_B FM_U32    *pu32BufLen,
    FM_O FM_U8     *pu8Buf,
    FM_O FM_U32    *pu32FileNum
);

FM_RET FM_SIC_Cmd
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Cmd,
    FM_I FM_U32     aPara[],
    FM_I FM_U8     *pu8InData,
    FM_I FM_U32     u32InLen,
    FM_O FM_U8     *pu8OutData,
    FM_B FM_U32    *pu32OutLen
);

FM_RET FM_SIC_ReadHiddenPart
(
	FM_I FM_HANDLE   hDev,
	FM_I FM_U32		 u32Offset,
	FM_I FM_U32      u32Size,
	FM_O FM_VOID     *pOutBuff,
	FM_I FM_U32      u32BufLen
);

FM_RET FM_SIC_WriteHiddenPart
(
	FM_I FM_HANDLE   hDev,
	FM_I FM_U32		 u32Offset,
	FM_I FM_U32      u32Size,
	FM_I FM_VOID     *pOutBuff,
	FM_I FM_U32      u32BufLen
);

FM_RET FM_SIC_FILE_GetInfo
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_S8     *ps8DirName,
    FM_I FM_S8     *ps8FileName,
    FM_O SIC_FILE_INFO *pFileInfo
);

FM_RET FM_SIC_WaitForEvent
(
    FM_I FM_HANDLE  hDev,
    FM_I FM_U32     u32Flag,
    FM_I FM_VOID   *pfunc,
    FM_I FM_VOID   *pPara
);

FM_RET FM_RSA_PKCS1_padding_add_type_1
(
	FM_U8   *to,
	FM_U32 tlen,
	FM_U8 *from,
	FM_U32 flen
);

FM_RET FM_RSA_PKCS1_padding_check_type_1
(
	FM_U8   *to,
	FM_U32 tlen,
	FM_U8   *from,
	FM_U32 flen
);

FM_RET FM_RSA_PKCS1_padding_add_type_2
(
	FM_U8   *to,
	FM_U32 tlen,
	FM_U8 *from,
	FM_U32 flen
);

FM_RET FM_RSA_PKCS1_padding_check_type_2
(
	FM_U8   *to,
	FM_U32 tlen,
	FM_U8   *from,
	FM_U32 flen
);

FM_RET FM_SIC_ContainerWriteECCCert
(
	FM_I FM_HANDLE  hDev,
	FM_I FM_U32  	u32Flag,
	FM_I FM_S8  	*ps8ContainerName,
	FM_I FM_U8  	*pu8Data,
	FM_I FM_U32  	u32DataLen
);

FM_RET FM_SIC_ContainerWrite
(
	FM_I FM_HANDLE  hDev,
	FM_I FM_U32  	u32Flag,
	FM_I FM_S8  	*ps8ContainerName,
	FM_I FM_U8  	*pu8Data,
	FM_I FM_U32  	u32DataLen
);

FM_RET FM_SIC_ContainerRead
(
	FM_I FM_HANDLE  hDev,
	FM_I FM_U32  	u32Flag,
	FM_I FM_S8  	*ps8ContainerName,
	FM_O FM_U8  	*pu8Data,
	FM_O FM_U32  	*pu32DataLen
);

FM_RET FM_SIC_ContainerDelete
(
	FM_I FM_HANDLE  hDev,
	FM_I FM_S8  	*ps8ContainerName
);

FM_RET FM_SIC_ContainerEnum
(
	FM_I FM_HANDLE  hDev,
	FM_O FM_S8  	*ps8ContainerNames,
	FM_O FM_U32  	*pu32ContainerNamesLen
);

FM_RET FM_SIC_ContainerInfo
(
 	FM_I FM_HANDLE  hDev,
    FM_I FM_S8      *ps8ContainerName,
    FM_O FM_U32     *pu32ContainerType
);

#ifdef FMCFG_OS_WINDOWS
FM_RET FM_SIC_ImportP12Cert
(
	FM_I FM_HANDLE   hDev,
	FM_I FM_U8      *pu8CertData,
	FM_I FM_U32      u32CertDataLen,
	FM_I FM_U8      *pu8Pin,
	FM_I FM_U32      u32PinLen,
    FM_I FM_S8      *ps8ContainerName,
    FM_I FM_U32      u32CertType,
	FM_B FM_HKEY    *phKeyID
);
#endif

FM_RET FM_SIC_ImportRSAPrivateKey
(
	FM_I FM_HANDLE   hDev,
	FM_I FM_U32 AsymFlag,
	FM_I FM_U8	*pu8Symbuf,
	FM_I FM_U32   SymFlag,
	FM_I FM_U32   WorkMode,
	FM_I FM_U8  *pu8IV,
    FM_I FM_U8  *pu8Asymbuf,
	FM_I FM_U32   AsymKeyCryptNum,
	FM_I FM_U32   AsymKeyStorNum
);

FM_RET FM_SIC_ImportECCPrivateKey
(
	FM_I FM_HANDLE   hDev,
	FM_I FM_U8	*pu8Symbuf,
	FM_I FM_U32   SymFlag,
	FM_I FM_U32   WorkMode,
	FM_I FM_U8  *pu8IV,
    FM_I FM_U8  *pu8Asymbuf,
	FM_I FM_U32   AsymKeyCryptNum,
	FM_I FM_U32   AsymKeyStorNum
);

FM_RET FM_SIC_DevReset
(
    FM_I FM_HANDLE  hDev
);


#ifdef  __cplusplus
    }
#endif  /* #ifdef  __cplusplus */

#endif  /* #ifndef FM_SIC_PUB_H */

