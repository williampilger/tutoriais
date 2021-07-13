#include <wx\wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <string.h>

int board[3][3];

bool player;//qual o player que está na vez
int turnos;//conta o s turnos
int ganhador;//jogador que ganhou. Zero se ninguem ganhou

void initBoard() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = 0;
		}
	}
	player = false;
	turnos = 0;
	ganhador = 0;
}

void checkBoard() {//verifica se alguém ganho
	//verificando linhas
	for (int i = 0; i < 3; i++) {
		int p1 = 0, p2 = 0;
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 1) p1++;
			if (board[i][j] == 2) p2++;
		}
		if (p1 == 3) {
			ganhador = 1;
			break;
		}
		else if (p2 == 3) {
			ganhador = 2;
			break;
		}
	}
	//verificando Colunas
	for (int i = 0; i < 3; i++) {
		int p1 = 0, p2 = 0;
		for (int j = 0; j < 3; j++) {
			if (board[j][i] == 1) p1++;
			if (board[j][i] == 2) p2++;
		}
		if (p1 == 3) {
			ganhador = 1;
			break;
		}
		else if (p2 == 3) {
			ganhador = 2;
			break;
		}
	}
	//Verificando diagonal principal

}

class ticTacToe : public wxApp {
public:
	virtual bool OnInit();
};

class MainFrame : public wxFrame {
public:
	MainFrame();
protected:
	wxMenuBar* m_mainMenuBar;
	wxMenu* m_menuGame;
	wxMenu* m_menuHelp;

	wxButton* m_btnUpLeft;
	wxButton* m_btnUpMid;
	wxButton* m_btnUpRight;
	
	wxButton* m_btnMidLeft;
	wxButton* m_btnMidMid;
	wxButton* m_btnMidRight;
	
	wxButton* m_btnLowLeft;
	wxButton* m_btnLowMid;
	wxButton* m_btnLowRight;

	wxStatusBar* m_statusBar;

	char m_msgStatusBar[200];

private:
	void OnNewGame(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	void OnBtnUpLeftClick(wxCommandEvent& event);
	void OnBtnUpMidClick(wxCommandEvent& event);
	void OnBtnUpRightClick(wxCommandEvent& event);

	void OnBtnMidLeftClick(wxCommandEvent& event);
	void OnBtnMidMidClick(wxCommandEvent& event);
	void OnBtnMidRightClick(wxCommandEvent& event);

	void OnBtnLowLeftClick(wxCommandEvent& event);
	void OnBtnLowMidClick(wxCommandEvent& event);
	void OnBtnLowRightClick(wxCommandEvent& event);
};

bool ticTacToe::OnInit() {//Método executado automaticamente
	MainFrame* frame = new MainFrame();
	frame->Show();
	//Aqui teremos que iniciar o tabuleiro
	return true;
}

enum {
	ID_NewGame = 1
};

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Tic Tac Toe") {
	this->SetSizeHints(600, 600);

	m_mainMenuBar = new wxMenuBar(0);//Menu Bar
	m_menuGame = new wxMenu();
	m_menuHelp = new wxMenu();

	m_mainMenuBar->Append(m_menuGame, "Game");//Coloca os botões na menuBar
	m_mainMenuBar->Append(m_menuHelp, "Help");

	//Criar submenus do menu GAME
	m_menuGame->Append(ID_NewGame, "&NewGame\tCtrl-N", "Start a new match");//Nome do botão, & Sublinha a letra de atalho. \t Joga pro final da linha
	m_menuGame->AppendSeparator();//Coloca um separador
	m_menuGame->Append(wxID_EXIT);//Botão que finaliza o programa

	//Criando submenus do menu HELP
	m_menuHelp->Append(wxID_ABOUT);

