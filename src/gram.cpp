#include "gram.h"
#include <string.h>
#include "stdio.h"

void GramTree::setType(int type) {
	this->type = type;
}

int GramTree::getType() {
	return this->type;
}

void GramTree::setStrValue(const char *value) {
	strcpy(this->strValue, value);
}

void GramTree::setStrValue(char *value) {
	strcpy(this->strValue, value);
}

char* GramTree::getStrValue() {
	return this->strValue;
}

int GramTree::getNumValue() {
	return this->numValue;
}

void GramTree::setNumValue(int value) {
	this->numValue = value;
}

int GramTree::getChildNum() {
	return this->childNum;
}

int GramTree::addChild(int type) {
	this->child[this->childNum] = new GramTree;
	this->child[this->childNum]->type = type;
	this->child[this->childNum]->father = this;
	this->childNum = this->childNum + 1;
	return this->childNum - 1;
}

void GramTree::addChildToLast(GramTree *node) {
	this->child[this->childNum] = node;
	this->childNum = this->childNum + 1;
}

void GramTree::addChildToFirst(GramTree *node) {
	for (int j = this->childNum; j > 0; j--) {
		this->child[j] = this->child[j - 1];
	}
	this->child[0] = node;
	this->childNum = this->childNum + 1;
}

GramTree* GramTree::getChild(int childIndex) {
	return this->child[childIndex];
}

int GramTree::removeChild(int index) {
	if (this->child[index] == NULL) return 0;
	this->child[index] = NULL;
	for (; index < this->childNum-1; index++) {
		this->child[index] = this->child[index + 1];
	}
	this->childNum = this->childNum - 1;
	return 1;
}

GramTree* GramTree::getFather() {
	return this->father;
}

void GramTree::showTree(int level) {
	char str[100];
	if (level == 0) {
		this->getTypeStr(str);
		printf("%s  strValue: %s  numValue: %d\n", str, this->getStrValue(), this->getNumValue());
	}
	for (int i = 0; i < childNum; i++) {
		if (this->child[i] == NULL) return;
		GramTree *p = this->child[i];
		for (int j = 0; j < level + 1; j++) {
			printf("   ");
		}
		p->getTypeStr(str);
		printf("|--%s  strValue: %s  numValue: %d\n", str, p->getStrValue(), p->getNumValue());
		p->showTree(level + 1);
	}
}

void GramTree::getTypeStr(char *str) {
	switch (this->type) {
	case GRAM_ROOT:
		strcpy(str, "GRAM_ROOT");
		break;
	case GRAM_TABLE:
		strcpy(str, "GRAM_TABLE");
		break;
	case GRAM_COLUMNLIST:
		strcpy(str, "GRAM_COLUMNLIST");
		break;
	case GRAM_COLUMN:
		strcpy(str, "GRAM_COLUMN");
		break;
	case GRAM_VALUELIST:
		strcpy(str, "GRAM_VALUELIST");
		break;
	case GRAM_STRVALUE:
		strcpy(str, "GRAM_STRVALUE");
		break;
	case GRAM_NUMVALUE:
		strcpy(str, "GRAM_NUMVALUE");
		break;
	case GRAM_CONDITION:
		strcpy(str, "GRAM_CONDITION");
		break;
	case GRAM_ISNULL:
		strcpy(str, "GRAM_ISNULL");
		break;
	case GRAM_NOTNULL:
		strcpy(str, "GRAM_NOTNULL");
		break;
	case GRAM_LOGIC:
		strcpy(str, "GRAM_LOGIC");
		break;
	case GRAM_COMPARE:
		strcpy(str, "GRAM_COMPARE");
		break;
	case GRAM_NULLVALUE:
		strcpy(str, "GRAM_NULLVALUE");
		break;
	case GRAM_INDEX:
		strcpy(str, "GRAM_INDEX");
		break;
	case GRAM_TEMP:
		strcpy(str, "GRAM_TEMP");
		break;
	case GRAM_OPERATION:
		strcpy(str, "GRAM_OPERATION");
		break;
	case GRAM_KEYVALUE:
		strcpy(str, "GRAM_KEYVALUE");
		break;
	case GRAM_SELECTEDLIST:
		strcpy(str, "GRAM_SELECTEDLIST");
		break;
	default:
		strcpy(str, "UNKNOW");
		break;
	}
}
