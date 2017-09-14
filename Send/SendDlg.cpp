// SendDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Send.h"
#include "SendDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
extern ReCallFunForTcpClient pReCallFunForTcpClient;
CSendDlg *gpTempDlg=NULL;

void ReConnetAndSendF_PROC()
{
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
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
// CSendDlg dialog

CSendDlg::CSendDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendDlg)
	m_dwFilePackageSize = 0;
	m_strServerIp = _T("");
	m_nPort = 0;
	m_strFileName = _T("");
	m_strDLFileName = _T("");
	m_strMsg = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pTcpClient = new CTcpClient(this);
}

CSendDlg::~CSendDlg(void)
{
	delete m_pTcpClient;
}

void CSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendDlg)
	DDX_Control(pDX, IDC_CNN_STATUS, m_ctlCnnStatus);
	DDX_Control(pDX, IDC_INFO, m_ctlInfo);
	DDX_Control(pDX, IDC_STATIC_SENDRATE, m_SendRate);
	DDX_Text(pDX, IDC_FILE_PACKAGE_SIZE, m_dwFilePackageSize);
	DDV_MinMaxInt(pDX, m_dwFilePackageSize, 1, 99996);
	DDX_Text(pDX, IDC_SERVER_IP, m_strServerIp);
	DDX_Text(pDX, IDC_PORT, m_nPort);
	DDX_Text(pDX, IDC_FILE_NAME, m_strFileName);
	DDX_Text(pDX, IDC_DLFILE_NAME, m_strDLFileName);
	DDX_Text(pDX, IDC_MSG, m_strMsg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSendDlg, CDialog)
	//{{AFX_MSG_MAP(CSendDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
	ON_BN_CLICKED(IDC_SEND, OnSendFile)
	ON_BN_CLICKED(IDC_SEND_MSG, OnSendMsg)
	ON_BN_CLICKED(IDC_CANCEL_SEND, OnCancelSend)
	ON_BN_CLICKED(IDC_BUTTON_DIR_PATH, OnButtonDirPath)
	ON_BN_CLICKED(IDC_DOWNLOAD, OnBnClickedDownload)
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendDlg message handlers

BOOL CSendDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_strServerIp = "10.102.19.165";// "127.0.0.1";
	m_nPort = 8000;
	m_dwFilePackageSize = 1024;
	m_strFileName = "C:\\Users\\Administrator\\Desktop\\qqq";
	m_strDLFileName = "C:\\Users\\Administrator\\Desktop\\qqq";
	UpdateData(FALSE);

	m_pTcpClient->SetProgressTimeInterval(100);
	m_pTcpClient->SetOnSocketClose(OnSocketClose);
	m_pTcpClient->SetOnOneNetMsg(OnOneNetMsg);
	m_pTcpClient->SetOnSendFileSucc(OnSendFileSucc);
	m_pTcpClient->SetOnSendFileFail(OnSendFileFail);
	m_pTcpClient->SetOnSendFileProgress(OnSendFileProgress);
	m_pTcpClient->SetOnSendFileRate(OnSendFileRate);

	/////////////////////////////////////////////////////////////
	gpTempDlg = (CSendDlg *)this;
	GReg_ReConnetAndSendF();
	/////////////////////////////////////////////////////////////

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSendDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSendDlg::OnPaint() 
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
HCURSOR CSendDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSendDlg::OnButtonDirPath() 
{
	char path[MAX_PATH];
	ZeroMemory(path, MAX_PATH);
	
	BROWSEINFO browseInfo;
	browseInfo.hwndOwner = m_hWnd;
	browseInfo.pidlRoot = NULL;
	browseInfo.pszDisplayName = path;
	browseInfo.lpszTitle = "ѡ��Ŀ¼";
	browseInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	browseInfo.lpfn = NULL;
	browseInfo.lParam = 0;
	browseInfo.iImage = 0;
	
	LPITEMIDLIST plDList = SHBrowseForFolder(&browseInfo);
	if(plDList && SHGetPathFromIDList(plDList, path))
	{
		m_strFileName = path;
	}
	
	UpdateData(FALSE);
}

void CSendDlg::OnConnect() 
{
	if(!UpdateData())
		return;

	m_pTcpClient->SetServerIpAddr((char *)(LPCTSTR)m_strServerIp);
	m_pTcpClient->SetPort(m_nPort);
	m_pTcpClient->SetFilePackageSize(m_dwFilePackageSize);
	
	m_ctlCnnStatus.SetWindowText("��ȴ�...");
	if(!m_pTcpClient->Connect())
		m_ctlCnnStatus.SetWindowText("����ʧ��!");
	else
		m_ctlCnnStatus.SetWindowText("������");
}

