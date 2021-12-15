#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <sstream>

using namespace std;

int IntInput (string text, string repeat, int min_input, int max_input)
{
	int input;
	string text_input;
	cout << text << endl;
	while (cin >> text_input)
	{
		istringstream s(text_input);
		s >> input;
		if (input > min_input && input <= max_input)
			break;
		cout << text << " " << repeat << endl;
	}
	cout << endl;
	return input;
}

int Minimum (vector <int>& zasobnik, vector <int> delka, int inf, int&i)
{
    int m=inf;
    for (auto j=zasobnik.begin(); j!= zasobnik.end(); j++)
    {
        if (m>delka[*j])
        {
            m=delka[*j];
            i=*j;
        }
    }
    remove(zasobnik.begin(), zasobnik.end(), i);
    zasobnik.pop_back();
    return i;
}

void Dijkstra (int& i, vector<vector<int>> vzdalenost, int pocet_krizovatek, vector<int>& delka_cesty, vector<int> krizovatky, vector<int>& postup_cesty, vector <int>& zasobnik, int inf)
{
    Minimum(zasobnik, delka_cesty, inf, i);

    for (int j=0; j<pocet_krizovatek; j++)
    {
        if (delka_cesty[j] > delka_cesty[i]+vzdalenost[i][j])
        {
            delka_cesty[j] = delka_cesty[i]+vzdalenost[i][j];
            postup_cesty[j] = krizovatky[i];
        }
    }
}

void AStar(int& i, vector<vector<int>> vzdalenost, vector<vector<int>> souradnice, int pocet_krizovatek, vector<int>& delka_cesty, vector<int> krizovatky, vector<int>& postup_cesty, vector<int>& F, int cil, vector <int>& zasobnik, int inf)
{
    Minimum(zasobnik, F, inf, i);

    for (int j=0; j<pocet_krizovatek; j++)
    {
        int h = sqrt((abs(souradnice[0][j] - souradnice[0][cil-1]))^2 + (abs(souradnice[1][j] - souradnice[1][cil-1]))^2);
        if (F[j] > delka_cesty[i]+vzdalenost[i][j] + h)
        {
            delka_cesty[j] = delka_cesty[i]+vzdalenost[i][j];
            F[j] = delka_cesty[i]+vzdalenost[i][j] + h ;
            postup_cesty[j] = krizovatky[i];
        }
    }
}

