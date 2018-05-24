#include<stdio.h>
#include<stdlib.h>
#define N 10 // Ο αριθμός των παραγγελιών

// Ορισμοί

typedef struct orders
{
	int customer_id;
	int town;
	int number_of_items;
	int priority;
	struct orders * next;
} orders;

typedef orders * pOrder;


typedef struct town_orders
{
	int customer_id;
	int number_of_items;
	int priority;
	struct town_orders * next;
} ATH_order, THE_order;

typedef ATH_order * pATH;
typedef THE_order * pTHE;

// συνάρτηση δημιουργίας αρχικής λίστας
void insertQ(pOrder *p, int customer_id, int town, int number_of_items, int priority)
{
	// ΒΑΛΤΕ ΕΔΩ ΤΟΝ ΚΩΔΙΚΑ ΣΑΣ
	// Dhmiourgoume enan deikti na deixnei se struct typou order kai desmeuoume tin aparaithth mnhmh
	struct orders *newOrder = (struct orders *)malloc(sizeof(struct orders));
	
	// An o deiktis deixnei se null tote simenei pws den uparxei arketi mnimi kai 
	// typwnoume minima sto xrhsth kai epistrefoume
	if(newOrder == NULL){
		printf("Den uparxei arketi mnimi\n");
		return;
	}
	// Diaforetika dimiourgoume to order pou einai struct kai tou dinoume ta dedomena pou perniountai
	// san orismata sti sunartisi
	// To customer_id einai to customer_id pou pernietai san orisma sti sunartisi kok
	newOrder->customer_id = customer_id;
	newOrder->town = town;
	newOrder->number_of_items = number_of_items;
	newOrder->priority = priority;
	// Bazoume to kainourgio order na deixnei ekei pou edeixne o pointer 
	newOrder->next = *p;
	// Kai ton deikti pou edeixne sta order na deixnei sto kainourgio order pou molis ftiaksame
	*p = newOrder;		
}

// συνάρτηση δημιουργίας και ταξινόμησης λιστών πόλεων
void insertQ1(pATH *q3, int customer_id, int number_of_items, int priority)
{
	// Akolouthwntas thn idia diadikasia opws apo panw ftiaxnoume enan pointer kai desmeuoume tin aparaithth mnimi
	struct town_orders *newOrder = (struct town_orders *)malloc(sizeof(struct town_orders));
	

	
	// Ftiaxnoume enan pointer pou deixnei se struct town_orders kai ton bazoume na deixnei ekei pou
	// deixnei o deiktis gia tin lista tis athinas
	struct town_orders *curr;
	curr = *q3;
	
	// An den uparxei arketi mnimi to emfanizoume sto xrhsth kai epistrefoume
	if(newOrder == NULL){
		printf("Adunamia desmeusis mnimis\n");
		return;
	}
	// Diaforetika ftiaxnoume to struct me ta aparaithta stoixeia pou perniountai san orisma sti sunartisi
	newOrder->customer_id = customer_id;
	newOrder->number_of_items = number_of_items;
	newOrder->priority = priority;
	
	// An o deixktis tis athinas deixnei se NULL i an ekei pou deixnei to priority einai 
	// mikrotero apo to priority tou newOrder pou ftiaksame
	if(*q3 == NULL || (*q3)->priority < newOrder->priority){
		// Tote prepei na baloume to newOrder pou ftiaksame ekei pou edeixne o head tis listas
		// kai ton head tis listas na deixnei sto kainourgio node pou ftiaksame
		newOrder->next = *q3;
		*q3 = newOrder;
	}
	else{
		// diaforetika xrhsimopoioume ton current deikti pou ftiaksame parapanw pou deixnei
		// ekei pou deixnei o head kai oso to epomeno stoixeio pou tha deiksi o deiktis den einai
		// NULL kai to priority tou opoiou einai megalutero apo to newOrder priority pou ftiaksame
		// proxwrame sto epomeno node
		while(curr->next != NULL && curr->next->priority > newOrder->priority){
			curr = curr->next;
		}
		// Otan to epomeno stoixeio apo auto pou deixnei o deiktis curr exei mikrotero priority apo to newOrder
		// pou theloume na eisagoume brikame stin ousia ti thesi stin opoia prepei na mpei kai einai amesws meta ti
		// thesi pou briskomaste twra kai prin apo tin epomeni, epomenws bazoume to newOrder na deixnei sto 
		// epomeno stoixeio pou deixnei o deiktis kai ton deikti na deixnei sto newOrder pou ftiaksame
		newOrder->next = curr->next;
		curr->next = newOrder;
	}
	
}

