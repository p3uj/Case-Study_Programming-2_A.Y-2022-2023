#include<stdio.h>
#include<malloc.h>  // header file for allocating a memory location
#include<stdlib.h>  // header file for clearing the screen.
#include<conio.h>   // header file for getch
int choice, createdDoubly, temp, deleteNum, nodeCount, found;
char consearch;

struct node{
    struct node *prev;
    int x;
    struct node *next;
};
/* - *head pointer variable used for NORMAL MEMORY LOCATION to pin the FIRST NUMBER in normal and reverse order.
    - *normal pointer variable used para sa normal order ng memory location. (Sineparate natin 'yong memory
    location ng pang normal order at sorted order para ma-access pa rin natin 'yong normal order kahit na
    mag-add tayo ng mga numbers). (Ang normal memory location ang gagamitin natin sa pag-display ng normal
    at reverse order).
    - *compare1 pointer variable used to point the number(node) to be compared at ito rin ay madalas umiikot
    for comparison. (Ginagamit para sa sorting (ascending at descending), inserting ng number(node) sa sorted
    linked list at deleting ng node).
    - *compare2 same purpose ng compare1 ang pinagkaiba lang ay ito ginagamit lang para sa inserting ng
    number(node) sa sorted linked list at deleting ng node.
    - *tail pointer variable used for NORMAL MEMORY LOCATION to pin the LAST NUMBER in normal and reverse order.
    - *sort pointer variable used para sa SORT MEMORY LOCATION. (Kailangan natin i-separate ang
    memory location ng iso-sort o sorted list dahil ito ang gagalawin nating memory location sa pag-sort ng
    mga numbers at pag-add rin ng numbers). (Ang sort memory location din ang gagamitin natin sa pag-sort
    at display ng ascending at descending order).
    - *headSort pointer variable used for SORT MEMORY LOCATION to pin the FIRST NUMBER in ascending and
    descending order.
    - *tailSort pointer variable used for SORT MEMORY LOCATION to pin the LAST NUMBER in ascending and
    descending order.

    - We need to use compare1 and compare2 para madetermine natin kung sa gitna ba ng pinagpo-pointan na
    number ng compare1 at compare2 natin ilalagay ang number to be insert. Example, ang number na pinagpo-
    pointan ng compare1 ay 3, at compare2 ay 5, tapos ang number to be insert is 4, at 'yong 4 na 'yan ay
    naka-lagay sa SORT MEMORY LOCATION. Kapag nag-true ang lumabas sa condition (which is
    if ((sort->x >= compare1->x) && (sort->x <= compare2->x)) ibig sabihin ganto raw (if (4>=3) && (4<=5)),
    kapag true ang lumabas d'yan after i-evaluate, ma-iinsert na antin si 4 sa gitna ni 3 at 5.
*/
struct node *head, *normal, *compare1, *compare2, *tail, *sort, *headSort, *tailSort;

