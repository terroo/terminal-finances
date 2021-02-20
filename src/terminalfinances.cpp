#include "terminalfinances.h"
#include "ui_terminalfinances.h"
#include <QTextEdit>

TerminalFinances::TerminalFinances(QWidget *parent) : QMainWindow(parent), ui(new Ui::TerminalFinances)
{
    ui->setupUi(this);
    m_set_checked_lang();
    m_start_db();
    m_set_accounts();
    m_set_month_year();
    m_show_data();
    m_set_combos();
}

TerminalFinances::~TerminalFinances()
{
    delete ui;
}

void TerminalFinances::m_show_data()
{
    Model m;
    Tools t;
    Views v;
    m.m_query.prepare(m.m_read_show_data());
    int count = 0, w = 70;
    if (m.m_query.exec())
    {
        ui->selData->setColumnCount(8);
        while (m.m_query.next())
        {
            ui->selData->insertRow(count);
            for (int c = 0; c <= 8; c++)
            {
                if (c == 1)
                {
                    ui->selData->setItem(count, c, new QTableWidgetItem(t.m_currency(m.m_query.value(c).toString())));
                }
                else if (c == 2)
                {
                    ui->selData->setItem(count, c, new QTableWidgetItem(t.m_get_account_str(m.m_query.value(c).toString(), m.m_query.value(4).toString())));
                }
                else if (c == 4)
                {
                    ui->selData->setItem(count, c, new QTableWidgetItem(t.m_get_op_str(m.m_query.value(c).toString())));
                }
                else if (c > 5)
                {
                    ui->selData->setItem(count, c, new QTableWidgetItem(t.m_dateformat(m.m_query.value(c).toString(), 0)));
                }
                else
                {
                    ui->selData->setItem(count, c, new QTableWidgetItem(m.m_query.value(c).toString()));
                }
            }
            ui->selData->setRowHeight(count, 30);
            count++;
        }
        for (int i = 0; i <= 7; ++i)
        {
            if (i == 1)
            {
                w = 105;
            }
            if (i == 2)
            {
                w = 160;
            }
            if (i == 3)
            {
                w = 780;
            }
            if (i == 4 || i == 5)
            {
                w = 118;
            }
            if (i == 6 || i == 7)
            {
                w = 200;
            }
            ui->selData->setColumnWidth(i, w);
        }
        ui->selData->setHorizontalHeaderLabels(m.m_set_headers);
        m_set_data_ui();
        while (count < ui->selData->rowCount())
        {
            ui->selData->removeRow(count);
        }
    }
}

void TerminalFinances::m_set_lang(QString language)
{
    Initial z;
    Views v;
    z.m_read_file();
    z.m_lang = language;
    z.m_file_create();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, v.m_msg[0], v.m_msg[1], QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        close();
    }
    ui->statusbar->showMessage(v.m_msg[2]);
}

void TerminalFinances::m_set_checked_lang()
{
    Initial z;
    z.m_check_file();
    if (z.m_lang == "pt")
    {
        ui->actionPortugu_s->setChecked(true);
    }
    else if (z.m_lang == "es")
    {
        ui->actionEspa_ol->setChecked(true);
    }
    else
    {
        ui->actionIngl_s->setChecked(true);
    }

    if (z.m_theme == "dark")
    {
        this->setStyleSheet("background-color:#383c4a;color:#d4dce3;font-size:15px;");
        ui->actionDark->setChecked(true);
        ui->actionLight->setChecked(false);
    }
    else
    {
        this->setStyleSheet("font-size:15px;");
        ui->actionDark->setChecked(false);
        ui->actionLight->setChecked(true);
    }

    m_currency = z.m_currency;
}

void TerminalFinances::m_set_combos()
{
    Tools t;
    Views v;
    QStringList months = t.m_all_months();
    ui->combo_rel_month->addItem(v.m_msg[3]);
    for (int i = 0; i < months.size(); ++i)
    {
        ui->combo_rel_month->addItem(months[i]);
    }

    Model m;
    m.m_query.prepare(m.m_select_distinct_year());
    m.m_query.prepare(m.m_sql);
    ui->combo_rel_year->addItem(v.m_msg[3]);
    if (m.m_query.exec())
    {
        while (m.m_query.next())
        {
            ui->combo_rel_year->addItem(m.m_query.value(0).toString());
        }
    }

    ui->balance_status->setStyleSheet("color:#57B4C0;");

    ui->tabWidget->setCurrentIndex(0);
    connect(ui->field_search, SIGNAL(returnPressed()), ui->btn_search, SIGNAL(clicked()));
    //connect(ui->btn_c, SIGNAL(returnPressed()),ui->desc_c,SIGNAL(clicked()));
}

