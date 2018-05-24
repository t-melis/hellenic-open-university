#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define  N  10					// πλήθος κειμένων
#define  M  100					// μέγιστο μήκος κειμένου+1 
#define  MAX 500				// μέγιστο πλήθος διακριτών λέξεων


typedef struct node  			// κόμβος ανεστραμμένης λίστας
{ 
int document_number;			// κωδικός κειμένου
struct node * next;
} NODE;

struct word_occurrences			// σύνδεση λέξης με ανεστραμμένη λίστα της
{
char word[M];					// λέξη
NODE * occurrences_list_head;	//κεφαλή ανεστραμμένης λίστας λέξης
};

struct word_occurrences inverted_file[MAX];   // ανεστραμμένο αρχείο


void initialize(char document_table[][M], int size)  // ανάγνωση κειμένων στον πίνακα document_table
{
int i, j,  flag;
for (i=0; i<size; i++)
  do
  { 
  	printf("Δώστε το κείμενο με κωδικό %d.\n", i); 
  	flag=0;
  	gets(document_table[i]);
  	for (j=0; j<strlen(document_table[i]); j++) 		// προγραμματισμός αμυντικός
       if (!(isalnum(document_table[i][j]) || isspace(document_table[i][j])))
	   		{
       		flag=1;
			break;						
			}
  	if (flag) printf("Το κείμενο πρέπει να αποτελείται από αριθμητικούς και αλφαβητικούς χαρακτήρες και κενά.\n");
  }
   while(flag); 
}


void inverted_file_creation(char document_table[][M], int size)  // δημιουργία ανεστραμμένου αρχείου  (ερώτημα (α))
{
	int i,j,ctr = -1;
	
	// Για όλες τις γραμμές του κειμένου
	for (i = 0; i < size; i++){
		// Φτιάχνουμε δεικτη σε χαρακτήρα για τη λέξη,  και έναν πίνακα 100 θέσεων για τη γραμμή
		char *word;
		char temp[M];
		// Αντιγράφουμε στον πίνακα 100 θεσεων τη γραμμή
		strcpy(temp,document_table[i]);
		// Αποθηκεύουμε στο δείκτη τη διεύθυνση της πρώτης λέξης
		word = strtok(temp, " ");
		
		// Όσο υπάρχουν λέξεις
		while(word != NULL){
			// Βρήμακε μια λέξη, αξάνουμε τον δείκτη κατα 1 - αρχικά έχει την τιμή 0
			ctr++;
			// Αν αυτή είναι η πρώτη λέξη τότε πρέπει να την αποθηκεύσουμε και να φτιάξουμε λίστα
			if(ctr == 0){
				// Αντιγράφουμε στον πίνακα  των δομών στη θέση 0 τη λέξη
				strcpy(inverted_file[ctr].word, word);
				// Και φτιάχνουμε έναν κόμβο
				NODE *newNode = (NODE *)malloc(sizeof(NODE));
				// Ο κόμβος θα έχει σαν γραμμη τη γραμμη που βρήκαμε τη λέξη, δηλαδη το 0
				newNode->document_number = i;
				// Και θα δείχνει εκεί που δείχνει η κεφαλή της ανεστραμένης λίστας 
				newNode->next = inverted_file[ctr].occurrences_list_head;
				// Τελος βάζουμε τον head να δείχνει στον καινούριο κόμβο που φτιάξαμε
				inverted_file[ctr].occurrences_list_head = newNode;
			}else{
				// Αν δεν είναι η πρώτη λέξη
				// Χρησιμοποιούμε μια βοηθητική μεταβλητή που θα τη χρησιμοποιήσουμε σαν boolean,
				// αρχικά τη δηλώνουμε 0 δηλαδή false
				int check = 0;
				// Απο την πρώτη λέξη μέχρι την προηγούμενη της λέξης 
				for(j = 0; j < ctr; j++){
					// Αν βρούμε ίδια λέξη
					if(strcmp(inverted_file[j].word,word) == 0){
						// Αφαιρούμε απο το μετρητή 1, δεν θέλουμε καινούρια θέση στον πίνακα
						ctr--;
						// Η βοηθητική μεταβλητή γίνεται 1 - δηλαδή true, βρήκαμε ίδια λέξη
						check = 1;
						// Φτιάχνουμε έναν δείκτη να δείχνει εκεί που δείχνει η κεφαλή της λίστας
						NODE *temp = inverted_file[j].occurrences_list_head;
						// Και προχωράμε μέχρι να πάμε στον τελευταίο κόμβο
						while(temp->next != NULL){
							temp = temp->next;
						}
						// Φτιάχνουμε τον καινούριο κόμβο
						NODE *newNode = (NODE *)malloc(sizeof(NODE));
						// Και βάζουμε στο document_number τη γραμμή που βρισκόμαστε
						newNode->document_number = i;
						// Βάζουμε τον τελευταίο κόμβο να δείχνει στον κόμβο που φτιάξαμε
						temp->next = newNode;
						// Και τον κόμβο που φτιάξαμε να δείχνει στο NULL μιας και είναι τελευταίος
						newNode->next = NULL;
						// Βγαίνουμε απο το loop
						break;
					}
				}
				// Αν περάσει η for και το check ειναι false, δηλαδή το !check είναι true
				// δηλαδή δεν έχουμε βρει ίδια λέξη, η αν έχουμε βρει ήδια λέξη το !check είναι false
				if(!(check)){
					// Βάζουμε στη σωστή θέση του πίνακα τη λέξη
					strcpy(inverted_file[ctr].word, word);
					// Φτιάχνουμε τον κόμβο
					NODE *newNode = (NODE *)malloc(sizeof(NODE));
					// Του δίνουμε τη γραμμή που βρήκαμε τη λέξη
					newNode->document_number = i;
					// Βάζουμε τον κόμβο να δείχνει εκεί που δείχνει η κεφαλή της ανεστραμένης λίστας
					newNode->next = inverted_file[ctr].occurrences_list_head;
					// Και την κεφαλή της ανεστραμένης λίστας να δείχνει στον καινούριο κόμβο
					// Στην ουσία ό,τι κάναμε και για την πρώτη λέξη
					inverted_file[ctr].occurrences_list_head = newNode;
				}
			}
			// Προχωράμε στην επόμενη λέξη
			word = strtok(NULL, " ");
		}	
	}
	// Απο τη θέση 0 μέχρι και το ctr, δηλαδή το σημείο του πίνακα που υπάρχουν λέξεις
	for(i = 0; i <= ctr; i++){
		// Τυπώνουμε τη λέξη
		printf("%s ",inverted_file[i].word);
		// Φτιάχνουμε ένα δείκτη και τον βάζουμε να δείχνει εκεί που δείχνει η κεφαλή της ανεστραμένης λίστας της λέξης
		NODE *temp = inverted_file[i].occurrences_list_head;
		// Όσο υπάρχουν κόμβοι
		while(temp){
			// Τυπώνουμε σε ποιές γραμμές βρίσκεται η λέξη
			printf("%d ", temp->document_number);
			// Πάμε στον επόμενο κόμβο
			temp = temp->next;
		}
		// Τυπώνουμε μια γραμμή και πάμε στην επόμενη λέξη του πίνακα
		putchar('\n');
	}
}


