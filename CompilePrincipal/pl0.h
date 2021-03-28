/*
 * PL/0 complier program for win32 platform (implemented in C)
 *
 * The program has been test on Visual C++ 6.0,  Visual C++.NET and
 * Visual C++.NET 2003,  on Win98,  WinNT,  Win2000,  WinXP and Win2003
 *
 */

typedef enum {
    false,
    true
} bool;

/* new! str storage overflow */
#define strmax 32	/* new ! �����������С */
#define norw 20     /* �ؼ��ָ��� */
#define txmax 100   /* ���ֱ����� */
#define nmax 14     /* number�����λ�� */
#define al 80       /* ���ŵ���󳤶� */
#define amax 2047   /* ��ַ�Ͻ�*/
#define levmax 3    /* ����������Ƕ���������� [0,  levmax]*/
#define cxmax 500   /* ��������������� */

/* ���� */
enum symbol {// add new sym
    nul,         ident,     number,     plus,      minus,
    times,       slash,     oddsym,     eql,       neq,
    lss,         leq,       gtr,        geq,       lparen,
    rparen,      comma,     semicolon,  period,    becomes,
    beginsym,    endsym,    ifsym,      thensym,   whilesym,
    writesym,    readsym,   dosym,      callsym,   constsym,
    varsym,      procsym,	quotation,  dvarsym,   dnumber,
	breaksym,	 forsym,	delsym,		arraysym,  newsym,
	lspsym,		 rspsym,    tuplesym,	colon
};
#define symnum 44

/* ���ֱ��е����� */
enum object {
    constant,
    variable,
    procedur,
    dvariable, //new!
    array,     //new!
    tuple	   //new!
};

/* ��������� */
enum fct {
    lit,     opr,     lod,
    sto,     cal,     inte, 
    jmp,     jpc,	  
	spt,/*new! ��׼����� */
    dli,/*new! ȡ��������ջ�� */
    stoa/*new! ���ڴ��޸�����ֵ */
};

// gen(spt,0,n):����������еĵ�n�� 


#define fctnum 11 

/* ���������ṹ */
/* new! �����Ӷ��ڸ������Ĵ��� */ 
struct instruction
{
    enum fct f; /* ���������ָ�� */
    int l;      /* ���ò���������Ĳ�β� */
    int a;      /* ����f�Ĳ�ͬ����ͬ */
    double d;   /* new ! �������� */
};
int LINE_NUM = 0; /* new! ��¼��ǰ�����Ӧ��Դ�ļ����� */
FILE* fas;  /* ������ֱ� */
FILE* fa;   /* ������������ */
FILE* fa1;  /* ���Դ�ļ�������ж�Ӧ���׵�ַ */
FILE* fa2;  /* ������ */
bool listswitch;    /* ��ʾ������������ */
bool tableswitch;   /* ��ʾ���ֱ���� */
char ch;            /* ��ȡ�ַ��Ļ�������getch ʹ�� */
enum symbol sym;    /* ��ǰ�ķ��� */
char id[al+1];      /* ��ǰident, �����һ���ֽ����ڴ��0 */
int num;            /* ��ǰnumber */
double dnum;			/* new ! ��ǰ�ĸ����� */
int cc, ll;          /* getchʹ�õļ�������cc��ʾ��ǰ�ַ�(ch)��λ�� */
int cx;             /* ���������ָ��, ȡֵ��Χ[0, cxmax-1]*/
char line[81];      /* ��ȡ�л����� */
char a[al+1];       /* ��ʱ����, �����һ���ֽ����ڴ��0 */
struct instruction code[cxmax]; /* ����������������� */
char word[norw][al];        /* ������ */
enum symbol wsym[norw];     /* �����ֶ�Ӧ�ķ���ֵ */
enum symbol ssym[256];      /* ���ַ��ķ���ֵ */
char mnemonic[fctnum][5];   /* ���������ָ������ */
bool declbegsys[symnum];    /* ��ʾ������ʼ�ķ��ż��� */
bool statbegsys[symnum];    /* ��ʾ��俪ʼ�ķ��ż��� */
bool facbegsys[symnum];     /* ��ʾ���ӿ�ʼ�ķ��ż��� */

