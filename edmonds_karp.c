#include<cstdio>
#include<cstdio>
#include<queue>
#include<cstring>
#include<vector>
#include<iostream>
#include<conio.h>

/*
algorithm EdmondsKarp in pseudo code
    input:
        graph   (graph[v] should be the list of edges coming out of vertex v in the
                 original graph and their corresponding constructed reverse edges
                 which are used for push-back flow.
                 Each edge should have a capacity, flow, source and sink as parameters,
                 as well as a pointer to the reverse edge.)
        s       (Source vertex)
        t       (Sink vertex)
    output:
        flow    (Value of maximum flow)
    
    flow := 0   (Initialize flow to zero)
    repeat
        (Run a bfs to find the shortest s-t path.
         We use 'pred' to store the edge taken to get to each vertex,
         so we can recover the path afterwards)
        q := queue()
        q.push(s)
        pred := array(graph.length)
        while not empty(q)
            cur := q.pull()
            for Edge e in graph[cur]
                 if pred[e.t] = null and e.t ≠ s and e.cap > e.flow
                    pred[e.t] := e
                    q.push(e.t)
    
        if not (pred[t] = null)         
            (We found an augmenting path.
             See how much flow we can send) 
            df := ∞
            for (e := pred[t]; e ≠ null; e := pred[e.s])
                df := min(df, e.cap - e.flow)
            (And update edges by that amount)
            for (e := pred[t]; e ≠ null; e := pred[e.s])
                e.flow  := e.flow + df
                e.rev.flow := e.rev.flow - df
            flow := flow + df
    
    until pred[t] = null  (i.e., until no augmenting path was found)
    return flow
*/

using namespace std;
int capacities[10][10];

int flowPassed[10][10];

vector<int> graph[10];

int parentsList[10];       

int currentPathCapacity[10];  

 

int bfs(int startNode, int endNode)

{

    memset(parentsList, -1, sizeof(parentsList));
    memset(currentPathCapacity, 0, sizeof(currentPathCapacity));

    queue<int> q;
    q.push(startNode); // Inserts a new element at the top of the stack, above its current top element. The content of this new element is initialized to a copy of val.
    parentsList[startNode] = -2;
    currentPathCapacity[startNode] = 999;
    while(!q.empty()) // true if the container size is 0, false otherwise.
    {
        int currentNode = q.front(); // Returns a reference to the first element in the container. 
        q.pop(); // Removes an element from the front of the queue. 
        for(int i=0; i<graph[currentNode].size(); i++)
        {
            int to = graph[currentNode][i];
            if(parentsList[to] == -1)
            {
                if(capacities[currentNode][to] - flowPassed[currentNode][to] > 0)
                {
                    parentsList[to] = currentNode;
                    currentPathCapacity[to] = min(currentPathCapacity[currentNode], // Returns the smallest of the values in initializer list ilist.
                    capacities[currentNode][to] - flowPassed[currentNode][to]);
                    if(to == endNode)
                    {
                        return currentPathCapacity[endNode];
                    }
                    q.push(to); // Inserts a new element at the top of the stack, above its current top element. The content of this new element is initialized to a copy of val.
                }
            }
        }
    }
    return 0;
}

int edmondsKarp(int startNode, int endNode)
{
    int maxFlow = 0;
      while(true)
    {
        int flow = bfs(startNode, endNode);
        if (flow == 0) 
        {
            break;
        }
        maxFlow += flow;
        int currentNode = endNode;
        while(currentNode != startNode)
        {
            int previousNode = parentsList[currentNode];
            flowPassed[previousNode][currentNode] += flow;
            flowPassed[currentNode][previousNode] -= flow;
            currentNode = previousNode;
        }
    }
    return maxFlow;
}

int main()
{
    int nodesCount, edgesCount;
    cout<<"enter the number of nodes and edges\n";
    cin>>nodesCount>>edgesCount;
    int source, sink;
    cout<<"enter the source and sink\n";
    cin>>source>>sink;
    for(int edge = 0; edge < edgesCount; edge++)
    {
        cout<<"enter the start and end vertex alongwith capacity\n";
        int from, to, capacity;
        cin>>from>>to>>capacity;
        capacities[from][to] = capacity;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }
    int maxFlow = edmondsKarp(source, sink);
    cout<<endl<<endl<<"Max Flow is:"<<maxFlow<<endl;
    getch();
}
