// lab2_110550146.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class PrimeFactorization {
private:
	int num1, num2;
	vector<int> num1_factor, num2_factor;

public:
	PrimeFactorization() {
		num1 = 0;
		num2 = 0;
	}
	PrimeFactorization(int _a, int _b) {
		num1 = _a;
		num2 = _b;
	}
	void Get_Prime_Factorization() {
		for (int i = 2; i <= sqrt(num1); i++) {
			while (num1 % i == 0) {
				num1 = num1 / i;
				num1_factor.push_back(i);
			}
		}
		if (num1!=1)
			num1_factor.push_back(num1);
		for (int i = 2; i <= sqrt(num2); i++) {
			while (num2 % i == 0) {
				num2 = num2 / i;
				num2_factor.push_back(i);
			}
		}
		if (num2!=1)
			num2_factor.push_back(num2);
	}

	void Print_Prime_Factorization() {
		cout << "num1_Prime_factor : \" ";
		long long int size1, size2;
		size1 = num1_factor.size();
		size2 = num2_factor.size();
		for (int i = 0; i <size1 ; i++)
			cout << num1_factor[i] << " ";
		cout<<"\"" << endl;
		cout << "num2_Prime_factor : \" ";
		for (int i = 0; i < size2 ; i++)
			cout << num2_factor[i] << " ";
		cout << "\"" << endl;
	}

	void Print_GCD() {
		int gcd = 1;
		for (int i = 0; i < num1_factor.size(); i++) {
			for (int j = 0; j < num2_factor.size(); j++) {
				if (num1_factor[i] == num2_factor[j]) {
					gcd = gcd * num1_factor[i];
					num2_factor[j] = 1;
					break;
				}
			}
		}
		cout << "GCD : " << gcd << endl;
	}

	void Print_LCM() {
		long long int lcm = 1;
		for (int i = 0; i < num1_factor.size(); i++)
			lcm = lcm * num1_factor[i];
		for (int i = 0; i < num2_factor.size(); i++)
			lcm = lcm * num2_factor[i];
		cout << "LCM : " << lcm << endl;
	}

};

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;

		cout << "num1 = " << a << endl;
		cout << "num2 = " << b << endl;

		PrimeFactorization PF(a, b);

		PF.Get_Prime_Factorization();
		PF.Print_Prime_Factorization();
		PF.Print_GCD();
		PF.Print_LCM();

		cout << endl;

	}

	system("PAUSE");
	return 0;
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