	wxFont font(48, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	this->SetMenuBar(m_mainMenuBar); //mostra a menu bar

	//Criando o GridSizer (vai fixar o layout da página, tipo uma matriz)
	wxGridSizer* gBoard = new wxGridSizer(3, 3, 0, 0);
	gBoard->SetMinSize(500, 500); //Deixa reduzir a janela no máximo até 500x500

	m_btnUpLeft = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnUpLeft->SetFont(font);
	gBoard->Add(m_btnUpLeft, 0, wxALL | wxEXPAND, 5);//Adiciona o botão ao grid. wxALL | wxEXPAND força ele a preencher todo o espaço. 5 define uma borda de 5 em torno do botão.

	m_btnUpMid = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnUpMid->SetFont(font);
	gBoard->Add(m_btnUpMid, 0, wxALL | wxEXPAND, 5);

	m_btnUpRight = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnUpRight->SetFont(font);
	gBoard->Add(m_btnUpRight, 0, wxALL | wxEXPAND, 5);
	
	m_btnMidLeft = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnMidLeft->SetFont(font);
	gBoard->Add(m_btnMidLeft, 0, wxALL | wxEXPAND, 5);//Adiciona o botão ao grid. wxALL | wxEXPAND força ele a preencher todo o espaço. 5 define uma borda de 5 em torno do botão.

	m_btnMidMid = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnMidMid->SetFont(font);
	gBoard->Add(m_btnMidMid, 0, wxALL | wxEXPAND, 5);

	m_btnMidRight = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnMidRight->SetFont(font);
	gBoard->Add(m_btnMidRight, 0, wxALL | wxEXPAND, 5);

	m_btnLowLeft = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnLowLeft->SetFont(font);
	gBoard->Add(m_btnLowLeft, 0, wxALL | wxEXPAND, 5);//Adiciona o botão ao grid. wxALL | wxEXPAND força ele a preencher todo o espaço. 5 define uma borda de 5 em torno do botão.

	m_btnLowMid = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnLowMid->SetFont(font);
	gBoard->Add(m_btnLowMid, 0, wxALL | wxEXPAND, 5);

	m_btnLowRight = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnLowRight->SetFont(font);
	gBoard->Add(m_btnLowRight, 0, wxALL | wxEXPAND, 5);

	this->SetSizer(gBoard);//Define o grid
	this->Layout();

	m_statusBar = this->CreateStatusBar(1, wxST_SIZEGRIP, wxID_ANY);

	this->Centre(wxBOTH);
	
	//Eventos de botões
	Bind(wxEVT_MENU, &MainFrame::OnNewGame, this, ID_NewGame);
	Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
	m_btnUpLeft->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnUpLeftClick), NULL, this);
	m_btnUpMid->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnUpMidClick), NULL, this);
	m_btnUpRight->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnUpRightClick), NULL, this);
	m_btnMidLeft->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnMidLeftClick), NULL, this);
	m_btnMidMid->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnMidMidClick), NULL, this);
	m_btnMidRight->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnMidRightClick), NULL, this);
	m_btnLowLeft->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnLowLeftClick), NULL, this);
	m_btnLowMid->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnLowMidClick), NULL, this);
	m_btnLowRight->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnLowRightClick), NULL, this);
}

wxIMPLEMENT_APP(ticTacToe);

void MainFrame::OnNewGame(wxCommandEvent& event) {
	wxMessageBox("Test... New Game!", "New Game...", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("Este eh um texte, escrito por William Pilger", "Sobre", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnExit(wxCommandEvent& event) {
	Close(true);
}

void MainFrame::OnBtnUpLeftClick(wxCommandEvent& event) {

}
void MainFrame::OnBtnUpMidClick(wxCommandEvent& event) {

}
void MainFrame::OnBtnUpRightClick(wxCommandEvent& event) {

}
void MainFrame::OnBtnMidLeftClick(wxCommandEvent& event) {

}
void MainFrame::OnBtnMidMidClick(wxCommandEvent& event) {

}
void MainFrame::OnBtnMidRightClick(wxCommandEvent& event) {

}
void MainFrame::OnBtnLowLeftClick(wxCommandEvent& event) {

}
void MainFrame::OnBtnLowMidClick(wxCommandEvent& event) {

}
void MainFrame::OnBtnLowRightClick(wxCommandEvent& event) {

}