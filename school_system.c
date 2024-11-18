#include "school_system.h"
#define CS 1
#define MATH 2
#define ENGLISH 3
/*decleration of helper functions*/
static void print_welcome(void);
static void print_line   (void);
static void swap_nodes 	(node_t** list_head, uint32_t first_node_index, uint32_t sec_node_index);
static void sort_nodes_alphabetically	(node_t** list_head);
static void sort_by_grades				(node_t** list_head, uint8_t subject);
static void view_grades					(node_t** list_head, uint8_t subject);
static void validate_name  (uint8_t* str);
static void validate_date  (date_t* date);
static void adjust_null    (uint8_t* str);
static uint32_t nodes_size (node_t** list_head);
static uint8_t name_length (uint8_t* str);
static uint8_t num_width   (uint64_t num);
static uint8_t upper_letter(uint8_t letter);
static uint8_t lower_letter(uint8_t letter);



void MAIN_MENU (void)
{	
	uint32_t choice = 0;
	node_t* head = NULL;
	print_welcome();
	while(1)
	{
		printf("\nPress 1 to Add Student\n");
		printf("Press 2 to Delete Student\n");
		printf("Press 3 to Edit Student\n");
		printf("Press 4 to View Students\n");
		printf("Press 5 to Rank Students\n");
		printf("Press 6 to Exit\n= ");
		scanf("%d",&choice);
		getchar();
		switch(choice)
		{
			case 1:
				NEW_STUDENT(&head);
				break;

			case 2:
				printf("\nEnter the Number of the Student: ");
				scanf("%d",&choice);
				DELETE_STUDENT(&head,choice);
				break;

			case 3:
				printf("\nEnter the Number of the Student: ");
				scanf("%d",&choice);
				getchar();
				STUDENT_EDIT(&head,choice);
				break;

			case 4:
				STUDENT_LIST(&head);
				break;

			case 5:
				RANK_STUDENT(&head);
				break;

			case 6:
				goto EXIT;
				break;

			default:
				printf("\nINVALID CHOICE!!!\n");
				break;
		}

	}								 
	EXIT:
	0+0;
}



void NEW_STUDENT (node_t** list_head)
{
	/*initializting new node and mask to check the last node*/
	node_t* new_node = NULL;
	node_t* last_node = NULL;

	/*try to reserve place at heap*/
	new_node = (node_t*)malloc(sizeof(node_t));

	/*check if new_node reserved correctly*/
	if (new_node != NULL)
	{
		/*scanning the new data from the user*/
		printf("\nEnter the Student Name: ");
		fgets(new_node->student.name, 30, stdin);
		validate_name(new_node->student.name);
		
		printf("\nEnter the Student Birthday (day/month/year): ");
		scanf("%d/%d/%d",&(new_node->student.date.day), &(new_node->student.date.month), &(new_node->student.date.year));
		validate_date(&(new_node->student.date));

		printf("\nEnter the Student ID: ");
		scanf("%d",&(new_node->student.ID) );

		/*get char is used to protect fgets from the \n in the scanf above */
		getchar();
		printf("\nEnter the Student Address: ");
		fgets(new_node->student.address, 50, stdin);
		adjust_null(new_node->student.address);
		
		printf("\nEnter the Student Phone Number: ");
		scanf("%lld",&(new_node->student.phone_number) );

		STUDENT_SCORE(&new_node);
		getchar();


		/*check if the linked list is empty*/
		if (*list_head == NULL)
			{
				/*assign the head to this (first) element*/
				*list_head = new_node;
				
				/*assign the other empty link by null*/
				new_node->node_link = NULL;
			}
		else
			{
				/*finding the last node*/
				last_node = *list_head;

				/*the last node is linked by null so it will stop lopping at the last element*/
				while(last_node->node_link != NULL)
				{
					/*jumping to the link of next node*/
					last_node = last_node->node_link;
				}
				/*linking the last node by the new node*/
				last_node->node_link = new_node;

				/*assign the link of new last node by null*/
				new_node->node_link = NULL;
			}

		}
	else
	{
		printf("failed to create student");
	}

} 

