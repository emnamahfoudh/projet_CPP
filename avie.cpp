#include "avie.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QSqlQueryModel>
#include<QString>


using namespace std;

avie::avie()
{
id_fournisseur=0;
rapid=" ";
service=" ";
commentaire=" ";


}

avie::avie( int id_fournisseur,QString rapid,QString service,QString commentaire)

{
    this->id_fournisseur=id_fournisseur;
    this->rapid=rapid;
    this->service=service;
    this->commentaire=commentaire;



}

int avie::getid_fournisseur(){return id_fournisseur;}
QString avie::getrapid(){return rapid ;}
QString avie::getservice(){return service ;}
QString avie::getcommentaire(){return commentaire ;}


void  avie::setid_fournisseur(int id_fournisseur){this->id_fournisseur=id_fournisseur;}
void  avie::setrapid(QString rapid){this->rapid=rapid;}
void  avie::setservice(QString service){this->service=service;}
void  avie::setcommentaire(QString commentaire){this->commentaire=commentaire;}


bool avie::ajouteravie()
{
    QString id_fournisseur_string=QString::number(id_fournisseur);

        QSqlQuery query;
              query.prepare("INSERT INTO AVIE (id_fournisseur, rapid, service, commentaire) "
                          "VALUES (:id, :rapi, :servi, :comm)");
              query.bindValue(0, id_fournisseur_string);
              query.bindValue(1, rapid);
              query.bindValue(2, service);
              query.bindValue(3, commentaire);



              return query.exec();
}


QSqlQueryModel * avie::afficheravie()
{
QSqlQueryModel *model = new QSqlQueryModel;

model->setQuery("SELECT*  FROM AVIE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_fournisseur"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("rapid"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("service"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("commentaire"));



return model;
}
