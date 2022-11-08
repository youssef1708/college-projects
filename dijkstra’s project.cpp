//youssef yasser abo el-naga




#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Node
{
    char label;
    int cost;
};


class heapify(int arr[],int s, int i)
{

    int M=2*i+1;
    int r=2*i+2;
    int min=i;
    if(arr[M]<arr[min])
        {
            min = M;
        }
    if(arr[r]<arr[min])
        {
            min = r;
        }
    if(min != i)
        {
            swap(arr[i],arr[min]);
            heapify(arr,n,min)

        }

}
buildHeap(int arr[],int n)
{
    for (int i = n/2-1; i >=0 ; i--)
    {
        heapify(arr,n,i);

    }
}


class MinHeap
{
    Node* heap; //an array of nodes
    int _size; //size of array
public:
    Node extractMin(); //returns & removes the node with minimum cost
    void buildMinHeap(Node[],int);// allocates array then builds a min-heap from an array of struct Node with the given size
    void minHeapify(int i, int n);//restores the min-heap property for the “heap”array using the given index and size n
    void decreaseKey(char label,int newCost);//decreases the node that has the givenlabel to newCost
    int parent(int i);//returns the index of the parent of i
    int getSize();//returns size of the heap
    bool inHeap(char);//checks if the node with the given label is in the heap
};


class WeightedGraph {
    int **g;
    int nVertices;
public:
    int getNVertices();//returns the number of vertices
    int getWeight(char, char);//returns weight of the edge connecting the given vertices
    int *returnNeighbors(int v);// returns the indices of the neighbors of the vertex v as an int array
    int numNeighbors(int v);//returns the number of neighbors of the vertex v
    void
    loadGraphFromFile(ifstream &);//allocates the adjacency matrix & initializes edge weights from the specified file
    void dijkstra(char startVertex, char *prev,
                  Node distances[]);//find the shortest path from the start vertex to all other vertices, by filling the prev array and the distances array
};

int main()
{
    WeightedGraph wg;
    ifstream ifile("graph.txt");
    wg.loadGraphFromFile(ifile);
    char* p;
    p = new char[wg.getNVertices()];
    Node* n;
    n=new Node[wg.getNVertices()];
    wg.dijkstra('g',p,n);
    cout<<endl<<"Node\tCost\tPrevious";
    for(int i=0;i<wg.getNVertices();i++)
    {
        cout<<endl<<n[i].label<<"\t"<<n[i].cost<<"\t"<<p[i];
    }
    ifile.close();
    return 0;

}
