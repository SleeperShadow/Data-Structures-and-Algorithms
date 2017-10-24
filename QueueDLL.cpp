#include <iostream>
#include "string"
#include <algorithm>
using namespace std;
template<typename T>
struct Node{
    T data;
    Node* prev;
    Node* next;
    Node<T>(T const& val){
        prev=next=NULL;
        data=val;
    }
    Node<T>(){
        prev=next=NULL;
    }
};
template<typename T>
class Queue{
private:
    Node<T> *first,*last;
    int capacity;
public:
    Queue(){
        capacity=0;
        first=last=NULL;
    }
    Queue(Queue const& queue){

        capacity=0;
        if(queue.capacity>=1) {
            const Node<T> *current = queue.first;
            for (int i = 0; i < queue.capacity; i++) {
                push(current->data);
                current = current->next;
            }
        }
        else {
            first = last = NULL;
        }
    }

    ~Queue(){
        for(int i=0;i<capacity;i++){
            Node<T>* temp=first;
            first=first->next;
            delete temp;
        }
    }
    Queue& operator=(Queue const&queue){
        if(this!=&queue){
            //Delete Queue if not NULL already
            for(int i=0;i<capacity;i++){
                Node<T>* temp=first;
                first=first->next;
                delete temp;
            }
            capacity=0;
            if(queue.capacity>=1) {
                const Node<T> *current = queue.first;
                for (int i = 0; i < queue.capacity; i++) {
                    push(current->data);
                    current = current->next;
                }
            }
            else {
                first = last = NULL;
            }
        }
        return *this;
    }

    T pop(){
        T x;
        if(capacity==1)
        {
            x=first->data;
            delete first;delete last;
            first=last=NULL;
            capacity--;
        }
        else if(capacity>=2) {
            x = first->data;
            Node<T> *temp = first;
            first = first->next;
            first->prev = NULL;
            delete temp;
            capacity--;
        }
        else if(capacity==0)
            throw runtime_error("The queue is already empty! You can't pop more!");
        return x;

    }
    void push(T const& element){
        
        if(!empty()){
            last->next=new Node<T>(element);
            last->next->prev=last;
            last=last->next;
            capacity++;
            
        }
        else{
            last=first=new Node<T>(element);
            capacity++;
        }
    }
    T const front()const{
        return first->data;
    }
    bool const empty()const{
        return capacity==0;
    }
    int const size()const{
        return capacity;
    }
    T const back()const{
        return last->data;
    }
    void swap(int pos1,int pos2){
        int top=max(pos1,pos2);
        int bot=min(pos1,pos2);
        if(bot>0 && top<=capacity && top!=bot){
            Node<T>* bottom=first;
            Node<T>* topper=first;
            for(int i=0;i<top-1;i++){
                if(i<bot-1)
                    bottom=bottom->next;
                topper=topper->next;
            }
            int temp=bottom->data;
            bottom->data=topper->data;
            topper->data=temp;

        }
        else if(top==bot)
            cerr<<"You can't swap an element with itself"<<endl;
        else
            throw runtime_error("Inadequate positions given to swap() function!");
    }
    void swapqueue(Queue& queue){
        Node<T>*temp=first;
        first=queue.first;
        queue.first=temp;

        temp=last;
        last=queue.last;
        queue.last=temp;

        int t=capacity;
        capacity=queue.capacity;
        queue.capacity=t;

    }
    friend ostream& operator<<(ostream& os,Queue const& q){
        Node<T>*temp=q.first;
        for(int i=0;i<q.capacity;i++)
            {
                os<<temp->data<<'\t';
                temp=temp->next;
            }
            os<<endl;
        return os;
    }
    //prints out the queue deleting it at the same time
    void print(){
        while(!empty())
            cout<<pop()<<"  ";
        cout<<endl;
    }



};

int main(){
    Queue<double> emptyQueue, emptyQue;
    //cout<< emptyQueue.front() << " " << emptyQueue.back() << "Finished test 0.1\n\n";
    //cout<< emptyQueue.pop()<< "Finished test 0.2\n\n";
    
    
	Queue<double> que1;
	cout << que1;
	que1.push(1.11);
	cout << que1;
	cout << que1.front() << " " << que1.back() << endl;
	cout << "Finished test 1 !\n\n";
	
	cout<< "first: "<< emptyQueue;
	cout<< "second: "<< que1;
	emptyQueue.swapqueue(que1);
	cout<< "first: "<< emptyQueue;
	cout<< "second: "<< que1;
	que1.swapqueue(emptyQueue);
	cout<< "first: "<< emptyQueue;
	cout<< "second: "<< que1;
	cout<< "first: "<< emptyQue; 
	cout<< "second: " << emptyQueue; 
	emptyQueue.swapqueue(emptyQue);
	cout<< "first: "<< emptyQue; 
	cout<< "second: " << emptyQueue; 
	emptyQue.push(5.3);
	cout<< "first: "<< emptyQue; 
	cout<< "second: " << que1; 
	emptyQue.swapqueue(que1);
	cout<< "first: "<< emptyQue; 
	cout<< "second: " << que1; 
	cout<< "Finished test 0.3 \n\n"; 

	Queue<double> que2 = que1;
	cout << que2;
	que2.push(2.22);
	cout << que2;
	cout << "Finished test 2 !\n\n";

	Queue<double> que3;
	que3 = que2;
	cout << que3;
	que3.push(3.33);
	cout << que3;
	cout << "Finished test 3 !\n\n";

	Queue<double> que4;
	if (que4.empty()) cout << que4;
	if (!que3.empty()) cout << que3;
	cout << "Finished test 4 !\n\n";

	if (que1.size() == 1) cout << "Success\n";
	if (que2.size() == 2) cout << "Success\n";
	if (que3.size() == 3) cout << "Success\n";
	if (!que4.size()) cout << "Success\n";
	cout << "Finished test 5 !\n\n";

	Queue<double> que5;
	//que5.pop();
	//cout <<  que5.pop() << "1" << endl; /* throw runtime error
	que5 = que3;
	que5.pop();
	cout << que5.pop() << endl;
	cout << que5;
	cout << "Finished test 6 !\n\n";

	Queue<double> que6;
	if (que5.front() == 2.22) cout << "Success\n";
	if (que5.back() == 3.33) cout << "Success\n";
	//temp = que6.front(); /* Should return
	//temp = que6.back();                 runtime_error */
	cout << "Finished test 7 !\n\n";

	cout << que3;
	que3.swap(1, 3);
	cout << que3;
	//que3.swap(4, 5);
	//que6.swap(1, 2);
	cout << "Finished test 8 !\n\n";

	Queue<double> que7;
	cout << que7;
	cout << que3 << endl;
	que7.swapqueue(que3);
	cout << que7;
	cout << que3;
	cout << "Finished test 9 !\n\n";

	cout << que7;
	que7.print();
	cout << que7;
	cout << "Finished test 10 !\n\n";

    return 0;
}