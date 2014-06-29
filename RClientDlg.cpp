
// RClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RClient.h"
#include "RClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CRClientDlg 对话框




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


// CRClientDlg 消息处理程序

BOOL CRClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	if(getService())
	{
		AfxMessageBox(_T("connect success！"));
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRClientDlg::OnBnClickedOpenpic()
{
	CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL, 
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("JPG Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"),
		NULL);

	if(dlg.DoModal()==IDOK)
	{
		file_path_name=dlg.GetPathName(); //文件名保存在了FilePathName里
		UpdateData(false); //更新路径公共变量
		showPic(file_path_name,&m_pic);
		if(dct((LPCSTR)(LPCTSTR)file_path_name))
		{
			//对扫描后的向量进行聚类，这里k-means 的k=4
			cluster(v,vc,4);
			sort(vc.begin(),vc.end());
			//把聚类结果保存在facedata对象中
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
	在特定控件上显示图片
*/
void CRClientDlg::showPic(CString path,CStatic *ct)
{
	if(path=="")
	{
		AfxMessageBox(_T("图片不存在"));
		return ;
	}
	CRect rect;
	ct->GetClientRect(&rect);
	//m_pic.GetClientRect(&rect);     //m_picture为Picture Control控件变量，获得控件的区域对象

	CImage image;       //使用图片类
	image.Load(path);   //装载路径下图片信息到图片类
	//CDC* pDC = m_pic.GetWindowDC();    //获得显示控件的DC
	CDC* pDC=ct->GetWindowDC();
	image.Draw( pDC -> m_hDC,rect);      //图片类的图片绘制Draw函数
	ReleaseDC(pDC);
}
bool CRClientDlg::dct(const char* file)
{
	IplImage* img=cvLoadImage(file,1);
	if(!img)//载入失败
	{
		AfxMessageBox(_T("载入失败"));
		return false;
	}
	if(!img->imageData)//载入的图像数据是否正确
	{
		AfxMessageBox(_T("载入的图像数据是否正确"));
		return false;
	}

	IplImage* imggray=cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U,1);

	cvCvtColor(img,imggray,CV_RGB2GRAY);
	//获取图像信息
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
	//量化系数
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
			//从img_mat中取出8*8子块
			CvMat *imgmatsub=cvCreateMat(8,8,CV_64FC1);
			CvRect imgmatsubrect=cvRect(8*ii,8*jj,8,8);
			cvGetSubArr(img_mat,imgmatsub,imgmatsubrect);
			IplImage* imgdstsub=cvCreateImage(cvSize(8,8),IPL_DEPTH_64F,1);
			//对字块进行DCT处理
			cvDCT(imgmatsub,imgdstsub,CV_DXT_FORWARD);
			CvMat *imgmatdctsub=cvCreateMat(8,8,CV_64FC1);
			//把DCT图像转化成矩阵
			cvConvert(imgdstsub,imgmatdctsub);
			imgmatquantize8=cvCreateMat(8,8,CV_64FC1);
			for (int i=0;i<8;i++)
			{
				for(int j=0;j<8;j++)
				{	
					
					//对经过DCT后字块进行量化
					double lianghua=cvRound(cvmGet(imgmatdctsub,i,j)/QS[i][j]);//quantization *QS[i][j]
					
					//另将量化后值存在imgmatquantize8中，以便之后对之进行zigzag扫描
					cvmSet(imgmatquantize8,i,j,lianghua);
					
				}
			}

			//对量化后矩阵进行zigzag扫描,把扫描后的数据存在v中
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
	对矩阵进行zigzag扫描，m表示扫描矩阵，n表示矩阵维度,v为扫描后得到的定长向量
*/
void CRClientDlg::zigzag(CvMat* m,int n,vector<double> &v)
{
	int N,i,j,s,dir,squa;
	i=j=0;
	dir=0;
	s=0;
	N=n;
	squa=N*N;
	//扫描前16个数
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
	验证数组中是否包含一个值
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
	对向量中进行聚类，v表示要聚类的向量，vc表示聚类返回的结果，k表示聚多少类
*/
void CRClientDlg::cluster(vector<double> v,vector<double> &vc,int k)
{
	double* nc=new double[k];
	double* c=new double[k];
	vector<vector<double> > g(k);
	int x=0,s=0;
	//给聚类中心赋初值，并保证各个聚类中心值不一样
	for(int i=0;i<k;i++)
	{
		
		c[x++]=v[s++];
		//确保c数组中不包含要加入的值
		while(contains(c,x,v[s]))
		{
			s++;
		}

	}
	while(true)
	{
		//根据中心进行分类
		group(v,c,k,g);
		//求分类后的新的聚类中心
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
	判断两个数组是否相等
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
	得到向量的各数之和
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
	对向量中数进行分组，v表示要分组向量，c表示求出的聚类中心数组，cLen表示c数组长度，g用于返回分类好后的向量集
*/
void CRClientDlg::group(vector<double> v,double c[],int cLen,vector<vector<double> > &g)
{
	double* gi=new double[v.size()];
	//标记每个数所属的组别
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
	//对每个聚类中心进行分组
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
	获得最小值下标
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
	识别按钮事件
*/
void CRClientDlg::OnBnClickedRecognitionbtn()
{
	facestruct fs;
	if(fd.isNull())
	{
		AfxMessageBox(_T("未找到待识别图片"));
		return ;
	}
	fs.k1=fd.get_k1();
	fs.k2=fd.get_k2();
	fs.k3=fd.get_k3();
	fs.k4=fd.get_k4();
	// 把待识别对象向量传送到服务器端识别
	int Ret= send( s, (char*)(&fd),sizeof(facedata), 0 );
	 if (Ret == SOCKET_ERROR) {
       
		AfxMessageBox(_T("send failed with error"));
        closesocket(s);
        WSACleanup();
        return ;
    }
	HANDLE hFile;
	//接收6张图片，每张图片大小为6*3209
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
	//把接收到的图片在相应控件上显示
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
	连接服务器端
*/
bool CRClientDlg::getService()
{
	if(WSAStartup(MAKEWORD(2,2),&wsd) != 0)
	{
		AfxMessageBox(_T("WSAStartup failed"));
		return false;
	}
	// 创建套接字
	s= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//tcp
	//s = socket(AF_INET,SOCK_DGRAM,0);//udp
	if(s == INVALID_SOCKET)
	{
		AfxMessageBox(_T("socket() failed"));
		WSACleanup();
		return false;
	}
	//char		buf[BUF_SIZE];	// 接受数据
	SOCKADDR_IN	servAddr;		// 服务器套接字地址
	//SOCKET		sockClient = socket(AF_INET,SOCK_DGRAM,0);
	int			nRet;
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(5000);

	// 向服务器发送数据
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
