/*
 * PL/0 complier program for win32 platform (implemented in C)
 *
 * The program has been test on Visual C++ 6.0, Visual C++.NET and
 * Visual C++.NET 2003, on Win98, WinNT, Win2000, WinXP and Win2003
 *
 * 使用方法：
 * 运行后输入PL/0源程序文件?
 * 回答是否输出虚拟机代码
 * 回答是否输出名字表
 * fa.tmp输出虚拟机代码
 * fa1.tmp输出源文件及其各行对应的首地址
 * fa2.tmp输出结?
 * fas.tmp输出名字表
 */

#include <stdio.h>

#include "pl0.h"
#include "string.h"

/* 解释执行时使用的栈 */
#define stacksize 500


int main()
{
	bool nxtlev[symnum];

//	printf("Input pl/0 file?   ");
//	scanf("%s", fname);     /* 输入文件名 */
	char temp[] = "MonkeyPeach.PL0";
	strcpy(fname,temp);
	fin = fopen(fname, "r");

	if (fin)//MonkeyPeach.PL0 
	{
		//printf("List object code?(Y/N)");   /* 是否输出虚拟机代码 */
		//scanf("%s", fname);
		fname[0] = 'n'; 
		listswitch = 0;

		//printf("List symbol table?(Y/N)");  /* 是否输出名字表 */
		//scanf("%s", fname);
		tableswitch = 1;

		fa1 = fopen("fa1.tmp", "w");
		fprintf(fa1,"Input pl/0 file?   ");
		fprintf(fa1,"%s\n",fname);

		init();     /* 初始化 */

		err = 0;
		cc = cx = ll = 0;
		ch = ' ';

		if(-1 != getsym())
		{
			fa = fopen("fa.tmp", "w");
			fas = fopen("fas.tmp", "w");
			addset(nxtlev, declbegsys, statbegsys, symnum);
			nxtlev[period] = true;

			if(-1 == block(0, 0, nxtlev))   /* 调用编译程序 */
			{
				fclose(fa);
				fclose(fa1);
				fclose(fas);
				fclose(fin);
				printf("\n");
				return 0;
			}
			fclose(fa);
			fclose(fa1);
			fclose(fas);

			if (sym != period)
			{
				error(9);
			}

			if (err == 0)
			{
				fa2 = fopen("fa2.tmp", "w");
				interpret();    /* 调用解释执行程序 */
				fclose(fa2);
			}
			else
			{
				printf("Errors in pl/0 program");
			}
		}

		fclose(fin);
	}
	else
	{
		printf("Can't open file!\n");
	}

	printf("\n");
	return 0;
}

/*
* 初始化
*/
void init()
{
	int i;
	/* 设置单字符符号 */
	for (i=0; i<=255; i++)
	{
		ssym[i] = nul;
	}
	ssym['+'] = plus;
	ssym['-'] = minus;
	ssym['*'] = times;
	ssym['/'] = slash;
	ssym['('] = lparen;
	ssym[')'] = rparen;
	ssym['='] = eql;
	ssym[','] = comma;
	ssym['.'] = period;
	ssym['#'] = neq;
	ssym[';'] = semicolon;
	/* new */
	ssym['"'] = quotation; 
	ssym['['] = lspsym;
	ssym[']'] = rspsym; 

	/* 设置保留字名字,按照字母顺序，便于折半查找 */
	strcpy(&(word[0][0]), "begin");
	strcpy(&(word[1][0]), "call");
	strcpy(&(word[2][0]), "const");
	strcpy(&(word[3][0]), "do");
	strcpy(&(word[4][0]), "end");
	strcpy(&(word[5][0]), "if");
	strcpy(&(word[6][0]), "odd");
	strcpy(&(word[7][0]), "procedure");
	strcpy(&(word[8][0]), "read");
	strcpy(&(word[9][0]), "then");
	strcpy(&(word[10][0]), "var");
	strcpy(&(word[11][0]), "while");
	strcpy(&(word[12][0]), "write");
	/* new ! */
	strcpy(&(word[13][0]), "dvar");
	strcpy(&(word[14][0]), "break");
	strcpy(&(word[15][0]), "for");
	strcpy(&(word[16][0]), "del");
	strcpy(&(word[17][0]), "arr");
	strcpy(&(word[18][0]), "new");
	strcpy(&(word[19][0]), "tuple");

	/* 设置保留字符号 */
	wsym[0] = beginsym;
	wsym[1] = callsym;
	wsym[2] = constsym;
	wsym[3] = dosym;
	wsym[4] = endsym;
	wsym[5] = ifsym;
	wsym[6] = oddsym;
	wsym[7] = procsym;
	wsym[8] = readsym;
	wsym[9] = thensym;
	wsym[10] = varsym;
	wsym[11] = whilesym;
	wsym[12] = writesym;
	/* new ! */
	wsym[13] = dvarsym;
	wsym[14] = breaksym;
	wsym[15] = forsym;
	wsym[16] = delsym;
	wsym[17] = arraysym;
	wsym[18] = newsym;
	wsym[19] = tuplesym;
	/* 设置指令名称 */
	strcpy(&(mnemonic[lit][0]), "lit");
	strcpy(&(mnemonic[opr][0]), "opr");
	strcpy(&(mnemonic[lod][0]), "lod");
	strcpy(&(mnemonic[sto][0]), "sto");
	strcpy(&(mnemonic[cal][0]), "cal");
	strcpy(&(mnemonic[inte][0]),"int");
	strcpy(&(mnemonic[jmp][0]), "jmp");
	strcpy(&(mnemonic[jpc][0]), "jpc");
	/* new ! */
	strcpy(&(mnemonic[spt][0]), "spt");
    strcpy(&(mnemonic[dli][0]), "dli");
    strcpy(&(mnemonic[stoa][0]), "stoa");
    
	/* 设置符号集 */
	for (i=0; i<symnum; i++)
	{
		declbegsys[i] = false;
		statbegsys[i] = false;
		facbegsys[i] = false;
	}

	/* 设置声明开始符号集 */
	declbegsys[constsym] = true;
	declbegsys[varsym] = true;
	declbegsys[procsym] = true;
	/* new ！ */
	declbegsys[dvarsym] = true;
	declbegsys[arraysym] = true;  
	declbegsys[tuplesym] = true;  
	/* 设置语句开始符号集 */
	statbegsys[beginsym] = true;
	statbegsys[callsym] = true;
	statbegsys[ifsym] = true;
	statbegsys[whilesym] = true;
	statbegsys[readsym] = true;
	statbegsys[writesym] = true;

	/* 设置因子开始符号集 */
	facbegsys[ident] = true;
	facbegsys[number] = true;
	facbegsys[lparen] = true;
	/* new ! */
	facbegsys[dnumber] = true;
}

/*
* 用数组实现集合的集合运算
*/
int inset(int e, bool* s)
{
	return s[e];
}

int addset(bool* sr, bool* s1, bool* s2, int n)
{
	int i;
	for (i=0; i<n; i++)
	{
		sr[i] = s1[i]||s2[i];
	}
	return 0;
}

int subset(bool* sr, bool* s1, bool* s2, int n)
{
	int i;
	for (i=0; i<n; i++)
	{
		sr[i] = s1[i]&&(!s2[i]);
	}
	return 0;
}

