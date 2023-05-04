#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
struct tache {
    int ind;//nom de la tache
    int p;// temps de traitement 
    int r; //date de disponibilite 
    int c; //date de fin de traitement 
};

void tri_r(int n, tache T[]) {
    // tri des taches selon l'ordre 
    //croissant temps de traitement  
    tache t;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (T[i].r > T[j].r) {
                t = T[i];
                T[i] = T[j];
                T[j] = t;
            }
        }
    }
}
int ordonnancer(int n, tache T[]) {
    //ordonnancement de la premiere tache qui commence a l'instant t=0
    T[0].c = T[0].r+T[0].p;
    //ordonnacement des autres tache avec i=1
    for (int i = 1; i < n; i++) {
        T[i].c = max(T[i - 1].c, T[i].r) + T[i].p;
    }
    return T[n - 1].c;
 }

void affichage(int n, tache T[]) {
    cout << setw(n) << " _________________________ " << endl;
    cout << setw(3) << " ";
    for (int i = 0; i < n; i++) {
        cout << setw(3) << "T" << T[i].ind;
    }
    cout << " " << endl;
    cout << setw(3) << "rj";
    for (int i = 0; i < n; i++) {
        cout << setw(4) << T[i].r;
    }
    cout << " " << endl;
    cout << setw(3) << "pj";
    for (int i = 0; i < n; i++) {
        cout << setw(4) << T[i].p;
    }
    cout << " " << endl;
}

int main()
{
    const int n = 5;
    //creation de l'instance du 1|rj|Cmax
    //const int n = 5;
    tache T[n];
    cout << "Quels sont les temps de taitement ?" << endl;
    for (int i = 0; i < n; i++) {
        cin >> T[i].p;
        T[i].ind = i + 1;
    }
    cout << "Quels sont les dates de disponibilites ?" << endl;
    for (int i = 0; i < n; i++) {
        cin >> T[i].r;
    }
    //affichage de l'instance 
    //appel a la fonction affichage
    affichage(n, T);
    // resolution de probleme
    //appel a la fonction tri 
    tri_r(n, T);
    //ordonnacement des taches 
    //appel a la fonction ordonnancer 
    int Cmax = ordonnancer(n, T);
    //affichage de la solution avec details
    cout << "L'ordonnacement optimal est de valeur :" << Cmax << endl;
    for (int i = 0; i < n; i++) {
        cout <<"T" << T[i].ind << " : [" << T[i].c - T[i].p << ", " << T[i].c << "]." << endl;
    }

}