void TerminalFinances::m_set_data_ui()
{
    ui->selData->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->selData->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->selData->verticalHeader()->setVisible(false);
    ui->selData->verticalHeader()->setMinimumWidth(30);
    ui->selData->setStyleSheet("QTableView {selection-background-color: #57B4C0;}");
}

void TerminalFinances::m_set_month_year()
{
    Tools t;
    ui->current_month_year_c->setText(t.m_get_month());
    ui->current_month_year_d->setText(t.m_get_month());
}

void TerminalFinances::m_start_db()
{
    Start s;
    Views v;
    QStringList files;
    files << m_user_filedb << m_userdir << m_absolute_dir_filedb;
    s.m_run(files);
    m_db.setDatabaseName(m_user_filedb);
    !m_db.open() ? ui->statusbar->showMessage(tr("Falha ao conectar ao banco.")) : ui->statusbar->showMessage(v.m_msg[4]);
    QTimer::singleShot(3000, [&]() { ui->statusbar->clearMessage(); });
}

void TerminalFinances::m_set_accounts()
{
    AccountsList a;
    QStringList accounts_c = a.m_accounts(0);
    QStringList accounts_d = a.m_accounts(1);
    for (int i = 0; i < accounts_c.size(); ++i)
    {
        ui->account_type_c->addItem(accounts_c[i]);
    }
    for (int i = 0; i < accounts_d.size(); ++i)
    {
        ui->account_type_d->addItem(accounts_d[i]);
    }
}

void TerminalFinances::on_btn_c_clicked()
{
    Tools t;
    Views v;
    Model m;
    QStringList fields;

    fields << "0" << ui->desc_c->text() << QString::number(ui->account_type_c->currentIndex()) << t.m_rm_semidot(ui->value_c->text());

    if (!t.m_fields_validate(fields))
    {
        QMessageBox::warning(this, v.m_msg[6], v.m_msg[7]);
        return;
    }

    if (m.m_insert(fields))
    {
        ui->info_c->clear();
        ui->desc_c->clear();
        ui->value_c->setValue(0.00);
        ui->statusbar->showMessage(v.m_msg[8]);
        ui->selData->clear();
        m_show_data();
        QTimer::singleShot(3000, [&]() { ui->statusbar->clearMessage(); });
    }
    else
    {
        QMessageBox::critical(this, v.m_msg[9], v.m_msg[10]);
    }
}

void TerminalFinances::on_selData_cellDoubleClicked(int row, int column)
{
    column = 0;
    ui->selData->setStyleSheet("QTableView {selection-background-color: #E06C75;}");
    QStringList fields = {ui->selData->item(row, column)->text(), ui->selData->item(row, 1)->text(), ui->selData->item(row, 3)->text()};
    UpdateFields u(fields);
    u.exec();
    ui->selData->clear();
    m_show_data();
}

void TerminalFinances::on_btn_d_clicked()
{
    Tools t;
    Views v;
    Model m;
    QStringList fields;
    fields << "1" << ui->desc_d->text() << QString::number(ui->account_type_d->currentIndex()) << t.m_rm_semidot(ui->value_d->text());
    if (!t.m_fields_validate(fields))
    {
        QMessageBox::warning(this, v.m_msg[6], v.m_msg[7]);
        return;
    }

    if (m.m_insert(fields))
    {
        ui->info_d->clear();
        ui->desc_d->clear();
        ui->value_d->setValue(0.00);
        ui->statusbar->showMessage(v.m_msg[12]);
        ui->selData->clear();
        m_show_data();
        QTimer::singleShot(3000, [&]() { ui->statusbar->clearMessage(); });
    }
    else
    {
        QMessageBox::critical(this, v.m_msg[9], v.m_msg[10]);
    }
}

void TerminalFinances::on_btn_send_mail_clicked()
{
    FileSave f;
    Views v;
    QString content = f.m_save_content();
    QProcess *process = new QProcess(this);
    QString sendmail = "xdg-email";
    QStringList arguments;
    arguments << "--utf8"
              << "--subject"
              << "Terminal Finances"
              << "--body" << content;
    process->start(sendmail, arguments);

    ui->statusbar->showMessage(v.m_msg[13]);
    QTimer::singleShot(3000, [&]() { ui->statusbar->clearMessage(); });
}

