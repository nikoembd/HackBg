/*****************************************************************
* Description: C implementation of Dijkstra's algorithm
*
* Author: Nikolay Yanakiev (Niko)
* Date: 21.09.2014
*****************************************************************/
/*
Implement Dijsktra's algorithm for finding optimal paths using:
Data structures
C or C++
The input is going to be be:
N M - number of nodes and number connections
n1 n2 w - M lines of node1 and node2 numbers and the weight of the connection
a b - on the M+1-st line, vertices a and b whose shortest path you should find, -1 if there is no path
On the exit - one number - the length of the path. With a newline at the end or not, it's ok both ways.
Important
The grading will include mostly code reviewing - write good code.
*/

#include <stdio.h>
#include <stdlib.h>
//
// Local Constants
//

#define cN_min 2
#define cM_min (cN_min - 1)
#define cINFINITE (unsigned int)(0xFFFF)
#define cFALSE 0u
#define cTRUE 1u

//
// Local Variables
//
static signed int N = cN_min;
static signed int M = cM_min;

//
// Local Prototypes
//
signed int DijkstraAlgo(unsigned int **uiGraph, unsigned long ulSize, unsigned int uiSrc);



int main (void)
{
    static unsigned int uiCntRow, uiCntCol;
    static signed int uiStart = -1, uiEnd = -1;
    static signed int siTemp;
    static signed int siResult;
    static unsigned int **Graph = NULL;

    // 1.1. Ask for input NodesNumber (max sint32_max and min 2)
    while (cN_min == N)
    {
        printf("\n\r-------------------------");
        printf("\n\rNumber of nodes: N = ");
        scanf("%d", &N);
        if ((N < cN_min) && (N != 0) )
        {
            printf("\n\rInvalid number of nodes N!");
            printf("\n\rTry again with number in range of N=[2; 32767]");
            N = cN_min;
        }
        else if (0 == N)
            return 0;
        else
            break;
    }

    // 1.2. Ask for input ConnectionsNumber (max N-1 and min 1)
    while (cM_min == M)
    {
        printf("\n\rNumber of connections: M = ");
        scanf("%d", &M);

        if ( ( ((M > N*(N-1)/2) || (M < 0))) && (M != 0) )
        {
            printf("\n\rInvalid number of connections M!");
            printf("\n\rTry again with number in range of M=[1; <nodes-1>]");
            M = cM_min;
        }
        else if (0 == M)
            return 0;
        else
            break;
    }

    // 2.1. Inputs are valid, proceed with allocating memory for the graph
    Graph = (unsigned int**)calloc(N*N, sizeof(signed int));
    if (NULL == Graph)
    {
        printf("\n\rNo free memory. Closing!\n\r");
        return 0;
    }

    // 2.2. Describe connections
    printf("\n\rEnter weights for every connection:");
    for (uiCntRow = 0; uiCntRow < N; uiCntRow++)
    {
        for (uiCntCol = 0; uiCntCol < N; uiCntCol++)
        {
            // Escape main diagonal - i.e. connection between vertice and itself - always 0x00
            if (uiCntRow == uiCntCol)
            {
                Graph[uiCntRow][uiCntCol] = cINFINITE;
                continue;
            }
            // Escape already set weights
            if (0 != Graph[uiCntRow][uiCntCol])
                continue;

            siTemp = -1;
            while (siTemp < 0)
            {
                printf("\n\rWeigh for vector '%d' to '%d': ", uiCntRow, uiCntCol);
                scanf("%d", &siTemp);
                if (siTemp < 0)
                {
                    printf("\n\rEnter positive value or '0'!");
                }
                else if (0 == siTemp)
                {
                    // Initialize graph with infinite values, when no connection is made
                    Graph[uiCntRow][uiCntCol] = (unsigned int)cINFINITE;
                }
                else
                {
                    Graph[uiCntRow][uiCntCol] = (unsigned int)siTemp;
                }
            }
        }
    }

    // 3.1. Get the path to calculate length
    while (uiStart < 0)
    {
        printf("\n\rStart point number: ");
        scanf("%d", &uiStart);

        if ( (uiStart < 0) || (uiStart >= (N*N)) )
        printf("\n\rEnter positive and '0' to '%d' start point!", (N*N)-1);
    }

    while (uiEnd < 0)
    {
        printf("\n\rEnd point number: ");
        scanf("%d", &uiEnd);
        if ( (uiEnd < 0) || (uiEnd >= (N*N)) )
        printf("\n\rEnter positive and '0' to '%d' end point!", (N*N)-1);
    }

    // 3.2. Run Dijkstra Algorithm
    siResult = DijkstraAlgo(Graph, (unsigned long)(N*N), uiStart);

    // 3.3. Print the output information
    if (siResult > 0)
        printf("\n\rThe length of path from vertice '%d' to '%d' is %d.", uiStart, uiEnd, siResult);
    else
        printf("\n\rLength is 0.");

    // 4. Application Finish jobs - dynamic memory DEallocation, etc.
    free(Graph);
    return 0;
}


signed int DijkstraAlgo(unsigned int **uiGraph, unsigned long ulSize, unsigned int uiSrc)
{
    unsigned int uiOrder = ulSize/2;
    unsigned int uiCntr, i, j, uimin, uiMinID;
    unsigned int auiDist[uiOrder];
    unsigned char auiChecked[uiOrder];


    // Prepare working data
    for (uiCntr=0; uiCntr < uiOrder; uiCntr++)
    {
        auiDist[uiCntr] = cINFINITE;
        auiChecked[uiCntr] = cFALSE;
    }

    // Mark the initial point
    auiDist[uiCntr] = 0;

    // Start Calculation loop
    for (uiCntr=0, uimin = cINFINITE; uiCntr < uiOrder; uiCntr++)
    {
        // Calc the min distance and pick the next element
        for (i=0; i < uiOrder; i++)
        {
            if ( (auiDist[i] <= uimin) && (cFALSE == auiChecked[i]) )
            {
                uiMinID = i;
                uimin = auiDist[i];
            }
        }

        // Mark the picked item as processed
        auiChecked[uiMinID] = cTRUE;

        // Process adjacent entries
        for (j=0; j < uiOrder; j++)
        {
            // Update of value should be made only in 3 cases:
            // - there is connection between the current node and the observed one
            // - the item has not been processed yet
            // - the total path way is smaller than previously calculated
            if ( (uiGraph[uiMinID][j]) && (cFALSE == auiChecked[uiMinID]) )
            {
                if ( (cINFINITE == auiDist[uiMinID]) ||
                     ((auiDist[uiMinID] + uiGraph[uiMinID][j]) < auiDist[j]) )
                {
                    auiDist[j] = auiDist[uiMinID] + uiGraph[uiMinID][j];
                }
            }
        }
    }

    return auiDist[uiSrc] ? (signed int)auiDist[uiSrc] : -1;
}
