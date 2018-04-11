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
	int numberNeirPoint = 0; //
	int uniqueVectoNumber;  // номер но порядку
	VertexPoint PathPoint; // точка в моделі
	vector<double> distansToPoint; // список дистанцій до сусідніх точок
	vector<int> uniqueVectoNumderNeb; // список номерів сусідніх точок в загалному списку;
	float antKoeficient; // коефіціент алгоритму

};

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
	vertexVectorUnique = vertexVector;
	sort(vertexVectorUnique.begin(), vertexVectorUnique.end());	
	vertexVectorUnique.resize(unique(vertexVectorUnique.begin(), vertexVectorUnique.end()) - vertexVectorUnique.begin());  //и удаляем дубликаты //всё, теперь p содержит только уникальные точки
	for (int i = 0; i < vertexVectorUnique.size(); i++) {
		pathVertexPoint tempPathPoint;
		vector<VertexPoint> tempNeirPoint;		
		 tempPathPoint.PathPoint = vertexVectorUnique[i];
		 tempPathPoint.uniqueVectoNumber = i;
		for (int j = 0; j < vertexVector.size(); j++)
		{
			if (tempPathPoint.PathPoint == vertexVector[j]) {
				double distans;
				int numbeInTrio = j % 3; 		
				if (j == 0) numbeInTrio = 0;
				if (numbeInTrio == 0) {			
					tempNeirPoint.push_back(vertexVector[j + 1]);
					tempNeirPoint.push_back(vertexVector[j + 2]);
				}
				if (numbeInTrio == 1) {
					tempNeirPoint.push_back(vertexVector[j + 1]);
					tempNeirPoint.push_back(vertexVector[j - 1]);
				}
				if (numbeInTrio == 2) {
					tempNeirPoint.push_back(vertexVector[j - 1]);
					tempNeirPoint.push_back(vertexVector[j - 2]);
				}

			}
		}
		sort(tempNeirPoint.begin(), tempNeirPoint.end());
		//и удаляем дубликаты
		tempNeirPoint.resize(unique(tempNeirPoint.begin(), tempNeirPoint.end()) - tempNeirPoint.begin()); //и удаляем дубликаты
		double distans;
		for (int e = 0; e < tempNeirPoint.size();e++)
		{ //розраховуемо дистанцію 
			distans = sqrt(pow(tempPathPoint.PathPoint.x - tempNeirPoint[e].x, 2) + pow(tempPathPoint.PathPoint.y - tempNeirPoint[e].y, 2) + pow(tempPathPoint.PathPoint.z - tempNeirPoint[e].z, 2));
			tempPathPoint.distansToPoint.push_back(distans);
			tempPathPoint.numberNeirPoint++;
		}
		vector<VertexPoint>::iterator vertexIterator;
		for (int k = 0; k < tempPathPoint.distansToPoint.size(); k++)
		{

			// знаходження відповідного еленета в відсортовановану списку
			vertexIterator = find(vertexVectorUnique.begin(), vertexVectorUnique.end(), tempNeirPoint[k]);
			// отримання його номера 
			int postion = distance(vertexVectorUnique.begin(), vertexIterator);
			tempPathPoint.uniqueVectoNumderNeb.push_back(postion);
			// запис пустих м-коефыентыв
			tempPathPoint.antKoeficient = 0;
		}
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
	vector<float> distanceVector;
	vector<vector<int>> resaltPOintPath;	
	int i = 0;
	int firstIter;
	if (vectoOfPathPoint.size() / 10 < 10) {
		firstIter = 10;
	}
	else
	{
		if (vectoOfPathPoint.size() / 10 > 100) {
			firstIter = 100;
		}
		else {
			firstIter = vectoOfPathPoint.size() / 10;
		}
	}

	while (i != firstIter) {
		//for (int i = 0; i < 10; i++) {
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
		float routeDistans = 0;
		bool noway = false;
		while (curentNumber != endPoint) {
			//srand(time(0));
			int randomkoeficient = rand() % 1000;

			//cout << randomkoeficient << " \t";
			int numberChekedPoint = 0; // кылькыть первырених елементыв 
			for (int k = 0; k < curentPathPoint.numberNeirPoint; k++) {
				//якщо останны еоофіціент менше 1000;
				int randomKoeficientVertex = ((1000 / curentPathPoint.numberNeirPoint)*(k + 1));
				//tempPathPoint.randomKoefcient.push_back((1000 / tempPathPoint.neirPoint.size())*(k + 1));
				if (k == curentPathPoint.numberNeirPoint - 1) randomKoeficientVertex = 1000;
				if (randomKoeficientVertex >= randomkoeficient) {

					// отримання його номера 
					bool alredyCheck = false;

					int curentNumberTemp = curentPathPoint.uniqueVectoNumderNeb[k];
					for (int l = 0; l < chekedPointNumber.size(); l++) {
						if (curentNumberTemp == chekedPointNumber[l]) {
							alredyCheck = true;
							numberChekedPoint++;

							if (numberChekedPoint >= curentPathPoint.numberNeirPoint) {
								curentNumber = endPoint;
								k = curentPathPoint.numberNeirPoint;
								noway = true;
								//cout <<  " no way";//
							}
							break;
						}
					}
					if (alredyCheck == false) {
						//додавння дистанції відрізка до загалної
						curentNumber = curentPathPoint.uniqueVectoNumderNeb[k];
						routeDistans += curentPathPoint.distansToPoint[k];
						curentPathPoint = vectoOfPathPoint[curentNumber];
						tempResaltPath.push_back(curentNumber);

						chekedPointNumber.push_back(curentNumber);
						numberChekedPoint = 0;
						nuberPointRoute++;// кількість точок маршруту.
						break;
					}
				}
			}
		}
		if (noway == false) {
			//вставка в масив
			vector<vector<int>>::iterator itp;
			vector<float>::iterator itd;
			itd = distanceVector.begin();
			itp = resaltPOintPath.begin();
			bool last = true;
			//вставка знайденого шляшу в масив відповідей
			// якщо перший елемнрт то просто вставляэмо 
			if (distanceVector.size() == 0) {
				distanceVector.push_back(routeDistans);

				resaltPOintPath.push_back(tempResaltPath);
			}
			else {

				for (int e = 0; e < distanceVector.size(); e++) {
					if (routeDistans < distanceVector[e]) {
						distanceVector.insert(itd, routeDistans);
						resaltPOintPath.insert(itp, tempResaltPath);
						last = false;
						break;
					}
					itd = distanceVector.begin() + e + 1;
					itp = resaltPOintPath.begin() + e + 1;
				}
				if (last == true) {
					distanceVector.push_back(routeDistans);
					resaltPOintPath.push_back(tempResaltPath);
				}

			}
			cout << routeDistans << "\n";
			i++;
		}
	}
	cout <<  "\n \n";
		// кінець першої обробки
		getchar();
		// сортуємо масив по дистанції
		// розрахунок коефіціенті мурах
		float bestPath = distanceVector[0];   // змінна найкоротшої дистанції
		vector<bool>  pointKoefChanged;
		for (int h = 0; h < vectoOfPathPoint.size(); h++) pointKoefChanged.push_back(false);
		// оюхлдимо шляши для визначення коефіціету	

		distanceVector.erase(distanceVector.begin() + distanceVector.size() / 2, distanceVector.end());
		resaltPOintPath.erase(resaltPOintPath.begin() + resaltPOintPath.size()/2, resaltPOintPath.end());
		for (int i = 0; i < resaltPOintPath.size(); i++) {
			float investpatchKoef;
			if (i == 0) investpatchKoef = 6000;
			else investpatchKoef = bestPath / distanceVector[i] *100; // для кожного шляху розраховуемо коефіціен - йго відношеннядо найкоротшого 
			for (int j = 0; j < resaltPOintPath[i].size(); j++) {
				int cureninPoint = resaltPOintPath[i][j];
				// для кожної точки вибраного маршруту розраховуємо коєфіціент мурахи
				if (vectoOfPathPoint[cureninPoint].antKoeficient < investpatchKoef)   vectoOfPathPoint[cureninPoint].antKoeficient = investpatchKoef;
				pointKoefChanged[cureninPoint] = true;
			}
		}
		
		// другий цикл
		//пошук шляху з новими коефіціентами 
		int numberIterationAfterBestP = 0;
		//for (int i = 0; i < 10; i++) {
		while (numberIterationAfterBestP < firstIter*3) {
			//
			
			int curentNumber = startPoint;
			vector<int> chekedPointNumber;
			chekedPointNumber.push_back(curentNumber);
			int nuberPointRoute = 0;

			vector<int> tempResaltPath;
			tempResaltPath.push_back(curentNumber);
			//
			pathVertexPoint curentPathPoint, nextPathPoint;
			curentPathPoint = vectoOfPathPoint[startPoint];


			float routeDistans = 0;
			bool toLongDistance = false;
			int numberChekedPoint = 0;// кылькыть первырених елементыв
			while (curentNumber != endPoint) {
			

				int randomkoeficient = rand() % 1000 + 1;
				//randomkoeficient += vectoOfPathPoint[curentPathPoint.uniqueVectoNumderNeb[curentPathPoint.numberNeirPoint - 1]].antKoeficient; //додавання коефыыента сотанньої точки 
				float randomandK = 0;
				for (int v = 0; v < curentPathPoint.numberNeirPoint; v++) {
					int numberOfNeir = curentPathPoint.uniqueVectoNumderNeb[v];
					randomandK = randomandK + 1 + vectoOfPathPoint[numberOfNeir].antKoeficient/100;
				}
				float fullkoefe = 1000 / randomandK;
				for (int k = 0; k < curentPathPoint.numberNeirPoint; k++) {
					
					int numberOfNeir = curentPathPoint.uniqueVectoNumderNeb[k];
					int randomKoeficientVertex = fullkoefe*(k + 1+ vectoOfPathPoint[numberOfNeir].antKoeficient / 100);
					
					if (randomKoeficientVertex >= randomkoeficient  || k == curentPathPoint.numberNeirPoint - 1) {

						// отримання його номера 

						bool alredyCheck = false; // змына перрки елемента
						int curentNumberTemp = curentPathPoint.uniqueVectoNumderNeb[k];
						for (int l = 0; l < chekedPointNumber.size(); l++) {
							if (curentNumberTemp == chekedPointNumber[l]) {
								alredyCheck = true;
								numberChekedPoint++;

								if (numberChekedPoint >= curentPathPoint.numberNeirPoint) {
									curentNumber = endPoint;
									k = curentPathPoint.numberNeirPoint;
								//	cout   << " no way" << "\n";///
									toLongDistance = true;
								}
								break;
							}
						}
						if (alredyCheck == false) {
							curentNumber = curentPathPoint.uniqueVectoNumderNeb[k];
							//додавння дистанції відрізка до загалної
							routeDistans += curentPathPoint.distansToPoint[k];
							if (routeDistans > bestPath * 2) {
								curentNumber = endPoint;
								k = curentPathPoint.numberNeirPoint;
							//	cout  << " to long" << "\n";//
								toLongDistance = true;
							}
							curentPathPoint = vectoOfPathPoint[curentNumber];
							tempResaltPath.push_back(curentNumber);
						//	cout << curentNumber << " ";
							chekedPointNumber.push_back(curentNumber);
							numberChekedPoint = 0;
							nuberPointRoute++;// кількість точок маршруту.
							//continue;
							break;
						}
					}

				}

			}
			//numberIterationAfterBestP++;
			if (toLongDistance == false) { // якщо шлях нормалний 
				numberIterationAfterBestP++;
				cout << routeDistans << "\n";
				// обробка шляху
				vector<vector<int>>::iterator itp;
				vector<float>::iterator itd;
				itd = distanceVector.begin();
				itp = resaltPOintPath.begin();
				bool newbestPath = false;
				bool last = true;
				//вставка знайденого шляшу в масив відповідей
				for (int e = 0; e < distanceVector.size(); e++) {
					if (routeDistans < distanceVector[e]) {
						distanceVector.insert(itd, routeDistans);
						resaltPOintPath.insert(itp, tempResaltPath);
						if (e == 0)   newbestPath = true;
						last = false;
						break;
					}
					itd = distanceVector.begin() + e + 1;
					itp = resaltPOintPath.begin() + e + 1;
				}
				if (last == true) {
					distanceVector.push_back(routeDistans);
					resaltPOintPath.push_back(tempResaltPath);
				}
				// якщо шлях доший іфд найкогротшого 
				if (newbestPath == false) {		
					float investpatchKoef = bestPath / routeDistans * 100; // для кожного шляху розраховуемо коефіціен - йго відношеннядо найкоротшого 
					for (int j = 0; j < tempResaltPath.size(); j++) {
						int cureninPoint = tempResaltPath[j];
						// для кожної точки вибраного маршруту розраховуємо коєфіціент мурахи
						if (vectoOfPathPoint[cureninPoint].antKoeficient < investpatchKoef)   vectoOfPathPoint[cureninPoint].antKoeficient = investpatchKoef;			
						
					}
				}
				// якщо шлях найкоротший
				else {
					numberIterationAfterBestP = 0;
					bestPath = distanceVector[0];
					// обнулення всіх коефіціентів
					for (int h = 0; h < vectoOfPathPoint.size(); h++) {
						for (int q = 0; q < vectoOfPathPoint[h].uniqueVectoNumderNeb.size(); q++) {
							vectoOfPathPoint[q].antKoeficient = 0;
						}
					}
					for (int y = 0; y < distanceVector.size(); y++)
					{
						float investpatchKoef;
						if (i == 0) investpatchKoef = 600000;
						else investpatchKoef = bestPath / distanceVector[y] * 100; // для кожного шляху розраховуемо коефіціен - йго відношеннядо найкоротшого 
							for (int j = 0; j < resaltPOintPath[y].size(); j++) {
								int cureninPoint = resaltPOintPath[y][j];
								// для кожної точки вибраного маршруту розраховуємо коєфіціент мурахи
								if (vectoOfPathPoint[cureninPoint].antKoeficient < investpatchKoef)   vectoOfPathPoint[cureninPoint].antKoeficient = investpatchKoef;
						}
					
					}
				}
			}
		}

 // виввід найкращого результату.
		cout << "\n" << distanceVector[0];
	getchar();
	return 0;
}

