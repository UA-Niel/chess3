//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_GAME_H
#define SCHAKEN_GAME_H

#include "schaakStuk.h"
#include "positie.h"
#include "chessboard.h"
#include <map>

class positie;
// variabelen om de status van het spel/bord te bewaren
extern map<string, schaakStuk*> schaakStukken;

class game {
public:


    game();
    ~game();

    bool move(schaakStuk*,positie);

    bool schaak(zw kleur);
    bool schaakmat(zw kleur);
    bool pat(zw kleur);
    void setStartBord();

    map<string, schaakStuk*> schaakStukken;
    string mapChessToPosition(schaakStuk* s);


};


#endif //SCHAKEN_GAME_H