//-----Creating a Doubly Linked List-----//
void createDoubly(){
    createdDoubly = 0;  // In default, ang value ni createdDoubly ay 0. Also, kapag magke-create ulit ng bagong doubly linked list, magiging 0 ulit ang value nito.
    printf("------------------------------------------------------------\n");
    printf("\t(1) Create a Doubly Linked List\n");
    printf("!!! Enter a 0 to end the creating a Doubly Linked List!!!\n");
    printf("------------------------------------------------------------\n");
    head=normal=tail=sort=headSort=tailSort=NULL;   // Initialize si head, normal, tail, sort, headSort at tailSort bilang NULL.

    normal = (struct node *)malloc(sizeof(struct node));  // Gagawa ng memory location para kay normal para mailagay ang number na ii-input.
    sort = (struct node *)malloc(sizeof(struct node));    // Gagawa ng memory location para kay sort para mailagay 'yong number na ika-copy.

    printf("Enter a number: ");
    scanf("%d", &normal->x);
    sort->x = normal->x;    // Kung ano man ang number na nasa normal->x ay ganon din 'yong number na malalagay sa normal->x. (In short, copy and paste lang ginawa natin).

// The while statement is used para magpa-enter s'ya ng magpa-enter ng number hanggat 'yong number na inenter n'ya ay hindi 0. (Kapag 0 na don lang hihinto ang pagpapa-enter kay user).
    while (normal->x != 0){
        createdDoubly=1;        // Sign if you have already created a node.(If the value of createdDoubly variable is 1, it means you already created a node). (Kailangan ito para ma-unlock 'yong menu).
        if (head==NULL){        // Papasok dito kapag naka-NULL pa rin ang head. Isang beses lang tayo papasok dito at iyon ay sa unang beses lang.
            head = normal;      // Ilalagay si head kung nasa'n man si normal.
            head->prev = NULL;  // Initialize 'yong laman ni head->prev to NULL.
            head->next = NULL;  // Initialize 'yong laman ni head->next to NULL.
            tail = normal;      // Ilalagay si tail kung nasa'n man si normal.
            headSort = sort;    // Ilalagay si headSort kung nasa'n man si sort.
            headSort->prev = NULL;    // Initialize 'yong laman ni headSort->prev to NULL.
            headSort->next = NULL;    // Initialize 'yong laman ni headSort->next to NULL.
            tailSort = sort;    // Ilalagay si tailSort kung nasa'n man si sort.
        }
        else {                  // Dito na papasok kapag false na si if statement. At dito na tayo lagi papasok kapag mag-enter ulit ng number. (pangalawang number, pangatlong number, so on...)
            tail->next = normal;  // Ili-linked si tail->next kay normal node.
            normal->prev = tail;  // Ili-linked si normal->prev kay tail node.
            normal->next = NULL;  // Initialize 'yong laman ni normal->next to NULL.
            tail = normal;        // Ililipat(Ilalagay) si tail kung nasa'n man si normal.
            tailSort->next = sort;  // Ili-linked si tailSort->next kay sort node.
            sort->prev = tailSort;  // Ili-linked si sort->prev kay tailSort node.
            sort->next = NULL;        // Initialize 'yong laman ni sort->next to NULL.
            tailSort = sort;        // Ililipat(Ilalagay) si tailSort kung nasa'n man si sort.
        }

        normal = (struct node *)malloc(sizeof(struct node));  // Allocate another memory location for normal in preparation of the next number to be input.
        sort = (struct node *)malloc(sizeof(struct node)); // Gagawa ng another memory location para kay normal para mailagay 'yong next number na ika-copy.

        printf("Enter a number: ");
        scanf("%d", &normal->x);
        sort->x = normal->x;    // Kung ano man ang number na nasa normal->x ay ganon din 'yong number na malalagay sa sort->x.
    }   // End of the while statement.
    printf("\n\nPress any key to go back to Main Menu...");
    getch();    // Hold the key to be entered from the user.
    system("cls");  // Clear the screen.
}
//-----End of the function-----//

//-----Display the Normal Order-----//
void normalDisplay(){
    if (choice==21){    // Kailangan itong condition(if (choice==21)) para hindi dito pumasok kapag kinol itong function mula sa insertNode function.
        printf("---------------------------------------------------\n");
        printf("\t(2) Display a Doubly Linked List\n");
        printf("---------------------------------------------------\n");
        printf("Normal Order\n");
        normal = head;    // Ilalagay si normal pointer variable kung nasa'n man si head pointer variable.
        while (normal != NULL){ // Mag-loloop ito hanggat ang normal pointer variable ay hindi naka-NULL.
            printf("%d  ", normal->x);   // Print 'yong number na nasa normal->x;
            normal = normal->next;  // Ilalagay(Ililipat) si normal kung nasa'n man naka-linked ang normal->next para na next na ipi-print na number.
        } // End of the while statement.
        printf("\n\nPress any key to go back to Main Menu...");
        getch();    // Hold the key to be entered from the user.
        system("cls");  // Clear the screen.
    } // End of if statement.
    else {  // Dito papasok kapag tinawag itong function mula sa insertNode Function. This statement also used para ma-copy at mailagay sa normal memory location ang gustong i-insert na number at i-linked ito.
        normal = (struct node *)malloc(sizeof(struct node));    // Gagawa ng bagong memory location para kay normal para mailagay dito 'yong number na ika-copy(which is number to be inserted).
        normal->x = sort->x;    // Kung ano man ang number na nasa sort->x(which is number na ii-insert) ay ganon din 'yong number na malalagay sa normal->x.
        tail->next = normal;    // Ili-linked 'yong node na tail->next kay normal node.
        normal->prev = tail;    // Ili-linked 'yong node na normal->prev kay tail node.
        normal->next = NULL;    // Initialize 'yong laman ni normal->next bilang NULL.
        tail = normal;          // Ililipat(ilalagay) si tail kay normal node para ma-update 'yong bagong last number sa linked list (which is 'yong number na ininsert ayon na ang BAGONG LAST NUMBER sa NORMAL MEMORY LOCATION ng linked list).
    } // End of else statement. (Balik sa insertNode at i-execute 'yong next statement doon).
}
//-----End of the function-----//