void Algorithm (vector<vector<int>> vzdalenost, vector<vector<int>> souradnice, int start, int cil, int inf, int b)
{
	int pocet_krizovatek=vzdalenost.size();
	int i;
	vector <int> delka_cesty(pocet_krizovatek, inf);
	vector <int> postup_cesty(pocet_krizovatek, inf);
	vector <int> F(pocet_krizovatek, inf);
	vector <int> krizovatky(pocet_krizovatek);
	vector <int> zasobnik(pocet_krizovatek);
	for (int i=0; i<pocet_krizovatek; i++)
	{
		krizovatky[i]=i+1;
		zasobnik[i]=i;
	}
	delka_cesty[start-1]=0;
	postup_cesty[start-1]=0;
	F[start-1]=0;

	do
	{
		if (b==1) { AStar(i, vzdalenost, souradnice, pocet_krizovatek, delka_cesty, krizovatky, postup_cesty, F, cil, zasobnik, inf); }
		else { Dijkstra(i, vzdalenost, pocet_krizovatek, delka_cesty, krizovatky, postup_cesty, zasobnik, inf); }
	}
	while (i!=cil-1);

	vector <int> trasa(1,krizovatky[cil-1]);
	while(!trasa.front()==0) { trasa.insert(trasa.begin(),postup_cesty[trasa.front()-1]); }

	ofstream f;
	f.open("edges.dat", ios_base::app);
	for (int i = 0; i < vzdalenost[0].size(); ++i) {
		for (int j = 0; j < vzdalenost[0].size(); ++j) {
			if (j < i || vzdalenost[i][j] == inf)
				continue;
			for (int k = 0; k < 2; ++k) {
				f << souradnice[0][(k) ? j : i] + ((b==2) ? *max_element(souradnice[0].begin(), souradnice[0].end()) : 0) << " " << souradnice[1][(k) ? j : i] - ((b==2) ? *max_element(souradnice[1].begin(), souradnice[1].end()) : 0) << " ";
				bool found = false;
				for (int l = 1; l < trasa.size(); ++l) {
					if (trasa[l-1]-1 == i && trasa[l]-1 == j || trasa[l-1]-1 == j && trasa[l]-1 == i)
						found = true;
				}
				if (found)
					f << 2 << endl;
				else
					f << 1 << endl;
			}
			f << endl;
		}
	}
	f.close();

	cout << "Trasa: " ;
	for(int i=1; i<trasa.size(); i++)
	{
		cout << trasa[i] << " ";
	}
	cout << endl;
	cout << "Delka trasy: " << delka_cesty[cil-1] << " km" << endl << endl;
}
int main()
{
	remove("edges.dat");
	int start, cil, a;
	int inf=1000000;
	vector<vector<int>> vzdalenost =   {{inf,   inf,    inf,    95,     110,    inf,    147,    115,    91,     124,    inf,    128,    127},
										{inf,   inf,    inf,    inf,    inf,    79,     inf,    inf,    inf,    inf,    96,     89,     inf},
										{inf,   inf,    inf,    inf,    inf,    92,     inf,    244,    inf,    inf,    123,    inf,    inf},
										{95,    inf,    inf,    inf,    inf,    inf,    134,    inf,    inf,    inf,    inf,    inf,    82},
										{110,   inf,    inf,    inf,    inf,    inf,    inf,    97,     92,     inf,    inf,    inf,    inf},
										{inf,   79,     92,     inf,    inf,    inf,    inf,    141,    inf,    inf,    65,     inf,    inf},
										{147,   inf,    inf,    134,    inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf},
										{115,   inf,    244,    inf,    97,     141,    inf,    inf,    inf,    23,     inf,    inf,    inf},
										{91,    inf,    inf,    inf,    92,     inf,    inf,    inf,    inf,    inf,    inf,    inf,    119},
										{124,   inf,    inf,    inf,    inf,    inf,    inf,    23,     inf,    inf,    inf,    inf,    inf},
										{inf,   96,     123,    inf,    inf,    65,     inf,    inf,    inf,    inf,    inf,    inf,    inf},
										{128,   89,     inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf,    inf},
										{127,   inf,    inf,    82,     inf,    inf,    inf,    inf,    119,    inf,    inf,    inf,    inf}};
	vector<vector<int>> souradnice =   {{92,    170,    229,    53,     114,    193,    93,     142,    78,     140,    208,    134,    35},
										{86,    37,     75,     67,     126,    59,     25,     94,     119,    84,     39,     51,     95}};

	do
	{
		cout << "Praha - 1" << endl << "Brno - 2" << endl << "Ostrava - 3" << endl << "Plzen - 4" << endl << "Liberec - 5" << endl
		<< "Olomouc - 6" << endl << "Ceske Budejovice - 7" << endl << "Hradec Kralove - 8" << endl << "Usti nad Labem - 9" << endl
		<< "Pardubice - 10" << endl << "Zlin - 11" << endl << "Jihlava - 12" << endl << "Karlovy Vary - 13" << endl << endl;

		start = IntInput ("Zadejte start", "znovu", 0, vzdalenost.size());
		cil = IntInput ("Zadejte cil", "znovu", 0, vzdalenost.size());

		if(start == cil)
		{
		cout << "Uz jste v cili." << endl << endl;
		}
		else
		{
		   cout << "A Star:" << endl;
		   Algorithm(vzdalenost, souradnice, start, cil, inf, 1);
		   cout << "Dikstra:" << endl;
		   Algorithm(vzdalenost, souradnice, start, cil, inf, 2);
		}
	}
	while(IntInput("Chcete zadat dalsi trasu? [1/0] ", "", -1, 1));

	return 0;
}
