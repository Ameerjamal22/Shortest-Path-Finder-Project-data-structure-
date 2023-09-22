#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNumberOfVertices 30
#define MAXNumberOfChars 30

// student name : ameer rabie , student id : 1211226 , student section : 3 .

/*
    struct node for the vertix node .
    Test : OK .
*/
struct ListNode {

    int index ;
    char name[MAXNumberOfChars] ;
    struct ListNode * next ;
    int size ;

};

typedef struct ListNode * ListOfVertices ; // type defining the pointer to the vertix node with ListOfVertices .


/*
    def : a function that creates list of vertices used to map the cities to the index of them in the adjacency list .
    return : returns a pointer to the list of vertices .
    Test : OK .
*/
ListOfVertices CreateList(){

    struct ListNode * Head = (struct ListNode *)malloc (sizeof(struct ListNode )) ; // dynamically allocating the head node in the memory .

    Head -> next = NULL ;
    Head -> size = 0 ; // initializes the size of the list to zero
    Head -> index = -1 ;

    return Head ;
}


/*
    Parameters : a pointer to the pointer that points to the Head node of the list of Vertices and array of chars that contain the new city name .
    def : inserts a new city to the list of graph vertices if it does not exist already and give it a unique index .
    Test : OK .
*/
void InsertVertix (  struct ListNode ** Head , char vertixName[] ){

    struct ListNode * temp = (*Head) ; // defining a pointer to traverse the list of vertices .

    /*
        checks if the name already exist in the list of vertices , and if so gets out of the function .
    */
    while (1){

        if ( temp -> index != -1  && strcmp( temp -> name , vertixName  ) == 0  ){

            return ;

        }

        if ( temp -> next == NULL ){

            break ;

        }
        temp = temp -> next ;

    }

    // if the city does not exist in the list of vertices creates a new vertix node and it to the list after giving it a unique id  .
    struct ListNode * newVertix = ( struct ListNode *)malloc (sizeof( struct ListNode ) ) ;

    // connecting the node to the list and copying the name to the attribute of the new node .
    newVertix -> index = (*Head) -> size ;
    strcpy( newVertix -> name , vertixName ) ;
    newVertix -> next = NULL ;

    if (temp == *Head) { // if list is empty
        (*Head) -> next = newVertix;
    } else {
        temp -> next = newVertix;
    }

    (*Head) -> size += 1 ; // incrementing the size of the list of vertices by one .

    return ;

}


/*
    parameter : a pointer to the head node of the list of vertices .
    def : print the list of vertices and their id's used for debuging .
    Test : OK .
*/
void DisplayListOfVertices ( struct ListNode * list ){


    if ( list == NULL || list -> next == NULL ){

        printf("there is no vertices in the list \n") ;
        return ;

    }
    list = list -> next ;


    // loops through the list of vertices and prints every vertix name and id  .
    while (list != NULL ){

        printf("%d , %s   ....", list -> index , list -> name ) ;
        list = list -> next ;

    }
    printf("\n") ;

    return ;

}

/*
    parameters : a pointer to the pointer that points to the Head of the list of vertices
    def : deletes the list of vertices (used for debuging )
    Test : OK .
*/
void deleteListOfVertices ( struct ListNode ** list ){

    struct ListNode * temp ;

    if ( (*list) -> next == NULL ){
        return ;
    }

    struct ListNode * temp2 = (*list) ;

    (*list) = (*list)  -> next ;

    // loops through list and deletes every node in it .
    while ( (*list) != NULL ){

        temp = (*list) ;
        (*list) = (*list) -> next ;
        free(temp) ;

    }

    // reinitializing the attributes of the list .
    (*list) = temp2 ;
    (*list) -> size = 0 ;
    (*list) -> next = NULL ;
    (*list) -> index = -1 ;

}


