#include "gendoc.h"

GenDoc::GenDoc(QWidget *parent) : QWidget(parent) {}

const QString GenDoc::m_gen_tags(QStringList result)
{
    Tools t;
    Initial z;
    Views v;
    QString combo_month = result[0], combo_year = result[1], total_cred = result[2], total_deb = result[3], balance_color = result[4], balance_string = result[5];
    if (combo_month == v.m_msg[3] && combo_year == v.m_msg[3])
    {
        combo_month = "";
        combo_year = "";
    };
    QString result_r = "<style>"
                       "div {text-align:center!important}"
                       ".table{width:100%;margin-bottom:1rem;color:#212529;background:#fff;}"
                       ".table td,.table th{padding:2px;vertical-align:top;border-top:1px solid #a9aeb4}"
                       ".table thead th{vertical-align:bottom;border-bottom:2px solid #dee2e6}"
                       ".table tbody+tbody{border-top:2px solid #dee2e6}"
                       ".table-bordered{border:1px solid #dee2e6}"
                       ".table-bordered td,.table-bordered th{border:1px solid #a9aeb4}"
                       ".table-bordered thead td,.table-bordered thead th{border-bottom-width:2px}"
                       ".container,.container-fluid{width:100%;padding-right:3px;padding-left:3px;margin-right:auto;margin-left:auto}"
                       ".text-center{text-align:center!important}"
                       ".success {color:#1e7e34;}.danger{color:#a71d2a}"
                       "h2 {font-weight:500;line-height:1.2}"
                       ".container {max-width:1000px;}"
                       "</style>"
                       "<div class='container'>"
                       "<table class='table table-bordered'>"
                       "<thead>"
                       "<tr><th colspan='6'><h2>" +
                       combo_month.toUpper() + " " + combo_year.toUpper() + "</h2></th></tr>"
                                                                            "<tr><th colspan='2'>" +
                       v.m_msg[51] + z.m_currency.leftJustified(6, ' ') + " <strong class='success'>" + t.m_currency(total_cred) + "</strong> </th>"
                                                                                                                                   "<th colspan='1'>" +
                       v.m_msg[52] + z.m_currency.leftJustified(6, ' ') + " <strong class='danger'>" + t.m_currency(total_deb) + "</strong> </th> "
                                                                                                                                 "<th colspan='3' class='text-center'>" +
                       v.m_msg[53] + z.m_currency.leftJustified(6, ' ') + " <strong style='color: " + balance_color + "'>" + t.m_currency(balance_string) + "</strong></th>"
                                                                                                                                                            "<tr>"
                                                                                                                                                            "<th>" +
                       v.m_msg[54] + "</th>"
                                     "<th>" +
                       v.m_msg[28] + "</th>"
                                     "<th>" +
                       v.m_msg[55] + "</th>"
                                     "<th>" +
                       v.m_msg[27] + "</th>"
                                     "<th>" +
                       v.m_msg[25] + "</th>"
                                     "<th>" +
                       v.m_msg[24] + "</th>"
                                     "</tr>"
                                     "</thead>"
                                     "<tbody>";
    return result_r;
}

void GenDoc::m_set_t()
{
    m_t << "<tr>"
        << "<td>"
        << "</td>"
        << "</tr>"
        << "</tbody></table></div>"
        << "</div>"
        << "<div style='max-width:1200px;margin:auto;'>"
        << "background: #fff;color:#000;border:1px solid #2D3037;text-align:center;";
}

const QStringList GenDoc::m_gen_color()
{
    Views v;
    const QStringList r = {
        "#1e7e34", v.m_msg[56], v.m_msg[57],
        "color:#00b5ad;text-align:center;", "#57B4C0",
        v.m_msg[58], v.m_msg[59],
        "color: #2D3037;text-align:center;", "#a71d2a",
        v.m_msg[60], v.m_msg[61],
        "color: #ef325a;text-align:center;"};
    return r;
}
