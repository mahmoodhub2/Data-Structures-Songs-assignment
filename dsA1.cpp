/*
  FILE : dsA1.cpp
* PROJECT :  Major-Assignment 1#
* PROGRAMMER : Mahmood Al-Zubaidi
* FIRST VERSION : 20/june/2021
* DESCRIPTION : The purpose of this function is to orgnize the inputted artist, title, and rating in structures and display them based on thier rating then traverse them based on rating
				then traversing them alphebaticlly based on the artist name. 
*/




#include "dsA1LL.cpp"
#include "dsA1.h"




#pragma warning(disable: 4996)


int getSongInfo(songInfo** head, char artist[], char title[], char rating[], songInfo** tail);
void getArtistInfo(songInfo** head2, char artist[], char title[], char rating[], songInfo** tail2);
void printSongInfo(songInfo* head);
void backward(songInfo* tail);
songInfo* findSong(songInfo** head, char artist[], char title[], char rating[], songInfo *curr);
int findRating(songInfo** head, char rating[]);
int deleteNode(songInfo** head, songInfo** tail, songInfo* curr);
void freeData(songInfo* head);
void clearCRLF(char* str);



int main(void) {
	char artist[30];
	char title[30];
	char rating[30];
	songInfo* head = NULL;
	songInfo* tail = NULL;
	songInfo* tail2 = NULL;
	songInfo* head2 = NULL;
	songInfo* curr = NULL;


	while (true) {

		printf("Please enter the Artist of the song: ");
		fgets(artist, sizeof(artist), stdin);
		clearCRLF(artist);
		if (strchr(artist, '.') != NULL) {
			break;
		}

		printf("Please enter the Title of the song: ");
		fgets(title, sizeof(title), stdin);
		clearCRLF(title);

		printf("Please enter the Rating of the song: ");
		fgets(rating, sizeof(rating), stdin);
		clearCRLF(rating);
		int element = 0;
		sscanf(rating, "%d", &element);
		if(element > 5 || element < 1){
			printf("The rate is out of range!\n");
		}

		getSongInfo(&head, artist, title, rating, &tail);
		getArtistInfo(&head2, artist, title, rating, &tail2);

	}

	printSongInfo(head);
	backward(tail);
	backward(tail2);
	

	while (true) {	
		printf("\nPlease enter the Artist of the searching song: ");

		fgets(artist, sizeof(artist), stdin);
		clearCRLF(artist);
		printf("\nPlease enter the title of the searching song: ");
		fgets(title, sizeof(title), stdin);
		clearCRLF(title);
		printf("\nPlease enter the rating of the searching song: ");
		fgets(rating, sizeof(rating), stdin);
		clearCRLF(rating);
		
		if (findSong(&head, artist, title, rating, curr) != NULL) {
			printf("\n Please enter the new rate: ");
			fgets(rating, sizeof(rating), stdin);
			clearCRLF(rating);
			if (findRating(&head, rating) == 0) {
				getArtistInfo(&head2, artist, title, rating, &tail2);

				deleteNode(&head, &tail, curr);
				getSongInfo(&head, artist, title, rating, &tail);

				printSongInfo(head);
				backward(tail);
				backward(tail2);
				break;
			}
			else {
				printSongInfo(head);
				backward(tail);
				backward(tail2);
			}
		}
	}
	

	
	freeData(head);
	freeData(head2);
	
	return 0;
}



/** Function: getSongInfo
* Description: this function filles in the structure witht the new alloacted data.
* Parameters: five: which are: a pointer to a pointer for the structure to get it's address, second and third one are the arrays that contain
* the user's input. fourth one is a pointer to apointer of the tail that points to the last node.
* Returns: 0 if there no memorry left. and 1 after initlizing the head and tail with the newblock that contains the allocated data.
*/
int getSongInfo(songInfo** head, char artist[], char title[], char rating[], songInfo** tail) {
	songInfo* newBlock = NULL;
	songInfo* beforeElement = NULL;
	songInfo* afterElement = NULL;


	newBlock = (songInfo*)malloc(sizeof(songInfo));
	if (newBlock == NULL) {
		printf("Error! No more memorry\n");
		return 0;
	}

	newBlock->artist = (char*)malloc((strlen(artist) + 1) * sizeof(char));
	newBlock->title = (char*)malloc((strlen(title) + 1) * sizeof(char));
	newBlock->rating = (char*)malloc((strlen(rating) + 1) * sizeof(char));


	strcpy(newBlock->artist, artist);
	strcpy(newBlock->title, title);
	strcpy(newBlock->rating, rating);
	newBlock->prev = newBlock->next = NULL;


	if (*head == NULL)	{
		*head = *tail = newBlock;
		return 1;
	}


	else if (strcmp((*head)->rating, rating) >= 0) {
		newBlock->next = *head;
		(*head)->prev = newBlock;
		*head = newBlock;
	}
	else {

		beforeElement = *head;		
		afterElement = (*head)->next;	

		while (afterElement != NULL)
		{
			if (strcmp(afterElement->rating, rating) >= 0)
			{
				break;
			}
			beforeElement = afterElement;
			afterElement = afterElement->next;
		}	

		newBlock->prev = beforeElement;
		newBlock->next = afterElement;
		beforeElement->next = newBlock;
		if (afterElement == NULL)
		{
			*tail = newBlock;
		}
		else
		{
			afterElement->prev = newBlock;
		}

	}


}



