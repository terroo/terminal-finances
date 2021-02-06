#include "start.h"

Start::Start(QWidget *parent) : QWidget(parent){}

void Start::m_run( QStringList files ){
    Views v;
    QString user_filedb = files[0], userdir = files[1], absolute_dir_filedb = files[2];
    QFileInfo localdb( user_filedb );
    QFile file( user_filedb );
    QDir localdir( userdir );

    if ( !localdir.exists() ){
        if( QDir().mkpath( userdir ) ){
            if( QFile::copy( absolute_dir_filedb , user_filedb ) ){
                if( ! file.setPermissions( QFile::ReadOwner|QFile::WriteOwner )  ){
                    qDebug() << v.m_msg[62];
                }
            }
        }
    }

    if( ! localdb.exists() ){
        if( QFile::copy( absolute_dir_filedb , user_filedb ) ){
            if( ! file.setPermissions( QFile::ReadOwner|QFile::WriteOwner )  ){
                qDebug() << v.m_msg[62];
            }
        }
     }
}
