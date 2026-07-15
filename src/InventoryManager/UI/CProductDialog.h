#pragma once
#include "afxdialogex.h"
#include "Models/Product.h"


// CProductDialog dialog

class CProductDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CProductDialog)

public:
	CProductDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CProductDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRODUCT_DIALOG};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	Product GetProduct() const;
	void SetProduct(const Product& product);

private:
	CString m_name;
	int m_quantity = 0;
	double m_price = 0;
	CString m_supplier;
	CString m_category;

	bool m_isEditMode = false;

	BOOL OnInitDialog();
	void OnOK();
};
