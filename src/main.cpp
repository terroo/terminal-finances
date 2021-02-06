#include "terminalfinances.h"
#include <QApplication>
#include "initial.h"
#include <QTranslator>
#include <QMessageBox>

int main(int argc, char ** argv ){
    QApplication a(argc, argv);
    Initial z;
    QTranslator t;
    z.m_check_file();

    if( z.m_lang == "en" ){
        t.load( z.m_en );
    }else if( z.m_lang == "es" ){
        t.load( z.m_es );
    }

    if( z.m_lang != "pt" ){
        a.installTranslator( &t );
    }

    TerminalFinances w;
    w.show();
    return a.exec();
}
