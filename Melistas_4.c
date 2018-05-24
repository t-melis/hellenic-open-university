#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define  N  10					// ������ ��������
#define  M  100					// ������� ����� ��������+1 
#define  MAX 500				// ������� ������ ��������� ������


typedef struct node  			// ������ ������������� ������
{ 
int document_number;			// ������� ��������
struct node * next;
} NODE;

struct word_occurrences			// ������� ����� �� ������������ ����� ���
{
char word[M];					// ����
NODE * occurrences_list_head;	//������ ������������� ������ �����
};

struct word_occurrences inverted_file[MAX];   // ������������ ������


void initialize(char document_table[][M], int size)  // �������� �������� ���� ������ document_table
{
int i, j,  flag;
for (i=0; i<size; i++)
  do
  { 
  	printf("����� �� ������� �� ������ %d.\n", i); 
  	flag=0;
  	gets(document_table[i]);
  	for (j=0; j<strlen(document_table[i]); j++) 		// ��������������� ���������
       if (!(isalnum(document_table[i][j]) || isspace(document_table[i][j])))
	   		{
       		flag=1;
			break;						
			}
  	if (flag) printf("�� ������� ������ �� ����������� ��� ������������ ��� ������������ ���������� ��� ����.\n");
  }
   while(flag); 
}


void inverted_file_creation(char document_table[][M], int size)  // ���������� ������������� �������  (������� (�))
{
	int i,j,ctr = -1;
	
	// ��� ���� ��� ������� ��� ��������
	for (i = 0; i < size; i++){
		// ���������� ������ �� ��������� ��� �� ����,  ��� ���� ������ 100 ������ ��� �� ������
		char *word;
		char temp[M];
		// ������������ ���� ������ 100 ������ �� ������
		strcpy(temp,document_table[i]);
		// ������������ ��� ������ �� ��������� ��� ������ �����
		word = strtok(temp, " ");
		
		// ��� �������� ������
		while(word != NULL){
			// ������� ��� ����, �������� ��� ������ ���� 1 - ������ ���� ��� ���� 0
			ctr++;
			// �� ���� ����� � ����� ���� ���� ������ �� ��� ������������� ��� �� ��������� �����
			if(ctr == 0){
				// ������������ ���� ������  ��� ����� ��� ���� 0 �� ����
				strcpy(inverted_file[ctr].word, word);
				// ��� ���������� ���� �����
				NODE *newNode = (NODE *)malloc(sizeof(NODE));
				// � ������ �� ���� ��� ������ �� ������ ��� ������� �� ����, ������ �� 0
				newNode->document_number = i;
				// ��� �� ������� ���� ��� ������� � ������ ��� ������������ ������ 
				newNode->next = inverted_file[ctr].occurrences_list_head;
				// ����� ������� ��� head �� ������� ���� ��������� ����� ��� ��������
				inverted_file[ctr].occurrences_list_head = newNode;
			}else{
				// �� ��� ����� � ����� ����
				// �������������� ��� ��������� ��������� ��� �� �� ���������������� ��� boolean,
				// ������ �� ��������� 0 ������ false
				int check = 0;
				// ��� ��� ����� ���� ����� ��� ����������� ��� ����� 
				for(j = 0; j < ctr; j++){
					// �� ������ ���� ����
					if(strcmp(inverted_file[j].word,word) == 0){
						// ��������� ��� �� ������� 1, ��� ������� ��������� ���� ���� ������
						ctr--;
						// � ��������� ��������� ������� 1 - ������ true, ������� ���� ����
						check = 1;
						// ���������� ���� ������ �� ������� ���� ��� ������� � ������ ��� ������
						NODE *temp = inverted_file[j].occurrences_list_head;
						// ��� ��������� ����� �� ���� ���� ��������� �����
						while(temp->next != NULL){
							temp = temp->next;
						}
						// ���������� ��� ��������� �����
						NODE *newNode = (NODE *)malloc(sizeof(NODE));
						// ��� ������� ��� document_number �� ������ ��� �����������
						newNode->document_number = i;
						// ������� ��� ��������� ����� �� ������� ���� ����� ��� ��������
						temp->next = newNode;
						// ��� ��� ����� ��� �������� �� ������� ��� NULL ���� ��� ����� ����������
						newNode->next = NULL;
						// ��������� ��� �� loop
						break;
					}
				}
				// �� ������� � for ��� �� check ����� false, ������ �� !check ����� true
				// ������ ��� ������ ���� ���� ����, � �� ������ ���� ���� ���� �� !check ����� false
				if(!(check)){
					// ������� ��� ����� ���� ��� ������ �� ����
					strcpy(inverted_file[ctr].word, word);
					// ���������� ��� �����
					NODE *newNode = (NODE *)malloc(sizeof(NODE));
					// ��� ������� �� ������ ��� ������� �� ����
					newNode->document_number = i;
					// ������� ��� ����� �� ������� ���� ��� ������� � ������ ��� ������������ ������
					newNode->next = inverted_file[ctr].occurrences_list_head;
					// ��� ��� ������ ��� ������������ ������ �� ������� ���� ��������� �����
					// ���� ����� �,�� ������ ��� ��� ��� ����� ����
					inverted_file[ctr].occurrences_list_head = newNode;
				}
			}
			// ��������� ���� ������� ����
			word = strtok(NULL, " ");
		}	
	}
	// ��� �� ���� 0 ����� ��� �� ctr, ������ �� ������ ��� ������ ��� �������� ������
	for(i = 0; i <= ctr; i++){
		// ��������� �� ����
		printf("%s ",inverted_file[i].word);
		// ���������� ��� ������ ��� ��� ������� �� ������� ���� ��� ������� � ������ ��� ������������ ������ ��� �����
		NODE *temp = inverted_file[i].occurrences_list_head;
		// ��� �������� ������
		while(temp){
			// ��������� �� ����� ������� ��������� � ����
			printf("%d ", temp->document_number);
			// ���� ���� ������� �����
			temp = temp->next;
		}
		// ��������� ��� ������ ��� ���� ���� ������� ���� ��� ������
		putchar('\n');
	}
}


