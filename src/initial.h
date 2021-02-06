#ifndef INITIAL_H
#define INITIAL_H

#include <QWidget>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QProcess>
#include <QDebug>

class Initial : public QWidget{
    Q_OBJECT
public:
    explicit Initial(QWidget *parent = nullptr);
    const QString m_home = qgetenv("HOME"),
                  m_file_ini = "config.ini",
                  m_dir = m_home + "/.config/terminalfinances",
                  m_path_file = m_dir + "/" + m_file_ini,
                  m_en = "/etc/xdg/terminalfinances/TerminalFinances_en_US.qm",
                  m_es = "/etc/xdg/terminalfinances/TerminalFinances_en_US.qm";

    QString m_content, m_lang = "pt", m_theme = "light",
            m_get_lang = qgetenv("LANG"), m_currency = "R$";

    bool m_check_file();
    void m_file_create();
    void m_set_content();
    void m_read_file();
signals:

};

#endif // INITIAL_H
