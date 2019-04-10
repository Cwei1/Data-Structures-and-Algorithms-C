/*Cardy Wei
Programming Assignment 1
Implementing Stacks and Queues
Data Structures and Algorithms I
Professor Sable*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>

using namespace std;

template <class T>//template class Simplelist
class SimpleList{
private:
    class Node{
        public:
            T x;
            Node *next;//Node doesn't need a constructor, only needs to access this data
    };
public:
    Node *head;
    Node *tail;
    string name;
    int size;
    SimpleList(string givenname){
        head = tail = NULL;//constructor, when it initialises, it starts with a NULL pointer
        size = 0;
        name=givenname;
    }

    string retname(){
        return name;
    }
   
    virtual void push(T value){} //virtual functions accessable outside of this class
    virtual T pop(){};

protected:
    virtual void addinFront(T value){
        Node *np =new Node(); //creates a new node
        np->x=value;//sets value of node
        np->next=head;//sets next to what will soon be the old head node
        head=np;//np is now the head node

        if (size==0){
            tail = head;//the first node added into the list, is still considered both the head and the tail (we kicked the NULL out)
        }
        size++;
    }
    
    virtual void addinEnd(T value){
        Node *np=new Node();//new node
        np->x=value;//set node value
        if (size != 0){
            tail->next=np;//old tail node sets its next to np
            tail=np;//np is now tail node
            tail->next=NULL;//need this to fix segmentation fault
            size++;
        }
        else{
            addinFront(value);//if this is the first node added, adding a node to the end is basically the same thing as adding a node to the front
        }
    }

    virtual T popper(){
        Node *tmp = head;
        T retval = head->x;//value of the Node to be popped
        head=head->next;//the next node is now the head node
        delete tmp;//the old head node is then deleted
        size--;
        return retval;
    }
};

template <class T>
class Stack : public SimpleList<T>{
public:
    Stack<T>(string givenname):SimpleList<T>(givenname){};//constructor with name attribute
    void push(T value){
        SimpleList<T>::addinFront(value);//stacks add to the front and pop off the front
    }
    T pop(){
        return SimpleList<T>::popper();
    }
};

template <class T>
class Queue : public SimpleList<T>{
public:
    Queue<T>(string givenname):SimpleList<T>(givenname){};//constructor with name attribute
    void push(T value){
        SimpleList<T>::addinEnd(value);//queues add to the rear, and pop off the front
    }
    T pop(){
        return SimpleList<T>::popper();
    }
};

int main(){
    string line;
    list<string> names;//list of names, the conditions for creating a new stack/queue basically said that the entire second word in the create command cannot have been used before, so we store it in this list
    list<SimpleList<int> *> listSLi;//three lists of simple lists of different types
    list<SimpleList<double> *> listSLd;
    list<SimpleList<string> *> listSLs;
    ofstream outputFile;
    ifstream myfile;
    string inputfilename;
    string outputfilename;
    cout << "Please enter the name of your input file: ";
    cin >> inputfilename;
    cout << "Please enter the name of your output file: ";
    cin >> outputfilename;
    outputFile.open (outputfilename.c_str());//open the output file
    myfile.open(inputfilename.c_str());//open the input file
    if (myfile.is_open()){
        while ( getline (myfile,line) ){
            string outputline="PROCESSING COMMAND: "+line; //what we are processing in this giant chunk of code
            string output="";
            string tmps;
            istringstream test(line);
            int counter=0;
            string *command=new string[3];
            while (test >> tmps) {
                command[counter]=tmps;
                counter++;
            } //place the command into an array for easy accessability 
            if (command[0]=="create"){//conditions for creation
                if (find(names.begin(), names.end(), command[1]) != names.end()){//check if the name already exists in the names list
                    output="ERROR: This name already exists!";
                }
                else{
                    names.push_front(command[1]);
                    if (command[2]=="stack"){
                        if (command[1][0]== 'i'){//integer stack
                            SimpleList<int> *pSLi;
                            pSLi=new Stack<int>(command[1]);
                            listSLi.push_front(pSLi);
                        }                    
                        else if (command[1][0]== 'd'){//double stack
                            SimpleList<double> *pSLd;
                            pSLd=new Stack<double>(command[1]);
                            listSLd.push_front(pSLd);
                        } 
                        else{
                            SimpleList<string> *pSLs;//string stack
                            pSLs=new Stack<string>(command[1]);
                            listSLs.push_front(pSLs);
                        }          
                    }
                    else{
                        if (command[1][0]== 'i'){//integer queue
                            SimpleList<int> *pSLi;
                            pSLi=new Queue<int>(command[1]);
                            listSLi.push_front(pSLi);
                        }                    
                        else if (command[1][0]== 'd'){//double queue
                            SimpleList<double> *pSLd;
                            pSLd=new Queue<double>(command[1]);
                            listSLd.push_front(pSLd);
                        } 
                        else{
                            SimpleList<string> *pSLs;//string queue
                            pSLs=new Queue<string>(command[1]);
                            listSLs.push_front(pSLs);
                        }          
                    }
                }
            }

            else if(command[0]=="push"){
                if (find(names.begin(), names.end(), command[1]) != names.end()){
                    if (command[1][0]=='i'){//integer push
                        for (list<SimpleList<int> *>::iterator iter = listSLi.begin(), end = listSLi.end(); iter != end; ++iter) {
                            if ((*iter)->retname() == command[1] ){//used iterators to go through the list of simple list names and if a name matches, we push the value to it
                                (*iter)->push(atoi((command[2]).c_str()));//needed to convert string to int
                            }                           
                        }
                    }
                    else if (command[1][0]=='d'){//double push
                        for (list<SimpleList<double> *>::iterator iter2 = listSLd.begin(), end = listSLd.end(); iter2 != end; ++iter2) {
                            if ((*iter2)->retname()==command[1]){
                                (*iter2)->push(atof((command[2]).c_str()));//needed to convert string to double
                            }
                        }
                    }        
                    else{
                        for (list<SimpleList<string> *>::iterator iter3 = listSLs.begin(), end = listSLs.end(); iter3 != end; ++iter3) {//string push
                            if ((*iter3)->retname()==command[1]){
                                (*iter3)->push(command[2]);
                            }
                        }
                    }                        
                }
                else{
                    output="ERROR: This name does not exist!";//if the name is not found, this passes
                }
            }
            else{
                if (find(names.begin(), names.end(), command[1]) != names.end()){
                    if (command[1][0]=='i'){
                        for (list<SimpleList<int> *>::iterator iter = listSLi.begin(), end = listSLi.end(); iter != end; ++iter) {
                            if ((*iter)->retname() == command[1] && (*iter)->size != 0){//if the iterator finds the correct one, and it isn't currently empty, it will allow it to pop
                                ostringstream s;
                                s << (*iter)->pop();//this was done to maintain uniformity amongst the types
                                output="Value popped: " + s.str();
                            }
                            else if ((*iter)->retname() == command[1] && (*iter)->size == 0){
                                output="ERROR: This list is empty!";//if the names matches and is empty, return this
                            }          
                        }
                    }
                    else if (command[1][0]=='d'){
                        for (list<SimpleList<double> *>::iterator iter2 = listSLd.begin(), end = listSLd.end(); iter2 != end; ++iter2) {
                            if ((*iter2)->retname() == command[1] && (*iter2)->size != 0){
                                ostringstream s;
                                s << (*iter2)->pop();
                                output= "Value popped: " + s.str();
                            }
                            else if ((*iter2)->retname() == command[1] && (*iter2)->size == 0){
                                output="ERROR: This list is empty!";
                            }
                        }
                    }        
                    else{
                        for (list<SimpleList<string> *>::iterator iter3 = listSLs.begin(), end = listSLs.end(); iter3 != end; ++iter3) {
                            if ((*iter3)->retname() == command[1] && (*iter3)->size != 0){

                                ostringstream s;
                                s << (*iter3)->pop();
                                output="Value popped: " + s.str();
                            }
                            else if ((*iter3)->retname() == command[1] && (*iter3)->size == 0){
                                output="ERROR: This list is empty!";
                            }
                        }
                    }                        
                }
                else{
                    output="ERROR: This name does not exist!";//passes if the user is trying to pass a pop statement on a list that doesn't exist
                }
            }
            if (outputFile.is_open()){
                string finaloutput=outputline+"\n";
                if (output!=""){
                    finaloutput=finaloutput+output+"\n";
                } 
                outputFile <<finaloutput;//output statement into the output file, this mess was done, because extraneous white spaces kept popping up
            }
        }  
    }
    myfile.close();
    outputFile.close();//files closed
    return 0;//main needs a return 0 to know that it ended
}
