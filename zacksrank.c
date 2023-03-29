#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char* replaceWord(const char* s, const char* oldW,
                const char* newW)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
 
    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;
 
            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }
 
    // Making new string of enough length
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
 
    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }
 
    result[i] = '\0';
    return result;
}
int main(int argc, char  *argv[])
{
    FILE* ptr;
    char str[200];
    char search[] = "rank_view";
    char span_class[] = "sr-only";
    char rank_search_strong_sell[] = "5-Strong Sell";
    char rank_search_sell[] = "4-Sell";
    char rank_search_hold[] = "3-Hold";
    char rank_search_buy[]  = "2-Buy";
    char rank_search_strong_buy[]  = "1-Strong Buy";
    char title_search[] = "<title>";
    char symbol_search[] = "var _ticker_string";
    char last_price_search[] = "p class=\"last_price\"";

    char *charptr;
    char *spanclassptr;
    char *rankptr;
    char *titleptr;
    char *symbolptr;
    char *lastpriceptr;
    char c[] = " - Stock Price Today - Zacks";
    char d[] = "";
    char *result= NULL;

    if ( argc == 1 ) {
	printf ( "Please enter the name of the stock symbol data file to process\n");
        exit (0);
    }

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\"%d/%d/%d\",", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);

    ptr = fopen(argv[1], "r");
 
    if (NULL == ptr) {
        printf("File can't be opened \n");
	exit(0);
    }
 
    //printf("content of this file are \n");
    while (fgets(str, 200, ptr) != NULL) {


	//////////  Search for the Symbol  //////////////////
        symbolptr =  strstr ( str, symbol_search );
        if (symbolptr != NULL) /* Substring title found */
	{
	        str[strlen(str) - 1] = '\0';
		result = replaceWord(str, "var _ticker_string   =", "");
		result = replaceWord(result, ";", "");
		result = replaceWord(result, "'", "");
		result = replaceWord(result, " ", "");
		printf("\"%s\",", result);

	}


	//////////  Search for the title  //////////////////
        titleptr =  strstr ( str, title_search );
        if (titleptr != NULL) /* Substring title found */
	{
	        str[strlen(str) - 1] = '\0';
		result = replaceWord(str, c, d);
		result = replaceWord(result, "    <title>", "");
		result = replaceWord(result, "</title>", "");

		printf("\"%s\",", result);
	}


	//////////  Search for the last price  //////////////////
        lastpriceptr =  strstr ( str, last_price_search );
        if (lastpriceptr != NULL) /* Substring title found */
	{
	        str[strlen(str) - 1] = '\0';
		
		result = replaceWord(str, "         <p class=\"last_price\">", "");
		result = replaceWord(result, "<span>", "");
		result = replaceWord(result, "</span>", "");
		result = replaceWord(result, "</p>", "");
		result = replaceWord(result, "USD", "");
		result = replaceWord(result, "$", "");

		printf("%s,", result);
		
	}



	//////////// Search for the Ranking ///////////////
        charptr =  strstr ( str, search );
	//printf("Found = %s", str);

        if (charptr != NULL) /* Substring rank_view found */
	{
		//printf("Found = %s", str);

                if (fgets(str, 200, ptr) != NULL) {
                     spanclassptr =  strstr( str, span_class );
                     if (spanclassptr != NULL) /* Substring found */
	             {
		         //printf(">>>>>>>>>>>> next line = %s\n", str);

			 // Sell
                         rankptr =  strstr( str, rank_search_sell );
                         if (rankptr != NULL) /* Substring found */
			 {
		             printf("\"SELL\"" );
			 }

			 // strong Sell
                         rankptr =  strstr( str, rank_search_strong_sell );
                         if (rankptr != NULL) /* Substring found */
			 {
		             printf("\"Strong SELL\"" );
			 }

			 // Hold
                         rankptr =  strstr( str, rank_search_hold );
                         if (rankptr != NULL) /* Substring found */
			 {
		             printf("\"HOLD\"" );
			 }

			 // Buy
                         rankptr =  strstr( str, rank_search_buy );
                         if (rankptr != NULL) /* Substring found */
			 {
		             printf("\"BUY\"" );
			 }

			 // Strong Buy
                         rankptr =  strstr( str, rank_search_strong_buy );
                         if (rankptr != NULL) /* Substring found */
			 {
		             printf("\"Strong BUY\"" );
			 }
		         printf("\n" );
                     }
                }
	}
    }
 
    fclose(ptr);
    return 0;
}
