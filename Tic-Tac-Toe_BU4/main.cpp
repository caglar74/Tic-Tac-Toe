#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//Spielfeld
void spielfeldAnzeigen(char feld[]) {
    cout << endl;
    cout << " " << feld[0] << " | " << feld[1] << " | " << feld[2] << "     0 | 1 | 2\n";
    cout << "---+---+---   ---+---+---\n";
    cout << " " << feld[3] << " | " << feld[4] << " | " << feld[5] << "     3 | 4 | 5\n";
    cout << "---+---+---   ---+---+---\n";
    cout << " " << feld[6] << " | " << feld[7] << " | " << feld[8] << "     6 | 7 | 8\n\n";
}

//Zustände lol
enum State {
    START,
    SPIELER_ZUG,
    BOT_ZUG,
    PRUEFEN,
    SPIEL_ENDE
};

int main() {

    //Zeit
    srand(time(0));
    bool spielLaeuft = true;

    while (spielLaeuft) {

        char feld[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
        char spielerX = 'X';
        char spielerO = 'O';
        char aktuellerSpieler;
        bool gegenBot = false;

        int gewinn[8][3] = {
            {0,1,2},{3,4,5},{6,7,8},
            {0,3,6},{1,4,7},{2,5,8},
            {0,4,8},{2,4,6}
        };

        State zustand = START;
        int eingabe;

        while (zustand != SPIEL_ENDE) {

            switch (zustand) {

            //Ja Start halt
            case START:
                cout << "Willkommen bei Tic Tac Toe!\n";
                cout << "1 - Gegen Freund\n";
                cout << "2 - Gegen Bot\n";
                cin >> eingabe;

                if (eingabe == 2)
                    gegenBot = true;
                else
                    gegenBot = false;

                //  Zufällig bestimmen, wer anfängt
                if (rand() % 2 == 0)
                    aktuellerSpieler = spielerX;
                else
                    aktuellerSpieler = spielerO;

                spielfeldAnzeigen(feld);

                //  Richtigen Start-Zustand setzen
                if (gegenBot && aktuellerSpieler == spielerO)
                    zustand = BOT_ZUG;
                else
                    zustand = SPIELER_ZUG;

                break;

            case SPIELER_ZUG:
                cout << "Spieler " << aktuellerSpieler << ", Feld (0-8): ";
                cin >> eingabe;

                if (eingabe < 0 || eingabe > 8 || feld[eingabe] != ' ') {
                    cout << "Ungueltiger Zug!\n";
                } else {
                    feld[eingabe] = aktuellerSpieler;
                    spielfeldAnzeigen(feld);
                    zustand = PRUEFEN;
                }
                break;

            case BOT_ZUG: {
                cout << "Bot ist dran...\n";
                int zug = -1;

                // prüft, ob er gewinnen kann
                for (int i = 0; i < 8; i++) {
                    int a = gewinn[i][0];
                    int b = gewinn[i][1];
                    int c = gewinn[i][2];

                    if (feld[a] == spielerO && feld[b] == spielerO && feld[c] == ' ')
                        zug = c;
                    if (feld[a] == spielerO && feld[c] == spielerO && feld[b] == ' ')
                        zug = b;
                    if (feld[b] == spielerO && feld[c] == spielerO && feld[a] == ' ')
                        zug = a;
                }

                //Bot prüft, ob er mich blocken kann
                if (zug == -1) {
                    for (int i = 0; i < 8; i++) {
                        int a = gewinn[i][0];
                        int b = gewinn[i][1];
                        int c = gewinn[i][2];

                        if (feld[a] == spielerX && feld[b] == spielerX && feld[c] == ' ')
                            zug = c;
                        if (feld[a] == spielerX && feld[c] == spielerX && feld[b] == ' ')
                            zug = b;
                        if (feld[b] == spielerX && feld[c] == spielerX && feld[a] == ' ')
                            zug = a;
                    }
                }
                //Wenn er nicht gewinnen kann oder nicht blocken kann placed er random
                if (zug == -1) {
                    zug = rand() % 9;
                    while (feld[zug] != ' ')
                        zug = rand() % 9;
                }

                feld[zug] = spielerO;
                spielfeldAnzeigen(feld);
                zustand = PRUEFEN;
                break;
            }

            case PRUEFEN: {
                bool gewonnen = false;

                for (int i = 0; i < 8; i++) {
                    int a = gewinn[i][0];
                    int b = gewinn[i][1];
                    int c = gewinn[i][2];

                    if (feld[a] != ' ' &&
                        feld[a] == feld[b] &&
                        feld[b] == feld[c]) {

                        cout << "Spieler " << feld[a] << " hat gewonnen!\n";
                        zustand = SPIEL_ENDE;
                        gewonnen = true;
                    }
                }

                if (!gewonnen) {
                    bool feldFrei = false;

                    for (int i = 0; i < 9; i++) {
                        if (feld[i] == ' ')
                            feldFrei = true;
                    }

                    if (!feldFrei) {
                        cout << "Unentschieden!\n";
                        zustand = SPIEL_ENDE;
                    } else {
                        if (aktuellerSpieler == spielerX)
                            aktuellerSpieler = spielerO;
                        else
                            aktuellerSpieler = spielerX;

                        if (gegenBot && aktuellerSpieler == spielerO)
                            zustand = BOT_ZUG;
                        else
                            zustand = SPIELER_ZUG;
                    }
                }
                break;
            }

            case SPIEL_ENDE:
                break;
            }
        }

        cout << "\nNochmal spielen?\n";
        cout << "1 - Ja\n";
        cout << "2 - Nein\n";
        cin >> eingabe;

        if (eingabe != 1)
            spielLaeuft = false;
    }

    cout << "Spiel beendet.\n";
    return 0;
}
