// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <ctime>
#define FILENAME "input.stl"
using namespace std;
//
struct  VertexPoint
{
	double x, y, z;
	VertexPoint(int x = 0, int y = 0, int z = 0) :x(x), y(y), z(z) {}
};
   
//оператор меньше для sort
bool operator<(const VertexPoint& a, const VertexPoint& b)
{
	return a.x<b.x || a.x == b.x && (a.y<b.y || a.y == b.y && a.z<b.z);
}
//оператор проверки на равенство для unique
bool operator==(const VertexPoint& a, const VertexPoint& b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z;
}
ostream& operator<<(ostream& os, const VertexPoint& b)
{
	os << b.x << "\t" << b.y << "\t" << b.z << "\n";
	return os;
}
// точка маршруту
struct pathVertexPoint
{
	int uniqueVectoNumber;  // номер но порядку
	VertexPoint PathPoint; // точка в моделі
	vector<VertexPoint>  neirPoint; // список сусідніх точок на карті
	vector<double> distansToPoint; // список дистанцій до сусідніх точок
	vector<double> antPoint;
	vector<int> randomKoefcient; // коефіціент до сусідніх точок
	vector<int> uniqueVectoNumderNeb; // список номерів сусідніх точок в загалному списку;
	vector<int> antKoeficient; // коефіціент алгоритму

};


//перерахунок коефыцыентыв.
vector<int> chengeKoeficient(vector<int> inKoeficient, vector<int> inPersent) {
	int koefPersent;
	int persentSum = 0;
	vector<int> vectorOfPersent;
	vector<int> outKOeficient;
	int tempKoeficent = 0;
	//koefPersent = 1000 / inKoeficient.size();
	for (int i = 0; i < inPersent.size(); i++) {
		koefPersent = 1 + inPersent[i] / 500;
		vectorOfPersent.push_back(koefPersent);
		persentSum = persentSum + koefPersent;
	}
	koefPersent = 1000 / persentSum;
	for (int i = 0; i < inPersent.size(); i++) {
		tempKoeficent = tempKoeficent + koefPersent*vectorOfPersent[i];
		outKOeficient.push_back(tempKoeficent);
	}
	return outKOeficient;
}

