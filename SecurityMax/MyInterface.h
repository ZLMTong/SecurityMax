#pragma once


// CMyInterface

class CMyInterface : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyInterface)

public:
	CMyInterface();
	virtual ~CMyInterface();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
	DWORD m_dwCount;			//��ǰѡ��Ի�������
	CDialogEx* m_pDlg[20];		//ѡ��д洢�ĶԻ�������
	void InsertTab(DWORD dwCount, ...);		//����ѡ�
	void AddDlg(DWORD dwCount, ...);		//���ӶԻ���
	void SetSelAndShow(int nSel);			//���õ�ǰѡ�еĶԻ�����ʾ
	afx_msg void OnSize(UINT nType, int cx, int cy);


	
};