//-----Display the Reverse Order-----//
void reverseDisplay(){
    printf("---------------------------------------------------\n");
    printf("\t(2) Display a Doubly Linked List\n");
    printf("---------------------------------------------------\n");
    printf("Reverse Order\n");
    normal = tail;    // Ilalagay si normal pointer variable kung nasa'n man si tail pointer variable.
    while (normal != NULL){ // Mag-loloop ito hanggat ang normal pointer variable ay hindi naka-NULL.
        printf("%d  ", normal->x);   // Print 'yong number na nasa normal->x;
        normal = normal->prev;      // Ilalagay(Ililipat) si normal kung nasa'n man naka-linked ang normal->prev para na next na ipi-print na number.
    } // End of the while statement.
    printf("\n\nPress any key to go back to Main Menu...");
    getch();    // Hold the key to be entered from the user.
    system("cls");  // Clear the screen.
}
//-----End of the function-----//

//-----Sorting Part: Ascending Order (Balloon Sort)-----//
void sortingAs(){
    sort = headSort;    // Assign the sort pointer variable to headSort.
// The outer while statement ay maglo-loop lang s'ya ng maglo-loop hanggat 'yong sort pointer variable ay hindi naka-NULL.
    while (sort != NULL){   // Outer Loop
        compare1 = sort->next;  // Assign the compare1 where the sort->next was linked until NULL para sa comparison. (Ilalagay natin si compare1 kung sa'n man naka-linked si sort->next para sa comparison)
        while (compare1 != NULL){   // Inner Loop (This inner loop will keep looping unless the compare1 is equal to NULL)
            if (sort->x > compare1->x){ // Swap the value of sort->x and compare1->x kapag true ang lumabas pagtapos i-evaluate 'yong condition ng if statement.
                temp = compare1->x;     // temp variable will hold the value of compare1->x. (Ang laman ni temp variable ay 'yong number na nasa compare1->x).
                compare1->x = sort->x;  // The new value in compare1->x is the value stored of sort->x. (Kung ano man ang value ng nasa sort->x ay 'yon na rin ang BAGONG VALUE ng compare1->x)
                sort->x = temp;         // The new value in sort->x is the value stored in temp. (Kung ano man ang value ng nasa temp ay 'yon na rin ang BAGONG VALUE ng sort->x)
            }   // End of Swapping
            compare1 = compare1->next;  // Assign the compare1 where the compare1->next was linked until NULL para sa next comparison. (Ilalagay natin si compare1 kung sa'n man naka-linked si compare1->next para sa next comparison)
        }   // End of the Inner Loop
        sort = sort->next;  // Assign the sort where the sort->next was linked until NULL para sa next comparison. (Ilalagay natin si sort pointer variable kung sa'n man naka-linked si sort->next para sa next comparison)
    }   // End of the Outer Loop

    // We put the if statement para hindi magprint kapag tinatawag natin si sortingAs function mula sa insertNode function.
    // Printing the data in doubly linked list in Ascending order.
    if (choice==31){
        printf("---------------------------------------------------\n");
        printf("\t(3) Sorted Doubly Linked List\n");
        printf("---------------------------------------------------\n");
        printf("Ascending\n");
        sort = headSort;    // Assign the sort pointer variable to headSort.
        while (sort!=NULL){ // Mag-loloop ito hanggat ang sort pointer variable ay hindi naka-NULL.
            printf("%d  ", sort->x); // Print 'yong number na nasa sort->x.
            sort = sort->next;  // Ilalagay(Ililipat) si sort kung nasa'n man naka-linked ang sort->next.
        } // End of the while statement.
        printf("\n\nPress any key to go back to Main Menu...");
        getch();    // Hold the key to be entered from the user.
        system("cls");  // Clear the screen.
    }
}
//-----End of the function-----//

//-----Sorting Part: Descending Order (Balloon Sort)-----//
void sortingDes(){
    sort = headSort;    // Assign the sort pointer variable to headSort.
    while (sort != NULL){   // Outer Loop
        compare1 = sort->next;  // Assign the compare1 where the sort->next was linked until NULL para sa comparison. (Ilalagay natin si compare1 kung sa'n man naka-linked si sort->next para sa comparison)
        while (compare1 != NULL){   // Inner Loop (This inner loop will keep looping unless the compare1 is equal to NULL)
            if(sort->x < compare1->x){  // Swap the value of sort->x and compare1->x kapag true ang lumabas pagtapos i-evaluate 'yong condition ng if statement.
                temp = compare1->x;     // temp variable will hold the value of compare1->x. (Kung ano man ang number na nasa compare1->x ay ganon din ang magiging laman(number) ni temp variable).
                compare1->x = sort->x;  // The new value in compare1->x is the value stored of sort->x. (Kung ano man ang value ng nasa sort->x ay 'yon na rin ang BAGONG VALUE ng compare1->x)
                sort->x = temp;         // The new value in sort->x is the value stored in temp. (Kung ano man ang value ng nasa temp ay 'yon na rin ang BAGONG VALUE ng sort->x)
            }   // End of swapping
            compare1 = compare1->next;  // Assign the compare1 where the compare1->next was linked until NULL para sa next comparison. (Ilalagay natin si compare1 kung sa'n man naka-linked si compare1->next para sa next comparison)
        }   // End of the Inner Loop
        sort = sort->next;  // Assign the sort where the sort->next was linked until NULL para sa next comparison. (Ilalagay natin si sort pointer variable kung sa'n man naka-linked si sort->next para sa next comparison)
    }   // End of the Outer loop

    // Printing the data in doubly linked list.
    printf("---------------------------------------------------\n");
    printf("\t(3) Sorted Doubly Linked List\n");
    printf("---------------------------------------------------\n");
    printf("Descending\n");
    sort = headSort;    // Assign the normal pointer variable to head.
    while (sort!=NULL){ // Mag-loloop ito hanggat ang sort pointer variable ay hindi naka-NULL.
        printf("%d  ", sort->x); // Print 'yong number na nasa sort->x.
        sort = sort->next;  // Ilalagay(Ililipat) si sort kung nasa'n man naka-linked ang sort->next.
    } // End of the while statement.
    printf("\n\nPress any key to go back to Main Menu...");
    getch();    // Hold the key to be entered from the user.
    system("cls");  // Clear the screen.
}
//-----End of the function-----//