int main()
{
	std::string  noneadedstring;
	std::ifstream file(FILENAME);
	double tempVectorX;
	double tempVectorY;
	double tempVectorZ;
	vector<VertexPoint>  vertexVector;
	vector<VertexPoint>  vertexVectorUnique;
	VertexPoint tempVertexCoord;
	vector<pathVertexPoint> vectoOfPathPoint;
	int startPoint, endPoint;

	if (!file.is_open())
	{
		std::cout << "cannot open file: " << FILENAME;
		getchar();
		return 1;
	}
	while (!file.eof()) {
		file >> noneadedstring;
		//cout << noneadedstring << "\t";
		if (noneadedstring == "vertex") {
			file >> tempVertexCoord.x;
			file >> tempVertexCoord.y;
			file >> tempVertexCoord.z;
			vertexVector.push_back(tempVertexCoord);
		}
		
	}
	//
	vertexVectorUnique = vertexVector;
	sort(vertexVectorUnique.begin(), vertexVectorUnique.end());
	//и удаляем дубликаты
	vertexVectorUnique.resize(unique(vertexVectorUnique.begin(), vertexVectorUnique.end()) - vertexVectorUnique.begin());
	//всё, теперь p содержит только уникальные точки

	//
ofstream fileOut("input.txt");
ofstream fileOutPath("inputpath.txt");
ofstream fileOutdistance("inputdistance.txt");
ofstream fileKoeficient("inputcoef.txt");

	//
	for (int i = 0; i < vertexVectorUnique.size(); i++) {
	//for (int i = 0; i < 1; i++) {
		pathVertexPoint tempPathPoint;
		tempPathPoint.neirPoint.clear();
		 tempPathPoint.PathPoint = vertexVectorUnique[i];
		 tempPathPoint.uniqueVectoNumber = i;
		for (int j = 0; j < vertexVector.size(); j++)
		{
			if (tempPathPoint.PathPoint == vertexVector[j]) {
				double distans;
				int numbeInTrio = j % 3; 
				//cout << numbeInTrio << "\t";
				if (j == 0) numbeInTrio = 0;
				if (numbeInTrio == 0) {
					tempPathPoint.neirPoint.push_back(vertexVector[j + 1]);
					tempPathPoint.neirPoint.push_back(vertexVector[j + 2]);
					distans = sqrt(pow(tempPathPoint.PathPoint.x- vertexVector[j + 1].x,2) + pow(tempPathPoint.PathPoint.y - vertexVector[j + 1].y, 2)+ pow(tempPathPoint.PathPoint.z - vertexVector[j + 1].z, 2));
					tempPathPoint.distansToPoint.push_back(distans);
					distans = sqrt(pow(tempPathPoint.PathPoint.x - vertexVector[j + 2].x, 2) + pow(tempPathPoint.PathPoint.y - vertexVector[j + 2].y, 2) + pow(tempPathPoint.PathPoint.z - vertexVector[j + 2].z, 2));
					tempPathPoint.distansToPoint.push_back(distans);
				}
				if (numbeInTrio == 1) {
					tempPathPoint.neirPoint.push_back(vertexVector[j - 1]);				
					tempPathPoint.neirPoint.push_back(vertexVector[j + 1]);
					distans = sqrt(pow(tempPathPoint.PathPoint.x - vertexVector[j + 1].x, 2) + pow(tempPathPoint.PathPoint.y - vertexVector[j + 1].y, 2) + pow(tempPathPoint.PathPoint.z - vertexVector[j + 1].z, 2));
					tempPathPoint.distansToPoint.push_back(distans);
					distans = sqrt(pow(tempPathPoint.PathPoint.x - vertexVector[j -1].x, 2) + pow(tempPathPoint.PathPoint.y - vertexVector[j -1].y, 2) + pow(tempPathPoint.PathPoint.z - vertexVector[j -1].z, 2));
					tempPathPoint.distansToPoint.push_back(distans);
				}
				if (numbeInTrio == 2) {
					tempPathPoint.neirPoint.push_back(vertexVector[j - 2]);				
					tempPathPoint.neirPoint.push_back(vertexVector[j - 1]);
					distans = sqrt(pow(tempPathPoint.PathPoint.x - vertexVector[j - 1].x, 2) + pow(tempPathPoint.PathPoint.y - vertexVector[j - 1].y, 2) + pow(tempPathPoint.PathPoint.z - vertexVector[j - 1].z, 2));;
					tempPathPoint.distansToPoint.push_back(distans);
					distans = sqrt(pow(tempPathPoint.PathPoint.x - vertexVector[j - 2].x, 2) + pow(tempPathPoint.PathPoint.y - vertexVector[j - 2].y, 2) + pow(tempPathPoint.PathPoint.z - vertexVector[j - 2].z, 2));
					tempPathPoint.distansToPoint.push_back(distans);
				}

			}
		}
		//
		sort(tempPathPoint.neirPoint.begin(), tempPathPoint.neirPoint.end());
		//и удаляем дубликаты
		tempPathPoint.neirPoint.resize(unique(tempPathPoint.neirPoint.begin(), tempPathPoint.neirPoint.end()) - tempPathPoint.neirPoint.begin());
		//
		vector<VertexPoint>::iterator vertexIterator;
		for (int k = 0; k < tempPathPoint.neirPoint.size(); k++)
		{
			//вивід в файл
			fileOut << tempPathPoint.neirPoint[k];
			// знаходження відповідного еленета в відсортовановану списку
			vertexIterator = find(vertexVectorUnique.begin(), vertexVectorUnique.end(), tempPathPoint.neirPoint[k]);

			// отримання його номера 

			int postion = distance(vertexVectorUnique.begin(), vertexIterator);
			tempPathPoint.uniqueVectoNumderNeb.push_back(postion);
			//fileOutPath << postion << "\n";
			//визначення початкових коефіціентів
			tempPathPoint.randomKoefcient.push_back((1000 / tempPathPoint.neirPoint.size())*(k+1));
			fileOutdistance << tempPathPoint.randomKoefcient[k] << "\n";

			// запис пустих м-коефыентыв
			tempPathPoint.antKoeficient.push_back(0);

		}
		for (int h = 0; h < tempPathPoint.distansToPoint.size(); h++)
		{
			fileOut << tempPathPoint.distansToPoint[h] << "\t";
		}
		fileOut << "\n \n";
		vectoOfPathPoint.push_back(tempPathPoint);
	}
	//
	printf("number of vertex point %i \n", vertexVectorUnique.size());
	//
	printf("enter star point nuber\n");
	scanf_s("%i", &startPoint);
	printf("enter end point nuber \n");
	scanf_s("%i", &endPoint);
	//
	srand(time(0));
	vector<int> distanceVector;

	vector<vector<int>> resaltPOintPath;
	
	for (int i = 0; i < 10; i++) {
		int curentNumber = startPoint;
	vector<int> chekedPointNumber;
	chekedPointNumber.push_back(curentNumber);
	int nuberPointRoute = 0;
	vector<int> tempResaltPath;
	tempResaltPath.push_back(curentNumber);
	//
	pathVertexPoint curentPathPoint, nextPathPoint;
	curentPathPoint = vectoOfPathPoint[startPoint];

	//srand(time(0));
	int routeDistans = 0;
		while (curentNumber != endPoint) {
			//srand(time(0));
			int randomkoeficient = rand() % 1000 + 1;

			//cout << randomkoeficient << " \t";
		
			int numberChekedPoint = 0; // кылькыть первырених елементыв 
			for (int k = 0; k < curentPathPoint.neirPoint.size(); k++) {
				//якщо останны еоофіціент менше 1000;
				if (k == curentPathPoint.neirPoint.size() - 1) curentPathPoint.randomKoefcient[k] = 1000;
				if (curentPathPoint.randomKoefcient[k] >= randomkoeficient) {

					// отримання його номера 
					bool alredyCheck = false;
					
					int curentNumberTemp = curentPathPoint.uniqueVectoNumderNeb[k];
					for (int l = 0; l < chekedPointNumber.size(); l++) {
						if (curentNumberTemp == chekedPointNumber[l]) {
							alredyCheck = true;
							numberChekedPoint++;

							if (numberChekedPoint >= curentPathPoint.neirPoint.size()) {
								curentNumber = endPoint;
								k = curentPathPoint.neirPoint.size();
								//cout <<  " no way";//
								fileOutPath << "\n" << "no way" << "\t";
								//goto noway;
							}
							break;
						}
					}
						//додавння дистанції відрізка до загалної
					curentNumber = curentPathPoint.uniqueVectoNumderNeb[k];
					routeDistans += curentPathPoint.distansToPoint[k];
						curentPathPoint = vectoOfPathPoint[curentNumber];
						tempResaltPath.push_back(curentNumber);
						fileOutPath << curentNumber << "\t";//
						//cout << curentNumber << " ";//

						chekedPointNumber.push_back(curentNumber);
						numberChekedPoint = 0;
						nuberPointRoute++;// кількість точок маршруту.
						break;
				}

			}
			
		}
		fileOutPath << "\n"<< nuberPointRoute<<"\t"<< routeDistans<<"\n";
		//cout << curentNumber << "\n ";
		cout << routeDistans << "\n";
		distanceVector.push_back(routeDistans);
		resaltPOintPath.push_back(tempResaltPath);
	}

	// кінець першої обробки
	getchar();
	// сортуємо масив по дистанції
	sort(distanceVector.begin(), distanceVector.end()); // сортування масиву результів.
	// розрахунок коефіціенті мурах
	int bestPath = distanceVector[0];   // змінна найкоротшої дистанції
	vector<bool>  pointKoefChanged;
	for (int h = 0; h < vectoOfPathPoint.size(); h++) pointKoefChanged.push_back(false);
	// оюхлдимо шляши для визначення коефіціету	
	for (int i = 0; i < resaltPOintPath.size(); i++) {
			int investpatchKoef = bestPath / distanceVector[i] * 1000; // для кожного шляху розраховуемо коефіціен - йго відношеннядо найкоротшого 
			for (int j = 0; j < resaltPOintPath[i].size() - 1; j++) {
				int cureninPoint = resaltPOintPath[i][j];
				for (int k = 0; k < vectoOfPathPoint[cureninPoint].uniqueVectoNumderNeb.size(); k++) {
					if (vectoOfPathPoint[cureninPoint].uniqueVectoNumderNeb[k] == resaltPOintPath[i][j + 1]) { // для кожної точки вибраного маршруту розраховуємо коєфіціент мурахи
						if (vectoOfPathPoint[cureninPoint].antKoeficient[k] == 0) {
							vectoOfPathPoint[cureninPoint].antKoeficient[k] = investpatchKoef;
						}
						else {
							vectoOfPathPoint[cureninPoint].antKoeficient[k] = (vectoOfPathPoint[cureninPoint].antKoeficient[k] + investpatchKoef) / 2;
						}
						fileKoeficient << vectoOfPathPoint[cureninPoint].antKoeficient[k] << " ";
						pointKoefChanged[cureninPoint] = true;

						
					}
				}
			}
			fileKoeficient << " \n";
		}
	// перарахунок коефіціентів у всіх пройдених точках 
	for (int t = 0; t < vectoOfPathPoint.size(); t++) {
		if (pointKoefChanged[t] == true) {

			vectoOfPathPoint[t].randomKoefcient = chengeKoeficient(vectoOfPathPoint[t].randomKoefcient, vectoOfPathPoint[t].antKoeficient);
		}
	}
	// другий цикл
	//пошук шляху з новими коефіціентами 
	for (int i = 0; i < 10; i++) {
		//
		//cout << i << " \t";
	noway:
		cout << i << " \t";
		int curentNumber = startPoint;
		vector<int> chekedPointNumber;
		chekedPointNumber.push_back(curentNumber);
		int nuberPointRoute = 0;
	
		vector<int> tempResaltPath;
		tempResaltPath.push_back(curentNumber);
		//
		pathVertexPoint curentPathPoint, nextPathPoint;
		curentPathPoint = vectoOfPathPoint[startPoint];


		int routeDistans = 0;
		while (curentNumber != endPoint) {
			//srand(time(0));
			int randomkoeficient = rand() % 1000 + 1;

			//cout << distanceVector.size() << " \t";
			int numberChekedPoint = 0; // кылькыть первырених елементыв
			for (int k = 0; k < curentPathPoint.neirPoint.size(); k++) {
				//якщо останны еоофіціент менше 1000;
				if (k == curentPathPoint.neirPoint.size() - 1) curentPathPoint.randomKoefcient[k] = 1000;
				if (curentPathPoint.randomKoefcient[k] >= randomkoeficient) {

					// отримання його номера 
					
					bool alredyCheck = false; // змына перрки елемента
					int curentNumberTemp = curentPathPoint.uniqueVectoNumderNeb[k];
					for (int l = 0; l < chekedPointNumber.size(); l++) {
						if (curentNumberTemp == chekedPointNumber[l]) {
							alredyCheck = true;
							numberChekedPoint++;

							if (numberChekedPoint >= curentPathPoint.neirPoint.size()) {
								curentNumber = endPoint;
								k = curentPathPoint.neirPoint.size();
								//cout <<  " no way";//
								fileOutPath << "\n" << "no way" << "\t";
								//goto noway;
							}
							break;
							//continue;
						}
					}
					if (alredyCheck == false) {
						curentNumber = curentPathPoint.uniqueVectoNumderNeb[k];
						//додавння дистанції відрізка до загалної
						routeDistans += curentPathPoint.distansToPoint[k];
						curentPathPoint = vectoOfPathPoint[curentNumber];
						tempResaltPath.push_back(curentNumber);
						fileOutPath << curentNumber << "\t";//
						//cout << curentNumber << " ";//
						chekedPointNumber.push_back(curentNumber);
						numberChekedPoint = 0;
						nuberPointRoute++;// кількість точок маршруту.
						//continue;
					}
				}

			}

		}
		fileOutPath << "\n" << nuberPointRoute << "\t" << routeDistans << "\n";
		//cout << curentNumber << "\n ";
		cout << routeDistans << "\n";
		// обробка шляху
		vector<vector<int>>::iterator itp;
		vector<int>::iterator itd;
		itd = distanceVector.begin();
		itp = resaltPOintPath.begin();
		bool newbestPath = false;
		//вставка знайденого шляшу в масив відповідей
		for (int e = 0; e < distanceVector.size(); e++) {
			if (routeDistans < distanceVector[e]) {
				distanceVector.insert(itd, routeDistans);
				resaltPOintPath.insert(itp, tempResaltPath);
				if (e == 0)   newbestPath = true;
				break;
			}
			itd = distanceVector.begin() + e + 1;
			itp = resaltPOintPath.begin()+ e + 1 ;
		}
		// якщо шлях доший іфд найкогротшого 
		if (newbestPath == false) {

			int investpatchKoef = bestPath / routeDistans * 1000; // для кожного шляху розраховуемо коефіціен - йго відношеннядо найкоротшого 
			for (int j = 0; j < tempResaltPath.size() - 1; j++) {
				int cureninPoint = tempResaltPath[j];
				for (int k = 0; k < vectoOfPathPoint[cureninPoint].uniqueVectoNumderNeb.size(); k++) {
					if (vectoOfPathPoint[cureninPoint].uniqueVectoNumderNeb[k] == tempResaltPath[j + 1]) { // для кожної точки вибраного маршруту розраховуємо коєфіціент мурахи
					if (vectoOfPathPoint[cureninPoint].antKoeficient[k] == 0) {
						vectoOfPathPoint[cureninPoint].antKoeficient[k] = investpatchKoef;
					}
					else {
						vectoOfPathPoint[cureninPoint].antKoeficient[k] = (vectoOfPathPoint[cureninPoint].antKoeficient[k] + investpatchKoef) / 2;
					}
						
						pointKoefChanged[cureninPoint] = true;
						fileKoeficient << vectoOfPathPoint[cureninPoint].antKoeficient[k] << " ";
		}
					
				}
				vectoOfPathPoint[j].randomKoefcient = chengeKoeficient(vectoOfPathPoint[j].randomKoefcient, vectoOfPathPoint[j].antKoeficient); // зміна коефіціенту
			}
		}
		// якщо шлях найкоротший
		else {
			bestPath= distanceVector[0];
			// обнулення всіх коефіціентів
			for (int h = 0; h < vectoOfPathPoint.size(); h++) {
				pointKoefChanged[h] = false;
				for (int q = 0; q < vectoOfPathPoint[h].uniqueVectoNumderNeb.size(); q++) {
					vectoOfPathPoint[q].antKoeficient[h] = 0;
				}
			}
			for (int y = 0; y < distanceVector.size(); y++) {
				int investpatchKoef = 1000; // для кожного шляху розраховуемо коефіціен - йго відношеннядо найкоротшого 
				for (int j = 0; j < tempResaltPath.size() - 1; j++) {
					int cureninPoint = tempResaltPath[j];
					for (int k = 0; k < vectoOfPathPoint[cureninPoint].uniqueVectoNumderNeb.size(); k++) {
					
						if (vectoOfPathPoint[cureninPoint].uniqueVectoNumderNeb[k] == resaltPOintPath[y][j + 1])
					{ // для кожної точки вибраного маршруту розраховуємо коєфіціент мурахи
						if (vectoOfPathPoint[cureninPoint].antKoeficient[k] == 0) {
							vectoOfPathPoint[cureninPoint].antKoeficient[k] = investpatchKoef;
						}
						else {
							vectoOfPathPoint[cureninPoint].antKoeficient[k] = (vectoOfPathPoint[cureninPoint].antKoeficient[k] + investpatchKoef) / 2;
						}
							pointKoefChanged[cureninPoint] = true;
							fileKoeficient << vectoOfPathPoint[cureninPoint].antKoeficient[k] << " ";

						}
					}
				}
			}
			// запис нових коефіцнтів 
			for (int t = 0; t < vectoOfPathPoint.size(); t++) {
				if (pointKoefChanged[t] == true) {

					vectoOfPathPoint[t].randomKoefcient = chengeKoeficient(vectoOfPathPoint[t].randomKoefcient, vectoOfPathPoint[t].antKoeficient);
				}
			}

		}
		fileKoeficient << " \n";

	}

	fileOutPath << "\n"<< distanceVector [0]<<"\n"; // виввід найкращого результату.
	getchar();
	fileOut.close();
	fileOutPath.close();
	fileOutdistance.close();
	fileKoeficient.close();
	return 0;
}

