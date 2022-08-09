/***
 * @author pengpenglang
 * @date: 2019-09-09
 * @info: 大一上 程序设计课（高级班） 排序算法上机实验
 */
#include <bits/stdc++.h>
using namespace std;

int n, arr[50005];  // the parameter about sequence
int b[50005];
int shift, compare;
clock_t start, finish;
double duration;

void menu();
void init();
void swap(int x, int y);
void Inline_sort();
void Half_sort();
void Twoway_sort();
void ShellInsert(int dlta[]);
void ShellSort(int dlta[], int t);
void Hill_sort();
void Bubble_sort1();
void Bubble_sort2();
void Bubble_sort3();
void Cocktail_sort();
void quicksort();
void Quick_sort();
void Simple_selection_sort();
void HeapAdjust(int s, int m);
void HeapSort();
void Heap_sort();
void Mergsort(int l, int r);
void Merge_sort();
void Gnome_sort();
void MSD_sort();
int maxbit();
void radixsort();
void LSD_sort();
void help();
void result();

int main() {
    menu();  // show the choice you want
    int choice;
    while (cin >> choice) {
        if (choice == 16) {
            help();
            cout << "Do you want to exit, if please press 'y', else another key:";
            char input;
            cin >> input;
            if (input == 'y') break;
            menu();
            continue;
        }
        cout << "There to ways to put in your data: 1--Manual entry   2--Importing files(Strictly follow the address:d://sortlist.txt)" << endl;
        cout << "your choice: ";
        int tot;
        cin >> tot;
        init();
        if (tot == 1) {
            cout << "You have selected sort, then please confirm the number of sequence you want to sort:";
            cin >> n;
            cout << "Now please commit the value of the sequence one by one:";
            for (int i = 1; i <= n; i++) cin >> arr[i];
        } else if (tot == 2) {
            ifstream file;
            file.open("d://sortlist.txt");
            int cnt = 1;
            if (!file) {
                cout << "[Error] Open file sucessfully!" << endl;
            }
            int temp;
            file >> n;
            for (int i = 1; i <= n; i++) {
                file >> arr[i];
            }
        } else {
            cout << "[Error] Don't have this choice." << endl;
        }
        switch (choice) {
            case 1:
                Inline_sort();
                break;
            case 2:
                Half_sort();
                break;
            case 3:
                Twoway_sort();
                break;
            case 4:
                Hill_sort();
                break;
            case 5:
                Bubble_sort1();
                break;
            case 6:
                Bubble_sort2();
                break;
            case 7:
                Bubble_sort3();
                break;
            case 8:
                Cocktail_sort();
                break;
            case 9:
                Quick_sort();
                break;
            case 10:
                Simple_selection_sort();
                break;
            case 11:
                Heap_sort();
                break;
            case 12:
                Merge_sort();
                break;
            case 13:
                Gnome_sort();
                break;
            case 14:
                MSD_sort();
                break;
            case 15:
                LSD_sort();
                break;
            defalt:
                cout << "[Error] Don't have this choice." << endl;
        }
        cout << endl;
        result();
        if (choice == 1 || choice == 2) {
            cout << "Do you want to find if a number in your array? If please press'y', else another key:";
            char key;
            cin >> key;
            if (key == 'y') {
                cout << "Choose the number you want to find in your array:";
                int temp;
                cin >> temp;
                bool flag = binary_search(arr + 1, arr + 1 + n, temp);  //�ж��Ƿ����
                if (flag)
                    cout << "The first number in your array is at Num." << lower_bound(arr + 1, arr + n + 1, temp) - arr - 1 << "." << endl;  //������һ�����ڵ���key��λ��
                else
                    cout << "Sorry, don't find the number in array." << endl;
            }
            cout << endl;
        }
        cout << "Do you want to exit, if please press 'y', else another key:";
        char input;
        cin >> input;
        if (input == 'y') break;
        menu();
    }
    cout << "Good bye ~" << endl;
    system("pause");
    return 0;
}

void init() {
    memset(arr, 0, sizeof arr);
    shift = 0, compare = 0;
}

void menu() {
    cout << "-------Welcome to using Sort Demo System------" << endl
         << "Please choose the_sort you want first         " << endl
         << "1--Inline_sort      2--Half_sort              " << endl
         << "3--Twoway_sort      4--Hill_sort              " << endl
         << "5--Bubble_sort1.0   6--Bubble_sort2.0         " << endl
         << "7--Bubble_sort3.0   8--Cocktail_sort          " << endl
         << "9--Quick_sort       10--Simple_selection_sort " << endl
         << "11--Heap_sort       12--Merge_sort            " << endl
         << "13--Gnome_sort      14--MSD_sort              " << endl
         << "15--LSD_sort        16--help&introduction     " << endl
         << "----------------------------------------------" << endl
         << endl;
    cout << "your choice:";
}

