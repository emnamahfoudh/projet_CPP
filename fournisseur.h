#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include<QString>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include<QVector>


class fournisseur
{
public:
    fournisseur();
    fournisseur(int,QString,int,QString,QString,QString);

    int getid_f();
    QString getsociete();
    int getnum_tel();
    QString getnom_f();
    QString getprenom_f();
    QString getadresse();



    void setid_f(int);
    void setsociete(QString);
    void setnum_tel(int);
    void setnom_f(QString);
    void setprenom_f(QString);
    void setadresse(QString);



    QSqlQueryModel * rechercher(QString v);
    QSqlQueryModel * trie_nom();

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    void creation_pdf();

private:
    int id_f,num_tel;
    QString societe,nom_f,prenom_f,adresse;






};

#endif // FOURNISSEUR_H
