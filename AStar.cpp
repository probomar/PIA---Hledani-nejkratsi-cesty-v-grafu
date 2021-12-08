#include "AStar.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

void AStarAlgorithm(int vzdalenost[13][13], int start, int cil, int souradnice [2][13])
{
    int inf=1000000;
        int pocet_krizovatek=sizeof(vzdalenost)/sizeof(*vzdalenost);

        int cestan[pocet_krizovatek][pocet_krizovatek];

        for(int i=0; i<pocet_krizovatek; i++)
        {
            for(int j=0; j<pocet_krizovatek; j++)
            {
                if(vzdalenost[i][j]==0)
                {
                    cestan[i][j]=inf;
                }
                else
                {
                    cestan[i][j]=vzdalenost[i][j];
                }
            }
        }

        int krizovatky[pocet_krizovatek];
        for (int i=0; i<pocet_krizovatek; i++)
        {
            krizovatky[i]=i+1;
        }

        int postup_cesty[pocet_krizovatek];
        postup_cesty[start-1]=0;

        vector<int> delka_cesty(pocet_krizovatek);
        for(int i=0; i<pocet_krizovatek; i++)
        {
            delka_cesty[i]=inf;
        }
        delka_cesty[start-1]=0;

        vector<int> F(pocet_krizovatek);
        for(int i=0; i<pocet_krizovatek; i++)
        {
            F[i]=inf;
        }
        F[start-1]=0;

        for(int i=0; i<pocet_krizovatek; i++)
        {
            cout << delka_cesty[i] <<", ";
        }
        cout << endl << endl;

        vector <int> zasobnik(pocet_krizovatek);
        for (int i=0; i<pocet_krizovatek; i++)
        {
            zasobnik[i]=i;
        }
        int k=0, i;
        /*cout << "Zasobnik ";
        print_vector(zasobnik);
        cout << endl;*/


    //Delka cest
        do
        {
            int m=inf;
            for (auto j=zasobnik.begin(); j!= zasobnik.end(); j++)
            {
                if (m>F[*j])
                {
                    m=F[*j];
                    i=*j;
                }
            }
            remove(zasobnik.begin(), zasobnik.end(), i);
            zasobnik.pop_back();

            cout << "i=" << i << ":   ";
            for (int j=0; j<pocet_krizovatek; j++)
            {
                if (F[j] > delka_cesty[i]+cestan[i][j] + sqrt(abs((souradnice[1][j] - souradnice[1][cil -1]))^2 + abs((souradnice[2][j] - souradnice[2][cil -1]))^2))
                {
                    delka_cesty[j] = delka_cesty[i]+cestan[i][j];
                    F[j] = delka_cesty[i]+cestan[i][j] + sqrt(abs((souradnice[1][j] - souradnice[1][cil -1]))^2 + abs((souradnice[2][j] - souradnice[2][cil -1]))^2);

                    postup_cesty[j] = krizovatky[i];
                }
                cout << delka_cesty[j] << ", ";
            }
            cout << endl << "F=  ";
            for (int j = 0; j < pocet_krizovatek; j++)
            {
                cout << F[j];
            }
            /*cout << endl;
            cout << "Zasobnik: ";
            print_vector(zasobnik);
            cout << endl;
            k++;
            cout <<"k= " << k << endl;*/
        }

        while (i!=(cil-1));
        cout << endl;

    //Vypis nejkratsich cest do vsech bodu
        for(int i=0; i<pocet_krizovatek; i++)
        {
            cout << postup_cesty[i] << "  ";
        }
        cout << endl;


    //Trasa cesty
        vector <int> trasa(1,krizovatky[cil-1]);
        while(!trasa.front()==0)
        {
            trasa.insert(trasa.begin(),postup_cesty[trasa.front()-1]);
        }

        cout << "Trasa: " ;
        for(int i=1; i<trasa.size(); i++)
        {
            cout << trasa[i] << " ";
        }
        cout << endl;

    //Delka trasy
        cout << "Delka trasy: " << delka_cesty[cil-1] << endl;
}