//-----Inserting a Node-----//
void insertNode(){
    sortingAs();    // Function call to sortingAs function (Tinawag natin si sortingAs function para i-sort muna ang mga numbers bago mag-add ng panibagong number kase isa sa mga requirements 'yon kaya pupunta tayo sa sortingAs Function).
    printf("---------------------------------------------------\n");
    printf("\t(4) Insert a Node\n");
    printf("---------------------------------------------------\n");
    sort = (struct node *)malloc(sizeof(struct node));  // Allocate another memory location for sort in preparation to the number to be insert. (Sa memory location ng sorted list natin ito ilalagay kase isa sa mga requirements 'yon kaya si sort memory location ang ginamit natin at hindi si normal memory location, pero hindi pa sya totally naka-linked).
    printf("Enter a number: ");
    scanf("%d", &sort->x);
    normalDisplay();    // Function call to normalDisplay function (Tinawag natin si normalDisplay function para i-copy 'yong number na ii-insert sa memory location ng normal kaya pupunta tayo sa normalDisplay Function).
    compare1 = headSort;   // Assign the compare1 to headSort for preparation in the following statements. (Ilalagay natin si compare1 kung nasa'n man si headSort para sa following statement).
/* The if statement is used to initialize the next and prev ng sort node to NULL for preparation
to the next statement. */
    if (compare1 != NULL){
        sort->next = NULL;
        sort->prev = NULL;
    }
/* The while statement is used to linked the number to be inserted and it will keep looping as long
as hindi pa nali-linked ang number to be inserted.*/
    while ((sort->next == NULL) && (sort->prev == NULL)){   // Kapag na-linked na ang sort->next(hindi na naka-NULL) o 'yong sort->prev(hindi na naka-NULL), hindi na ito maglo-loop(hindi na dito papasok).
        compare2 = compare1->next;    // Assign the compare2 where the compare1->next was linked for preparation to the comparison. (Ang purpose ng compare2 ay nabanggit na sa pinaka-taas).
        /* The if statement is used para ma-linked 'yong number to be inserted IF 'yong number to be inserted
        ay mas MABABA sa UNANG NUMBER ng ASCENDING order. Kapag pumasok dito sa if statement, mababago na rin
        ang UNANG NUMBER sa ASCENDING order.*/
        if (sort->x <= compare1->x){    // Kapag true ang lumabas after i-evaluate ang condition na 'to, ili-linked na n'ya ang number to be inserted.
            sort->next = compare1;  // Ili-linked 'yong node na sort->next kay compare1 node.
            compare1->prev = sort;  // Ili-linked 'yong node na compare1->prev kay sort node.
            sort->prev = NULL;      // Initialize 'yong laman ni sort->prev bilang NULL.
            headSort = sort;        // Ililipat(ilalagay) si headSort kay sort node para ma-update 'yong BAGONG FIRST NUMBER sa ASCENDING ORDER (which is 'yong BAGONG FIRST NUMBER na natin sa ASCEDNING ORDER ay ang number na ininsert).
        } // End of if statement
        /* The else if statement is used para ma-linked 'yong number to be inserted IF 'yong number
        to be inserted ay mas MATAAS sa LAST NUMBER ng ASCENDING order. Kapag pumasok dito sa else if statement,
        mababago na rin ang LAST NUMBER sa ASCENDING order.*/
        else if (sort->x >= tailSort->x){   // Kapag true ang lumabas after i-evaluate ang condition na 'to, ili-linked na n'ya ang number to be inserted.
            sort->prev = tailSort;  // Ili-linked 'yong node na sort->prev kay tailSort node.
            tailSort->next = sort;  // Ili-linked 'yong node na tailSort->next kay sort node.
            sort->next = NULL;      // Initialize 'yong laman ni sort->next bilang NULL.
            tailSort = sort;        // Ililipat(ilalagay) si tailSort kay sort node para ma-update 'yong BAGONG LAST NUMBER sa ASCENDING ORDER (which is 'yong BAGONG LAST NUMBER na natin sa ASCEDNING ORDER ay ang number na ininsert).
        } // End of else if statement
        /* The else if statement is used para ma-linked 'yong number to be inserted IF 'yong number to be
        inserted ay HINDI MATAAS SA UNANG NUMBER AT SA HULING NUMBER ng ASCENDING order. */
        else if ((sort->x >= compare1->x) && (sort->x <= compare2->x)){
            sort->prev = compare1; // Linked the sort->prev in the compare1 node.
            sort->next = compare2; // Linked the sort->next in the compare2 node.
            compare1->next = sort; // Linked the compare1->next in the sort node.
            compare2->prev = sort; // Linked the compare2->prev in the sort node.
        } // End of else if statement
        compare1 = compare1->next;    // Assign the compare1 where the compare1->next was linked for preparation to the next comparison.
    }   // End of the while loop
    printf("Number %d successfully inserted", sort->x);
    printf("\n\nPress any key to go back to Main Menu...");
    getch();    // Hold the key to be entered from the user.
    system("cls");  // Clear the screen.
}
//-----End of the function-----//

