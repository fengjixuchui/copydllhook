// lxListBox.cpp: 实现文件
//

#include "stdafx.h"
#include "OutGoingFileTool.h"
#include "lxListBox.h"
#include "afxdialogex.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

// lxListBox 对话框

IMPLEMENT_DYNAMIC(lxListBox, CListCtrl)

lxListBox::lxListBox(CWnd* pParent /*=nullptr*/)
	: CListCtrl()
{

}

lxListBox::~lxListBox()
{
}

void lxListBox::DoDataExchange(CDataExchange* pDX)
{
	CListCtrl::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(lxListBox, CListCtrl)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// lxListBox 消息处理程序
VOID lxListBox::OnDropFiles(HDROP hDropInfo){
	UINT  nNumOfFiles = DragQueryFileA(hDropInfo, 0xFFFFFFFF, NULL, 0); //文件的个数
	char decryptbuffer[260];
	char   cFilePathName[250];
	char   pBuffer[250];
	char  Filepullpath [250] = "C:\\Users\\Wrench\\Desktop\\";
	for (UINT nIndex = 0; nIndex < nNumOfFiles; ++nIndex)
	{
		FileInfo = std::shared_ptr<rjFileInfo>(new rjFileInfo());
		DragQueryFileA(hDropInfo, nIndex, cFilePathName, _MAX_PATH);  //得到文件名
		LPARAM lParam = (LPARAM)cFilePathName;
		FileInfo->EncryptBuffer = new char[256];
		ZeroMemory(FileInfo->EncryptBuffer, 256);
		char buffer[20] = { 0 };
		USES_CONVERSION;
		try
		{
			FILE * TEMP = fopen(cFilePathName, "r");
			if(!TEMP)
			{
				printf("open fail errno = %d reason = %s \n", errno, strerror(errno));
			}
		for (int i = 0;i <=20;i++ )
		{
			auto status =fread(buffer+i, 1, 1, TEMP);
		}
		fseek(TEMP, 0, SEEK_SET);
		if (strstr(buffer, FileName)!=NULL)
		{
			//这里从加密文件中提取RjFileSrtuct结构。
			auto length = sizeof(RjFileSrtuct) + 1;
			for (int i = 0; i < length; i++)
			{
				auto status = fread(FileInfo->encryptHead.FileHeadName + i, 1, 1, TEMP);
			}

			fseek(TEMP, length, SEEK_SET);
			for (int i = 0; i <= 256; i++)
			{
				auto status = fread(FileInfo->EncryptBuffer+i, 1, 1, TEMP);
				if (!status)
					break;
				*(CHAR*)(FileInfo->EncryptBuffer + i) ^= 'a'; //decrypt buffer
				fseek(TEMP, 0, SEEK_CUR);
			}
		}
		

		strcat(Filepullpath,FileInfo->encryptHead.FileSrcName);
		FILE * TEMP1 = fopen(Filepullpath, "w+");
		for (int i = 0; i < strlen(reinterpret_cast<const char*>(FileInfo->EncryptBuffer)); i++)
		{
			fwrite(FileInfo->EncryptBuffer+i,1,1, TEMP1);
		}
		fflush(TEMP1);
		fclose(TEMP);
		fclose(TEMP1);
		}
		catch (CMemoryException* e)
		{

		}
		catch (CFileException* e)
		{

		}
		catch (CException* e)
		{

		}
		//_splitpath_s(cFilePathName, NULL, 0, NULL, 0, pBuffer, _MAX_FNAME, NULL, 0);// 得到文件名
		//这里解析加密文件的文件格式
		InsertItem(0, (LPCTSTR)FileInfo->encryptHead.FileSrcName);// 在第一列插入文件名
		//SetItemText(0, 1, (LPCTSTR)cFilePathName);// 在第二列插入文件路径
	}
	DragFinish(hDropInfo);
}
