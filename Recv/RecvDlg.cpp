// RecvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Recv.h"
#include "RecvDlg.h"
#include "SysUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll
#define BUF_SIZE 1024
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
extern ReCallFunForTcpClient pReCallFunForTcpClient;
CRecvDlg *gpTempDlg=NULL;

void ReConnetAndSendF_PROC()
{
    //AfxMessageBox("ReConnetAndSendF_PROC");
    if (NULL == gpTempDlg)
    {
        return;
    }
    gpTempDlg->ReConnetAndSendF();
}

void GReg_ReConnetAndSendF()
{
    pReCallFunForTcpClient = ReConnetAndSendF_PROC;
}

///////////////////////////////////////////////////////////////////////
class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
        // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecvDlg dialog

CRecvDlg::CRecvDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CRecvDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CRecvDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CRecvDlg::~CRecvDlg(void)
{
    delete m_pTcpServer1;
    m_pTcpServer1 = NULL;
}

void CRecvDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CRecvDlg)
    DDX_Control(pDX, IDC_NET_MSG, m_ctlNetMsg);
    DDX_Control(pDX, IDC_CONN_COUNT, m_ctlCnnCount);
    DDX_Control(pDX, IDC_INFO1, m_ctlInfo1);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRecvDlg, CDialog)
    //{{AFX_MSG_MAP(CRecvDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_CANCEL_RECV, OnCancelRecv)
    ON_BN_CLICKED(IDC_CLOSE_CNN, OnCloseCnn)
    ON_BN_CLICKED(IDC_STOP_ACCEPT, OnStopAccept)
    ON_BN_CLICKED(IDC_START_ACCEPT, OnStartAccept ,OnStartListening)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecvDlg message handlers

