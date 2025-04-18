#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

// Функция для считывания двух столбцов из CSV-файла.
// path - путь к CSV-файлу.
// col1_data - вектор, в который будут записаны данные первого столбца.
// col2_data - вектор, в который будут записаны данные второго столбца.
// delimiter - разделитель столбцов в CSV-файле (по умолчанию запятая).
// success - логический флаг, который устанавливается в true, если чтение прошло успешно, и в false, если произошла ошибка.

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


void diff(std::vector<double>& arr, std::vector<double>& data)
{
	for (int i = 0; i < data.size() / 2; i++)
	{
		arr.push_back(data[data.size() / 2 + i] - data[i]);
	}
}

double aver(std::vector<double>& a_arr)
{
	double average = 0.0;
	for (int i = 0; i < a_arr.size(); i++)
	{
		average += a_arr[i];
	}
	average /= a_arr.size();

	return average;
}

std::vector<double> a_arr(std::vector<double>& x_, std::vector<double>& y_)
{
	std::vector<double> a;
	for (int i = 0; i < x_.size(); i++)
	{
		a.push_back(y_[i] / x_[i]);
	}
	return a;
}

std::vector<double> a_diff(std::vector<double>& a, double average)
{
	std::vector<double> arr;
	for (int i = 0; i < a.size(); i++)
	{
		arr.push_back(a[i] - average);
	}
	return arr;
}

std::vector<double> a2_arr(std::vector<double>& arr)
{
	std::vector<double> a;
	for (int i = 0; i < arr.size(); i++)
	{
		a.push_back(arr[i] * arr[i]);
	}
	return a;
}

double s(std::vector<double>& a2_arr)
{
	double t = 0.0;
	double sum = 0.0;

	for (int i = 0; i < a2_arr.size(); i++)
	{
		sum += a2_arr[i];
	}

	t = sqrt(sum / (a2_arr.size() * (a2_arr.size() - 1)));

	return t;
}



int main()
{
	std::vector<double> data1;
	std::vector<double> data2;

	if (readData("voltage_amp1.csv", data1, data2))
	{
		std::cout << "succeed" << std::endl;

		// Вывод считанных данных (для проверки)
		std::cout << "arr 1:" << std::endl;
		for (double val : data1)
		{
			std::cout << val << " ";
		}
		std::cout << std::endl;

		std::cout << "arr 2:" << std::endl;
		for (double val : data2)
		{
			std::cout << val << " ";
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "fail" << std::endl;
	}

	std::vector<double> x_;
	std::vector<double> y_;
	diff(x_, data1);
	diff(y_, data2);

	std::vector<double> a = a_arr(x_, y_);
	double average = aver(a);
	std::vector<double> a_d = a_diff(a, average);
	std::vector<double> a2 = a2_arr(a_d);

	std::cout << average << std::endl;
	std::cout << s(a2) << std::endl;
	double delta_t = 0.5;
	double kelvin = 295;
	double t_coef = 2.3646;
	double delta_tan = s(a2) * t_coef;
	double tan = average;
	double e_k = kelvin * tan;
	std::cout << e_k<<std::endl;

	double delta_e_k = sqrt((average * average  * delta_t * delta_t) / 9.0 + kelvin * kelvin * delta_tan * delta_tan);
	std::cout << delta_e_k << std::endl;

	double u_eb = aver(data1);
	std::cout << u_eb << std::endl;
	double avar_ln = aver(data2);
	std::cout << avar_ln << std::endl;
	double ln_i_0 = avar_ln - (e_k * u_eb) / kelvin;
	double i_0 = exp(avar_ln - (e_k * u_eb) / kelvin);
	std::cout << i_0 << std::endl;
	std::cout << std::endl;
	std::cout << ln_i_0 << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < data1.size(); i++)
	{
		std::cout << data1[i] << " " << ln_i_0 + e_k * data1[i] / kelvin << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;


	std::ofstream file;
	file.open("result1.csv");
	for (int i = 0; i < a2.size(); i++)
	{
		file << i + 1 << " & " << data1[data1.size() / 2 + i] << " & " << data1[i] << " & " << x_[i]
			 << " & " << data2[data2.size() / 2 + i] << " & " << data2[i] << " & " << y_[i]
			 << " & " << a[i] << " & " << a_d[i] << " & " << a2[i] << " \\\\ " << std::endl;
	}
	file.close();

	return 0;
}

