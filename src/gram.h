// comment: 语法树的定义
#ifndef DBMS_GRAMTREE_H
#define DBMS_GRAMTREE_H
class GramTree{
private:
	int type;
	char strValue[100] = "";
	int numValue = 0;
	int childNum = 0;
	GramTree *father;
	GramTree *child[20]; //childlist

public:
	const static int GRAM_ROOT = 10001, GRAM_TABLE = 10002, GRAM_COLUMN = 10003,
		GRAM_COLUMNLIST = 10004, GRAM_VALUELIST = 10005, GRAM_STRVALUE = 10006,
		GRAM_NUMVALUE = 10007, GRAM_CONDITION = 10008, GRAM_ISNULL = 10009,
		GRAM_NOTNULL = 10010, GRAM_LOGIC = 10011, GRAM_COMPARE = 10012,
		GRAM_NULLVALUE = 10013, GRAM_INDEX = 10014, GRAM_TEMP = 10015,
		GRAM_OPERATION = 10016, GRAM_KEYVALUE = 10017, GRAM_SELECTEDLIST = 10018;
	
	void setType(int type);
	int getType();
	void setStrValue(char* value);
	void setStrValue(const char *value);
	char* getStrValue();
	void setNumValue(int value);
	int getNumValue();
	int getChildNum();
	int addChild(int type);    //return new child index
	void addChildToLast(GramTree *node);
	void addChildToFirst(GramTree *node);
	GramTree* getChild(int childIndex);    //return child pointer
	int removeChild(int index);    //return 1 means succeeded and 0 means this child does not exist
	GramTree* getFather();    //return father pointer
	void showTree(int level = 0);
	void getTypeStr(char *str);    //get string according to type
};

#endif