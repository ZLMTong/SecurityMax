// PETLSDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETLSDialog.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "PERVAToOffset.h"


// CPETLSDialog �Ի���

IMPLEMENT_DYNAMIC(CPETLSDialog, CDialogEx)

CPETLSDialog::CPETLSDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4_TLS, pParent)
	, m_startAddressOfRawData(_T(""))
	, m_endAddressOfRawData(_T(""))
	, m_addressOfIndex(_T(""))
	, m_addressOfCallBacks(_T(""))
	, m_sizeOfZeroFill(_T(""))
	, m_characteristics(_T(""))
{

}

CPETLSDialog::~CPETLSDialog()
{
}

void CPETLSDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_startAddressOfRawData);
	DDX_Text(pDX, IDC_EDIT2, m_endAddressOfRawData);
	DDX_Text(pDX, IDC_EDIT3, m_addressOfIndex);
	DDX_Text(pDX, IDC_EDIT4, m_addressOfCallBacks);
	DDX_Text(pDX, IDC_EDIT5, m_sizeOfZeroFill);
	DDX_Text(pDX, IDC_EDIT6, m_characteristics);
}


BEGIN_MESSAGE_MAP(CPETLSDialog, CDialogEx)
END_MESSAGE_MAP()


// CPETLSDialog ��Ϣ�������


BOOL CPETLSDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	getTLSInfo();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CPETLSDialog::getTLSInfo()
{
	// 4. �ҵ�����Ŀ¼��
	IMAGE_DATA_DIRECTORY* pDataDir = NULL;
	pDataDir = m_pOptHdr->DataDirectory;
	// 5. �õ�������RVA
	DWORD dwImpRva = pDataDir[9].VirtualAddress;


	IMAGE_TLS_DIRECTORY* pTLSHeader;

	pTLSHeader = (IMAGE_TLS_DIRECTORY*)
		(PERVAToOffset::RVAToOffset(m_pDosHDr, dwImpRva) + (DWORD)m_pDosHDr);


	m_startAddressOfRawData.Format(L"%08X", pTLSHeader->StartAddressOfRawData);
	m_endAddressOfRawData.Format(L"%08X", pTLSHeader->EndAddressOfRawData);

	m_addressOfIndex.Format(L"%08X", pTLSHeader->AddressOfIndex);
	m_addressOfCallBacks.Format(L"%08X", pTLSHeader->AddressOfCallBacks);
	m_sizeOfZeroFill.Format(L"%08X", pTLSHeader->SizeOfZeroFill);
	m_characteristics.Format(L"%08X", pTLSHeader->Characteristics);

	

}