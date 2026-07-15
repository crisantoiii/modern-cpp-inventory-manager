// CProductDialog.cpp : implementation file
//

#include "pch.h"
#include "Application\InventoryManager.h"
#include "afxdialogex.h"
#include "UI\CProductDialog.h"


// CProductDialog dialog

IMPLEMENT_DYNAMIC(CProductDialog, CDialogEx)

CProductDialog::CProductDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRODUCT_DIALOG, pParent)
{

}

CProductDialog::~CProductDialog()
{
}

void CProductDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);

    DDX_Text(
        pDX,
        IDC_EDIT_NAME,
        m_name);

    DDX_Text(
        pDX,
        IDC_EDIT_QUANTITY,
        m_quantity);

    DDX_Text(
        pDX,
        IDC_EDIT_PRICE,
        m_price);

    DDX_Text(
        pDX,
        IDC_EDIT_SUPPLIER,
        m_supplier);

    DDX_CBString(
        pDX,
        IDC_COMBO_CATEGORY,
        m_category);
}


BEGIN_MESSAGE_MAP(CProductDialog, CDialogEx)
END_MESSAGE_MAP()


// CProductDialog message handlers
Product CProductDialog::GetProduct() const
{
    return Product
    {
        0,
        m_name,
        m_quantity,
        m_price,
        m_category,
        m_supplier
    };
}

void CProductDialog::SetProduct(const Product& product)
{
    m_name = product.name;
    m_quantity = product.quantity;
    m_price = product.price;
    m_supplier = product.supplier;
    m_category = product.category;

    m_isEditMode = true;
}

BOOL CProductDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    if (m_isEditMode)
    {
        SetWindowText(_T("Edit Product"));
    }
    else
    {
        SetWindowText(_T("Add Product"));
    }

    CComboBox* combo =
        (CComboBox*)GetDlgItem(IDC_COMBO_CATEGORY);

    combo->AddString(_T("Peripheral"));
    combo->AddString(_T("Storage"));
    combo->AddString(_T("CPU"));
    combo->AddString(_T("Memory"));
    combo->AddString(_T("Graphics"));

    combo->SetCurSel(0);

    UpdateData(FALSE);

    return TRUE;
}

void CProductDialog::OnOK()
{
    if (!UpdateData(TRUE))
        return;

    CDialogEx::OnOK();
}