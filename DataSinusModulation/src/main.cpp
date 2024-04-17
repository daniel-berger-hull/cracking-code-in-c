#include "wx/wx.h"
#include "wx/sizer.h"

#include <iostream>

#include "GraphRendering.h"
#include "SignalGenerator.h"
#include "GlobalData.h"

#include "AppConstant.h"





using namespace std;




class MyApp: public wxApp
{
public:

    MyApp();
    ~MyApp();

    SignalGenerator *  getSignalGenerator()     {   return signal;   }

 private:
    bool OnInit();

    SignalGenerator *signal = nullptr;

};



class MyFrame : public wxFrame
{
public:
    MyFrame(MyApp* parent);

private:
    MyApp* parent;

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

     wxDECLARE_EVENT_TABLE();
};




//////////////////////////////////////////////////////////////////////////////////////////////////////
//                  IMPLEMENTATION OF MyApp function members...
//////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_APP(MyApp)

MyApp::MyApp()
{
}

MyApp::~MyApp()
{
 if ( signal != nullptr )  delete signal;
}


bool MyApp::OnInit()
{
    MyFrame * frame = new MyFrame(this);


    GraphRendering* drawPane   = new GraphRendering( (wxFrame*) frame );

     wxButton* testButton = new wxButton( frame, ID_REDRAW_BUTTON, "OK" , wxPoint(40,700), wxSize(100,30));

    frame->SetAutoLayout(true);

    frame->Show();

    cout << "OnInit called\n";
    signal = new SignalGenerator();
    signal->generate(256);

    GlobalData* singleton = GlobalData::GetInstance();

  //  int* myBuffer = new int[256];
  //  for (int i=0;i<256;i++)   myBuffer[i] = i;

//    singleton->copySignalBuffer(myBuffer,256);
    singleton->copySignalBuffer(signal->getSignalBuffer(),256);


 //   delete myBuffer;

    return true;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////
//                  IMPLEMENTATION OF MyFrame function members...
//////////////////////////////////////////////////////////////////////////////////////////////////////


wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
 //   EVT_MENU(ID_StartWorkerMenuItem, MyFrame::OnStartWorkerMenuItemClick)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_MENU(wxID_EXIT, MyFrame::OnExit)
  //  EVT_BUTTON(ID_StartWorkerButton, MyFrame::OnStartWorkerButtonClick) // Tell the OS to run MainFrame::OnExit whe
//    EVT_THREAD(ID_WORKER_EVENT, MyFrame::OnWorkerEvent)
wxEND_EVENT_TABLE()


MyFrame::MyFrame(MyApp* parent)  : wxFrame(nullptr, wxID_ANY, "Hello World", wxDefaultPosition, wxSize(FRAME_WIDTH,FRAME_HEIGHT))
{
    this->parent = parent;
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_SPAWN_CHILD, "&Child Process...\tCtrl-C",  "Start a child process");

    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}



