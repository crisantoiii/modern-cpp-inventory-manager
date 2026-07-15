
// InventoryManagerView.cpp : implementation of the CInventoryManagerView class
//

#include "pch.h"
#include "Application/framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "InventoryManager.h"
#endif

#include "InventoryManagerDoc.h"
#include "InventoryManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CInventoryManagerView

IMPLEMENT_DYNCREATE(CInventoryManagerView, CView)

BEGIN_MESSAGE_MAP(CInventoryManagerView, CView)
	ON_EN_CHANGE(IDC_SEARCH_EDIT,&CInventoryManagerView::OnSearchChanged)
	ON_COMMAND(ID_PRODUCT_NEWPRODUCT, &CInventoryManagerView::OnProductNew)
	ON_COMMAND(ID_PRODUCT_DELETEPRODUCT, &CInventoryManagerView::OnProductDelete)
	ON_COMMAND(ID_PRODUCT_EDITPRODUCT, &CInventoryManagerView::OnProductEdit)
	ON_UPDATE_COMMAND_UI(ID_PRODUCT_DELETEPRODUCT,&CInventoryManagerView::OnUpdateProductDelete)
	ON_UPDATE_COMMAND_UI(ID_PRODUCT_EDITPRODUCT,&CInventoryManagerView::OnUpdateProductEdit)
	ON_NOTIFY(NM_DBLCLK,IDC_PRODUCT_LIST,&CInventoryManagerView::OnProductDoubleClick)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_PRODUCT_LIST,&CInventoryManagerView::OnColumnClick)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CInventoryManagerView construction/destruction

CInventoryManagerView::CInventoryManagerView() noexcept
{
	// TODO: add construction code here

}

CInventoryManagerView::~CInventoryManagerView()
{
}

BOOL CInventoryManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CInventoryManagerView drawing

void CInventoryManagerView::OnDraw(CDC* /*pDC*/)
{
	CInventoryManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CInventoryManagerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CInventoryManagerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_PRODUCT_POPUP, point.x, point.y, this, TRUE);
#endif
}


// CInventoryManagerView diagnostics

#ifdef _DEBUG
void CInventoryManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CInventoryManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CInventoryManagerDoc* CInventoryManagerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CInventoryManagerDoc)));
	return (CInventoryManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CInventoryManagerView message handlers
int CInventoryManagerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_SearchEdit.Create(
		WS_CHILD |
		WS_VISIBLE |
		WS_BORDER |
		ES_AUTOHSCROLL,
		CRect(0, 0, 0, 0),
		this,
		IDC_SEARCH_EDIT);

	InitializeProductList();
	RefreshProductList();

	return 0;
}

void CInventoryManagerView::OnSize(
	UINT nType,
	int cx,
	int cy)
{
	CView::OnSize(nType, cx, cy);

	if (!::IsWindow(m_ProductList))
		return;

	m_SearchEdit.MoveWindow(
		10,
		10,
		cx - 20,
		24);

	m_ProductList.MoveWindow(
		10,
		40,
		cx - 20,
		cy - 50);
}

void CInventoryManagerView::InitializeProductList() {
	m_ProductList.Create(
		WS_CHILD |
		WS_VISIBLE |
		LVS_REPORT |
		LVS_SINGLESEL,
		CRect(0, 0, 0, 0),
		this,
		IDC_PRODUCT_LIST);

	m_ProductList.SetExtendedStyle(
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES |
		LVS_EX_CHECKBOXES );

	m_ProductList.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 60);
	m_ProductList.InsertColumn(1, _T("Product"), LVCFMT_LEFT, 250);
	m_ProductList.InsertColumn(2, _T("Qty"), LVCFMT_RIGHT, 80);
	m_ProductList.InsertColumn(3, _T("Price"), LVCFMT_RIGHT, 100);
	m_ProductList.InsertColumn(4, _T("Category"), LVCFMT_LEFT, 150);
	m_ProductList.InsertColumn(5, _T("Supplier"), LVCFMT_LEFT, 150);
}

void CInventoryManagerView::RefreshProductList() {
	ProductQuery query;
	query.searchText = m_searchText;
	query.sortColumn = m_sortColumn;
	query.ascending = m_sortAscending;

	const auto& products = GetProductService().GetProducts(query);

	m_ProductList.DeleteAllItems();
	int index = 0;
	for (const auto& product : products)
	{
		int row = m_ProductList.InsertItem(index, FormatHelper::ToString(product.id));
		m_ProductList.SetItemData(row, product.id);
		m_ProductList.SetItemText(row, 1, product.name);
		m_ProductList.SetItemText(row, 2, FormatHelper::ToString(product.quantity));
		m_ProductList.SetItemText(row, 3, FormatHelper::ToCurrency(product.price));
		m_ProductList.SetItemText(row, 4, product.category);
		m_ProductList.SetItemText(row, 5, product.supplier);

		index++;
	}
}

