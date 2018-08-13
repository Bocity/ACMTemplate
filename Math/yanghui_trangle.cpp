#include <iostream>
using namespace std;

int* returnArray(int N);
int main() {
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int *A = returnArray(i);
        for (int j = 0; j < i; j++) {
        cout << A[j];
        cout << "  ";
    }
        cout << endl;
    }   

}

int* returnArray(int N) {
    int *a = new int[N];
    if (N == 1) {
        a[0] = 1;
        return a;
    }
    else if(N == 2) {
        a[0] = 1;
        a[1] = 1;
        return a;
    }
    else {
        int* b = returnArray(N - 1);
        for (int i = 1; i < N - 1; i++) {
            a[i] = b[i] + b[i - 1];
        }
        a[0] = 1;
        a[N - 1] = 1;
        return a;
    }

}