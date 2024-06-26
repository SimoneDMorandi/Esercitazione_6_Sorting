#include <SortingAlgorithm.hpp>
#include <iostream>
#include <chrono>
#include<vector>
#include <numeric>
#include <iomanip>

using namespace std;
using namespace SortLibrary;

/* Definisco la funzione che calcola il tempo di esecuzione degli algoritmi di ordinamento per i due vettori
   identici e ne restituisce la durata in un vettore di due componenti.*/
vector<double> ComputeTime(vector<int> & vector_bs, vector<int> & vector_ms)
{
    vector<double> duration(2);

    // Calcolo il tempo di esecuzione di BubbleSort.
    chrono::steady_clock::time_point t_begin_bs = chrono::steady_clock::now();
    BubbleSort(vector_bs);
    chrono::steady_clock::time_point t_end_bs = chrono::steady_clock::now();
    double duration_bs = chrono::duration_cast<chrono::nanoseconds>(t_end_bs-t_begin_bs).count();

    // Calcolo il tempo di esecuzione di MergeSort.
    chrono::steady_clock::time_point t_begin_ms = chrono::steady_clock::now();
    MergeSort(vector_ms);
    chrono::steady_clock::time_point t_end_ms = chrono::steady_clock::now();
    double duration_ms = chrono::duration_cast<chrono::nanoseconds>(t_end_ms-t_begin_ms).count();

    duration[0] = duration_bs;
    duration[1] = duration_ms;

    return duration;
}