void CInventoryManagerView::OnProductNew()
{
	CProductDialog dlg;

	if (dlg.DoModal() != IDOK)
		return;

	try
	{
		GetProductService().AddProduct(dlg.GetProduct());

		RefreshProductList();
	}
	catch (const std::exception& ex)
	{
		AfxMessageBox(CString(ex.what()));
	}
}

ProductService& CInventoryManagerView::GetProductService() const
{
	return theApp.GetContext().GetProductService();
}

void CInventoryManagerView::OnProductDoubleClick(
	NMHDR*,
	LRESULT* pResult)
{
	OnProductEdit();
	*pResult = 0;
}

INT64 CInventoryManagerView::FindRowByProductId(INT64 productId) const
{
	const int itemCount = m_ProductList.GetItemCount();

	for (int row = 0; row < itemCount; ++row)
	{
		int id = static_cast<int>(m_ProductList.GetItemData(row));

		if (id == productId)
			return row;
	}

	return -1;
}

int CInventoryManagerView::GetSelectedRow() const
{
	return m_ProductList.GetNextItem(
		-1,
		LVNI_SELECTED);
}

std::optional<INT64> CInventoryManagerView::GetSelectedProductId() const
{
	int row = GetSelectedRow();

	if (row == -1)
		return std::nullopt;

	return static_cast<INT64>(m_ProductList.GetItemData(row));
}

void CInventoryManagerView::OnProductDelete()
{
	auto productId = GetSelectedProductId();

	if (!productId)
		return;

	const auto& product = GetProductService().GetProductById(*productId);

	CString message;

	message.Format(_T("Delete '%s'?"), (LPCTSTR)(product->name));

	if (AfxMessageBox(
		message,
		MB_YESNO | MB_ICONQUESTION)
		!= IDYES)
	{
		return;
	}

	try
	{
		GetProductService().DeleteProduct(product->id);

		RefreshProductList();
	}
	catch (const std::exception& ex)
	{
		AfxMessageBox(CString(ex.what()));
	}
}

void CInventoryManagerView::OnProductEdit()
{
	auto productId = GetSelectedProductId();
	if (!productId)
	{
		return;
	}

	const auto& product = GetProductService().GetProductById(*productId);

	CProductDialog dlg;

	dlg.SetProduct(*product);

	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	try
	{
		Product updated = dlg.GetProduct();

		updated.id = product->id;

		GetProductService().UpdateProduct(updated);

		RefreshProductList();
	}
	catch (const std::exception& ex)
	{
		AfxMessageBox(CString(ex.what()));
	}

	INT64 newRow = FindRowByProductId(product->id);

	if (newRow != -1)
	{
		m_ProductList.SetFocus();
		m_ProductList.SetItemState(
			static_cast<int>(newRow),
			LVIS_SELECTED | LVIS_FOCUSED,
			LVIS_SELECTED | LVIS_FOCUSED);

		m_ProductList.EnsureVisible(static_cast<int>(newRow), FALSE);
	}
}

bool CInventoryManagerView::HasSelection() const
{
	return GetSelectedProductId().has_value();
}

void CInventoryManagerView::OnUpdateProductEdit(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(HasSelection());
}

void CInventoryManagerView::OnUpdateProductDelete(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(HasSelection());
}

BOOL CInventoryManagerView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_DELETE)
		{
			if (HasSelection())
			{
				OnProductDelete();
				return TRUE;
			}
		}
	}

	return CView::PreTranslateMessage(pMsg);
}

void CInventoryManagerView::OnSearchChanged()
{
	m_SearchEdit.GetWindowText(
		m_searchText);

	RefreshProductList();
}

void CInventoryManagerView::OnColumnClick(
	NMHDR* pNMHDR,
	LRESULT* pResult)
{
	auto* pListView =
		reinterpret_cast<NMLISTVIEW*>(pNMHDR);

	int clickedColumn = pListView->iSubItem;

	auto sortColumn = ToSortColumn(clickedColumn);

	if (sortColumn == m_sortColumn)
	{
		m_sortAscending = !m_sortAscending;
	}
	else
	{
		m_sortColumn = sortColumn;
		m_sortAscending = true;
	}

	RefreshProductList();

	*pResult = 0;
}

ProductSortColumn CInventoryManagerView::ToSortColumn(int column) const
{
	switch (column)
	{
	case 0:
		return ProductSortColumn::Id;

	case 1:
		return ProductSortColumn::Name;

	case 2:
		return ProductSortColumn::Quantity;

	case 3:
		return ProductSortColumn::Price;

	case 4:
		return ProductSortColumn::Category;

	case 5:
		return ProductSortColumn::Supplier;

	default:
		return ProductSortColumn::Id;
	}
}