/* ���ֱ�ṹ */
struct tablestruct
{
    char name[al];      /* ���� */
    enum object kind;   /* ���ͣ�const, var, array or procedure */
    double val;            /* ��ֵ����constʹ�� */
    double dval;		/* new ! ��constʹ�� */ 
    int level;          /* �����㣬��const��ʹ�� */
    int adr;            /* ��ַ����const��ʹ�� */
    int size;           /* ��Ҫ������������ռ�, ��procedureʹ�� */
    int bottom;			/* new ! Ԫ���½磬Ҳ��heap�еĻ���ַ*/
    int upper; 			/* new ! Ԫ���Ͻ磬����bottom-upper=���ݸ���*/
};

struct tablestruct table[txmax]; /* ���ֱ� */

/*new!�½�Ԫ�����ݴ洢��*/
double heap[1024]={0.0}; 
int heapState[1024]={0}; 

FILE* fin;
FILE* fout;
char fname[al];
int err; /* ��������� */

#define strmax 32 
char str[32][32];   /* ����ַ� */
int nowstr = 0;		/* ��¼��ʽ��������ַ������� */ 
/* �������лᷢ��fatal errorʱ������-1��֪�������ĺ����������˳����� */
#define getsymdo                      if(-1 == getsym()) return -1
#define getchdo                       if(-1 == getch()) return -1
#define testdo(a, b, c)               if(-1 == test(a, b, c)) return -1
#define gendo(a, b, c, d)             if(-1 == gen(a, b, c, d)) return -1
#define expressiondo(a, b, c)         if(-1 == expression(a, b, c)) return -1
#define factordo(a, b, c)             if(-1 == factor(a, b, c)) return -1
#define termdo(a, b, c)               if(-1 == term(a, b, c)) return -1
#define conditiondo(a, b, c)          if(-1 == condition(a, b, c)) return -1
#define statementdo(a, b, c)          if(-1 == statement(a, b, c)) return -1
#define constdeclarationdo(a, b, c)   if(-1 == constdeclaration(a, b, c)) return -1
#define vardeclarationdo(a, b, c)     if(-1 == vardeclaration(a, b, c)) return -1
/* new ! */
#define dvardeclarationdo(a, b, c)     if(-1 == dvardeclaration(a, b, c)) return -1
#define arraydeclarationdo(a, b, c)    if(-1 == arraydeclaration(a, b, c)) return -1
#define tupledeclarationdo(a, b, c)    if(-1 == tupledeclaration(a, b, c)) return -1
void error(int n);
int getsym();
int getch();
void init();
int gen(enum fct x, int y, int z,double d);
int test(bool* s1, bool* s2, int n);
int inset(int e, bool* s);
int addset(bool* sr, bool* s1, bool* s2, int n);
int subset(bool* sr, bool* s1, bool* s2, int n);
int mulset(bool* sr, bool* s1, bool* s2, int n);
int block(int lev, int tx, bool* fsys);
void interpret();
int factor(bool* fsys, int* ptx, int lev);
int term(bool* fsys, int* ptx, int lev);
int condition(bool* fsys, int* ptx, int lev);
int expression(bool* fsys, int* ptx, int lev);
int statement(bool* fsys, int* ptx, int lev);
void listcode(int cx0);
int vardeclaration(int* ptx, int lev, int* pdx);
int constdeclaration(int* ptx, int lev, int* pdx);
int arraydeclaration(int* ptx, int lev, int* pdx);
int position(char* idt, int tx);
int enter(enum object k, int* ptx, int lev, int* pdx);
int base(int l, double* s, int b);
void showHeapFree();
int findFreeStart(int len);
