/* ΓΕ4 - Υποεργασία 1 */

#include <stdio.h>
#include <stdlib.h>

/*Δήλωση σταθερών τιμών για Μ και Ν*/
#define M 5
#define N 10

/*Δήλωση των συναρτήσεων*/
/*Μηδενισμός των πινάκων SalesPerProduct και SalesPerSeller*/
void init_matrix(int matrix[], int n);
/*Υπολογισμός των συνολικών πωλήσεων ανα προϊόν και αποθήκευσή τους στον πίνακα SalesPerProduct*/
void calc_salesperproduct(int Sales[][N], int SalesPerProduct[], int m, int n);
/*Υπολογισμός των συνολικών πωλήσεων ανα πωλητή και αποθήκευσή τους στον πίνακα SalesPerSeller*/
void calc_salesperseller(int Sales[][N], int SalesPerSeller[], int m, int n);
/*Προϊόν με τις μεγαλύτερες πωλήσεις*/
void print_topsellingProduct(int Prices[], int SalesPerProduct[], int n);
/*Προϊόν με τις λιγότερες πωλήσεις*/
void print_worstsellingProduct(int Prices[], int SalesPerProduct[], int n);
/*Εκτύπωση του πίνακα Sales*/
void print_matrix(int Sales[][N], int m, int n);

int main(void) {
	
	/*Δήλωση του πίνακα Prices*/
	int Prices[N] = { 25, 30, 50, 100, 20, 60, 40, 55, 65, 100 };
	
	/*Δήλωση του πίνακα Sales*/
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

	/*Κλήση calc_salesperproduct για τον υπολογισμό των συνολικών πωλήσεων ανα προϊόν*/
	calc_salesperproduct(Sales, SalesPerProduct, M, N);


	/*Κλήση της calc_salesperseller για τον υπολογισμό των συνολικών πωλήσεων ανα πωλητή*/
	calc_salesperseller(Sales, SalesPerSeller, M, N);

	/*Κλήση της print_topsellingProduct για το ποιο προϊόν έκανε τις μεγαλύτερες πωλήσεις*/
	print_topsellingProduct(Prices, SalesPerProduct, N);
	
	/*Κλήση της print_worstsellingProduct για το ποιο προϊόν έκανε τις λιγότερες πωλήσεις*/
	print_worstsellingProduct(Prices, SalesPerProduct, N);

	/*Κλήση της print_matrix για την εκτύπωση πίνακα*/
	print_matrix(Sales, M, N);

	system("PAUSE");
}

/*Υποερώτημα 1*/
/*Μηδενισμός των στοιχείων των πινάκων SalesPerProduct και SalesPerSeller*/
void init_matrix(int matrix[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		matrix[i] = 0;
	}
}

/*Υποερώτημα 2*/
/* Υπολογισμός των συνολικών πωλήσεων για κάθε προϊόν SalesPerProduct */
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

/*Υποερώτημα 3*/
/* Υπολογισμός των συνολικών πωλήσεων για κάθε πωλητή SalesPerSeller */
void calc_salesperseller(int Sales[][N], int SalesPerSeller[], int m, int n) {
	
	/* ΒΑΛΤΕ ΕΔΩ ΤΟΝ ΚΩΔΙΚΑ ΣΑΣ */
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

/*Υποερώτημα 4*/
/*Ποιο προϊόν έκανε τις περισσότερες πωλήσεις (σε μονάδες πώλησης) καθώς και το αντίστοιχο κέρδος σε Ευρώ*/
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


/*Υποερώτημα 5*/
/*Ποιο προϊόν έκανε τις λιγότερες πωλήσεις (σε συνολική αξία πώλησης) καθώς και το αντίστοιχο κέρδος σε Ευρώ*/
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

/*Υποερώτημα 6*/
/*Εκτύπωση του πίνακα Sales*/
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
