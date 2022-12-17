/*
 *  CSC A48 - Winter 2022 - Assignment 1 starter
 * 
 *  (c) 2020-22 Francisco Estrada
 *  - No part of this code may be reproduced without written authorization
 * 
 * This is the file where you will be doing most of your work. The
 * functionality you must provide for part 1 of the assignment is described
 * in the handout. Given in detail in the comments at the head of each
 * function below. 
 * 
 * Plan your work carefully, review the notes for Unit 3, and work carefully
 * to complete the functions in this file. You can bring 
 * questions to your TAs or instructors during office hours. Please
 * remember:
 * 
 * - You should not share any part of your solution in any form
 * - You should not post any assignment code on Piazza
 * - You should definitely *help* other understand any ideas and
 *   concepts regarding linked lists that you have already mastered,
 *   but being careful not to give away parts of the solution, or
 *   descriptions of how to implement functions below.
 * - If you are not sure whether you can or can not discuss some
 *   particular aspect of the work to be done, remember it's always 
 *   safe to talk with your TAs.
 * - Obtaining external 'help' including being given code by an
 *   external party, or being tutored on how to solve
 *   the assignment constitutes an academic offense.
 * 
 * All tasks to be completed by you are clearly labeled with a
 * ***** TO DO ****** comment block, which also gives you details
 * about what you have to implement. Look carefully and make sure
 * you don't miss a thing!
 * 
 * NOTE: This file contains no main() function! you can not compile
 * it on its own to create an executable. It's meant to be used
 * together with Part1_driver.c - be sure to read that file carefully
 * to understand how to use the tests there - Any additional tests
 * you want to run on the code below should be added to Part1_driver.c
 * 
 * Before you even get starter implementing, please complete the
 * student identification section below, and check that you are aware
 * of the policy on academic honesty and plagiarism.
 */

/* Student identification:
 * 
 * Student Name (Last name, First name): Sajewski-Lee, Casper
 * Student Number: 1008493701
 * UTORid: leecaspe
 * Your instructor's name is: Purva
 */

/* Academic Integrity Statement:
 * 
 * I hereby certify that the work contained in this file is my own, and
 * that I have not received any parts of my solution from other sources
 * including my fellow students, external tutoring services, the internet,
 * or algorithm implementations found online.
 * 
 * Sign here with your name: Casper Sajewski-Lee
 *
 *  
 */

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STR_LEN 1024

/* Compound data type declarations */
/***************************************************************************/
/******                         TO DO                               ********/
/****** In the space below, complete the definitions of the compound *******/
/****** data types that will be needed to implement the movie review *******/
/****** linked list. This includes the MovieReview type, and the     *******/
/****** ReviewNode. Details about the contents of these can be       *******/
/****** found in the assignment handout. Read them carefully!        *******/
/******                                                              *******/
/****** AFTER completing the basic linked list, complete the CDT     *******/
/****** required to implement a list for the movie's cast.           *******/
/***************************************************************************/

typedef struct castList_struct
{
	char name[MAX_STR_LEN];
	float salary;
	struct castList_struct *next;  
} CastList;

typedef struct movieReview_struct
{
	char movie_title[MAX_STR_LEN];
	char movie_studio[MAX_STR_LEN];
	int year;
	float BO_total;
	int score;
	CastList *cast;
} MovieReview;

typedef struct reviewNode_struct
{
	MovieReview review;
	struct reviewNode_struct *next;   
} ReviewNode;

typedef struct actor_node
{
	char name[MAX_STR_LEN];
	float movie_earnings;
	int movie_appearances;
	struct actor_node *next;
} Actor_Earning_List;

ReviewNode *newMovieReviewNode()
{
    ReviewNode *new_node = NULL;
	new_node = (ReviewNode *)calloc(1, sizeof(ReviewNode));
	strcpy(new_node->review.movie_title, "");
	strcpy(new_node->review.movie_studio, "");
	new_node->review.year = -1;
	new_node->review.BO_total = -1;
	new_node->review.score = -1;
	new_node->next = NULL;
	new_node->review.cast = NULL;
	return (new_node);
}