void swap(int x, int y) {
    arr[0] = arr[x];
    arr[x] = arr[y];
    arr[y] = arr[0];
}

void Inline_sort() {
    start = clock();
    for (int i = 2; i <= n; i++) {
        if (arr[i] <= arr[i - 1]) {
            arr[0] = arr[i];
            int j;
            for (j = i - 1; arr[0] < arr[j]; --j)
                arr[j + 1] = arr[j], shift++, compare++;
            arr[j + 1] = arr[0], shift++;
        }
    }
    finish = clock();
}

void Half_sort() {
    start = clock();
    for (int i = 2; i <= n; i++) {
        arr[0] = arr[i];
        int low = 1, high = i - 1, mid;
        while (low <= high) {
            mid = (low + high) / 2;
            if (arr[i] < arr[mid])
                high = mid - 1;
            else
                low = mid + 1;
            compare++;
        }
        for (int j = i - 1; j >= high; --j)
            arr[j + 1] = arr[j], shift++;
        arr[high + 1] = arr[0], shift++;
    }
    finish = clock();
}

void Twoway_sort() {
    start = clock();
    int T[n + 1];
    T[0] = arr[1];
    int first, last;
    first = last = 0;
    for (int i = 2; i <= n; i++) {
        if (arr[i] < T[first]) {
            first = (first - 1 + n) % n;
            T[first] = arr[i];
            shift++, compare++;
        } else if (arr[i] > T[last]) {
            last++;
            T[last] = arr[i];
            shift++, compare++;
        } else {
            last++;
            T[last] = T[last - 1];
            int j;
            for (j = last - 1; arr[i] < T[(j - 1) % n]; j = (j - 1 + n) % n)
                arr[j] = T[(j - 1 + n) % n], compare++;
            T[j] = arr[i], shift++;
        }
    }
    for (int i = 0; i < n; i++) {
        arr[i + 1] = T[first];
        first = (first + 1) % n;
    }
    finish = clock();
}

void ShellInsert(int k) {
    for (int i = k + 1; i <= n; i++) {
        compare++;
        if (arr[i] < arr[i - k]) {
            arr[0] = arr[i];
            int j;
            for (j = i - k; j > 0 && arr[0] < arr[j]; j -= k)
                arr[j + k] = arr[j], shift++;
            arr[j + k] = arr[0], shift++;
        }
    }
}

void ShellSort(int dlta[], int t) {
    for (int k = 0; k < t; k++)
        ShellInsert(dlta[k]);
}

void Hill_sort() {
    start = clock();
    int t = 4;
    int dlta[4] = {5, 3, 2, 1};
    ShellSort(dlta, t);
    finish = clock();
}

void Bubble_sort1() {
    start = clock();
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= n - i; j++) {
            compare++;
            if (arr[j] > arr[j + 1]) {
                shift++;
                swap(j, j + 1);
            }
        }
    }
    finish = clock();
}

void Bubble_sort2() {
    start = clock();
    bool flag = true;
    for (int i = 1; i < n && flag; i++) {
        flag = false;
        for (int j = 1; j < n; j++) {
            compare++;
            if (arr[j] > arr[j + 1]) {
                shift++;
                swap(j, j + 1);
                flag = true;
            }
        }
    }
    finish = clock();
}

void Bubble_sort3() {
    start = clock();
    int flag = n;
    for (int i = 1; i <= flag + 1; i++) {
        int k = flag;
        for (int j = 1; j < k; j++) {
            compare++;
            if (arr[j] > arr[j + 1]) {
                flag = j + 1;
                swap(j, j + 1);
                shift++;
            }
        }
    }
    finish = clock();
}

void Cocktail_sort() {
    start = clock();
    int bottom = 1, top = n;
    bool flag = true;
    int bound = 1;
    while (flag) {
        flag = false;
        for (int i = bottom; i < top; i++) {
            compare++;
            if (arr[i] > arr[i + 1]) {
                swap(i, i + 1);
                flag = true;
                bound = i;
                shift++;
            }
        }
        top = bound;
        for (int i = top; i > bottom; i--) {
            compare++;
            if (arr[i] < arr[i - 1]) {
                swap(i, i - 1);
                flag = true;
                bound = i;
                shift++;
            }
        }
        bottom = bound;
    }
    finish = clock();
}

void quicksort(int low, int high) {
    int i, j, key;
    if (low > high) return;
    i = low;
    j = high;
    key = arr[low];
    while (i != j) {
        while (j > i && arr[j] >= key) j--, compare++;
        while (i < j && arr[j] <= key) i++, compare++;
        if (i != j) {
            int middle = arr[i];
            arr[i] = arr[j];
            arr[j] = middle;
            shift++;
        }
    }
    arr[low] = arr[i], shift++;
    arr[i] = key, shift++;
    quicksort(low, i - 1);
    quicksort(i + 1, high);
}