void STUDENT_SCORE (node_t** list_head)
{
	printf("\nEnter Computer Science, Math ,English grades: ");
	scanf("%f,%f,%f", &((*list_head)->student.grade.cs), &((*list_head)->student.grade.math), &((*list_head)->student.grade.english) );
}



void DELETE_STUDENT (node_t** list_head, uint32_t position)
{
	if( (position < 1) || (position >nodes_size(list_head)) )
	{
		printf("\nWRONG NUMBER!!!\n");
	}
	else
	{	

		node_t* deleted_node = *list_head; 
		if (position == 1)
		{
			(*list_head) = (*list_head)->node_link;
			free(deleted_node);
		}
		else
		{
			node_t* node_before = *list_head;
			/*point the head to the required element*/
			for (int i = 0; i < position - 1; ++i)
			{
				deleted_node = (deleted_node)->node_link;
				if(i < position-2)
				{
					node_before = node_before->node_link;
				}
				else
				{
					/*Nothing*/
				}
			}
			/*copy the replaced node to new node*/
			node_before->node_link = (deleted_node)->node_link;
			(deleted_node)->node_link = NULL;
			free(deleted_node);
		
		}
		printf("\nDONE\n");
	}
}


void STUDENT_EDIT	(node_t** list_head, uint32_t position)
{
	if( (position < 1) || (position >nodes_size(list_head)) )
	{
		printf("\nWRONG NUMBER!!!\n");
	}
	else
	{
		node_t* selected_node = *list_head;
		uint32_t choice = 0;
		
		/*point the head to the required element*/
		for (int i = 0; i < position-1; ++i)
		{
			selected_node = selected_node->node_link;
		}	//selected_node = selected_node->node_link;

		printf("\nWhich Data You Need To Edit ?\n");
		printf("1)Name  2)Birthday  3)ID  4)Address  5)Phone Number\n= ");
		scanf("%d",&choice);
		getchar();
		
		switch(choice)
		{
			case 1:
				printf("\nEnter the New Student Name: ");
				fgets(selected_node->student.name, 30, stdin);
				validate_name(selected_node->student.name);	
				break;

			case 2:
				printf("\nEnter the New Student Birthday (day/month/year): ");
				scanf("%d/%d/%d",&(selected_node->student.date.day), &(selected_node->student.date.month), &(selected_node->student.date.year));
				break;

			case 3:
				printf("\nEnter the New Student ID: ");
				scanf("%d",&(selected_node->student.ID) );
				break;

			case 4:
				getchar();
				printf("\nEnter the New Student Address: ");
				fgets(selected_node->student.address, 50, stdin);
				adjust_null(selected_node->student.address);		
				break;

			case 5:
				printf("\nEnter the New Student Phone Number: ");
				scanf("%lld",&(selected_node->student.phone_number) );
				break;
			case 6:
				STUDENT_SCORE(&selected_node);
				getchar();
				break;
			default:			
				break;

		}
	}
}