ReviewNode *findMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, ReviewNode *head)
{
	ReviewNode *review_pointer = head;
	while (review_pointer != NULL)
    {
		if (strcmp(review_pointer->review.movie_title, title) == 0 && strcmp(review_pointer->review.movie_studio, studio) == 0 && review_pointer->review.year == year)
			return review_pointer;
		review_pointer = review_pointer->next;
	}
    return NULL;  
}

ReviewNode *insertMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, float BO_total, int score, ReviewNode *head)
{
	if (findMovieReview(title, studio, year, head) == NULL)
	{
		ReviewNode *new_head =  newMovieReviewNode();
		strcpy(new_head->review.movie_title, title);
		strcpy(new_head->review.movie_studio, studio);
		new_head->review.year = year;
		new_head->review.BO_total = BO_total;
		new_head->review.score = score;
		new_head->next = head;
		return (new_head);
	}
	return (head);
}

int countReviews(ReviewNode *head)
{
	ReviewNode *review_pointer = head;
	int review_counter = 0;
	while (review_pointer != NULL)
	{
		review_pointer = review_pointer->next;
		review_counter++;
	}
	return (review_counter);
}
void updateMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, float BO_total, int score, ReviewNode *head)
{
	ReviewNode *review_pointer = head;
	bool movie_found = false;
	while (review_pointer != NULL)
	{
		if (strcmp(review_pointer->review.movie_title, title) == 0 && strcmp(review_pointer->review.movie_studio, studio) == 0 && review_pointer->review.year == year)
		{
			review_pointer->review.BO_total = BO_total;
			review_pointer->review.score = score;
			movie_found = true;
		}
		review_pointer = review_pointer->next;
	}
	if (!movie_found)
	{
		printf("Sorry, no such movie exists in the database");
	}
}

ReviewNode *deleteMovieReview(char title[MAX_STR_LEN], char studio[MAX_STR_LEN],int year, ReviewNode *head)
{
	ReviewNode *review_pointer = head;
	ReviewNode *next_pointer = review_pointer->next;
	if (strcmp(title, head->review.movie_title) == 0 && strcmp(head->review.movie_studio, studio) == 0 && year == head->review.year)
		return (next_pointer);
	while (review_pointer != NULL)
	{
		if (strcmp(title, next_pointer->review.movie_title) == 0 && strcmp(next_pointer->review.movie_studio, studio) == 0 && year == next_pointer->review.year)
		{
			review_pointer->next = next_pointer->next;
			break;
		}
		review_pointer = next_pointer;
		next_pointer = next_pointer->next;
	}
	return (head);
}

float printMovieReviews(ReviewNode *head)
{
	ReviewNode *review_pointer = head;
	int sum_BO = 0;
	while (review_pointer != NULL)
	{
		printf("%s\n", review_pointer->review.movie_title);
		printf("%s\n", review_pointer->review.movie_studio);
		printf("%d\n", review_pointer->review.year);
		printf("%f\n", review_pointer->review.BO_total);
		printf("%d\n", review_pointer->review.score);
		printf("*******************\n");
		sum_BO += review_pointer->review.BO_total;
		review_pointer = review_pointer->next;
	}
	return (sum_BO);
    /*
     * This function prints out all the reviews in the database, one after another.
     * Each field in the review is printed in a separate line, with *no additional text*
     * (that means, the only thing printed is the value of the corresponding field).
     * 
     * Reviews are separated from each other by a line of
     * "*******************"

     * The function also computes and returns the Box-office total, for all the
     * movies that match the query.
     * 
     * See the A1 handout for a sample of the output that should be produced
     * by this function
     */
}

float queryReviewsByStudio(char studio[MAX_STR_LEN], ReviewNode *head)
{
	ReviewNode *review_pointer = head;
	int sum_BO = 0;
	while (review_pointer != NULL)
	{
		
		if (strcmp(studio, review_pointer->review.movie_studio) == 0)
		{
			printf("%s\n", review_pointer->review.movie_title);
			printf("%s\n", review_pointer->review.movie_studio);
			printf("%d\n", review_pointer->review.year);
			printf("%f\n", review_pointer->review.BO_total);
			printf("%d\n", review_pointer->review.score);
			printf("*******************\n");
			sum_BO += review_pointer->review.BO_total;
		}
		review_pointer = review_pointer->next;
	}
	return (sum_BO);
}
			
    /*
     * This function looks for reviews whose studio matches the input query.
     * It prints out the contents of all reviews matching the query in exactly
     * the same format used by the printMovieReviews() function above.
     * 
     * Additionally, it computes and returns the Box-office total, for all the
     * movies that match the query.
     */


