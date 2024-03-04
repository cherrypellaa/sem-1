#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 4000
#define MAX_LENGTH 100

struct Data {
    char location[MAX_LENGTH];
    char city[MAX_LENGTH];
    int price;
    int rooms;
    int bathrooms;
    int carParks;
    char type[MAX_LENGTH];
    char furnish[MAX_LENGTH];
}dataset[4000];

struct Data dataset[MAX_ROWS];
int num_rows = 0;

void readCSVFile(const char *filename) 
{
    FILE *file = fopen(filename, "r");

    char line[MAX_LENGTH];
    int isFirstLine = 1; 
    while (fgets(line, sizeof(line), file)) 
    {
        if (isFirstLine) 
        {
            isFirstLine = 0;
        }

        if (num_rows >= MAX_ROWS) 
        {
            printf("Too many rows in the file. Increase MAX_ROWS.\n");
            break;
        }

        char *token = strtok(line, ",");
        if (token) 
        {
            strcpy(dataset[num_rows].location, token);

            token = strtok(NULL, ",");
            if (token) 
            {
                strcpy(dataset[num_rows].city, token);

                token = strtok(NULL, ",");
                if (token) 
                {
                    dataset[num_rows].price = atoi(token);

                    token = strtok(NULL, ",");
                    if (token) 
                    {
                        dataset[num_rows].rooms = atoi(token);

                        token = strtok(NULL, ",");
                        if (token) 
                        {
                            dataset[num_rows].bathrooms = atoi(token);

                            token = strtok(NULL, ",");
                            if (token) 
                            {
                                dataset[num_rows].carParks = atoi(token);

                                token = strtok(NULL, ",");
                                if (token) 
                                {
                                    strcpy(dataset[num_rows].type, token);

                                    token = strtok(NULL, ",");
                                    if (token) 
                                    {
                                        strcpy(dataset[num_rows].furnish, token);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        num_rows++;
    }

    fclose(file);
}

void displayData(int n) 
{
    printf("%-25s%-15s%-15s%-8s%-12s%-12s%-15s%-15s\n", "Location", "City", "Price", "Rooms", "Bathrooms", "CarParks", "Type", "Furnish");
    for (int i = 1; i < (n > num_rows ? num_rows : n); ++i) 
    {
        printf("%-25s%-15s%-15d%-8d%-12d%-12d%-15s%-15s\n", dataset[i].location, dataset[i].city, dataset[i].price,
               dataset[i].rooms, dataset[i].bathrooms, dataset[i].carParks, dataset[i].type, dataset[i].furnish);
    }
    printf("Press Enter To Continue...");
    getchar();
	getchar();
	system("clear");
}

void searchData(const char *column, const char *query) 
{
    int found = 0;
    
    if (strcmp(column, "Location") == 0 || strcmp(column, "City") == 0 || strcmp(column, "Type") == 0 || strcmp(column, "Furnish") == 0 || strcmp(column, "Price") == 0 || strcmp(column, "Rooms") == 0 || strcmp(column, "Bathrooms") == 0 || strcmp(column, "CarParks") == 0)
    {
        printf("What data do you want to find = ");
        scanf("%s", query);
        for (int i = 0; i < num_rows; ++i) 
        {
            if ((strcmp(column, "Location") == 0 && strstr(dataset[i].location, query) != NULL) ||
                (strcmp(column, "City") == 0 && strstr(dataset[i].city, query) != NULL) ||
                (strcmp(column, "Type") == 0 && strstr(dataset[i].type, query) != NULL) ||
                (strcmp(column, "Furnish") == 0 && strstr(dataset[i].furnish, query) != NULL) ||
                (strcmp(column, "Price") == 0 && dataset[i].price == atoi(query)) ||
                (strcmp(column, "Rooms") == 0 && dataset[i].rooms == atoi(query)) ||
                (strcmp(column, "Bathrooms") == 0 && dataset[i].bathrooms == atoi(query)) ||
                (strcmp(column, "CarParks") == 0 && dataset[i].carParks == atoi(query))) 
                {

                    if (!found) 
                    {
                        printf("Data found. Detail of data:\n");
                        printf("%-25s%-15s%-15s%-8s%-12s%-12s%-15s%-15s\n", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");
                        found = 1;
                    }

                    printf("%-25s%-15s%-15d%-8d%-12d%-12d%-15s%-15s\n", dataset[i].location, dataset[i].city, dataset[i].price,
                       dataset[i].rooms, dataset[i].bathrooms, dataset[i].carParks, dataset[i].type, dataset[i].furnish);
            }
        }
    }
    else 
    {
        printf("Invalid column name.\n");
    }
    
    if (!found) 
    {
        printf("Data not found!\n");
    }
    
    printf("Press Enter To Continue...");
    getchar();
    getchar();
    system("clear");
}

void displayFirstNRows(int n) 
{
    printf("%-25s%-15s%-15s%-8s%-12s%-12s%-15s%-15s\n", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");

    for (int i = 1; i < (n < num_rows ? n : num_rows); ++i) 
    {
        printf("%-25s%-15s%-15d%-8d%-12d%-12d%-15s%-15s\n", dataset[i].location, dataset[i].city, dataset[i].price,
               dataset[i].rooms, dataset[i].bathrooms, dataset[i].carParks, dataset[i].type, dataset[i].furnish);
    }
}

char *getColumnValue(struct Data data, const char *column) 
{
    static char value[MAX_LENGTH]; 

    if (strcmp(column, "Location") == 0) 
    {
        strcpy(value, data.location);
    } 
    else if (strcmp(column, "City") == 0) 
    {
        strcpy(value, data.city);
    } 
    else if (strcmp(column, "Type") == 0) 
    {
        strcpy(value, data.type);
    } 
    else if (strcmp(column, "Furnish") == 0) 
    {
        strcpy(value, data.furnish);
    } 
    else 
    {
        value[0] = '\0'; 
    }
    
    return value;
}

void bubbleSort(struct Data *arr, int n, const char *column, const char *order) 
{
    int i, j;
    struct Data temp;

    for (i = 0; i < n - 1; i++) 
    {
        for (j = 0; j < n - i - 1; j++) 
        {
            int cmp = 0;

            if (strcmp(column, "Price") == 0) 
            {
                cmp = (order[0] == 'a') ? (arr[j].price > arr[j + 1].price) : (arr[j].price < arr[j + 1].price);
            } 
            else if (strcmp(column, "Rooms") == 0) 
            {
                cmp = (order[0] == 'a') ? (arr[j].rooms > arr[j + 1].rooms) : (arr[j].rooms < arr[j + 1].rooms);
            } 
            else if (strcmp(column, "Bathrooms") == 0) 
            {
                cmp = (order[0] == 'a') ? (arr[j].bathrooms > arr[j + 1].bathrooms) : (arr[j].bathrooms < arr[j + 1].bathrooms);
            } 
            else if (strcmp(column, "CarParks") == 0) 
            {
                cmp = (order[0] == 'a') ? (arr[j].carParks > arr[j + 1].carParks) : (arr[j].carParks < arr[j + 1].carParks);
            } 
            else if (strcmp(column, "Location") == 0 || strcmp(column, "City") == 0 || strcmp(column, "Type") == 0 || strcmp(column, "Furnish") == 0) 
            {
                const char *val1 = getColumnValue(arr[j], column);
                const char *val2 = getColumnValue(arr[j + 1], column);
                cmp = (order[0] == 'a') ? (strcmp(val1, val2) > 0) : (strcmp(val1, val2) < 0);
            }

            if (cmp) 
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void sortData(const char *column, const char *order) 
{
    if (strcmp(column, "Price") == 0 || strcmp(column, "Rooms") == 0 || strcmp(column, "Bathrooms") == 0 ||
        strcmp(column, "CarParks") == 0 || strcmp(column, "Location") == 0 || strcmp(column, "City") == 0 ||
        strcmp(column, "Type") == 0 || strcmp(column, "Furnish") == 0) 
    {
        
            printf("Sort ascending or descending (asc/dsc)? ");
            scanf("%s", order);

            if (strcmp(order, "asc") == 0 || strcmp(order, "dsc") == 0) 
            {
                bubbleSort(dataset, num_rows, column, order);
                displayFirstNRows(10);
            } 
            else 
            {
                printf("Invalid order. Please use 'asc' or 'dsc'.\n");
            }
    } 
    else 
    {
        printf("Invalid column name.\n");
    }
    printf("Press Enter To Continue...");
    getchar();
    getchar();
    system("clear");
}



void export(int num_rows);

void exportData(int num_rows) 
{
    printf("File name: ");
    char exportFileName[MAX_LENGTH];
    scanf("%s", exportFileName);

    strcat(exportFileName, ".csv");
	
	FILE *fp = fopen(exportFileName, "w");
	
	fprintf(fp, "Location,City,Price,Rooms,Bathrooms,CarParks,Type,Furnish\n");
	
	for (int j = 0; j < num_rows; j++) 
    {
		fprintf(fp, "%s,%s,%d,%d,%d,%d,%s,%s\n", dataset[j].location, dataset[j].city, dataset[j].price,
			dataset[j].rooms, dataset[j].bathrooms, dataset[j].carParks, dataset[j].type, dataset[j].furnish);
	}
	
	fclose(fp);
	printf("Data successfully written to file %s!\n", exportFileName);
    printf("Press Enter To Continue...");
	getchar();
	getchar();
	system("clear");
}

int main() 
{
    readCSVFile("file.csv");

    int choice, rows_to_display;
    char column[MAX_LENGTH], query[MAX_LENGTH], order[MAX_LENGTH];

    do {
        printf("\nWhat do you want to do?\n1. Display data\n2. Search Data\n3. Sort Data\n4. Export Data\n5. Exit\nYour choice: ");
        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid input. Please enter a number.\n");
            getchar();
            getchar();
            system("clear");
        }

        switch (choice) 
        {
            case 1:
                printf("Number of rows: ");
                if (scanf("%d", &rows_to_display) != 1) 
                {
                    printf("Invalid input. Please enter a number.\n");
                    scanf("%*s"); 
                    break;
                }
                displayData(rows_to_display);
                break;
            case 2:
                printf("Choose column: ");
                scanf("%s", column);
                
                searchData(column, query);
                break;
            case 3:
                printf("Choose column (Price, Rooms, Bathrooms, CarParks, Location, City, Type, Furnish): ");
                scanf("%s", column);
                sortData(column, order); 
                break;
            case 4:
                exportData(num_rows);
                break;
            case 5:
                printf("Exiting...\n");
                exit(1);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } 
    while (choice != 5);

    return 0;
}