void STUDENT_LIST (node_t** list_head)
{
	sort_nodes_alphabetically(list_head);


	if(*list_head != NULL)
	{
		node_t* last_node = *list_head;
		uint8_t ZERO = 0, index = 1;
		uint8_t name_width = 30, ID_width = 10, phone_number_width = 16, address_width = 45, birthday_width = 15 ;

		printf("\n\n");
		while( ((last_node->node_link )!= NULL) || (++ZERO) )
		{
			if (ZERO == 0)
			{
				/*printing the number of student*/
				printf("%d)\n",index);


				/*print the upper line*/
				printf(" ");
				for (int i = 0; i < 125; ++i) 
				{
					printf("_");
				}
				printf("\n");
				
				/*printing the titles*/
				printf("| 		Name	       |  ID	   |    Phone Number  |   		Address	    		     |  Date of Birth |");
				
				/**printing lower line*/
				print_line();

				/*printing the data*/
				printf("\n|%s",last_node->student.name);
				for (int i = 0; i < (name_width - name_length(last_node->student.name) ); ++i)
				{
					printf(" ");
				}printf("|");

				printf(" %d",last_node->student.ID);
				for (int i = 0; i < (ID_width - num_width(last_node->student.ID) ); ++i)
				{
					printf(" ");
				}printf("|");


				printf(" 0%d",last_node->student.phone_number);
				for (int i = 0; i < (phone_number_width - num_width(last_node->student.phone_number)); ++i)
				{
					printf(" ");
				}printf("|");


				printf(" %s",last_node->student.address);
				for (int i = 0; i < (address_width - name_length(last_node->student.address) ); ++i)
				{
					printf(" ");
				}printf("|");

				/*print 0 before number if it less than 10*/
				if (num_width(last_node->student.date.day) == 1)
					{
						printf(" 0%d/",last_node->student.date.day);
					}
				else
					{
						printf(" %d/",last_node->student.date.day);
					}
				
				/*also check month*/
				if (num_width(last_node->student.date.month) == 1)
				{
					printf("0");
				}
				else
				{
					/*noting*/
				}
				/*print month*/
				printf("%d/",last_node->student.date.month);
				/*print year*/
				printf("%d",last_node->student.date.year);
				

				for (int i = 0; i < birthday_width-10; ++i)
				{
					printf(" ");
				}printf("|");


				/*printing the last line we print the width of title then | to make the table separations*/
				print_line();

				printf("\n\n");
				index++;
				last_node = last_node->node_link;

			}	
			else
			{
				/*printing the number of student*/
				printf("%d)\n",index);


				/*print the upper line*/
				printf(" ");
				for (int i = 0; i < 125; ++i) 
				{
					printf("_");
				}
				printf("\n");
				
				/*printing the titles*/
				printf("| 		Name	       |  ID	   |    Phone Number  |   		Address	    		     |  Date of Birth |");
				
				/**printing lower line*/
				print_line();

				/*printing the data*/
				printf("\n|%s",last_node->student.name);
				for (int i = 0; i < (name_width - name_length(last_node->student.name) ); ++i)
				{
					printf(" ");
				}printf("|");

				printf(" %d",last_node->student.ID);
				for (int i = 0; i < (ID_width - num_width(last_node->student.ID) ); ++i)
				{
					printf(" ");
				}printf("|");


				printf(" 0%d",last_node->student.phone_number);
				for (int i = 0; i < (phone_number_width - num_width(last_node->student.phone_number)); ++i)
				{
					printf(" ");
				}printf("|");


				printf(" %s",last_node->student.address);
				for (int i = 0; i < (address_width - name_length(last_node->student.address) ); ++i)
				{
					printf(" ");
				}printf("|");

				/*print 0 before number if it less than 10*/
				if (num_width(last_node->student.date.day) == 1)
					{
						printf(" 0%d/",last_node->student.date.day);
					}
				else
					{
						printf(" %d/",last_node->student.date.day);
					}
				
				/*also check month*/
				if (num_width(last_node->student.date.month) == 1)
				{
					printf("0");
				}
				else
				{
					/*noting*/
				}
				/*print month*/
				printf("%d/",last_node->student.date.month);
				/*print year*/
				printf("%d",last_node->student.date.year);
				

				for (int i = 0; i < birthday_width-10; ++i)
				{
					printf(" ");
				}printf("|");


				/*printing the last line we print the width of title then | to make the table separations*/
				print_line();

				printf("\n\n");
				index++;
				last_node = last_node->node_link;

				break;
			}		
		}
	}
	else
	{
		printf("\nThere is No Students to View !\n");
	}
}

void RANK_STUDENT (node_t** list_head)
{
	uint32_t choice = 0;
	/*taking the subject from user*/
	begin:
	printf("\nPress 1 for CS, 2 for MATH, 3 for english: ");
	scanf("%d",&choice);
	
	/*sorting according to certain subject*/
	switch(choice)
	{
		case CS:
			sort_by_grades(list_head,CS);
			break;

		case MATH:
			sort_by_grades(list_head,MATH);
			break;

		case ENGLISH:
			sort_by_grades(list_head,ENGLISH);
			break;

		default:
			printf("\nINVALID CHOICE!!\n");
			/*return back to get valid choice*/
			goto begin;
			break;
	}

	/*view the students after sorting them*/
	view_grades(list_head, choice);
}



/*---------------------------------------------------------------------------------------------------*/
/******************************************* Helper Functions ****************************************/
/*---------------------------------------------------------------------------------------------------*/

