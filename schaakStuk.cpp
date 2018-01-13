//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "schaakStuk.h"
#include "game.h"

//Check if coordinate is in field
bool isInField(string test) {
    string valid = "abcdefgh";
    char a = test[0];
    bool no = true;
    for (auto c : valid) {
        if (a == c) no = false;
    }
    if (!no) return true;

    valid = "12345678";
    char b = test[1];
    no = true;
    for (auto c : valid) {
        if (a == c) no = false;
    }
    if (!no) return true;

    return false;
}

vector<string> pion::geldige_zetten(game& g, positie currentPosition) {
    vector<string> v;

    int currentX = currentPosition.kolom;
    int currentY = currentPosition.row;

    int one = 1;
    int two = 2;
    if (this->getKleur() == wit) {
        one = -1;
        two = -2;
    }

    string test = "";
    if (this->firstSet) {
        //X - 2, Y
        test = positie::intToStr(currentY);
        test += to_string(currentX + two);
        if (g.schaakStukken.count(test) <= 0)
            v.push_back(test);
    }
    //X - one, Y
    test = positie::intToStr(currentY);
    test += to_string(currentX + one);
    if (g.schaakStukken.count(test) <= 0)
        if (isInField(test)) v.push_back(test);

    //X - one, Y - one
    test = positie::intToStr(currentY - one);
    test += to_string(currentX + one);
    if (g.schaakStukken.count(test) > 0)
        if (isInField(test)) v.push_back(test);

    //X - one, Y + one
    test = positie::intToStr(currentY + one);
    test += to_string(currentX + one);
    if (g.schaakStukken.count(test) > 0)
        if (isInField(test)) v.push_back(test);

    return v;
}

vector<string> toren::geldige_zetten(game& g, positie currentPosition) {
    vector<string> v;

    int currentX = currentPosition.kolom;
    int currentY = currentPosition.row;

    string test = "";
    //Forward
    for (int i = 1; i <= 8; i++) {
        test = positie::intToStr(currentY);
        test += to_string(currentX + i);

        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }
    //Right
    for (int i = 1; i <=8 ; i++) {
        test = positie::intToStr(currentY + i);
        test += to_string(currentX);



        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }
    //Left
    for (int i = 1; i <= 8; i++) {
        test = positie::intToStr(currentY - i);
        test += to_string(currentX);

        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }
    //Backward
    for (int i = 1; i <= 8; i++) {
        test = positie::intToStr(currentY);
        test += to_string(currentX - i);

        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }

    return v;
};

vector<string> paard::geldige_zetten(game& g, positie currentPosition) {
    vector<string> v;

    int currentX = currentPosition.kolom;
    int currentY = currentPosition.row;

    string test;
    //Testing: Current -> 2x Up -> Left & Right
    test = positie::intToStr(currentY -1);
    test += to_string(currentX + 2);

    //Check if there's something on test-place
    if (g.schaakStukken.count(test) > 0) {
        //If not own color, it's valid
        if (g.schaakStukken[test]->getKleur() != this->getKleur()) {
            v.push_back(test);
        }
    } else {
        //If in field & empty, valid
        if (isInField(test)) v.push_back(test);
    }

    test = positie::intToStr(currentY +1);
    test += to_string(currentX + 2);

    //Check if there's something on test-place
    if (g.schaakStukken.count(test) > 0) {
        //If not own color, it's valid
        if (g.schaakStukken[test]->getKleur() != this->getKleur()) {
            v.push_back(test);
        }
    } else {
        //If in field & empty, valid
        if (isInField(test)) v.push_back(test);
    }





    //Testing: Current -> 2x Down -> Left & Right
    test = positie::intToStr(currentY +1);
    test += to_string(currentX - 2);

    //Check if there's something on test-place
    if (g.schaakStukken.count(test) > 0) {
        //If not own color, it's valid
        if (g.schaakStukken[test]->getKleur() != this->getKleur()) {
            v.push_back(test);
        }
    } else {
        //If in field & empty, valid
        if (isInField(test)) v.push_back(test);
    }

    test = positie::intToStr(currentY -1);
    test += to_string(currentX - 2);

    //Check if there's something on test-place
    if (g.schaakStukken.count(test) > 0) {
        //If not own color, it's valid
        if (g.schaakStukken[test]->getKleur() != this->getKleur()) {
            v.push_back(test);
        }
    } else {
        //If in field & empty, valid
        if (isInField(test)) v.push_back(test);
    }



    //Testing: Current -> 2x left -> Top & Bottom
    test = positie::intToStr(currentY +2);
    test += to_string(currentX - 1);

    //Check if there's something on test-place
    if (g.schaakStukken.count(test) > 0) {
        //If not own color, it's valid
        if (g.schaakStukken[test]->getKleur() != this->getKleur()) {
            v.push_back(test);
        }
    } else {
        //If in field & empty, valid
        if (isInField(test)) v.push_back(test);
    }

    test = positie::intToStr(currentY +2);
    test += to_string(currentX + 1);

    //Check if there's something on test-place
    if (g.schaakStukken.count(test) > 0) {
        //If not own color, it's valid
        if (g.schaakStukken[test]->getKleur() != this->getKleur()) {
            v.push_back(test);
        }
    } else {
        //If in field & empty, valid
        if (isInField(test)) v.push_back(test);
    }



    //Testing: Current -> 2x right -> Top & Bottom
    test = positie::intToStr(currentY -2);
    test += to_string(currentX - 1);

    //Check if there's something on test-place
    if (g.schaakStukken.count(test) > 0) {
        //If not own color, it's valid
        if (g.schaakStukken[test]->getKleur() != this->getKleur()) {
            v.push_back(test);
        }
    } else {
        //If in field & empty, valid
        if (isInField(test)) v.push_back(test);
    }

    test = positie::intToStr(currentY -2);
    test += to_string(currentX + 1);

    //Check if there's something on test-place
    if (g.schaakStukken.count(test) > 0) {
        //If not own color, it's valid
        if (g.schaakStukken[test]->getKleur() != this->getKleur()) {
            v.push_back(test);
        }
    } else {
        //If in field & empty, valid
        if (isInField(test)) v.push_back(test);
    }

    return v;

};

