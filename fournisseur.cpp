#include "fournisseur.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QSqlQueryModel>
#include<QString>
#include<QFileDialog>



    using namespace std;

    fournisseur::fournisseur()
    {
    id_f=0;
    num_tel=0;
    societe=" ";
    nom_f=" ";
    prenom_f=" ";
    adresse=" ";

    }

    fournisseur::fournisseur( int id_f,QString societe,int num_tel,QString nom_f,QString prenom_f,QString adresse)
    {
        this->id_f=id_f;
        this->societe=societe;
        this->num_tel=num_tel;
        this->nom_f=nom_f;
        this->prenom_f=prenom_f;
        this->adresse=adresse;


    }

    int fournisseur::getid_f(){return id_f;}
    QString fournisseur::getsociete(){return societe  ;}
    int fournisseur::getnum_tel(){return  num_tel ;}
    QString fournisseur::getnom_f(){return  nom_f ;}
    QString fournisseur::getprenom_f(){return  prenom_f ;}
    QString fournisseur::getadresse(){return  adresse ;}


    void  fournisseur::setid_f(int id_f){this->id_f=id_f;}
    void  fournisseur::setsociete(QString societe){this->societe=societe;}
    void  fournisseur::setnum_tel(int num_tel){this->num_tel=num_tel;}
    void  fournisseur::setnom_f(QString nom_f){this->nom_f=nom_f;}
    void  fournisseur::setprenom_f(QString prenom_f){ this->prenom_f=prenom_f;}
    void  fournisseur::setadresse(QString adresse){this->adresse=adresse;}


    bool fournisseur::ajouter()
    {
        QString id_fournisseur_string=QString::number(id_f);
            QString num_tel_string=QString::number(num_tel);
               QSqlQuery query;
                  query.prepare("INSERT INTO FOURNISSEUR (id_f, societe, num_tel,nom_f,prenom_f,adresse) "
                                "VALUES (:id, :soci, :num, :nom, :prenom, :adres)");
                  query.bindValue(0, id_fournisseur_string);
                  query.bindValue(1, societe);
                  query.bindValue(2, num_tel_string);
                  query.bindValue(3, nom_f);
                  query.bindValue(4, prenom_f);
                  query.bindValue(5, adresse);


                  return query.exec();
    }


    QSqlQueryModel * fournisseur::afficher()
    {
    QSqlQueryModel *model = new QSqlQueryModel;

    model->setQuery("SELECT*  FROM FOURNISSEUR");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_f"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("societe"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("num_tel"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom_f"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("prenom_f"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));

    return model;
    }

    bool fournisseur::modifier()
    {


        QSqlQuery query;
           query.prepare("update FOURNISSEUR SET societe=?,num_tel=?,nom_f=?,prenom_f=?,adresse=? where id_f=?");
           query.addBindValue(societe);
           query.addBindValue(num_tel);
           query.addBindValue(nom_f);
           query.addBindValue(prenom_f);
           query.addBindValue(adresse);
           query.addBindValue(id_f);
          return query.exec();

    }
    bool fournisseur::supprimer(int id_f)
    {

        QSqlQuery query;
           query.prepare("Delete from FOURNISSEUR where id_f=:id_f ");
           query.bindValue(0, id_f);
          return query.exec();
    }

    QSqlQueryModel * fournisseur::rechercher(QString v)
    {
        QString id_fournisseur_string=QString::number(id_f);
        QString num_tel_string=QString::number(num_tel);
         QSqlQueryModel *model=new QSqlQueryModel();

          model->setQuery("SELECT * FROM FOURNISSEUR  WHERE id_f LIKE '%"+v+"%' OR societe LIKE '%"+v+"%' OR num_tel LIKE '%"+v+"%' OR nom_f LIKE '%"+v+"%' OR prenom_f LIKE '%"+v+"%' OR adresse LIKE '%"+v+"%'");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_fournisseur"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("societe"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("num_tel"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom_f"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("prenom_f"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));

          return model;
    }

    QSqlQueryModel *fournisseur::trie_nom()
    {
        QSqlQueryModel *model=new QSqlQueryModel();
         model->setQuery("SELECT * FROM FOURNISSEUR ORDER BY nom_f ");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_fournisseur"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("societe"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("num_tel"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom_f"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("prenom_f"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));


         return model;
    }