int mulset(bool* sr, bool* s1, bool* s2, int n)
{
	int i;
	for (i=0; i<n; i++)
	{
		sr[i] = s1[i]&&s2[i];
	}
	return 0;
}

/*
*   出错处理，打印出错位置和错误编码
*/
void error(int n)
{
	char space[81];
	memset(space,32,81);
	space[cc-1]=0; //出错时当前符号已经读完，所以cc-1
	//printf("****%s!%d ", space, n);
	fprintf(fa1,"****%s!%d ", space, n);
	/* new! 增加错误处理提示 */
	switch(n){
		case 1:printf("第%d行：=不为:=\n",LINE_NUM);break;
		case 2:printf("第%d行：常量=后应为数字\n",LINE_NUM);break;
		case 3:printf("第%d行：常量说明标识后应是=\n",LINE_NUM);break;
		case 4:printf("第%d行：const、var、dvar、proc后应是标识\n",LINE_NUM);break;
		case 5:printf("第%d行：缺少逗号\n",LINE_NUM);break;
		case 9:printf("第%d行：缺少句号\n",LINE_NUM);break;
		case 10:printf("第%d行：缺少分号\n",LINE_NUM);break;
		case 11:printf("第%d行：变量未找到\n",LINE_NUM);break;
		case 12:printf("第%d行：赋值语句格式错误\n",LINE_NUM);break;
		case 13:printf("第%d行：没有检测到赋值符号\n",LINE_NUM);break;
		case 14:printf("第%d行：call后应为标识符\n",LINE_NUM);break; 
		case 15:printf("第%d行：call后标识符应为过程\n",LINE_NUM);break; 
		case 16:printf("第%d行：缺少then\n",LINE_NUM);break;
		case 17:printf("第%d行：缺少end或分号%d\n",LINE_NUM);break; 
		case 18:printf("第%d行：缺少do\n",LINE_NUM);break; 
		case 19:printf("第%d行：del后缺少标志符\n",LINE_NUM);break; 
		case 20:printf("第%d行：逻辑表达式缺少逻辑运算符\n",LINE_NUM);break;
		case 21:printf("第%d行：不能为过程\n",LINE_NUM);break; 
		case 22:printf("第%d行：缺少右括号\n",LINE_NUM);break; 
		case 23:printf("第%d行：del后标识符类型应为数组tuple\n",LINE_NUM);break; 
		case 24:printf("第%d行：array数组已为空，无需delete\n",LINE_NUM);break; 
		case 25:printf("第%d行：array不可重复分配空间\n",LINE_NUM);break; 
		case 26:printf("第%d行：array分配空间缺少'['\n",LINE_NUM);break; 
		case 27:printf("第%d行：array上界未给定\n",LINE_NUM);break; 
		case 28:printf("第%d行：array分配空间缺少']'\n",LINE_NUM);break; 
		case 29:printf("第%d行：array下界未给定\n",LINE_NUM);break; 
		case 30:printf("第%d行：整型过大溢出\n",LINE_NUM);break;
		case 31:printf("第%d行：数越界\n",LINE_NUM);break;
		case 32:printf("第%d行：read参数表的标识符不是变量, 或嵌套层数过多\n",LINE_NUM);break;
		case 33:printf("第%d行：格式错误，应是右括号\n",LINE_NUM);break;
		case 34:printf("第%d行：格式错误，应是左括号\n",LINE_NUM);break;
		case 35:printf("第%d行：read中应是声明过的变量名\n",LINE_NUM);break;
		case 36:printf("第%d行：数组下标越界",LINE_NUM);break;
		case 37:printf("第%d行：tuple已为空，无需delete\n",LINE_NUM);break;
		case 38:printf("第%d行：tuple不可重复分配空间\n",LINE_NUM);break;
		case 39:printf("第%d行：tuple分配空间缺少'('\n",LINE_NUM);break;
		case 40:printf("第%d行：tuple空间大小未指定\n",LINE_NUM);break;
		case 41:printf("第%d行：tuple分配空间缺少')'\n",LINE_NUM);break;
		case 42:printf("第%d行：tuple下标越界\n",LINE_NUM);break;
		case 43:printf("第%d行：缺少冒号\n",LINE_NUM);break;
		case 44:printf("第%d行：注释语句错误\n",LINE_NUM);break;
	}err++;
}

/*
* 漏掉空格，读取一个字符。
*
* 每次读一行，存入line缓冲区，line被getsym取空后再读一行
*
* 被函数getsym调用。
*/
int getch()
{
	if (cc == ll)
	{
		if (feof(fin))
		{
			printf("program incomplete");
			return -1;
		}
		ll=0;
		cc=0;
		//printf("%d ", cx);
		fprintf(fa1,"%d ", cx);
		ch = ' ';
		while (ch != 10)//ch == 10 为换行符 
		{
			
			//fscanf(fin,"%c", &ch)
			//richard
			if (EOF == fscanf(fin,"%c", &ch))	// EOF 定义为 -1 
			{
				line[ll] = 0;					// 为line的最后添加空字符 
				break;
			}
			
			//end richard
			//printf("%c", ch);
			fprintf(fa1, "%c", ch);
			line[ll] = ch;
			ll++;
		}
		//printf("\n");
		fprintf(fa1, "\n");
		/* new ! LINE_NUM */
		LINE_NUM++;
	}
	ch = line[cc];
	cc++;
	return 0;
}

/*
* 词法分析，获取一个符号
*/
int getsym()
{
	int i,j,k;

	/* the original version lacks "\r", thanks to foolevery */
	while (ch==' ' || ch==10 || ch==13 || ch==9)  /* 忽略空格、换行、回车和TAB */
	{
		getchdo;
	}
	// new ! 增加大写字母判断 
	if ((ch>='a' && ch<='z')||(ch>='A' && ch<='Z'))
	{           /* 名字或保留字以字母开头 */
		k = 0;
		do {
			if(k<al)
			{
				a[k] = ch;
				k++;
			}
			getchdo;
		} while (ch>='a' && ch<='z' || ch>='0' && ch<='9');
		a[k] = 0;
		strcpy(id, a);
		/* 二分法搜索当前符号是否为保留字 */
		/*i = 0;
		j = norw-1;
		do {    
			k = (i+j)/2;
			if (strcmp(id,word[k]) <= 0)
			{
				j = k - 1;
			}
			if (strcmp(id,word[k]) >= 0)
			{
				i = k + 1;
			}
		} while (i <= j);*/
		/* 遍历法搜索当前符号是否为保留字 */
		i = 0;
		while(strcmp(id,word[i])!=0 && i < norw)i++;
		
		if (i < norw)
		{
			sym = wsym[i];
		}
		else
		{
			sym = ident; /* 搜索失败则，是名字或数字 */
		}
	}
	else
	{
		if (ch>='0' && ch<='9')
		{           /* 检测是否为数字：以0..9开头 */
			k = 0;
			num = 0;
			sym = number;
			do {
				num = 10*num + ch - '0';
				k++;
				getchdo;
			} while (ch>='0' && ch<='9'); /* 获取数字的值 */
			
			if(ch == '.'){				  /* new ! 增加小数点判断 */
				sym = dnumber;		  /* new ! 转化类型为小数 */
				getchdo;//printf("THIS IS A DNUM %c\n",ch);
				dnum = num;//printf("%lf\n",dnum); 
				//MonkeyPeach.PL0 
				double div = 1;
				do {
					dnum = 10*dnum + ch - '0';
					k++;
					div*=10;
					getchdo;//printf("THIS IS A DNUM %c\n",ch);
				}while (ch>='0' && ch<='9'); /* 获取数字的值 */
				dnum/=div;
				//printf("THIS IS A DNUM %lf\n",dnum);
			} 
			
			k--;
			if (k > nmax)
			{
				error(30);
			}
		}
		else
		{
			if (ch == ':')      /* 检测赋值符号 */
			{
				getchdo;
				if (ch == '=')
				{
					sym = becomes;
					getchdo;
				}
				else
				{
					sym = colon;  /*new 添加冒号的识别*/
					//sym = nul;  /* 不能识别的符号 */
				}
			}
			else
			{
				if (ch == '<')      /* 检测小于或小于等于符号 */
				{
					getchdo;
					if (ch == '=')
					{
						sym = leq;
						getchdo;
					}
					else
					{
						sym = lss;
					}
				}
				else
				{
					if (ch=='>')        /* 检测大于或大于等于符号 */
					{
						getchdo;
						if (ch == '=')
						{
							sym = geq;
							getchdo;
						}
						else
						{
							sym = gtr;
						}
					}
					else
					{	sym = ssym[ch];
						/* new 注释语句 */
						if(ch == '{'){getchdo;
							while(ch!='}'){
								getchdo;
							}
							getsymdo;
							return 0; 
						}
						     /* 当符号不满足上述条件时，全部按照单字符符号处理 */
						//getchdo;
						//richard
						
						
						if (sym != period)
						{
							getchdo;
						}
						//end richard
					}
				}
			}
		}
	}
	return 0;
}

