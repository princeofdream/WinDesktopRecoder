#include "stdafx.h"
#include "PThread_Main.h"


PThread_Main::PThread_Main()
{
}


PThread_Main::~PThread_Main()
{
}



UINT __cdecl ThreadProc(LPVOID pParam)
{
	int i0 = 0;
	int ret = 0;
	CString * pStr = (CString*)pParam;
	//*pStr = _T("Hello World!");
	while (true)
	{
		printf("Thread test loop: %d.\n", i0);
		i0++;
		if (i0 > 20)
			break;
		Sleep(500);
	}
	AfxEndThread(ret,TRUE/*�Ƿ�ɾ���ֳ���ռ�õ��ڴ�*/ ); //��ǰ�˳��̺߳���
	return 0;
}



UINT PThread_Main::Start_PThread(long* pParam)
{
#if 1	//thread test
	CWinThread *pThread = NULL;
	CString strArg = _T("");

	pThread = AfxBeginThread(
		ThreadProc,         //�߳���������
		&strArg,          //�߳���������
		THREAD_PRIORITY_NORMAL,       //�߳����ȼ�
		0,            //Windowsϵͳһ���߳�ջ��СΪ1 MB�������̵߳���Ŀ�������ڴ��ջ�ռ��С�й�
		0,            //�̴߳�����־���磺CREATE_SUSPENDED
		NULL);           //ϵͳ��ȫ������NULL

	if (pThread)
	{
		printf("Start PThread Sucess!");
		//pThread->m_bAutoDelete = TRUE;     //���߳̽������Զ�����̶߳���,Ĭ����TRUE
		//WaitForSingleObject(pThread->m_hThread, INFINITE); //�ȴ��߳̽���
														   //AfxMessageBox(strArg);
	}
#endif
	return 0;
}


