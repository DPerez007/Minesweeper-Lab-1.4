#pragma once
#include "wx/wx.h"
class Main : public wxFrame
{
public:
	Main();
	~Main();
public:
	int nFieldWidth = 10;
	int nFieldHeight = 10;
	wxButton **btn;
	int *nField = nullptr;
	bool bFirstClick = true;
	int* mineloc = nullptr;
	


	void OnButtonClicked(wxCommandEvent &evt);
	void rclick(wxMouseEvent& evt);
	wxDECLARE_EVENT_TABLE();
};

