#include "bullet.h"

bullet::bullet(){}


void bullet::fly()
{
    int y = this->y();
    int top = y-500;
    setPos(x(), y-3);
    if(y < top){
        this->scene()->removeItem(this);
        delete this;
    }
}
