#include "WGraph.h"
#include "queue.h"

/*
Overall O(n^2*m)
In analysis, the worst case measured for all the function T(n) = O(n^2*m)+T(n-1)+O(n^2)+O(n)+O(nE)+O(n^2)+c
= O(n^2*m)+2*O(n^2)+O(n^2)*2*O(n)
as O(n^2*m) is the worst time complexity, so others will be discarded. 
The worst case running time will be O(n^2*m) in this program.
*/

/*  O(1) since there are some the linear functions,*/
void insert_into_edges(Graph graph, int i, int j) { 
    Edge* edge = malloc(sizeof(Edge));
    edge->v = i;
    edge->w = j;
    edge->weight = 1;
    insertEdge(graph, *edge);
}

/*
These nested loop, the worst case for first loop traverses as i = 0,1,2...n-1,
as n measured as #word, so it cost n + c in brief and c is constant value.
The second loop begins from i+1, so it traverse as 1,2,3...n, it cost (n-1)/2 + c
In total, the cost will be n*(n-1)/2 + c which is O(n^2)
After that, there is inner while loop cost m since it begins from sub_len = 0,1,2...m in 
the worst case, as m measured the length of word.
In conclusion, The worst case is O(n^2*m)
*/

void search_words_to_edges(Graph graph, char words[][MAX_LETTER], int total_len) {
    //1, find two consecutive word 2, then insert into the edge 
    char *str, *sub_str, *buf_str;
    int sub_len, kind, len_str, len_cmped_str;
    bool flag, one_diff; 
    for (int i = 0; i < total_len; i++) {
        str = words[i]; //string for previous word compared to other
        for (int j = i+1; j < total_len; j++) {
            flag = false; //if true, then it is consecutive.
            sub_str = words[j]; //substring which is compared
            len_str = strlen(words[i]);
            len_cmped_str = strlen(words[j]);
            kind = len_str - len_cmped_str;

            //kind for length: 1: (str > sub_str), 0: (str = sub_str), -1-> (str < sub_str)
            if (kind == 1 || kind == -1 || kind == 0) {                   
                buf_str = str;
                sub_len = 0;

                //two consecutive words allow only one difference
                one_diff = false; 
                    
                //this loop shift the pointer to compare sting and substring with one word diff
                while (sub_len < strlen(words[j])) {
                    if (*buf_str == *sub_str) {
                        buf_str++; sub_str++;
                    }
                    else if (!one_diff) {
                        one_diff = true;
                        if (kind == -1) {
                            sub_str++; //compared word is one letter longer
                        }
                        else if (kind == 0) {
                            buf_str++; sub_str++; //two same letter word, and both shift one
                        }
                        else {
                            buf_str++; //the word compared others is one letter longer
                        }   
                    }
                    else {
                        sub_len = -1; //if more than one diff, set an fault value and exit
                        break;
                    }
                    sub_len++;
                }
                if (sub_len == len_cmped_str) {
                    flag = true;
                }     
            }
            if (flag) {
                insert_into_edges(graph, i, j); 
            }
        }
    }
}

/*
This func will be called recursively as it traversal the pred with pred and its length is O(n)
as T(n) = T(n-1) + c */
void analysePath(int v, int pred[], int* count) {

    //Recursion and apply the predition array and count it length number
    if (pred[v] != -1) {
        *count+=1;
        analysePath(pred[v], pred, count);
    }
}

/*
This func has loop from i = 0,1...n-1 so it will traverse n in worst case
but it also call the recursion each time so T(n) = n*T(n-1)+c -> O(n^2)
Return the maximum number in path and store each number of length into the arr[]
*/
int max_seq(int arr[], int pred[], int V) {
    int max = -1;
    for (int i = 0; i < V; i++) {
        int count = 0;
        analysePath(i, pred, &count);
        if (max < count)
            max = count;
        arr[i] = count;
    }
    return max;
}

/* 
This func is recursion as before so it is T(n-1) = O(n)
*/
void showPath(int v, int pred[], char words[][MAX_LETTER]) {
    if (pred[v] == -1) {
        printf("%s", words[v]);
    } 
    else {
        showPath(pred[v], pred, words);
        printf(" -> %s", words[v]);
    }
}

/*
Bellman_Ford Algorithm is O(VE) but now we measure Big-O in terms of m,n
so V is the #word which is n and #edge increase depends on new vertex insert in graph so it will 
also be n, then T(n) = O(n^2)+c
*/
void find_the_longest_path (Graph graph, int pred[MAX_WORDS], int V) {

    //Apply Bellman_Ford Algorithm to find the longest path
    int dist[MAX_WORDS];  
    int E = graph->nE;
    int src = 0;
    
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[src] = 0;
    for (int i = 1; i <= V-1; i++) {
        for (int j = 0; j < E; j++) {   
            int u = graph->edge_info[j].v; //source
            int v = graph->edge_info[j].w; //destination
            int weight = (graph->edge_info[j].weight*-1);
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u; //store each distance from the previous vertex in matrix
            }
        }
    }
}

/*
The worst case of main() contains 4 loops in parallel measured the #word 
one for freeGraph and last while loop measured the length of queue which is linear cost O(1)
showGraph cost O(n^2) since two for loop to traverse and display which is V also n, 
then T(n) = O(n^2)+3*O(n)+2*O(1)+c and we discard the term less than O(n^2)
Then worst case of main() is basic O(n^2)
*/

int main() {
    char words[MAX_WORDS][MAX_LETTER]; //store one word in a line
    int pred[MAX_WORDS], path_len_arr[MAX_WORDS]; //prediction array is to store the longest path in index
    int input, V, max_seq_length;
    Graph graph;
    queue q = newQueue();
    
    printf("Enter a number: ");
    if (!scanf("%d", &input)) {
        return -1;
    }
    graph = newGraph(input);
    V = graph->nV;

    for (int i = 0; i < V; i++) {
        printf("Enter a word: ");
        scanf("%s", words[i]);
    }

    //This function is to distingush two conecutive words and put them into Graph
    search_words_to_edges(graph, words, V);

    //Apply Bellman_Ford Algorithm to find the longest path
    find_the_longest_path(graph, pred, V);
    
    //Show the basic adjacent path of each vertex in graph
    showGraph(graph, words);

    //Insert each length of path begining from i vertex into parameter path_len_arr[] 
    max_seq_length = max_seq(path_len_arr, pred, V);

    printf("Maximum sequence length: %d\n", max_seq_length+1);
    printf("Maximal sequence(s):\n");
    
    for (int i = 0; i < V; i++) {
        if (path_len_arr[i] == max_seq_length) {
            //Enqueue the index of each word corresponding with the max sequence length in acsending order
            QueueEnqueue(q,i);    
        }
    }

    //since the input is alpheatical, then acsending order queue will dequeue the alpheatical order
    while (!QueueIsEmpty(q)) {
        showPath(QueueDequeue(q), pred, words);  
        printf("\n");
    }

    freeGraph(graph);
    return 0;
}