vector<string> loper::geldige_zetten(game& g, positie currentPosition) {
    vector<string> v;

    int currentX = currentPosition.kolom;
    int currentY = currentPosition.row;

    string test = "";
    //Diagonal right-up
    for (int i = 1; i < 8; i++) {
            test = positie::intToStr(currentY + i);
            test += to_string(currentX + i);

        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }

    //Diagonal left-up
    for (int i = 1; i < 8; i++) {
        test = positie::intToStr(currentY - i);
        test += to_string(currentX + i);

        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }

    //Diagonal bottom-up
    for (int i = 1; i < 8; i++) {
        test = positie::intToStr(currentY + i);
        test += to_string(currentX - i);

        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }

    //Diagonal bottom-up
    for (int i = 1; i < 8; i++) {
        test = positie::intToStr(currentY - i);
        test += to_string(currentX - i);

        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }


    return v;
};

vector<string> koning::geldige_zetten(game& g, positie currentPosition) {
    vector<string> v;

    int currentX = currentPosition.kolom;
    int currentY = currentPosition.row;

    string test = "";
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            test = positie::intToStr(currentY + j);
            test += to_string(currentX + i);

            //Check if there's something on test-place
            if (g.schaakStukken.count(test) > 0) {
                //If not own color, it's valid
                if (g.schaakStukken[test]->getKleur() != this->getKleur()) {
                    v.push_back(test);
                }
            } else {
                //If in field & empty, valid
                if (isInField(test)) v.push_back(test);
            }
        }
    }

  /*  for (auto i: v) {
        cout << i << endl;
    }
*/
    return v;
};

vector<string> koningin::geldige_zetten(game& g, positie currentPosition) {
    vector<string> v;

    int currentX = currentPosition.kolom;
    int currentY = currentPosition.row;

    string test = "";
    //Forward
    for (int i = 1; i <= 8; i++) {
        test = positie::intToStr(currentY);
        test += to_string(currentX + i);

        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }
    //Right
    for (int i = 1; i <=8 ; i++) {
        test = positie::intToStr(currentY + i);
        test += to_string(currentX);



        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }
    //Left
    for (int i = 1; i <= 8; i++) {
        test = positie::intToStr(currentY - i);
        test += to_string(currentX);

        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }
    //Backward
    for (int i = 1; i <= 8; i++) {
        test = positie::intToStr(currentY);
        test += to_string(currentX - i);

        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }

    //Diagonal right-up
    for (int i = 1; i < 8; i++) {
        test = positie::intToStr(currentY + i);
        test += to_string(currentX + i);

        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }

    //Diagonal left-up
    for (int i = 1; i < 8; i++) {
        test = positie::intToStr(currentY - i);
        test += to_string(currentX + i);

        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }

    //Diagonal bottom-up
    for (int i = 1; i < 8; i++) {
        test = positie::intToStr(currentY + i);
        test += to_string(currentX - i);

        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }

    //Diagonal bottom-up
    for (int i = 1; i < 8; i++) {
        test = positie::intToStr(currentY - i);
        test += to_string(currentX - i);

        //Take enemy piece
        if (g.schaakStukken.count(test) > 0) {
            //Or stop if own piece
            if (g.schaakStukken[test]->getKleur() == this->getKleur()) break;

            v.push_back(test);
            break;
        }
        //Outside board?
        if (!isInField(test)) break;

        v.push_back(test);
    }


    return v;
};
