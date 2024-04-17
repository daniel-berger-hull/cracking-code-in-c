#ifndef APPCONSTANT_H_INCLUDED
#define APPCONSTANT_H_INCLUDED

#define   FRAME_WIDTH       800
#define   FRAME_HEIGHT      800
#define   CANVAS_WIDTH      800
#define   CANVAS_HEIGHT     400
#define   CANVAS_MARGIN      25


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





#endif // APPCONSTANT_H_INCLUDED
