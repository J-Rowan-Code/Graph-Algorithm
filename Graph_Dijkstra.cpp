
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

//Add exception to handle if a node doesn't exist Test case 6 NODE N not there!

struct Node{
	char key;
	int weight;
	Node *next;
};

struct graphNode{
	char key;
	Node *listPtr;
};

class Graph{
	private:
		vector<graphNode> chain;
	public:
		Graph(){};
		~Graph(){};
		void addNewChain(char key);
		void addNewEdge(char A, char B, int distance);
		void printGraph();
		void reverse();
		void Dijkstra();
		void sort();
		void populate();
		bool checkFull();
};

Graph mathIsCool;



int main (int argc, char **argv){
	string expression, token;
	ifstream inputFile;
	bool checker;
	
	if(argc!=2) {cout<< "Type a file name. " << endl << argv[1] << endl; exit(0);}
	inputFile.open(argv[1]);
	//inputFile.open("graph5.txt");
	
	if(inputFile.is_open()==false){cout << "Could not read file: " << argv[1] <<endl; exit(0);}
	
	while(!inputFile.eof()){
		getline(inputFile, expression);
		stringstream line(expression);
		if(inputFile.eof()) {break;}
		if(expression[0] == '#') {continue;}
		
		char nodeName;
		if(expression[0] == 'N' && expression[1] == 'o'){
			getline(line, token,' ');
			getline(line, token,' ');
			nodeName = (token.c_str())[0];
			//cout << "Node " << nodeName << endl;
			mathIsCool.addNewChain(nodeName);
			
			//Do something with the graphs probably
		}else{
			char nodeFrom, nodeTo;
			getline(line, token, ' ');
			nodeFrom = (token.c_str())[0];
			//cout << "From " << nodeFrom;
			getline(line, token, ' ');
			nodeTo = (token.c_str())[0];
			//cout << " to " << nodeTo;
			
			int cost;
			getline (line, token, ' ');
			//cost = stoi(token);
			cost = atoi(token.c_str());
			//cout << " costs " << cost << endl;
			
			mathIsCool.addNewEdge(nodeFrom, nodeTo, cost);
			//Put the edges onto the graph
		}
		
	}
	
	//mathIsCool.printGraph();
	
	mathIsCool.sort();
	checker = mathIsCool.checkFull();
	while(checker){
		checker = false;
		mathIsCool.populate();
		mathIsCool.sort();
		checker = mathIsCool.checkFull();
	}
	//mathIsCool.printGraph();
	mathIsCool.Dijkstra();
	
}

void addNodeFront(Node *&listPointer, char newKey, int newWeight){
	Node *temp;
	temp = new Node;
	temp->key = newKey;
	temp->weight = newWeight;
	temp->next = listPointer;
	listPointer = temp;
}

int navigateList(int A, Node *B){
	int min;
	min=99999;
	if(B==NULL){
		cout << endl << "Too far" << endl;
		return 999999;
	}
	min = A + B->weight;
	//printf("KEY: %c:\n", B->key);
	B = B->next;
	return min;
}

int listSize(Node *A){
	Node *temp=A;
	int B=1;
	
	while(temp!=NULL){
		if(temp==NULL){
			//cout << "Bother" << endl;
			break;
		}
		temp = temp->next;
		B++;
	}
	return B;
}
	
	//cout << endl << "Works good" <<endl;
	




/*void addNodeRear(Node *&listPointer, char newKey, int newWeight){
	Node *temp;
	temp = new Node;
	
}*/

void printLL(Node *& listPointer){
	Node *temp;
	temp = listPointer;
	while (temp!=NULL){
		printf("to node %c dist: %d\n", temp->key, temp->weight);
		temp = temp->next;
	}
}

int min(int A, int B){
	if(A < B){
		return A;
	}
	else{
		return B;
	}
}

bool Graph::checkFull(){
	int N, indx;
	N = chain.size();
	for(indx=0; indx<N; indx++){
		if(chain[indx].key!=indx+65){
			//cout << " Yeah nah she's not that right aye";
			return true;
		}
	}
	return false;
}

void Graph::populate(){
	int N, indx, temp;
	bool miss;
	char missing;
	N = chain.size();
	for(indx=0; indx<N; indx++){
		if(chain[indx].key!=indx+65){
			//cout << " Yeah nah she's not that right aye";
			miss=true;
			temp = indx;
			break;
		}
	}
	missing = temp+65;
	
	
	if(miss){
		addNewChain(missing);
	}
	addNewEdge(missing, 1, 999999);
}

void Graph::addNewChain(char newKey){
	graphNode temp;
	temp.key = newKey;
	temp.listPtr = NULL;
	chain.push_back(temp);
}

