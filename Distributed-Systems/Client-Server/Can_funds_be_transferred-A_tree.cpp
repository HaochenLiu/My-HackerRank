/*
Use this function to write data to socket
void write_string_to_socket(int sock_descriptor, char* message, uint32_t length);

Use this function to read data from socket
void read_string_from_socket(int sock_descriptor, char** message, uint32_t *length);
*/

// All global declarations go here
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

class Tree;
class TreeNode;

class Tree {
public:
    unordered_map<int, TreeNode*> m;
    TreeNode* root;
    Tree();
    Tree(int v);
    void insert(int p, int n);
    stack<int> pathToRoot(int p);
    int getPathLen(int n1, int n2);
};

class TreeNode {
public:
    int val;
    TreeNode* parent;
    vector<TreeNode*> child;
    TreeNode(int v);
};

Tree::Tree() {
    root = NULL;
}

Tree::Tree(int v) {
    root = new TreeNode(v);
    m[v] = root;
}

void Tree::insert(int p, int n) {
    TreeNode* pnode;
    TreeNode* nnode;
    if(m.find(p) == m.end()) {
        pnode = new TreeNode(p);
        m[p] = pnode;
    } else {
        pnode = m[p];
    }

    if(m.find(n) == m.end()) {
        nnode = new TreeNode(n);
        m[n] = nnode;
    } else {
        nnode = m[n];
    }
    
    pnode->child.push_back(nnode);
    nnode->parent = pnode;
}

stack<int> Tree::pathToRoot(int p) {
    TreeNode* node = m[p];
    stack<int> res;
    while(node) {
        res.push(node->val);
        node = node->parent;
    }
    return res;
}

int Tree::getPathLen(int n1, int n2) {
    stack<int> path1 = pathToRoot(n1);
    stack<int> path2 = pathToRoot(n2);
    while(true) {
        if(path1.empty() || path2.empty()) {
            break;
        }
        if(path1.top() == path2.top()) {
            path1.pop();
            path2.pop();
        } else {
            break;
        }
    }
    return path1.size() + path2.size() + 1;
}

TreeNode::TreeNode(int v) {
    val = v;
    parent = NULL;
}

Tree t;

/*
This function is called only once before any client connection is accepted by the server.
Read any global datasets or configurations here
*/

vector<int> split(string& str) {
    vector<int> res;
    if(str.empty()) return res;
    int beg = 0;
    int end = 0;
    int n = str.size();
    while(end < n) {
        if(str[end] != ',') {
            end++;
        } else {
            res.push_back(stoi(str.substr(beg, end - beg)));
            beg = end + 1;
            end = beg;
        }
    }
    res.push_back(stoi(str.substr(beg, end - beg + 1)));
    return res;
}

bool canTransfer(string message) {
    vector<int> node = split(message);
    return t.getPathLen(node[0], node[1]) <= node[2];
}

void init_server() {
    printf("Reading configuration\n");
    string line;
    ifstream myfile("training.txt");
    if(myfile.is_open()) {
        getline(myfile, line);
        int N = stoi(line);
        while(getline(myfile, line)) {
            vector<int> node = split(line);
            t.insert(node[0], node[1]);
        }
        myfile.close();
    }
    fflush(stdout);
}
    
/*
Write your code here
This function is called everytime a new connection is accepted by the server
*/
void * process_client_connection(void* ptr) {
    connection_t* conn;

    if(!ptr) pthread_exit(0); 
    conn = (connection_t*)ptr;

    printf("Connection received\n");
    fflush(stdout);

    int terminate_client = 0;
    do {
        /* read length of message */
        char* message = NULL;
        uint32_t message_length = 0;

        /* read message */
        read_string_from_socket(conn->sock, &message, &message_length);

        printf("Received = %s\n", message);
        string s = string(message);

        /* End of operation on this clinet */
        if(strcmp(message, "END") == 0) {
            terminate_client = 1;
        } else {
            /* write message */        
            if(canTransfer(s)) {
                char* YES = "YES";
                write_string_to_socket(conn->sock, YES, strlen(YES));
            } else {
                char* NO = "NO";
                write_string_to_socket(conn->sock, NO, strlen(NO));
            }
        }
        
        free(message);
    } while(!terminate_client);

    /* close socket and clean up */
    printf("Closing client on socket %d\n", conn->sock);
    fflush(stdout);
    close(conn->sock);
    free(conn);
    pthread_exit(0);
}
