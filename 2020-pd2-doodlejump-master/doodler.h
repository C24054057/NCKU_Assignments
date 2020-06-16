#ifndef DOODLER_H
#define DOODLER_H


#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#define doodlerSizex 40
#define doodlerSizey 45

class doodler : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    doodler();

public slots:
    void turn_right();
    void turn_left();

};


#endif // DOODLER_H
