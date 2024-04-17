#ifndef GRAPHRENDERING_H
#define GRAPHRENDERING_H

#include "wx/wx.h"

#include "AppConstant.h"




class GraphRendering : public wxPanel
{
    public:
        GraphRendering(wxFrame* parent);
        virtual ~GraphRendering();



        void paintEvent(wxPaintEvent & evt);
        void paintNow();
        void render(wxDC& dc);

     DECLARE_EVENT_TABLE()


    private:
     void drawOutsideFrame(wxDC&  dc, DrawParam canvasParam);
     void drawBackgroundGrid(wxDC&  dc,DrawParam canvasParam);
     void drawData(wxDC&  dc,DrawParam canvasParam);


};

#endif // GRAPHRENDERING_H