void Quick_sort() {
    start = clock();
    quicksort(1, n);
    finish = clock();
}

void Simple_selection_sort() {
    start = clock();
    for (int i = 1; i <= n; i++) {
        int d = i;
        for (int j = i + 1; j <= n; j++) {
            compare++;
            if (arr[j] < arr[d])
                d = j;
        }
        compare++;
        if (d != i) {
            swap(d, i);
            shift++;
        }
    }
    finish = clock();
}

void HeapAdjust(int s, int m) {
    arr[0] = arr[s];
    for (int j = 2 * s; j <= m; j *= 2) {
        if (j < m && arr[j] < arr[j + 1]) j++, compare++;
        if (arr[0] >= arr[j]) {
            compare;
            break;
        }
        arr[s] = arr[j];
        s = j;
    }
    arr[s] = arr[0];
}

void HeapSort() {
    for (int i = n / 2; i > 0; i--)
        HeapAdjust(i, n);
    for (int i = n; i > 1; i--) {
        swap(1, i);
        HeapAdjust(1, i - 1);
        shift++;
    }
}

void Heap_sort() {
    start = clock();
    HeapSort();
    finish = clock();
}

void Mergesort(int l, int r) {
    if (l == r) return;
    int m = (l + r) / 2;
    Mergesort(l, m);
    Mergesort(m + 1, r);
    int lp = l, rp = m + 1, s = 0;
    while (lp <= m && rp <= r) {
        if (arr[lp] < arr[rp]) b[s++] = arr[lp++], compare++;
        if (arr[lp] > arr[rp]) b[s++] = arr[rp++], compare++;
    }
    while (lp <= m) b[s++] = arr[lp++];
    while (rp <= r) b[s++] = arr[rp++];
    for (int i = l; i <= r; i++) arr[i] = b[i - l];
}

void Merge_sort() {
    start = clock();
    Mergesort(1, n);
    finish = clock();
}

void Gnome_sort() {
    start = clock();
    int i = 0;
    while (i <= n) {
        if (i == 0 || arr[i] >= arr[i - 1])
            i++, compare++;
        else {
            swap(i, i - 1);
            shift++;
            i--;
        }
    }
    finish = clock();
}

void MSD_sort() {
    start = clock();
    int bucket[10001];
    memset(bucket, 0, sizeof bucket);
    for (int i = 1; i <= n; i++)
        bucket[arr[i]]++;
    memset(arr, 0, sizeof arr);
    int cnt = 1;
    for (int i = 0; i < 10001; i++) {
        while (bucket[i]) {
            arr[cnt++] = i;
            bucket[i]--;
        }
    }
    finish = clock();
}

int maxbit() {
    int maxData = arr[1];
    for (int i = 2; i <= n; i++) {
        if (maxData < arr[i])
            maxData = arr[i], compare++;
    }
    int d = 1;
    int p = 10;
    while (maxData >= p) {
        maxData /= 10;
        ++d;
    }
    return d;
}

void radixsort() {
    int d = maxbit();
    int *tmp = new int[n + 10];
    int *count = new int[10];
    int i, j, k;
    int radix = 1;
    for (i = 1; i <= d; i++) {
        for (j = 0; j < 10; j++)
            count[j] = 0;
        for (j = 1; j <= n; j++) {
            k = (arr[j] / radix) % 10;
            count[k++];
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j];
        for (j = n; j >= 1; j--) {
            k = (arr[j] / radix) % 10;
            tmp[count[k] - 1] = arr[j];
            count[k]--;
        }
        for (j = 1; j <= n; j++)
            arr[j] = tmp[j];
        radix = radix * 10;
    }
    delete[] tmp;
    delete[] count;
}

void LSD_sort() {
    start = clock();
    radixsort();
    finish = clock();
}

void help() {
    cout << "==============================   Help  ===============================" << endl
         << "1.This system sets the maximum number of sequences to 50000.          " << endl
         << "2.After every sort system will ask if you want exit.                  " << endl
         << "3.The number supported for MSD_sort&LSD_sort is between 0 and 10,000." << endl
         << "4.Other question please read the introduction.md                      " << endl
         << "5.The numbers of sortlist.txt must beseparated by a space / carriage  " << endl
         << "6.The number found in the search algorithm starts from the 0th bit    " << endl
         << "======================================================================" << endl
         << endl;
}

void result() {
    cout << "The calculation ends, and the sorting sequence is as follows:" << endl;
    cout << "Number of comparations:" << compare << endl;
    cout << "Number of exchanges:" << shift << endl;
    cout << "Ascending sequence is as follows:" << endl;
    for (int i = 1; i <= n; i++) {
        cout << setw(10) << arr[i];
        if (i == 10) cout << endl;
    }
    cout << endl;
    cout << "The time it takes to execute the algorithm:" << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
    cout << endl;
}