void CSendDlg::OnDisconnect() 
{
	m_pTcpClient->Disconnect();
	m_ctlCnnStatus.SetWindowText("�Ͽ�����");
}


void CSendDlg::OnSendFile() 
{
	DispInfo(""); // �����Ϣ

	if(!UpdateData())
		return;

	if(m_strFileName.IsEmpty())
	{
		MessageBox("Ҫ���͵��ļ���·������Ϊ��!");
		return;
	}

	CString strZipFileName = m_strFileName + _T(".zip");
	DispInfo("����ѹ���ļ�...");
	CreateZipFromDir(m_strFileName, strZipFileName);
	DispInfo("�ļ�ѹ����ɣ���ʼ����...");

	m_pTcpClient->SetFilePackageSize(m_dwFilePackageSize);
	if(!m_pTcpClient->SendFile((char *)(LPCTSTR)strZipFileName))
		//AfxMessageBox("�����ļ�ʧ��");
		//DispInfo("�����ļ�ʧ��");
		;
	
}

void CSendDlg::OnSendMsg(void)
{
	char s[99999];

	if(!UpdateData())
		return;


	sprintf(s, "@00000001%s", m_strMsg);
	m_pTcpClient->SendNetMsg(s, strlen(s) - 6);
}

void CSendDlg::OnSocketClose(void *pNotifyObj, SOCKET hSocket, EMSocketCloseReason scr)
{
	CSendDlg *pSendDlg = (CSendDlg *)pNotifyObj;
	CString strInfo;

	strInfo.Format("�Ͽ����ӣ�SocketCloseReason = %d", scr);
	pSendDlg->m_ctlCnnStatus.SetWindowText(strInfo);
}

void CSendDlg::OnOneNetMsg(void *pNotifyObj, char *Msg, int nMsgLen)
{
	CSendDlg *pSendDlg = (CSendDlg *)pNotifyObj;
	char s[9999];
	CString strInfo;

	strncpy(s, Msg, nMsgLen);
	s[nMsgLen] = 0;
	strInfo = s;

	pSendDlg->DispInfo(strInfo);
}

void CSendDlg::OnSendFileSucc(void *pNotifyObj, char *szPathName)
{
	CSendDlg *pSendDlg = (CSendDlg *)pNotifyObj;
	
	pSendDlg->DispInfo("������ϣ�");
}

void CSendDlg::OnSendFileFail(void *pNotifyObj, char *szPathName, EMSendFileFailReason SendFileFailReadson)
{
	CSendDlg *pSendDlg = (CSendDlg *)pNotifyObj;
	CString strInfo;

	strInfo.Format("OnSendFileFail,SendFileFailReason = %d", SendFileFailReadson);
	pSendDlg->DispInfo(strInfo);
}

void CSendDlg::OnSendFileProgress(void *pNotifyObj, int nSentBytes, int nTotalBytes)
{
	CSendDlg *pSendDlg = (CSendDlg *)pNotifyObj;
	CString strInfo;
	
	strInfo.Format("%d / %d", nSentBytes, nTotalBytes); 
	pSendDlg->DispInfo(strInfo);
	pSendDlg->DispSendRate(strInfo);
}

void CSendDlg::OnSendFileRate(void *pNotifyObj, int nSendRate)
{
	CSendDlg *pSendDlg = (CSendDlg *)pNotifyObj;
	CString strInfo;
	
	strInfo.Format("%d KB/s", nSendRate);
	pSendDlg->DispSendRate(strInfo);
}

void CSendDlg::DispInfo(CString strInfo)
{
	m_ctlInfo.SetWindowText(strInfo);
}

void CSendDlg::DispSendRate(CString strInfo)
{
	m_SendRate.SetWindowText(strInfo);
}


void CSendDlg::OnCancelSend() 
{
	m_pTcpClient->CancelSendFile();	
}

void CSendDlg::ReConnetAndSendF()
{
	//AfxMessageBox("�Զ��ؽ�");
	m_pTcpClient->Disconnect();
	m_pTcpClient->Connect();
	OnSendFile();
	//OnConnect();
	//OnSendFile();
}