static uint32_t nodes_size (node_t** list_head)

{
	uint32_t size = 0;
	node_t* temp = *list_head;
	if (*list_head != NULL)
	{
		while( (temp->node_link ) != NULL )
		{
			size++;
			temp = temp->node_link;
		}size++;	
	}

	else
	{
		/*Nothing*/
	}	
	return size;

}


static void swap_nodes (node_t** list_head, uint32_t first_node_index, uint32_t sec_node_index)
{
	node_t* first_node = *list_head;
	node_t* sec_node = *list_head;
	node_t* before_first_node = NULL;
	node_t* before_sec_node   = NULL;
	node_t* temp_node         = NULL;
	if( (*list_head) != (NULL) )  
	{
		for (int i = 0; (i < first_node_index - 1) && (first_node != NULL); ++i)
		{
				before_first_node = first_node;
				first_node = first_node->node_link;
		}
		
		for (int i = 0; (i < sec_node_index - 1) && (sec_node != NULL); ++i)
		{
				before_sec_node = sec_node;
				sec_node = sec_node->node_link;
		}
		if( (first_node == NULL) || (sec_node == NULL) )
		{
			printf("failed to swap\n");
		}
		else
		{
			/*link the node before first element by second element*/
			/*check if it first element*/
			if(before_first_node != NULL)
			{
				before_first_node->node_link = sec_node;
			}
			else
			{
				/*make the fist element the swapped element*/
				(*list_head) = sec_node;
			}
			
			/*link the node before second element by first element*/
			/*check if it last element*/
			if(before_sec_node != NULL)
			{
				before_sec_node->node_link = first_node;
			}
			else
			{
				/*make the fist element the swapped element*/
				(*list_head) = first_node;
			
			}
			
			/*swap the two elements*/
			temp_node  = first_node->node_link;
			first_node->node_link = sec_node->node_link;
			sec_node->node_link   = temp_node;

		}
	
	}
		
	else
	{
		printf("failed to insert the node\n");
	}

}



static void sort_nodes_alphabetically(node_t** list_head)
{
	if((*list_head) != NULL)
	{
		uint32_t size = nodes_size(list_head);
		node_t* node = *list_head;
		node_t* next_node = node->node_link;

		for (int i = 0;  (i) < (size ); i++)
		{
			node = (*list_head);
			next_node = node->node_link;


			for (int j = 0;  (j) < (size - 1); j++)
			{

				for (int k = 0; k < 30; ++k)
				{
					if ( (node->student.name[k]) == (next_node->student.name[k]) )
					{

					}
					else if ((node->student.name[k]) >= (next_node->student.name[k]))
					{
						swap_nodes(list_head, j+1, j+2);
						break;
					}
					else
					{
						break;
					}
				}
				node = node->node_link;
				next_node = next_node->node_link;
			}


		}	
	}

	else
	{
		/*can't sort null*/	
	}
}


static void sort_by_grades (node_t** list_head, uint8_t subject)
{
		if((*list_head) != NULL)
	{
		uint32_t size = nodes_size(list_head);
		node_t* node = *list_head;
		node_t* next_node = node->node_link;

		for (int i = 0;  (i) < (size ); i++)
		{
			node = (*list_head);
			next_node = node->node_link;


			for (int j = 0;  (j) < (size - 1); j++)
			{

				switch(subject)
				{
				case CS:
					if ((node->student.grade.cs) < (next_node->student.grade.cs))
					{
						swap_nodes(list_head, j+1, j+2);
					}		
					else
					{
						/*nothing*/
					}
					break;

				case MATH:
					if ((node->student.grade.math) < (next_node->student.grade.math))
					{
						swap_nodes(list_head, j+1, j+2);
					}		
					else
					{
						/*nothing*/
					}
					break;
				case ENGLISH:
					if ((node->student.grade.english) < (next_node->student.grade.english))
					{
						swap_nodes(list_head, j+1, j+2);
					}		
					else
					{
						/*nothing*/
					}
					break;

				default:
					printf("\nWRONG SUBJECT!!\n");
					break;
				}
				node = node->node_link;
				next_node = next_node->node_link;
			}


		}	
	}

	else
	{
		printf("Error can't sort null\n");
	}	
}