void word_query(char * word) 											// συνάρτηση εύρεσης κειμένων που περιέχουν τη λέξη word (ερώτημα (β))
{
	int i;
	// Για όλες τις θέσεις του πίνακα
	for(i = 0; i < MAX; i++){
		// Αν βρούμε τη λέξη
		if(strcmp(inverted_file[i].word, word) == 0){
			// Φτιάχνουμε ένα δείκτη και τον βάζουμε να δείχνει εκεί που δείχνει η κεφαλή της ανεστραμένης λίστας
			// που υπάρχει η λέξη
			NODE *temp = inverted_file[i].occurrences_list_head;
			// Τυπώνουμε τη λέξη
			printf("Η λέξη \"%s\" βρίσκεται στη/ις γραμμη/ές: ",inverted_file[i].word);
			// Όσο ο δείκτης δεν είναι NULL
			while(temp){
				// Τυπώνουμε τις γραμμές που βρίσκεται η λέξη χρησιμοποιώντας την ανεστραμένη λίστα
				printf("%d ", temp->document_number);
				// Πάμε στον επόμενο κόμβο
				temp = temp->next;
			}
			// Τυπώνουμε μια κενή γραμμή και επιστρέφουμε
			putchar('\n');
			return;
		}
	}
	// Αν έχει τελειώσει η for και δεν έχει βρεθεί η λέξη τυπώνουμε πως
	// δεν υπάρχει και επιστρέφουμε
	printf("Η λέξη δεν υπάρχει\n");
	return;                                                
}    



int main()
{
char document_table[N][M];							//	πίνακας κειμένων
char  search_string[M];								// 	συμβολοσειρά ψαξίματος

system("chcp 1253");

printf("Δώστε ένα συνολο κειμένων:\n");				// 	ανάγνωση κειμένων στον πίνακα document_table				
initialize(document_table, N);

printf("\nΗ ανάστροφη αναπαράσταση είναι η ακολουθη:\n");
inverted_file_creation(document_table, N);

printf("\nΔώστε μια συμβολοσειρά για εντοπισμό των κειμένων που την περιέχουν:\n");
scanf("%s", search_string);
word_query(search_string);


return 0;
}
 
