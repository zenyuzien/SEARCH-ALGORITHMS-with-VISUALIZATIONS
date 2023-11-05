
#include <iostream>
#include <fstream>
using namespace std; 

void input_graph()
{ 
    ofstream tmp("graph_data.txt", ios::trunc);
    tmp.close();
    ofstream f("graph_data.txt");
    if(! f.is_open())
    cout<<"nope";
    int n,m, c;
    cout << "enter number of nodes \n" ;
    cin >> n ; 
    f << to_string(n);
    
    for(int i = 0 ; i < n ; i++)
    {
        cout << "enter heuristic value for node "<< i << endl ;
        cin >> c ;
        f << " "<< to_string(c);
    }
       
    while(1)
    {
        cout << "enter 1 for adding an edge, else enter -1 to proceed\n" ;
        cin >> m ;
        if(m == -1)
        break; 
        cout <<"enter node1,node2,cost sperated by spaces to create undirected edge n1<->n2 \n";
        cin >> m >> n >> c ;
        f << " 0 " << to_string(m) << " " << to_string(n) << " " << to_string(c) ;
    }
    f<<" -1";
    f.close();
}

int main()
{
    cout << "Would you like to proceed with same input as earlier? 1 - yes / 0 - no " << endl ;
    short int c ; 
    cin >> c ;
    if( c== 1 )
    return 0 ;
    else if (c != 0)
    {
        cout << "invalid input, exiting the program " << endl ;
        return 0;
    }
    input_graph();
    return 0;
}