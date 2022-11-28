#include <iostream>
#include <Windows.h>

using namespace std;

void Create(int** mas, const int ROW_COUNT, const int COL_COUNT, const int HIGH, const int LOW,
																				int i, int j);
void Print(int** mas, const int ROW_COUNT, const int COL_COUNT, int i, int j);
void Input(int** mas, const int ROW_COUNT, const int COL_COUNT, int i, int j);
void Part1_ZeroCol(int** mas, const int COL_COUNT, bool& result,
	int colNo, int rowNo, int& k);
void Part1_CountCol(int** mas, const int COL_COUNT, int& count, int colNo, int rowNo);
void Part1_CountCols(int** mas, const int ROW_COUNT, const int COL_COUNT,
	int& count, bool& result, int rowNo);
bool IsMaxInColK(int** mas, const int colNo, const int max, const int ROW_COUNT,
	int rowNo);
bool IsMinInRowN(int** mas, const int rowNo, const int min, const int COL_COUNT,
	int colNo);
void Part2_SaddlePointRows(int** a, const int ROW_COUNT, const int COL_COUNT,
	int& No, int rowNo);
void Part2_SaddlePointRow(int** a, const int  ROW_COUNT, const int COL_COUNT,
	int& No, const int rowNo, int colNo);

int main()
{
	srand(time(NULL));

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int ROW_COUNT; cout << "RowCount = "; cin >> ROW_COUNT;
	int COL_COUNT; cout << "ColCount = "; cin >> COL_COUNT;
	const int HIGH = 20;
	const int LOW = 10;

	int** mas = new int* [ROW_COUNT];
	for (int i = 0; i < ROW_COUNT; i++)
		mas[i] = new int[COL_COUNT];

	int i = 0;
	int j = 0;
	Create(mas, ROW_COUNT, COL_COUNT, HIGH, LOW, i, j);
	Input(mas, ROW_COUNT, COL_COUNT, i, j);
	Print(mas, ROW_COUNT, COL_COUNT, i, j);

	bool result = false;
	int count = 0;
	Part1_CountCols(mas, ROW_COUNT, COL_COUNT, count, result, 0);
	if (result)
		cout << "count = " << count << endl;
	else
		cout << "there are no zero elements" << endl;
	cout << endl;
	
	cout << "Saddle points: max in row & min in col" << endl;
	cout << "\t" << "No" << "\t" << "Row" << "\t" << "Col" << endl;
	int No = 0;
	Part2_SaddlePointRows(mas, ROW_COUNT, COL_COUNT, No, 0);
	cout << endl;

	for (int i = 0; i < ROW_COUNT; i++)
		delete[] mas[i];
	delete[] mas;
	return 0;

}
void Create(int** mas, const int ROW_COUNT, const int COL_COUNT, const int HIGH, const int LOW,
																				int i, int j)
{
	mas[i][j] = LOW + rand() % (HIGH - LOW + 1);
	if (j < COL_COUNT - 1)
		Create(mas, ROW_COUNT, COL_COUNT, HIGH, LOW, i, j + 1);
	else 
		if (i < ROW_COUNT - 1)
			Create(mas, ROW_COUNT, COL_COUNT, HIGH, LOW, i + 1, 0);
}
void Print(int** mas, const int ROW_COUNT, const int COL_COUNT, int i, int j)
{
	cout << mas[i][j] << '\t';
	if (j < COL_COUNT - 1)
		Print(mas, ROW_COUNT, COL_COUNT, i, j + 1);
	else
		if (i < ROW_COUNT - 1)
		{
			cout << "\n";
			Print(mas, ROW_COUNT, COL_COUNT, i + 1, 0);
		}
		else cout << "\n";
}
void Input(int** mas, const int ROW_COUNT, const int COL_COUNT, int i, int j)
{
	cout << "mas[" << i << "][" << j << "] = "; cin >> mas[i][j];
	if (j < COL_COUNT - 1)
		Input(mas, ROW_COUNT, COL_COUNT, i, j + 1);
	else
		if (i < ROW_COUNT - 1)
		{
			cout << "\n";
			Input(mas, ROW_COUNT, COL_COUNT, i + 1, 0);
		}
}

void Part1_ZeroCol(int** mas, const int COL_COUNT, bool& result,
	int colNo, int rowNo, int& k)
{
	if (mas[rowNo][colNo] == 0)
	{
		result = true;
		k++;
	}
	else
		if (colNo < COL_COUNT - 1)
			Part1_ZeroCol(mas, COL_COUNT, result, colNo + 1, rowNo, k);
}
void Part1_CountCol(int** mas, const int COL_COUNT, int& count, int colNo, int rowNo)
{
	if (mas[rowNo][colNo] < 0)
		count++;
	if (colNo < COL_COUNT - 1)
		Part1_CountCol(mas, COL_COUNT, count, colNo + 1, rowNo);
}
void Part1_CountCols(int** mas, const int ROW_COUNT, const int COL_COUNT,
	int& count, bool& result, int rowNo)
{
	int k = 0;
	Part1_ZeroCol(mas, ROW_COUNT, result, 0, rowNo, k);
	if (k > 0)
		Part1_CountCol(mas, ROW_COUNT, count, 0, rowNo);
	if (rowNo < ROW_COUNT - 1)
		Part1_CountCols(mas, ROW_COUNT, COL_COUNT, count, result, rowNo + 1);
}
bool IsMinInRowN(int** mas, const int rowNo, const int min, const int COL_COUNT,
	int colNo)
{
	if (mas[rowNo][colNo] < min)
		return false;
	if (colNo < COL_COUNT - 1)
		return IsMinInRowN(mas, rowNo, min, COL_COUNT, colNo + 1);
	else
		return true;
}
bool IsMaxInColK(int** mas, const int colNo, const int max, const int ROW_COUNT,
	int rowNo)
{
	if (mas[rowNo][colNo] > max)
		return false;
	if (rowNo < ROW_COUNT - 1)
		return IsMaxInColK(mas, colNo, max, ROW_COUNT, rowNo + 1);
	else
		return true;
}
void Part2_SaddlePointRow(int** mas, const int  ROW_COUNT, const int COL_COUNT,
	int& No, const int rowNo, int colNo)
{
	if (IsMinInRowN(mas, rowNo, mas[rowNo][colNo], COL_COUNT, 0) &&
		IsMaxInColK(mas, colNo, mas[rowNo][colNo], ROW_COUNT, 0))
	{
		cout << "\t" << ++No << "\t" << rowNo << "\t" << colNo << endl;
	}
	if (colNo < COL_COUNT - 1)
		Part2_SaddlePointRow(mas, ROW_COUNT, COL_COUNT, No, rowNo, colNo + 1);
}
void Part2_SaddlePointRows(int** mas, const int ROW_COUNT, const int COL_COUNT,
	int& No, int rowNo)
{
	Part2_SaddlePointRow(mas, ROW_COUNT, COL_COUNT, No, rowNo, 0);
	if (rowNo < ROW_COUNT - 1)
		Part2_SaddlePointRows(mas, ROW_COUNT, COL_COUNT, No, rowNo + 1);
}