#ifndef PROP1_H
#define PROP1_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#define nprop1 6
#define prop1Sizex 500
#define prop1Sizey 20
#define wprop1 450
#define hprop1 30000

#define nprop2 150
#define prop2Sizex 50
#define prop2Sizey 15
#define wprop2 450
#define hprop2 30000

class prop : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    prop();


    int x, y;

};

#endif // PROP1_H
