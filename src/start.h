#ifndef START_H
#define START_H

#include <QWidget>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include "views.h"

class Start : public QWidget{
    Q_OBJECT
public:
    explicit Start(QWidget *parent = nullptr);
    void m_run( QStringList );
signals:

};

#endif // START_H
