#ifndef GENDOC_H
#define GENDOC_H

#include <QWidget>
#include "tools.h"
#include "initial.h"
#include "views.h"

class GenDoc : public QWidget
{
    Q_OBJECT
public:
    explicit GenDoc(QWidget *parent = nullptr);
    const QString m_gen_tags(QStringList);
    const QStringList m_gen_color();
    QStringList m_t;
    void m_set_t();
signals:
};

#endif // GENDOC_H
