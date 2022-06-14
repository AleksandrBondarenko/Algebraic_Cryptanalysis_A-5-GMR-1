#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <cmath>
using namespace std;
unsigned int rotate_1(unsigned int reg_1)
{
	reg_1 = ((reg_1 << 1) | (((reg_1 >> 18) ^ (reg_1 >> 17) ^ (reg_1 >> 16) ^ (reg_1 >> 13)) & 1)) & 0x7ffff;
	return reg_1;
}
unsigned int rotate_2(unsigned int reg_2)
{
	reg_2 = ((reg_2 << 1) | (((reg_2 >> 21) ^ (reg_2 >> 20) ^ (reg_2 >> 16) ^ (reg_2 >> 12)) & 1)) & 0x3fffff;
	return reg_2;
}
unsigned int rotate_3(unsigned int reg_3)
{
	reg_3 = ((reg_3 << 1) | (((reg_3 >> 22) ^ (reg_3 >> 21) ^ (reg_3 >> 18) ^ (reg_3 >> 17)) & 1)) & 0x7fffff;
	return reg_3;
}
unsigned int rotate_4(unsigned int reg_4)
{
	reg_4 = ((reg_4 << 1) | (((reg_4 >> 16) ^ (reg_4 >> 13) ^ (reg_4 >> 12) ^ (reg_4 >> 8)) & 1)) & 0x1ffff;
	return reg_4;
}
char M[8] = { 0, 0, 0, 1, 0, 1, 1, 1 };

void rotate_r1(unsigned int(&r1)[2][19]) {
	unsigned int tmp0 = 0;
	unsigned int tmp1 = 0;
	tmp0 ^= (r1[0][13] ^ r1[0][16] ^ r1[0][17] ^ r1[0][18]);
	tmp1 ^= (r1[1][13] ^ r1[1][16] ^ r1[1][17] ^ r1[1][18]);
	for (int i = 18; i >= 1; i--) {
		r1[0][i] = r1[0][i - 1];
		r1[1][i] = r1[1][i - 1];
	}
	r1[0][0] = tmp0;
	r1[1][0] = tmp1;
}
void rotate_r2(unsigned int(&r2)[2][22]) {
	unsigned int tmp0 = 0;
	unsigned int tmp1 = 0;
	tmp0 ^= (r2[0][12] ^ r2[0][16] ^ r2[0][20] ^ r2[0][21]);
	tmp1 ^= (r2[1][12] ^ r2[1][16] ^ r2[1][20] ^ r2[1][21]);
	for (int i = 21; i >= 1; i--) {
		r2[0][i] = r2[0][i - 1];
		r2[1][i] = r2[1][i - 1];
	}
	r2[0][0] = tmp0;
	r2[1][0] = tmp1;
}

void rotate_r3(unsigned int(&r3)[2][23]) {
	unsigned int tmp0 = 0;
	unsigned int tmp1 = 0;
	tmp0 ^= (r3[0][17] ^ r3[0][18] ^ r3[0][21] ^ r3[0][22]);
	tmp1 ^= (r3[1][17] ^ r3[1][18] ^ r3[1][21] ^ r3[1][22]);
	for (int i = 22; i >= 1; i--) {
		r3[0][i] = r3[0][i - 1];
		r3[1][i] = r3[1][i - 1];
	}
	r3[0][0] = tmp0;
	r3[1][0] = tmp1;
}
void rotate_r4(unsigned int(&r4)[2][17]) {
	unsigned int tmp0 = 0;
	unsigned int tmp1 = 0;
	tmp0 ^= (r4[0][8] ^ r4[0][12] ^ r4[0][13] ^ r4[0][16]);
	tmp1 ^= (r4[1][8] ^ r4[1][12] ^ r4[1][13] ^ r4[1][16]);
	for (int i = 16; i >= 1; i--) {
		r4[0][i] = r4[0][i - 1];
		r4[1][i] = r4[1][i - 1];
	}
	r4[0][0] = tmp0;
	r4[1][0] = tmp1;
}
void mrotate_r1(unsigned int(&r1)[19]) {
	unsigned int tmp0 = 0;
	tmp0 ^= (r1[13] ^ r1[16] ^ r1[17] ^ r1[18]);
	for (int i = 18; i >= 1; i--) {
		r1[i] = r1[i - 1];
	}
	r1[0] = tmp0;
}
void mrotate_r2(unsigned int(&r2)[22]) {
	unsigned int tmp0 = 0;
	tmp0 ^= (r2[12] ^ r2[16] ^ r2[20] ^ r2[21]);
	for (int i = 21; i >= 1; i--) {
		r2[i] = r2[i - 1];
	}
	r2[0] = tmp0;
}