// Συναρτήσεις εκτυπώσεων

// συνάρτηση εκτύπωσης αρχικής λίστας
void printQ(pOrder q)
{
	// ΒΑΛΤΕ ΕΔΩ ΤΟΝ ΚΩΔΙΚΑ ΣΑΣ
	printf("\tSynolikes Paraggelies\n");
	printf("Kwdikos Poli Posotita Proteraiotita\n");
	// Ftiaxnoume ena deikti na deixnei se orders kai ton bazoume na deixnei ekei pou deixnei o head
	struct orders *curr = q;
	// Oso autos o deiktis den einai NULL tupwnoume ta stoixeia tou order kai proxwrame
	while(curr != NULL){
		printf("%d",curr->customer_id);
		printf("%6d",curr->town);
		printf("%6d",curr->number_of_items);
		printf("%6d",curr->priority);
		putchar('\n');
		curr = curr->next;
	}	
}

// συνάρτηση εκτύπωσης λίστας πόλης
void printQ1(pATH q1)
{
	// ΒΑΛΤΕ ΕΔΩ ΤΟΝ ΚΩΔΙΚΑ ΣΑΣ
	printf("Kwdikos Posotita Proteraiotita\n");
	// Antistoixa kai edw ftiaxnoume ena deikti na deixnei se town_orders kai ton bazoume na deixnei ekei pou deixnei o head
	struct town_orders *curr = q1;
	// Oso autos den einai NULL tupwnoume ta stoixeia tou struct kai proxwrame parakatw
	while(curr != NULL){
		printf("%6d",curr->customer_id);
		printf("%6d",curr->number_of_items);
		printf("%6d",curr->priority);
		putchar('\n');
		curr = curr->next;
	}
}

main()
{
	pOrder q, ALL;
	pATH q1;
	pTHE q2;
	int i, code, town, numOfItem, prior;
	srand(time(NULL));
	
// Αρχικοποιήσεις
	q=NULL;
	q1=NULL;
	q2=NULL;	

// Εισαγωγή δεδομένων
		
	// ΒΑΛΤΕ ΕΔΩ ΤΟΝ ΚΩΔΙΚΑ ΣΑΣ
	for(i = 0; i < N; i++){
		printf("Dwse kwdiko pelath: \n");
		scanf("%d",&code);
		do{
			printf("Dwse arithmo polis: (1)Athina \t (2)Thessaloniki \n");
			scanf("%d",&town);
		}while(!((town == 1) || ( town == 2)));
		printf("Dwse plithos proiontwn: \n");
		scanf("%d",&numOfItem);
		do{
			printf("Dwse arithmo proteraiotitas: (3)Ypsili, (2)Metria, (1)Xamili\n");
			scanf("%d",&prior);
		}while(!((prior == 1) || (prior == 2) ||(prior == 3)));
		insertQ(&q,code,town,numOfItem,prior);
		
//		An thelete gia na min bazete eseis dedomena o parakatw kwdikas dhmiourgei 
//		   random test dedomena sxoliaste ton apopanw kwdika kai trekste auton
//		code = (rand()%1000) +1;
//		town = (rand()%2) +1;
//		numOfItem = (rand()%300)+1;
//		prior=(rand()%3) +1;
//		insertQ(&q,code,town,numOfItem,prior);
		
		
	}
	
	printQ(q);
	putchar('\n');
// Διαχωρισμός παραγγελιών

	for (i=1;i<=N;i++)
	{
		if(q->town==1)
		{
			insertQ1(&q1, q->customer_id, q->number_of_items, q->priority);			
		}
		else
		{
			insertQ1(&q2, q->customer_id, q->number_of_items, q->priority);						
		}
		q=q->next;
	}

//Εκτυπώσεις	
	putchar('\n');		
	printf("   Paraggelies Athinas \n");
	printQ1(q1);
	putchar('\n');
	printf("   Paraggelies Thessalonikis \n");
	printQ1(q2);
	system("PAUSE");
}

