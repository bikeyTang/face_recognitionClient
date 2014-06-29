
// RClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RClient.h"
#include "RClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRClientDlg �Ի���




CRClientDlg::CRClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, PicWindow, m_pic);
	DDX_Control(pDX, RecogPic1, display1);
	DDX_Control(pDX, RecogPic2, display2);
	DDX_Control(pDX, RecogPic3, display3);
	DDX_Control(pDX, recogPic4, display4);
	DDX_Control(pDX, recogPic5, display5);
	DDX_Control(pDX, recogPic6, display6);
}

BEGIN_MESSAGE_MAP(CRClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(OpenPic, &CRClientDlg::OnBnClickedOpenpic)
	ON_BN_CLICKED(RecognitionBtn, &CRClientDlg::OnBnClickedRecognitionbtn)
//	ON_STN_CLICKED(RecogPic1, &CRClientDlg::OnStnClickedRecogpic1)
END_MESSAGE_MAP()


// CRClientDlg ��Ϣ�������

BOOL CRClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	if(getService())
	{
		AfxMessageBox(_T("connect success��"));
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRClientDlg::OnBnClickedOpenpic()
{
	CFileDialog dlg(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL, 
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("JPG Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"),
		NULL);

	if(dlg.DoModal()==IDOK)
	{
		file_path_name=dlg.GetPathName(); //�ļ�����������FilePathName��
		UpdateData(false); //����·����������
		showPic(file_path_name,&m_pic);
		if(dct((LPCSTR)(LPCTSTR)file_path_name))
		{
			//��ɨ�����������о��࣬����k-means ��k=4
			cluster(v,vc,4);
			sort(vc.begin(),vc.end());
			//�Ѿ�����������facedata������
			fd.set_k1(vc[0]);
			fd.set_k2(vc[1]);
			fd.set_k3(vc[2]);
			fd.set_k4(vc[3]);
			vc.clear();
			v.clear();
		}
	}
	else
	{
		return;
	}
}
/*
	���ض��ؼ�����ʾͼƬ
*/
void CRClientDlg::showPic(CString path,CStatic *ct)
{
	if(path=="")
	{
		AfxMessageBox(_T("ͼƬ������"));
		return ;
	}
	CRect rect;
	ct->GetClientRect(&rect);
	//m_pic.GetClientRect(&rect);     //m_pictureΪPicture Control�ؼ���������ÿؼ����������

	CImage image;       //ʹ��ͼƬ��
	image.Load(path);   //װ��·����ͼƬ��Ϣ��ͼƬ��
	//CDC* pDC = m_pic.GetWindowDC();    //�����ʾ�ؼ���DC
	CDC* pDC=ct->GetWindowDC();
	image.Draw( pDC -> m_hDC,rect);      //ͼƬ���ͼƬ����Draw����
	ReleaseDC(pDC);
}
bool CRClientDlg::dct(const char* file)
{
	IplImage* img=cvLoadImage(file,1);
	if(!img)//����ʧ��
	{
		AfxMessageBox(_T("����ʧ��"));
		return false;
	}
	if(!img->imageData)//�����ͼ�������Ƿ���ȷ
	{
		AfxMessageBox(_T("�����ͼ�������Ƿ���ȷ"));
		return false;
	}

	IplImage* imggray=cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U,1);

	cvCvtColor(img,imggray,CV_RGB2GRAY);
	//��ȡͼ����Ϣ
	int height,width,step,channels;
	uchar *data;

	height=imggray->height;
	width=imggray->width;

	step=imggray->widthStep;
	channels=imggray->nChannels;
	data=(uchar *)imggray->imageData;

	CvMat *img_mat= cvCreateMat(width,height, CV_64FC1);
	IplImage* dst=cvCreateImage(cvSize(width,height),IPL_DEPTH_64F,1);
	cvConvert(imggray,img_mat);
	CvMat *imgmatquantize8;
	//����ϵ��
	int QS[8][8]={
		16,11,10,16,24,40,51,61,
		12,12,14,19,26,58,60,55,
		14,13,16,24,40,57,69,56,
		14,17,22,29,51,87,80,62,
		18,22,37,56,68,109,103,77,
		24,35,55,64,81,104,113,92,
		49,64,78,87,103,121,120,101,
		72,92,95,98,112,100,103,99
	};

	for (int ii=0;ii<width/8;ii++)
	{
		for(int jj=0;jj<height/8;jj++)
		{
			//��img_mat��ȡ��8*8�ӿ�
			CvMat *imgmatsub=cvCreateMat(8,8,CV_64FC1);
			CvRect imgmatsubrect=cvRect(8*ii,8*jj,8,8);
			cvGetSubArr(img_mat,imgmatsub,imgmatsubrect);
			IplImage* imgdstsub=cvCreateImage(cvSize(8,8),IPL_DEPTH_64F,1);
			//���ֿ����DCT����
			cvDCT(imgmatsub,imgdstsub,CV_DXT_FORWARD);
			CvMat *imgmatdctsub=cvCreateMat(8,8,CV_64FC1);
			//��DCTͼ��ת���ɾ���
			cvConvert(imgdstsub,imgmatdctsub);
			imgmatquantize8=cvCreateMat(8,8,CV_64FC1);
			for (int i=0;i<8;i++)
			{
				for(int j=0;j<8;j++)
				{	
					
					//�Ծ���DCT���ֿ��������
					double lianghua=cvRound(cvmGet(imgmatdctsub,i,j)/QS[i][j]);//quantization *QS[i][j]
					
					//��������ֵ����imgmatquantize8�У��Ա�֮���֮����zigzagɨ��
					cvmSet(imgmatquantize8,i,j,lianghua);
					
				}
			}

			//��������������zigzagɨ��,��ɨ�������ݴ���v��
			zigzag(imgmatquantize8,8,v);
			cvReleaseMat(&imgmatsub);
			cvReleaseMat(&imgmatdctsub);
			cvReleaseImage(&imgdstsub);
			cvReleaseMat(&imgmatquantize8);
		}
	}
	cvReleaseImage(&imggray);
	return true;
}
/*
	�Ծ������zigzagɨ�裬m��ʾɨ�����n��ʾ����ά��,vΪɨ���õ��Ķ�������
*/
void CRClientDlg::zigzag(CvMat* m,int n,vector<double> &v)
{
	int N,i,j,s,dir,squa;
	i=j=0;
	dir=0;
	s=0;
	N=n;
	squa=N*N;
	//ɨ��ǰ16����
	while(s<16)
	{
		switch(dir)
		{
		case 0:
			v.push_back(cvmGet(m,i,j));
			j++;
			if(0==i)
				dir=1;
			if(N-1==i)
				dir=3;
			break;
		case 1:
			v.push_back(cvmGet(m,i,j));
			i++;
			j--;
			if(N-1==i)
				dir=0;
			else if(0==j)
				dir=2;
			break;
		case 2:
			v.push_back(cvmGet(m,i,j));
			i++;
			if(0==j)
				dir=3;
			if(N-1==j)
				dir=1;
			break;
		case 3:
			v.push_back(cvmGet(m,i,j));
			i--;
			j++;
			if(N-1==j)
				dir=2;
			else if(0==i)
				dir=0;
			break;
		default:
			break;
		}
		s++;
	}
}
/*
	��֤�������Ƿ����һ��ֵ
*/
bool CRClientDlg::contains(double arr[],int len,double val)
{
	for(int i=0;i<len;i++)
	{
		if(val==arr[i])
			return true;
	}
	return false;
}
/*
	�������н��о��࣬v��ʾҪ�����������vc��ʾ���෵�صĽ����k��ʾ�۶�����
*/
void CRClientDlg::cluster(vector<double> v,vector<double> &vc,int k)
{
	double* nc=new double[k];
	double* c=new double[k];
	vector<vector<double> > g(k);
	int x=0,s=0;
	//���������ĸ���ֵ������֤������������ֵ��һ��
	for(int i=0;i<k;i++)
	{
		
		c[x++]=v[s++];
		//ȷ��c�����в�����Ҫ�����ֵ
		while(contains(c,x,v[s]))
		{
			s++;
		}

	}
	while(true)
	{
		//�������Ľ��з���
		group(v,c,k,g);
		//��������µľ�������
		double sumValue=0;
		for(int i=0;i<k;i++)
		{
			getSum(g[i],sumValue);
			nc[i]=sumValue/g[i].size();
			g[i].clear();
		}

		if(!equal(nc,k,c,k))
		{
			delete[] c;
			c=nc;
			nc=new double[k];
		}else
			break;

	}
	for(int i=0;i<k;i++){
		vc.push_back(c[i]);
	}
	delete[] nc;
	delete[] c;
}
/*
	�ж����������Ƿ����
*/
bool CRClientDlg::equal(double nc[],int nLen,double c[],int cLen)
{

	if(nLen!=cLen)
	{
		return false;
	}else{
		for(int i=0;i<cLen;i++)
		{
			if(nc[i]!=c[i])
				return false;
		}
	}
	return true;
}
/*
	�õ������ĸ���֮��
*/
void CRClientDlg::getSum(vector<double> v,double &sumValue)
{
	double sumV=0;
	vector<double>::iterator it=v.begin();
	while(it!=v.end())
	{
		sumV+=*it;
		it++;
	}
	sumValue=sumV;
}
/*
	�������������з��飬v��ʾҪ����������c��ʾ����ľ����������飬cLen��ʾc���鳤�ȣ�g���ڷ��ط���ú��������
*/
void CRClientDlg::group(vector<double> v,double c[],int cLen,vector<vector<double> > &g)
{
	double* gi=new double[v.size()];
	//���ÿ�������������
	for(int i=0;i<v.size();i++)
	{
		double* d=new double[cLen];

		for(int j=0;j<cLen;j++)
		{
			d[j]=abs(v[i]-c[j]);
		}
		int ci;
		getMin(d,cLen,ci);
		gi[i]=ci;
		delete[] d;
	}
	//��ÿ���������Ľ��з���
	for(int i=0;i<cLen;i++)
	{
		for(int j=0;j<v.size();j++)
		{
			if(gi[j]==i)
			{
				g[i].push_back(v[j]);
			}
		}
	}
	delete[] gi;
}
/*
	�����Сֵ�±�
*/
void CRClientDlg::getMin(double d[],int len,int &ci)
{
	int i=0;
	double min=d[0];
	for(int j=1;j<len;j++)
	{
		if(d[j]<min)
		{
			i=j;
			min=d[j];
		}
	}
	ci=i;
}
template<class Out_Type, class In_Type>
Out_Type CRClientDlg::type_convert(const In_Type& T)
{
	stringstream ss;
	ss<<T;
	Out_Type result;
	ss>>result;
	return result;
}
/*
	ʶ��ť�¼�
*/
void CRClientDlg::OnBnClickedRecognitionbtn()
{
	facestruct fs;
	if(fd.isNull())
	{
		AfxMessageBox(_T("δ�ҵ���ʶ��ͼƬ"));
		return ;
	}
	fs.k1=fd.get_k1();
	fs.k2=fd.get_k2();
	fs.k3=fd.get_k3();
	fs.k4=fd.get_k4();
	// �Ѵ�ʶ������������͵���������ʶ��
	int Ret= send( s, (char*)(&fd),sizeof(facedata), 0 );
	 if (Ret == SOCKET_ERROR) {
       
		AfxMessageBox(_T("send failed with error"));
        closesocket(s);
        WSACleanup();
        return ;
    }
	HANDLE hFile;
	//����6��ͼƬ��ÿ��ͼƬ��СΪ6*3209
	for(int i=0;i<6;i++)
	{
		DWORD dwNumberOfBytesRecv=0;
		DWORD dwCountOfBytesRecv=0;
		char Buffer[3209];
		CString filename ;
		filename.Append(type_convert<string>(i).c_str());
		filename.Append(".bmp");
		file_path_name=filename;
		hFile = CreateFile(filename,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		int count=0;
		do 
		{
			count++;
			dwNumberOfBytesRecv = recv(s,Buffer,sizeof(Buffer),0);
			WriteFile(hFile,Buffer,dwNumberOfBytesRecv,&dwNumberOfBytesRecv,NULL);
		} while (count<6);
		
		 CloseHandle(hFile);
	}
	//�ѽ��յ���ͼƬ����Ӧ�ؼ�����ʾ
	for(int i=0;i<6;i++)
	{
		CString path ;
		path.Append(type_convert<string>(i).c_str());
		path.Append(".bmp");
		switch(i)
		{
		case 0:
			showPic(path,&display1);
			break;
		case 1:
			showPic(path,&display2);
			break;
		case 2:
			showPic(path,&display3);
			break;
		case 3:
			showPic(path,&display4);
			break;
		case 4:
			showPic(path,&display5);
			break;
		case 5:
			showPic(path,&display6);
			break;
		}
	}
}
/*
	���ӷ�������
*/
bool CRClientDlg::getService()
{
	if(WSAStartup(MAKEWORD(2,2),&wsd) != 0)
	{
		AfxMessageBox(_T("WSAStartup failed"));
		return false;
	}
	// �����׽���
	s= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//tcp
	//s = socket(AF_INET,SOCK_DGRAM,0);//udp
	if(s == INVALID_SOCKET)
	{
		AfxMessageBox(_T("socket() failed"));
		WSACleanup();
		return false;
	}
	//char		buf[BUF_SIZE];	// ��������
	SOCKADDR_IN	servAddr;		// �������׽��ֵ�ַ
	//SOCKET		sockClient = socket(AF_INET,SOCK_DGRAM,0);
	int			nRet;
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(5000);

	// ���������������
	//send(sockClient,(char*)(&fd),sizeof(facedata),NULL);
	int nServAddLen = sizeof(servAddr);
	nRet=connect( s, (SOCKADDR*) &servAddr, sizeof(servAddr) );
	if (nRet == SOCKET_ERROR) 
	{
       // wprintf(L"connect failed with error: %d\n", WSAGetLastError() );
		AfxMessageBox(_T("connect failed with error"));
        closesocket(s);
        WSACleanup();
        return false;
	}
	return true;
}
