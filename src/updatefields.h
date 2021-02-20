#ifndef UPDATEFIELDS_H
#define UPDATEFIELDS_H

#include <QDialog>
#include <QMessageBox>
#include "model.h"
#include "tools.h"
#include "views.h"

namespace Ui
{
    class UpdateFields;
}

class UpdateFields : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateFields(QStringList fields = {""}, QWidget *parent = nullptr);
    ~UpdateFields();
    QStringList m_update_fields;
    bool m_item_del = false;

private slots:
    void on_button_edit_balance_clicked();

    void on_pushButton_clicked();

private:
    Ui::UpdateFields *ui;
};

#endif // UPDATEFIELDS_H
