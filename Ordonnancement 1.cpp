#include <iostream>
using namespace std;
struct tache{
    int ind;//nom de la tache
    int p;// temps de traitement 
    int c; //date de fin de traitement 
};

int main()
{
    //création de l'instance du 1||C
    const int n = 5;
    tache T[n];
    cout << "Quels sont les temps de traitement ?" << endl;
    for (int i = 0; i < n; i++) {
       cin >> T[i].p;
       T[i].ind = i + 1;
    }
    // résolution de problème
    // tri des taches selon l'ordre croissant des temps de traitement 
    tache t;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (T[i].p > T[j].p) {
                t = T[i];
                T[i] = T[j];
                T[j] = t;
            }
        }
    }
    //ordonnancement des taches 
    //ordonnancement de la première tâche qui commence a l'instant t=0
    T[0].c = T[0].p;
    //ordonnancement des autres tache avec i=1
    for (int i = 1; i < n; i++) {
        T[i].c = T[i - 1].c + T[i].p;
    }
    //affichage de la solution avec détails
    cout << "L'ordonnancement optimal est de valeur :" << T[n - 1].c << endl;
    for (int i = 0; i < n; i++) {
        cout << "T" << T[i].ind << " : [" << T[i].c - T[i].p << " , " << T[i].c << " ]." << endl;
     }

  
}


