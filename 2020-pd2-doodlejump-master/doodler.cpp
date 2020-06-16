#include "doodler.h"
#include "doodlegame.h"

doodler::doodler(){}

void doodler::turn_right(){
    if(x()>wview)
        setPos(0-doodlerSizex,y());
    else
        setPos(x()+hmove, y());
}

void doodler::turn_left(){
    if(x()+doodlerSizex<0)
        setPos(wview, y());
    else
        setPos(x()-hmove, y());
}
