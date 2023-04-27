#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void PrintArray(std::vector<int>& array) {
    for (int i = 0; i < array.size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void HeapSort(std::vector<int>& array) {
    if (array.size() <= 1) return;
    int len = array.size();
    vector <int> tmp, ans;
    tmp.push_back(NULL);
    for (int i = 0; i < len; i++)     tmp.push_back(array[i]);
    //cout << tmp.size() << endl;
    for (int r = 0; r < array.size(); r++) {
        int l = tmp.size() - 1-r;
        for (int i = l; i > 1; i--) {
            if (tmp[l] > tmp[l / 2]) {
                int temp = tmp[l];
                tmp[l] = tmp[l / 2];
                tmp[l / 2] = temp;
            }
            l--;
        }
        ans.push_back(tmp[1]);
        for (int j = 1; j < tmp.size()-1; j++) {
            tmp[j] = tmp[j + 1];
        }
    }
    for (int i = 0; i < ans.size(); i++) {
        array[ans.size()-i-1] = ans[i];
    }
}

void QuickSort(vector<int>& array) {
    vector <int> tmp,left,right;
    if (array.size() <= 1) return;
    int pi = 0, p = array[0],len=array.size();
    for (int i = 1; i < len; i++) {
        if (array[i] < p)
            left.push_back(array[i]);
        else if (array[i] >= p)
            right.push_back(array[i]);
    }
    QuickSort(left);
    QuickSort(right);
    int temp = 0;
    for (int i = 0; i < left.size(); i++) {
        array[temp++] = left[i];
    }
    array[temp++] = p;
    for (int j = 0; j < right.size(); j++) {
        array[temp++] = right[j];
    }
}

int main() {
    std::fstream file;
    file.open("input2.txt");

    int times = 0;
    file >> times;

    for (int t = 0; t < times; t++) {
        int size = 0;
        file >> size;

        std::vector<int> array1;
        std::vector<int> array2;

        for (int i = 0; i < size; i++) {
            int x;
            file >> x;
            array1.push_back(x);
            array2.push_back(x);
        }

        HeapSort(array1);
        cout << "Max Heap Sort : ";
        PrintArray(array1);

        QuickSort(array2);
        cout << "Quick Sort : ";
        PrintArray(array2);
        cout << endl;
    }
    std::system("pause");
    return 0;
}