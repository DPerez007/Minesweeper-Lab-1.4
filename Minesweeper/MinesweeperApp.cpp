#include "MinesweeperApp.h"

wxIMPLEMENT_APP(MinesweeperApp);

MinesweeperApp::MinesweeperApp()
{

}
MinesweeperApp::~MinesweeperApp()
{

}
bool MinesweeperApp::OnInit()
{
	m_frame1 = new Main();
	m_frame1->Show();
	return true;
}