#include "Main.h"
#include "wx/wx.h"

wxBEGIN_EVENT_TABLE(Main,wxFrame)
//EVT_BUTTON(10001,OnButtonClicked)
wxEND_EVENT_TABLE()

Main::Main() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxPoint(30,30),wxSize(800, 600))
{
	btn = new wxButton*[nFieldWidth * nFieldHeight];
	wxGridSizer *grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

	Main::nField = new int[Main::nFieldWidth * Main::nFieldHeight];
	Main::mineloc = new int[Main::nFieldWidth * Main::nFieldHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < nFieldHeight; y++)
		{

			btn[y * (Main::nFieldWidth)+x] = new wxButton(this, 10000 + (y * (Main::nFieldWidth)+x));
			grid->Add(btn[y * (Main::nFieldWidth)+x], 1, wxEXPAND | wxALL);
			btn[y * Main::nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Main::OnButtonClicked, this);
			btn[y * Main::nFieldWidth + x]->Bind(wxEVT_RIGHT_DOWN, &Main::rclick, this);
			Main::nField[y * Main::nFieldWidth + x] = 0;
			Main::mineloc[y * Main::nFieldWidth + x] = 0;
		}


	}
	this->SetSizer(grid);
	grid->Layout();
}
Main::~Main()
{
	delete[]btn;
}
void Main::OnButtonClicked(wxCommandEvent &evt)
{
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;
	//populates mines
	if (bFirstClick)
	{
		int mines = 30;
		

		while (mines)
		{
			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHeight;


			if (nField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y)
			{
				nField[ry * nFieldWidth + rx] == -1;
				mines--;

			}

		}
		bFirstClick = false;
	}
	btn[y*nFieldWidth + x]->Enable(false);
	//check
	if (nField[y*nFieldWidth + x] == -1 && Main::mineloc[y * Main::nFieldWidth + x] != 1)
	{
		wxMessageBox("BOOOM!! - GAME OVER :(");
		bFirstClick = true;
		
		for(int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++)
			{
				Main::nField[y * Main::nFieldWidth + x] = 0;
				btn[y * Main::nFieldWidth + x]->SetLabel("");
				btn[y * Main::nFieldWidth + x]->Enable(true);
				Main::mineloc[y * Main::nFieldWidth + x] = 0;
			}
	}
	else
	{
		int mine_count = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight)
				{
					if (nField[(y + j) * nFieldWidth + (x + i)] == -1)
					{
						mine_count++;
					}
				}
			}
		}

		if (Main::mineloc[y * Main::nFieldWidth + x] != 1)
		{
			btn[y * Main::nFieldWidth + x]->SetLabel(std::to_string(mine_count));
			btn[y * Main::nFieldWidth + x]->Enable(false);
		}

	}

	
	evt.Skip();
}
void Main::rclick(wxMouseEvent& evt)
{
	int x = (evt.GetId() - 10000) % Main::nFieldWidth;
	int y = (evt.GetId() - 10000) / Main::nFieldWidth;

	if (Main::mineloc[y * Main::nFieldWidth + x] == 0)
	{
		Main::mineloc[y * Main::nFieldWidth + x] = 1;
		btn[y * Main::nFieldWidth + x]->SetLabel("M");
		//btn[y * cMain::nFieldWidth + x] -> Enable(false);
	}
	else
	{
		Main::mineloc[y * Main::nFieldWidth + x] = 0;
		btn[y * Main::nFieldWidth + x]->SetLabel("");
		//btn[y * cMain::nFieldWidth + x] -> Enable(true);
	}
	
	evt.Skip();
}

