#include <iostream>
#include <bits/stdc++.h>

// RadixSort, MergeSort, ShellSort, CountSort, QuickSort
using namespace std;
using namespace std::chrono;
ifstream in("sortari.in");
ofstream out("sortari.out");
int vr[10000005], copie_vr[10000005], fr[10000005],aux[10000005];

//mergesort
void Interclasare(int *v, int s, int m, int d)
{
    int i, j, k;
    i = s;
    j = m + 1;
    k = 0;
    while (i <= m && j <= d)
        if (v[i] < v[j])
            aux[++k] = v[i++];
        else
            aux[++k] = v[j++];
    while (i <= m)
        aux[++k] = v[i++];
    while (j <= d)
        aux[++k] = v[j++];
    k = 0;
    for (i = s; i <= d; i++)
        v[i] = aux[++k];
}
void MergeSort(int v[], int s, int d)
{

 if (s < d)
    {
        int m = (s + d) / 2;
        MergeSort(v, s, m);
        MergeSort(v, m + 1, d);
        Interclasare(v, s, m, d);
    }
}

void ShellSort(int v[], int n)
{
for (int gap = n/2; gap > 0; gap /= 2)
    {

        for (int i = gap; i < n; i += 1)
        {

            int temp = v[i];

            int j;
            for (j = i; j >= gap && v[j - gap] > temp; j -= gap)
                v[j] = v[j - gap];

            v[j] = temp;
        }
    }

}

void CountSort(int v[], int n)
{
    int maxi = v[0];

    for (int i = 1; i < n; i++)
    {
        if (v[i] > maxi)
            maxi = v[i];
    }

    for (int i = 0; i <= maxi; ++i)
    {
        fr[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        fr[v[i]]++;
    }
    for (int i = 1; i <= maxi; i++)
    {
        fr[i] += fr[i - 1];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        aux[fr[v[i]] - 1] = v[i];
        fr[v[i]]--;
    }
    for (int i = 0; i < n; i++)
    {
        v[i] = aux[i];
    }

}
//radix cu count la baza
int Maxim(int v[], int n)
{
    int maxi = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] > maxi)
            maxi = v[i];
    return maxi;
}

void CountSortRadix(int v[], int n, int exp)
{
    int i, numara[10] = {0};

    for (i = 0; i < n; i++)
        numara[(v[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        numara[i] += numara[i - 1];

    for (i = n - 1; i >= 0; i--)
    {
        aux[numara[(v[i] / exp) % 10] - 1] = v[i];
        numara[(v[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        v[i] = aux[i];
}

void radixsort(int v[], int w[], int n)
{
    int m = Maxim(v, n);

    for (int exp = 1; m / exp > 0; exp *= 10)
        CountSortRadix(v, n, exp);
}

//quick sort
int poz(int v[],int lft, int rgh)
{
    int x = v[rgh], i = lft, j;
    for (j = lft; j <= rgh - 1; j++)
        if (v[j] <= x)
        {
            swap(v[i], v[j]);
            i++;
        }
    swap(v[i], v[rgh]);
    return i;
}

void QuickSort(int v[],int lft, int rgh)
{
  if (lft<rgh)
    {
        int i=poz(v,lft,rgh);
        QuickSort(v,lft, i-1);
        QuickSort(v,i+1, rgh);
    }

}

void copie(int v[], int w[], int n)
{
    for (int i = 0; i < n; i++)
        v[i] = w[i];
}
bool sortare(int v[], int n)
{
      for (int i = 0; i < n - 1; i++)
        if (v[i] > v[i + 1])
            return false;
    return true;
}
int getRandomNumber(int min, int max)
{
    static constexpr double fraction { 1.0 / (RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}
int main()
{

    int n,nr_max,nrteste;
    out<<"Numarul de teste efectuate: ";
    in>> nrteste;
    out<<nrteste<<endl;


    for(int i=1; i<=nrteste; ++i)
    {


        in>>n;
        out << "Vom sorta "<< n <<" numere"<<endl;

        in >> nr_max;
        out << "Numarul maxim este: "<< nr_max<<endl;

        for(int j = 0; j< n; ++j)
        {
            vr[j] = getRandomNumber(0, nr_max);
            copie_vr[j] = vr[j];
        }

        out <<'\n';
        auto start = high_resolution_clock::now();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        ///ShellSOrt
        start = high_resolution_clock::now();
        ShellSort(vr, n );
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        out << "ShellSort:  " << duration.count() / 1000 << " milisecunde.  Sortare corecta (1 / 0): "
             << sortare(vr, n) << "\n";
        copie(vr, copie_vr, n);

         ///MergeSort

        start = high_resolution_clock::now();
        MergeSort(vr, 0, n - 1);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        out << "MergeSort:  " << duration.count() / 1000 << " milisecunde.  Sortare corecta (1 / 0): "
             << sortare(vr, n) << "\n";
        copie(vr, copie_vr, n);


        ///CountSort

        if(nr_max<=1000000)
        {
            start = high_resolution_clock::now();
            CountSort(vr, n);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);

            out << "CountSort a fost efectuat in "<< duration.count() / 1000 << " milisecunde. Sortare corecta (1 / 0): " << sortare(vr, n) << '\n';
            copie(vr, copie_vr, n);
        }
        else
        {
            out<<"A fost depasita limita de 1000000 de numere pentru CountSort\n";
        }

        ///RadixSort

        start = high_resolution_clock::now();
        radixsort(vr, aux, n);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        out << "RadixSort  " << duration.count() / 1000 << " milisecunde. Sortare corecta (1 / 0): "
             << sortare(vr, n) << "\n";
        copie(vr, copie_vr, n);

        ///QuickSort

        start = high_resolution_clock::now();
        QuickSort(vr,0, n - 1);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        out << "QuickSort " << duration.count() / 1000 << " milisecunde. Sortare corecta (1 / 0):"<< sortare(vr, n) << "\n";
        copie(vr, copie_vr, n);

        out<<'\n';

    }


    return 0;
}
