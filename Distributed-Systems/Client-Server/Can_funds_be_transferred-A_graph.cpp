/*
graph data structure
*/

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
#include <queue>

int N;
vector<vector<int>> tree;

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
    vector<int> val = split(message);
    queue<int> q;
    unordered_map<int, int> m;    
    q.push(val[0]);
    m[val[0]] = 1;
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        int dist = m[node];
        int n = tree[node].size();
        for(int i = 0; i < n; i++) {
            if(tree[node][i] == val[1]) {
                return (dist + 1 <= val[2]);
            }
            if(m.find(tree[node][i]) == m.end()) {
                m[tree[node][i]] = dist + 1;
                q.push(tree[node][i]);
            }
        }
    }
    return false;
}

void init_server() {
    printf("Reading configuration\n");
    string line;
    ifstream myfile("training.txt");
    if(myfile.is_open()) {
        getline(myfile, line);
        N = stoi(line);
        tree.clear();
        tree.resize(N + 1);
        while(getline(myfile, line)) {
            vector<int> node = split(line);
            tree[node[0]].push_back(node[1]);
            tree[node[1]].push_back(node[0]);
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
