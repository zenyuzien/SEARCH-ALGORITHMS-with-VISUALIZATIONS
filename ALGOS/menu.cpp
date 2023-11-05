#include "algos.h" 

void parse_graph( struct graph & g , ofstream& f)
{ 
    vector<int> inp_v ;
    ifstream inpLine("graph_data.txt");
    if (!inpLine) {
        cerr << "Error: Unable to open the file." << endl;
        return ;
    }
    string line;
    if(getline(inpLine, line))
    {
        istringstream iss(line); // split into integers
        int num; 
        while(iss >> num)
        inp_v.push_back(num);
    }
    inpLine.close();
    //for(auto j : inp_v)
    //cout << j << " ";
    //cout << endl ;
    int x = 0 ;

    g.n = inp_v[x++] ; 
    f << to_string(g.n);
    g.arr.resize(g.n);
    for(int i = 0 ; i < g.n ; i++)
    g.arr[i].resize(g.n);
    for(int i = 0 ; i < g.n ; i++)
    g.arr[i][i] = I ;
    
    g.heur.resize(g.n);
    
    for(int i = 0 ; i < g.n ; i++)
    g.heur[i] = inp_v[x++] ;
    
    int m,n,c ;
    while(1)
    {
        
        //cout << "xm = inp_v[" << x << "] = " << inp_v[x]<< endl ;
        m = inp_v[x++];
        
        if(m == -1)
        break; 
        //cout << "m = inp_v[" << x << "] = " << inp_v[x]<< endl ;
        m = inp_v[x++];
        //cout << "n = inp_v[" << x<< "] = " << inp_v[x]<< endl ;
        n = inp_v[x++];
        //cout << "c = inp_v[" << x<< "] = " << inp_v[x]<< endl ;
        c = inp_v[x++];
        f << endl <<to_string(m) << " "<< to_string(n) ;
        g.arr[n][m] = c;
        g.arr[m][n] = c ;
    }
    f<< endl<<"-1"<<endl;
}

int main()
{
    struct graph g; 
    ofstream trunc("vis_data.txt", ios::trunc);
    trunc.close();
    ofstream f("vis_data.txt");
    parse_graph(g,f);
    
    cout << "enter number for corresponding algorithm \n" << endl ;
    cout << "1 - British Museum Search" << endl ;
    cout << "2 - Bredth First Search" << endl ;
    cout << "3 - Depth First Search" << endl ;
    cout << "4 - Hill climbing Search" << endl ;
    cout << "5 - Beam Search" << endl ;
    cout << "6 - Oracle Search" << endl ;
    cout << "7 - Oracle with Heuristics Search" << endl ;
    cout << "8 - Branch and Bound Search" << endl ;
    cout << "9 - Branch and Bound with Heuristics Search" << endl ;
    cout << "10 - Branch and Bound with Extended List Search" << endl ;
    cout << "11 - A* Search" << endl ;
    cout << "12 - Best First Search" << endl ;
    cout << "13 - AO* Search" << endl ;
    int n ; 
    //fflush(stdin);
    cin >> n ; 
    if( n < 1 || n > 13)
    {
        cout << "wrong input, terminating program \n" ;
        return 0;
    }
    int S,G; 
    cout << "enter start node, goal node sperated by spaces  " << endl;
    cin >> S >> G; 
    if(n != 1)
    f << to_string(1)<< endl;
    clock_gettime(CLOCK_REALTIME, &time_start);
    switch(n)
    {
        case 1 : 
        f << to_string(0)<< endl;
        BMS(g,S,G,f);
        break; 

        case 2:
        BFS(g,S,G,f);
        break; 

        case 3 : 
        DFS(g,S,G,f);
        break; 

        case 4:
        HC(g,S,G,f);
        break;  

        case 5 : 
        BS(g,S,G,f);
        break; 

        case 6:
        oracle(g,S,G,f);
        break; 

        case 7 : 
        oracle_H(g,S,G,f);
        break; 

        case 8:
        BB(g,S,G,f); 
        break; 

        case 9 : 
        BB_H(g,S,G,f); 
        break; 

        case 10:
        BB_EL(g,S,G,f); 
        break; 

        case 11 : 
        Astar(g,S,G,f);
        break; 

        case 12:
        BESTFS(g,S,G,f);
        break; 

        case 13 : 
        AO_star(g,S,G,f);
        break; 

        default:
        break;
    }
    clock_gettime(CLOCK_REALTIME, &time_end);
    double time_spent = (time_end.tv_sec - time_start.tv_sec) + (time_end.tv_nsec - time_start.tv_nsec) / BILLION;

    std::cout << "The elapsed time is " << time_spent << " seconds" << std::endl;
    f.close();
    return 0; 
}