//-----------------------------------------------------------------------------------
//���ļ���ӵ�zip�ļ��У�ע�����Դ�ļ�srcFileΪ������ӿ�Ŀ¼  
//fileNameInZip: ��zip�ļ��е��ļ������������·��  
void CSendDlg::AddFileToZip(zipFile zf, const char* fileNameInZip, const char* srcFile)  
{  
	FILE* srcfp = NULL;  
	
	//��ʼ��д��zip���ļ���Ϣ  
	zip_fileinfo zi;  
	zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour =  
		zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;  
	zi.dosDate = 0;  
	zi.internal_fa = 0;  
	zi.external_fa = 0;  
	
	//���srcFileΪ�գ������Ŀ¼  
	char new_file_name[MAX_PATH];  
	memset(new_file_name, 0, sizeof(new_file_name));  
	strcat(new_file_name, fileNameInZip);  
	if (srcFile == NULL)  
	{  
		strcat(new_file_name, "/");  
	}  
    
	//��zip�ļ��д������ļ�  
	zipOpenNewFileInZip(zf, new_file_name, &zi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION);  
	
	if (srcFile != NULL)  
	{  
		//��Դ�ļ�  
		srcfp = fopen(srcFile, "rb");  
		if (srcfp == NULL)  
		{  
			MessageBox(_T("�޷�����ļ�") + CString(srcFile) + _T("!"));  
			zipCloseFileInZip(zf); //�ر�zip�ļ�  
			return;  
		}  
		
		//����Դ�ļ���д��zip�ļ�  
		char buf[100*1024]; //buffer  
		int numBytes = 0;  
		while( !feof(srcfp) )  
		{  
			numBytes = fread(buf, 1, sizeof(buf), srcfp);  
			zipWriteInFileInZip(zf, buf, numBytes);  
			if( ferror(srcfp) )  
				break;  
		}  
		
		//�ر�Դ�ļ�  
		fclose(srcfp);  
	}  
	
	//�ر�zip�ļ�  
	zipCloseFileInZip(zf);  
}  


//�ݹ������Ŀ¼��zip�ļ�  
void CSendDlg::CollectFilesInDirToZip(zipFile zf, const CString& strPath, const CString& parentDir)  
{  
//  USES_CONVERSION; //for W2CA  
    
  CString strRelativePath;  
  CFileFind finder;   
  BOOL bWorking = finder.FindFile(strPath + _T("//*.*"));  
  while(bWorking)   
  {   
      bWorking = finder.FindNextFile();   
      if(finder.IsDots())  
          continue;   
        
      if (parentDir == _T(""))  
          strRelativePath = finder.GetFileName();  
      else  
          strRelativePath = parentDir + _T("//") + finder.GetFileName(); //������zip�ļ��е����·��  
    
      if(finder.IsDirectory())  
      {  
          AddFileToZip(zf, strRelativePath, NULL); //��zip�ļ�������Ŀ¼�ṹ  
          CollectFilesInDirToZip(zf, finder.GetFilePath(), strRelativePath); //�ݹ��ռ���Ŀ¼�ļ�  
          continue;  
      }  
        
      AddFileToZip(zf, strRelativePath, finder.GetFilePath()); //���ļ���ӵ�zip�ļ���  
  }  
} 

//���սӿڣ���ĳ��Ŀ¼����zip�ļ�  
void CSendDlg::CreateZipFromDir(const CString& dirName, const CString& zipFileName)  
{  
//	USES_CONVERSION; //ʹ��W2CAת��unicode�ַ���  
	zipFile newZipFile = zipOpen(zipFileName, 0); //����zip�ļ�  
	if (newZipFile == NULL)  
	{  
		MessageBox(_T("�޷�����zip�ļ�!"));  
		return;  
	}  
    
	CollectFilesInDirToZip(newZipFile, dirName, _T(""));  
	zipClose(newZipFile, NULL); //�ر�zip�ļ�  
}  




//***********************************************************************//
void  DownloadFile()
{
	char *filename = "E:\\test_jie.pdf";

	FILE *fp = fopen(filename, "wb");  //�Զ����Ʒ�ʽ�򿪣��������ļ�

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("10.102.19.165");
	sockAddr.sin_port = htons(12345);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//ѭ���������ݣ�ֱ���ļ��������
	char buffer[1024] = { 0 };  //�ļ�������
	int nCount;
	while ((nCount = recv(sock, buffer, 1024, 0)) > 0) {
		fwrite(buffer, nCount, 1, fp);
	}

	fclose(fp);
	closesocket(sock);
	WSACleanup();
}

//�����ļ�
void CSendDlg::OnBnClickedDownload()
{
	DownloadFile();
}

//***********************************************************************//