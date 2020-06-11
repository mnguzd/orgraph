#include <iostream>
#include <fstream>

int** Graph;  //Двумерный массив, матрица смежности
int NumberOfVertex, StartVertex = 0, Distance = 0;   //Количество вершин
bool* Found;

using namespace std;


void Dispose() {
	for (int i = 0; i < NumberOfVertex; i++) {
		delete[] Graph[i];
	}
	delete[] Found;
}


void Path(int Start, int Distanceance) {
	if (Distanceance == 0) { //Если расстояние до вершины равно нулю, значит существует путь от Start
		Found[Start] = true;
	}
	else {
		for (int V = 0; V < NumberOfVertex; ++V) { //Цикл для всех вершин, кроме исходной
			if ((Graph[Start][V] > 0)) {
				if ((V != Start)) {
					if ((Distanceance >= Graph[Start][V])) {
						Path(V, Distanceance - Graph[Start][V]);     /*Запускаем рекурсию для всех вершин, кроме исходной
																   уменьшая расстояние, так как прошли один путь*/
					}
				}
			}
		}
	}
}

void Init(const string pathToFile) {
	ifstream fin(pathToFile); //Файл с начальными значениями, в первой строке 1 это кол-во вершин, 2-исходная вершина, 3-исходная длина
	fin >> NumberOfVertex >> StartVertex >> Distance; //Считывание значений количества вершин, конечной вершины и расстояния.
	Found = new bool[NumberOfVertex]; //Массив с проверенными элементами.
	Graph = new int* [NumberOfVertex];
	for (int i = 0; i < NumberOfVertex; ++i) {   //Инициализация графа

		Graph[i] = new int[NumberOfVertex];

		Found[i] = false;

		for (int j = 0; j < NumberOfVertex; ++j)
		{
			int d = 0;
			fin >> d;
			Graph[i][j] = d;
		}
	}
	fin.close();    //Закрытие потока файла
}

int main() {
	const string path = "input.txt";
	Init(path);  //функция инициализации графа 
	Path(StartVertex, Distance);
	ofstream fout;
	fout.open("output.txt");
	for (int i = 0; i < NumberOfVertex; ++i) {   //Вывод вершин
		if (Found[i]) {
			fout << i << ' ';
		}
	}
	fout.close();
	Dispose(); //Удаление выделившейся памяти
	return (0);
}