/*
    Test : OK .
    Parameters : a pointer to the integer that represent the number of edges in the file .
    def : takes the vertices from the file and add them one by one to the list of vertices to map them to the index of them in the adjacency list .
*/
ListOfVertices  TakeverticesFromFile( int * NumberOfEdges ){

    FILE * fp = fopen("cities.txt" , "r" ) ; // opening the input file .

    // checking if the file opening operation has failed .
    if ( fp == NULL ){

        printf("failed to open the file ") ;
        return NULL ;

    }


    char source[MAXNumberOfChars] ;
    char dest[MAXNumberOfChars] ;
    char distance[MAXNumberOfChars] ;

    for (int i = 0 ; i < MAXNumberOfChars ; i ++ ){

        source[i] = dest[i] = '\0' ;

    }

    ListOfVertices vertices = CreateList() ; // creating the list of vertices that will store the vertices .


    // looping until the end of file to take the vertices names .
    while ( fscanf(fp , "%s %s %s\n", source , dest , distance  ) == 3 ){


        InsertVertix( &vertices , source ) ;
        InsertVertix( &vertices , dest ) ;

        (*NumberOfEdges) += 1 ;

        for (int i = 0 ; i < MAXNumberOfChars ; i ++ ){

            source[i] = dest[i] = '\0' ;

        }

    }

    fclose(fp); // closing the input file .

    return vertices ; // returning the list of vertices scanned from the file .

}

/*
    parameter : the name of vertix , a pointer to the head of the list of vertices .
    def : searches for the vertix name in the list of veritces and returns its index ;
    return : returns an integer index of the vertix .
    Test : OK .
*/
int getVertixIndex( char name[] , ListOfVertices vertices ){

    struct ListNode * temp = vertices -> next ; // defining a pointer

    // loops through the list of vertices to find and compares the passed name of the vertix to the current node .
    while (temp != NULL ){

        // if the passed name is the same in the node returns the node index .
        if ( strcmp( name , temp -> name ) == 0  ){

            return temp -> index ;

        }

        temp = temp -> next ;
    }

    // if the passed name of the vertix is not in the list prints a message to the user and returns -1 .
    printf("Vertix not found \n") ;
    return -1 ;


}

/*
    struct list of graphs node to store the nodes connected to each node .
*/
struct GraphNode {

    int index ; // stores the index of the node linked to the Head node
    int distance ; // stores the distance from the Head node to each node connected to it .
    struct GraphNode * next ; // a pointer to the next node in the graph node .
    struct GraphNode * last ; // a pointer to the last node to make the insertion of the node connected node time complexity o(1)

};


typedef struct GraphNode * GraphNode ; // type defining the list of graph nodes

/*
    Parameters : the index of the Head node .
    def : creates a list of graph node that is connected to the passed index node .
    return : returns a pointer to the Head of the list of graph nodes .
*/
GraphNode CreateGraphNode ( int index  ){

    GraphNode temp = ( GraphNode )malloc( sizeof( struct GraphNode ) ) ; // creates a graph node and dynamically allocate a place for it in the memory .

    temp -> index = index ;
    temp -> distance = 0 ; // the distance between the head node and itself is zero .
    temp -> last = temp ; // initializes the last element to the head node as the node itself .
    temp -> next = NULL ;

    return temp ; // returns a pointer to the head node of the list .

}

/*
    Parameters : the index of the destination in the edge , int distance : distance between the source and destination
    a pointer to the head node of the list of graph nodes of connected to the source .
    def : adds the edge to the list of graph nodes of the source node .
*/
void insertAdjacentNode ( int destantionIndex , int distance , GraphNode * source ){

    // creates the node to be linked and initialize its index and distance .
    GraphNode temp = ( GraphNode )malloc( sizeof (struct GraphNode ) ) ;
    temp -> index = destantionIndex ;
    temp -> distance = distance ;
    temp -> next = NULL ;

    // links the node to the list .
    (*source) -> last -> next = temp ;
    (*source ) -> last = temp ;

}

/*
    Parameters : a pointer to the pointer that points to the head node of the list of graph nodes .
    def : deletes the list
    used for testing and memory cleaning .
    Test : OK .
*/
void DeleteEdgesList( struct GraphNode ** g ){

    GraphNode temp = (*g) -> next ;
    GraphNode temp2 ;

    // iterates through all the connected lists to the node and deletes them  .
    while ( temp != NULL ){

        temp2 = temp ;
        temp = temp -> next ;
        free(temp2) ;

    }

    (*g) -> last = (*g) ; // the last node will become the head node itself .
    (*g) -> next = NULL ; // the next of the head node is null .

}

