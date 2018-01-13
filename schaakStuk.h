//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include <chessboard.h>
#include "positie.h"

class game;

enum zw{zwart,wit};

class schaakStuk {
public:
    bool firstSet = true;
    schaakStuk(zw kleur): kleur(kleur) {}

    virtual Piece piece() const=0;      // Deze functie krijg je cadeau
                                        // Je hebt die nodig om het stuk in de
                                        // GUI te tekenen
                                        // Meer info: kijk naar mainwindow.cpp, lijn 24

    zw getKleur() const { return kleur; }


    positie currentPositie;
    void setCurrentPositie(const positie& currentPositie) {
        this->currentPositie = currentPositie;
    }
    positie& getCurrentPositie() {
        return this->currentPositie;
    }

    virtual vector<string> geldige_zetten(game& g, positie currentPosition) = 0;

private:
    zw kleur;
};

class pion:public schaakStuk {
public:

    pion(zw kleur):schaakStuk(kleur) {}
    virtual Piece piece() const override {
        return Piece(Piece::Pawn,getKleur()==wit?Piece::White:Piece::Black);
    }

protected:
    //Geldige posities
    vector<string> geldige_zetten(game& g, positie currentPosition);
};

class toren:public schaakStuk {
public:
    toren(zw kleur):schaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Rook,getKleur()==wit?Piece::White:Piece::Black);
    }

protected:
    //Geldige posities
    vector<string> geldige_zetten(game& g, positie currentPosition);
};

class paard:public schaakStuk {
public:
    paard(zw kleur):schaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Knight,getKleur()==wit?Piece::White:Piece::Black);
    }

protected:
    //Geldige posities
    vector<string> geldige_zetten(game& g, positie currentPosition);
};

class loper:public schaakStuk {
public:
    loper(zw kleur):schaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Bishop,getKleur()==wit?Piece::White:Piece::Black);
    }

protected:
    //Geldige posities
    vector<string> geldige_zetten(game& g, positie currentPosition);
};

class koning:public schaakStuk {
public:
    koning(zw kleur):schaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::King,getKleur()==wit?Piece::White:Piece::Black);
    }

protected:
    //Geldige posities
    vector<string> geldige_zetten(game& g, positie currentPosition);
};

class koningin:public schaakStuk {
public:
    koningin(zw kleur):schaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Queen,getKleur()==wit?Piece::White:Piece::Black);
    }

protected:
    //Geldige posities
    vector<string> geldige_zetten(game& g, positie currentPosition);
};

#endif //SCHAKEN_SCHAAKSTUK_H
