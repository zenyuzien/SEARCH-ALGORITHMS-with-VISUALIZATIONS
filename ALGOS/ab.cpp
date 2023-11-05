
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

/*

I would make the user make the entire tree heterogeneous.
For smooth input purpose, every node will have value and depth, so user can insert nodes based on (value, depth)
If user enters 2 nodes with same values on same depth, children input will be asked from left to right
minimaxFrom(struct node* , bool isMax ) would return the optimal value from any given node address

*/

struct node 
{
    int val ;
    int depth ;
    struct node* next;
    vector< struct node* > v; 
};

void buildedges(int& cnt, struct node* n, ofstream& f)
{
    for(auto i : n->v)
    {
        f << endl << to_string(n->val) << " "<<to_string(i->val) ;
        cnt++;
    }
    
    for(auto i : n->v)
    buildedges(cnt,i,f);
    
}

void display(struct node* r)
{
    cout<<"node val: " << r->val << " node depth: " << r->depth << " children: " << endl;
    for(auto i : r->v)
    cout << i->val << ", " << i->depth << endl ; 
    for(auto i : r->v)
    display(i);
}

void fillchildren( struct node * from , int depth, vector<int>& v)
{
    int tmp,tmp2;
    cout << "enter how many children nodes for the node " << from->val << " of depth " << from->depth<<" " ;
    cin>>tmp;
    
    for(int i = 1 ; i <= tmp ; i++)
    {
        cout<<"enter value for child no. " << i << " of node " << from->val << " of depth " << from->depth <<" ";
        cin>>tmp2;
        
        struct node * tmpnode= new node ; 
        tmpnode->val = tmp2; 
        tmpnode->depth = depth +1 ;
        tmpnode->next= NULL;
        v.push_back(tmpnode->val);
        from->v.push_back(tmpnode);
    }
    
    for(auto i : from->v)
    fillchildren(i,depth+1,v);
    
}

void init_graph( vector<int>&v, struct node * root )
{
    cout<<"enter value of root node: ";
    cin>>root->val ; 
    root->depth = 0 ;
    v.push_back(root->val);
    fillchildren(root,0,v);
}

pair<int, struct node*> minimaxFrom( struct node * r , bool isMax, int  alpha , int  beta, ofstream& f)
{
    f << to_string(r->val)<<" ";
    if(r->v.size() == 0)
    return {r->val,r} ;
    
    pair<int, struct node*> tmp,  min = {INT_MAX,NULL} , max = {INT_MIN,NULL} ;
    

    if(isMax)
    {
        for(auto i : r->v)
        {
            tmp = minimaxFrom(i , false, alpha, beta, f) ;
            max = max.first > tmp.first ? max : tmp ;
            alpha = alpha > max.first ? alpha : max.first; 
            if (beta <= alpha) 
            break;
        }
        
        r->next= max.second;
        return {max.first, r};
    }
    
    else
    for(auto i : r->v)
    {
        tmp = minimaxFrom(i , true, alpha , beta, f) ;
        min = min.first < tmp.first ? min : tmp ;
        beta = beta < min.first ? beta : min.first ;
        if(beta <= alpha)
        break;
    }
    
    r->next= min.second;
    return { min.first, r};
}

void display_path(struct node* p, ofstream&f)
{
    f <<endl; 
    while(p)
    {
        cout << p->val << " ";
        f << to_string(p->val) << " ";
        p=p->next;
    }cout << endl ;
}

int main()
{
    struct node* root = new node ;
    vector<int> v ;
    ofstream tmp("vis_data.txt",ios::trunc);
    tmp.close();
    ofstream f("vis_data.txt");
    init_graph(v, root);
    display(root);
    int rv= root->val; 
    int num = 0 ;
    for(auto i : v)
    f << to_string(i)<<" ";    
    buildedges(num,root,f);

    int alpha = INT_MIN, beta = INT_MAX ;
    f<<endl << "-1"<< endl << "-2" << endl;
    
    auto x=  minimaxFrom(root,true, alpha, beta ,f);
    
    // answer-> x.first, display x.second
    cout << "ans: " << x.first << endl ;
    display_path(x.second,f);
    f<<endl<< to_string(rv) <<" "<< to_string(x.first);
    f.close();
    
    return 0;
}