void TerminalFinances::on_btn_save_clicked()
{

    FileSave f;
    Views v;
    QFile file(f.m_filename);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, v.m_msg[14], v.m_msg[15]);
        return;
    }

    QTextStream enter_file(&file);
    QString text = enter_file.readAll();
    qDebug() << f.m_filename;
    QTextEdit parent;
    parent.setText(text);

    QPrinter printer;
    printer.setOutputFileName("terminalfinances.pdf");
    printer.setPrinterName("Terminal Finances");
    QPrintDialog diag_printer(&printer, this);
    if (diag_printer.exec() == QDialog::Rejected)
    {
        return;
    }

    parent.print(&printer);
    ui->statusbar->showMessage(v.m_msg[16]);
    QTimer::singleShot(3000, [&]() { ui->statusbar->clearMessage(); });
}

void TerminalFinances::on_btn_search_clicked()
{
    m_search_list();
}

void TerminalFinances::on_btn_generate_rel_clicked()
{

    Views v;
    Tools t;
    FileSave s;
    GenDoc g;
    Model m;
    m.m_read_show_data();
    g.m_set_t();

    QString combo_month = ui->combo_rel_month->currentText(),
            combo_month_index_str{},
            combo_year = ui->combo_rel_year->currentText(),
            result{}, sql, sql_c, sql_d, balance_color{}, balance_name{},
            balance_string, total_cred, total_deb;

    QStringList to_result, sqlist;

    float total{0}, total_c{0}, total_d{0}, balance;
    qint64 combo_month_index = ui->combo_rel_month->currentIndex();

    combo_month_index_str = (combo_month_index < 10 ? "0" + QString::number(combo_month_index) : QString::number(combo_month_index));
    QSqlQuery query, query_c, query_d;

    sqlist << combo_month << combo_year << combo_month_index_str;
    m.m_set_sql(sqlist);
    sql = m.m_sqlist[0], sql_c = m.m_sqlist[1], sql_d = m.m_sqlist[2];

    if (query.exec(sql))
    {
        while (query.next())
        {
            total += query.value(1).toFloat();
        }
    }

    if (query_c.exec(sql_c))
    {
        while (query_c.next())
        {
            total_c += query_c.value(0).toFloat();
        }
    }

    if (query_d.exec(sql_d))
    {
        while (query_d.next())
        {
            total_d += query_d.value(0).toFloat();
        }
    }

    balance = total_c - total_d;
    const QStringList gencolor = g.m_gen_color();

    if (balance > 0)
    {
        balance_color = gencolor[0];
        balance_name = gencolor[1];
        ui->balance_status->setText(gencolor[2]);
        ui->balance_status->setStyleSheet(gencolor[3]);
    }
    else if (balance == 0)
    {
        balance_color = gencolor[4];
        balance_name = gencolor[5];
        ui->balance_status->setText(gencolor[6]);
        ui->balance_status->setStyleSheet(gencolor[7]);
    }
    else
    {
        balance_color = gencolor[8];
        balance_name = gencolor[9];
        ui->balance_status->setText(gencolor[10]);
        ui->balance_status->setStyleSheet(gencolor[11]);
    }

    balance_string = QString::number(balance);
    total_cred = QString::number(total_c);
    total_deb = QString::number(total_d);

    to_result << combo_month << combo_year << total_cred << total_deb << balance_color << balance_string;

    if (total > 0)
    {
        result = g.m_gen_tags(to_result);
    }

    if (query.exec())
    {
        int count = 0, w = 70;
        while (query.next())
        {
            result += g.m_t[0] + g.m_t[1] + t.m_dateformat(query.value(7).toString(), 1) + g.m_t[2] +
                      g.m_t[1] + t.m_get_op_str(query.value(4).toString()) + g.m_t[2] +
                      g.m_t[1] + t.m_get_account_str(query.value(2).toString(), query.value(4).toString()) + g.m_t[2] +
                      g.m_t[1] + query.value(3).toString() + g.m_t[2] +
                      g.m_t[1] + m_currency.leftJustified(6, ' ') + t.m_currency(query.value(1).toString()) + g.m_t[2] +
                      g.m_t[1] + query.value(0).toString() + g.m_t[2] + g.m_t[3];

            ui->tableWidget->setColumnCount(8);

            ui->tableWidget->insertRow(count);
            for (int c = 0; c <= 8; c++)
            {
                if (c == 1)
                {
                    ui->tableWidget->setItem(count, c, new QTableWidgetItem(t.m_currency(query.value(c).toString())));
                }
                else if (c == 2)
                {
                    ui->tableWidget->setItem(count, c, new QTableWidgetItem(t.m_get_account_str(query.value(c).toString(), query.value(4).toString())));
                }
                else if (c == 4)
                {
                    ui->tableWidget->setItem(count, c, new QTableWidgetItem(t.m_get_op_str(query.value(c).toString())));
                }
                else if (c > 5)
                {
                    ui->tableWidget->setItem(count, c, new QTableWidgetItem(t.m_dateformat(query.value(c).toString(), 0)));
                }
                else
                {
                    ui->tableWidget->setItem(count, c, new QTableWidgetItem(query.value(c).toString()));
                }
            }
            ui->tableWidget->setRowHeight(count, 30);
            count++;
        }

        for (int i = 0; i <= 7; ++i)
        {
            if (i == 1)
            {
                w = 105;
            }
            if (i == 2)
            {
                w = 160;
            }
            if (i == 3)
            {
                w = 780;
            }
            if (i == 4 || i == 5)
            {
                w = 118;
            }
            if (i == 6 || i == 7)
            {
                w = 200;
            }
            ui->tableWidget->setColumnWidth(i, w);
        }
        ui->tableWidget->setHorizontalHeaderLabels(m.m_set_headers);
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget->verticalHeader()->setVisible(false);
        ui->tableWidget->verticalHeader()->setMinimumWidth(30);
        ui->tableWidget->setStyleSheet("QTableView {selection-background-color: #57B4C0;}");
        ui->label_rel_c->setText("<h1 style='text-align:center;'>" + m_currency.leftJustified(6, ' ') + t.m_currency(QString::number(total_c)) + "</h1>");
        ui->label_rel_d->setText("<h1 style='text-align:center;'>" + m_currency.leftJustified(6, ' ') + t.m_currency(QString::number(total_d)) + "</h1>");
        ui->label_rel_s->setText("<h1 style='text-align:center;'>" + m_currency.leftJustified(6, ' ') + t.m_currency(QString::number(balance)) + "</h1>");
        while (count < ui->tableWidget->rowCount())
        {
            ui->tableWidget->removeRow(count);
        }

        if (total > 0)
        {
            s.m_save_file(result);
        }
    }
    else
    {
        QMessageBox::critical(this, v.m_msg[17], v.m_msg[18]);
    }
}

