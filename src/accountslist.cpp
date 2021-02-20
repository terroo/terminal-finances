#include "accountslist.h"

AccountsList::AccountsList(QWidget *parent) : QWidget(parent) {}

QStringList AccountsList::m_accounts(int z)
{
    Views v;
    QStringList adds;
    adds << v.m_msg[37] << v.m_msg[38] << v.m_msg[39] << v.m_msg[40];
    QStringList dels;
    dels << v.m_msg[41] << v.m_msg[42] << v.m_msg[43] << v.m_msg[44] << v.m_msg[45] << v.m_msg[46];
    return (z == 0 ? adds : dels);
}