void Graph::sort(){
	graphNode temp;
	Node *current, *mini, *temp2, *temp3, *begin, *prev, *test;
	int indx, pass, min;
	for(pass = 0; pass < chain.size()-1; pass++){
		min = pass;
		for(indx = pass+1; indx<chain.size(); indx++){
			if(chain[indx].key < chain[min].key){ min = indx;}
		}
		temp = chain[min];
		chain[min] = chain[pass];
		chain[pass] = temp;
	}
	
	int indx2, N;
	for(indx=0; indx<chain.size(); indx++){
		min=0;
		current = chain[indx].listPtr;
		temp = chain[indx];
		N = listSize(current);
		begin = current;
		//temp3 = current;
		for(pass=0; pass<N-1; pass++){
			mini = begin;
			current = begin;
			temp3 = chain[indx].listPtr;
			for(indx2 = pass+1; indx2<N; indx2++){
				if(current->next==NULL){
					break;}
				if(current->next->key < mini->key){mini = current->next;}
				//printf("Comparing %c and %c.\n%c was the lower value\n",current->next->key, current->key, mini->key);
				current = current->next;
			}
			//printf("\n\nMini key end loop is %c\n\n",mini->key); 
			if(min==0){
				
				//NOT SUPER SURE ABOUT THIS LINE BELOW!!
				
				if(temp3==mini || begin==mini){begin = begin->next;continue;}
				while(temp3->next!=mini){
					temp3 = temp3->next;
				}
				//printf("Temp 3 is %c. Temp3 -> next is %c. Mini is %c\n", temp3->key, temp3->next->key, mini->key);
				temp2 = chain[indx].listPtr;
				temp3->next = mini->next;
				mini->next = temp2;
				chain[indx].listPtr = mini;
				min=1;
				begin = mini;
				prev = begin;
				if(begin->next!=NULL){
					begin = begin->next;
				}
				
				test = chain[indx].listPtr;
				//printf("\n\nIn list %c First is %c then is %c then %c\n\n", chain[indx].key, chain[indx].listPtr->key, test->next->key, test->next->next->key);
				
			}else{
				if(temp3==mini || begin==mini){begin=begin->next; continue;}
				//printf("\n\n%c is mini key, %c is listptr key\n\n", mini->key, temp.listPtr->key);
				while(temp3->next!=mini){
					temp3 = temp3->next;
				}
				temp2 = begin->next;
				temp3->next = mini->next;
				if(mini!=temp2&&mini->next!=NULL){
					mini->next = temp2;
				}else{
					mini->next = begin;
				}
				
				prev->next = mini;
				begin = mini;
				prev = begin;
				if(begin==NULL){continue;}
				if(begin->next!=NULL){
					begin = begin->next;
				}
			}
		}
	}

}


void Graph::addNewEdge(char A, char B, int distance){
	int indx;
	for(indx=0; chain.size(); indx++){
		if(A == chain[indx].key){break;}
	}
	addNodeFront(chain[indx].listPtr, B, distance);
}

void Graph::printGraph(){
	int indx;
	for (indx=0; indx<chain.size(); indx++){
		printf("From node %c: \n", chain[indx].key);
		printLL(chain[indx].listPtr);
	}
}

void Graph::reverse(){
	Node *P1, *P2, *P3;
	unsigned int indx;;
	//printf(" %d", chain.size());
	
	for (indx=0; indx<chain.size(); indx++){
		if(chain[indx].listPtr==NULL){
			continue;
		}
		//cout << "Index here is: " << indx << endl;
		P2 = chain[indx].listPtr;
		if(P2->next!=NULL){
			P3 = P2->next;
		}

		while(P3!=NULL){
			//printf("%c \n", chain[indx].key);
			P1 = P3->next;
			P3 -> next = chain[indx].listPtr;
			chain[indx].listPtr = P3;
			P3 = P1;
		}
		P2->next = NULL;
	}
}
	
void Graph::Dijkstra(){
	int N = chain.size();
	int count, small, indx, d[N];
	char s[N];
	bool stillT=true;
	count = 0;
	Node *current;
	//current = chain[0].listPtr;
	
	//cout << current->weight;
	//current = current->next;
	//cout << current->weight;
	//printf("%d items in chain \n", N);
	for(indx=0; indx<N; indx++){
		d[indx] = 999999;
		s[indx] = 't';
	}
	d[0]=0;
	s[0]= 'p';
	
	//cout << "did it do?" << c[0] << endl;
	
	//printf("\n\nLIST SIZE IS: %d\n\n", listSize(current));

	
	while(stillT){
		current = chain[count].listPtr;
		
		//printf("Now working with chain %c\n", chain[count].key);
		
		small = 9999999;
		stillT = false;
		for(indx=0; indx<N; indx++){
			if(s[indx]=='t'){
				stillT = true;
			}
		}
		if (stillT!=true){break;}
		indx=0;
		while(current!=NULL){
			if(chain[count].key == indx+65){
				indx++;
				//printf("Chain key is %c indexing value is %c\n", chain[count].key, indx+65);
				continue;}
			if(current==NULL){
				continue;
			}
			
			
			
			if(current->key==indx+65){
				d[indx] = min(d[indx], (d[count] + current->weight));
				//printf("Comparing indx %d (%c) with node %c. Value stored is %d\n",indx, indx+65, current->key, d[indx]);
				current = current->next;
			}
			indx++;
			if(indx>26){
				indx=0;
			}
		}
		for(indx=0; indx<N; indx++){
			if(s[indx] == 'p'){continue;}
			if(d[indx]<small){
				small = d[indx];
				count = indx;
			}
		}
		s[count]='p';
	}
	
	for(indx=1; indx<chain.size(); indx++){
		if(d[indx]==999999){continue;}
		printf("From A to %c:%d\n", indx+65, d[indx]);
	}
	/*
	current = chain[0].listPtr;
	indx = 1;
	while(current!=NULL){
		
		cout << "From A to " << current->key << ":" << d[indx] << endl;
		current = current->next;
		indx++;
	}*/
}
	