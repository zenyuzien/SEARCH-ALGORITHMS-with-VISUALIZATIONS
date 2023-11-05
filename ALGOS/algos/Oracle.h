#ifndef O_
#define O_


void oracle_util(struct graph &g ,
vector<bool> visit,
int CC,
int cnode,int goal,
struct node* path,
int& maxora, struct qnode& Q, ofstream& f)
{
    

    if(visit[cnode]==true)
    return;

    f<< to_string(cnode) << " ";
    visit[cnode] = true;
    
    struct node* newnode = new node();
    newnode->next= path ;
    newnode->val = cnode;
    path = newnode; 
    
    for (int i = 0; i < g.n; i++)
    {
        if ( g.arr[cnode][i]!=I && g.arr[cnode][i]!=0 && i==goal)
        {
            newnode = new node();
            newnode->next= path ;
            newnode->val = goal;
            path = newnode; 
            
            f<< to_string(goal) << " ";
            print_path(path, CC+ g.arr[cnode][goal]);
            
            if( maxora==0 || CC + g.arr[cnode][goal] < maxora )
            {
                gpath = path ;
                maxora = CC + g.arr[cnode][goal] ;
                continue;
            }
        }

        if ( g.arr[cnode][i]!=I && g.arr[cnode][i]!=0 && visit[i]==0  )
        {
           //// if( maxora==0 || (CC + g.arr[cnode][i] < maxora) )
            ////{
                Q.q.push( { {CC + g.arr[cnode][i] , i},{path,visit}  }); 
               // printf("pushed %d with %d \n",i,CC + g.arr[cnode][i]);
          // // }
            
        }
            
    }
    
    while (!Q.q.empty())
    {
        //printf("tmp->top %d, %d \n", Q.q.top().second.first, q.top().first);
        auto x = Q.q.top();
        Q.q.pop();
       // if(visit[x.second.first]==false)
       // //if(maxora ==0 || x.first.first < maxora )
        oracle_util(g, x.second.second, x.first.first, x.first.second, goal, x.second.first, maxora , Q, f);
       // else
       // cout<< "oracle excee\n";
    }
}

void oracle(struct graph & g, int st, int gl, ofstream& f)
{
    vector <bool> visit(g.n);
    struct node* path = NULL;
    struct qnode Q ;
    int maxora = 0 ;
    oracle_util( g , visit, 0 , st , gl , path,  maxora, Q, f );
    if(gpath && printf("best path: "))
    display_path(gpath,f);
    
    f << endl << to_string(st) << " " << to_string(gl) ; 
}


#endif