/*
    Parameters : array of graph nodes lists (adjacency list) , int size :number of vertices .
    def : function to prints the adjacency list ( used for debuging ) .
    Test : OK .
*/
void printGraph( GraphNode Graph[MAXNumberOfVertices]  , int size ){

    int i = 0 ;
    // loop through every vertix list of connected nodes and prints all of them .
    while ( size -- ){

        printf("%d -> " , i ) ;
        struct GraphNode * temp = Graph[i] -> next ;

        while ( temp != NULL ){

            if (temp == NULL )break ;
            printf(" ( %d , %d )" , temp -> index , temp -> distance ) ;
            temp = temp -> next ;


        }
        printf("\n") ;

        i ++ ;

    }


}

/*
    Parameters : integer index , list of veritces in the graph .
    return : returns s string that represents the name if the city that have the passed index .
    Test : OK .
*/
char * getTheCityByIndex ( int index  , ListOfVertices list ){

    struct ListNode * temp = list -> next ;

    // loops through the nodes to the vertices list until the given index is found , and if so returns the name of the city with that index .
    while ( temp != NULL ){

        if ( temp -> index == index ){

            return temp -> name ; // returns the name of the city .

        }

        temp = temp -> next ;

    }

    // if the index is not found in the list prints a message to the user and returns null .
    printf("city not found \n") ;
    return NULL ;

}

#define MAX 100

typedef struct queueRecord * queue ;

struct queueRecord{

    int size ;
    int front ;
    int rear ;
    int array[MAX] ;


};

queue createQueue (){

    queue q= (queue)malloc(sizeof(struct queueRecord)) ;

    q -> size = 0 ;
    q -> front = 0 ;
    q -> rear = 0 ;
    for (int i = 0 ; i < MAX ; i ++ )q->array[i] = -1 ;

    return q ;

}

void Enqueue( int x ,queue q ){

    if (q -> size == MAX){
        printf("queue is full \n") ;
        return ;
    }

    q -> array[q-> rear ] = x ;
    q -> rear = ( q->rear + 1 )% MAX ;
    q->size += 1 ;

}

void dequeue ( queue q ){

    q->array[q->front] = -1 ;
    q->front = (q->front + 1 ) % MAX ;
    q -> size -= 1 ;

}

int front (queue q ){

    if (q ->size == 0 ){
        printf("queue is empty \n") ;
        return -1 ;
    }

    return q->array[q->front] ;

}

void deleteQueueElement( queue q ){

    if (q -> size == 0 ){
        printf("queue is already empty \n") ;
        return ;
    }

    while (q -> size > 0 ){
        printf(" %d ",front(q)) ;
        dequeue(q) ;
    }
    printf("\n") ;
}

