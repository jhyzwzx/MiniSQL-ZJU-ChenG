#ifndef _INDEXMANAGE_H_
#define _INDEXMANAGE_H_
#include <vector>
#include <map>
#include "recordManager.h"
using namespace std;

#define SINGLE 0
#define LARGER 1
#define NOTLESS 2
#define NOTLARGER 3
#define LESS 4

class IndexManager
{
private:
	map< string, BplusTree > indexTable; //store the B+ tree list
public:
	bool createIndex( Target t, string indexName );
	vector<index_info>& searchSingle( Target t ); 
	bool insert( Target t );
	bool deleteKey( Target t );
	bool deleteIndex( Target t );
};

struct indexResult
{
	int blockNumber;
	int offset;
	indexResult* next;
};

struct indexNode
{
	string tableName;
	string attribute;
	string inexName;
};

template< class T >
class Target 
{
private:
	string table;
	string attribute;
	T key;
	index_info index;
	int type;
public:
	Target( string t, string a )
	Target( string t, string a, T x );
	~Target();
	void setTable( string name );
	void setAttribute( string name );
	void setBeginKey( T x );
	void setEndKey( T x );
	void setKey(T x);
	void setvalue(T x);
	void setindex_info(index_info tmp);
	string getTable();
	strinng getAttribute();
	index_info getIndexInfo();
	T getKey();
	T getBeginKey();
	T getEndKey();
	bool isSingle();
};

template< class T >
class BplusTree
{
private:
	int M;
	InteriorNode root;

public:
	BplusTree();
	~BplusTree();
	bool isEmpty();
	bool insert( T target ); //T.getIndexInfo() returns index_info
	bool delete( T target ); 
	bool deleteIndex(string indexname);
	vector<index_info>& rangeSearch( T beginTarget, T endTarget );
	vector<index_info>& singleSearch( T target ); 
};

template < class T >
class InteriorNode
{ 
private:
	int M;  
	vector<T> key;
	vector<InteriorNode*> pointer;

public:
	InteriorNode();
	~InteriorNode();

	virtual bool isEmpty();
	bool checkKey( T target ); //check whether the key with the value of taget exist or not
	T getKey( int i );
	InteriorNode* getChildPointer( int i );
	InteriorNode* getTargetPointer( T target );
};

template< class T >
class LeafNode:public InteriorNode
{  
private:
	vector<int> blockNumber;
	vector<int> offset;
	LeafNode* nextLeafNode;

public:
	virtual bool isEmpty();
	vector<index_info> getRecordAddress( T target );
	LeafNode* getNextLeaf();
};

#endif