int main()
{
    /* Definisco il numero di iterazioni su cui verrà fatta la media dei tempi
       e la grandezza, sufficientemente grande, del vettore.*/


    // Richiedo la dimensione del vettore di grandi dimensioni.
    unsigned int N;
    cout << "Inserire la dimensione del vettore, sufficientemente grande." << endl;;
    cin >> N;

    // Richiedo la dimensione del vettore di piccole dimensioni.
    unsigned int s;
    cout << "Inserire la dimensione del vettore, sufficientemente piccola." << endl;
    cin >> s;

    // Definisco la precisione con cui verrano stampati i risultati.
    cout << fixed << setprecision(0);

    /* Tutti i test saranno eseguiti allo stesso modo:
       Si generano N vettori di un tipo, per ciascuno si crea una copia,
       si calcola per ugnuno il tempo necessario per ordinarlo rispettivamente con i due metodi,
       poi si calcola la media dei tempi e si comparano i risultati.
       Ciò che cambia da un test all'altro è l'inizializzione dei vettori.*/


    // Test 1 : Vettore ordinato.

    // Inizializzo le variabili che conterranno la media dei tempi.
    double mean_bs = 0;
    double mean_ms = 0;

    cout << "Test 1: Vettore ordinato." << endl;
    for(unsigned int j = 0; j < N; j++)
    {
        // Definisco i vettori ordinati.

        vector<int> vector_bs(N);
        iota(vector_bs.begin(),vector_bs.end(),0);

        // Definisco una copia del vettore, in modo da passare ai due algoritmi lo stesso oggetto.
        vector<int> vector_ms = vector_bs;

        // Calcolo il tempo di esecuzione.
        vector<double> duration = ComputeTime(vector_bs,vector_ms);

        // Aggiungo i valori al totale.
        mean_bs += duration[0];
        mean_ms += duration[1];
    }

    // Comparo i risultati:
    // Mi aspetto che BubbleSort sia più veloce di MergeSort.
    cout << "Tempo medio per BubbleSort: " << mean_bs/N << "ns" << endl;
    cout << "Tempo medio per MergeSort: " << mean_ms/N << "ns" << endl;
    if(mean_bs < mean_ms)
    {
        cout << "BubbleSort vince." << endl << endl;
    }
    else
    {
        cerr << "MergeSort vince." << endl << endl;
    }

    // Test 2 : Vettore parzialmente ordinato.

    mean_bs = 0;
    mean_ms = 0;

    // Definisco il seed per la funzione rand(), in modo da non generare sempre gli stessi numeri.
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "Test 2: Vettore parzialmente ordinato." << endl;
    for(unsigned int j = 0; j < N; j++)
    {
        // Definisco i vettori ordinati fino a metà della loro lunghezza.
        vector<int> vector_bs(N);
        iota(vector_bs.begin(),vector_bs.begin() + N/2 ,0);
        for(unsigned int i = N-1; i > N/2 -1; i--)
        {
            vector_bs[i] = (rand() % N) +N/2;  // Genero numeri casuali tra N/2 ed N.
        }
        vector<int> vector_ms = vector_bs;

        vector<double> duration = ComputeTime(vector_bs,vector_ms);
        mean_bs += duration[0];
        mean_ms += duration[1];
    }

    // Comparo i risultati:
    // Mi aspetto che MergeSort sia più veloce di BubbleSort.
    cout << "Tempo medio per BubbleSort: " << mean_bs/N << "ns" << endl;
    cout << "Tempo medio per MergeSort: " << mean_ms/N << "ns" << endl;
    if(mean_bs < mean_ms)
    {
        cerr << "BubbleSort vince." << endl << endl;
    }
    else
    {
        cout << "MergeSort vince." << endl << endl;
    }

    // Test 3 : Vettore non ordinato.

    mean_bs = 0;
    mean_ms = 0;

    cout << "Test 3: Vettore non ordinato." << endl;
    for(unsigned int j = 0; j < N; j++)
    {
        // Definisco i vettori casuali.
        vector<int> vector_bs(N);
        for(unsigned int i = 0; i < N; i++)
        {
            vector_bs[i] = rand() % N;
        }
        vector<int> vector_ms = vector_bs;

        vector<double> duration = ComputeTime(vector_bs,vector_ms);
        mean_bs += duration[0];
        mean_ms += duration[1];
    }

    // Comparo i risultati:
    // Mi aspetto che MergeSort sia molto più veloce di Bubblesort.
    cout << "Tempo medio per BubbleSort: " << mean_bs/N << "ns" << endl;
    cout << "Tempo medio per MergeSort: " << mean_ms/N << "ns" << endl;
    if(mean_bs < mean_ms)
    {
        cerr << "BubbleSort vince." << endl << endl;
    }
    else
    {
        cout << "MergeSort vince." << endl << endl;
    }

    // Test 4 : Vettore decrescente.

    mean_bs = 0;
    mean_ms = 0;

    cout << "Test 4: Vettore decrescente." << endl;
    for(unsigned int j = 0; j < N; j++)
    {
        // Definisco i vettori decrescenti.
        vector<int> vector_bs(N);
        iota(vector_bs.rbegin(), vector_bs.rend(), 0);
        vector<int> vector_ms = vector_bs;

        vector<double> duration = ComputeTime(vector_bs,vector_ms);
        mean_bs += duration[0];
        mean_ms += duration[1];
    }

    // Comparo i risultati:
    // Mi aspetto che MergeSort sia molto più veloce di Bubblesort.
    cout << "Tempo medio per BubbleSort: " << mean_bs/N << "ns" << endl;
    cout << "Tempo medio per MergeSort: " << mean_ms/N << "ns" << endl;
    if(mean_bs < mean_ms)
    {
        cerr << "BubbleSort vince." << endl << endl;
    }
    else
    {
        cout << "MergeSort vince." << endl << endl;
    }

    // Test 5 : Vettore decrescente di piccole dimensioni.

    mean_bs = 0;
    mean_ms = 0;

    cout << "Test 5: Vettore decrescente di piccole dimensioni." << endl;
    for(unsigned int j = 0; j < N; j++)
    {
        // Definisco i vettori decrescenti.
        vector<int> vector_bs(s);
        iota(vector_bs.rbegin(), vector_bs.rend(), 0);
        vector<int> vector_ms = vector_bs;

        vector<double> duration = ComputeTime(vector_bs,vector_ms);
        mean_bs += duration[0];
        mean_ms += duration[1];
    }

    // Comparo i risultati:
    // Mi aspetto che Bubblesort sia più veloce di MergeSort.
    cout << "Tempo medio per BubbleSort: " << mean_bs/N << "ns" << endl;
    cout << "Tempo medio per MergeSort: " << mean_ms/N << "ns" << endl;
    if(mean_bs < mean_ms)
    {
        cout << "BubbleSort vince." << endl << endl;
    }
    else
    {
        cerr << "MergeSort vince." << endl << endl;
    }

    return 0;
}