/*
    Parameters : string source , destination , array of lists of graph nodes (adjacency list) , list of all vertices in the graph .
    def : prints the shortest path (edges) between the source and the destination (it considers that all the edges of the graph have the same weight )
    o(V+E) .
*/
void Bfs ( char source[MAXNumberOfChars] , char destnation[MAXNumberOfChars] , GraphNode Graph[MAXNumberOfVertices] , ListOfVertices vertices ){

    int sor = getVertixIndex( source , vertices ) ; // gets the index of the source from the list of vertics and store it in integer sor .
    int des = getVertixIndex( destnation , vertices ) ; // gets the index of the destination from the list of vertics and store it in integer des .

    // checks if one of them does not exist , and if so prints a message to the user and gets out of the function .
    if ( sor == -1 || des == -1 ){

        printf("one of the nodes does not exist \n");
        return ;

    }

    int visted[ ( vertices -> size ) ] ; // creating visited array to check if the vertix is visited or not .
    int parent[ ( vertices -> size ) ] ; // create a parent array that stores the parent of every node in the graph after the bfs to detect the path

    for (int i = 0 ; i < ( vertices -> size ); i ++ )visted[i] = parent[i] = -1 ; // initializes the values of all indices of the array to -1 .


    queue q = createQueue() ; // create a queue that will be used to store the nodes that we want to traverse the adjacent nodes of them .

    Enqueue( sor , q ) ; // enques the source to the q ,so we can start the bfs from .
    visted[sor] = 1 ; // marks the source as visited since it is pushed to the queue .
    parent[sor] = -2 ; // setting the parent of the source node to -2 to recognize it when detecting the path .

    // the bfs loop .
    while ( q -> size > 0 ){

        int current = front( q ) ; // setting the current node to traverse as the front of the queue .
        GraphNode temp = Graph[current] -> next ; // creating a temp graph node pointer to traverse all the edges between the current node and its adjacent nodes .

        while ( temp != NULL ){

            // if the node is not visited , then adds it to the queue , and marks it as visited , and setting is parent as current .
            if ( visted[ temp -> index ] == -1 ){

                Enqueue( temp -> index , q ) ;
                parent[ temp -> index ] = current ;
                visted[ temp -> index ] = 1 ;

            }

            temp = temp -> next ;

        }

        if ( q -> size == 0 ){

            break ;

        }
        dequeue( q ) ; // removing the traversed node from the queue .

    }

    int temp = des ;

    // checking if the parent of the destination is -1 then there is no path between the source and the destination node .
    // and if so prints a message to the user and gets out of the function .
    if ( parent[temp] == -1 ){

        printf("there is no path between the two nodes \n") ;
        return ;

    }

    FILE* output = fopen( "shortest_distance.txt" , "a" ) ; // opening the file to append the new result of bfs and the path .

    // creating an array stack to store the path .
    int stack[vertices -> size ] ;
    int top = -1 ;

    // path detection
    while (1){

        // if the temp is -2 then we added the source node of the stack so we break out of the loop
        if ( temp == -2 ){

            break ;

        }
        stack[++top] = temp ; // adding the index of the node in the path to the stack .
        temp = parent[temp] ;

    }

    // prints the path to the console and the file .
    printf( "BFS : ") ;
    printf( "[" ) ;

    int temptop = top ;

    while ( top > 0 ){

        printf( "%s ->" , getTheCityByIndex( stack[top--] , vertices )) ;


    }
    printf(" %s ]" , getTheCityByIndex( des , vertices ) ) ;
    printf("\n") ;



    fprintf( output , "BFS : ") ;
    fprintf( output , "[") ;

    top = temptop ;
    while ( top > 0 ){

        fprintf( output , "%s ->" , getTheCityByIndex( stack[top--] , vertices )) ;


    }
    fprintf( output , " %s ]" , getTheCityByIndex( des , vertices ) ) ;
    fprintf( output , "\n") ;

    fclose( output ) ;

}

/*
    Parameters : string source , destination , array of lists of graph nodes (adjacency matrix) , list of vertices .
    def : computes the shortest path distance and prints the path from the source to the destination (for weighted graphs ).
    Test : OK .
*/