/*
* 生成虚拟机代码
*
* x: instruction.f;
* y: instruction.l;
* z: instruction.a;
*/
/*new! 当涉及到double类型的数时，参数有可能为浮点数*/
int gen(enum fct x, int y, int z,double d)
{
	if (cx >= cxmax)
	{
		printf("Program too long"); /* 程序过长 */
		return -1;
	}
	code[cx].f = x;
	code[cx].l = y;
	code[cx].a = z;
	code[cx].d = d;
	cx++;
	return 0;
}


/*
* 测试当前符号是否合法
*
* 在某一部分（如一条语句，一个表达式）将要结束时时我们希望下一个符号属于某集?
* （该部分的后跟符号），test负责这项检测，并且负责当检测不通过时的补救措施，
* 程序在需要检测时指定当前需要的符号集合和补救用的集合（如之前未完成部分的后跟
* 符号），以及检测不通过时的错误号。
*
* s1:   我们需要的符号
* s2:   如果不是我们需要的，则需要一个补救用的集?
* n:    错误号
*/
int test(bool* s1, bool* s2, int n)
{
	if (!inset(sym, s1))
	{
		error(n);
		/* 当检测不通过时，不停获取符号，直到它属于需要的集合或补救的集合 */
		while ((!inset(sym,s1)) && (!inset(sym,s2)))
		{
			getsymdo;
		}
	}
	return 0;
}

/*
* 编译程序主?
*
* lev:    当前分程序所在层
* tx:     名字表当前尾指针
* fsys:   当前模块后跟符号集?
*/
int block(int lev, int tx, bool* fsys)
{
	int i;

	int dx;                 /* 名字分配到的相对地址 */
	int tx0;                /* 保留初始tx */
	int cx0;                /* 保留初始cx */
	bool nxtlev[symnum];    /* 在下级函数的参数中，符号集合均为值参，但由于使用数组实现，
							传递进来的是指针，为防止下级函数改变上级函数的集合，开辟新的空?
							传递给下级函数*/

	dx = 3;
	tx0 = tx;               /* 记录本层名字的初始位置 */
	table[tx].adr = cx;

	gendo(jmp, 0, 0,0);

	if (lev > levmax)
	{
		error(32);
	}

	do {

		if (sym == constsym)    /* 收到常量声明符号，开始处理常量声明 */
		{
			getsymdo;

			/* the original do...while(sym == ident) is problematic, thanks to calculous */
			/* do { */
			constdeclarationdo(&tx, lev, &dx);  /* dx的值会被constdeclaration改变，使用指针 */
			while (sym == comma)	// 若为逗号，说明const常量未分析完毕 
			{
				getsymdo;			// 取出const常量 
				constdeclarationdo(&tx, lev, &dx);	// 填写表 
			}
			if (sym == semicolon)	// 若为分号，说明常量以编译完成 
			{
				getsymdo;
			}
			else
			{
				error(5);   /*漏掉了逗号或者分号*/
			}
			/* } while (sym == ident); */
		}

		if (sym == varsym)      /* 收到变量声明符号，开始处理变量声明 */
		{
			getsymdo;

			/* the original do...while(sym == ident) is problematic, thanks to calculous */
			/* do {  */
			vardeclarationdo(&tx, lev, &dx);
			while (sym == comma)
			{
				getsymdo;
				vardeclarationdo(&tx, lev, &dx);
			}
			if (sym == semicolon)
			{
				getsymdo;
			}
			else
			{
				error(5);
			}
			/* } while (sym == ident);  */
		}
		
		if (sym == dvarsym)     /* new ！收到浮点变量声明符号，开始处理变量声明 */
		{
			getsymdo;			//读取字符 
			dvardeclarationdo(&tx, lev, &dx);
			while (sym == comma)//判断是否有多个浮点数 
			{
				getsymdo;		//读取字符，并全部声明 
				dvardeclarationdo(&tx, lev, &dx);
			}
			if (sym == semicolon)//判断是否结束 
			{
				getsymdo;
			}
			else
			{
				error(5);
			}
			/* } while (sym == ident);  */
		}
		
		if (sym == arraysym)	/* new ！收到数组变量声明符号，开始处理变量声明 */
		{
			getsymdo;			//读取字符 
			arraydeclarationdo(&tx, lev, &dx);
			while (sym == comma)//循环判断多个变量 
			{
				getsymdo;		//读取字符，通过循环声明所有数组 
				arraydeclarationdo(&tx, lev, &dx);
			}
			if (sym == semicolon)//判断是否全部声明 
			{
				getsymdo;
			}
			else
			{
				error(5);
			}
			/* } while (sym == ident);  */
		}
		
		if (sym == tuplesym)	/* new ！收到元组变量声明符号，开始处理变量声明 */
		{
			getsymdo;			//读取字符	
			tupledeclarationdo(&tx, lev, &dx);
			while (sym == comma)//判断是否有多个元组 
			{
				getsymdo;		//读取字符，循环完成多次声明 
				tupledeclarationdo(&tx, lev, &dx);
			}
			if (sym == semicolon)//检测是否结束 
			{
				getsymdo;
			}
			else
			{
				error(5);
			}
			/* } while (sym == ident);  */
		}
		while (sym == procsym) /* 收到过程声明符号，开始处理过程声明 */
		{
			getsymdo;

			if (sym == ident)
			{
				enter(procedur, &tx, lev, &dx); /* 记录过程名字 */
				getsymdo;
			}
			else
			{
				error(4);   /* procedure后应为标识符 */
			}

			if (sym == semicolon)
			{
				getsymdo;
			}
			else
			{
				error(5);   /* 漏掉了分号 */
			}

			memcpy(nxtlev, fsys, sizeof(bool)*symnum);
			nxtlev[semicolon] = true;
			if (-1 == block(lev+1, tx, nxtlev))
			{
				return -1;  /* 递归调用 */
			}

			if(sym == semicolon)
			{
				getsymdo;
				memcpy(nxtlev, statbegsys, sizeof(bool)*symnum);
				nxtlev[ident] = true;
				nxtlev[procsym] = true;
				testdo(nxtlev, fsys, 6);
			}
			else
			{
				error(5);   /* 漏掉了分号 */
			}
		}
		memcpy(nxtlev, statbegsys, sizeof(bool)*symnum);
		nxtlev[ident] = true;
		testdo(nxtlev, declbegsys, 7);
	} while (inset(sym, declbegsys));   /* 直到没有声明符号 */

	code[table[tx0].adr].a = cx;    /* 开始生成当前过程代码 */
	table[tx0].adr = cx;            /* 当前过程代码地址 */
	table[tx0].size = dx;           /* 声明部分中每增加一条声明都会给dx增加1，声明部分已经结束，dx就是当前过程数据的size */
	cx0 = cx;
	gendo(inte, 0, dx,0);             /* 生成分配内存代码 */

	if (tableswitch)        /* 输出名字表 */
	{
		printf("TABLE:\n");
		if (tx0+1 > tx)
		{
			printf("    NULL\n");
		}
		for (i=tx0+1; i<=tx; i++)
		{
			switch (table[i].kind)
			{
			case constant:
				printf("%5d const %8s ", i, table[i].name);
				if(table[i].dval!=0)
					printf("dval=%lf\n", table[i].dval);
				else printf("val=%d\n", table[i].val);
					
				fprintf(fas, "%5d const %8s ", i, table[i].name);
				if(table[i].dval!=0)
					fprintf(fas, "dval=%lf\n", table[i].dval);
				else fprintf(fas, "val=%d\n", table[i].val);
				break;
			case variable:
				printf("%5d var   %8s ", i, table[i].name);
				printf("lev=%d addr=%d\n", table[i].level, table[i].adr);
				fprintf(fas, "%5d var   %8s ", i, table[i].name);
				fprintf(fas, "lev=%d addr=%d\n", table[i].level, table[i].adr);
				break;
			case dvariable:
				printf("%5d dvar  %8s ", i, table[i].name);
				printf("lev=%d addr=%d\n", table[i].level, table[i].adr);
				fprintf(fas, "%5d dvar  %8s ", i, table[i].name);
				fprintf(fas, "lev=%d addr=%d\n", table[i].level, table[i].adr);
				break;
			case procedur:
				printf("%5d proc  %8s ", i, table[i].name);
				printf("lev=%d addr=%d size=%d\n", table[i].level, table[i].adr, table[i].size);
				fprintf(fas,"%5d proc  %8s ", i, table[i].name);
				fprintf(fas,"lev=%d addr=%d size=%d\n", table[i].level, table[i].adr, table[i].size);
				break;
			case array:
				printf("%5d array %8s ", i, table[i].name);
				printf("lev=%d addr=%d\n", table[i].level, table[i].adr);
				fprintf(fas, "%5d array %8s ", i, table[i].name);
				fprintf(fas, "lev=%d addr=%d\n", table[i].level, table[i].adr);
				break;
			case tuple:
				printf("%5d tuple %8s ", i, table[i].name);
				printf("lev=%d addr=%d\n", table[i].level, table[i].adr);
				fprintf(fas, "%5d tuple %8s ", i, table[i].name);
				fprintf(fas, "lev=%d addr=%d\n", table[i].level, table[i].adr);
				break;
			}
		}
		printf("\n");
	}

	/* 语句后跟符号为分号或end */
	memcpy(nxtlev, fsys, sizeof(bool)*symnum);  /* 每个后跟符号集和都包含上层后跟符号集和，以便补救 */
	nxtlev[semicolon] = true;
	nxtlev[endsym] = true;
	statementdo(nxtlev, &tx, lev);
	gendo(opr, 0, 0,0);                       /* 每个过程出口都要使用的释放数据段指令 */
	memset(nxtlev, 0, sizeof(bool)*symnum); /*分程序没有补救集合 */
	testdo(fsys, nxtlev, 8);                /* 检测后跟符号正确性 */
	listcode(cx0);                          /* 输出代码 */
	return 0;
}