static void validate_name (uint8_t*str)
{
	uint8_t i = 0;	
	/* replace the \n which stored by fgets with \0 */
	adjust_null(str);

	while(str[i] != '\0')
	{
		if (str[i] == ' ')
		{	
			/*if space is found we capitilize the first letter of the next name*/
			str[i+1] = upper_letter(str[i+1]);

			/*skip the uppered letter*/
			i++;						
		}

		else if ( ((str[i] >= 'A')&&(str[i] <= 'Z')) || ((str[i] >= 'a')&&(str[i] <= 'z')) || (str[i] == '-') || (str[i] == '_') )
		{
			if (i == 0)
			{
				/*uppering the first letter of name which hasn't space before*/
				str[i] = upper_letter(str[i]);
			}
			else
			{
				/*lowering all the letters expect the beginning of names (already skipped in the above if condition)*/
				str[i] = lower_letter(str[i]);
			}
		}

		else
		{
			/*printing error to user*/
			printf("ERROR INVALID NAME!!\n");
			/*retake the name from user*/
			printf("Re Enter The Name: \n");
			fgets(str, 30, stdin);
			/*check if the new name is valid*/
			validate_name(str);

			/*break from loop to don't change the string after back from recursion*/
			break;
		}
		 i++;
	}
}

static void validate_date  (date_t* date)
{
	if ( ((date->day) > (31)) ||((date->month) > (12)) || ((date->year) > (2023)) || ((date->year) < (1)) ||((date->month) < (1)) ||((date->day) < (1)))
	{
		printf("\nINVALID BIRHDAY!!!\n");
		printf("\nRe Enter Birthday: ");
		scanf("%d/%d/%d",&(date->day), &(date->month), &(date->year));
		validate_date(date);
		
	}
	else
	{
		/*nothing*/
	}
}




static void view_grades	(node_t** list_head, uint8_t subject)
{
	if(*list_head != NULL)
	{
		node_t* last_node = *list_head;
		uint8_t ZERO = 0, index = 1;
		
		printf("\n\n");
		while((last_node->node_link )!= NULL || ++ZERO)
		{
			if (ZERO == 0)
			{
				/*printing the number of student*/
				printf("%d) %s\n",index,last_node->student.name);
				switch(subject)
				{
					case CS:
						printf("CS Degree = %.2f\n",last_node->student.grade.cs);
						break;

					case MATH:
						printf("MATH Degree = %.2f\n",last_node->student.grade.math);
						break;

					case ENGLISH:
						printf("English Degree = %.2f\n",last_node->student.grade.english);
						break;

					default:
						printf("\nINVALID CHOICE!!\n");
						break;
				}		
				index++;
				last_node = last_node->node_link;
			
			}
			else
			{
				/*printing the number of student*/
				printf("%d) %s\n",index,last_node->student.name);
				switch(subject)
				{
					case CS:
						printf("CS Degree = %.2f\n\n",last_node->student.grade.cs);
						break;

					case MATH:
						printf("MATH Degree = %.2f\n\n",last_node->student.grade.math);
						break;

					case ENGLISH:
						printf("English Degree = %.2f\n\n",last_node->student.grade.english);
						break;

					default:
						printf("\nINVALID CHOICE!!\n");
						break;
				}		
				index++;
				last_node = last_node->node_link;
				break;
			
			}
		}

	}
	else
	{
		printf("Error: can't display null\n");
	}

}


static void adjust_null(uint8_t* str)
{
	uint8_t i = 0;
	while(str[i] != '\n')
	{
		i++;
	}
	str[i] = '\0';
	
} 


static uint8_t upper_letter (uint8_t letter)
{
	if ( (letter >= 'a')&&(letter <= 'z') )
	{
		letter += 'A' - 'a';
	}
	else
	{
		/*nothing*/
	}
	return letter;
}


static uint8_t lower_letter (uint8_t letter)
{
	if ( (letter >= 'A')&&(letter <= 'Z') )
	{
		letter += 'a' - 'A';
	}
	else
	{
		/*nothing*/
	}
	return letter;
}


