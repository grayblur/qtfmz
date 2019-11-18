#pragma once

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
//#include <stdlib.h>
//# include <stdio.h>
#include <memory>
#include <string.h>
#include <iostream>




#if defined( _MSC_VER ) || defined (WIN32)
#include <crtdbg.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
_CrtMemState startMemState;
_CrtMemState endMemState;
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include "fm_def.h"
#include "fm_cpc_pub.h"

#include "tinyxml2.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "S2JDll.h"

#ifdef __cplusplus
}
#endif



#define NID_sm2p256v1           1116


#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

//
#define PRI						0x10000000				//˽��
#define PUB						0x10000001				//����
#define Encrypted				0x20000000				//�Ѽ���
#define Uncrypted				0x20000001				//δ����
#define Serverddd				"administrator"						//�����



//������
#define SUCCESS					0x00000000	             //�ɹ�
#define ERROR					0x00000001				 //��������
#define OpenFileError			0x00000002				 //���ļ�ʧ��
#define MallocError				0x00000003				 //�ڴ����ʧ��
#define FreeError				0x00000004				 //�ڴ��ͷ�ʧ��
#define LoadXmlError			0x00000005				 //load XMLʧ��
#define KeyError				0x00000006				 //key����
#define TokenError				0x00000007				 //token����
#define SMS2EnError				0x00000008				 //sm2���ܴ���
#define SMS2DeError				0x00000009				 //sm2���ܴ���
#define SMS2SignError			0x0000000A				 //sm2ǩ������
#define SMS2VerifyError			0x0000000B				 //sm2ǩ������
#define NoPermission			0x0000000C				 //û��Ȩ��
#define OutOfIndex				0x0000000D				 //������־�����Ŀ