//-----Delete a node-----//
void deleteNode(){
    printf("---------------------------------------------------\n");
    printf("\t(5) Delete a Node\n");
    printf("---------------------------------------------------\n");
	printf("\nEnter a number to be deleted: ");
	scanf("%d", &deleteNum);

    // Deleting the number in normal memory location
    normal = head;  // Ilalagay si normal pointer variable kung nasa'n man si head pointer variable.
    while (normal != NULL){ // Mag-loloop ito hanggat ang normal pointer variable ay hindi naka-NULL.
        found = 0;  // In default, ang value ni found variable ay 0. Gagamitin natin si found variable para madetermine kung nasa linked list ba ang number na ide-delete.
        compare2 = normal->next;    // Ilalagay si compare2 kung sa'n man naka-linked si normal->next. Kailangan ito para sa pag-update ng linked kapag ide-delete na ang number.
        /* The if statement is used para ma-unlinked 'yong head node kase 'yong number na nasa loob ng
        head node ang ide-delete, para totally ma-delete kailangan i-unlinked para 'di na s'ya kasama sa linked
        list. Also, kapag pumasok dito sa if statement, mababago na rin 'yong UNANG NUMBER sa normal order. */
        if (deleteNum == head->x){  // Kapag true ang lumabas after i-evaluate, ide-delete na 'yong unang number sa normal order.
            found = 1;  // Kapag ang number na ide-delete ay nasa linked list, then ang bagong value na ni found variable ay 1.
            head = compare2;    // Ilalagay(Ililipat) si head kung nasa'n man si compare2 para ma-update 'yong UNANG NUMBER sa normal order.
            normal->next = NULL;    // Initialize 'yong normal->next bilang NULL. Kailangan i-initialize para maging malinis 'yong linked list natin.
            head->prev = NULL;      // Initialize 'yong head->prev bilang NULL. Kailangan i-initialize para hindi na naka-linked ang BAGONG UNANG NUMBER natin sa normal order.
            break;  // Para i-stop ang while loop. Ibig sabihin hindi na pupunta pa sa following statement, diretso na agad sa next statement sa labas ng while loop which is 'yong if (found == 0).
        } // End of the if statement.
        /* The else if statement is used para ma-unlinked 'yong tail node kase 'yong number na nasa loob ng
        tail node ang ide-delete, para totally ma-delete kailangan i-unlinked para 'di na s'ya kasama sa linked
        list. Also, kapag pumasok dito, mababago na rin 'yong HULING NUMBER sa normal order. */
        else if (deleteNum == tail->x){ // Kapag true ang lumabas after i-evaluate, ide-delete na 'yong huling number sa normal order.
            found = 1;  // Kapag ang number na ide-delete ay nasa linked list, then ang bagong value na ni found variable ay 1.
            normal = tail;  // Ilalagay(Ililipat) si normal kung nasa'n man si tail para sa next statement.
            tail = normal->prev;    // Ilalagay(Ililipat) si tail kung sa'n man naka-linked si normal->prev para ma-update ang BAGONG LAST NUMBER sa normal order.
            tail->next = NULL;  // Initialize 'yong tail->next bilang NULL. Kailangan i-initialize para maging malinis 'yong linked list natin.
            normal->prev = NULL;// Initialize 'yong normal->prev bilang NULL. Kailangan i-initialize para maging malinis 'yong linked list natin.
            break;  // Para i-stop ang while loop. Ibig sabihin hindi na pupunta pa sa following statement, diretso na agad sa next statement sa labas ng while loop which is 'yong if (found == 0).
        } // End of the if statement.
        /* The else if statement is used para ma-unlinked 'yong normal node kase 'yong number na nasa loob ng
        normal node ang ide-delete, para totally ma-delete kailangan i-unlinked para 'di na s'ya kasama sa linked
        list. Also, kapag pumasok dito, mababago na rin 'yong linked ni compare1 node at compare2 node. */
        else if (deleteNum == normal->x){   // Kapag true ang lumabas after i-evaluate, ide-delete na 'yong number na nasa normal->x.
            found = 1;  // Kapag ang number na ide-delete ay nasa linked list, then ang bagong value na ni found variable ay 1.
            normal->next = NULL;    // Initialize 'yong normal->next bilang NULL para maging malinis ang linked list.
            normal->prev = NULL;    // Initialize 'yong normal->next bilang NULL para maging malinis ang linked list.
            compare1->next = compare2;  // Ia-update ang linked. Ili-linked si compare1->next sa compare2 node para 'di na kasama 'yong number na ide-delete sa linked list.
            compare2->prev = compare1;  // Ia-update ang linked. Ili-linked si compare2->prev sa compare1 node para 'di na kasama 'yong number na ide-delete sa linked list.
        } // End of the else if statement.
        normal = normal->next;  // Ilalagay(Ililipat) si normal pointer variable kung sa'n man naka-linked si normal->next para incase na mag-true na ang next comparison ay mali-linked natin s'ya sa tamang node.
        if (compare2 != NULL)
            compare1 = compare2->prev;  // Ilalagay(Ililipat) si compare1 pointer variable kung sa'n man naka-linked si compare2->prev para incase na mag-true na ang next comparison ay mali-linked natin s'ya sa tamang node.
    } // End of while statement.

    if (found == 0) // Kapag ang value ng found variable ay 0 pa rin after umikot sa while loop, ibig sabihin wala sa linked list 'yong number na ide-delete.
        printf("%d is not in the list\n", deleteNum);
    else
        printf("%d is successfully deleted!\n", deleteNum);
    printf("\n\nPress any key to go back to Main Menu...");
    getch();    // Hold the key to be entered from the user.
    system("cls");  // Clear the screen.

    // Deleting the number in ascending memory location
    sort = headSort;    // Ilalagay si sort pointer variable kung nasa'n man si headSort pointer variable.
	while (sort != NULL){   // Mag-loloop ito hanggat ang normal pointer variable ay hindi naka-NULL.
		compare2 = sort->next;  // Ilalagay si compare2 kung sa'n man naka-linked si sort->next. Kailangan ito para sa pag-update ng linked kapag ide-delete na ang number.
		/* The if statement is used para ma-unlinked 'yong headSort node kase 'yong number na nasa loob ng
        headSort node (which is UNANG NUMBER SA ASCENDING ORDER) ang ide-delete, para totally ma-delete
        kailangan i-unlinked para 'di na s'ya kasama sa linked list. Also, kapag pumasok dito sa if statement,
        mababago na rin 'yong UNANG NUMBER sa ascending order. */
        if (deleteNum == headSort->x){  // Kapag true ang lumabas after i-evaluate, ide-delete na 'yong unang number sa ascending order.
			headSort = compare2;    // Ilalagay(Ililipat) si headSort kung nasa'n man si compare2 para ma-update 'yong UNANG NUMBER sa ascending order.
			sort->next = NULL;  // Initialize 'yong sort->next bilang NULL. Kailangan i-initialize para maging malinis 'yong linked list natin.
			headSort->prev = NULL;  // Initialize 'yong headSort->prev bilang NULL. Kailangan i-initialize para hindi na naka-linked ang BAGONG UNANG NUMBER natin sa ascending order.
            break;  // Para i-stop ang while loop. Ibig sabihin hindi na pupunta pa sa following statement, diretso na agad sa next statement sa labas ng while loop which is 'yong if (found == 0).
		} // End of if stament.
        /* The else if statement is used para ma-unlinked 'yong tailSort node kase 'yong number na nasa loob ng
        tailSort node (which is LAST NUMBER IN ASCENDING ORDER) ang ide-delete, para totally ma-delete kailangan
        i-unlinked para 'di na s'ya kasama sa linked list. Also, kapag pumasok dito, mababago na rin 'yong
        HULING NUMBER sa ascending order. */
		else if (deleteNum == tailSort->x){ // Kapag true ang lumabas after i-evaluate, ide-delete na 'yong huling number sa ascending order.
			sort = tailSort;    // Ilalagay(Ililipat) si sort kung nasa'n man si tailSort para sa next statement.
			tailSort = sort->prev;  // Ilalagay(Ililipat) si tailSort kung sa'n man naka-linked si sort->prev para ma-update ang BAGONG LAST NUMBER sa ascending order.
			tailSort->next = NULL;  // Initialize 'yong tailSort->next bilang NULL. Kailangan i-initialize para maging malinis 'yong linked list natin.
			sort->prev = NULL;// Initialize 'yong sort->prev bilang NULL. Kailangan i-initialize para maging malinis 'yong linked list natin.
            break;  // Para i-stop ang while loop. Ibig sabihin hindi na pupunta pa sa following statement, diretso na agad sa next statement sa labas ng while loop which is 'yong if (found == 0).
		} // End of if else statement.
        /* The else if statement is used para ma-unlinked 'yong sort node kase 'yong number na nasa loob ng
        sort node ang ide-delete, para totally ma-delete kailangan i-unlinked para 'di na s'ya kasama sa linked
        list. Also, kapag pumasok dito, mababago na rin 'yong linked ni compare1 node at compare2 node. */
		else if (deleteNum == sort->x){
			sort->next = NULL;  // Initialize 'yong sort->next bilang NULL para maging malinis ang linked list.
			sort->prev = NULL;  // Initialize 'yong normal->next bilang NULL para maging malinis ang linked list.
			compare1->next = compare2;// Ia-update ang linked. Ili-linked si compare1->next sa compare2 node para 'di na kasama 'yong number na ide-delete sa linked list.
			compare2->prev = compare1;// Ia-update ang linked. Ili-linked si compare2->prev sa compare1 node para 'di na kasama 'yong number na ide-delete sa linked list.
		} // End of is else statement.
		sort = sort->next;  // Ilalagay(Ililipat) si sort pointer variable kung sa'n man naka-linked si sort->next para incase na mag-true na ang next comparison ay mali-linked natin s'ya sa tamang node.
        if (compare2 != NULL)
            compare1 = compare2->prev;// Ilalagay(Ililipat) si compare1 pointer variable kung sa'n man naka-linked si compare2->prev para incase na mag-true na ang next comparison ay mali-linked natin s'ya sa tamang node.
	} // End of while statement.
}
//-----End of the function-----//