float queryReviewsByScore(int min_score, ReviewNode *head)
{
	ReviewNode *review_pointer = head;
	int sum_BO = 0;
	while (review_pointer != NULL)
	{
		if (min_score <= review_pointer->review.score)
		{
			printf("%s\n", review_pointer->review.movie_title);
			printf("%s\n", review_pointer->review.movie_studio);
			printf("%d\n", review_pointer->review.year);
			printf("%f\n", review_pointer->review.BO_total);
			printf("%d\n", review_pointer->review.score);
			printf("*******************\n");
			sum_BO += review_pointer->review.BO_total;
		}
		review_pointer = review_pointer->next;
	}
	return (sum_BO);
    /*
     * This function looks for reviews whose score is greater than, or equal to
     * the input 'min_score'.
     * It prints out the contents of all reviews matching the query in exactly
     * the same format used by the printMovieReviews() function above.
     * 
     * Additionally, it computes and returns the Box-office total, for all the
     * movies that match the query.
     */
}

ReviewNode *deleteReviewList(ReviewNode *head)
{
	ReviewNode *review_pointer = head;
	ReviewNode *node_to_delete = review_pointer->next;
	while (node_to_delete != NULL)
	{
		review_pointer->next = NULL;
		review_pointer = node_to_delete;
		node_to_delete = node_to_delete->next;
	}
	review_pointer = NULL;
	return (review_pointer);
  /*
   * This function deletes the movie review database, releasing all the
   * memory allocated to the nodes in the linked list.
   * 
   * Returns a NULL pointer so that the head of the list can be set to NULL
   * after deletion.
   */

}

/* CRUNCHY SECTION! Do not work on the functions below until
 * your basic linked list is working properly and is fully tested!
 */ 

ReviewNode *sortReviewsByTitle(ReviewNode *head)
{
	int movies_to_sort = countReviews(head);
	ReviewNode *start_of_review_list = NULL;
	ReviewNode *review_pointer = head;
	while (review_pointer != NULL)
	{
		start_of_review_list = insertMovieReview(review_pointer->review.movie_title, review_pointer->review.movie_studio, review_pointer->review.year, review_pointer->review.BO_total, review_pointer->review.score, start_of_review_list);
		review_pointer = review_pointer->next;
	}
	for (int index = 0; index < movies_to_sort; index++)
	{

		ReviewNode *lowest_title = start_of_review_list;
		ReviewNode *pointer_to_check = start_of_review_list;
		review_pointer = head;
		while (pointer_to_check != NULL)
		{
			if (strcmp(lowest_title->review.movie_title, pointer_to_check->review.movie_title) > 0)
			{
				lowest_title = pointer_to_check;
			}
			pointer_to_check = pointer_to_check->next;
		}
		review_pointer = head;
		int movie_index = index;
		int y = 0;
		while (y < movie_index)
		{
			review_pointer = review_pointer->next;
			y++;
		}
		strcpy(review_pointer->review.movie_title, lowest_title->review.movie_title);
		strcpy(review_pointer->review.movie_studio, lowest_title->review.movie_studio);
		review_pointer->review.year = lowest_title->review.year;
		review_pointer->review.BO_total = lowest_title->review.BO_total;
		review_pointer->review.score = lowest_title->review.score;
		review_pointer->review.cast = lowest_title->review.cast;
		start_of_review_list = deleteMovieReview(lowest_title->review.movie_title, lowest_title->review.movie_studio, lowest_title->review.year, start_of_review_list);
	}
	return (head);
}

