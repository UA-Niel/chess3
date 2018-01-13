//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include <QtWidgets/QMessageBox>
#include "game.h"
#include "positie.h"
#include "chessboard.h"
#include "mainwindow.h"

map<string, schaakStuk*> schaakStukken;

game::game() {}

game::~game() {}

// Zet het bord klaar; voeg de stukken op de jusite plaats toe
schaakStuk* zwartKoning = new koning(zwart);
schaakStuk* witKoning = new koning(wit);
void game::setStartBord() {
    //Zwart
    schaakStuk *zwartPion1 = new pion(zwart);
    schaakStuk *zwartPion2 = new pion(zwart);
    schaakStuk *zwartPion3 = new pion(zwart);
    schaakStuk *zwartPion4 = new pion(zwart);
    schaakStuk *zwartPion5 = new pion(zwart);
    schaakStuk *zwartPion6 = new pion(zwart);
    schaakStuk *zwartPion7 = new pion(zwart);
    schaakStuk *zwartPion8 = new pion(zwart);

    schaakStuk* zwartToren1 = new toren(zwart);
    schaakStuk* zwartToren2 = new toren(zwart);

    schaakStuk* zwartPaard1 = new paard(zwart);
    schaakStuk* zwartPaard2 = new paard(zwart);

    schaakStuk* zwartLoper1 = new loper(zwart);
    schaakStuk* zwartLoper2 = new loper(zwart);

    schaakStuk* zwartKoningin = new koningin(zwart);

    schaakStukken["a2"] = zwartPion1;
    schaakStukken["b2"] = zwartPion2;
    schaakStukken["c2"] = zwartPion3;
    schaakStukken["d2"] = zwartPion4;
    schaakStukken["e2"] = zwartPion5;
    schaakStukken["f2"] = zwartPion6;
    schaakStukken["g2"] = zwartPion7;
    schaakStukken["h2"] = zwartPion8;
    schaakStukken["a1"] = zwartToren1;
    schaakStukken["b1"] = zwartPaard1;
    schaakStukken["c1"] = zwartLoper1;
    schaakStukken["d1"] = zwartKoning;
    schaakStukken["e1"] = zwartKoningin;
    schaakStukken["f1"] = zwartLoper2;
    schaakStukken["g1"] = zwartPaard2;
    schaakStukken["h1"] = zwartToren2;

    //Wit
    schaakStuk *witPion1 = new pion(wit);
    schaakStuk *witPion2 = new pion(wit);
    schaakStuk *witPion3 = new pion(wit);
    schaakStuk *witPion4 = new pion(wit);
    schaakStuk *witPion5 = new pion(wit);
    schaakStuk *witPion6 = new pion(wit);
    schaakStuk *witPion7 = new pion(wit);
    schaakStuk *witPion8 = new pion(wit);

    schaakStuk* witToren1 = new toren(wit);
    schaakStuk* witToren2 = new toren(wit);

    schaakStuk* witPaard1 = new paard(wit);
    schaakStuk* witPaard2 = new paard(wit);

    schaakStuk* witLoper1 = new loper(wit);
    schaakStuk* witLoper2 = new loper(wit);

    schaakStuk* witKoningin = new koningin(wit);

    schaakStukken["a7"] = witPion1;
    schaakStukken["b7"] = witPion2;
    schaakStukken["c7"] = witPion3;
    schaakStukken["d7"] = witPion4;
    schaakStukken["e7"] = witPion5;
    schaakStukken["f7"] = witPion6;
    schaakStukken["g7"] = witPion7;
    schaakStukken["h7"] = witPion8;
    schaakStukken["a8"] = witToren1;
    schaakStukken["b8"] = witPaard1;
    schaakStukken["c8"] = witLoper1;
    schaakStukken["d8"] = witKoning;
    schaakStukken["e8"] = witKoningin;
    schaakStukken["f8"] = witLoper2;
    schaakStukken["g8"] = witPaard2;
    schaakStukken["h8"] = witToren2;

    for (auto i : schaakStukken) {
        i.second->setCurrentPositie(i.first);
    }
}

// Verplaats stuk s naar positie p
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool game::move(schaakStuk* s, positie p) {
    string currentPosition = mapChessToPosition(s);

    if (s == NULL) return false;

    //Get geldige_zetten
    vector<string> v = s->geldige_zetten(*this, currentPosition);


    for (int i = 0; i < v.size(); i++) {
        if (v[i] == p.str()) {

            //deleting
            map<string, schaakStuk *>::iterator it;
            it = schaakStukken.find(currentPosition);
            schaakStukken.erase(it);
            schaakStukken[p.str()] = s;

            s->firstSet = false;
            return true;
        }
    }

    return false;
}

// Geeft true als kleur schaak staat
bool game::schaak(zw kleur) {
    zw oppositeColor = zwart;
    schaakStuk* king = witKoning;
    string color = "Wit staat schaak!!";
    if (kleur == zwart) {
        oppositeColor = wit;
        king = zwartKoning;
        color = "Zwart staat schaak!!!";
    }

    vector<string> v;
    for (auto i : schaakStukken) {
        if (i.second->getKleur() == oppositeColor) {
            v = i.second->geldige_zetten(*this, i.first);



            for (auto j : v) {
                if (j == king->getCurrentPositie().str()) {
                    QMessageBox joehoe;
                    joehoe.setText(QString::fromStdString(color));
                    joehoe.exec();

                    cout << "j " << j << endl;

                    return true;
                }
            }
        }
    }

    return false;
}

// Geeft true als kleur schaakmat staat
bool game::schaakmat(zw kleur) {
    return false;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool game::pat(zw kleur) {
    return false;
}


//Inverses map search
string game::mapChessToPosition(schaakStuk* s) {
    for (auto i : schaakStukken)
        if (i.second == s)
            return i.first;
}