/*
* 在名字表中加入一项
*
* k:      名字种类const,dvar,var or procedure
* ptx:    名字表尾指针的指针，为了可以改变名字表尾指针的值
* lev:    名字所在的层次,，以后所有的lev都是这样
* pdx:    dx为当前应分配的变量的相对地址，分配后要增加1
*/
int enter(enum object k, int* ptx, int lev, int* pdx)
{
	(*ptx)++;
	strcpy(table[(*ptx)].name, id); /* 全局变量id中已存有当前名字的名字 */
	table[(*ptx)].kind = k;
	switch (k)
	{
	case constant:  /* 常量名字 */
		if (num > amax)
		{
			error(31);  /* 数越界 */
			num = 0;
		}
		if(sym == number)
			table[(*ptx)].val = num;
		if(sym == dnumber) /* new ! 新增浮点型常量*/
			table[(*ptx)].dval = dnum; 
		break;
	case variable:  /* 变量名字 */
		table[(*ptx)].level = lev;
		table[(*ptx)].adr = (*pdx);
		(*pdx)++;
		break;
	case procedur:  /*　过程名字　*/
		table[(*ptx)].level = lev;
		break;
	case dvariable:  /* new ! 浮点数名字 */
		table[(*ptx)].level = lev;	//记录层级
		table[(*ptx)].adr = (*pdx);	//记录地址
		(*pdx)++;					//修改名字表中的地址（自增）
		break;
	case array:  /* new ! 数组名字 */
		table[(*ptx)].level = lev;	//记录层级
		table[(*ptx)].adr = (*pdx);	//记录地址
		getsymdo;					//读取字符
		if(sym == lspsym){			//进行语法判断
			getsymdo;				//读取字符
			if(sym == number){
				getsymdo;			//读取字符
				table[(*ptx)].bottom = 0;  	//设定下界为0 
				table[(*ptx)].upper = num;	//上界取决于初始化时声明的大小 
				int temp = num;
				char oid[al+1],tempid[al+1]={' '};
				strcpy(oid,id);		//创建临时变量保存读取到的id信息 
				strcpy(id,tempid);
				(*pdx)++;			//修改名字表中的地址（自增） 
				while(temp){		//将按照数组初始化空间的大小进行分配 
					enter(dvariable,ptx,lev,pdx);//按照浮点变量进行创建 
					temp--;
				}
				strcpy(id,oid);		//保存读取到的id信息 
				if(sym == rspsym){
					/* pass, no proc need to be done */
				}
				else error(28);		//错误处理 
			}
			else error(27);			//错误处理 
		}
		else error(26);				//错误处理 
		break;
	case tuple:  /* new ! 数组名字 */
		table[(*ptx)].level = lev;	//记录层级 
		table[(*ptx)].adr = (*pdx); //记录地址 
		getsymdo;					//读取字符 
		if(sym==lparen){			//进行语法判断 
			getsymdo;
			if(sym==number){		//首先应该声明元组大小 
				getsymdo;
				if(sym==colon){		//语法规范为冒号 
					int freestart = findFreeStart(num);	//找出堆中连续的空闲区 
					table[(*ptx)].bottom = freestart;  	//根据连续空闲区地址分配给元组 
					table[(*ptx)].upper = freestart+num;//同时设定上界 
					getsymdo;
					int pos = 0;
					while(sym==number){	// 之后需要以此对于元组中的值进行初始化 
						heap[table[(*ptx)].bottom+pos++]=num;//修改堆中对应内存的值 
						getsymdo;
						if(sym == comma){
							// pass 
						}
						else break;getsymdo;
					}
					if(sym == rparen){
						// pass
					}
					else error(41);	// 错误处理 
				}else error(43);	// 错误处理 
				
			}else error(40);		// 错误处理 
		}
		else error(39); 			// 错误处理 
		(*pdx)++;					// 最后修改名字表中的表头变量地址 
		break;
	}
}