//-----Search a Number-----//
void searchNode(){
    printf("---------------------------------------------------\n");
    printf("\t(6) Search a Number in the List\n");
    printf("---------------------------------------------------\n");
    sortingAs();    // Function call to sortingAs function (Pupunta tayo sa sortingAs function). Also, inilagay natin itong function para if ever na nag-create ng doubly linked list tapos hindi muna sinort ang list at dumiretso agad sa search function, madi-display natin 'yong tamang bilang kung pang ilang node ang number na hinahanap.

    consearch = 'Y';    // Initialize consearch variable to Y para makapasok sa while statement.

    while (consearch == 'Y' || consearch == 'y'){   // Maglo-loop ito hanggat 'yong value ng consearch natin ay Y or y.
        int searchNum;
        system("cls");  // Clear the screen.
        printf("---------------------------------------------------\n");
        printf("\t(6) Search a Number in the List\n");
        printf("---------------------------------------------------\n");
        printf("\nEnter a number to search: ");
        scanf("%d", &searchNum);

        // For normal memory location (Normal Order)
        found=0;    // naka set sa 0 as default. also, kapag magsesearch ulit si user ng another number, iseset ulit yung found and nodeCount sa 0 kasi panibago ulit na search
        nodeCount= 0;
        normal = head;  // Ilalagay si normal pointer variable kung nasa'n man si head pointer variable para sa next statement.
        printf("\nIn normal order:\n");
        while (normal != NULL){
            nodeCount++;    // Bibilangin ni nodeCount lahat ng node na madadaanan ni normal pointer variable.
            if (normal->x == searchNum){
                found = 1;  // set na si found as 1. Sign na nahanap na ang number to be search.
                printf("\n%d is in the list. It is in node number %d", searchNum, nodeCount);
            }
            normal = normal->next;  // Ilalagay(Ililipat) si normal pointer variable kung sa'n man naka-linked si normal->next para sa next comparison.
        }
        if (!found){ // if condition kung hindi nahanap yung number sa isang node
            printf("%d is not in the list.\n", searchNum);
        }

        // For sort memory location (Ascending Order)
        found=0;    // naka set sa 0 as default. also, kapag magsesearch ulit si user ng another number, iseset ulit yung found and nodeCount sa 0 kasi panibago ulit na search
        nodeCount= 0;
        sort = headSort;    // Ilalagay si sort pointer variable kung nasa'n man si headSort pointer variable para sa next statement.
        printf("\n\nIn ascending order:\n");
        while (sort != NULL) {
            nodeCount++;    // counter kung pang ilang node yung hinahanap na number sa list.
            if (sort->x == searchNum){
                found = 1; // nag set sya as 1, ibig sabihin nahanap nya yung hinahanap na number sa isang node
                printf("\n%d is in the list. It is in node number %d", searchNum, nodeCount);
            }
            sort = sort->next;  // Ilalagay(Ililipat) si sort pointer variable kung sa'n man naka-linked si sort->next para sa next comparison.
        }
        if (!found) { // if condition kung hindi nahanap yung number sa isang node
            printf("%d is not in the list.\n", searchNum);
        }

        printf("\n\nDo you want to search another number? (Y/N): ");
        scanf(" %c", &consearch);
    }
    printf("\n\nPress any key to go back to Main Menu...");
    getch();
    system("cls");
}
//-----End of the function-----//

