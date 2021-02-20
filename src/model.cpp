#include "model.h"

Model::Model(QWidget *parent) : QWidget(parent) {}

bool Model::m_insert(QStringList insert)
{
    QString values, fields = "tf_value, tf_account, tf_desc, tf_op, tf_user";
    for (int i = 3; i >= 0; --i)
    {
        values += "'" + insert[i] + "', ";
    }
    values += "'" + m_user + "'";
    m_sql = "INSERT INTO " + m_table + "( " + fields + " ) VALUES ( " + values + " )";
    return m_query.exec(m_sql);
}

QString Model::m_read_show_data()
{
    Views v;

    for (int k = 24; k <= 31; k++)
    {
        m_set_headers << v.m_msg[k];
    }

    m_sql = "SELECT * FROM " + m_table + " ORDER BY id DESC LIMIT 20";
    return m_sql;
}

bool Model::m_update(QStringList insert)
{
    m_sql = "UPDATE " + m_table + " SET tf_value='" + insert[1] + "', tf_desc='" + insert[2] + "', tf_date_update=CURRENT_TIMESTAMP WHERE id=" + insert[0];
    return m_query.exec(m_sql);
}

bool Model::m_delete(QString id)
{
    m_sql = "DELETE FROM " + m_table + " WHERE id=" + id;
    return m_query.exec(m_sql);
}

QString Model::m_select_distinct_year()
{
    m_sql = "SELECT DISTINCT SUBSTR(tf_date_update,1,4) FROM " + m_table + " ORDER BY SUBSTR(tf_date_update,1,4) DESC";
    return m_sql;
}

void Model::m_set_sql(QStringList sqlist)
{
    Views v;
    // combo_month, combo_year, combo_month_index_str
    // sqlist[0], sqlist[1], sqlist[2]
    QString sql, sql_c, sql_d;
    if (sqlist[0] == v.m_msg[3] && sqlist[1] == v.m_msg[3])
    {
        sql = "SELECT * FROM terminalfinances";
        sql_c = "SELECT tf_value FROM terminalfinances WHERE tf_op == '0'";
        sql_d = "SELECT tf_value FROM terminalfinances WHERE tf_op == '1'";
    }

    if (sqlist[0] == v.m_msg[3] && sqlist[1] != v.m_msg[3])
    {
        sql = "SELECT * FROM terminalfinances WHERE SUBSTR(tf_date_update,1,4) == '" + sqlist[1] + "'";
        sql_c = "SELECT tf_value FROM terminalfinances WHERE SUBSTR(tf_date_update,1,4) == '" + sqlist[1] + "' AND tf_op == '0'";
        sql_d = "SELECT tf_value FROM terminalfinances WHERE SUBSTR(tf_date_update,1,4) == '" + sqlist[1] + "' AND tf_op == '1'";
    }

    if (sqlist[0] != v.m_msg[3] && sqlist[1] == v.m_msg[3])
    {
        sql = "SELECT * FROM terminalfinances WHERE SUBSTR(tf_date_update,6,2) == '" + sqlist[2] + "'";
        sql_c = "SELECT tf_value FROM terminalfinances WHERE SUBSTR(tf_date_update,6,2) == '" + sqlist[2] + "' AND tf_op == '0'";
        sql_d = "SELECT tf_value FROM terminalfinances WHERE SUBSTR(tf_date_update,6,2) == '" + sqlist[2] + "' AND tf_op == '1'";
    }

    if (sqlist[0] != v.m_msg[3] && sqlist[1] != v.m_msg[3])
    {
        sql = "SELECT * FROM terminalfinances WHERE SUBSTR(tf_date_update,1,4) = '" + sqlist[1] + "' AND SUBSTR(tf_date_update,6,2) == '" + sqlist[2] + "'";
        sql_c = "SELECT tf_value FROM terminalfinances WHERE SUBSTR(tf_date_update,1,4) = '" + sqlist[1] + "' AND SUBSTR(tf_date_update,6,2) == '" + sqlist[2] + "' AND tf_op == '0'";
        sql_d = "SELECT tf_value FROM terminalfinances WHERE SUBSTR(tf_date_update,1,4) = '" + sqlist[1] + "' AND SUBSTR(tf_date_update,6,2) == '" + sqlist[2] + "' AND tf_op == '1'";
    }

    m_sqlist << sql << sql_c << sql_d;
}
