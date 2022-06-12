#pragma once
#include"wx/wx.h"
#include "Main.h"
class MinesweeperApp : public wxApp
{
public:
	MinesweeperApp();
	~MinesweeperApp();
private:
	Main* m_frame1 = nullptr;

public:
	virtual bool OnInit();
};

