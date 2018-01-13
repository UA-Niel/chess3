//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "positie.h"
#include <cstdlib>


ostream& operator<<(ostream& s,positie p)
{ return s;}


positie::positie(int kolom, int row) {
    this->row = row;
    this->kolom = kolom;
}
positie::positie(string s) {
    this->row = this->charToInt(s[0]);
    this->kolom = ((int)s[1]) - 48;
}


int positie::charToInt(char c) {
    string characters = "abcdefgh";

    for (int i = 0; i < characters.length(); i++) {

        if (c == characters[i]) return i;
    }

    return -1;
}

string positie::intToStr(int i) {
    return string(1, "abcdefgh"[i]);
}


string positie::str() {
    string partOne = this->intToStr(this->row);
    string partTwo = to_string(this->kolom +1);

    return partOne + partTwo;
}


positie::positie() {
    this->kolom = 0;
    this->row = 0;
}

int positie::getX() {
    return this->kolom;
}
int positie::getY() {
    return this->row;
}
