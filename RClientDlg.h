
// RClientDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "highgui.h"
#include <cv.h>
#include <cvaux.h>
#include "winsock.h"
#include <WINSOCK2.H>
#include <Ws2tcpip.h>
#include "mysql.h"
#include "facedata.h"
#include <vector>
#include <math.h>
#include <iomanip>
#include <string>
#include <cstring>
#include "afxwin.h"
#pragma comment(lib,"WS2_32.lib")
#pragma comment(lib, "opencv_objdetect248d.lib")
using namespace std;

// CRClientDlg 对话框
class CRClientDlg : public CDialogEx
{
// 构造
public:
	CRClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_RCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString file_path_name;
	CStatic m_pic;
	facedata fd;
	vector<double> v,vc;
	typedef struct Face{
		double k1;
		double k2;
		double k3;
		double k4;
	}facestruct;
	void showPic(CString path,CStatic *ct);
	bool dct(const char* file);
	afx_msg void OnBnClickedOpenpic();
	bool contains(double arr[],int len,double val);
	void zigzag(CvMat* m,const int n,vector<double> &v);
	void cluster(vector<double> v,vector<double> &vc,int k);
	void getSum(vector<double> v,double &sumValue);
	void group(vector<double> v,double c[],int cLen,vector< vector<double> > &g);
	bool equal(double nc[],int nLen,double c[],int cLen);
	void getMin(double d[],int len,int &ci);
	template<class Out_Type, class In_Type>
		Out_Type type_convert(const In_Type& T);
		afx_msg void OnBnClickedRecognitionbtn();
		CStatic display1;
		CStatic display2;
		CStatic display3;
public:
	WSADATA	wsd;	
	SOCKET	s;
	bool getService();
//	afx_msg void OnStnClickedRecogpic1();
	CStatic display4;
	CStatic display5;
	CStatic display6;
};
