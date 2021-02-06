#include "filesave.h"

FileSave::FileSave(QWidget *parent) : QWidget(parent){}

bool FileSave::m_file_exists(QString path){
    QFileInfo check_file(path);

    return (check_file.exists() && check_file.isFile());
}

void FileSave::m_save_file( QString content ){
    Views v;
    QFile file( m_filename );
    if ( m_file_exists( m_filename ) ){
        if( !file.remove() ){
            qDebug() << v.m_msg[47];
        }
    }
    if( ! file.open(QFile::ReadWrite|QFile::Text)){
        QMessageBox::critical( this, v.m_msg[48], v.m_msg[49] );
        return;
    }
    QTextStream out_file( &file );
    out_file << content << '\n';
    file.flush();
    file.close();
}

QString FileSave::m_save_content(){
    Views v;
    QString str {};
    QFile file( m_filename );
    if( ! file.open(QFile::ReadOnly|QFile::Text)){
        qDebug() << v.m_msg[50];
        str = v.m_msg[14];
    }else{
        QTextStream out_file( &file );
        str = out_file.read( 9999999999 );
        file.flush();
        file.close();
    }
    return str;
}