//-----Option Part: Normal, Reverse, Ascending, Descending Order-----//
void displayAndSort(){
	if (choice==2){
        printf("---------------------------------------------------\n");
		printf("\t(2) Display a Doubly Linked List\n");
        printf("---------------------------------------------------\n");
	    printf("(21) Normal\n");
	    printf("(22) Reverse\n");
	    printf("\nEnter a choice: ");
        scanf("%d", &choice);

	    switch(choice){//Alternative sa if else para hindi mahaba
	    case 21: system("cls");normalDisplay(); break; //case to call the normalDisplay function
	    case 22: system("cls");reverseDisplay(); break; //case to call the reverseDisplay function
	    default: printf("Invalid choice! Returning to menu!");getch();break;
	    }
	    }
	else {
        printf("---------------------------------------------------\n");
		printf("\t(3) Sort a Doubly Linked List\n");
        printf("---------------------------------------------------\n");
	    printf("(31) Ascending\n");
	    printf("(32) Descending\n");
        printf("\nEnter a choice: ");
        scanf("%d", &choice);
        switch (choice){ //Alternative sa if else para hindi mahaba
        case 31: system("cls");sortingAs(); break; //case to call the sortingAs function
        case 32: system("cls");sortingDes(); break; // case to call the sortingDes function
        default: printf("Invalid choice! Returning to menu!");getch();break;
        }
    }
    system("cls");
}
//-----End of the function-----//

