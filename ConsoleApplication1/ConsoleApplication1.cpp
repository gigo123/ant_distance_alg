// ConsoleApplication1.cpp: ���������� ����� ����� ��� ����������� ����������.
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
   
//�������� ������ ��� sort
bool operator<(const VertexPoint& a, const VertexPoint& b)
{
	return a.x<b.x || a.x == b.x && (a.y<b.y || a.y == b.y && a.z<b.z);
}
//�������� �������� �� ��������� ��� unique
bool operator==(const VertexPoint& a, const VertexPoint& b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z;
}
ostream& operator<<(ostream& os, const VertexPoint& b)
{
	os << b.x << "\t" << b.y << "\t" << b.z << "\n";
	return os;
}
// ����� ��������
struct pathVertexPoint
{
	int numberNeirPoint = 0; //
	int uniqueVectoNumber;  // ����� �� �������
	VertexPoint PathPoint; // ����� � �����
	vector<double> distansToPoint; // ������ ��������� �� ������ �����
	vector<int> uniqueVectoNumderNeb; // ������ ������ ������ ����� � ��������� ������;
	float antKoeficient; // ���������� ���������

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
	vertexVectorUnique.resize(unique(vertexVectorUnique.begin(), vertexVectorUnique.end()) - vertexVectorUnique.begin());  //� ������� ��������� //��, ������ p �������� ������ ���������� �����
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
		//� ������� ���������
		tempNeirPoint.resize(unique(tempNeirPoint.begin(), tempNeirPoint.end()) - tempNeirPoint.begin()); //� ������� ���������
		double distans;
		for (int e = 0; e < tempNeirPoint.size();e++)
		{ //������������ ��������� 
			distans = sqrt(pow(tempPathPoint.PathPoint.x - tempNeirPoint[e].x, 2) + pow(tempPathPoint.PathPoint.y - tempNeirPoint[e].y, 2) + pow(tempPathPoint.PathPoint.z - tempNeirPoint[e].z, 2));
			tempPathPoint.distansToPoint.push_back(distans);
			tempPathPoint.numberNeirPoint++;
		}
		vector<VertexPoint>::iterator vertexIterator;
		for (int k = 0; k < tempPathPoint.distansToPoint.size(); k++)
		{

			// ����������� ���������� ������� � ��������������� ������
			vertexIterator = find(vertexVectorUnique.begin(), vertexVectorUnique.end(), tempNeirPoint[k]);
			// ��������� ���� ������ 
			int postion = distance(vertexVectorUnique.begin(), vertexIterator);
			tempPathPoint.uniqueVectoNumderNeb.push_back(postion);
			// ����� ������ �-����������
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
			int numberChekedPoint = 0; // �������� ���������� ��������� 
			for (int k = 0; k < curentPathPoint.numberNeirPoint; k++) {
				//���� ������� ���������� ����� 1000;
				int randomKoeficientVertex = ((1000 / curentPathPoint.numberNeirPoint)*(k + 1));
				//tempPathPoint.randomKoefcient.push_back((1000 / tempPathPoint.neirPoint.size())*(k + 1));
				if (k == curentPathPoint.numberNeirPoint - 1) randomKoeficientVertex = 1000;
				if (randomKoeficientVertex >= randomkoeficient) {

					// ��������� ���� ������ 
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
						//�������� ��������� ������ �� �������
						curentNumber = curentPathPoint.uniqueVectoNumderNeb[k];
						routeDistans += curentPathPoint.distansToPoint[k];
						curentPathPoint = vectoOfPathPoint[curentNumber];
						tempResaltPath.push_back(curentNumber);

						chekedPointNumber.push_back(curentNumber);
						numberChekedPoint = 0;
						nuberPointRoute++;// ������� ����� ��������.
						break;
					}
				}
			}
		}
		if (noway == false) {
			//������� � �����
			vector<vector<int>>::iterator itp;
			vector<float>::iterator itd;
			itd = distanceVector.begin();
			itp = resaltPOintPath.begin();
			bool last = true;
			//������� ���������� ����� � ����� ��������
			// ���� ������ ������� �� ������ ���������� 
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
		// ����� ����� �������
		getchar();
		// ������� ����� �� ���������
		// ���������� ���������� �����
		float bestPath = distanceVector[0];   // ����� ���������� ���������
		vector<bool>  pointKoefChanged;
		for (int h = 0; h < vectoOfPathPoint.size(); h++) pointKoefChanged.push_back(false);
		// �������� ����� ��� ���������� ����������	

		distanceVector.erase(distanceVector.begin() + distanceVector.size() / 2, distanceVector.end());
		resaltPOintPath.erase(resaltPOintPath.begin() + resaltPOintPath.size()/2, resaltPOintPath.end());
		for (int i = 0; i < resaltPOintPath.size(); i++) {
			float investpatchKoef;
			if (i == 0) investpatchKoef = 6000;
			else investpatchKoef = bestPath / distanceVector[i] *100; // ��� ������� ����� ������������ ��������� - ��� ����������� ������������ 
			for (int j = 0; j < resaltPOintPath[i].size(); j++) {
				int cureninPoint = resaltPOintPath[i][j];
				// ��� ����� ����� ��������� �������� ����������� ��������� ������
				if (vectoOfPathPoint[cureninPoint].antKoeficient < investpatchKoef)   vectoOfPathPoint[cureninPoint].antKoeficient = investpatchKoef;
				pointKoefChanged[cureninPoint] = true;
			}
		}
		
		// ������ ����
		//����� ����� � ������ ������������� 
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
			int numberChekedPoint = 0;// �������� ���������� ���������
			while (curentNumber != endPoint) {
			

				int randomkoeficient = rand() % 1000 + 1;
				//randomkoeficient += vectoOfPathPoint[curentPathPoint.uniqueVectoNumderNeb[curentPathPoint.numberNeirPoint - 1]].antKoeficient; //��������� ���������� �������� ����� 
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

						// ��������� ���� ������ 

						bool alredyCheck = false; // ����� ������ ��������
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
							//�������� ��������� ������ �� �������
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
							nuberPointRoute++;// ������� ����� ��������.
							//continue;
							break;
						}
					}

				}

			}
			//numberIterationAfterBestP++;
			if (toLongDistance == false) { // ���� ���� ��������� 
				numberIterationAfterBestP++;
				cout << routeDistans << "\n";
				// ������� �����
				vector<vector<int>>::iterator itp;
				vector<float>::iterator itd;
				itd = distanceVector.begin();
				itp = resaltPOintPath.begin();
				bool newbestPath = false;
				bool last = true;
				//������� ���������� ����� � ����� ��������
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
				// ���� ���� ����� ��� ������������� 
				if (newbestPath == false) {		
					float investpatchKoef = bestPath / routeDistans * 100; // ��� ������� ����� ������������ ��������� - ��� ����������� ������������ 
					for (int j = 0; j < tempResaltPath.size(); j++) {
						int cureninPoint = tempResaltPath[j];
						// ��� ����� ����� ��������� �������� ����������� ��������� ������
						if (vectoOfPathPoint[cureninPoint].antKoeficient < investpatchKoef)   vectoOfPathPoint[cureninPoint].antKoeficient = investpatchKoef;			
						
					}
				}
				// ���� ���� �����������
				else {
					numberIterationAfterBestP = 0;
					bestPath = distanceVector[0];
					// ��������� ��� �����������
					for (int h = 0; h < vectoOfPathPoint.size(); h++) {
						for (int q = 0; q < vectoOfPathPoint[h].uniqueVectoNumderNeb.size(); q++) {
							vectoOfPathPoint[q].antKoeficient = 0;
						}
					}
					for (int y = 0; y < distanceVector.size(); y++)
					{
						float investpatchKoef;
						if (i == 0) investpatchKoef = 600000;
						else investpatchKoef = bestPath / distanceVector[y] * 100; // ��� ������� ����� ������������ ��������� - ��� ����������� ������������ 
							for (int j = 0; j < resaltPOintPath[y].size(); j++) {
								int cureninPoint = resaltPOintPath[y][j];
								// ��� ����� ����� ��������� �������� ����������� ��������� ������
								if (vectoOfPathPoint[cureninPoint].antKoeficient < investpatchKoef)   vectoOfPathPoint[cureninPoint].antKoeficient = investpatchKoef;
						}
					
					}
				}
			}
		}

 // ����� ���������� ����������.
		cout << "\n" << distanceVector[0];
	getchar();
	return 0;
}