void Dijkstra ( char source[MAXNumberOfChars] , char destination[MAXNumberOfChars] , GraphNode Graph[MAXNumberOfVertices] , ListOfVertices vertices ){

    int sor = getVertixIndex( source , vertices ) ; // getting the index of the source and storing it in integer sor .
    int dest = getVertixIndex( destination , vertices ) ; // gets the index of the destination and stores it in integer dest .

    // checks if one of them does not exist , and if so prints a message to the user and gets out of the function .
    if ( sor == -1 || dest == -1 ){

        printf("one of the nodes does not exist \n");
        return ;

    }

    int distance[vertices -> size ] ; // defines the array that will store the distance from the source to every node .
    int parent[ vertices -> size ] ; // defines the parent array that will store the parent of every node to detect the path .


    for (int i = 0 ; i < vertices -> size ; i ++ )distance[i] = parent[i] = -1 ; // initialize the values of both arrays to -1

    queue q = createQueue() ; // creates a queue to store the nodes that we want to traverse their adjacent nodes .

    parent[sor] = -2 ; // marks the parent of the source to -2 to recognize it  while saving the path
    distance[sor] = 0 ; // sets the distance of the source to 0

    Enqueue( sor , q ) ; // adding the source node index to the queue .

    int current ;
    GraphNode temp ;

    while ( q -> size > 0 ){

        current = front(q) ; // setting the current node to traverse as the top of the queue .
        temp = Graph[current] -> next ; // setting the temp pointer to traverse the adjacent nodes of the current node .

        while ( temp != NULL ){

            // if the distance is infinite (-1) or the distance of the current node + the weight of the edge  between the temp node and current < distance to the temp node
            // then we update the distance of the temp node . and enqueue temp node to the queue , and update the parent of the temp node to the current node
            if ( distance[ temp -> index ] == -1 || distance[current] + temp -> distance < distance[ temp -> index] ){

                distance[ temp -> index ] = distance[current] + temp -> distance ;
                parent[ temp -> index ] = current ;
                Enqueue( temp -> index , q ) ;

            }

            temp = temp -> next ;
        }

        dequeue(q) ; // deletes the current node from the queue after traversing it .

    }


    parent[sor] = -2 ;

    int temp1 = dest ;

    // checks if the parent of the destination is -1 ,and if so then there is no path between the source and the destination so it prints a message to the user and get out of the function
    if ( parent[ temp1 ] == -1 ){

        printf("there is no path between the two nodes \n") ;
        return ;

    }

    //saving the path to an array stack and then prints it to the console and the short distance file
    FILE *output = fopen( "shortest_distance.txt" , "a" ) ;

    fprintf( output , "Dijkstra :- " ) ;
    fprintf( output , "Distance = %d : " , distance[ dest ] ) ;
    fprintf( output , "   Path :") ;

    int stack[vertices -> size ] ;
    int top = -1 ;

    while (1){

        if ( temp1 == -2 ){

            break ;

        }
        stack[++top] = temp1 ;
        temp1 = parent[temp1] ;

    }

    int tempTop = top ;

    fprintf( output , "[") ;

    while ( top > 0 ){

        fprintf( output , "%s ->%dkm->" , getTheCityByIndex( stack[top] , vertices ) , distance[stack[top-1] ] - distance[stack[top]]) ;
        top -- ;

    }

    fprintf( output , " %s ]" , getTheCityByIndex( dest , vertices ) ) ;
    fprintf( output , "\n") ;

    fclose(output) ;

    printf( "Dijkstra :- " ) ;
    printf( "Distance = %d : " , distance[ dest ] ) ;
    printf( "   Path :") ;

    printf( "[" ) ;

    while ( tempTop > 0 ){

        printf( "%s -> %dkm ->" , getTheCityByIndex( stack[tempTop] , vertices ) , distance[stack[tempTop-1] ] - distance[stack[tempTop]]) ;
        tempTop -- ;

    }

    printf( " %s ]" , getTheCityByIndex( dest , vertices ) ) ;
    printf( "\n") ;

}






