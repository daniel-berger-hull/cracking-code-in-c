#include "GraphRendering.h"
#include "GlobalData.h"






BEGIN_EVENT_TABLE(GraphRendering, wxPanel)
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
EVT_PAINT(GraphRendering::paintEvent)

END_EVENT_TABLE()



//GraphRendering::GraphRendering()
GraphRendering::GraphRendering(wxFrame* parent) : wxPanel(parent, -1, wxDefaultPosition, wxSize(CANVAS_WIDTH,CANVAS_HEIGHT))
{
    //ctor
}

GraphRendering::~GraphRendering()
{
    //dtor
}

void GraphRendering::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    render(dc);
}


void GraphRendering::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void GraphRendering::render(wxDC&  dc)
{
    dc.SetBrush(*wxBLACK_BRUSH); // Have a black background  filling
    dc.DrawRectangle( 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT );


    // The title of the canvas...
    dc.SetTextForeground( wxColor(255,255,255) ); // 5-pixels-thick red outline
    dc.DrawText(wxT("Data Distribution"), CANVAS_WIDTH/2, 5);

    drawOutsideFrame(dc,DRAWING_PARAMS);
    drawBackgroundGrid(dc,DRAWING_PARAMS);
    drawData(dc,DRAWING_PARAMS);
}


//void BasicDrawPane::drawOutsideFrame(wxDC&  dc, DrawParam canvasParam, wxColor color)
void GraphRendering::drawOutsideFrame(wxDC&  dc, DrawParam canvasParam)
{
    dc.SetPen( wxPen( wxColor(canvasParam.axisColor.Red(), canvasParam.axisColor.Green(), canvasParam.axisColor.Blue() ), 2 ) );
    dc.DrawRectangle( canvasParam.canvasMargin, canvasParam.canvasMargin,
                       canvasParam.canvasWidth-(2*canvasParam.canvasMargin),
                       canvasParam.canvasHeight-(2*canvasParam.canvasMargin) );


}

void GraphRendering::drawBackgroundGrid(wxDC&  dc,DrawParam canvasParam)
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


//void BasicDrawPane::drawData(wxDC&  dc,DrawParam canvasParam, int *data)
void GraphRendering::drawData(wxDC&  dc,DrawParam canvasParam)
{
   GlobalData* singleton = GlobalData::GetInstance();

   int *data = singleton->getSignalBuffer();
   unsigned int dataSize = singleton->getBufferSize();

   if (data == nullptr || dataSize<=0)
     throw ("Invalid data (null pointer provided to the drawData method!)");


    //int centerY =  canvasParam.canvasMargin + (canvasParam.canvasHeight / 2);
    int centerY =  canvasParam.canvasHeight / 2;

    int minX =  canvasParam.canvasMargin + 4;
    int maxX =  canvasParam.canvasWidth-(2*canvasParam.canvasMargin);
    int x = minX;

    //for (x=minX; x<maxX; x+= 5)
    dc.SetPen( wxPen( wxColor(0,255,0), 2 ) ); // 5-pixels-thick red outline
    for (int i=0;i<dataSize;i++)
    {
        int y = centerY + data[i];
        dc.DrawCircle( wxPoint(x,y), 4 );
        x +=2;
    }

}