//-----Main Menu-----//
void menu(){
    printf("----------------------------------------");
    printf("\n\tMAIN MENU\n");
    printf("----------------------------------------\n");
    printf("(1) Create a new Doubly Linked List\n");
    printf("(2) Display a Doubly Linked List\n");
    printf("(3) Sort a Doubly Linked List\n");
    printf("(4) Insert a Node\n");
    printf("(5) Delete a Node\n");
    printf("(6) Search a Number in the List\n");
    printf("(7) Exit\n");
    printf("----------------------------------------\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
}
//-----End of the function-----//

int main(){
    while (createdDoubly==0){   // Outer loop. Maglo-loop ito hanggat ang value ni createdDoubly ay 0. In default, naka 0 si createdDoubly.
        printf("(1) Create a Doubly Linked List\n");
        printf("(7) Exit\n\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        while (choice!=1 && choice!=7){ // 1st inner loop. Maglo-loop ito hanggat ang choice na inenter ay hindi 1 o hindi 7.
            printf("\n!!!You must create a doubly linked list!!!\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
        } // End of the 1st innert loop.
        system("cls");  // for clearing the screen.
        if (choice==7){
            printf("--------------------------------------------------");
            printf("\n\tThank you for using our program!\n");
            printf("--------------------------------------------------\n");
            return 0;
        }
        else
            createDoubly();     // Function call to createDoubly function. (Pupunta tayo kay createDoubly function).

        while (createdDoubly==1){   // 2nd inncer loop. Maglo-loop ito hanggat ang value ni createdDoubly ay 1.
            menu(); // Function call to function menu (Pupunta tayo kay menu function).
            system("cls");  // for clearing the screen.
            switch (choice){
                case 1: createDoubly(); break;  // Execute this case if the choice is 1. Function call to createDoubly function.
                case 2: displayAndSort(); break;
                case 3: displayAndSort(); break;
                case 4: insertNode(); break;
                case 5: deleteNode(); break;
                case 6: searchNode(); break;
                case 7: printf("--------------------------------------------------");
                        printf("\n\tThank you for using our program!\n");
                        printf("--------------------------------------------------\n");
                        return 0;break;
                default: printf("!!! INVALID CHOICE !!!"); break;
            } // End of the switch case.
        } // End of the 2nd inner loop.
    } // End of the outer loop.
    return 0;
}