BOOL CRecvDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);            // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    m_pTcpServer1 = new CTcpServer(this);

    m_pTcpServer1->SetBindIpAddr("");
    m_pTcpServer1->SetPort(8000);
    m_pTcpServer1->SetProgressTimeInterval(1000);
    m_pTcpServer1->SetOnAccept(OnAccept);
    m_pTcpServer1->SetOnAcceptErr(OnAcceptErr);
    m_pTcpServer1->SetOnSocketConnect(OnSocketConnect);
    m_pTcpServer1->SetOnSocketClose(OnSocketClose);
    m_pTcpServer1->SetOnOneNetMsg(OnOneNetMsg);
    m_pTcpServer1->SetOnRecvFileRequest(OnRecvFileRequest);
    m_pTcpServer1->SetOnRecvFileProgress(OnRecvFileProgress);
    m_pTcpServer1->SetOnRecvFileFail(OnRecvFileFail);
    m_pTcpServer1->SetOnRecvFileSucc(OnRecvFileSucc);
    if(!m_pTcpServer1->StartAccept())
    {
        AfxMessageBox("��ʼ����ʧ��");
        return FALSE;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    gpTempDlg = (CRecvDlg *)this;
    GReg_ReConnetAndSendF();
    //////////////////////////////////////////////////////////////////////////////
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRecvDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you wil need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRecvDlg::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRecvDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

void CRecvDlg::OnAccept(void *pNotifyObj, SOCKET hSocket, BOOL &bAccept)
{
    CRecvDlg *pRecvDlg = (CRecvDlg *)pNotifyObj;
    CString strInfo;
    strInfo.Format("OnAccept-%d", hSocket);

    pRecvDlg->DispInfo(strInfo);
}

void CRecvDlg::OnAcceptErr(void *pNotifyObj, SOCKET hAccept)
{
    CRecvDlg *pRecvDlg = (CRecvDlg *)pNotifyObj;
    CString strInfo;
    strInfo.Format("OnAcceptErr-%d", hAccept);

    pRecvDlg->DispInfo(strInfo);
}

void CRecvDlg::OnOneNetMsg(void *pNotifyObj, char *Msg, int nMsgLen)
{
    CRecvDlg *pRecvDlg = (CRecvDlg *)pNotifyObj;
    CString strNetMsg;
    char s[10240];
    
    memcpy(s, Msg, nMsgLen);
    s[nMsgLen] = 0;
    strNetMsg = (LPCTSTR)s;

    pRecvDlg->DispNetMsg(strNetMsg);
}

void CRecvDlg::OnRecvFileRequest(void *pNotifyObj, char *szPathName, BOOL &bRecv)
{
    CRecvDlg *pRecvDlg = (CRecvDlg *)pNotifyObj;
    CString strInfo;

    strInfo = "OnRecvFileRequest: ";
    strInfo = strInfo + szPathName;
    pRecvDlg->DispInfo(strInfo);

    bRecv = TRUE;
}

void CRecvDlg::OnRecvFileProgress(void *pNotifyObj, DWORD dwRecvedBytes, DWORD dwFileSize)
{
    CRecvDlg *pRecvDlg = (CRecvDlg *)pNotifyObj;
    CString strInfo;

    strInfo.Format("%d / %d", dwRecvedBytes, dwFileSize);
    pRecvDlg->DispInfo(strInfo);
}

void CRecvDlg::OnRecvFileSucc(void *pNotifyObj, char *szPathName)
{
    CRecvDlg *pRecvDlg = (CRecvDlg *)pNotifyObj;
    CString strInfo = "OnRecvFileSucc";

    pRecvDlg->DispInfo(strInfo);

	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	CString strFilePath = szFilePath;
	strFilePath = strFilePath.Left(strFilePath.ReverseFind('\\')+1);
	CString strZipName =  szPathName;
	strZipName = strZipName.Left(strZipName.ReverseFind('.'));
	strFilePath += strZipName;
	::CreateDirectory(strFilePath, NULL);
	pRecvDlg->UnzipFile(szPathName, strFilePath);
}

void CRecvDlg::OnRecvFileFail(void *pNotifyObj, char *szPathName, EMRecvFileFailReason RecvFileFailReason)
{
    CRecvDlg *pRecvDlg = (CRecvDlg *)pNotifyObj;
    CString strInfo;
    
    strInfo.Format("[CRecvDlg]OnRecvFileFail, RecvFileFailReason = %d", RecvFileFailReason);
    pRecvDlg->DispInfo(strInfo);
}

void CRecvDlg::DispInfo(CString &strInfo)
{
    m_ctlInfo1.SetWindowText(strInfo);
}

void CRecvDlg::DispNetMsg(CString &strNetMsg)
{
    m_ctlNetMsg.SetWindowText(strNetMsg);
}

void CRecvDlg::DispCnnCount(void)
{
    CString strCnnCount;

    strCnnCount.Format("%d", m_pTcpServer1->GetClientCount());
    m_ctlCnnCount.SetWindowText(strCnnCount);
}

void CRecvDlg::OnCancelRecv() 
{
    m_pTcpServer1->CancelAllRecvFile();
}

void CRecvDlg::OnSocketConnect(void *pNotifyObj, SOCKET hSocket)
{
    CRecvDlg *pRecvDlg = (CRecvDlg *)pNotifyObj;
    CString strInfo;

    strInfo.Format("OnSocketConnect-%d", hSocket);
    pRecvDlg->DispInfo(strInfo);
    pRecvDlg->DispCnnCount();
}

void CRecvDlg::OnSocketClose(void *pNotifyObj, SOCKET hSocket, EMSocketCloseReason scr)
{
    CRecvDlg *pRecvDlg = (CRecvDlg *)pNotifyObj;
    CString strInfo;

    strInfo.Format("OnSocketDisconnect-%d, SocketCloseReason=%d", hSocket, scr);
    pRecvDlg->DispInfo(strInfo);
    pRecvDlg->DispCnnCount();
}

void CRecvDlg::OnCloseCnn() 
{
    CString strInfo = "�ر������е�����";
    m_pTcpServer1->CloseAllServerClientSocket();
    DispInfo(strInfo);
}

void CRecvDlg::OnStopAccept() 
{
    m_pTcpServer1->StopAccept();
}

void CRecvDlg::OnStartAccept() 
{
    m_pTcpServer1->StartAccept();
	OnStartListening();
}

void CRecvDlg::OnStartListening()
{
	//�ȼ���ļ��Ƿ����
	char *filename = "F:\\����\\�ֲ�ʽ���ʱ�ʾ����_���.pdf";  //�ļ���
	FILE *fp = fopen(filename, "rb");  //�Զ����Ʒ�ʽ���ļ�
	//if (fp == NULL) {
	//	printf("Cannot open file, press any key to exit!\n");
	//	system("pause");
	//	exit(0);
	//}
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("10.102.19.165");
	sockAddr.sin_port = htons(12345);
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	listen(servSock, 20);
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	//ѭ���������ݣ�ֱ���ļ���β
	char buffer[BUF_SIZE] = { 0 };  //������
	int nCount;
	while ((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0) {
		send(clntSock, buffer, nCount, 0);
	}
	shutdown(clntSock, SD_SEND);  //�ļ���ȡ��ϣ��Ͽ����������ͻ��˷���FIN��
	recv(clntSock, buffer, BUF_SIZE, 0);  //�������ȴ��ͻ��˽������
	fclose(fp);
	closesocket(clntSock);
	closesocket(servSock);
	WSACleanup();
	//system("pause");
}

void CRecvDlg::ReConnetAndSendF()
{    
    CString strInfo = "��ʼ������ӣ��ȴ�������������";
    GetDlgItem(IDC_STATIC_SHOW)->SetWindowText(strInfo);
    //AfxMessageBox("ReConnetAndSendF33");
    gpTempDlg->OnCloseCnn();
    gpTempDlg->OnStartAccept();
}


void CRecvDlg::UnzipFile(CString strFilePath, CString strTempPath)
{
	int nReturnValue;

	//��zip�ļ�
	unzFile unzfile = unzOpen(strFilePath);					
	if(unzfile == NULL)
	{
		MessageBox("��zip�ļ�ʧ��!", "��ʾ", MB_OK|MB_ICONWARNING);
		return;
	}

	//��ȡzip�ļ�����Ϣ
	unz_global_info* pGlobalInfo = new unz_global_info;
	nReturnValue = unzGetGlobalInfo(unzfile, pGlobalInfo);
	if(nReturnValue != UNZ_OK)
	{
		MessageBox("��ȡzip�ļ���Ϣʧ��!", "��ʾ", MB_OK|MB_ICONWARNING);
		return;
	}

	//����zip�ļ�
	unz_file_info* pFileInfo = new unz_file_info;
	char szZipFName[MAX_PATH];							//��Ŵ�zip�н����������ڲ��ļ���
	for(int i=0; i<pGlobalInfo->number_entry; i++)
	{
		//�����õ�zip�е��ļ���Ϣ
		nReturnValue = unzGetCurrentFileInfo(unzfile, pFileInfo, szZipFName, MAX_PATH, 
			NULL, 0, NULL, 0);
		if(nReturnValue != UNZ_OK)
		{
			MessageBox("����zip�ļ���Ϣʧ��!", "��ʾ", MB_OK|MB_ICONWARNING);
			return;
		}

		//�ж����ļ��л����ļ�
		switch(pFileInfo->external_fa)
		{
//		case FILE_ATTRIBUTE_DIRECTORY:					//�ļ���
		case 32309248:
			{
				CString strDiskPath = strTempPath + _T("//") + szZipFName;
				::CreateDirectory(strDiskPath, NULL);
			}
			break;
		default:										//�ļ�
			{
				//�����ļ�
				CString strDiskFile = strTempPath + _T("//") + szZipFName;
				HANDLE hFile = CreateFile(strDiskFile, GENERIC_WRITE,
					0, NULL, OPEN_ALWAYS, FILE_FLAG_WRITE_THROUGH, NULL);
				if(hFile == INVALID_HANDLE_VALUE)
				{
					MessageBox("�����ļ�ʧ��!", "��ʾ", MB_OK|MB_ICONWARNING);
					return;
				}

				//���ļ�
				nReturnValue = unzOpenCurrentFile(unzfile);
				if(nReturnValue != UNZ_OK)
				{
					MessageBox("���ļ�ʧ��!", "��ʾ", MB_OK|MB_ICONWARNING);
					CloseHandle(hFile);
					return;
				}

				//��ȡ�ļ�
				const int BUFFER_SIZE = 4096;
				char szReadBuffer[BUFFER_SIZE];
				while(TRUE)
				{
					memset(szReadBuffer, 0, BUFFER_SIZE);
					int nReadFileSize = unzReadCurrentFile(unzfile, szReadBuffer, BUFFER_SIZE);
					if(nReadFileSize < 0)				//��ȡ�ļ�ʧ��
					{
						MessageBox("��ȡ�ļ�ʧ��!", "��ʾ", MB_OK|MB_ICONWARNING);
						unzCloseCurrentFile(unzfile);
						CloseHandle(hFile);
						return;
					}
					else if(nReadFileSize == 0)			//��ȡ�ļ����
					{
						unzCloseCurrentFile(unzfile);
						CloseHandle(hFile);
						break;
					}
					else								//д���ȡ������
					{
						DWORD dWrite = 0;
						BOOL bWriteSuccessed = WriteFile(hFile, szReadBuffer, BUFFER_SIZE, &dWrite, NULL);
						if(!bWriteSuccessed)
						{
							MessageBox("��ȡ�ļ�ʧ��!", "��ʾ", MB_OK|MB_ICONWARNING);
							unzCloseCurrentFile(unzfile);
							CloseHandle(hFile);
							return;
						}
					}
				}
			}
			break;
		}
		unzGoToNextFile(unzfile);
	}

	//�ر�
	if(unzfile)
	{
		unzClose(unzfile);
	}
}