/** Function: getArtistInfo
* Description: this function filles in the structure witht the new alloacted data.
* Parameters: five: which are: a pointer to a pointer for the structure to get it's address, second and third one are the arrays that contain
* the user's input. fourth one is a pointer to apointer of the tail that points to the last node.
* Returns: Nothing.
*/
void getArtistInfo(songInfo** head2, char artist[], char title[], char rating[], songInfo** tail2) {
	songInfo* newBlock = NULL;
	songInfo* beforeElement = NULL;
	songInfo* afterElement = NULL;


	newBlock = (songInfo*)malloc(sizeof(songInfo));
	if (newBlock == NULL) {
		printf("Error! No more memorry\n");
	}
	
	newBlock->artist = (char*)malloc((strlen(artist) + 1) * sizeof(char));
	newBlock->title = (char*)malloc((strlen(title) + 1) * sizeof(char));
	newBlock->rating = (char*)malloc((strlen(rating) + 1) * sizeof(char));


	strcpy(newBlock->artist, artist);
	strcpy(newBlock->title, title);
	strcpy(newBlock->rating, rating);
	newBlock->prev = newBlock->next = NULL;


	if (*head2 == NULL) {
		*head2 = newBlock;
	}
	else if (strcmp((*head2)->artist, artist) >= 0) {
		newBlock->next = *head2;
		(*head2)->prev = newBlock;
		*head2 = newBlock;
	}
	else {

		beforeElement = *head2;
		afterElement = (*head2)->next;

		while (afterElement != NULL) {
			if (strcmp(afterElement->artist, artist) >= 0) {
				break;
			}

			beforeElement = afterElement;
			afterElement = afterElement->next;
		}
		newBlock->prev = beforeElement;
		newBlock->next = afterElement;
		beforeElement->next = newBlock;


		if (afterElement == NULL) {
			*tail2 = newBlock;
		}
		else {
			afterElement->prev = newBlock;
		}


	}
}


/** Function: printSongInfo
* Description: this function prints out the list of the user's input that exists inside the struct
* Parameters: a pointer to the structure that now has the allocated user's input.
* Returns: nothing.
*/
void printSongInfo(songInfo* head) {
	songInfo* ptr = head;
	char a[10] = "Artist";
	char t[10] = "Title";
	char r[10] = "Rating";
	printf("\n%-35s 	%-35s	%-35s\n\n", a, t, r);
	while (ptr != NULL) {
		printf("%-35s 	%-35s	%-35s\n", ptr->artist, ptr->title, ptr->rating);
		ptr = ptr->next;

	}
}



/** Function: printSongInfo
* Description: this function prints out the traversed list of the user's input that exists inside the struct
* Parameters: a pointer to the tail points to the last node.
* Returns: nothing.
*/
void backward(songInfo* tail) {
	char a[10] = "Artist";
	char t[10] = "Title";
	char r[10] = "Rating";
	songInfo* item = NULL;
	item = tail;
	printf("\n%-35s 	%-35s	%-35s\n\n", a, t, r);
	while (item != NULL) {
		printf("%-35s 	%-35s	%-35s\n", item->artist, item->title, item->rating);
		item = item->prev;
	}

}



/** Function: findSong
* Description: it compares the recent user's input with the information that is inside the struct.
* Parameters: a pointer to a pointer for the node, the three arrays that contain the user's input and a pointer for the current node.
* Returns: A pointer to the node where it found the same info, or it returns Null if not found.
*/
songInfo* findSong(songInfo** head, char artist[], char title[], char rating[], songInfo* curr) {
	songInfo * next = NULL;
	curr = *head;

	while (curr != NULL) {
		if (strcmp(artist, curr->artist) == 0 && strcmp(title, curr->title) == 0 && strcmp(rating, curr->rating) == 0) {
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}



/** Function: findRating
* Description: it compares the recently inputted rating witht he rating inside the struct.
* Parameters: a pointer to a pointer for the head.
* Returns: 1 if succfully found the same rating. if not then 0.
*/
int findRating(songInfo** head, char rating[]) {
	songInfo* curr = NULL, * next = NULL;
	curr = *head;

	while (curr != NULL) {
		if ( strcmp(rating, curr->rating) == 0) {
			return 1;
		}
		curr = curr->next;
	}
	return 0;
}



/** Function: deleteNode
* Description: it deletes the node that has same information.
* Parameters: a pointer to a pointer for the head which has the node, tail which will be used to point to the last element of the node and the curr whic will be pointing to the current node.
* Returns: if it is the only node it returns 1. 
*/
int deleteNode(songInfo** head, songInfo** tail, songInfo* curr) {
	songInfo* next = NULL;

	curr = *head;

	while (curr != NULL) {

		if ((curr == *head) && (curr == *tail)) {
			free(curr);
			return 1;
		}

		if (curr == *head) {
			songInfo* secondElement = curr->next;
			*head = curr->next;
			secondElement->prev = NULL;
		}
		else {
			if (curr == *tail) {
				songInfo* secondLastElement = curr->prev;
				*tail = curr->prev;
				secondLastElement->prev = NULL;
			}
			else {
				songInfo* proceedingElement = curr->next;
				songInfo* followingElement = curr->prev;

				followingElement->prev = proceedingElement;
				proceedingElement->next = followingElement;
			}
			
		}
		free(curr);
		return 1;
		
		curr = curr->next;
	}
	return 0;
}



/** Function: freeData
* Description: it frees the node out of memorry.
* Parameters: pointer to the node.
* Returns: nothing.
*/
void freeData(songInfo* head) {
	songInfo* curr = NULL;
	songInfo* next = NULL;
	curr = head;

	while (curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}
}


/** Function: clearCRLF
* Description: this function replaces the '\n' with the '\0' for the end of the line of the string.
* Parameters: a pointer to the variable that contains the user's input
* Returns: nothing.
*/
void clearCRLF(char* str) {
	char* whereIsCRLF = strchr(str, '\n');
	if (whereIsCRLF != NULL)
	{
		*whereIsCRLF = '\0';
	}
}