void TerminalFinances::m_search_list()
{
    Views v;
    QString search = ui->field_search->text();
    if (search.isEmpty())
    {
        QMessageBox::warning(this, v.m_msg[19], v.m_msg[20]);
        return;
    }

    QSqlQuery query, query_t;

    query.prepare("SELECT * FROM terminalfinances WHERE tf_desc LIKE '%" + search + "%' OR tf_account LIKE '%" + search + "%' OR tf_value LIKE '%" + search + "%'");
    query_t.prepare("SELECT SUM(tf_value) FROM terminalfinances WHERE tf_desc LIKE '%" + search + "%' OR tf_account LIKE '%" + search + "%' OR tf_value LIKE '%" + search + "%'");
    int count = 0;

    Tools t;
    if (query.exec())
    {

        float total_search = {0};
        if (query_t.exec())
        {
            while (query_t.next())
            {
                total_search = query_t.value(0).toFloat();
            }

            ui->label_total_search->setText("<h2>" + t.m_currency(QString::number(total_search)) + "</h2>");
        }

        ui->search_tab->setColumnCount(8);
        while (query.next())
        {

            ui->search_tab->insertRow(count);

            for (int c = 0; c <= 8; c++)
            {
                if (c == 1)
                {
                    ui->search_tab->setItem(count, c, new QTableWidgetItem(t.m_currency(query.value(c).toString())));
                }
                else if (c == 2)
                {
                    ui->search_tab->setItem(count, c, new QTableWidgetItem(t.m_get_account_str(query.value(c).toString(), query.value(4).toString())));
                }
                else if (c == 4)
                {
                    ui->search_tab->setItem(count, c, new QTableWidgetItem(t.m_get_op_str(query.value(c).toString())));
                }
                else if (c > 5)
                {
                    ui->search_tab->setItem(count, c, new QTableWidgetItem(t.m_dateformat(query.value(c).toString(), 0)));
                }
                else
                {
                    ui->search_tab->setItem(count, c, new QTableWidgetItem(query.value(c).toString()));
                }
            }

            ui->search_tab->setRowHeight(count, 30);

            count++;
        }

        if (count == 0)
        {
            ui->label_total_search->setText("<h2>0,00</h2>");
            for (int r = 7; r > -1; r--)
            {
                ui->search_tab->removeColumn(r);
            }
            for (int m = ui->search_tab->rowCount(); m > -1; --m)
            {
                ui->search_tab->removeRow(m);
            }
            QMessageBox::information(this, v.m_msg[21], v.m_msg[22] + " '" + search + "' .", v.m_msg[23]);
            ui->field_search->clear();
            ui->field_search->setFocus();
            return;
        }

        ui->field_search->clear();

        ui->search_tab->setColumnWidth(0, 100);
        ui->search_tab->setColumnWidth(1, 100);
        ui->search_tab->setColumnWidth(2, 200);
        ui->search_tab->setColumnWidth(3, 700);
        ui->search_tab->setColumnWidth(4, 100);
        ui->search_tab->setColumnWidth(5, 100);
        ui->search_tab->setColumnWidth(6, 200);
        ui->search_tab->setColumnWidth(7, 200);

        QStringList headers;

        for (int k = 24; k <= 31; k++)
        {
            headers << v.m_msg[k];
        }

        ui->search_tab->setHorizontalHeaderLabels(headers);

        ui->search_tab->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->search_tab->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->search_tab->verticalHeader()->setMinimumWidth(30);
        ui->search_tab->setStyleSheet("QTableView {selection-background-color: #57B4C0;}");

        while (count < ui->search_tab->rowCount())
        {
            ui->search_tab->removeRow(count);
        }
    }
    else
    {
        qDebug() << v.m_msg[32];
    }
}

