#include "updatefields.h"
#include "ui_updatefields.h"

UpdateFields::UpdateFields(QStringList fields, QWidget *parent) : QDialog(parent), ui(new Ui::UpdateFields)
{
    ui->setupUi(this);
    fields[1].remove(".");
    fields[1].replace(",", ".");
    ui->fiel_desc_edit_balance->setText(fields[2]);
    ui->value_edit_balance->setValue(fields[1].toDouble());
    ui->label_id->setText(fields[0]);
    m_update_fields = fields;
}

UpdateFields::~UpdateFields()
{
    delete ui;
}

void UpdateFields::on_button_edit_balance_clicked()
{
    Views v;
    Tools t;
    QStringList fields = {ui->label_id->text(), t.m_rm_semidot(ui->value_edit_balance->text()), ui->fiel_desc_edit_balance->text()};
    if (!t.m_fields_validate(fields))
    {
        QMessageBox::warning(this, v.m_msg[6], v.m_msg[7]);
        return;
    }

    Model m;
    if (m.m_update(fields))
    {
        this->close();
    }
    else
    {
        QMessageBox::critical(this, v.m_msg[14], v.m_msg[75]);
        this->close();
    }
}

void UpdateFields::on_pushButton_clicked()
{
    Views v;
    Model m;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, v.m_msg[6], v.m_msg[76] + ui->label_id->text() + "?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        if (m.m_delete(ui->label_id->text()))
        {
            this->close();
        }
        else
        {
            QMessageBox::critical(this, v.m_msg[14], v.m_msg[75]);
            this->close();
        }
    }
}
