#ifndef TERMINALFINANCES_H
#define TERMINALFINANCES_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QPrintDialog>
#include <QPrinter>
#include <QInputDialog>
#include <QFile>
#include <QByteArray>
#include <QFileDialog>
#include "start.h"
#include "tools.h"
#include "accountslist.h"
#include "model.h"
#include "updatefields.h"
#include "filesave.h"
#include "initial.h"
#include "gendoc.h"
#include "views.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TerminalFinances; }
QT_END_NAMESPACE

class TerminalFinances : public QMainWindow{
    Q_OBJECT

public:
    TerminalFinances(QWidget *parent = nullptr);
    ~TerminalFinances();

    const QString m_home_user = qgetenv("HOME");
    const QString m_filedb = "terminalfinances.db";
    const QString m_absolute_dir_filedb = "/etc/xdg/terminalfinances/terminalfinances.db"; // from
    const QString m_userdir = m_home_user + "/.config/terminalfinances";
    const QString m_user_filedb = m_home_user + "/.config/terminalfinances/" + m_filedb; // for

    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
    QString m_currency;

    void m_set_combos();
    void m_show_data();
    void m_set_accounts();
    void m_start_db();
    void m_set_month_year();
    void m_set_data_ui();
    void m_search_list();
    void m_set_checked_lang();
    void m_set_lang( QString );

private slots:
    void on_btn_c_clicked();

    void on_selData_cellDoubleClicked(int row, int column);

    void on_btn_d_clicked();

    void on_btn_generate_rel_clicked();

    void on_btn_send_mail_clicked();

    void on_btn_save_clicked();

    void on_btn_search_clicked();

    void on_actionTerminal_Finances_triggered();

    void on_actionSair_triggered();

    void on_actionLan_amentos_triggered();

    void on_actionRelat_rios_triggered();

    void on_actionPesquisar_triggered();

    void on_actionPortugu_s_triggered();

    void on_actionIngl_s_triggered();

    void on_actionEspa_ol_triggered();

    void on_actionDark_triggered();

    void on_actionLight_triggered();

    void on_actionExportar_Banco_de_Dados_triggered();

private:
    Ui::TerminalFinances *ui;
};
#endif // TERMINALFINANCES_H