void TerminalFinances::on_actionTerminal_Finances_triggered()
{
    Views v;
    QMessageBox::about(this, v.m_msg[33], v.m_msg[34]);
}

void TerminalFinances::on_actionSair_triggered()
{
    close();
}

void TerminalFinances::on_actionLan_amentos_triggered()
{
    ui->tabWidget->setCurrentIndex(1);
}

void TerminalFinances::on_actionRelat_rios_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
}

void TerminalFinances::on_actionPesquisar_triggered()
{
    ui->tabWidget->setCurrentIndex(3);
    ui->field_search->setFocus();
}

void TerminalFinances::on_actionPortugu_s_triggered()
{
    ui->actionEspa_ol->setChecked(false);
    ui->actionIngl_s->setChecked(false);
    m_set_lang("pt");
}

void TerminalFinances::on_actionIngl_s_triggered()
{
    Initial z;
    ui->actionEspa_ol->setChecked(false);
    ui->actionPortugu_s->setChecked(false);
    m_set_lang("en");
}

void TerminalFinances::on_actionEspa_ol_triggered()
{
    ui->actionPortugu_s->setChecked(false);
    ui->actionIngl_s->setChecked(false);
    m_set_lang("es");
}

void TerminalFinances::on_actionDark_triggered()
{
    Initial z;
    z.m_read_file();
    z.m_theme = "dark";
    z.m_file_create();
    this->setStyleSheet("background-color:#383c4a;color:#d4dce3;font-size:15px;");
    ui->actionDark->setChecked(true);
    ui->actionLight->setChecked(false);
}

void TerminalFinances::on_actionLight_triggered()
{
    Initial z;
    z.m_read_file();
    z.m_theme = "light";
    z.m_file_create();
    this->setStyleSheet("");
    this->setStyleSheet("font-size:15px;");
    ui->actionDark->setChecked(false);
    ui->actionLight->setChecked(true);
}

void TerminalFinances::on_actionExportar_Banco_de_Dados_triggered()
{
    Tools t;
    Views v;
    QString filename = QFileDialog::getSaveFileName(this, v.m_msg[35], QDir::homePath() + t.m_return_filename_db(), "*.db");
    QString user_filedb = m_user_filedb;
    if (QFile::copy(user_filedb, filename))
    {
        ui->statusbar->showMessage(v.m_msg[36]);
        QTimer::singleShot(4000, [&]() { ui->statusbar->clearMessage(); });
    }
}
