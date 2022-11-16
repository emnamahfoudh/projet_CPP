#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include"fournisseur.h"
#include"avie.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouteravis_clicked();

    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_afficher_clicked();

    void on_le_rech_textChanged(const QString &arg1);

    void on_tablefournisseur_activated(const QModelIndex &index);

    void on_rb_nom_clicked();

    void on_afficheravis_clicked();

    void on_qr_clicked();

    void on_pdf_clicked();

private:
    Ui::MainWindow *ui;

    fournisseur Fi;
    avie Av;
};
#endif // MAINWINDOW_H
