// lab1_110550146.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
using namespace std;

class Data {
public:
    int a;
    int b;
};

Data answer, n, m;
char op;

void select() {
    switch (op) {
    case 'p':
        answer = m;
        break;
    case '+':
        cin >> n.a >> n.b;
        answer.a = m.a + n.a;
        answer.b = m.b + n.b;
        break;
    case '*':
        cin >> n.a >> n.b;
        answer.a = m.a * n.a - m.b * n.b;
        answer.b = m.a * n.b + m.b * n.a;
        break;
    }
}

void output() {
    switch (answer.a) {
    case 0:
        if (answer.b == 0)
            cout << "0" << endl;
        else if (answer.b == 1)
            cout << "i" << endl;
        else if (answer.b == -1)
            cout << "-i" << endl;
        else
            cout << answer.b << "i" << endl;
        break;
    default:
        cout << answer.a;
        if (answer.b > 1)   cout << "+" << answer.b << "i" << endl;
        else if (answer.b == 1) cout << "+i" << endl;
        else if (answer.b == -1) cout << "-i" << endl;
        else if (answer.b < 0)  cout << answer.b << "i" << endl;
        else  cout << endl;
        break;
    }
}

void input(int time) {
    for (int t = 0; t < time; t++) {
        cin >> op >> m.a >> m.b;
        select();
        output();
    }
}

int main() {
    int times;
    cin >> times;
    input(times);
    system("pause");
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
