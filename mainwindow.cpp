#include "mainwindow.h"
#include "schaakStuk.h"
#include <QMessageBox>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    scene = new ChessBoard;
    QGraphicsView *view = new QGraphicsView(scene);
    setCentralWidget(view);
    connect(scene,SIGNAL(clicked(int,int)),this,SLOT(clicked(int,int)));

    g.setStartBord();
    update();




}

// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void MainWindow::update() {
    scene->clearBoard();

    for (auto i : g.schaakStukken) {
        int x = (int)i.first[1] - 48;
        int y = positie::charToInt(i.first[0]);

        scene->setItem(--x, y, i.second->piece());
        i.second->setCurrentPositie(positie(--x, y));
    }
}

// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
bool trigger = false;
schaakStuk *s = nullptr;
bool witTurn = true;
void MainWindow::clicked(int r, int k) {
   if (!trigger) {
       int find = g.schaakStukken.count(positie(r,k).str());
       if (find <= 0) return;

       s = g.schaakStukken[positie(r,k).str()];
       if (witTurn) {
           if (s->getKleur() != wit) {
               cout << "Wit is aan de beurt!!!!" << endl;
               return;
           }
       } else {
           if (s->getKleur() != zwart) {
               cout << "Zwart is aan de beurt!!!!" << endl;
               return;
           }
       }

       //Marking valid spots
       vector<string> v = s->geldige_zetten(g, positie(r,k));
       for (auto i : v) {
           positie x = positie(i);
           int r = x.getX();
           int k = x.getY();

           scene->setTileFocus(r,k,!scene->hasTileFocus(r,k));
       }


       trigger = true;
       scene->setPieceFocus(r,k, !scene->hasPieceFocus(r,k));

   } else {
        setPiece(s, positie(r,k));
        trigger = false;
        scene->removeAllFocus();
   }


    update();
}
void MainWindow::selectPiece(schaakStuk *s, positie p) {

}
void MainWindow::setPiece(schaakStuk *s, const positie &p) {
    if (!g.move(s, p)) return;

    if (witTurn) {
        witTurn = false;
    } else {
        if (!witTurn) {
            witTurn = true;
        }
    }

    g.schaak(zwart);
    return;
}
