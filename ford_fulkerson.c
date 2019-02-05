/*
Maximum Flow (ADU Feb 21)
a WimpyPoint presentation owned by Mark Dettinger

    Maximum Flow in a Network
    The Ford-Fulkerson Algorithm in C 

Maximum Flow in a Network
Given a directed graph with a source and a sink and capacities assigned to the edges, determine the maximum flow from the source to the sink.

    For each edge, the flow must not exceed the edge's capacity.
    For each node, the incoming flow must be equal to the outgoing flow. 

The Ford-Fulkerson Algorithm in C
*/
#include <stdio.h>

//Basic Definitions

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX_NODES 1000
#define oo 1000000000

//Declarations

int n;  // number of nodes //noeuds
int e;  // number of edges // bords
int capacity[MAX_NODES][MAX_NODES]; // capacity matrix
int flow[MAX_NODES][MAX_NODES];     // flow matrix
int color[MAX_NODES]; // needed for breadth-first search               
int pred[MAX_NODES];  // array to store augmenting path

int min (int x, int y) 
{
    return (x < y ? x : y);  // returns minimum of x and y
}

//A Queue for Breadth-First Search

int head,tail;
int q[MAX_NODES+2];

void enqueue (int x)
{
    q[tail] = x;
    tail++;
    color[x] = GRAY;
}

int dequeue (void)
{
    int x = q[head];
    head++;
    color[x] = BLACK;
    return x;
}

//Breadth-First Search for an augmenting path

int bfs (int start, int target)
{
    int u,v;
    u = 0;
    //for (u=0; u<n; u++)
    while (u++ < n)
    {
	   color[u] = WHITE;
    }   
    head = 0;
    tail = 0;
    enqueue(start);
    pred[start] = -1;
    while (head!=tail)
    {
	u = dequeue();
    v = 0;
        // Search all adjacent white nodes v. If the capacity
        // from u to v in the residual network is positive,
        // enqueue v.
	//for (v=0; v<n; v++)
        while (v++ < n)
        {
    	    if (color[v]==WHITE && capacity[u][v]-flow[u][v]>0)
            {
    		  enqueue(v);
    		  pred[v] = u;
    	    }
    	}
    }
    // If the color of the target node is black now,
    // it means that we reached it.
    return color[target]==BLACK;
}

//Ford-Fulkerson Algorithm

int max_flow (int source, int sink) {
    int i;
    int j;
    int u;
    // Initialize empty flow.
    int max_flow;
    max_flow = 0;
    i = 0;
    //for (i=0; i<n; i++)
    while (i++ < n)
    {
        j = 0;
    	//for (j=0; j<n; j++)
        while (j++ < n)
        {
    	    flow[i][j] = 0;
    	}
    }
    // While there exists an augmenting path,
    // increment the flow along this path.
    while (bfs(source,sink)) 
    {
            // Determine the amount by which we can increment the flow.
    	int increment = oo;
    	u = n - 1;
        //for (u=n-1; pred[u]>=0; u=pred[u])
        while (pred[u] >= 0)
        {
            u = pred[u];
    	    increment = min(increment,capacity[pred[u]][u]-flow[pred[u]][u]);
    	}
            // Now increment the flow.
    	//for (u=n-1; pred[u]>=0; u=pred[u])
        u = n - 1;
        while (pred[u] >= 0)
        {
            u=pred[u];
    	    flow[pred[u]][u] += increment;
    	    flow[u][pred[u]] -= increment;
    	}
    	max_flow += increment;
    }
    // No augmenting path anymore. We are done.
    return (max_flow);
}

//Reading the input file and the main program

void read_input_file(void)
{
    int a,b,c,i,j;
    FILE* input = fopen("mf.in","r");
    // read number of nodes and edges
    fscanf(input,"%d %d",&n,&e);
    // initialize empty capacity matrix 
    i  = 0;
    //for (i=0; i<n; i++)
    while (i++ < n)
    {
	   j = 0;
       while (j++ < n)
       //for (j=0; j<n; j++)
       {
	       capacity[i][j] = 0;
	   }
    }
    // read edge capacities
    i = 0;
    //for (i=0; i<e; i++)
    while (i++ < e)
    {
	   fscanf(input,"%d %d %d",&a,&b,&c);
	   capacity[a][b] = c;
    }
    fclose(input);
}

int main (void)
{
    read_input_file(void);
    printf("%d\n",max_flow(0,n-1));
    return 0;
}
/*
The Input File

6 10    // 6 nodes, 10 edges
0 1 16  // capacity from 0 to 1 is 16
0 2 13  // capacity from 0 to 2 is 13
1 2 10  // capacity from 1 to 2 is 10
2 1 4   // capacity from 2 to 1 is 4
3 2 9   // capacity from 3 to 2 is 9
1 3 12  // capacity from 1 to 3 is 12
2 4 14  // capacity from 2 to 4 is 14
4 3 7   // capacity from 4 to 3 is 7
3 5 20  // capacity from 3 to 5 is 20
4 5 4   // capacity from 4 to 5 is 4

Output of the Program
The program computes the maximum flow from 0 to 5.

23

    
    
    
    

Last modified 2001-02-21
mdettinger@arsdigita.com 	
*/