#ifndef MODEL_H
#define MODEL_H

#include <QWidget>
#include <QtSql>
#include <QDebug>
#include "views.h"

class Model : public QWidget{
    Q_OBJECT
public:
    explicit Model(QWidget *parent = nullptr);
    QSqlQuery m_query;
    QString m_sql;
    QString m_table = "terminalfinances";
    const QString m_user = qgetenv( "USER" );
    bool m_insert( QStringList );
    bool m_delete( QString );
    bool m_update( QStringList );
    QString m_read_show_data();
    QString m_select_distinct_year( );
    QStringList m_set_headers;
    void m_set_sql( QStringList );
    QStringList m_sqlist;

signals:

};

#endif // MODEL_H