void mrotate_r3(unsigned int(&r3)[23]) {
	unsigned int tmp0 = 0;
	tmp0 ^= (r3[17] ^ r3[18] ^ r3[21] ^ r3[22]);
	for (int i = 22; i >= 1; i--) {
		r3[i] = r3[i - 1];
	}
	r3[0] = tmp0;
}
void mrotate_r4(unsigned int(&r4)[17]) {
	unsigned int tmp0 = 0;
	tmp0 ^= (r4[8] ^ r4[12] ^ r4[13] ^ r4[16]);
	for (int i = 16; i >= 1; i--) {
		r4[i] = r4[i - 1];
	}
	r4[0] = tmp0;
}

void main(void)
{ // в данном коде каждый кусок генерирует свои анные(кусок может быть как закоменчен, так и незакоменчен. 
	//Можно легко подкорректировать при необходимости. Я не доводил этот код до ума, т.к. использовал только один раз.




	/*unsigned int r1[2][19] = {0};
	unsigned int r2[2][22] = {0};
	unsigned int r3[2][23] = {0};
	unsigned int r4[2][17] = {0};
	unsigned int keyvector [2] [64] = {0};
	for(int i = 0; i < 32; i++){
		keyvector[1][i] ^= 1;
		keyvector[1][i] = keyvector[1][i] << i;
	}
	for(int i = 32; i < 64; i++){
		keyvector[0][i] ^= 1;
		keyvector[0][i] = keyvector[0][i] << i;
	}
	for (unsigned int i = 0; i < 64; i++)
		{
		rotate_r1(r1);
		rotate_r2(r2);
		rotate_r3(r3);
		rotate_r4(r4);
		r1[0][0] ^= keyvector[0][i];
		r2[0][0] ^= keyvector[0][i];
		r3[0][0] ^= keyvector[0][i];
		r4[0][0] ^= keyvector[0][i];
		r1[1][0] ^= keyvector[1][i];
		r2[1][0] ^= keyvector[1][i];
		r3[1][0] ^= keyvector[1][i];
		r4[1][0] ^= keyvector[1][i];
		}
	ofstream out5("outkey5.txt");
	out5 << r1[0][0] << " " << r1[1][0] << "\n";
	out5 << r2[0][0] << " " << r2[1][0] << "\n";
	out5 << r3[0][0] << " " << r3[1][0] << "\n";
	for (int i = 0; i < 250; i++)
		{
		rotate_r1(r1);
		rotate_r2(r2);
		rotate_r3(r3);
		rotate_r4(r4);
		}
	ofstream out1("key_system_r1.txt");
	ofstream out2("key_system_r2.txt");
	ofstream out3("key_system_r3.txt");
	ofstream out4("key_system_r4.txt");

	for(int i = 0; i < 19; i ++){
		out1 << r1[0][i] << " " << r1[1][i] << "\n";
	}
	for(int i = 0; i < 22; i ++){
		out2 << r2[0][i] << " " << r2[1][i] << "\n";
	}
	for(int i = 0; i < 23; i ++){
		out3 << r3[0][i] << " " << r3[1][i] << "\n";
	}
	for(int i = 0; i < 17; i ++){
		out4 << r4[0][i] << " " << r4[1][i] << "\n";
	}
	out1.close();
	out2.close();
	out3.close();
	out4.close();
	out5.close();*/
	
		//генерация для крайнего этапа восстановления ключа
	ofstream out1("key_system_r1.txt");
	ofstream out2("key_system_r2.txt");
	ofstream out3("key_system_r3.txt");
	ofstream out4("key_system_r4.txt");
	unsigned int r1[2][19] = { 0 };
	unsigned int r2[2][22] = { 0 };
	unsigned int r3[2][23] = { 0 };
	unsigned int r4[2][17] = { 0 };
	unsigned int keyvector[2][64] = { 0 };
	for (int i = 0; i < 32; i++) {
		keyvector[1][i] ^= 1;
		keyvector[1][i] = keyvector[1][i] << i;
	}
	for (int i = 32; i < 64; i++) {
		keyvector[0][i] ^= 1;
		keyvector[0][i] = keyvector[0][i] << i;
	}
	for (unsigned int i = 0; i < 64; i++)
	{
		rotate_r1(r1);
		rotate_r2(r2);
		rotate_r3(r3);
		rotate_r4(r4);
		r1[0][0] ^= keyvector[0][i];
		r2[0][0] ^= keyvector[0][i];
		r3[0][0] ^= keyvector[0][i];
		r4[0][0] ^= keyvector[0][i];
		r1[1][0] ^= keyvector[1][i];
		r2[1][0] ^= keyvector[1][i];
		r3[1][0] ^= keyvector[1][i];
		r4[1][0] ^= keyvector[1][i];
	}

	for (int i = 0; i < 19; i++) {
		out1 << r1[0][i] << " " << r1[1][i] << "\n";
	}
	for (int i = 0; i < 22; i++) {
		out2 << r2[0][i] << " " << r2[1][i] << "\n";
	}
	for (int i = 0; i < 23; i++) {
		out3 << r3[0][i] << " " << r3[1][i] << "\n";
	}
	for (int i = 0; i < 17; i++) {
		out4 << r4[0][i] << " " << r4[1][i] << "\n";
	}
	out1.close();
	out2.close();
	out3.close();
	out4.close();





	////начальный	 этап
	//unsigned int reg_1 = 0, reg_2 = 0, reg_3 = 0, reg_4 = 0;
	//unsigned int k = 0;
	//unsigned int l = 0;
	//unsigned int lt = 0;
	//unsigned int ind = 0;
	//unsigned int count = 0;
	//unsigned int count2 = 0;
	//unsigned int key = 0;
	//char sum = 0;
	///*bitset<8388608> *F = new std::bitset<8388608>();///надо не битсет а массивы
	//bitset<8388608> *F1 = new std::bitset<8388608>();
	//bitset<8388608> *F2 = new std::bitset<8388608>();
	//bitset<8388608> *G = new std::bitset<8388608>();
	//bitset<8388608> *G1 = new std::bitset<8388608>();
	//bitset<8388608> *G2 = new std::bitset<8388608>();
	//bitset<8388608> *H = new std::bitset<8388608>();
	//bitset<8388608> *H1 = new std::bitset<8388608>();
	//bitset<8388608> *H2 = new std::bitset<8388608>();*/
	//char *F = new char [524288];
	//char *F1 = new char [524288];
	//char *F2 = new char [524288];
	//char *G = new char [4194304];
	//char *G1 = new char [4194304];
	//char *G2 = new char [4194304];
	//char *H = new char [8388608];
	//char *H1 = new char [8388608];
	//char *H2 = new char [8388608];

	//unsigned int PF [191];
	//unsigned int PG [254];
	//unsigned int PH [277];
	//unsigned int PFZ [19];
	//unsigned int PGZ [22];
	//unsigned int PHZ [23];
	//
	//ofstream foutz1("first_degree_x.txt");
	//ofstream foutz2("first_degree_y.txt");
	//ofstream foutz3("first_degree_z.txt");
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	////1111111111111111111111111111111111111111111111111111111111111111111111111111
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	///*for(int i = 0; i < 191; i++){
	//	PF[i] = 0;
	//}
	//for(int i = 0; i < 254; i++){
	//	PG[i] = 0;
	//}
	//for(int i = 0; i < 277; i++){
	//	PH[i] = 0;
	//}*/
	//sum = 0;
	//for(int i = 0; i < 524288; i++){//составление изначальной функции
	//	sum = (((i >> 15) & 1) << 2) | (((i >> 6) & 1) << 1) | (((i >> 1) & 1) << 0);
	//	F[i] = M[sum] ^ ((i >> 11) & 1);
	//	F1[i] = F[i] ;
	//	F2[i] = F[i];
	//}
	//
	int ind = 0;
	int count = 0;
	///ищем позиции где степень не более 2 для первой функции
	for (int i = 0; i < 4194304; i++) {
		for (int j = 0; j < 64; j++) {
			if (((i >> j) & 1) == 1) {
				ind++;
			}
			if (ind > 2) {
				break;
			}
			if ((i >> j) == 0) {
				break;
			}

		}
		if (ind <= 2) {
			cout << i << " ";
			count++;

		}

		/*if(ind == 1){
			if(count2 != temj - 1)
				cout << "error";
			PFZ[temj - 1] = countt;
			cout << PFZ[count2] << " ";
			foutz1 << PFZ[count2] << " ";
			count2++;

		}*/
		ind = 0;
	}
	cout << count;
	/*cout << endl << "count2 " << count2 << endl << endl;
	*for(int i = 0; i < 191; i++){

	}*/
	//*/
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		////222222222222222222222222222222222222222222222222222222222222222222222222222
		////////////////////////////////////////////////////////////////////////////////////////////////////////


		//sum = 0;
		//for(int i = 0; i < 4194304; i++){//составление изначальной функции
		//	sum = (((i >> 14) & 1) << 2) | (((i >> 8) & 1) << 1) | (((i >> 3) & 1) << 0);
		//	G[i] = M[sum] ^ ((i >> 1) & 1);
		//	G1[i] = G[i] ;
		//	G2[i] = G[i];
		//}
		//
		////ind = 0;
		//count = 0;
		////count2 = 0;
		// ///ищем позиции где степень не более 2 для 2 функции
		//for(int i = 0; i < 4194304; i ++){
		//	for(int j = 0; j < 64; j++){
		//	//	temj = j;
		//		if(((i >> j) & 1) == 1){
		//			ind ++;
		//		}
		//		if(ind > 2){
		//			break;
		//		}
		//		if((i >> j) == 0){
		//			break;
		//		}
		//	}
		//	if(ind <= 2){
		//		PG[count] = i;
		//		//countt = count;
		//		count ++;
		//	}
		//	/*if(ind == 1){
		//		PGZ[temj - 1] = countt + 191;
		//		foutz2 << PGZ[count2] << " ";
		//		count2++;
		//	}*/
		//	ind = 0;
		//}
		//

		///////////////////////////////////////////////////////////////////////////////////////////////////
		////33333333333333333333333333333333333333333333333333333333333333333333333333333333333333
		////////////////////////////////////////////////////////////////////////////////////////////////////

		//sum = 0;
		//for(int i = 0; i < 8388608; i++){//составление изначальной функции
		//	sum = (((i >> 19) & 1) << 2) | (((i >> 15) & 1) << 1) | (((i >> 4) & 1) << 0);
		//	H[i] = M[sum] ^ ((i >> 0) & 1);
		//	H1[i] = H[i];
		//	H2[i] = H[i];
		//}
		//
		////ind = 0;
		//count = 0;
		////count2 = 0;
		// //ищем позиции где степень не более 2 для 3 функции
		//for(int i = 0; i < 8388608; i ++){
		//	for(int j = 0; j < 64; j++){
		//		//temj = j;
		//		if(((i >> j) & 1) == 1){
		//			ind ++;
		//		}
		//		if(ind > 2){
		//			break;
		//		}
		//		if((i >> j) == 0){
		//			break;
		//		}
		//	}
		//	if(ind <= 2){
		//		PH[count] = i;
		//		//countt = count;
		//		count ++;
		//	}
		//	/*if(ind == 1){
		//		PHZ[temj - 1] = countt + 445;
		//		foutz3 << PHZ[count2] << " ";
		//		count2++;
		//	}*/
		//	ind = 0;
		//}

		//foutz1.close();
		//foutz2.close();
		//foutz3.close();

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////составление системы уравнений
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//


		/////////////////////////////////////////////////////////////////////////////////////
		/////начальные жегалкны
		///*k = 524288 / 2;
		//	l = 0;
		//	lt = 0;
		//	while(true)///многочлен жегалкина 1
		//	{
		//		while(l < 524288){
		//		for(int i = l; i < k + l; i ++)
		//		{
		//			F2[i + k]  = F2[i + k] ^ F2[i];
		//			lt ++;
		//		}
		//		l += k + lt;
		//		lt = 0;
		//		}
		//		l = 0;
		//		lt = 0;
		//		if(k == 1){
		//			break;
		//		}
		//		k /= 2;
		//	}
		//	k = 4194304 / 2;
		//	l = 0;
		//	lt = 0;
		//	while(true)///многочлен жегалкина 2
		//	{
		//		while(l < 4194304){
		//		for(int i = l; i < k + l; i ++)
		//		{
		//			G2[i + k]  = G2[i + k] ^ G2[i];
		//			lt ++;
		//		}
		//		l += k + lt;
		//		lt = 0;
		//		}
		//		l = 0;
		//		lt = 0;
		//		if(k == 1){
		//			break;
		//		}
		//		k /= 2;
		//	}
		//	k = 8388608 / 2;
		//	l = 0;
		//	lt = 0;
		//	while(true)///многочлен жегалкина 3
		//	{
		//		while(l < 8388608){
		//		for(int i = l; i < k + l; i ++)
		//		{
		//			H2[i + k]  = H2[i + k] ^ H2[i];
		//			lt ++;
		//		}
		//		l += k + lt;
		//		lt = 0;
		//		}
		//		l = 0;
		//		lt = 0;
		//		if(k == 1){
		//			break;
		//		}
		//		k /= 2;
		//	}*/

		//ofstream fout1("system_x.txt");
		//
		//
		//for(int i = 0; i < 722; i++){
		////ctrl = (((k >> 15) & 1) << 2) | (((k >> 6) & 1) << 1) | (((k >> 1) & 1) << 0);

		//
		//

		//	k = 524288 / 2;
		//	l = 0;
		//	lt = 0;
		//	while(true)///многочлен жегалкина 1
		//	{
		//		while(l < 524288){
		//		for(int j = l; j < k + l; j ++)
		//		{
		//			F2[j + k]  = F2[j + k] ^ F2[j];
		//			lt ++;
		//		}
		//		l += k + lt;
		//		lt = 0;
		//		}
		//		l = 0;
		//		lt = 0;
		//		if(k == 1){
		//			break;
		//		}
		//		k /= 2;
		//	}
		//	for(int j = 0; j < 191; j++){
		//		fout1 << F2[PF[j]];
		//		
		//	}
		//	fout1 << "\n";
		//	for(int j = 0; j < 524288; j++){
		//		F2[j] = F1[j];
		//	}
		//	for(int j = 0; j < 524288; j++){
		//		F2[j] = F1[rotate_1(j)];
		//	}
		//	for(int j = 0; j < 524288; j++){
		//		F1[j] = F2[j];
		//	}
		//}
		//fout1.close();
		//cout << "1 compleat\n";
		//
		//ofstream fout2("system_y.txt");
		//for(int i = 0; i < 722; i++){
		//	k = 4194304 / 2;
		//	l = 0;
		//	lt = 0;
		//	while(true)///многочлен жегалкина 2
		//	{
		//		while(l < 4194304){
		//		for(int j = l; j < k + l; j ++)
		//		{
		//			G2[j + k]  = G2[j + k] ^ G2[j];
		//			lt ++;
		//		}
		//		l += k + lt;
		//		lt = 0;
		//		}
		//		l = 0;
		//		lt = 0;
		//		if(k == 1){
		//			break;
		//		}
		//		k /= 2;
		//	}
		//	for(int j = 0; j < 254; j++){
		//		fout2 <<  G2[PG[j]];
		//	}
		//	fout2 << "\n";
		//	for(int j = 0; j < 4194304; j++){
		//		G2[j] = G1[j];
		//	}
		//	for(int j = 0; j < 4194304; j++){
		//		if(rotate_2(j) >= 4194304){
		//		cout << rotate_2(j) << endl;
		//		}
		//		G2[j] = G1[rotate_2(j)];
		//	}
		//	for(int j = 0; j < 4194304; j++){
		//		G1[j] = G2[j];
		//	}
		//}
		//fout2.close();
		//cout << "2 compleat \n";
		/////////////////////////////////////////////////////////////////////////////
		///**if (M[ctrl] == ((k >> 1) & 1))
		//{*/

		//ofstream fout3("system_z.txt");
		//for(int i = 0; i < 722; i++){
		//	/*for(int j = 0; j < 8388608; j++){
		//		H2[j] = H1[rotate_1(j)];
		//	}
		//	for(int j = 0; j < 8388608; j++){
		//		H1[j] = H2[j];
		//	}*/

		//	k = 8388608 / 2;
		//	l = 0;
		//	lt = 0;
		//	while(true)///многочлен жегалкина 3
		//	{
		//		while(l < 8388608){
		//		for(int j = l; j < k + l; j ++)
		//		{
		//			H2[j + k]  = H2[j + k] ^ H2[j];
		//			lt ++;
		//		}
		//		l += k + lt;
		//		lt = 0;
		//		}
		//		l = 0;
		//		lt = 0;
		//		if(k == 1){
		//			break;
		//		}
		//		k /= 2;
		//	}
		//	for(int j = 0; j < 277; j++){
		//		fout3 << H2[PH[j]];

		//	}
		//	fout3 << "\n";
		//	for(int j = 0; j < 8388608; j++){
		//		H2[j] = H1[j];
		//	}
		//	for(int j = 0; j < 8388608; j++){
		//		H2[j] = H1[rotate_3(j)];
		//	}
		//	for(int j = 0; j < 8388608; j++){
		//		H1[j] = H2[j];
		//	}
		//}
		//fout3.close();
		//cout << "3 compleat \n";
		//



		//
		///*for(int j = 0; j < 191; j++){
		//		matrix [i] [j] = F2[PF[j]];
		//	}
		//for(int j = 0; j < 254; j++){
		//		matrix [i] [j + 191] = G2[PG[j]];
		//	}
		//for(int j = 0; j < 277; j++){
		//		matrix [i] [j + 254 + 191] = H2[PH[j]];
		//	}*/

		//////восстановление 3-х ф-ций там сейчас не значения а жегалкин
		///*for(int j = 0; j < 524288; j++){
		//		F2[j] = F1[j];
		//	}
		//for(int j = 0; j < 4194304; j++){
		//		G2[j] = G1[j];
		//	}
		//for(int j = 0; j < 8388608; j++){
		//		H2[j] = H1[j];
		//	}*/

		// /// система составлена












		////unsigned int c = 0; 
		////for(int i = 0; i < 524288; i++){ //проверка жегалкина на адекватность
		////	cout << F1[i] << " " << i;
		////	cout << "\n";
		////	if(F1[i] == 1){
		////		c++;
		////	}
		////}
		///*cout << "\n" << "counter =  " << c << endl;*/
		///*for(int i = 0; i < 191; i ++){
		//	cout << P[i] << endl;
		//}*/ 



		////for(int i = 0; i < 191; i ++){ // в F1 сейчас коэффиценты жегалкина а в F функции. Тут выводится обрезанный столбец коэфф. жегалкина
		////	byte[i] = F1[P[i]] ;// pfyjcbv d ,bnctn
		//	
		///*}



		////cout << endl << endl;
		//
		//}*/
		//

		//cout << endl;
		//delete[]F;
		//delete[]F1;
		//delete[]F2;
		//delete[]G;
		//delete[]G1;
		//delete[]G2;
		//delete[]H;
		//delete[]H1;
		//delete[]H2;
	cout << "finish\n";
	system("pause");
}