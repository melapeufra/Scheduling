#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>
using namespace std;
struct tache {
	int ind;//indice 
	int p;//temps de traitement 
	int r;// date de disponibilite 
	int d;//date echue 
};
void tri_r(int n, tache T[], int s[]) {//tri des taches 
	for (int i = 0; i < n; i++)
		s[i] = i;
	int x;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (T[s[i]].r > T[s[j]].r) {
				//permutation
				x = s[i];
				s[i] = s[j];
				s[j] = x;
			}
		}
	}
}

int ordonnancer(int n, tache T[], int s[], int c[]) {
	int l = 0;
	c[s[0]] = T[s[0]].r + T[s[0]].p;//ordonnancement de la première tache
	// valeur de Lmax 
	if (max(c[s[0]] - T[s[0]].d, 0) > l)
		l = max(c[s[0]] - T[s[0]].d, 0);
	//ordonnancement du reste des taches i=1 a n-1
	for (int i = 1; i < n; i++) {
		c[s[i]] = max(c[s[i - 1]], T[s[i]].r) + T[s[i]].p;
		// valeur de Lmax
		if (max(c[s[i]] - T[s[i]].d, 0) > l)
			l = max(c[s[i]] - T[s[i]].d, 0);
	}
	return l;
}
void recherche_locale(int n, int s[], int s1[]) {
	//génération de deux indices aléatoires 
	int i1 = rand() % n;
	int i2 = rand() % n;
	while (i1 == i2) {
		i2 = rand() % n;
	}
	//copier les valeurs de la solution s dans s1
	for (int i = 0; i < n; i++) 
		s1[i] = s[i];
	//permutation
	int val = s1[i1];
	s1[i1] = s1[i2];
	s1[i2] = val;
}


void affichage_sol(int n, tache T[], int c[], int s[]) {
	cout << setw(3) << " ";
	for (int i = 0; i < n; i++) {
		cout << setw(3) << "T" << s[i] + 1;
	}
	cout << " " << endl;
	cout << setw(3) << "cj";
	for (int i = 0; i < n; i++) {
		cout << setw(4) << c[s[i]];
	}
	cout << " " << endl;
	cout << setw(3) << "lj";
	for (int i = 0; i < n; i++) {
		cout << setw(4) << max(0, c[s[i]] - T[s[i]].d);
	}
	cout << " " << endl;
}
void affichage(int n, tache T[], int c[], int s[]) {
	cout << setw(3) << " ";
	for (int i = 0; i < n; i++) {
		cout << setw(3) << "T" << s[i] + 1;
	}
	cout << " " << endl;
	cout << setw(3) << "cj";
	for (int i = 0; i < n; i++) {
		cout << setw(4) << c[s[i]];
	}
	cout << " " << endl;
	cout << setw(3) << "lj";
	for (int i = 0; i < n; i++) {
		cout << setw(4) << max(0, c[s[i]] - T[s[i]].d);
	}
	cout << " " << endl;
}

void recuit_simule(int n, tache T[], int c[], int s[]) {
	int L;	                    int L1;	                 int L2;
	int* s1 = new int[n];	    int* c1 = new int[n];
	int* s2 = new int[n];	    int* c2 = new int[n];
	double delta;           	int nb = 1000;
	double Teta = 100000.00;	double Tetaf = 1.00;
	double alpha = 0.025;	    double y;	             int k;
	//solution initiale
	tri_r(n, T, s1);
	L1 = ordonnancer(n, T, s1, c1);
	//la solution initiale est aussi la meilleure solution jusqu'ici
	L = L1;
	for (int i = 0; i < n; i++) {
		s[i] = s1[i];			
        c[i] = c1[i];
	}
	//affichage de la solution 
	cout << " ____________________________" << endl;
	cout << "Valeur de Lmax de la solution initiale : " << L << endl;
	affichage(n, T, c, s);
	//Phase d'améloirationn :
	while (Teta > Tetaf) {
		k = 1;
		while (k < nb) {
			// la transformation 
			recherche_locale(n, s1, s2);
			L2 = ordonnancer(n, T, s2, c2);
			delta = L2 - L1;
			if (delta < 0) {
				L1 = L2;
				for (int i = 0; i < n; i++) {
					s1[i] = s2[i];			
					c1[i] = c2[i];
				}
				if (L2 < L) {
                    // est mieux que la mieullere solution trouvee 
					L = L2;
					for (int i = 0; i < n; i++) {
						s[i] = s2[i];		
						c[i] = c2[i];
					}
					cout << " ____________________________" << endl;
					cout << "Solution amelioree Lmax = " << L << endl;
					affichage(n, T, c, s);
				}
			}
			else {// delta >=0
				float p = float(rand() % 1001);
				p = p / 1000;
				y = exp(-delta / Teta);
				if (p <= y) {
					//on accepte une mauvaise solution; 
					//s2 devient la solution actuelle s1
					L1 = L2;
					for (int i = 0; i < n; i++) {
						s1[i] = s2[i];											c1[i] = c2[i];
					}
				}
			}
			k += 1;
		}//end while(k<nb)
		Teta *= alpha;
		cout << "teta : " << Teta << endl;
	}// end while (teta>tetaf)
	delete[] c1;	delete[] s1;
	delete[] c2;	delete[] s2;
}


void instance(int n, tache T[]) {
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
	cout << setw(3) << "dj";
	for (int i = 0; i < n; i++) {
		cout << setw(4) << T[i].d;
	}
	cout << " " << endl;
}





int main() {
	const int n = 10;
	tache T[n];// un tableau de n tache
	cout << "Inserer les temps d'execution" << endl;
	for (int i = 0; i < n; i++) {
		T[i].ind = i + 1;		cin >> T[i].p;
	}
	cout << "Inserer les dates de disponibilite" << endl;
	for (int i = 0; i < n; i++)
		cin >> T[i].r;
	cout << "Inserer les dates echues" << endl;
	for (int i = 0; i < n; i++)
		cin >> T[i].d;
	//affichage de l'instance 
	instance(n, T);
	//solution
	int c[n];				
    int s[n];
	// resolution 
	recuit_simule(n, T, c, s);
}


