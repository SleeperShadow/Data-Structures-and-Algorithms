// Trees1.cpp : Defines the entry point for the console application.
//

#include "iostream"
#include <stack>
#include <list>
using namespace std;

class Tree {
private:
	int root;
	list<Tree> arr;
public:
	Tree() {
		root = 0;
	}
	Tree(int const& _root)
	{
		root = _root;
	}
	Tree& addChild(Tree tree) {
		arr.push_back(tree);
		return *this;
	}
	int getRoot() {
		return root;
	}
	list<Tree> getSubTrees() {
		return arr;
	}
	friend ostream& operator<<(ostream& os, Tree const& tree) {
		os << "( "<<tree.root<<" ";
		for (auto i = tree.arr.begin(); i != tree.arr.end(); ++i) {
			operator<<(os,*i);
		}
		os << ")";
		return os;
	}
	bool isLeaf() {
		if (arr.empty())
			return true;
		return false;
	}
	int sumLeafs() {
		int sum = 0;
		if (isLeaf()) 
			return root;
		
		for (auto i = arr.begin(); i != arr.end(); i++)
			sum+=i->sumLeafs();
		return sum;
	}
	int depth() {
		int max = 0;
		if (arr.empty())return 1;
		for (list<Tree>:: iterator i = arr.begin(); i != arr.end(); ++i) {
			int curr = 1;
			curr += i->depth();
			if (curr > max)max = curr;
		}
		return max;
	}
	int width() {
		return maxWidth(arr);
	}
	int maxWidth(list<Tree> lt) {
		int max = lt.size();
		if (max == 0)return 0;
		int current = 0;
		int j = 0;
		for(list<Tree>::iterator i = lt.begin(); i != lt.end() && j<max; ++j) {
			current += i->arr.size();
			for (list<Tree>::iterator k = i->arr.begin(); k != i->arr.end(); ++k)
				lt.push_back(*k);
			++i;
			lt.pop_front();
		}
		int next=maxWidth(lt);
		if (max < current)max = current;
		return max > next ? max : next;
	}
	void layerPos(int value) {
		int pos = 1;
		if (root == value) { cout << "This is the root at layer 1" << endl; return; }
		list<Tree> layer = findLayer(value, arr,pos);
		int j = 1;
		for (list<Tree>::iterator i = layer.begin(); i != layer.end(); ++i, j++)
			if (i->root == value) break;
		cout << "The layer is  " << pos << "  and the position is  " << j << endl;
	}
	list<Tree> findLayer(int value, list<Tree> lt, int& pos) {
		int max = lt.size();
		int j = 0;
		bool flag = false;
		++pos;
		for (list<Tree>::iterator i = lt.begin(); i != lt.end(); ++i)
			if (value == i->root)flag = true;
		if (flag)return lt;
		for (list<Tree>::iterator i = lt.begin(); i != lt.end() && j<max; ++j) {
			for (list<Tree>::iterator k = i->arr.begin(); k != i->arr.end(); ++k)
				lt.push_back(*k);
			++i;
			lt.pop_front();
		}
		return findLayer(value, lt, pos);
	}
	int breadth() {
		int max = arr.size();

		if (arr.empty())return 0;

		for (list<Tree>::iterator i = arr.begin(); i != arr.end(); ++i) {
			int curr = i->breadth();
			if (curr > max)max = curr;
		}
		return max;
	}
	void dfs() {
		if (arr.empty()) { 
			cout << root << " "; 
			return;
		}
		for (list<Tree>::iterator i = arr.begin(); i != arr.end(); i++) {
			i->dfs();
		}
		cout << root << " ";
		return;
	}
	void bfs() {
		cout << root << " ";
		if (arr.empty()) {
			return;
		}
		for (list<Tree>::iterator i = arr.begin(); i != arr.end(); ++i) {
			cout << i->root << " ";
		}
		for (list<Tree>::iterator i = arr.begin(); i != arr.end(); ++i) {
				for (list<Tree>::iterator it = i->arr.begin(); it != i->arr.end(); ++it)
					it->bfs();
		}

	}
	bool dfs(int elem) {
		if (root == elem)
			return true;
		if (arr.empty())return false;
		for (list<Tree>::iterator i = arr.begin(); i != arr.end(); ++i) {
			if (i->dfs(elem))return true;
		}
		return false;
	}
	bool dfs(int a,list<int>& path){
		path.push_back(root);
		if(root==a)
			return true;
		if(arr.empty())
			return false;
		
		for (list<Tree>::iterator i = arr.begin(); i != arr.end(); ++i) {
			if(!i->dfs(a,path))
				path.pop_back();
			else
				return true;

		}

	}
	void reverseTree() {
		 reverse(*this);
	}
	void reverse(Tree& lt) {
		list<Tree> children;
		if (lt.arr.empty())return;
		for (list<Tree>::reverse_iterator ri = lt.arr.rbegin();	ri!=lt.arr.rend() ; ++ri) 
			children.push_back(*ri);
		lt.arr.clear();
		for (list<Tree>::iterator i = children.begin(); i!=children.end(); i++) 
			lt.arr.push_back(*i);
		for (list<Tree>::iterator i = lt.arr.begin(); i != lt.arr.end(); i++)
			reverse(*i);
	}
	bool bfs(int elem) {
		if (root == elem)return true;
		if (arr.empty()) return false;
		for (list<Tree>::iterator i = arr.begin(); i != arr.end(); ++i) {
			if (i->root == elem)return true;
		}
		for (list<Tree>::iterator i = arr.begin(); i != arr.end(); ++i) {
			for (list<Tree>::iterator it = i->arr.begin(); it != i->arr.end(); ++it)
				it->bfs(elem);
		}
		return false;
	}
	int commonParent(int a, int b){
		list<Tree> children;
		if(!dfs(a) || !dfs(b))
			return -1;
		list<int> parents1;
		list<int> parents2;
		dfs(a,parents1);
		dfs(b,parents2);
		for(auto i=parents1.rbegin();i!=parents1.rend();i++){
			for(auto j=parents2.rbegin();j!=parents2.rend();j++)
				if(*i==*j)return *i;
		}
		return -1;
	}

};
int main()
{
	Tree tree(1);
	tree.addChild(Tree(2).addChild(3).addChild(4))
		.addChild(Tree(5).addChild(6).addChild(Tree(7).addChild(12).addChild(11)).addChild(8))
		.addChild(9);
	cout << tree<<endl;
	cout << tree.sumLeafs() << endl;
	cout << tree.depth() << endl;
	cout << tree.breadth() << endl;
	tree.dfs();
	cout << endl;
	tree.bfs();
	cout << endl;
	cout <<"Max Width:" <<tree.width() << endl;
	cout << (tree.dfs(0)? "True":"False")<<endl;
	cout << (tree.bfs(1) ? "True" : "False") << endl;
	tree.layerPos(6);
	tree.reverseTree();
	cout << tree << endl;
	cout<<tree.commonParent(6,11)<<endl;

    return 0;
}

