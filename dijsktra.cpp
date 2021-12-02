#include "dijsktra.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void DijsktraAlgorithm(int vzdalenost[13][13], int start, int cil)
{
    /*for (int i=0; i<13; i++)
    {
        for(int j=0; j<13; j++)
        {
            cout << vzdalenost[i][j] << " ";
        }
        cout << endl;
    }*/

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

        /*for(int i=0; i<pocet_krizovatek; i++)
        {
            cout << delka_cesty[i] <<", ";
        }
        cout << endl << endl;*/

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
            if (m>delka_cesty[*j])
            {
                m=delka_cesty[*j];
                i=*j;
            }
        }
        remove(zasobnik.begin(), zasobnik.end(), i);
        zasobnik.pop_back();

            //cout << "i=" << i << ":   ";
        for (int j=0; j<pocet_krizovatek; j++)
        {
            if (delka_cesty[j] > delka_cesty[i]+cestan[i][j])
            {
                delka_cesty[j] = delka_cesty[i]+cestan[i][j];
                postup_cesty[j] = krizovatky[i];
            }
                //cout << delka_cesty[j] << ", ";
        }
            /*cout << endl;
            cout << "Zasobnik: ";
            print_vector(zasobnik);
            cout << endl;
            k++;
            cout <<"k= " << k << endl;*/
    }
    while (i!=cil);
        //cout << endl;

    //Vypis nejkacich cest do vsech bodu
        /*for(int i=0; i<pocet_krizovatek; i++)
        {
            cout << postup_cesty[i] << "  ";
        }
        cout << endl;*/

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


