#include "lex.h"
#include <string.h>
#include <ctype.h>

int Token::getType() {
	return this->type;
}

void Token::setType(int type) {
	this->type = type;
}

char* Token::getValue() {
	return this->value;
}

void Token::setValue(char *value) {
	strcpy(this->value, value);
}

void Token::toUpperCase() {
	char *cur = this->value;
	for (; *cur != '\0'; cur++) {
		if ((int)*cur >= (int)'a' && (int)*cur <= (int)'z') {
			*cur = toupper(*cur);
		}
	}
}

void Token::idAutoType() {
	if (this->type != Token::ID) return;
	if (strcmp(this->value, "CREATE") == 0) {
		this->type = Token::TK_CREATE;
	}
	else if (strcmp(this->value, "TABLE") == 0) {
		this->type = Token::TK_TABLE;
	}
	else if (strcmp(this->value, "DROP") == 0) {
		this->type = Token::TK_DROP;
	}
	else if (strcmp(this->value, "INSERT") == 0) {
		this->type = Token::TK_INSERT;
	}
	else if (strcmp(this->value, "INTO") == 0) {
		this->type = Token::TK_INTO;
	}
	else if (strcmp(this->value, "VALUE") == 0) {
		this->type = Token::TK_VALUE;
	}
	else if (strcmp(this->value, "DELETE") == 0) {
		this->type = Token::TK_DELETE;
	}
	else if (strcmp(this->value, "FROM") == 0) {
		this->type = Token::TK_FROM;
	}
	else if (strcmp(this->value, "WHERE") == 0) {
		this->type = Token::TK_WHERE;
	}
	else if (strcmp(this->value, "UPDATE") == 0) {
		this->type = Token::TK_UPDATE;
	}
	else if (strcmp(this->value, "SET") == 0) {
		this->type = Token::TK_SET;
	}
	else if (strcmp(this->value, "INDEX") == 0) {
		this->type = Token::TK_INDEX;
	}
	else if (strcmp(this->value, "ON") == 0) {
		this->type = Token::TK_ON;
	}
	else if (strcmp(this->value, "SELECT") == 0) {
		this->type = Token::TK_SELECT;
	}
	else if (strcmp(this->value, "INT") == 0) {
		this->type = Token::TK_INT;
	}
	else if (strcmp(this->value, "CHAR") == 0) {
		this->type = Token::TK_CHAR;
	}
	else if (strcmp(this->value, "IS") == 0) {
		this->type = Token::TK_IS;
	}
	else if (strcmp(this->value, "NOT") == 0) {
		this->type = Token::TK_NOT;
	}
	else if (strcmp(this->value, "NULL") == 0) {
		this->type = Token::TK_NULL;
	}
	else if (strcmp(this->value, "AND") == 0) {
		this->type = Token::TK_AND;
	}
	else if (strcmp(this->value, "OR") == 0) {
		this->type = Token::TK_OR;
	}
}

void Token::strRemoveQuote() {
	char *cur = this->value;
	while (*cur != '\0') {
		*cur = *(cur + 1);
		cur++;
	}
	*(cur - 2) = '\0';
}