#ifdef __cplusplus
extern "C" {
#endif
	static const char * base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	static const char padding_char = '=';


	//*****************no define in linux but defined in gmssl***********************
#ifndef _WIN64
	typedef unsigned int BOOL;
	typedef unsigned short USHORT;
	typedef unsigned int        UINT;
#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#endif

	typedef unsigned char BYTE;
	typedef unsigned int UINT32;
	typedef int INT32;
	typedef uint64_t TIME64;
	typedef void *				HANDLE;

	typedef HANDLE HSFL;

	typedef struct tagBuffer
	{
		UINT32			nLen;
		BYTE  *pbData;
	}FileBuffer, CertBuffer, SignBuffer, DataBuffer, CustomAttr;

	//��ݱ�ʶ*	2*cerbuffer
	typedef struct tagToken
	{
		//CertBuffer exCert;								//����֤��
		//CertBuffer signCert;							//ǩ��֤��
		char exCert[128];								//����֤��
		char signCert[128];							//ǩ��֤��
	}SToken, *PSToken;







	//�㷨��ʶ*					20
	typedef struct {
		BOOL bCrypt;						//�Ƿ����
		//char *szCryptAlg;					
		UINT32 szCryptAlg;					//�����㷨	
		UINT32 ucCryptMode;					//����ģʽ
		UINT32 numbits;						//����λ��
		//char *szSignAlg;					//ǩ����ժҪ���㷨
		UINT32 szSignAlg;
		//UINT32 uSymAlg;					//�Գ�
		//UINT32 uAsymAlg;					//�ǶԳ�
		//UINT32 uHashAlg;					//�Ӵ�
	}CipherMethod, *PCipherMethod;



	//**************��ǩͷ-ǩ������		certbuffer+cipherMethod+signbuffer
	typedef struct {
		CertBuffer signer;						//ǩ���ߵ�ǩ��֤��
		CipherMethod cipherMethod;				//ǩ���㷨��ʶ
		//UINT32 nSignMessageLen;					//ǩ��ֵ����
		SignBuffer signMessage;						//�ǶԱ�ǩ�г���ǩ������������������ݵ�ǩ�����		
	}SignAttribute;

	//ǩ���б�     4+signAttrCount*signAttr
	typedef struct {
		UINT32 signAttrCount;
		SignAttribute* signAttr;
	}SignAttributeList, *PSignAttributeList;


	//������			4+4+nSessionKeyLen
	typedef struct {
		char Serialnumber[128];							//֤�����к�
		UINT32 nSessionKeyLen;				//���ȣ���Ϊ0XFFFFFFFF��ʾ������
		void* sessionKey;					//��Կ����
	}Decryptor, *PDecryptor;


	//�����߱�					4+nReceiverCount*Receiver
	typedef struct {
		UINT32 nDecryptorCount;				//����������
		Decryptor* decryptor;				//�������б�
	}DecryptorList, *PDecryptorList;


	//**************��ǩͷ-��������		cipherMethod+receiverList
	typedef struct tagEncryptAttribute {
		BOOL bEncrypt;						//�Ƿ����				
		CipherMethod cipherMethod;				//�㷨��ʶ
		DecryptorList decryptorList;				//�������б�
	}EncryptAttribute, PEncryptAttribute;
	//

	//***************************�����ǩͷ     36+signattr+encryptAttr
	typedef struct SFL_Head_st {
		BYTE labelID[4];                            //��־���̶�Ϊ"@SFL"
		BYTE verID[12];								//SFL�ĸ�ʽ�汾����"1.3"
		SignAttribute signAttr;						//��ǩ��ǩ������
		EncryptAttribute encryptAttr;				//��ǩ��ļ�������
		char creator[128];								//��ǩ�����ߵļ���֤�����к�			
		TIME64 createTime;							//������ǩ��ʱ�䣬Ϊϵͳʱ��
		TIME64 lastAccessTime;						//�Ա�ǩ���д������ʱ�䣬Ϊϵͳʱ��
	}SFL_Head;






	//***********��ǩ��-��ȫ����
	//typedef struct SecurityAttribute_st {
	//	EncryptAttribute encryptAttr;					//�ļ��ļ�������
	//	SignAttribute signAttr;							//�ļ���ǩ������
	//	SESeal    	sealAttr;							//�ļ���ӡ������
	//	WaterMarkAttr wmarkAttr;						//�ļ���ˮӡ����
	//	FingerPrintTagAttribute figureAttr;				//�ļ���ָ������
	//	IPrivilegeAttr privilege;								//�ļ���Ȩ������
	//}SecurityAttribute;


	//**************��ǩ��-Ȩ������
	//��չȨ��*				4+4
	typedef struct tagExPrivilegeAttr
	{
		USHORT		nPriID;
		UINT32		nReserve;
	}IExPrivilegeAttr;

	//��չȨ���б�*			4+nExtPriCount*IExPrivilegeAttr
	typedef struct tagExPrivilegeAttrList
	{
		UINT32			nExtPriCount;
		IExPrivilegeAttr	*pExtPriAttrList;
	}IExPrivilegeAttrList;

	//������Ȩ��*        cerbuffer+28+exPriList
	typedef struct {
		CertBuffer user;								//���˼���֤��
		//	ECCrefPublicKey* user;
		BOOL bRead;										//�Ƿ��пɶ�Ȩ��
		UINT32 nTotalReadCount;							//�ɶ�����
		UINT32 nAlReadCount;							//�Ѷ�����
		BOOL bWrite;									//�Ƿ���дȨ��
		BOOL bPrint;									//�Ƿ��д�ӡȨ��
		UINT32 nPrintCount;								//�ɴ�ӡ����
		UINT32 nPrintedCount;							//�Ѵ�ӡ����
		BOOL bCopy;										//�Ƿ�ɸ���
		BOOL bCapture;									//�Ƿ�ɽ���
		//IExPrivilegeAttrList	exPriList;				//��չȨ��
	}IPrivilegeAttr;

	//������Ȩ������
	typedef struct {
		Decryptor decryptor;
		IPrivilegeAttr privilege;
	}OperatorAttr;


	//������Ȩ���б�			4+nAceCount*pAce
	typedef struct {
		UINT32 nAceCount;
		OperatorAttr* pAce;
	}OperatorList;

	typedef struct {
		OperatorList operatorList;
	}PrivAttr;




	//**************��ǩ��-ӡ������*			NULL
	typedef struct SES_Header
	{
		char* szVid;
	}SES_Header;


	typedef struct SES_ESPropertyInfo
	{
		INT32	type;
		char*	szName;
		CertBuffer *pCertList;
		UINT32	nListLen;
		TIME64	createDate;
		TIME64	validStart;
		TIME64	validEnd;
	}SES_ESPropertyInfo;

	typedef struct SES_ESPictrueInfo
	{
		char*	szType;
		DataBuffer picData;
	}SES_ESPictrueInfo;

	typedef struct SES_SealInfo
	{
		char* szESID;
		SES_ESPropertyInfo esProperty;
		SES_ESPictrueInfo picture;
		DataBuffer userData;
	}SES_SealInfo;


	typedef struct tagSES_SignInfo {
		CertBuffer signCert;
		char* signAlg;
		SignBuffer signData;
	}SES_SignInfo;

	typedef struct SESeal
	{
		SES_Header header;
		SES_SealInfo esealInfo;
		SES_SignInfo signInfo;
	}SESeal, *PSESeal;




	//**************��ǩ��-ˮӡ����*			NULL
	typedef struct tagWaterMarkAttr
	{
		CertBuffer  embedFile;
		CertBuffer  waterLoadInfo;
		UINT32	   embedAlgID;
		UINT32       embedMode;
		char       creator[128];
		TIME64    creatorTime;
	}WaterMarkAttr, *PWaterMarkAttr;



	//**************��ǩ��-ָ�Ʊ�ǩ����*			NULL
	typedef struct {
		CertBuffer	operatorr;
		BOOL bActionRead;
		BOOL bActionWrite;
		BOOL bActionPrint;
		BOOL bActionEncrypt;
		BOOL bActionDecrypt;
		BOOL bActionSign;
		BOOL bActionWatermark;
		BOOL bActionStamp;
	} BioVerifyAction, *PBioVerifyAction;

	typedef struct {
		UINT32				nOperatorCount;
		BioVerifyAction*	bioVerifyAction;
	}BioVerifyActionList, *PBioVerifyActionList;

	typedef struct {
		char*	szTemplateDBAttr;
		char*  	szTemplateAttr;
		char*	szAlgorithmAttr;
		INT32	bioSecurityLevel;
	} BioSystemAttr;

	typedef struct {
		BioVerifyAction	bioVerifyActionList;
		BioSystemAttr	bioSysAttr;
	} FingerPrintTagAttr, *PFingerPrintTagAttr;



	//**************��ǩ��-�ļ���ʶ����*       72
	typedef struct tagIIdentifyAttr
	{
		char		szFileNo[128];					//�ļ����
		char		szFileCreator[128];				//�ļ�������
		TIME64		tFileCreate;					//�ļ�����ʱ��
	}IdentifyAttr;


	//***********��ǩ��-�������ԣ��ģ� 108
	typedef struct ContentAttribute_st {
		//BYTE fileAddr[64];							//�洢��ַ���ļ�Ϊ����ʽ�洢ʱ����ʾ���ļ���URL��Ϊ����ʽ�洢ʱ����ʾ���ļ��ڱ�ǩ���е�ƫ����
		//ULONG fileSize;								//�ļ����ĵ��ֽ���
		//BYTE fileName[32];							//�ļ����������ļ���չ��
		//UINT32 hashLen;
		//BYTE* hashValue;							//�ļ�ժҪ
		UINT32  crLen;								//��ǰ�����˳���
		char  *curReviewer;							//��ǰ������
		UINT32  trLen;								//�������˳���
		char  *totalReviewer;						//��������
		INT32 fileType;								//�ļ�����
		INT32 fileLevel;							//�ļ�����
		INT32 fileSize;								//�ļ������ֽ���
		char fileName[256];							//�ļ���
		char fileTitle[256];							//�ļ�����
		TIME64 fileDate;							//�ļ�����޸�ʱ��
		TIME64 expiredDate;							//�ļ�ʧЧ���ڣ������������ļ���ʧЧ���޷������޸ģ�ֻ�ܶ�ȡ
		TIME64 desuetudeDate;						//���ļ���Ч���ڣ����ļ�ʧЧ������
		TIME64 destroyDate;						//�ļ��������ڣ����ں��ļ��޷���ȡ

	}ContentAttr;


	//**************��ǩ��-��������*		12
	typedef struct AlignAttr_st
	{
		INT32			fileAlignSize;
		INT32			fileEffectSize;
		INT32			labelAlignSize;
	}AlignAttr;


	//**************��ǩ��-��չ����*		8+nLen
	typedef struct tagExtend
	{
		USHORT			nAttrID;
		UINT32			nLen;
		BYTE			*pbContent;

	}Extend;

	typedef struct tagExtendAttr {
		UINT32 nExtendCount;
		Extend* pExtend;
	}ExtendAttr;


	//**************��ǩ��-��־����*					120+uHCLen+uDesLen
	//1-���� 0-˽��
	typedef struct tagLogContent
	{
		UINT32  uType;						//��־����
		char  szName[128];						//������
		UINT32  uHCLen;						//ǩ��֤�����кų���
		//BYTE  *pSerial;						//������ǩ��֤�����к�
		char  *pSerial;						//������ǩ��֤�����к�
		char  szHardCode[128];				//Ӳ�����
		TIME64  operTime;					//����ʱ��
		UINT32  uResult;					//�������
		UINT32  uDesLen;					//������������
		//BYTE  *pDescript;					//��������
		char  *pDescript;					//��������

	}LogContent;

	typedef struct tagLogAttr {
		DataBuffer nlogEnc;
		UINT32 nLogCount;
		LogContent* pLog;

	}LogAttr;



	//***************************�����ǩ��			SignBuffer+	CertBuffer+WaterMarkAttr+FingerPrintTagAttribute+IIdentifyAttr+ContentAttribute+IExtendAttr+ILogAttr
	typedef struct SFL_Text_st {
		SignAttributeList mSAttribute;					//ʹ�õ�ǰ�����ߵ�ǩ��˽Կ���ļ�����ǩ����Ľ��
		//CertBuffer cert;								//�����ߵ�ǩ��֤��
		//ConfigAttribute configAttr;					//��������	
		//SecurityAttribute securityAttr;				//��ȫ����
		PrivAttr priv;									//Ȩ������
		PSESeal stampAttr;								//ӡ������
		PWaterMarkAttr waterMark;						//ˮӡ����
		PFingerPrintTagAttr fingerPrint;			//ָ������
		IdentifyAttr identify;							//��ʶ���� �ļ�Ψһ��ʶ
		ContentAttr bFileAttr;						//��������
		AlignAttr align;								//��������
		ExtendAttr	extend;								//��չ����
		LogAttr log;									//������־����
		LogAttr prilog;									//˽����־����
	}SFL_Text;
	//
	typedef struct SFL_DATA_st {
		BOOL bEncrypt;
		FileBuffer fileData;
	}SFL_DATA;


	////*****************************************��ǩ�ṹ�嶨��
	////�����ǩ�ṹ      head+text
	typedef struct SecuredFileLabel_st {
		SFL_Head baseHead;                           //--��ǩͷ
		SFL_Text baseText;							 //--��ǩ��
		SFL_DATA baseData;							//--�ļ�����
	}SecuredFileLabel;




	//api-level3
	//*********************************�����***************************
	int Server_Create(IN const SToken* pToken,
		IN const char* srcSFL,
		OUT const char* dstSFL);

	int Server_InternalRead(IN const SToken* pToken,
		IN const char* srcSFL,
		OUT const char* dstSFL);

	int Server_InternalWrite(IN const SToken* pToken,
		IN const char* srcSFL,
		OUT const char* dstSFL);

	int Server_Send(IN const SToken* pToken,
		IN const SToken* puserToken,
		IN const char* srcSFL,
		OUT const char* dstSFL);

	int Server_AddLogAttr(IN const SToken* pToken,
		IN const LogContent* pLog,
		IN const char* srcSFL);

	char* Server_GetLogAttr(IN const SToken* pToken,
		IN int cnt,
		IN BOOL flag,
		IN const char* srcSFL);

	int Server_SetPriAttr(IN const SToken* pToken,
		IN const IPrivilegeAttr* pPri,
		IN const char* srcSFL);

	char* Server_GetPriAttr(IN const SToken* pToken,
		IN const char* srcSFL);

	int Server_SetContentAttr(IN const SToken* pToken,
		IN const ContentAttr* pContent,
		IN const char* srcSFL);

	char* Server_GetContentAttr(IN const SToken* pToken,
		IN const char* srcSFL);





	//*********************************�ͻ���***************************
	int Client_Upload(IN const SToken* pToken,
		IN const char* srcSFL,
		OUT const char* dstSFL);

	int Client_InternalRead(IN const SToken* pToken,
		IN const char* srcSFL,
		OUT const char* dstSFL);

	int Client_InternalWrite(IN const SToken* pToken,
		IN const char* srcSFL,
		OUT const char* dstSFL);

	//��˽����־���ܻ�������
	int Client_Send(IN const SToken* pToken,
		IN const SToken* puserToken,
		IN const char* srcSFL,
		OUT const char* dstSFL);

	int  Client_AddLogAttr(IN const SToken* pToken,
		IN const LogContent* pLog,
		IN const char* srcSFL);

	char* Client_GetLogAttr(IN const SToken* pToken,
		IN int cnt,
		IN const char* srcSFL);


	char* Client_GetPriAttr(IN const SToken* pToken,
		IN const char* srcSFL);

	int Client_SetContentAttr(IN const SToken* pToken,
		IN const ContentAttr* pContent,
		IN const char* srcSFL);

	char* Client_GetContentAttr(IN const SToken* pToken,
		IN const char* srcSFL);

	//*************************����*******************
	int IsEncrypted(IN const char* srcSFL);

#ifdef __cplusplus
}
#endif