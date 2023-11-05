#ifndef BMS_
#define BMS_


void BMS_util( struct graph& g, int cnode, int goal, vector<bool> visit, struct node* path, ofstream& f )
{
    visit[cnode]=true;
    f << to_string(cnode)<< " ";
    struct node* newnode = new node();
    newnode->next= path ;
    newnode->val = cnode;
    path = newnode;
    
    bool at1 = false ;
    for(int i = 0 ; i < g.n; i++)
    {
        if( i != cnode && g.arr[cnode][i] && visit[i]==false)
        {
            if(i==goal)
            {
                struct node* newnode = new node();
                newnode->next= path ;
                newnode->val = goal;
                path = newnode;
                f << to_string(goal)<< " ";
                print_path(path, 0);
            }
            
            else
            {
                at1=true;
                BMS_util(g,i,goal,visit,path,f);
            }
        }
    }
    
    if(at1== false)
    print_path(path, 0);
}

void BMS(struct graph & g, int s, int G, ofstream& f)
{
    vector<bool> visit(g.n);
    struct node* path =NULL ;
    BMS_util(g,s,G,visit,path,f );
    f <<endl<< endl<< to_string(s) << " " << to_string(G);
}

#endif 