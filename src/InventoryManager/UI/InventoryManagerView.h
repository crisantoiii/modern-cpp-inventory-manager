
// InventoryManagerView.h : interface of the CInventoryManagerView class
//

#pragma once
#include <afxcmn.h>
#include <vector>
#include <optional>
#include "Models/Product.h"
#include "Utils/FormatHelper.h"
#include "Services/ProductService.h"
#include "Repository/MemoryProductRepository.h"
#include "CProductDialog.h"

class CInventoryManagerView : public CView
{
protected: // create from serialization only
	CInventoryManagerView() noexcept;
	DECLARE_DYNCREATE(CInventoryManagerView)

// Attributes
public:
	CInventoryManagerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CInventoryManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx,int cy);
	afx_msg void OnProductDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSearchChanged();
	afx_msg void OnProductNew();

	void OnProductDelete();
	void OnProductEdit();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnUpdateProductEdit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateProductDelete(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()

private:
	CListCtrl m_ProductList;
	CEdit m_SearchEdit;
	CString m_searchText;
	ProductSortColumn m_sortColumn = ProductSortColumn::Id;
	bool m_sortAscending = true;
	ProductService& GetProductService() const;
	ProductSortColumn ToSortColumn(int column) const;
	void InitializeProductList();
	void RefreshProductList();
	INT64 FindRowByProductId(INT64 productId) const;
	std::optional<INT64> GetSelectedProductId() const;
	int GetSelectedRow() const;
	bool HasSelection() const;

};

#ifndef _DEBUG  // debug version in InventoryManagerView.cpp
inline CInventoryManagerDoc* CInventoryManagerView::GetDocument() const
   { return reinterpret_cast<CInventoryManagerDoc*>(m_pDocument); }
#endif

