#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
#include <iterator>
using namespace std;
unsigned int M[8] = { 0, 0, 0, 1, 0, 1, 1, 1 };

void findKey()
{
	cout << "start\n";
	unsigned int reg_1 = 0;
	unsigned int reg_2 = 0;
	unsigned int reg_3 = 0;
	unsigned int reg_4 = 0;
	unsigned int reg_4_candidate = 0;
	unsigned int n = 800;
	unsigned int iteration_candidate = 0;
	unsigned int first_degree_x[19];
	unsigned int first_degree_y[22];
	unsigned int first_degree_z[23];
	char tmp;
	int pos;
	bool ind;
	ifstream system_x_input("system_x.txt");
	ifstream system_y_input("system_y.txt");
	ifstream system_z_input("system_z.txt");
	ifstream gamma_input("gamma.txt");
	if (!system_x_input.is_open() || !system_y_input.is_open() || !system_z_input.is_open() || !gamma_input.is_open())
	{
		cout << "Some of files did not open!\n";
		return;
	}
	vector<bitset<720>> vector1(1000);
	vector<bitset<720>> vector2(1000);
	vector<bitset<720>> vector3(1000);
	vector<bitset<720>> matrix(800);
	bitset<800> gamma;

	//заполнение матрицы предвычисленных данных
	for (int i = 0; i < vector1.size(); i++) {
		for (int k = 0; k < 190; k++) {
			if (k == 0)
				system_x_input >> tmp;
			system_x_input >> tmp;
			vector1[i][k] = tmp;
		}

	}
	for (int i = 0; i < vector2.size(); i++) {
		for (int k = 190; k < 443; k++) {
			if (k == 190)
				system_y_input >> tmp;
			system_y_input >> tmp;
			vector2[i][k] = tmp;
		}

	}
	for (int i = 0; i < vector3.size(); i++) {
		for (int k = 443; k < 719; k++) {
			if (k == 443)
				system_z_input >> tmp;
			system_z_input >> tmp;
			vector3[i][k] = tmp;
		}

	}

	//заполнение вектора с гаммой
	for (int i = 0; i < 800; i++) {
		gamma_input >> tmp;
		gamma[i] = tmp;
	}
	system_x_input.close();
	system_y_input.close();
	system_z_input.close();
	gamma_input.close();

	//заполнение массивов с позициями переменных 1-й степени
	ifstream first_degree_x_input("first_degree_x.txt");
	ifstream first_degree_y_input("first_degree_y.txt");
	ifstream first_degree_z_input("first_degree_z.txt");
	if (!first_degree_x_input.is_open() || !first_degree_y_input.is_open() || !first_degree_z_input.is_open())
	{
		cout << "Some of files did not open!\n";
		return;
	}
	for (int i = 18; i >= 0; i--) {
		first_degree_x_input >> first_degree_x[i];
		first_degree_x[i] -= 1;
	}
	for (int i = 21; i >= 0; i--) {
		first_degree_y_input >> first_degree_y[i];
		first_degree_y[i] -= 2;
	}
	for (int i = 22; i >= 0; i--) {
		first_degree_z_input >> first_degree_z[i];
		first_degree_z[i] -= 3;
	}
	first_degree_x_input.close();
	first_degree_y_input.close();
	first_degree_z_input.close();
	vector <bitset<720>>::iterator it;
	vector <bitset<720>>::iterator it1;
	vector <bitset<720>>::iterator it2;
	vector <bitset<720>>::iterator it3;

	//сборка уравнений
	for (reg_4_candidate = 75303; reg_4_candidate < 0x1ffff; reg_4_candidate++) {

		//cout << key << endl;
		it1 = vector1.begin();
		it2 = vector2.begin();
		it3 = vector3.begin();
		//чистим систему
		for (int i = 0; i < matrix.size(); i++)
		{
			matrix[i].reset();
		}

		ind = true;
		iteration_candidate = reg_4_candidate;
		//вносим гамму
		for (int k = 0; k < n; k++) {
			matrix[k][719] = gamma[k];
		}

		//дальнейшее заполнение системы
		for (int j = 0; j < n; j++) {
			unsigned int ctrl = (((iteration_candidate >> 15) & 1) << 2) | (((iteration_candidate >> 6) & 1) << 1) | (((iteration_candidate >> 1) & 1) << 0);
			if (M[ctrl] == ((iteration_candidate >> 15) & 1))
			{
				it1++;
			}
			if (M[ctrl] == ((iteration_candidate >> 6) & 1))
			{
				it2++;
			}
			if (M[ctrl] == ((iteration_candidate >> 1) & 1))
			{
				it3++;
			}
			matrix[j] ^= *it1;
			matrix[j] ^= *it2;
			matrix[j] ^= *it3;
			iteration_candidate = ((iteration_candidate << 1) | (((iteration_candidate >> 16) ^ (iteration_candidate >> 13) ^ (iteration_candidate >> 12) ^ (iteration_candidate >> 8)) & 1)) & 0x1ffff;
		}


		///////гаусс

		for (int i = 0; i < 719; i++)
		{
			pos = i + 1;
			if (!matrix[i].test(i)) {
				for (int j = i + 1; j < n; j++) {
					if (matrix[j].test(i)) {
						pos = j + 1;
						matrix[i] ^= matrix[j];
						matrix[j] ^= matrix[i];
						break;
					}
				}
			}
			for (int j = pos; j < n; j++) {
				if (matrix[j].test(i)) {
					matrix[j] ^= matrix[i];

				}
			}
		}
		bool indt = true;

		for (int i = 0; i < 719; i++) {
			if (!matrix[i].test(i))
			{
				ind = false;
				break;
			}
		}

		if (ind) {
			for (int i = 719; i < n; i++) {
				if (!matrix[i].none()) {
					ind = false;
					break;
				}
			}
		}

		if (ind) {
			///обратный ход
			for (int i = 718; i >= 0; i--) {
				if (matrix[i].test(i)) {
					for (int j = i - 1; j >= 0; j--) {
						if (matrix[j].test(i)) {
							matrix[j] ^= matrix[i];

						}
					}
				}
			}

			//извлекаем из матрицы заполнение регистров после инициализации
			reg_1 = 0;
			for (int i = 0; i < 19; i++) {
				reg_1 = reg_1 | matrix[first_degree_x[i]][719];
				reg_1 = reg_1 << 1;
			}
			reg_1 = reg_1 >> 1;
			reg_2 = 0;
			for (int i = 0; i < 22; i++) {
				reg_2 = reg_2 | matrix[first_degree_y[i]][719];
				reg_2 = reg_2 << 1;
			}
			reg_2 = reg_2 >> 1;
			reg_3 = 0;
			for (int i = 0; i < 23; i++) {
				reg_3 = reg_3 | matrix[first_degree_z[i]][719];
				reg_3 = reg_3 << 1;
			}
			reg_3 = reg_3 >> 1;
			reg_4 = reg_4_candidate;

			cout << "reg_1: " << hex << reg_1 << endl;
			cout << "reg_2: " << hex << reg_2 << endl;
			cout << "reg_3: " << hex << reg_3 << endl;
			cout << "reg_4: " << hex << reg_4 << endl;

			//находим ключ

			//откручиваем регистры
			for (int i = 0; i < 250; i++) {
				reg_1 = (reg_1 >> 1) | ((((((reg_1 >> 0) ^ (reg_1 >> 18) ^ (reg_1 >> 17) ^ (reg_1 >> 14)) & 1)) & 0x7ffff) << 18);
				reg_2 = (reg_2 >> 1) | ((((((reg_2 >> 0) ^ (reg_2 >> 21) ^ (reg_2 >> 17) ^ (reg_2 >> 13)) & 1)) & 0x3fffff) << 21);
				reg_3 = (reg_3 >> 1) | ((((((reg_3 >> 0) ^ (reg_3 >> 22) ^ (reg_3 >> 19) ^ (reg_3 >> 18)) & 1)) & 0x7fffff) << 22);
				reg_4 = (reg_4 >> 1) | ((((((reg_4 >> 0) ^ (reg_4 >> 14) ^ (reg_4 >> 13) ^ (reg_4 >> 9)) & 1)) & 0x1ffff) << 16);

			}
			//регистры открутили осталось восстановить ключ
			//используем предвычисления поэтому младшие биты сверху, но младший бит каждого из
			//регистров пропущен т.к. он установлен в 1 и информация уже утеряна
			//в данных из файла старшие биты справа далее слева        77

			unsigned int val_1 = 0;
			unsigned int val_2 = 0;
			unsigned int val_3 = 0;

			ifstream key_system_r1_input("key_system_r1.txt");
			ifstream key_system_r2_input("key_system_r2.txt");
			ifstream key_system_r3_input("key_system_r3.txt");
			ifstream key_system_r4_input("key_system_r4.txt");
			if (!key_system_r1_input.is_open() || !key_system_r2_input.is_open() || !key_system_r3_input.is_open() || !key_system_r4_input.is_open())
			{
				cout << "Some of files did not open!\n";
				return;
			}
			vector<bitset<65>> vectorkey(78);
			for (int i = 0; i < 18; i++) {
				if (i == 0) {
					key_system_r1_input >> val_1;
					key_system_r1_input >> val_2;
				}
				key_system_r1_input >> val_1;
				key_system_r1_input >> val_2;
				for (int j = 0; j < 32; j++) {
					vectorkey[i][j] = (val_1 >> j) & 1;
				}
				for (int j = 32; j < 64; j++) {
					vectorkey[i][j] = (val_2 >> (j - 32)) & 1;
				}

			}
			for (int i = 0; i < 21; i++) {
				if (i == 0) {
					key_system_r2_input >> val_1;
					key_system_r2_input >> val_2;
				}
				key_system_r2_input >> val_1;
				key_system_r2_input >> val_2;
				for (int j = 0; j < 32; j++) {
					vectorkey[i + 18][j] = (val_1 >> j) & 1;
				}
				for (int j = 32; j < 64; j++) {
					vectorkey[i + 18][j] = (val_2 >> (j - 32)) & 1;
				}
			}
			for (int i = 0; i < 22; i++) {
				if (i == 0) {
					key_system_r3_input >> val_1;
					key_system_r3_input >> val_2;
				}
				key_system_r3_input >> val_1;
				key_system_r3_input >> val_2;

				for (int j = 0; j < 32; j++) {
					vectorkey[i + 39][j] = (val_1 >> j) & 1;
				}
				for (int j = 32; j < 64; j++) {
					vectorkey[i + 39][j] = (val_2 >> (j - 32)) & 1;
				}

			}
			for (int i = 0; i < 16; i++) {
				if (i == 0) {
					key_system_r4_input >> val_1;
					key_system_r4_input >> val_2;
				}
				key_system_r4_input >> val_1;
				key_system_r4_input >> val_2;

				for (int j = 0; j < 32; j++) {
					vectorkey[i + 61][j] = (val_1 >> j) & 1;
				}
				for (int j = 32; j < 64; j++) {
					vectorkey[i + 61][j] = (val_2 >> (j - 32)) & 1;
				}

			}
			reg_1 = (reg_1 >> 1);
			for (int i = 0; i < 18; i++) {
				vectorkey[i][64] = (reg_1 & 1);
				reg_1 = (reg_1 >> 1);
			}
			reg_2 = (reg_2 >> 1);
			for (int i = 0; i < 21; i++) {
				vectorkey[i + 18][64] = (reg_2 & 1);
				reg_2 = (reg_2 >> 1);
			}
			reg_3 = (reg_3 >> 1);
			for (int i = 0; i < 22; i++) {
				vectorkey[i + 39][64] = (reg_3 & 1);
				reg_3 = (reg_3 >> 1);
			}
			reg_4 = (reg_4 >> 1);
			for (int i = 0; i < 16; i++) {
				vectorkey[i + 61][64] = (reg_4 & 1);
				reg_4 = (reg_4 >> 1);
			}

			for (int i = 0; i < 64; i++)
			{
				pos = i + 1;
				if (!vectorkey[i].test(i)) {
					for (int j = i + 1; j < 78; j++) {
						if (vectorkey[j].test(i)) {
							pos = j + 1;
							vectorkey[i] ^= vectorkey[j];
							vectorkey[j] ^= vectorkey[i];
							break;
						}
					}
				}
				for (int j = pos; j < 78; j++) {
					if (vectorkey[j].test(i)) {
						vectorkey[j] ^= vectorkey[i];

					}
				}
			}

			///обратный ход
			for (int i = 63; i >= 0; i--) {
				if (vectorkey[i].test(i)) {
					for (int j = i - 1; j >= 0; j--) {
						if (vectorkey[j].test(i)) {
							vectorkey[j] ^= vectorkey[i];

						}
					}
				}
			}
			key_system_r1_input.close();
			key_system_r2_input.close();
			key_system_r3_input.close();
			key_system_r4_input.close();
			unsigned __int64 final_key = 0;
			final_key |= (vectorkey[31][64] & 1);
			for (int i = 30; i >= 0; i--) {
				final_key = final_key << 1;
				final_key |= (vectorkey[i][64] & 1);
			}
			for (int i = 63; i >= 32; i--) {
				final_key = final_key << 1;
				final_key |= (vectorkey[i][64] & 1);
			}
			printf("Key: %.4X", final_key >> 32);
			printf("%.4X\n", final_key);
		}
	}
	cout << "finish\n";
}


void main()
{
	findKey();
	system("pause");
}
