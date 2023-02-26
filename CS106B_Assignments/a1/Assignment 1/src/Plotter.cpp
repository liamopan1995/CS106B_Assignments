#include "Plotter.h"
#include "strlib.h"
using namespace std;

void runPlotterScript(istream& input) {
    /* TODO: Delete this line and the one after it, then implement this function. */
    double x0= 0;
    double y0 = 0;
    bool ispendown = false ;
    PenStyle style = { 1, "black" };
    drawLine(x0, y0, 0, 0, style);
    for (string line; getline(input, line); ) {
        line = toLowerCase(line);
        Vector<string> formatedline = stringSplit(line," ");

        /*double x1 = stringToDouble(formatedline[1]);
        double y1 = stringToDouble(formatedline[2]);*/
        /* can either be a definitive coordination... */
         /*..or relative increment of coordination.*/

        if(formatedline[0] == "moveabs") {
                if (ispendown)
                {
                    drawLine( x0, y0, stringToDouble(formatedline[1]), stringToDouble(formatedline[2]), style);
                }
                x0 = stringToDouble(formatedline[1]);
                y0 = stringToDouble(formatedline[2]);
        }
        if(formatedline[0] == "moverel") {
                if (ispendown)
                {
                drawLine( x0, y0, x0 + stringToDouble(formatedline[1]), y0 + stringToDouble(formatedline[2]), style);
                }
                x0 = x0 + stringToDouble(formatedline[1]);
                y0 = y0 + stringToDouble(formatedline[2]);
        }
        if(formatedline[0] == "pendown") {
                ispendown = true;
        }
        if(formatedline[0] == "penup") {
                ispendown = false;
        }
        if(formatedline[0] == "pencolor") {
                style.color = formatedline[1];
        }
        if(formatedline[0] == "penwidth") {
                style.width = stringToDouble( formatedline[1] );
        }

        }

    }


