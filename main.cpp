#define _CRT_RAND_S
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <random>
#include <ctime>
#include <iomanip>
using namespace std;

void ascending_sort (int *arr, int grille_sz);
void fill_arr(int *lot, int num);
void check_duplicates (int *lot, int num);
int elementReinit(int el);

template <class T>
void ascending_sort (T *arr, int grille_sz);

int main() {//LOTO sur FDJ.COM

	int i;
    int cnt{0};
    time_t current = time(nullptr);
    char* seedTime = ctime(&current);

    fstream seedsFile;
    seedsFile.open("lotoResults.txt", ios::out | ios::app);
    if (seedsFile.is_open()) {
        seedsFile << seedTime;
    }
    else {
        cout << "ERROR. Could not create file!" << endl;
        cout << "Current results will not be stored on drive." << endl;
    }

    const int num = 5; //numbers quant(6 in LOTO)
	const int lots = 3; //numbers of seeds +1 for the average results
	int lot[num+1];
    double lucky[num+1]{0};


    while(cnt<lots) {
        fill_arr(lot, num);
        check_duplicates(lot,num);
        ascending_sort(lot, num);


        cout << "seed #" << cnt << ':' << endl;
        seedsFile << "\nseed #" << cnt << ':' << endl;
        for (i = 0; i <= num; i++) {
            lucky[i]+=lot[i];
            cout << lot[i] << ' ';
            seedsFile << lot[i] << ' ';
        }
        cout << endl;

        ++cnt;
    }

    for (i = 0; i <= num; i++) {
        lucky[i]/=lots;
    }
    ascending_sort(lucky, num);

    cout << "Result array: " << '\n';
    seedsFile << "\nResult array:\n";
	for (i = 0; i <= num; i++) {
        seedsFile << lucky[i] << ' ';
        cout << setprecision(2) << lucky[i]<< ' ';
    }

    seedsFile << '\n' << "-------" << endl;
    seedsFile.close();

	return 0;
}

void ascending_sort (int *arr, int grille_sz) {

    bool sorted{false};

    while (!sorted) {
        sorted = true;
        for (int i = 1; i < grille_sz; ++i) {
            if (arr[i - 1] > arr[i]) {
                int tmp = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = tmp;
                sorted = false;
            }
        }
    }

}

void fill_arr(int *lot, int num) {
    int j;
    errno_t         err;
    unsigned int    number;

    // Fill 5 random integers in the range [ 1,49 ] (Grille 1).
    for (j = 0; j < num; j++) {
        err = rand_s(&number);

        sleep((unsigned int) ((double) number /
                              ((double) UINT_MAX + 1) * 5.0) + 1);

        if (err != 0) {
            cout << "Error in random number generating" << endl;
        }
        lot[j] = (unsigned int) ((double) number /
                                 ((double) UINT_MAX + 1) * 49.0) + 1;
    }//j



    // Fill last "chance" random integer in the range [ 1,10 ].
    err = rand_s(&number);
    if (err != 0) {
        cout << "Error in random number generating" << endl;
    }
    lot[num] = (unsigned int) ((double) number /
                                ((double) UINT_MAX + 1) * 10.0) + 1;

}

int elementReinit(int el) {
    errno_t         err;
    unsigned int    number;

    err = rand_s(&number);
    sleep((unsigned int) ((double) number /
                              ((double) UINT_MAX + 1) * 6.0) + 1);

    if (err != 0) {
            cout << "Error in random number generating" << endl;
        }
    el = (unsigned int) ((double) number /
                                 ((double) UINT_MAX + 1) * 49.0) + 1;

    return el;
}


void check_duplicates(int *lot, int num) {

    bool isDuplicates{false};
    do {
        isDuplicates = false;
        for (int i = 0; i < num; ++i) {
            for (int j = num - 1; j <= 0; --j) {
                if (lot[i] == lot[j] && i != j) {
                    lot[i] = elementReinit(lot[i]);
                    isDuplicates = true;
                }
            }
        }
    } while(isDuplicates);
}

template<class T>
void ascending_sort(T *arr, int grille_sz) {

    bool sorted{false};

    while (!sorted) {
        sorted = true;
        for (int i = 1; i < grille_sz; ++i) {
            if (arr[i - 1] > arr[i]) {
                int tmp = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = tmp;
                sorted = false;
            }
        }
    }

}