int main()
{

    int NumberOfEdges = 0 ; // initializes the number of edges to zero
    ListOfVertices vertices ; // creates the list that will store the vertices and their index .

    vertices = TakeverticesFromFile( &NumberOfEdges ) ; // take the list of vertices from the file and updating the number of edges after counting it from the file

    //DisplayListOfVertices( list ) ;
    //printf("%d\n", NumberOfEdges) ;

    char source[MAXNumberOfChars] , destenation[MAXNumberOfChars] ; // defining the strings that will store the source and destination scanned from the file .
    int distance ; // defining the variable that will store the distance scanned from the file .

    struct GraphNode * Graph[MAXNumberOfVertices] ; // defining the adjacency list that will store the graph .

    for (int i = 0 ; i < MAXNumberOfVertices ; i ++ )Graph[i] = NULL ;

    for (int i = 0 ; i < vertices -> size ; i ++ ){

        Graph[i] = CreateGraphNode( i ) ;

    }

    /*
        reading the edges from the file and storing them in the adjacency list .
    */
    FILE *input = fopen( "cities.txt"  , "r" ) ;

    if ( input == NULL ){

        printf("the file does not exist \n") ;

    }



    for (int i = 0 ; i < NumberOfEdges ; i ++ ){

        fscanf( input ,"%29s %29s %d%*s", source, destenation, &distance);


        insertAdjacentNode( getVertixIndex( destenation ,vertices ) , distance , &Graph[ getVertixIndex(source , vertices ) ] ) ;
        //insertAdjacentNode( getVertixIndex( source ,vertices ) , distance , &Graph[ getVertixIndex( destenation , vertices ) ] ) ;

    }

    fclose( input ) ;


    printf("Welcome to the shortest Path program \n\n") ;

    // defining the variables that will store the inputs from the user .
    int choice ;
    char userSource[MAXNumberOfChars] ;
    char userDestination[MAXNumberOfChars] ;

    while (1){

        printf("\nEnter your Choice : \n") ;
        printf("1-Load data from the file cities.txt  .\n") ;
        printf("2-Enter source .\n") ;
        printf("3-Enter destination . \n") ;
        printf("4-Exit\n") ;

        scanf("%d" , &choice ) ;

        // scans the Graph and the list of vertices from the file .
        if ( choice == 1 ){

            vertices = TakeverticesFromFile( &NumberOfEdges ) ;
            //DisplayListOfVertices( list ) ;

            for (int i = 0 ; i < MAXNumberOfVertices ; i ++ )Graph[i] = NULL ;

            for (int i = 0 ; i < vertices -> size ; i ++ ){

                Graph[i] = CreateGraphNode( i ) ;

            }

            FILE *input = fopen( "cities.txt"  , "r" ) ;

            if ( input == NULL ){

                printf("the file does not exist \ n") ;
                continue ;

            }



            for (int i = 0 ; i < NumberOfEdges ; i ++ ){

                fscanf( input ,"%29s %29s %d%*s", source, destenation, &distance);


                insertAdjacentNode( getVertixIndex( destenation ,vertices ) , distance , &Graph[ getVertixIndex(source , vertices ) ] ) ;
                //insertAdjacentNode( getVertixIndex( source ,vertices ) , distance , &Graph[ getVertixIndex( destenation , vertices ) ] ) ;

            }


            fclose( input ) ;

        }

        // take the source city as an input from the user .
        else if ( choice == 2 ){

            for( int i = 0 ; i < MAXNumberOfChars ; i ++ )userSource[i] = '\0' ;
            printf("Enter the source :") ;
            scanf("%s" , userSource ) ;

            if ( getVertixIndex( userSource , vertices ) == -1  ){

                printf("the node does not exist \n") ;
                continue ;

            }

        }

        // take the destination from the user and computes the shortest path by bfs and dijkstra .
        else if ( choice == 3 ){

            for( int i = 0 ; i < MAXNumberOfChars ; i ++ )userDestination[i] = '\0' ;
            printf( "Enter the destenation :" ) ;
            scanf("%s" , userDestination ) ;

            if ( getVertixIndex( userDestination , vertices ) == -1  ){

                printf("the node does not exist \n") ;
                continue ;

            }

            if ( getVertixIndex( userSource , vertices ) == -1 ){

                printf("source node does not exit in the file \n" ) ;
                continue ;

            }

            if ( getVertixIndex( userDestination , vertices ) == -1 ){

                printf("destination node does not exit in the file \n" ) ;
                continue ;

            }

            FILE* output = fopen( "shortest_distance.txt" , "a" ) ;

            fprintf( output , "the shortest path from %s to %s :\n" , userSource , userDestination ) ;
            fclose( output ) ;

            Bfs( userSource , userDestination , Graph , vertices ) ;
            Dijkstra( userSource , userDestination , Graph , vertices ) ;

            output = fopen( "shortest_distance.txt" , "a" ) ;
            fprintf( output , "\n" ) ;
            fclose( output ) ;

        }
        // breaks out of the loop if the choice is 4 .
        else if ( choice == 4 ){

            break ;

        }

        else {

            printf("invalid choice \n") ;
            continue ;

        }

    }



    return 0;
}