static uint8_t name_length (uint8_t* str)
{
	uint8_t length = 0; 
	while(str[length]!= '\0')
	{
		length++;
	}

	return length;
}



static uint8_t num_width (uint64_t num)
{
	uint8_t width = 0;
	while(num != 0)
	{
		num /= 10;
		width++;
	}
	return width;
}

static void print_line (void)
{
	uint8_t name_width = 30, ID_width = 10, phone_number_width = 16, address_width = 45, birthday_width = 15 ;
	printf("\n|");
	for (int i = 0; i < name_width ; ++i)
	{
		printf("_");
	}printf("|");


	for (int i = 0; i <= ID_width ; ++i)
	{
		printf("_");
	}printf("|");


	for (int i = 0; i <= phone_number_width +1; ++i)
	{
		printf("_");
	}printf("|");


	for (int i = 0; i <= address_width; ++i)
	{
		printf("_");
	}printf("|");


	for (int i = 0; i <= birthday_width; ++i)
	{
		printf("_");
	}printf("|");
			
}



static void print_welcome(void)
{
	/*
	 	*   *   *****   *      *****   *****   *   *   ***** 	
	 	*   *   *       *      *       *   *   ** **   *     	
	 	* * *   *****   *      *       *   *   * * *   ***** 	
	 	** **   *       *      *       *   *   *   *   *     	
	 	*   *   *****   *****  *****   *****   *   *   *****

*/

	uint8_t row = 1, col = 1, space = 1;

	/*printing 5 rows*/
	for (row = 1; row < 6; ++row)
	{
		/*printing new line*/
		printf("\n");

		/*printing spaces*/
		for (space = 1; space < 9; ++space)
		{
			printf("	");
		}


		/* printing 'W' */

		for (col = 1; col < 8; ++col)
		{
			if( (col == 1) || (col == 7) || ( (row == 4)&&( (col == 3)||(col == 5)) ) || ((col == 4) && (row ==3)) )
			{
				printf("@");
			}
			else
			{
				printf(" ");
			}
		}
		

		/*printing space*/
		for(space = 1; space <3 ; space++)
		{
			printf(" ");
		}


		/* printing 'E' */
		for (col = 1; col < 6; ++col)
		{
			if( (col == 1) || (row == 1) || (row == 3) || (row == 5) )
			{
				printf("@");
			}
			else
			{
				printf(" ");
			}
		}
		

		/*printing space*/
		for(space = 1; space <3 ; space++)
		{
			printf(" ");
		}


		/* printing 'L' */
		for (col = 1; col < 6; ++col)
		{
			if( (col == 1) || (row == 5) )
			{
				printf("@");
			}
			else
			{
				printf(" ");
			}
		}
		

		/*printing space*/
		for(space = 1; space <3 ; space++)
		{
			printf(" ");
		}


		/* printing 'C' */
		for (col = 1; col < 6; ++col)
		{
			if( (col == 1) || (row == 1) || (row == 5)  )
			{
				printf("@");
			}
			else
			{
				printf(" ");
			}
		}
		

		/*printing space*/
		for(space = 1; space <3 ; space++)
		{
			printf(" ");
		}


		/* printing 'O' */
		for (col = 1; col < 6; ++col)
		{
			if( (col == 1) || (col == 5) || (row == 1) || (row == 5)  )
			{
				printf("@");
			}
			else
			{
				printf(" ");
			}
		}
		

		/*printing space*/
		for(space = 1; space <3 ; space++)
		{
			printf(" ");
		}


		/* printing 'M' */
		for (col = 1; col < 6; ++col)
		{
			if( (col == 1) || (col == 5) || ((row == 2) && (col!=3)) || ((col==3) && (row ==3)) )
			{
				printf("@");
			}
			else
			{
				printf(" ");
			}
		}
		

		/*printing space*/
		for(space = 1; space <3 ; space++)
		{
			printf(" ");
		}


		/* printing 'E' */
		for (col = 1; col < 6; ++col)
		{
			if( (col == 1) || (row == 1) || (row == 3) || (row == 5) )
			{
				printf("@");
			}
			else
			{
				printf(" ");
			}
		}
	}


	/**/
	printf("\n\n\n\n\n\n");
}
