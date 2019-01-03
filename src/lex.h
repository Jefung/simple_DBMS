// comment: 词法token定义
class Token {
private:
	int type;
	char value[100];

public:
	const static int TK_CREATE = 10001, TK_TABLE = 10002, TK_DROP = 10003,
		TK_INSERT = 10004, TK_INTO = 10005, TK_VALUE = 10006, TK_DELETE = 10007,
		TK_FROM = 10008, TK_WHERE = 10009, TK_UPDATE = 10010, TK_SET = 10011,
		TK_INDEX = 10012, TK_ON = 10013, TK_SELECT = 10014, TK_INT = 10015, TK_CHAR = 10016,
		//TYPE
		NUM = 10036, STR = 10037, ID = 10038,
		//CONDITION
		TK_IS = 10017, TK_NULL = 10018, TK_NOT = 10019, TK_AND = 10020,
		TK_OR = 10021, TK_GTR = 10022, TK_LSS = 10023, TK_EQU = 10024,
		TK_LEQ = 10025, TK_GEQ = 10026,
		//CALCULATE
		TK_ADD = 10027, TK_SUB = 10028, TK_MUL = 10029, TK_DIV = 10030,
		//SYMBOL
		TK_LP = 10031, TK_RP = 10032, TK_COMMA = 10033, TK_PERIOD=10034, TK_SEMICOLON = 10035;

	int getType();
	void setType(int);
	char* getValue();
	void setValue(char*);

	void toUpperCase();
	void idAutoType();
	void strRemoveQuote();
};