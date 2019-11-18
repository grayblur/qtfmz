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
#define PRI						0x10000000				//私有
#define PUB						0x10000001				//公有
#define Encrypted				0x20000000				//已加密
#define Uncrypted				0x20000001				//未加密
#define Serverddd				"administrator"						//服务端



//错误定义
#define SUCCESS					0x00000000	             //成功
#define ERROR					0x00000001				 //其他错误
#define OpenFileError			0x00000002				 //打开文件失败
#define MallocError				0x00000003				 //内存分配失败
#define FreeError				0x00000004				 //内存释放失败
#define LoadXmlError			0x00000005				 //load XML失败
#define KeyError				0x00000006				 //key错误
#define TokenError				0x00000007				 //token错误
#define SMS2EnError				0x00000008				 //sm2加密错误
#define SMS2DeError				0x00000009				 //sm2解密错误
#define SMS2SignError			0x0000000A				 //sm2签名错误
#define SMS2VerifyError			0x0000000B				 //sm2签名错误
#define NoPermission			0x0000000C				 //没有权限
#define OutOfIndex				0x0000000D				 //超过日志最大数目

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

	//身份标识*	2*cerbuffer
	typedef struct tagToken
	{
		//CertBuffer exCert;								//加密证书
		//CertBuffer signCert;							//签名证书
		char exCert[128];								//加密证书
		char signCert[128];							//签名证书
	}SToken, *PSToken;







	//算法标识*					20
	typedef struct {
		BOOL bCrypt;						//是否加密
		//char *szCryptAlg;					
		UINT32 szCryptAlg;					//加密算法	
		UINT32 ucCryptMode;					//加密模式
		UINT32 numbits;						//反馈位数
		//char *szSignAlg;					//签名（摘要）算法
		UINT32 szSignAlg;
		//UINT32 uSymAlg;					//对称
		//UINT32 uAsymAlg;					//非对称
		//UINT32 uHashAlg;					//杂凑
	}CipherMethod, *PCipherMethod;



	//**************标签头-签名属性		certbuffer+cipherMethod+signbuffer
	typedef struct {
		CertBuffer signer;						//签名者的签名证书
		CipherMethod cipherMethod;				//签名算法标识
		//UINT32 nSignMessageLen;					//签名值长度
		SignBuffer signMessage;						//是对标签中除了签名属性以外的所有内容的签名结果		
	}SignAttribute;

	//签名列表     4+signAttrCount*signAttr
	typedef struct {
		UINT32 signAttrCount;
		SignAttribute* signAttr;
	}SignAttributeList, *PSignAttributeList;


	//解密者			4+4+nSessionKeyLen
	typedef struct {
		char Serialnumber[128];							//证书序列号
		UINT32 nSessionKeyLen;				//长度，当为0XFFFFFFFF表示不加密
		void* sessionKey;					//密钥保护
	}Decryptor, *PDecryptor;


	//解密者表					4+nReceiverCount*Receiver
	typedef struct {
		UINT32 nDecryptorCount;				//解密者数量
		Decryptor* decryptor;				//解密者列表
	}DecryptorList, *PDecryptorList;


	//**************标签头-加密属性		cipherMethod+receiverList
	typedef struct tagEncryptAttribute {
		BOOL bEncrypt;						//是否加密				
		CipherMethod cipherMethod;				//算法标识
		DecryptorList decryptorList;				//解密者列表
	}EncryptAttribute, PEncryptAttribute;
	//

	//***************************定义标签头     36+signattr+encryptAttr
	typedef struct SFL_Head_st {
		BYTE labelID[4];                            //标志，固定为"@SFL"
		BYTE verID[12];								//SFL的格式版本，如"1.3"
		SignAttribute signAttr;						//标签的签名属性
		EncryptAttribute encryptAttr;				//标签体的加密属性
		char creator[128];								//标签创建者的加密证书序列号			
		TIME64 createTime;							//创建标签的时间，为系统时间
		TIME64 lastAccessTime;						//对标签最后写操作的时间，为系统时间
	}SFL_Head;






	//***********标签体-安全属性
	//typedef struct SecurityAttribute_st {
	//	EncryptAttribute encryptAttr;					//文件的加密属性
	//	SignAttribute signAttr;							//文件的签名属性
	//	SESeal    	sealAttr;							//文件的印章属性
	//	WaterMarkAttr wmarkAttr;						//文件的水印属性
	//	FingerPrintTagAttribute figureAttr;				//文件的指纹属性
	//	IPrivilegeAttr privilege;								//文件的权限属性
	//}SecurityAttribute;


	//**************标签体-权限属性
	//扩展权限*				4+4
	typedef struct tagExPrivilegeAttr
	{
		USHORT		nPriID;
		UINT32		nReserve;
	}IExPrivilegeAttr;

	//扩展权限列表*			4+nExtPriCount*IExPrivilegeAttr
	typedef struct tagExPrivilegeAttrList
	{
		UINT32			nExtPriCount;
		IExPrivilegeAttr	*pExtPriAttrList;
	}IExPrivilegeAttrList;

	//操作者权限*        cerbuffer+28+exPriList
	typedef struct {
		CertBuffer user;								//个人加密证书
		//	ECCrefPublicKey* user;
		BOOL bRead;										//是否有可读权限
		UINT32 nTotalReadCount;							//可读份数
		UINT32 nAlReadCount;							//已读份数
		BOOL bWrite;									//是否有写权限
		BOOL bPrint;									//是否有打印权限
		UINT32 nPrintCount;								//可打印份数
		UINT32 nPrintedCount;							//已打印份数
		BOOL bCopy;										//是否可复制
		BOOL bCapture;									//是否可截屏
		//IExPrivilegeAttrList	exPriList;				//扩展权限
	}IPrivilegeAttr;

	//操作者权限属性
	typedef struct {
		Decryptor decryptor;
		IPrivilegeAttr privilege;
	}OperatorAttr;


	//操作者权限列表			4+nAceCount*pAce
	typedef struct {
		UINT32 nAceCount;
		OperatorAttr* pAce;
	}OperatorList;

	typedef struct {
		OperatorList operatorList;
	}PrivAttr;




	//**************标签体-印章属性*			NULL
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




	//**************标签体-水印属性*			NULL
	typedef struct tagWaterMarkAttr
	{
		CertBuffer  embedFile;
		CertBuffer  waterLoadInfo;
		UINT32	   embedAlgID;
		UINT32       embedMode;
		char       creator[128];
		TIME64    creatorTime;
	}WaterMarkAttr, *PWaterMarkAttr;



	//**************标签体-指纹标签属性*			NULL
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



	//**************标签体-文件标识属性*       72
	typedef struct tagIIdentifyAttr
	{
		char		szFileNo[128];					//文件编号
		char		szFileCreator[128];				//文件创建者
		TIME64		tFileCreate;					//文件创建时间
	}IdentifyAttr;


	//***********标签体-内容属性（改） 108
	typedef struct ContentAttribute_st {
		//BYTE fileAddr[64];							//存储地址，文件为外联式存储时，表示该文件的URL；为内联式存储时，表示该文件在标签体中的偏移量
		//ULONG fileSize;								//文件明文的字节数
		//BYTE fileName[32];							//文件名，包括文件扩展名
		//UINT32 hashLen;
		//BYTE* hashValue;							//文件摘要
		UINT32  crLen;								//当前审阅人长度
		char  *curReviewer;							//当前审阅人
		UINT32  trLen;								//总审阅人长度
		char  *totalReviewer;						//总审阅人
		INT32 fileType;								//文件类型
		INT32 fileLevel;							//文件级别
		INT32 fileSize;								//文件明文字节数
		char fileName[256];							//文件名
		char fileTitle[256];							//文件标题
		TIME64 fileDate;							//文件最后修改时间
		TIME64 expiredDate;							//文件失效日期，超过该日期文件即失效，无法继续修改，只能读取
		TIME64 desuetudeDate;						//在文件有效期内，让文件失效的日期
		TIME64 destroyDate;						//文件销毁日期，过期后，文件无法读取

	}ContentAttr;


	//**************标签体-对齐属性*		12
	typedef struct AlignAttr_st
	{
		INT32			fileAlignSize;
		INT32			fileEffectSize;
		INT32			labelAlignSize;
	}AlignAttr;


	//**************标签体-扩展属性*		8+nLen
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


	//**************标签体-日志属性*					120+uHCLen+uDesLen
	//1-公有 0-私有
	typedef struct tagLogContent
	{
		UINT32  uType;						//日志类型
		char  szName[128];						//操作者
		UINT32  uHCLen;						//签名证书序列号长度
		//BYTE  *pSerial;						//操作者签名证书序列号
		char  *pSerial;						//操作者签名证书序列号
		char  szHardCode[128];				//硬件编号
		TIME64  operTime;					//操作时间
		UINT32  uResult;					//操作结果
		UINT32  uDesLen;					//操作描述长度
		//BYTE  *pDescript;					//操作描述
		char  *pDescript;					//操作描述

	}LogContent;

	typedef struct tagLogAttr {
		DataBuffer nlogEnc;
		UINT32 nLogCount;
		LogContent* pLog;

	}LogAttr;



	//***************************定义标签体			SignBuffer+	CertBuffer+WaterMarkAttr+FingerPrintTagAttribute+IIdentifyAttr+ContentAttribute+IExtendAttr+ILogAttr
	typedef struct SFL_Text_st {
		SignAttributeList mSAttribute;					//使用当前操作者的签名私钥对文件进行签名后的结果
		//CertBuffer cert;								//操作者的签名证书
		//ConfigAttribute configAttr;					//配置属性	
		//SecurityAttribute securityAttr;				//安全属性
		PrivAttr priv;									//权限属性
		PSESeal stampAttr;								//印章属性
		PWaterMarkAttr waterMark;						//水印属性
		PFingerPrintTagAttr fingerPrint;			//指纹属性
		IdentifyAttr identify;							//标识属性 文件唯一标识
		ContentAttr bFileAttr;						//内容属性
		AlignAttr align;								//对齐属性
		ExtendAttr	extend;								//扩展属性
		LogAttr log;									//公有日志属性
		LogAttr prilog;									//私有日志属性
	}SFL_Text;
	//
	typedef struct SFL_DATA_st {
		BOOL bEncrypt;
		FileBuffer fileData;
	}SFL_DATA;


	////*****************************************标签结构体定义
	////定义标签结构      head+text
	typedef struct SecuredFileLabel_st {
		SFL_Head baseHead;                           //--标签头
		SFL_Text baseText;							 //--标签体
		SFL_DATA baseData;							//--文件数据
	}SecuredFileLabel;




	//api-level3
	//*********************************服务端***************************
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





	//*********************************客户端***************************
	int Client_Upload(IN const SToken* pToken,
		IN const char* srcSFL,
		OUT const char* dstSFL);

	int Client_InternalRead(IN const SToken* pToken,
		IN const char* srcSFL,
		OUT const char* dstSFL);

	int Client_InternalWrite(IN const SToken* pToken,
		IN const char* srcSFL,
		OUT const char* dstSFL);

	//公私有日志可能会有问题
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

	//*************************公共*******************
	int IsEncrypted(IN const char* srcSFL);

#ifdef __cplusplus
}
#endif