/*
* 查找名字的位置.
* 找到则返回在名字表中的位置,否则返回0.
*
* idt:    要查找的名字
* tx:     当前名字表尾指针
*/
int position(char* idt, int tx)
{
	int i;
	strcpy(table[0].name, idt);
	i = tx;
	while (strcmp(table[i].name, idt) != 0)
	{
		i--;
	}
	return i;
}

/*
* 常量声明处理
*/
int constdeclaration(int* ptx, int lev, int* pdx)
{	// sym == ident 表明不是保留字，是数字或名字 
	if (sym == ident) /* 常量说明标识后应是= */
	{
		getsymdo;
		if (sym==eql || sym==becomes)
		{
			if (sym == becomes)
			{
				error(1);   /* 把=写成了:= */
			}
			getsymdo;
			if (sym == number)
			{
				enter(constant, ptx, lev, pdx);
				getsymdo;
			}
			else if(sym == dnumber){/* new ！新增浮点型常量 */
				enter(constant, ptx, lev, pdx);
				getsymdo;
			}
			else
			{
				error(2);   /* 常量说明=后应是数字 */
			}
		}
		else
		{
			error(3);   /* 常量说明标识后应是= */
		}
	}
	else
	{
		error(4);   /* const后应是标识 */
	}
	return 0;
}

/*
* 变量声明处理
*/
int vardeclaration(int* ptx,int lev,int* pdx)
{
	if (sym == ident)
	{
		enter(variable, ptx, lev, pdx); // 填写名字表
		getsymdo;
	}
	else
	{
		error(4);   /* var后应是标识 */
	}
	return 0;
}

/* new ! 
* 浮点数声明处理
*/
int dvardeclaration(int* ptx,int lev,int* pdx)
{
	if (sym == ident)
	{
		enter(dvariable, ptx, lev, pdx); // 填写名字表
		getsymdo;
	}
	else
	{
		error(4);   /* dvar后应是标识 */
	}
	return 0;
}
/* new ! 
* 数组声明处理
*/
int arraydeclaration(int* ptx, int lev, int* pdx){
	if (sym == ident)
	{
		enter(array, ptx, lev, pdx); // 填写名字表
		getsymdo;
	}
	else
	{
		error(4);   /* arr后应是标识 */
	}
	return 0;
}
/* new ! 
* 元组声明处理
*/
int tupledeclaration(int* ptx, int lev, int* pdx){
	if (sym == ident)
	{
		enter(tuple, ptx, lev, pdx); // 填写名字表
		getsymdo;
	}
	else
	{
		error(4);   /* tuple后应是标识 */
	}
	return 0;
}
/*
* 输出目标代码清单
*/
void listcode(int cx0)
{
	int i;
	if (listswitch)
	{
		for (i=cx0; i<cx; i++)
		{
			printf("%d %s %d %d\n", i, mnemonic[code[i].f], code[i].l, code[i].a);
			fprintf(fa,"%d %s %d %d\n", i, mnemonic[code[i].f], code[i].l, code[i].a);
		}
	}
}

