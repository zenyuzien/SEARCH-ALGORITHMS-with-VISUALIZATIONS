#ifndef HDC
#define HDC

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <queue>
#include <stack>
#include <ctime>
const double BILLION = 1000000000.0;
#define I 9999
using namespace std;
struct timespec time_start, time_end;

struct graph 
{
    int n ;
    vector< vector<int> > arr ; 
    vector< int > heur ;  
};

struct node 
{
    int val; 
    struct node* next; 
};

// for 2 ORACLES, 4 BBS
struct node* gpath ;

// BB_H OR_H
struct qnode_h
{
    priority_queue<
        pair<
            pair<
                int, // cc +h
                int // cc 
            >,
            
            pair <
                int, // node i
                pair <
                    struct node*, // path
                    vector<bool> // visit
                >
            >
        >,
        vector<pair<
            pair<
                int, // cc + h
                int // cc 
            >,
            
            pair <
                int, // node i
                pair <
                    struct node*, // path
                    vector<bool> // visit
                >
            >
        >>,
        greater<pair<
            pair<
                int, // cc +h 
                int // cc 
            >,
            
            pair <
                int, // node i
                pair <
                    struct node*, // path
                    vector<bool> // visit
                >
            >
        >>
    > q;
};

// BB, HC, BS, OR 
struct qnode
{
    priority_queue<
        pair<
            pair<
                int, // cc
                int // node i
            >,
            pair<
                struct node*, // path
                vector<bool> // visit
            >
        >
        ,
        vector<pair<
            pair<
                int, // cc
                int // node i
            >,
            pair<
                struct node*, // path
                vector<bool> // visit
            >
        >>,
        greater<pair<
            pair<
                int, // cc
                int // node i
            >,
            pair<
                struct node*, // path
                vector<bool> // visit
            >
        >>
    > q;
};

// A*
struct qnode_nelh 
{
    priority_queue<
        pair<
            pair<
                int, // cc +h
                int // cc 
            >,
            
            pair <
                int, // node i
                struct node* // path
            >
        >,
        vector<pair<
            pair<
                int, // cc + h
                int // cc 
            >,
            
            pair <
                int, // node i
                struct node* // path
            >
        >>,
        greater<pair<
            pair<
                int, // cc +h 
                int // cc 
            >,
            
            pair <
                int, // node i
                struct node* // path
            >
        >>
    > q;
};

// BB_EL BESTFS
struct qnode_nel
{
    priority_queue<
        pair<
            pair<
                int, // cc
                int // node i
            >,
            struct node* // path
        >
        ,
        vector<pair<
            pair<
                int, // cc
                int // node i
            >,
            struct node* // path
        >>,
        greater<pair<
            pair<
                int, // cc
                int // node i
            >,
            struct node* // path
        >>
    > q;
};

struct node_ao {
    int id;
    int g;
    int f;
    bool operator>(const node_ao& other) const {
        return f > other.f;
    }
};

void display_path( struct node* path , ofstream& f)
{
    f<<endl;
    while(path)
    {
        cout<< path->val <<" <- ";
        f<<path->val<<" ";
        path=path->next;
    }
    cout<<endl;
}

void print_path( struct node* path, int cost )
{
    if(cost)
    cout << "cost: " << cost << " ";
    while(path)
    {
        cout<< path->val <<" <- ";
        path=path->next;
    }
    cout<<endl;
}



#endif 