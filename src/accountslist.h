#ifndef ACCOUNTSLIST_H
#define ACCOUNTSLIST_H

#include <QWidget>
#include "views.h"

class AccountsList : public QWidget
{
    Q_OBJECT
public:
    explicit AccountsList(QWidget *parent = nullptr);
    QStringList m_accounts(int);
signals:
};

#endif // ACCOUNTSLIST_H