/*
* 语句处理
*/
int statement(bool* fsys, int* ptx, int lev)
{
	int i, cx1, cx2;
	bool nxtlev[symnum];

	if (sym == ident)   /* 准备按照赋值语句处理 */
	{
		i = position(id, *ptx);
		if (i == 0)
		{
			error(11);  /* 变量未找到 */
		}
		else
		{
			/* new ! 增加对于浮点类型的判断*/
			if(table[i].kind != variable && table[i].kind != dvariable && table[i].kind != array)
			{
				error(12);  /* 赋值语句格式错误 */
				i = 0;
			}
			else
			{	/*new operation on memory of array*/
				int pos ;
				if(table[i].kind == array){
					getsymdo;
					if(sym == lspsym){
						getsymdo;
						if(sym == number){
							getsymdo;
							pos = num;
							if(pos <= table[i].upper - table[i].bottom){
								//gendo(stoa, pos, table[pos_in_table].bottom, 0);   
							}
							else error(36);
							if(sym != rspsym){
								error(7);
							}
						}
						else error(8);
					}
					else error(6);
				}
				
				getsymdo;
				if(sym == becomes)
				{
					getsymdo;
				}
				else
				{
					error(13);  /* 没有检测到赋值符号 */
				}
				memcpy(nxtlev, fsys, sizeof(bool)*symnum);
				expressiondo(nxtlev, ptx, lev); /* 处理赋值符号右侧表达式 */
				if(i != 0 && table[i].kind!=array)
				{
					/* expression将执行一系列指令，但最终结果将会保存在栈顶，执行sto命令完成赋值 */
					gendo(sto, lev-table[i].level, table[i].adr,0);
				}
				if(i != 0 && table[i].kind==array){
					gendo(sto, lev-table[i].level, table[i+pos].adr,0);
				}
			}
		}//if (i == 0)
	}
	else
	{
		if (sym == readsym) /* 准备按照read语句处理 */
		{
			getsymdo;
			if (sym != lparen)
			{
				error(34);  /* 格式错误，应是左括号 */
			}
			else
			{
				do {
					getsymdo;	// 读取字符 
					/*增加格式化输入*/
					if(sym == quotation){//判断是否为引用 
						// write("count=",count," ans=?",ans);
						// output: count=$count ans=$ans
						char tempstr[32];	//设定缓冲区 
						int tspos = 0; 		//设定缓冲区指针 
						while(ch!='"'){		//判断引用结束 
							//printf("%c",ch);//调试时使用 
							tempstr[tspos++]=ch;//将字符保存到缓冲区 
							getchdo;		//读取字符 
						}
						tempstr[tspos]='\0';//必须加上终止符不然输出乱码
						getchdo; 			//读取字符 
						strcpy(str[nowstr],tempstr);// 将读取到的字符串存入缓冲区
						getsymdo;			//读取字符
						nowstr++; /* new! 标准化输出字符串+1 */
						if(nowstr > 32){	//错误处理，判断缓冲区是否溢出 
							error(1);		//错误处理函数 
						}
						gendo(spt, 0, nowstr-1,0); //生成缓冲区输出指令 
					}
					else if (sym == ident)
					{
						i = position(id, *ptx); /* 查找要读的变量 */
						if (i == 0)
						{
							error(35);  /* read()中应是声明过的变量名 */
						}
						else if (!(table[i].kind == variable || table[i].kind == dvariable))
						{
							error(32);	/* read()参数表的标识符不是变量, thanks to amd */
						}
						else
						{
							gendo(opr, 0, 16,0);  /* 生成输入指令，读取值到栈顶 */
							gendo(sto, lev-table[i].level, table[i].adr,0);   /* 储存到变量 */
						}
						getsymdo;
					}
					else
					{
						i=0;
					}

					

				} while (sym == comma); /* 一条read语句可读多个变量 */
			}
			if(sym != rparen)
			{
				error(33);  /* 格式错误，应是右括号 */
				while (!inset(sym, fsys))   /* 出错补救，直到收到上层函数的后跟符号 */
				{
					getsymdo;
				}
			}
			else
			{
				getsymdo;
			}
		}
		else
		{
			if (sym == writesym)    /* 准备按照write语句处理，与read类似 */
			{	getsymdo;			//符号读取 
				if (sym == lparen)	//语法规则判断 
				{
					do {
						getsymdo; 	//符号读取 
						/*增加格式化输出*/
						if(sym == quotation){	// 输出格式 
							// write("count=",count," ans=?",ans);
							// output: count=$count ans=$ans
							char tempstr[32];	// 创建临时缓冲区 
							int tspos = 0; 		// 设置缓冲区指针 
							while(ch!='"'){
								//printf("%c",ch);	//调试时使用 
								tempstr[tspos++]=ch;//读取源程序 
								getchdo;				
							}
							tempstr[tspos]='\0';//必须加上终止符不然输出乱码
							getchdo; 
							strcpy(str[nowstr],tempstr);// 将读取到的字符串存入缓冲区 
							getsymdo;
							nowstr++; 			/* new! 标准化输出字符串+1 */
							if(nowstr > 32){	//错误处理，缓冲区是否溢出 
								error(1);
							}
							gendo(spt, 0, nowstr-1,0);// 新增缓冲区输出指令 
						}
						/*非格式化输出，则为变量输出流程*/
						else{
							memcpy(nxtlev, fsys, sizeof(bool)*symnum);
							nxtlev[rparen] = true;	//用于错误处理 
							nxtlev[comma] = true;	/* write的后跟符号为) or , */
							expressiondo(nxtlev, ptx, lev); /* 调用表达式处理，此处与read不同，read为给变量赋值 */
							gendo(opr, 0, 14,0);  	/* 生成输出指令，输出栈顶的值 */	
						}
					} while (sym == comma);
					if (sym != rparen)
					{error(33);  /* write()中应为完整表达式 */}
					else{getsymdo;}
				}
				gendo(opr, 0, 15,0);  /* 输出换行 */}
			else
			{
				if (sym == callsym) /* 准备按照call语句处理 */
				{
					getsymdo;
					if (sym != ident)
					{
						error(14);  /* call后应为标识符 */
					}
					else
					{
						i = position(id, *ptx);
						if (i == 0)
						{
							error(11);  /* 过程未找到 */
						}
						else
						{
							if (table[i].kind == procedur)
							{
								gendo(cal, lev-table[i].level, table[i].adr,0);   /* 生成call指令 */
							}
							else
							{
								error(15);  /* call后标识符应为过程 */
							}
						}
						getsymdo;
					}
				}
				else
				{
					if (sym == ifsym)   /* 准备按照if语句处理 */
					{
						getsymdo;
						memcpy(nxtlev, fsys, sizeof(bool)*symnum);
						nxtlev[thensym] = true;
						nxtlev[dosym] = true;   /* 后跟符号为then或do */
						conditiondo(nxtlev, ptx, lev); /* 调用条件处理（逻辑运算）函数 */
						if (sym == thensym)
						{
							getsymdo;
						}
						else
						{
							error(16);  /* 缺少then */
						}
						cx1 = cx;   /* 保存当前指令地址 */
						gendo(jpc, 0, 0,0);   /* 生成条件跳转指令，跳转地址未知，暂时写0 */
						statementdo(fsys, ptx, lev);    /* 处理then后的语句 */
						code[cx1].a = cx;   /* 经statement处理后，cx为then后语句执行完的位置，它正是前面未定的跳转地址 */
					}
					else
					{
						if (sym == beginsym)    /* 准备按照复合语句处理 */
						{
							getsymdo;
							memcpy(nxtlev, fsys, sizeof(bool)*symnum);
							nxtlev[semicolon] = true;
							nxtlev[endsym] = true;  /* 后跟符号为分号或end */
							/* 循环调用语句处理函数，直到下一个符号不是语句开始符号或收到end */
							statementdo(nxtlev, ptx, lev);

							while (inset(sym, statbegsys) || sym==semicolon)
							{
								if (sym == semicolon)
								{
									getsymdo;
								}
								else
								{
									error(10);  /* 缺少分号 */
								}
								statementdo(nxtlev, ptx, lev);
							}
							if(sym == endsym)
							{
								getsymdo;
							}
							else
							{
								error(17);  /* 缺少end或分号 */
							}
						}
						else
						{
							if (sym == whilesym)    /* 准备按照while语句处理 */
							{
								cx1 = cx;   /* 保存判断条件操作的位置 */
								getsymdo;
								memcpy(nxtlev, fsys, sizeof(bool)*symnum);
								nxtlev[dosym] = true;   /* 后跟符号为do */
								conditiondo(nxtlev, ptx, lev);  /* 调用条件处理 */
								cx2 = cx;   /* 保存循环体的结束的下一个位置 */
								gendo(jpc, 0, 0,0);   /* 生成条件跳转，但跳出循环的地址未知 */
								if (sym == dosym)
								{
									getsymdo;
								}
								else
								{
									error(18);  /* 缺少do */
								}
								statementdo(fsys, ptx, lev);    /* 循环体 */
								gendo(jmp, 0, cx1,0); /* 回头重新判断条件 */
								code[cx2].a = cx;   /* 反填跳出循环的地址，与if类似 */
							}
							/* new !*/
							else if(sym == forsym){	//判断for关键字 
								getsymdo;			//读取字符 
								if(sym == ident){	//语法判断应该为变量 
									i = position(id,*ptx);//寻找变量在符号表中的位置 
									if(i == 0)error(11);//未找到则报错 
									else{//判断变量应该为整型或者浮点型，否则将报错 
										if(table[i].kind != variable && table[i].kind != dvariable )
										{
											error(12);  /* 赋值语句格式错误 */
											i = 0;
										}
									}
									getsymdo;//符号读入 
									if(sym == becomes){//这里需要对于变量进行初始化赋值 
										getsymdo;
									}
									else error(13);
									memcpy(nxtlev,fsys,sizeof(bool)*symnum);
									expressiondo(nxtlev,ptx,lev);//调用表达式语句完成赋值 
									if(i){//栈顶的值存到相对目标地址内存
										gendo(sto,lev-table[i].level,table[i].adr,0);
									}
								}
								else error(17);
								cx1 = cx;//记录当前的label 
								getsymdo;//符号读取 
								memcpy(nxtlev,fsys,sizeof(bool)*symnum);//错误处理 
								nxtlev[dosym]=true;//错误处理 
								conditiondo(nxtlev,ptx,lev);//调用条件判断语句 
								cx2 = cx;//记录现在的label 
								gendo(jpc,0,0,0);//生成值判断跳转指令，但是值未指定 
								if(sym == dosym){//语法判断 
									getsymdo;
								}
								else error(18);//调用声明语句，判断for循环内部的语句 
								statementdo(fsys,ptx,lev);
								gendo(jmp,0,cx1,0);	//所有的语句都结束此时可以利用label对于跳转的地址赋值 
								code[cx2].a=cx;		//也可以确认指令的地址 
							}
							/* new ! delete tuple */
							else if(sym == delsym){//printf("ddd\n");
								getsymdo;
								if(sym == ident){
									getsymdo;
									int pos_in_table;
									pos_in_table = position(id, *ptx);
									if(table[pos_in_table].kind==tuple){
										if(table[pos_in_table].bottom!=-1){
											int bottom = table[pos_in_table].bottom;
											int upper  = table[pos_in_table].upper;
											while(upper>=bottom){
												heapState[upper--]=0;
											}
											table[pos_in_table].bottom = -1;
											table[pos_in_table].upper  = -1;
											//showHeapFree();
											/*无需判断分号*/
//											if(sym == semicolon){
//												getsymdo;
//											}
//											else{
//												
//												error(17);
//											}
										}
										else{
											error(24);
										}
									}
									else{
										error(23);
									}
								}
								else{
									error(19);
								}
							}
							/* new ! new tuple */
							else if(sym == newsym){
								getsymdo;
								if(sym == ident){
									int pos_in_table;
									pos_in_table = position(id, *ptx);
									if(table[pos_in_table].kind==tuple){
										if(table[pos_in_table].bottom==-1){
											getsymdo;
											if(sym == lparen){
												getsymdo;
												if(sym == number){
													table[pos_in_table].bottom = num;
													getsymdo;
													if(sym == comma){
														getsymdo;
														if(sym == number){
															getsymdo;
															table[pos_in_table].upper = num;
															int temp = table[pos_in_table].bottom;
															while(temp<=table[pos_in_table].upper){
																heapState[temp]=1;
																temp++;
															}
															//showHeapFree();
															if(sym == rparen){
																getsymdo;
//																if(sym == semicolon){
//																	getsymdo;
//																}
//																else{
//																	error(17);
//																}
															}
															else{
																error(28);
															}
														}
														else error(27);
													}
													else error(28);
												}
												else error(29);
											}
											else{
												error(26);
											}
										}
										else{
											error(25);
										}
									}
									else{
										error(23);
									}
								}
								else{
									error(19);
								}
							}
							else
							{
								memset(nxtlev, 0, sizeof(bool)*symnum); /* 语句结束无补救集合 */
								testdo(fsys, nxtlev, 19);   /* 检测语句结束的正确性 */
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

/*表达式处理*/

int expression(bool* fsys, int* ptx, int lev)
{
	enum symbol addop;  /* 用于保存正负号 */
	bool nxtlev[symnum];

	if(sym==plus || sym==minus) /* 开头的正负号，此时当前表达式被看作一个正的或负的项 */
	{
		addop = sym;    /* 保存开头的正负号 */
		getsymdo;
		memcpy(nxtlev, fsys, sizeof(bool)*symnum);
		nxtlev[plus] = true;
		nxtlev[minus] = true;
		termdo(nxtlev, ptx, lev);   /* 处理项 */
		if (addop == minus)
		{
			gendo(opr,0,1,0); /* 如果开头为负号生成取负指令 */
		}
	}
	else    /* 此时表达式被看作项的加减 */
	{
		memcpy(nxtlev, fsys, sizeof(bool)*symnum);
		nxtlev[plus] = true;
		nxtlev[minus] = true;
		termdo(nxtlev, ptx, lev);   /* 处理项 */
	}
	while (sym==plus || sym==minus)
	{
		addop = sym;
		getsymdo;
		memcpy(nxtlev, fsys, sizeof(bool)*symnum);
		nxtlev[plus] = true;
		nxtlev[minus] = true;
		termdo(nxtlev, ptx, lev);   /* 处理项 */
		if (addop == plus)
		{
			gendo(opr, 0, 2,0);   /* 生成加法指令 */
		}
		else
		{
			gendo(opr, 0, 3,0);   /* 生成减法指令 */
		}
	}
	return 0;
}

/*项处理*/
int term(bool* fsys, int* ptx, int lev)
{
	enum symbol mulop;  /* 用于保存乘除法符号 */
	bool nxtlev[symnum];

	memcpy(nxtlev, fsys, sizeof(bool)*symnum);
	nxtlev[times] = true;
	nxtlev[slash] = true;
	factordo(nxtlev, ptx, lev); /* 处理因子 */
	while(sym==times || sym==slash)
	{
		mulop = sym;
		getsymdo;
		factordo(nxtlev, ptx, lev);
		if(mulop == times)
		{
			gendo(opr, 0, 4,0);   /* 生成乘法指令 */
		}
		else
		{
			gendo(opr, 0, 5,0);   /* 生成除法指令 */
		}
	}
	return 0;
}

/*因子处理*/
int factor(bool* fsys, int* ptx, int lev)
{
	int i;
	bool nxtlev[symnum];
	testdo(facbegsys, fsys, 24);    /* 检测因子的开始符号 */
	/* while(inset(sym, facbegsys)) */  /* 循环直到不是因子开始符号 */
	if(inset(sym,facbegsys))    /* BUG: 原来的方法var1(var2+var3)会被错误识别为因子 */
	{
		if(sym == ident)    /* 因子为常量或变量 */
		{
			i = position(id, *ptx); /* 查找名字 */
			if (i == 0)
			{
				error(11);  /* 标识符未声明 */
			}
			else
			{
				switch (table[i].kind)
				{
				case constant:  /* 名字为常量 */
					if(table[i].val)
					gendo(lit, 0, table[i].val,0);    /* 直接把常量的值入栈 */
					else gendo(lit, 0, 0,table[i].dval); /*new!取浮点值*/
					break;
				case variable:  /* 名字为变量 */
					gendo(lod, lev-table[i].level, table[i].adr,0);   /* 找到变量地址并将其值入栈 */
					break;
				case dvariable:  /* new!名字为浮点变量 */
					gendo(lod, lev-table[i].level, table[i].adr,0);   /* 找到变量地址并将其值入栈 */
					break;
				case procedur:  /* 名字为过程 */
					error(21);  /* 不能为过程 */
					break;
				case array:
					getsymdo;				//读取字符 
					if(sym == lspsym){		//判断语法结构 
						getsymdo;			//读取字符 
						if(sym == number){	//需要指定下标 
							getsymdo;		//读取字符 
							int pos_in_table = position(id,*ptx);
							int pos = num;	//获取下标和数组基地址 
							if(pos <= table[pos_in_table].upper - table[pos_in_table].bottom){//越界判断 
								gendo(lod, lev-table[i].level, table[pos+i].adr,0);		//取对应地址的值并入栈 
								//printf("%d %d %d\n",table[pos].adr+i+1,table[pos].adr+i,table[pos].adr);
							}
							else error(36);//错误处理，对应数组越界判断 
							if(sym != rspsym){//语法结构判断 
								error(7);		//错误处理 
							}
						}
						else error(8);			//是否指定下标 
					}
					else error(6);				//是否括号完整 
					break;
				case tuple:
					getsymdo;//读取符号 
					if(sym == lparen){		//是否左括号 
						getsymdo;			//读取字符 
						if(sym == number){	//是否指定下标 
							getsymdo;		//读取字符 
							int pos_in_table = position(id,*ptx);
							int pos = num;	//获取下标和元组对应到堆中的基地址 
							if(pos <= table[pos_in_table].upper - table[pos_in_table].bottom){//越界判断 
								gendo(dli,0 ,0 ,heap[table[pos_in_table].bottom+num]);//直接从内存中取值放到栈顶 
							}
							else error(42);	//元组越界判断 
							if(sym != rparen){
								error(7);	//括号是否完整 
							}
						}
						else error(8);		//是否指定下标 
					}
					else error(6); 			//调用方式是否为括号 
				}//MonkeyPeach.PL0
			}
			getsymdo;
		}
		else
		{
			if(sym == number)   /* 因子为整数 */
			{
				if (num > amax)
				{
					error(31);
					num = 0;
				}
				gendo(lit, 0, num,0);
				getsymdo;
			}
			if(sym == dnumber)   /* new ! 因子为浮点数 */
			{
				if (dnum > amax)
				{
					error(31);
					dnum = 0;
				}
				gendo(dli, 0, 0,dnum);
				getsymdo;
			}
			else
			{
				if (sym == lparen)  /* 因子为表达式 */
				{
					getsymdo;
					memcpy(nxtlev, fsys, sizeof(bool)*symnum);
					nxtlev[rparen] = true;
					expressiondo(nxtlev, ptx, lev);
					if (sym == rparen)
					{
						getsymdo;
					}
					else
					{
						error(22);  /* 缺少右括号 */
					}
				}
				testdo(fsys, facbegsys, 23);    /* 因子后有非法符号 */
			}
		}
	}
	return 0;
}

/*条件处理*/
int condition(bool* fsys, int* ptx, int lev)
{
	enum symbol relop;
	bool nxtlev[symnum];

	if(sym == oddsym)   /* 准备按照odd运算处理 */
	{
		getsymdo;
		expressiondo(fsys, ptx, lev);
		gendo(opr, 0, 6,0);   /* 生成odd指令 */
	}
	else
	{
		/* 逻辑表达式处理 */
		memcpy(nxtlev, fsys, sizeof(bool)*symnum);
		nxtlev[eql] = true;
		nxtlev[neq] = true;
		nxtlev[lss] = true;
		nxtlev[leq] = true;
		nxtlev[gtr] = true;
		nxtlev[geq] = true;
		expressiondo(nxtlev, ptx, lev);
		if (sym!=eql && sym!=neq && sym!=lss && sym!=leq && sym!=gtr && sym!=geq)
		{
			error(20);
		}
		else
		{
			relop = sym;
			getsymdo;
			expressiondo(fsys, ptx, lev);
			switch (relop)
			{
			case eql:
				gendo(opr, 0, 8,0);
				break;
			case neq:
				gendo(opr, 0, 9,0);
				break;
			case lss:
				gendo(opr, 0, 10,0);
				break;
			case geq:
				gendo(opr, 0, 11,0);
				break;
			case gtr:
				gendo(opr, 0, 12,0);
				break;
			case leq:
				gendo(opr, 0, 13,0);
				break;
			}
		}
	}
	return 0;
}

/*解释程序*///MonkeyPeach.PL0
void interpret()
{
	int p, b, t;    /* 指令指针，指令基址，栈顶指针 */
	struct instruction i;   /* 存放当前指令 */
	//int s[stacksize];   /* 栈 */
	
	double s[stacksize]={0.0};   /* new ! 栈 */
	
	//printf("start pl0\n");
	t = 0;
	b = 0;
	p = 0;
	s[0] = s[1] = s[2] = 0;
	do {
		i = code[p];    /* 读当前指令 */
		p++;
		switch (i.f)
		{
		case lit:   /* 将a的值取到栈顶 */
			s[t] = i.a;
			t++;
			break;
		/* new！ 浮点数的数字 */
		case dli:   /* 将a的值取到栈顶 */
			s[t] = i.d;
			t++;
			break;
		case opr:   /* 数学、逻辑运算 */
			switch (i.a)
			{
			case 0:
				t = b;
				p = s[t+2];
				b = s[t+1];
				break;
			case 1:
				s[t-1] = -s[t-1];
				break;
			case 2:
				t--;
				s[t-1] = s[t-1]+s[t];
				break;
			case 3:
				t--;
				s[t-1] = s[t-1]-s[t];
				break;
			case 4:
				t--;
				s[t-1] = s[t-1]*s[t];
				break;
			case 5:
				t--;
				s[t-1] = s[t-1]/s[t];
				break;
			case 6:
				s[t-1] = (int)s[t-1]%2;
				break;
			case 8:
				t--;
				s[t-1] = (s[t-1] == s[t]);
				break;
			case 9:
				t--;
				s[t-1] = (s[t-1] != s[t]);
				break;
			case 10:
				t--;
				s[t-1] = (s[t-1] < s[t]);
				break;
			case 11:
				t--;
				s[t-1] = (s[t-1] >= s[t]);
				break;
			case 12:
				t--;
				s[t-1] = (s[t-1] > s[t]);
				break;
			case 13:
				t--;
				s[t-1] = (s[t-1] <= s[t]);
				break;
			case 14:
				/*new! 转化为double类型栈时千万注意类型，不然出错难找*/
				printf("%lf", s[t-1]);
				fprintf(fa2, "%lf", s[t-1]);
				t--;
				break;
			case 15:
				printf("\n");
				fprintf(fa2,"\n");
				break;
			case 16://MonkeyPeach.PL0
				//printf("?");
				//fprintf(fa2, "?");
				/*new! 转化为double类型栈时千万注意类型，不然出错难找*/
				scanf("%lf", &(s[t]));
				fprintf(fa2, "%lf\n", s[t]);
				t++;
				break;
			}
			break;
		/* new! 字符串标准化输出 */
		case spt:
			printf("%s",str[(int)i.a]);
			break; 
		case lod:   /* 取相对当前过程的数据基地址为a的内存的值到栈顶 */
			s[t] = s[base(i.l,s,b)+i.a];
			t++;
			break;
		case sto:   /* 栈顶的值存到相对当前过程的数据基地址为a的内存 */
			t--;
			s[base(i.l,s,b)+i.a] = s[t];
			break;
		case stoa:  /* new 栈顶的值存到元组对应的内存空间中 */
			t--;
			heap[i.a+i.l] = s[t];
			break;
		case cal:   /* 调用子过程 */
			s[t] = base(i.l, s, b); /* 将父过程基地址入栈 */
			s[t+1] = b; /* 将本过程基地址入栈，此两项用于base函数 */
			s[t+2] = p; /* 将当前指令指针入栈 */
			b = t;  /* 改变基地址指针值为新过程的基地址 */
			p = i.a;    /* 跳转 */
			break;
		case inte:  /* 分配内存 */
			t += i.a;
			break;
		case jmp:   /* 直接跳转 */
			p = i.a;
			break;
		case jpc:   /* 条件跳转 */
			t--;//MonkeyPeach.PL0
			if (s[t] == 0)
			{
				p = i.a;
			}
			break;
		}
	} while (p != 0);
}
//MonkeyPeach.PL0
/* 通过过程基址求上l层过程的基址 */
int base(int l, double* s, int b)
{
	int b1;
	b1 = b;
	while (l > 0)
	{
		b1 = s[b1];
		l--;
	}//printf("%d   ",b1);
	return b1;
}
void showHeapFree(){
	int i = 0,j;
	for(;i < 32; i++){
		for(j = 0; j < 32 ; j ++){
			printf("%d ",heapState[i*32+j]);
		}
		printf("\n");
	}
}
int findFreeStart(int len){
	int i = 0 ;
	while(heapState[i]==0 && heapState[i+len-1]!=0){
		i++;
	}
	return i;
} 
