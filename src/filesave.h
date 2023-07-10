#ifndef FILESAVE_H
#define FILESAVE_H

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QProcess>
#include <QWidget>
#include "views.h"
class FileSave : public QWidget{
    Q_OBJECT
public:
    explicit FileSave(QWidget *parent = nullptr);
    void m_save_file( QString );
    bool m_file_exists( QString );
    QString m_filename = "/tmp/reports-finances.html";
    QString m_save_content();
signals:

};

#endif // FILESAVE_H
