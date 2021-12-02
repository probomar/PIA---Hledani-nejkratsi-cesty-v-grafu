#include <iostream>
#include "dijsktra.h"


using namespace std;

int main()
{
    int start, cil, a;

    int cesty[13][13]={ {0,0,0,1,1,0,1,1,1,1,0,1,1},
                        {0,0,0,0,0,1,0,0,0,0,1,1,0},
                        {0,0,0,0,0,1,0,1,0,0,1,0,0},
                        {1,0,0,0,0,0,1,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,1,1,0,0,0,0},
                        {0,1,1,0,0,0,0,1,0,0,1,0,0},
                        {1,0,0,1,0,0,0,0,0,0,0,0,0},
                        {1,0,1,0,1,1,0,0,0,1,0,0,0},
                        {1,0,0,0,1,0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,1,0,0,0,0,0},
                        {0,1,1,0,0,1,0,0,0,0,0,0,0},
                        {1,1,0,0,0,0,0,0,0,0,0,0,0},
                        {1,0,0,1,0,0,0,0,1,0,0,0,0}};

    int vzdalenost[13][13]={{0,0,0,95,110,0,147,115,91,124,0,128,127},
                            {0,0,0,0,0,79,0,0,0,0,89,96,0},
                            {0,0,0,0,0,92,0,244,0,0,123,0,0},
                            {95,0,0,0,0,0,134,0,0,0,0,0,82},
                            {110,0,0,0,0,0,0,97,92,0,0,0,0},
                            {0,79,92,0,0,0,0,141,0,0,65,0,0},
                            {147,0,0,134,0,0,0,0,0,0,0,0,0},
                            {115,0,244,0,97,141,0,0,0,23,0,0,0},
                            {91,0,0,0,92,0,0,0,0,0,0,0,119},
                            {124,0,0,0,0,0,0,23,0,0,0,0,0},
                            {0,96,123,0,0,65,0,0,0,0,0,0,0},
                            {128,89,0,0,0,0,0,0,0,0,0,0,0},
                            {127,0,0,95,0,0,0,0,119,0,0,0,0}};

    int souradnice[2][13]={ {92,170,229,53,114,193,93,142,78,140,208,134,35},
                            {86,37,75,67,126,59,25,94,119,84,39,51,95}};
    do
    {
        cout << "Praha - 1" <<endl <<"Brno - 2" <<endl <<"Ostrava - 3" <<endl <<"Plzen - 4" <<endl <<"Liberec - 5" <<endl <<"Olomouc - 6" <<endl <<"Ceske Budejovice - 7" <<endl <<"Hradec Kralove - 8" <<endl <<"Usti nad Labem - 9" <<endl <<"Pardubice - 10" <<endl <<"Zlin - 11" <<endl <<"Jihlava - 12" <<endl <<"Karlovy Vary - 13" <<endl;

        cout << endl << "Zadejte start." <<endl;
        cin >> start;

        while(start < 1 || start > 13)
        {
            cout << endl << "Zadejte start znovu" << endl;
            cin >> start;
        }

        cout << endl << "Zadejte cil." <<endl;
        cin >> cil;

        while(cil < 1 || cil > 13)
        {
            cout << endl << "Zadejte cil znovu" << endl;
            cin >> cil;
        }

        while(start == cil)
        {
            cin.ignore(1000, '\n');
            cout << endl << "Uz jste v cili."<<endl;
        }

    //Dijkstra
        DijsktraAlgorithm(vzdalenost, start, cil);

    //A*

        cout << endl << "Chcete zadat dalsi trasu? 1/0" <<endl;
        cin >> a;
    }
    while(a == 1);

    return 0;
}
