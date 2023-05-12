/*
 Program-6: Graphs
 Professor: David Hayes & George Maratos
 Author: Aaryan Sharma
 CS 141 - Spring 2023
 */


#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class node {
public:
    int val = 0;
    node* next = nullptr;

    node() {}
    node(int data) {
        this->val = data;
        this->next = NULL;
    }
};

void write(string dst, vector<node*>& vec) {
    /*
     This function takes a file name and a vector of linked lists as input, and writes the graph to a file with the given name.
     It loops through the vector and writes each linked list to the file.
     */

    ofstream fstr{dst};

    for (int i = 0; i < vec.size(); i++) {
        if (vec.at(i) != nullptr) {
            node* ptemp = vec.at(i);
            fstr << i << ":";

            while (ptemp != nullptr) {
                fstr << " " << ptemp->val;
                ptemp = ptemp->next;
            }
            fstr << endl;
        }
    }

    fstr.close();
}

void add_btw(vector<node*>& vertices, int index, int new_data) {
    /*
    This function takes a vector of linked lists, an index, and a new value as input, and adds a new node with the given value to the linked list at the given index in the vector.
    It inserts the new node in the correct position in the linked list to maintain the order.
    */

    node* pHead = vertices.at(index);

    if (pHead->val == new_data) {
        return;
    }

    else if (pHead->val > new_data) {
        node* newNode = new node(new_data);

        newNode->next = pHead;

        vertices.at(index) = newNode;

        return;
    }

    else {
        while (pHead->next != NULL) {
            if (pHead->next->val == new_data) {
                return;

            }

            else if (pHead->next->val > new_data) {
                node* newNode = new node(new_data);

                newNode->next = pHead->next;

                pHead->next = newNode;

            }

            else {
                pHead = pHead->next;
            }
        }
    }

    pHead->next = new node(new_data);
}

void load (string file_name, vector<node*>& vertices) {
    /*
    This function takes a file name and a vector of linked lists as input, and reads in the graph from the file.
    It loops through the lines of the file, extracts the node values from each line, and adds them to the vector using the append and add_btw functions.
    */

    string main;
    ifstream file(file_name);

    int max = 0;

    while (!file.eof()) {
        string str1, str2;
        file >> str1;

        if (str1 == "") {
            break;
        }

        file>>str2;
        cout << str1 << "  :  " << str2<< "----";

        if (stoi(str2) > max) {
            max = stoi(str2);
        }
        while (max >= vertices.size()) {
            vertices.push_back(NULL);
        }

        if (vertices.at(stoi(str1)) == NULL) {
            vertices.at(stoi(str1)) = new node(stoi(str2));
        }

        else {
            add_btw(vertices, stoi(str1), stoi(str2));
        }

        if (vertices.at(stoi(str2)) == NULL) {
            vertices.at(stoi(str2)) = new node(stoi(str1));

        }
        else {
            add_btw(vertices, stoi(str2), stoi(str1));
        }
    }
}

void getInfo(vector<node*>& vec_adj, int& nodes, int& edges, int& degree) {
    /*
    This function takes a vector of linked lists and three integers as input, and computes the number of nodes, the number of edges, and the maximum degree of the graph.
    */
    for (int i = 0; i < vec_adj.size(); i++) {
        int count = 0;

        if (vec_adj.at(i) != nullptr) {
            node* ptemp = vec_adj.at(i);
            nodes++;

            while (ptemp != nullptr) {
                ptemp = ptemp->next;
                count++;
            }

            if (count > degree) {
                degree = count;
            }
        }
        edges += count;
    }
}

void run(const string& src_path, const string& dst_path) {
    /*
    The run function is the main function of the program.
    It calls the load function to read in the graph from the file, the getInfo function to compute the graph information, and the write function to write the graph to the output file.
    It also prints out the number of nodes, the number of edges, and the maximum degree of the graph.
    */

    vector<int> vec_head, vec_node;
    vector<node*> vec_adj;

    load(src_path, vec_adj);

    int edges = 0;
    int nodes = 0;
    int degree = 0;

    getInfo(vec_adj, nodes, edges, degree);
    write(dst_path, vec_adj);


    cout << "adj_list" <<endl;
    for (int i = 0; i < vec_adj.size(); i++) {
        node* nav = vec_adj.at(i);
        if (nav == nullptr){
            continue;
        }
        cout << i<< ": ";
        while (nav!= nullptr){
            cout << nav->val<<" ";
            nav = nav->next;
        }
        cout <<endl;
    }
    cout << "-----------" <<endl;


    cout << "Number of nodes: " << nodes << endl;
    cout << "Number of edges: " << (edges / 2) << endl;
    cout << "Maximum degree: " << degree << endl;
}

int main() {
    run("youtube.txt", "output.txt");

    return 0;
}