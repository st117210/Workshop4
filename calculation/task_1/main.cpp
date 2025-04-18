#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

// ������� ��� ���������� ���� �������� �� CSV-�����.
// path - ���� � CSV-�����.
// col1_data - ������, � ������� ����� �������� ������ ������� �������.
// col2_data - ������, � ������� ����� �������� ������ ������� �������.
// delimiter - ����������� �������� � CSV-����� (�� ��������� �������).
// success - ���������� ����, ������� ��������������� � true, ���� ������ ������ �������, � � false, ���� ��������� ������.

bool readData(const std::string& filename, std::vector<double>& arr1, std::vector<double>& arr2) 
{
	std::ifstream file(filename);

	std::string line;
	while (getline(file, line)) 
	{
		std::stringstream ss(line);
		double val1, val2;

		if (ss >> val1 >> val2) 
		{
			arr1.push_back(val1);
			arr2.push_back(val2);
		}
	}

	file.close();
	return true;
}

double amp(double u)
{
	double r = 12.0; // ������������� ����������� � 12 ��.
	return u / r;
}

int main()
{
	std::vector<double> data1;
	std::vector<double> data2;

	if (readData("data1.csv", data1, data2)) 
	{
		std::cout << "������ ������� ��������� �� ����� data1.csv." << std::endl;

		// ����� ��������� ������ (��� ��������)
		std::cout << "������ 1:" << std::endl;
		for (double val : data1) 
		{
			std::cout << val << " ";
		}
		std::cout << std::endl;

		std::cout << "������ 2:" << std::endl;
		for (double val : data2) 
		{
			std::cout << val << " ";
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "�� ������� ��������� ������ �� ����� data1.csv." << std::endl;
	}
	double average_ln = 0.0;
	for (int i = 0; i < data2.size(); i++)
	{
		average_ln += log(amp(data2[i]));
	}
	average_ln /= data2.size();
	std::cout << average_ln << std::endl;

	std::ofstream outputFile("amperage1.csv");
	for (int i = 0; i < data2.size(); i++)
	{
		outputFile << amp(data2[i]) * 1000 << " & " << log(amp(data2[i])) << std::endl;
	}

	outputFile.close();





	return 0;
}

