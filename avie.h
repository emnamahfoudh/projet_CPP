#ifndef AVIE_H
#define AVIE_H
#include<QString>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include<QVector>


class avie
{
public:
    avie();


    avie(int,QString,QString,QString);
    int getid_fournisseur();


    QString getrapid();
    QString getservice();
    QString getcommentaire();

    void setid_fournisseur(int);


    void setrapid(QString);
    void setservice(QString);
    void setcommentaire(QString);



    bool ajouteravie();
    QSqlQueryModel * afficheravie();
    int calcul_type(int,int);


private:
    int id_fournisseur;
    QString rapid,service,commentaire;







};

#endif // AVIE_H
