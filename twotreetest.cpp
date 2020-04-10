// twotreetest.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <vector>
#include <stack>
using namespace std;
struct TREENODE
{
	char val;
	TREENODE* lchrild;
	TREENODE* rchrild;
	TREENODE(char x) :val(x), lchrild(NULL), rchrild(NULL) {}
};


void preoder(TREENODE* root, vector<char>& vec)
{
	if (root != NULL)
	{
		vec.push_back(root->val);
		preoder(root->lchrild, vec);
		preoder(root->rchrild, vec);
	}
}

void preoder1(TREENODE* root, vector<char>& vec)
{
	stack<TREENODE*> st;
	TREENODE* p = root;
	while (!st.empty()||p!=NULL)
	{
		while (p)
		{
			vec.push_back(p->val);
			st.push(p);
			p = p->lchrild;
		}
		p = st.top();
		st.pop();
		p = p->rchrild;
	}
}

void inoder(TREENODE* root, vector<char>& vec)
{
	if (root != NULL)
	{
		inoder(root->lchrild, vec);
		vec.push_back(root->val);
		inoder(root->rchrild, vec);
	}
}

void inoder1(TREENODE* root, vector<char>& vec)
{
	stack<TREENODE*> st;
	TREENODE* p = root;
	while (!st.empty() || p != NULL)
	{
		while (p)
		{
			st.push(p);
			p = p->lchrild;
		}
		p = st.top();
		st.pop();
		vec.push_back(p->val);
		p = p->rchrild;
	}
}

void postoder(TREENODE* root, vector<char>& vec)
{
	if (root != NULL)
	{
		postoder(root->lchrild, vec);
		postoder(root->rchrild, vec);
		vec.push_back(root->val);
	}
}

void postoder1(TREENODE* root, vector<char>& vec)
{
	stack<TREENODE*> st;
	TREENODE* p = root;
	TREENODE* q = NULL;
	while (!st.empty() || p != NULL)
	{
		if (p)
		{
			st.push(p);
			p = p->lchrild;
		}
		else
		{
			p = st.top();
			if (p->rchrild && p->rchrild != q)
			{
				p = p->rchrild;
			}
			else
			{
				p = st.top();
				st.pop();
				vec.push_back(p->val);
				q = p;
				p = NULL;
			}
		}
	}
}

void postoder2(TREENODE* root, vector<char>& vec)
{
	stack<TREENODE*> st;
	stack<int> st1;
	TREENODE* p = root;
	TREENODE* q = NULL;
	while (!st.empty() || p != NULL)
	{
		while (p)
		{
			st.push(p);
			st1.push(0);
			p = p->lchrild;
		}
		if (st1.top() == 1)
		{
			vec.push_back(st.top()->val);
			st.pop();
			st1.pop();
		}
		else
		{
			p = st.top();
			st1.top() = 1;
			p = p->rchrild;
		}
	}
}

TREENODE* createtree()
{
	TREENODE* A = new TREENODE('A');
	TREENODE* B = new TREENODE('B');
	TREENODE* C = new TREENODE('C');
	TREENODE* D = new TREENODE('D');
	TREENODE* E = new TREENODE('E');
	TREENODE* F = new TREENODE('F');
	TREENODE* G = new TREENODE('G');
	TREENODE* H = new TREENODE('H');
	TREENODE* I = new TREENODE('I');
	A->lchrild = B;
	A->rchrild = C;
	B->lchrild = D;
	D->lchrild = G;
	D->rchrild = H;
	C->lchrild = E;
	C->rchrild = F;
	E->rchrild = I;
	return A;
}

void printvec(vector<char>& vec)
{
	for (auto i:vec)
	{
		cout << i << " ";
	}
	cout << endl;
}
int main()
{
	TREENODE* root = createtree();
	vector<char> vec;
	preoder(root, vec);
	cout << "前序: ";
	printvec(vec);
	vec.clear();
	preoder1(root, vec);
	cout << "前序1: ";
	printvec(vec);
	vec.clear();
	inoder(root, vec);
	cout << "中序: ";
	printvec(vec);
	vec.clear();
	inoder1(root, vec);
	cout << "中序1: ";
	printvec(vec);
	vec.clear();
	postoder(root, vec);
	cout << "后续: ";
	printvec(vec);
	vec.clear();
	postoder1(root, vec);
	cout << "后续1: ";
	printvec(vec);
	vec.clear();
	postoder2(root, vec);
	cout << "后续2: ";
	printvec(vec);
	vec.clear();
    return 0;
}

