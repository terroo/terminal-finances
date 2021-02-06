#ifndef TOOLS_H
#define TOOLS_H

#include <QWidget>
#include <QDebug>
#include <QDateTime>
#include <QList>
#include <QLocale>
#include "views.h"

class Tools : public QWidget{
    Q_OBJECT
public:
    explicit Tools(QWidget *parent = nullptr);
    bool m_fields_validate( QStringList );
    void m_get_datetime();
    QString m_get_month();
    QString m_rm_semidot( QString );
    int m_datetime[6];
    QStringList m_all_months();
    QString m_currency( QString );
    QString m_return_filename_db();
    QString m_dateformat( QString, int );
    QString m_get_account_str( QString, QString );
    QString m_get_op_str( QString );
signals:

};

#endif // TOOLS_H
