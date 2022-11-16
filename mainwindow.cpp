#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"qrcode.h"
#include"fournisseur.h"
#include"avie.h"
#include<QMessageBox>
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QSqlQueryModel>
#include<QIntValidator>
#include<QFileDialog>
#include <QPainter>
#include <QtPrintSupport/QAbstractPrintDialog>
#include<QtSvg/QSvgRenderer>
#include<QDirModel>
#include"qrcode.h"
#include<fstream>
#include<QFileDialog>
#include<QPrinter>
#include<QTextDocument>

using qrcodegen::QrCode;
using qrcodegen::QrSegment;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        ui->tableavie->setModel(Av.afficheravie());
        ui->le_id_f->setValidator(new QIntValidator(0,999999999,this));
             ui->le_num->setValidator(new QIntValidator(0,999999999,this));
            ui->tablefournisseur->setModel(Fi.afficher());
            ui->le_id_f_2->setValidator(new QIntValidator(0,999999999,this));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouteravis_clicked()
{
    ui->tableavie->setModel((Av.afficheravie()));
        int id_fournisseur=ui->le_id_f_2->text().toInt();

        QString rapid=ui->cb_rapid->currentText();
        QString service=ui->cb_service->currentText();;
        QString commentaire=ui->cb_commentaire->currentText();;


          Av.setid_fournisseur(ui->le_id_f_2->text().toInt());
    avie Av (id_fournisseur,rapid,service,commentaire);
    bool test=Av.ajouteravie();
    if (test)
    {

        ui->tableavie->setModel(Av.afficheravie()); //refresh
        QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("Ajout avec succes\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
     ui->tableavie->setModel(Av.afficheravie());
    }




}

void MainWindow::on_ajouter_clicked()
{
    ui->tablefournisseur->setModel((Fi.afficher()));

        int id_f=ui->le_id_f->text().toInt();
        QString societe=ui->le_societe->text();
        int num_tel=ui->le_num->text().toInt();
        QString nom_f=ui->le_nom->text();
         QString prenom_f=ui->le_prenom->text();
          QString adresse=ui->le_adresse->text();
          Fi.setid_f(ui->le_id_f->text().toInt());
    fournisseur Fi (id_f ,societe,num_tel ,nom_f, prenom_f, adresse);
    bool test=Fi.ajouter();
    if (test)
    {

        ui->tablefournisseur->setModel(Fi.afficher()); //refresh
        QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("Ajout avec succes\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
     ui->tablefournisseur->setModel(Fi.afficher());
    }
}

void MainWindow::on_supprimer_clicked()
{
    Fi.setid_f(ui->le_id_f->text().toInt());
       bool test=Fi.supprimer(Fi.getid_f());
       QMessageBox msgBox;
       if (test)
         { //refresh
            ui->tablefournisseur->setModel(Fi.afficher());
           msgBox.setText("suppresion avec succes");
       }
       else
           msgBox.setText("Echec de suppression");
                   msgBox.exec();
}



void MainWindow::on_modifier_clicked()
{
    int id_f=ui->le_id_f->text().toInt();
    QString societe=ui->le_societe->text();
    int num_tel=ui->le_num->text().toInt();
    QString nom_f=ui->le_nom->text();
     QString prenom_f=ui->le_prenom->text();
      QString adresse=ui->le_adresse->text();
  fournisseur Fi (id_f ,societe,num_tel ,nom_f, prenom_f, adresse);
   bool test=Fi.modifier();

       if (test)
         {
           ui->tablefournisseur->setModel(Fi.afficher());
           QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("modification avec succes\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tablefournisseur->setModel(Fi.afficher());
       }

}


void MainWindow::on_afficher_clicked()
{
    fournisseur Fi;
            ui->tablefournisseur->setModel(Fi.afficher());
}






void MainWindow::on_le_rech_textChanged(const QString &arg1)
{
    QString ch = arg1;

                    if (ch=="")
                        ui->tablefournisseur->setModel(Fi.afficher());
                    else
                      ui->tablefournisseur->setModel(Fi.rechercher(ch));
}



void MainWindow::on_tablefournisseur_activated(const QModelIndex &index)
{
    QString val=ui->tablefournisseur->model()->data(index).toString();

        QSqlQuery qry;
        qry.prepare("select * from FOURNISSEUR where id_f='"+val+"'");
    if(qry.exec())
    {
        while(qry.next())
    {

            ui->le_id_f->setText((qry.value(0).toString()));
            ui->le_societe->setText((qry.value(1).toString()));
            ui->le_num->setText((qry.value(2).toString()));
            ui->le_nom->setText((qry.value(3).toString()));
            ui->le_prenom->setText((qry.value(4).toString()));
          ui->le_adresse->setText((qry.value(5).toString()));
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("erreur"),
                    QObject::tr("Echec de modification\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}





void MainWindow::on_rb_nom_clicked()
{
    ui->tablefournisseur->setModel((Fi.trie_nom()));
}


void MainWindow::on_afficheravis_clicked()
{
    avie Av;
            ui->tableavie->setModel(Av.afficheravie());
}

void MainWindow::on_qr_clicked()
{
    if(ui->tablefournisseur->currentIndex().row()==-1)
                   QMessageBox::information(nullptr, QObject::tr("QR code"),
                                            QObject::tr("Veuillez Choisir un CODE du Tableau.\n"
                                                        "Click Ok to exit."), QMessageBox::Ok);
               else
               {

                    int id=ui->tablefournisseur->model()->data(ui->tablefournisseur->model()->index(ui->tablefournisseur->currentIndex().row(),0)).toInt();
                    const QrCode qr = QrCode::encodeText(std::to_string(id).c_str(), QrCode::Ecc::LOW);
                    std::ofstream myfile;
                    myfile.open ("qrcode.svg") ;
                    myfile << qr.toSvgString(1);
                    myfile.close();
                    QSvgRenderer svgRenderer(QString("qrcode.svg"));
                    QPixmap pix( QSize(90, 90) );
                    QPainter pixPainter( &pix );
                    svgRenderer.render( &pixPainter );
                    ui->QRCODE_3->setPixmap(pix);
               }
}

void MainWindow::on_pdf_clicked()
{
    QString strStream;
        strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
            if (QFileInfo(strStream).suffix().isEmpty()) { strStream.append(".pdf"); }

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName(strStream);



                  QTextStream out(&strStream);

                  const int rowCount = ui->tablefournisseur->model()->rowCount();
                  const int columnCount = ui->tablefournisseur->model()->columnCount();

                  out <<"<html>\n"
                        "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                      << "<title>ERP - COMmANDE LIST<title>\n "
                      << "</head>\n"
                      "<body bgcolor=#ffffff link=#5000A0>\n"


                      "<h1 style=\"text-align: center;\"><strong> *****LISTE DES FOURNISSEURS ***** </strong></h1>"

                      "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                        "</br> </br>";
                  // headers
                  out << "<thead><tr bgcolor=#d6e5ff>";
                  for (int column = 0; column < columnCount; column++)
                      if (!ui->tablefournisseur->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->tablefournisseur->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";

                  // data table
                  for (int row = 0; row < rowCount; row++) {
                      out << "<tr>";
                      for (int column = 0; column < columnCount; column++) {
                          if (!ui->tablefournisseur->isColumnHidden(column)) {
                              QString data =ui->tablefournisseur->model()->data(ui->tablefournisseur->model()->index(row, column)).toString().simplified();
                              out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                          }
                      }
                      out << "</tr>\n";
                  }
                  out <<  "</table>\n"
                      "</body>\n"
                      "</html>\n";

                  QTextDocument document;
                  document.setHtml(strStream);
                  document.print(&printer);
}
