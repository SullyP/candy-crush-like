#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <QObject>
#include "case.h"
#include "bonbon.h"
#include "niveau.h"
#include "vue.h"

class Controleur : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int tailleBonbon READ getTailleBonbon WRITE setTailleBonbon NOTIFY tailleBonbonChanged)
public:
    explicit Controleur(QObject *parent = 0);
    int getTailleBonbon() const;
    void setTailleBonbon(int taille);
private:
    int tailleBonbon;
signals:
    void tailleBonbonChanged();
public slots:

};

#endif // CONTROLEUR_H
