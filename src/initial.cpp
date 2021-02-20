#include "initial.h"

Initial::Initial(QWidget *parent) : QWidget(parent) {}

bool Initial::m_check_file()
{
    QFileInfo local_file(m_path_file);
    if (local_file.exists())
    {
        m_read_file();
    }
    else
    {
        QDir().mkpath(m_dir);
        m_file_create();
    }
    return true;
}

void Initial::m_file_create()
{
    QFile file(m_path_file);
    QTextStream out_file(&file);
    m_set_content();
    file.open(QFile::ReadWrite | QFile::Text);
    out_file << m_content << '\n';
    file.flush();
    file.close();
}

void Initial::m_set_content()
{
    QString content = "# --------------------------------\n"
                      "# Terminal Finances 1.0.0\n"
                      "# Developed by Marcos Oliveira\n"
                      "# <https://terminalroot.com.br/>\n"
                      "# --------------------------------\n"
                      "lang = " +
                      m_lang + "\n"
                               "theme = " +
                      m_theme + "\n"
                                "currency = " +
                      m_currency;
    m_content = content;
}

void Initial::m_read_file()
{
    QFile inputFile(m_path_file);
    if (inputFile.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream content(&inputFile);
        while (!content.atEnd())
        {

            QString line = content.readLine();
            line.replace(" ", "");
            //line.remove('#');
            QStringList fullline = line.split('=');

            if (fullline.first() == "lang")
            {
                m_lang = fullline.last();
            }

            if (fullline.first() == "theme")
            {
                m_theme = fullline.last();
            }

            if (fullline.first() == "currency")
            {
                m_currency = fullline.last();
            }
        }
    }
    inputFile.close();
}
