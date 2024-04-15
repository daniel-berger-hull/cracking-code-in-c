#include "wx/wx.h"
#include "wx/sizer.h"

#include <iostream>

#include "SignalGenerator.h"


#define   FRAME_WIDTH       800
#define   FRAME_HEIGHT      800
#define   CANVAS_WIDTH      800
#define   CANVAS_HEIGHT     400
#define   CANVAS_MARGIN      25

using namespace std;

enum
{
    ID_REDRAW_BUTTON = 1,
    ID_SPAWN_CHILD = 2
};

struct DrawParam
{
   int canvasWidth;
   int canvasHeight;
   int canvasMargin;
   wxColor axisColor;
   wxColor gridColor;
};


const struct DrawParam DRAWING_PARAMS = {CANVAS_WIDTH, CANVAS_HEIGHT, CANVAS_MARGIN , wxColor(206,206,206) , wxColor(37,37,37)};





class MyApp: public wxApp
{
public:

    MyApp();
    ~MyApp();

    SignalGenerator *  getSignalGenerator()     {   return signal;   }

 private:
    bool OnInit();

   // wxFrame *frame;
   // BasicDrawPane * drawPane;
    SignalGenerator *signal = nullptr;

};



class MyFrame : public wxFrame
{
public:
    MyFrame(MyApp* parent);

private:
    MyApp* parent;
   // void OnHello(wxCommandEvent& event);
   // void OnSpawnChild(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

     wxDECLARE_EVENT_TABLE();
};



class BasicDrawPane : public wxPanel
{

public:
    BasicDrawPane(MyApp *app, wxFrame* parent);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

    DECLARE_EVENT_TABLE()


  private:

     MyApp *mainApp = nullptr;
     void drawOutsideFrame(wxDC&  dc, DrawParam canvasParam);
     void drawBackgroundGrid(wxDC&  dc,DrawParam canvasParam);
     void drawData(wxDC&  dc,DrawParam canvasParam, SignalGenerator *signal);

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
    //MyFrame * frame = new MyFrame();
    MyFrame * frame = new MyFrame(this);

    BasicDrawPane * drawPane   = new BasicDrawPane( this, (wxFrame*) frame );




//    drawPane = new BasicDrawPane( (wxFrame*) frame );

     wxButton* testButton = new wxButton( frame, ID_REDRAW_BUTTON, "OK" , wxPoint(40,700), wxSize(100,30));

    frame->SetAutoLayout(true);

    frame->Show();

    cout << "OnInit called\n";
    signal = new SignalGenerator();
    return true;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////
//                  IMPLEMENTATION OF MyFrame function members...
//////////////////////////////////////////////////////////////////////////////////////////////////////


wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
 //   EVT_MENU(ID_StartWorkerMenuItem, MyFrame::OnStartWorkerMenuItemClick)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_MENU(wxID_EXIT, MyFrame::OnExit)


  //  EVT_BUTTON(ID_StartWorkerButton, MyFrame::OnStartWorkerButtonClick) // Tell the OS to run MainFrame::OnExit when

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




//////////////////////////////////////////////////////////////////////////////////////////////////////
//                  IMPLEMENTATION OF BasicDrawPane function members...
//////////////////////////////////////////////////////////////////////////////////////////////////////


BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
// some useful events
/*
 EVT_MOTION(BasicDrawPane::mouseMoved)
 EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(BasicDrawPane::paintEvent)

END_EVENT_TABLE()


// some useful events
/*
 void BasicDrawPane::mouseMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseDown(wxMouseEvent& event) {}
 void BasicDrawPane::mouseWheelMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseReleased(wxMouseEvent& event) {}
 void BasicDrawPane::rightClick(wxMouseEvent& event) {}
 void BasicDrawPane::mouseLeftWindow(wxMouseEvent& event) {}
 */






BasicDrawPane::BasicDrawPane(MyApp *app,wxFrame* parent) : wxPanel(parent, -1, wxDefaultPosition, wxSize(CANVAS_WIDTH,CANVAS_HEIGHT))
{
   this->mainApp = app;

}

void BasicDrawPane::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    render(dc);
}


void BasicDrawPane::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void BasicDrawPane::render(wxDC&  dc)
{
    dc.SetBrush(*wxBLACK_BRUSH); // Have a black background  filling
    dc.DrawRectangle( 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT );


    // The title of the canvas...
    dc.SetTextForeground( wxColor(255,255,255) ); // 5-pixels-thick red outline
    dc.DrawText(wxT("Data Distribution"), CANVAS_WIDTH/2, 5);

    drawOutsideFrame(dc,DRAWING_PARAMS);
    drawBackgroundGrid(dc,DRAWING_PARAMS);


    drawData(dc,DRAWING_PARAMS, this->mainApp->getSignalGenerator() );





    // Look at the wxDC docs to learn how to draw other stuff
}



//void BasicDrawPane::drawOutsideFrame(wxDC&  dc, DrawParam canvasParam, wxColor color)
void BasicDrawPane::drawOutsideFrame(wxDC&  dc, DrawParam canvasParam)
{


    dc.SetPen( wxPen( wxColor(canvasParam.axisColor.Red(), canvasParam.axisColor.Green(), canvasParam.axisColor.Blue() ), 2 ) );
    dc.DrawRectangle( canvasParam.canvasMargin, canvasParam.canvasMargin,
                       canvasParam.canvasWidth-(2*canvasParam.canvasMargin),
                       canvasParam.canvasHeight-(2*canvasParam.canvasMargin) );


}

void BasicDrawPane::drawBackgroundGrid(wxDC&  dc,DrawParam canvasParam)
{
     //dc.SetPen( wxPen( wxColor(color.Red(), color.Green(), color.Blue() ), 1 ) );
     dc.SetPen( wxPen( wxColor(canvasParam.gridColor.Red(), canvasParam.gridColor.Green(), canvasParam.gridColor.Blue() ), 1 ) );

     int minX =  canvasParam.canvasMargin;
     int maxX =  canvasParam.canvasWidth-(2*canvasParam.canvasMargin);
     int minY =  canvasParam.canvasMargin;
     int maxY =  canvasParam.canvasHeight-(2*canvasParam.canvasMargin);

     for (int x=minX; x< maxX; x += canvasParam.canvasMargin)
        dc.DrawLine( x,minY, x, maxY );

     for (int y= minY; y<maxY;y+=canvasParam.canvasMargin)
        dc.DrawLine( minX,y, maxX,y );

};

void BasicDrawPane::drawData(wxDC&  dc,DrawParam canvasParam, SignalGenerator *data)
{
   if (data == nullptr)
     throw ("Invalid data (null pointer provided to the drawData method!)");
}