void insertCastMember(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int year, ReviewNode *head, char name[MAX_STR_LEN], float salary)
{
	ReviewNode *review_pointer = findMovieReview(title, studio, year, head);
	if (review_pointer != NULL && review_pointer->review.cast == NULL)
	{
		review_pointer->review.cast = calloc(1, sizeof(CastList));
		strncpy(review_pointer->review.cast->name, name, strlen(name));
		review_pointer->review.cast->salary = salary;
		review_pointer->review.cast->next = NULL;
	}
	else if (review_pointer != NULL)
	{
		CastList *slot_to_insert_cast_member = review_pointer->review.cast;
		while (slot_to_insert_cast_member->next != NULL)
		{
			slot_to_insert_cast_member = slot_to_insert_cast_member->next;
		}
		slot_to_insert_cast_member->next = calloc(1, sizeof(CastList));
		strncpy(slot_to_insert_cast_member->next->name, name, strlen(name));
		slot_to_insert_cast_member->next->salary = salary;
		slot_to_insert_cast_member->next->next = NULL;
	}
}

void whosTheStar(ReviewNode *head)
{
	ReviewNode *review_pointer = head;
	Actor_Earning_List *start_of_actor_list = calloc(1, sizeof(Actor_Earning_List));
	CastList *cast_pointer = NULL;
	Actor_Earning_List *actor_list_pointer = start_of_actor_list;
	while (review_pointer != NULL)
	{
		cast_pointer = review_pointer->review.cast;
		float total_actor_cost = 0;
		while (cast_pointer != NULL)
		{
			total_actor_cost += cast_pointer->salary;
			cast_pointer = cast_pointer->next;
		}
		float net_movie_earnings = (review_pointer->review.BO_total) - total_actor_cost;
		cast_pointer = review_pointer->review.cast;
		while (cast_pointer != NULL)
		{
			actor_list_pointer = start_of_actor_list;
			bool actor_in_list = false;
			while (actor_list_pointer != NULL)
			{
				if (strcmp(cast_pointer->name, actor_list_pointer->name) == 0)
				{
					actor_list_pointer->movie_earnings += net_movie_earnings;
					actor_list_pointer->movie_appearances += 1;
					actor_in_list = true;
					break;
				}
				actor_list_pointer = actor_list_pointer->next;
			}
			actor_list_pointer = start_of_actor_list;
			if (!actor_in_list)
			{
				while (actor_list_pointer->next != NULL)
					actor_list_pointer = actor_list_pointer->next;
				strcpy(actor_list_pointer->name, cast_pointer->name);
				actor_list_pointer->movie_earnings = net_movie_earnings;
				actor_list_pointer->movie_appearances = 1;
				actor_list_pointer->next = calloc(1, sizeof(Actor_Earning_List));
				actor_list_pointer->next->next = NULL;
			}
			cast_pointer = cast_pointer->next;
		}
		review_pointer = review_pointer->next;
	}
	actor_list_pointer = start_of_actor_list;
	Actor_Earning_List *highest_earner = start_of_actor_list;
	while (actor_list_pointer != NULL)
	{
		if ((actor_list_pointer->movie_earnings) / (actor_list_pointer->movie_appearances) > (highest_earner->movie_earnings) / (highest_earner->movie_appearances) )
			highest_earner = actor_list_pointer;
		actor_list_pointer = actor_list_pointer->next;
	}
	printf("%s\n", highest_earner->name);
	printf("%.2f\n", (highest_earner->movie_earnings) / (highest_earner->movie_appearances));
}
	
  /*
   *  This function goes through the movie database and determines who is
   * the cast members whose movies have the greatest average earnings.
   *
   * Earnings are defined as the box office total minus the salaries of all
   * cast members involved with the movie.
   *
   *  You're free to implement this function however you like, use any of
   * the code you wrote for other parts of the assignment, and write any
   * helper functions that you need. But:
   *
   *  You can not import extra libraries (no additional #include), and
   * all the implementation here should be your own. 
   *
   *  The function simply prints out:
   *
   *  Name of cast member
   *  Average movie earnings (as a floating point number)
   *
   *  For the cast member whose movies make the greatest average earnings
   */

void printNames(ReviewNode *movie)
{
// Prints out names of cast members for this movie
	CastList *p;

	if (movie==NULL||movie->review.cast==NULL) return;

	p=movie->review.cast;
	printf("The cast for this movie are:\n");
	while (p!=NULL)
	{
		printf("Cast Member: %s, Salary: %f\n",p->name,p->salary);
		p=p->next;
	}
}
