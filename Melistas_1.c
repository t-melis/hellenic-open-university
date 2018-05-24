/* ��4 - ���������� 1 */

#include <stdio.h>
#include <stdlib.h>

/*������ �������� ����� ��� � ��� �*/
#define M 5
#define N 10

/*������ ��� �����������*/
/*���������� ��� ������� SalesPerProduct ��� SalesPerSeller*/
void init_matrix(int matrix[], int n);
/*����������� ��� ��������� �������� ��� ������ ��� ���������� ���� ���� ������ SalesPerProduct*/
void calc_salesperproduct(int Sales[][N], int SalesPerProduct[], int m, int n);
/*����������� ��� ��������� �������� ��� ������ ��� ���������� ���� ���� ������ SalesPerSeller*/
void calc_salesperseller(int Sales[][N], int SalesPerSeller[], int m, int n);
/*������ �� ��� ����������� ��������*/
void print_topsellingProduct(int Prices[], int SalesPerProduct[], int n);
/*������ �� ��� ��������� ��������*/
void print_worstsellingProduct(int Prices[], int SalesPerProduct[], int n);
/*�������� ��� ������ Sales*/
void print_matrix(int Sales[][N], int m, int n);

int main(void) {
	
	/*������ ��� ������ Prices*/
	int Prices[N] = { 25, 30, 50, 100, 20, 60, 40, 55, 65, 100 };
	
	/*������ ��� ������ Sales*/
	int Sales[M][N] = {
		10,	9,	3,	6,	7,	5,	6,	6,	6,	7,
		5,	7,	8,	7,	5,	3,	5,	6,	1,	5,
		4,	7,	1,	10,	4,	4,	4,	5,	2,	9,
		3,	12,	2,	3,	3,	2,	8,	5,	2,	10,
		8,	18,	5,	2,	6,	1,	3,	5,	1,	5,
	};
	
	int SalesPerProduct[N], SalesPerSeller[M];
	init_matrix(SalesPerProduct, N);

	init_matrix(SalesPerSeller, M);

	/*����� calc_salesperproduct ��� ��� ���������� ��� ��������� �������� ��� ������*/
	calc_salesperproduct(Sales, SalesPerProduct, M, N);


	/*����� ��� calc_salesperseller ��� ��� ���������� ��� ��������� �������� ��� ������*/
	calc_salesperseller(Sales, SalesPerSeller, M, N);

	/*����� ��� print_topsellingProduct ��� �� ���� ������ ����� ��� ����������� ��������*/
	print_topsellingProduct(Prices, SalesPerProduct, N);
	
	/*����� ��� print_worstsellingProduct ��� �� ���� ������ ����� ��� ��������� ��������*/
	print_worstsellingProduct(Prices, SalesPerProduct, N);

	/*����� ��� print_matrix ��� ��� �������� ������*/
	print_matrix(Sales, M, N);

	system("PAUSE");
}

/*���������� 1*/
/*���������� ��� ��������� ��� ������� SalesPerProduct ��� SalesPerSeller*/
void init_matrix(int matrix[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		matrix[i] = 0;
	}
}

/*���������� 2*/
/* ����������� ��� ��������� �������� ��� ���� ������ SalesPerProduct */
void calc_salesperproduct(int Sales[][N], int SalesPerProduct[], int m, int n) {
	int i,j,sum;
	// Edw i ekswteriki mas epanalipsi paei sti stili prokeimenou 
	// na athroisoume kathe grammi kai na upologisoume tis sunolikes
	// poliseis gia kathe proion
	for(i = 0; i < n; i++){
		// arxikopoioume mia metabliti sum 
		sum=0;
		for(j = 0; j < m; j++){
			sum+=Sales[j][i];
		}
		SalesPerProduct[i] = sum;
	}
}

/*���������� 3*/
/* ����������� ��� ��������� �������� ��� ���� ������ SalesPerSeller */
void calc_salesperseller(int Sales[][N], int SalesPerSeller[], int m, int n) {
	
	/* ����� ��� ��� ������ ��� */
	int i,j,sum;
	// Theloume to ahtoirma gia kathe grammi - pwlhth epomenws arxikopoioume kathe fora mia metabliti sum
	// kai tin apothikeuoume ston pinaka SalesPerSeller sto telos
	for (i = 0; i < m; i++){
		sum = 0;
		for(j = 0; j < n; j++){
			sum+=Sales[i][j];
		}
		SalesPerSeller[i] = sum;
	}
}

/*���������� 4*/
/*���� ������ ����� ��� ������������ �������� (�� ������� �������) ����� ��� �� ���������� ������ �� ����*/
void print_topsellingProduct(int Prices[], int SalesPerProduct[], int n) {
	
	int i,max,profit,product;
	// arxikopoioume mia metabliti kai tis dinoume tin prwti timi tou pinaka
	max = SalesPerProduct[0];
	// diapername ton pinaka 
	for(i = 0; i < n; i++){
		// an broume megaluteri timi 
		if(SalesPerProduct[i] > max){
			// bazoume auti sti metabliti max
			 max=SalesPerProduct[i];
			 // briskoume ti proion
			 product = i+1;
			 // briskoume to kerdos se eurw
			 profit = max * Prices[i];
		}
	}
	printf("To proion me tis perissoteres pwlhseis einai to : %2d,\n Ekane %d pwlhseis \nTo kerdos tou se eurw einai: %2d Euro\n",product,max,profit);
}


/*���������� 5*/
/*���� ������ ����� ��� ��������� �������� (�� �������� ���� �������) ����� ��� �� ���������� ������ �� ����*/
void print_worstsellingProduct(int Prices[], int SalesPerProduct[], int n) {

	int i,min,profit,product;
	// Thetoume se mia metabliti min to prwto stoixeio tou pinaka
	min = SalesPerProduct[0];
	for(i = 0; i < n; i++){
		// An broume proion me mikroteres poliseis tote bazoume sto min auto
		if(SalesPerProduct[i] < min){
			min = SalesPerProduct[i];
			// Briskoume poio proion einai auto
			product = i+1;
			// Upologizoume to kerdos tou se euro
			profit= min *Prices[i];
		}
	}
	printf("To proion me tis ligoteres pwlhseis einai to : %2d,\n Ekane %d pwlhseis \nTo kerdos tou se eurw einai: %2d Euro\n",product,min,profit);
}

/*���������� 6*/
/*�������� ��� ������ Sales*/
void print_matrix(int Sales[][N], int m, int n) {

	int i,j;
	// Ektupwnoume ton pinaka
	for (i = 0; i < M; i++){
		for (j = 0; j < N; j++){
			// pairnoume xwro 4 psifiwn
			printf("%4d",Sales[i][j]);
		}
		putchar('\n');
	}
}