void word_query(char * word) 											// ��������� ������� �������� ��� ��������� �� ���� word (������� (�))
{
	int i;
	// ��� ���� ��� ������ ��� ������
	for(i = 0; i < MAX; i++){
		// �� ������ �� ����
		if(strcmp(inverted_file[i].word, word) == 0){
			// ���������� ��� ������ ��� ��� ������� �� ������� ���� ��� ������� � ������ ��� ������������ ������
			// ��� ������� � ����
			NODE *temp = inverted_file[i].occurrences_list_head;
			// ��������� �� ����
			printf("� ���� \"%s\" ��������� ���/�� ������/��: ",inverted_file[i].word);
			// ��� � ������� ��� ����� NULL
			while(temp){
				// ��������� ��� ������� ��� ��������� � ���� ��������������� ��� ����������� �����
				printf("%d ", temp->document_number);
				// ���� ���� ������� �����
				temp = temp->next;
			}
			// ��������� ��� ���� ������ ��� ������������
			putchar('\n');
			return;
		}
	}
	// �� ���� ��������� � for ��� ��� ���� ������ � ���� ��������� ���
	// ��� ������� ��� ������������
	printf("� ���� ��� �������\n");
	return;                                                
}    



int main()
{
char document_table[N][M];							//	������� ��������
char  search_string[M];								// 	������������ ���������

system("chcp 1253");

printf("����� ��� ������ ��������:\n");				// 	�������� �������� ���� ������ document_table				
initialize(document_table, N);

printf("\n� ��������� ������������ ����� � ��������:\n");
inverted_file_creation(document_table, N);

printf("\n����� ��� ������������ ��� ��������� ��� �������� ��� ��� ���������:\n");
scanf("%s", search_string);
word_query(search_string);


return 0;
}
 
