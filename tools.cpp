#include "tools.h"

Tools::Tools(QWidget *parent) : QWidget(parent){
    m_get_datetime();
}

QString Tools::m_currency( QString value ){
    double valor = value.toDouble();
    auto lang = QLocale("pt_BR");
    return lang.toString(valor, 'f', 2) ;
}

bool Tools::m_fields_validate( QStringList fields ){
    for( int i = 0; i < fields.size(); ++i ){
        if( fields[i].isEmpty() || fields[i] == "0.00" ){
            return false;
        }
    }
    return true;
}

void Tools::m_get_datetime(){
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local(UTC.toLocalTime());
    int int_day = QDate::currentDate().day(),
        int_month = QDate::currentDate().month(),
        int_year  = QDate::currentDate().year(),
        int_hour = local.time().hour(),
        int_min = local.time().minute(),
        int_sec = local.time().second();
    int c_datetime[6] { int_day, int_month, int_year, int_hour, int_min, int_sec };
    for( int i = 0; i < 6; ++i){
        m_datetime[i] = c_datetime[i];
    }

}

QString Tools::m_get_month(){
    QStringList months = m_all_months();
    QString str = months[ m_datetime[1] - 1 ] + "/" + QString::number( m_datetime[2] );
    return str;
}

QString Tools::m_rm_semidot(QString str ){
    return str.replace(",", ".");
}

QStringList Tools::m_all_months(){
    Views v;
    QStringList r;
    for( int i = 63; i <= 74; ++i ){
        r << v.m_msg[i];
    }
    return r;
}

QString Tools::m_return_filename_db(){
    QString str_d, str_m;
     str_d = ( m_datetime[0] < 10 ? "0" + QString::number( m_datetime[0] ) : QString::number( m_datetime[0] ) );
     str_m = ( m_datetime[1] < 10 ? "0" + QString::number( m_datetime[1] ) : QString::number( m_datetime[1] ) );
    return ("/terminalfinances-" + QString::number( m_datetime[2] ) +  "-" + str_m + "-" + str_d + ".db" );
}

QString Tools::m_dateformat(QString str, int n ){
    QString fmt = "yyyy-MM-dd hh:mm:ss";
    QDateTime dt = QDateTime::fromString(str, fmt);
    if( n == 0 ){
        str = dt.toString(" dd/MM/yyyy hh:mm:ss");
    }else{
        str = dt.toString(" dd/MM/yyyy");
    }

    return str;
}

QString Tools::m_get_account_str( QString account, QString op ){
    Views v;
    QString account_name;
    int n = 0;
    for (int j = 37; j <= 46; ++j) {
        n = j - 37;

       if( account == QString::number( n ) ){
           if( op == "1" ){
               j += 4;
           }
           account_name = v.m_msg[j];
       }
    }
    return account_name;
}

QString Tools::m_get_op_str( QString op ){
    Views v;
    return ( op == "0" ? v.m_msg[5] : v.m_msg[11] );
}
