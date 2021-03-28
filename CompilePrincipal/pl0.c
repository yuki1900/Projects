/*
 * PL/0 complier program for win32 platform (implemented in C)
 *
 * The program has been test on Visual C++ 6.0, Visual C++.NET and
 * Visual C++.NET 2003, on Win98, WinNT, Win2000, WinXP and Win2003
 *
 * ʹ�÷�����
 * ���к�����PL/0Դ�����ļ�?
 * �ش��Ƿ�������������
 * �ش��Ƿ�������ֱ�
 * fa.tmp������������
 * fa1.tmp���Դ�ļ�������ж�Ӧ���׵�ַ
 * fa2.tmp�����?
 * fas.tmp������ֱ�
 */

#include <stdio.h>

#include "pl0.h"
#include "string.h"

/* ����ִ��ʱʹ�õ�ջ */
#define stacksize 500


int main()
{
	bool nxtlev[symnum];

//	printf("Input pl/0 file?   ");
//	scanf("%s", fname);     /* �����ļ��� */
	char temp[] = "MonkeyPeach.PL0";
	strcpy(fname,temp);
	fin = fopen(fname, "r");

	if (fin)//MonkeyPeach.PL0 
	{
		//printf("List object code?(Y/N)");   /* �Ƿ������������� */
		//scanf("%s", fname);
		fname[0] = 'n'; 
		listswitch = 0;

		//printf("List symbol table?(Y/N)");  /* �Ƿ�������ֱ� */
		//scanf("%s", fname);
		tableswitch = 1;

		fa1 = fopen("fa1.tmp", "w");
		fprintf(fa1,"Input pl/0 file?   ");
		fprintf(fa1,"%s\n",fname);

		init();     /* ��ʼ�� */

		err = 0;
		cc = cx = ll = 0;
		ch = ' ';

		if(-1 != getsym())
		{
			fa = fopen("fa.tmp", "w");
			fas = fopen("fas.tmp", "w");
			addset(nxtlev, declbegsys, statbegsys, symnum);
			nxtlev[period] = true;

			if(-1 == block(0, 0, nxtlev))   /* ���ñ������ */
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
				interpret();    /* ���ý���ִ�г��� */
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
* ��ʼ��
*/
void init()
{
	int i;
	/* ���õ��ַ����� */
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

	/* ���ñ���������,������ĸ˳�򣬱����۰���� */
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

	/* ���ñ����ַ��� */
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
	/* ����ָ������ */
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
    
	/* ���÷��ż� */
	for (i=0; i<symnum; i++)
	{
		declbegsys[i] = false;
		statbegsys[i] = false;
		facbegsys[i] = false;
	}

	/* ����������ʼ���ż� */
	declbegsys[constsym] = true;
	declbegsys[varsym] = true;
	declbegsys[procsym] = true;
	/* new �� */
	declbegsys[dvarsym] = true;
	declbegsys[arraysym] = true;  
	declbegsys[tuplesym] = true;  
	/* ������俪ʼ���ż� */
	statbegsys[beginsym] = true;
	statbegsys[callsym] = true;
	statbegsys[ifsym] = true;
	statbegsys[whilesym] = true;
	statbegsys[readsym] = true;
	statbegsys[writesym] = true;

	/* �������ӿ�ʼ���ż� */
	facbegsys[ident] = true;
	facbegsys[number] = true;
	facbegsys[lparen] = true;
	/* new ! */
	facbegsys[dnumber] = true;
}

/*
* ������ʵ�ּ��ϵļ�������
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
*   ��������ӡ����λ�úʹ������
*/
void error(int n)
{
	char space[81];
	memset(space,32,81);
	space[cc-1]=0; //����ʱ��ǰ�����Ѿ����꣬����cc-1
	//printf("****%s!%d ", space, n);
	fprintf(fa1,"****%s!%d ", space, n);
	/* new! ���Ӵ�������ʾ */
	switch(n){
		case 1:printf("��%d�У�=��Ϊ:=\n",LINE_NUM);break;
		case 2:printf("��%d�У�����=��ӦΪ����\n",LINE_NUM);break;
		case 3:printf("��%d�У�����˵����ʶ��Ӧ��=\n",LINE_NUM);break;
		case 4:printf("��%d�У�const��var��dvar��proc��Ӧ�Ǳ�ʶ\n",LINE_NUM);break;
		case 5:printf("��%d�У�ȱ�ٶ���\n",LINE_NUM);break;
		case 9:printf("��%d�У�ȱ�پ��\n",LINE_NUM);break;
		case 10:printf("��%d�У�ȱ�ٷֺ�\n",LINE_NUM);break;
		case 11:printf("��%d�У�����δ�ҵ�\n",LINE_NUM);break;
		case 12:printf("��%d�У���ֵ����ʽ����\n",LINE_NUM);break;
		case 13:printf("��%d�У�û�м�⵽��ֵ����\n",LINE_NUM);break;
		case 14:printf("��%d�У�call��ӦΪ��ʶ��\n",LINE_NUM);break; 
		case 15:printf("��%d�У�call���ʶ��ӦΪ����\n",LINE_NUM);break; 
		case 16:printf("��%d�У�ȱ��then\n",LINE_NUM);break;
		case 17:printf("��%d�У�ȱ��end��ֺ�%d\n",LINE_NUM);break; 
		case 18:printf("��%d�У�ȱ��do\n",LINE_NUM);break; 
		case 19:printf("��%d�У�del��ȱ�ٱ�־��\n",LINE_NUM);break; 
		case 20:printf("��%d�У��߼����ʽȱ���߼������\n",LINE_NUM);break;
		case 21:printf("��%d�У�����Ϊ����\n",LINE_NUM);break; 
		case 22:printf("��%d�У�ȱ��������\n",LINE_NUM);break; 
		case 23:printf("��%d�У�del���ʶ������ӦΪ����tuple\n",LINE_NUM);break; 
		case 24:printf("��%d�У�array������Ϊ�գ�����delete\n",LINE_NUM);break; 
		case 25:printf("��%d�У�array�����ظ�����ռ�\n",LINE_NUM);break; 
		case 26:printf("��%d�У�array����ռ�ȱ��'['\n",LINE_NUM);break; 
		case 27:printf("��%d�У�array�Ͻ�δ����\n",LINE_NUM);break; 
		case 28:printf("��%d�У�array����ռ�ȱ��']'\n",LINE_NUM);break; 
		case 29:printf("��%d�У�array�½�δ����\n",LINE_NUM);break; 
		case 30:printf("��%d�У����͹������\n",LINE_NUM);break;
		case 31:printf("��%d�У���Խ��\n",LINE_NUM);break;
		case 32:printf("��%d�У�read������ı�ʶ�����Ǳ���, ��Ƕ�ײ�������\n",LINE_NUM);break;
		case 33:printf("��%d�У���ʽ����Ӧ��������\n",LINE_NUM);break;
		case 34:printf("��%d�У���ʽ����Ӧ��������\n",LINE_NUM);break;
		case 35:printf("��%d�У�read��Ӧ���������ı�����\n",LINE_NUM);break;
		case 36:printf("��%d�У������±�Խ��",LINE_NUM);break;
		case 37:printf("��%d�У�tuple��Ϊ�գ�����delete\n",LINE_NUM);break;
		case 38:printf("��%d�У�tuple�����ظ�����ռ�\n",LINE_NUM);break;
		case 39:printf("��%d�У�tuple����ռ�ȱ��'('\n",LINE_NUM);break;
		case 40:printf("��%d�У�tuple�ռ��Сδָ��\n",LINE_NUM);break;
		case 41:printf("��%d�У�tuple����ռ�ȱ��')'\n",LINE_NUM);break;
		case 42:printf("��%d�У�tuple�±�Խ��\n",LINE_NUM);break;
		case 43:printf("��%d�У�ȱ��ð��\n",LINE_NUM);break;
		case 44:printf("��%d�У�ע��������\n",LINE_NUM);break;
	}err++;
}

/*
* ©���ո񣬶�ȡһ���ַ���
*
* ÿ�ζ�һ�У�����line��������line��getsymȡ�պ��ٶ�һ��
*
* ������getsym���á�
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
		while (ch != 10)//ch == 10 Ϊ���з� 
		{
			
			//fscanf(fin,"%c", &ch)
			//richard
			if (EOF == fscanf(fin,"%c", &ch))	// EOF ����Ϊ -1 
			{
				line[ll] = 0;					// Ϊline�������ӿ��ַ� 
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
* �ʷ���������ȡһ������
*/
int getsym()
{
	int i,j,k;

	/* the original version lacks "\r", thanks to foolevery */
	while (ch==' ' || ch==10 || ch==13 || ch==9)  /* ���Կո񡢻��С��س���TAB */
	{
		getchdo;
	}
	// new ! ���Ӵ�д��ĸ�ж� 
	if ((ch>='a' && ch<='z')||(ch>='A' && ch<='Z'))
	{           /* ���ֻ���������ĸ��ͷ */
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
		/* ���ַ�������ǰ�����Ƿ�Ϊ������ */
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
		/* ������������ǰ�����Ƿ�Ϊ������ */
		i = 0;
		while(strcmp(id,word[i])!=0 && i < norw)i++;
		
		if (i < norw)
		{
			sym = wsym[i];
		}
		else
		{
			sym = ident; /* ����ʧ���������ֻ����� */
		}
	}
	else
	{
		if (ch>='0' && ch<='9')
		{           /* ����Ƿ�Ϊ���֣���0..9��ͷ */
			k = 0;
			num = 0;
			sym = number;
			do {
				num = 10*num + ch - '0';
				k++;
				getchdo;
			} while (ch>='0' && ch<='9'); /* ��ȡ���ֵ�ֵ */
			
			if(ch == '.'){				  /* new ! ����С�����ж� */
				sym = dnumber;		  /* new ! ת������ΪС�� */
				getchdo;//printf("THIS IS A DNUM %c\n",ch);
				dnum = num;//printf("%lf\n",dnum); 
				//MonkeyPeach.PL0 
				double div = 1;
				do {
					dnum = 10*dnum + ch - '0';
					k++;
					div*=10;
					getchdo;//printf("THIS IS A DNUM %c\n",ch);
				}while (ch>='0' && ch<='9'); /* ��ȡ���ֵ�ֵ */
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
			if (ch == ':')      /* ��⸳ֵ���� */
			{
				getchdo;
				if (ch == '=')
				{
					sym = becomes;
					getchdo;
				}
				else
				{
					sym = colon;  /*new ���ð�ŵ�ʶ��*/
					//sym = nul;  /* ����ʶ��ķ��� */
				}
			}
			else
			{
				if (ch == '<')      /* ���С�ڻ�С�ڵ��ڷ��� */
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
					if (ch=='>')        /* �����ڻ���ڵ��ڷ��� */
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
						/* new ע����� */
						if(ch == '{'){getchdo;
							while(ch!='}'){
								getchdo;
							}
							getsymdo;
							return 0; 
						}
						     /* �����Ų�������������ʱ��ȫ�����յ��ַ����Ŵ��� */
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
* �������������
*
* x: instruction.f;
* y: instruction.l;
* z: instruction.a;
*/
/*new! ���漰��double���͵���ʱ�������п���Ϊ������*/
int gen(enum fct x, int y, int z,double d)
{
	if (cx >= cxmax)
	{
		printf("Program too long"); /* ������� */
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
* ���Ե�ǰ�����Ƿ�Ϸ�
*
* ��ĳһ���֣���һ����䣬һ�����ʽ����Ҫ����ʱʱ����ϣ����һ����������ĳ��?
* ���ò��ֵĺ�����ţ���test���������⣬���Ҹ��𵱼�ⲻͨ��ʱ�Ĳ��ȴ�ʩ��
* ��������Ҫ���ʱָ����ǰ��Ҫ�ķ��ż��ϺͲ����õļ��ϣ���֮ǰδ��ɲ��ֵĺ��
* ���ţ����Լ���ⲻͨ��ʱ�Ĵ���š�
*
* s1:   ������Ҫ�ķ���
* s2:   �������������Ҫ�ģ�����Ҫһ�������õļ�?
* n:    �����
*/
int test(bool* s1, bool* s2, int n)
{
	if (!inset(sym, s1))
	{
		error(n);
		/* ����ⲻͨ��ʱ����ͣ��ȡ���ţ�ֱ����������Ҫ�ļ��ϻ򲹾ȵļ��� */
		while ((!inset(sym,s1)) && (!inset(sym,s2)))
		{
			getsymdo;
		}
	}
	return 0;
}

/*
* ���������?
*
* lev:    ��ǰ�ֳ������ڲ�
* tx:     ���ֱ�ǰβָ��
* fsys:   ��ǰģ�������ż�?
*/
int block(int lev, int tx, bool* fsys)
{
	int i;

	int dx;                 /* ���ַ��䵽����Ե�ַ */
	int tx0;                /* ������ʼtx */
	int cx0;                /* ������ʼcx */
	bool nxtlev[symnum];    /* ���¼������Ĳ����У����ż��Ͼ�Ϊֵ�Σ�������ʹ������ʵ�֣�
							���ݽ�������ָ�룬Ϊ��ֹ�¼������ı��ϼ������ļ��ϣ������µĿ�?
							���ݸ��¼�����*/

	dx = 3;
	tx0 = tx;               /* ��¼�������ֵĳ�ʼλ�� */
	table[tx].adr = cx;

	gendo(jmp, 0, 0,0);

	if (lev > levmax)
	{
		error(32);
	}

	do {

		if (sym == constsym)    /* �յ������������ţ���ʼ���������� */
		{
			getsymdo;

			/* the original do...while(sym == ident) is problematic, thanks to calculous */
			/* do { */
			constdeclarationdo(&tx, lev, &dx);  /* dx��ֵ�ᱻconstdeclaration�ı䣬ʹ��ָ�� */
			while (sym == comma)	// ��Ϊ���ţ�˵��const����δ������� 
			{
				getsymdo;			// ȡ��const���� 
				constdeclarationdo(&tx, lev, &dx);	// ��д�� 
			}
			if (sym == semicolon)	// ��Ϊ�ֺţ�˵�������Ա������ 
			{
				getsymdo;
			}
			else
			{
				error(5);   /*©���˶��Ż��߷ֺ�*/
			}
			/* } while (sym == ident); */
		}

		if (sym == varsym)      /* �յ������������ţ���ʼ����������� */
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
		
		if (sym == dvarsym)     /* new ���յ���������������ţ���ʼ����������� */
		{
			getsymdo;			//��ȡ�ַ� 
			dvardeclarationdo(&tx, lev, &dx);
			while (sym == comma)//�ж��Ƿ��ж�������� 
			{
				getsymdo;		//��ȡ�ַ�����ȫ������ 
				dvardeclarationdo(&tx, lev, &dx);
			}
			if (sym == semicolon)//�ж��Ƿ���� 
			{
				getsymdo;
			}
			else
			{
				error(5);
			}
			/* } while (sym == ident);  */
		}
		
		if (sym == arraysym)	/* new ���յ���������������ţ���ʼ����������� */
		{
			getsymdo;			//��ȡ�ַ� 
			arraydeclarationdo(&tx, lev, &dx);
			while (sym == comma)//ѭ���ж϶������ 
			{
				getsymdo;		//��ȡ�ַ���ͨ��ѭ�������������� 
				arraydeclarationdo(&tx, lev, &dx);
			}
			if (sym == semicolon)//�ж��Ƿ�ȫ������ 
			{
				getsymdo;
			}
			else
			{
				error(5);
			}
			/* } while (sym == ident);  */
		}
		
		if (sym == tuplesym)	/* new ���յ�Ԫ������������ţ���ʼ����������� */
		{
			getsymdo;			//��ȡ�ַ�	
			tupledeclarationdo(&tx, lev, &dx);
			while (sym == comma)//�ж��Ƿ��ж��Ԫ�� 
			{
				getsymdo;		//��ȡ�ַ���ѭ����ɶ������ 
				tupledeclarationdo(&tx, lev, &dx);
			}
			if (sym == semicolon)//����Ƿ���� 
			{
				getsymdo;
			}
			else
			{
				error(5);
			}
			/* } while (sym == ident);  */
		}
		while (sym == procsym) /* �յ������������ţ���ʼ����������� */
		{
			getsymdo;

			if (sym == ident)
			{
				enter(procedur, &tx, lev, &dx); /* ��¼�������� */
				getsymdo;
			}
			else
			{
				error(4);   /* procedure��ӦΪ��ʶ�� */
			}

			if (sym == semicolon)
			{
				getsymdo;
			}
			else
			{
				error(5);   /* ©���˷ֺ� */
			}

			memcpy(nxtlev, fsys, sizeof(bool)*symnum);
			nxtlev[semicolon] = true;
			if (-1 == block(lev+1, tx, nxtlev))
			{
				return -1;  /* �ݹ���� */
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
				error(5);   /* ©���˷ֺ� */
			}
		}
		memcpy(nxtlev, statbegsys, sizeof(bool)*symnum);
		nxtlev[ident] = true;
		testdo(nxtlev, declbegsys, 7);
	} while (inset(sym, declbegsys));   /* ֱ��û���������� */

	code[table[tx0].adr].a = cx;    /* ��ʼ���ɵ�ǰ���̴��� */
	table[tx0].adr = cx;            /* ��ǰ���̴����ַ */
	table[tx0].size = dx;           /* ����������ÿ����һ�����������dx����1�����������Ѿ�������dx���ǵ�ǰ�������ݵ�size */
	cx0 = cx;
	gendo(inte, 0, dx,0);             /* ���ɷ����ڴ���� */

	if (tableswitch)        /* ������ֱ� */
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

	/* ���������Ϊ�ֺŻ�end */
	memcpy(nxtlev, fsys, sizeof(bool)*symnum);  /* ÿ��������ż��Ͷ������ϲ������ż��ͣ��Ա㲹�� */
	nxtlev[semicolon] = true;
	nxtlev[endsym] = true;
	statementdo(nxtlev, &tx, lev);
	gendo(opr, 0, 0,0);                       /* ÿ�����̳��ڶ�Ҫʹ�õ��ͷ����ݶ�ָ�� */
	memset(nxtlev, 0, sizeof(bool)*symnum); /*�ֳ���û�в��ȼ��� */
	testdo(fsys, nxtlev, 8);                /* �����������ȷ�� */
	listcode(cx0);                          /* ������� */
	return 0;
}

/*
* �����ֱ��м���һ��
*
* k:      ��������const,dvar,var or procedure
* ptx:    ���ֱ�βָ���ָ�룬Ϊ�˿��Ըı����ֱ�βָ���ֵ
* lev:    �������ڵĲ��,���Ժ����е�lev��������
* pdx:    dxΪ��ǰӦ����ı�������Ե�ַ�������Ҫ����1
*/
int enter(enum object k, int* ptx, int lev, int* pdx)
{
	(*ptx)++;
	strcpy(table[(*ptx)].name, id); /* ȫ�ֱ���id���Ѵ��е�ǰ���ֵ����� */
	table[(*ptx)].kind = k;
	switch (k)
	{
	case constant:  /* �������� */
		if (num > amax)
		{
			error(31);  /* ��Խ�� */
			num = 0;
		}
		if(sym == number)
			table[(*ptx)].val = num;
		if(sym == dnumber) /* new ! ���������ͳ���*/
			table[(*ptx)].dval = dnum; 
		break;
	case variable:  /* �������� */
		table[(*ptx)].level = lev;
		table[(*ptx)].adr = (*pdx);
		(*pdx)++;
		break;
	case procedur:  /*���������֡�*/
		table[(*ptx)].level = lev;
		break;
	case dvariable:  /* new ! ���������� */
		table[(*ptx)].level = lev;	//��¼�㼶
		table[(*ptx)].adr = (*pdx);	//��¼��ַ
		(*pdx)++;					//�޸����ֱ��еĵ�ַ��������
		break;
	case array:  /* new ! �������� */
		table[(*ptx)].level = lev;	//��¼�㼶
		table[(*ptx)].adr = (*pdx);	//��¼��ַ
		getsymdo;					//��ȡ�ַ�
		if(sym == lspsym){			//�����﷨�ж�
			getsymdo;				//��ȡ�ַ�
			if(sym == number){
				getsymdo;			//��ȡ�ַ�
				table[(*ptx)].bottom = 0;  	//�趨�½�Ϊ0 
				table[(*ptx)].upper = num;	//�Ͻ�ȡ���ڳ�ʼ��ʱ�����Ĵ�С 
				int temp = num;
				char oid[al+1],tempid[al+1]={' '};
				strcpy(oid,id);		//������ʱ���������ȡ����id��Ϣ 
				strcpy(id,tempid);
				(*pdx)++;			//�޸����ֱ��еĵ�ַ�������� 
				while(temp){		//�����������ʼ���ռ�Ĵ�С���з��� 
					enter(dvariable,ptx,lev,pdx);//���ո���������д��� 
					temp--;
				}
				strcpy(id,oid);		//�����ȡ����id��Ϣ 
				if(sym == rspsym){
					/* pass, no proc need to be done */
				}
				else error(28);		//������ 
			}
			else error(27);			//������ 
		}
		else error(26);				//������ 
		break;
	case tuple:  /* new ! �������� */
		table[(*ptx)].level = lev;	//��¼�㼶 
		table[(*ptx)].adr = (*pdx); //��¼��ַ 
		getsymdo;					//��ȡ�ַ� 
		if(sym==lparen){			//�����﷨�ж� 
			getsymdo;
			if(sym==number){		//����Ӧ������Ԫ���С 
				getsymdo;
				if(sym==colon){		//�﷨�淶Ϊð�� 
					int freestart = findFreeStart(num);	//�ҳ����������Ŀ����� 
					table[(*ptx)].bottom = freestart;  	//����������������ַ�����Ԫ�� 
					table[(*ptx)].upper = freestart+num;//ͬʱ�趨�Ͻ� 
					getsymdo;
					int pos = 0;
					while(sym==number){	// ֮����Ҫ�Դ˶���Ԫ���е�ֵ���г�ʼ�� 
						heap[table[(*ptx)].bottom+pos++]=num;//�޸Ķ��ж�Ӧ�ڴ��ֵ 
						getsymdo;
						if(sym == comma){
							// pass 
						}
						else break;getsymdo;
					}
					if(sym == rparen){
						// pass
					}
					else error(41);	// ������ 
				}else error(43);	// ������ 
				
			}else error(40);		// ������ 
		}
		else error(39); 			// ������ 
		(*pdx)++;					// ����޸����ֱ��еı�ͷ������ַ 
		break;
	}
}

/*
* �������ֵ�λ��.
* �ҵ��򷵻������ֱ��е�λ��,���򷵻�0.
*
* idt:    Ҫ���ҵ�����
* tx:     ��ǰ���ֱ�βָ��
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
* ������������
*/
int constdeclaration(int* ptx, int lev, int* pdx)
{	// sym == ident �������Ǳ����֣������ֻ����� 
	if (sym == ident) /* ����˵����ʶ��Ӧ��= */
	{
		getsymdo;
		if (sym==eql || sym==becomes)
		{
			if (sym == becomes)
			{
				error(1);   /* ��=д����:= */
			}
			getsymdo;
			if (sym == number)
			{
				enter(constant, ptx, lev, pdx);
				getsymdo;
			}
			else if(sym == dnumber){/* new �����������ͳ��� */
				enter(constant, ptx, lev, pdx);
				getsymdo;
			}
			else
			{
				error(2);   /* ����˵��=��Ӧ������ */
			}
		}
		else
		{
			error(3);   /* ����˵����ʶ��Ӧ��= */
		}
	}
	else
	{
		error(4);   /* const��Ӧ�Ǳ�ʶ */
	}
	return 0;
}

/*
* ������������
*/
int vardeclaration(int* ptx,int lev,int* pdx)
{
	if (sym == ident)
	{
		enter(variable, ptx, lev, pdx); // ��д���ֱ�
		getsymdo;
	}
	else
	{
		error(4);   /* var��Ӧ�Ǳ�ʶ */
	}
	return 0;
}

/* new ! 
* ��������������
*/
int dvardeclaration(int* ptx,int lev,int* pdx)
{
	if (sym == ident)
	{
		enter(dvariable, ptx, lev, pdx); // ��д���ֱ�
		getsymdo;
	}
	else
	{
		error(4);   /* dvar��Ӧ�Ǳ�ʶ */
	}
	return 0;
}
/* new ! 
* ������������
*/
int arraydeclaration(int* ptx, int lev, int* pdx){
	if (sym == ident)
	{
		enter(array, ptx, lev, pdx); // ��д���ֱ�
		getsymdo;
	}
	else
	{
		error(4);   /* arr��Ӧ�Ǳ�ʶ */
	}
	return 0;
}
/* new ! 
* Ԫ����������
*/
int tupledeclaration(int* ptx, int lev, int* pdx){
	if (sym == ident)
	{
		enter(tuple, ptx, lev, pdx); // ��д���ֱ�
		getsymdo;
	}
	else
	{
		error(4);   /* tuple��Ӧ�Ǳ�ʶ */
	}
	return 0;
}
/*
* ���Ŀ������嵥
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
* ��䴦��
*/
int statement(bool* fsys, int* ptx, int lev)
{
	int i, cx1, cx2;
	bool nxtlev[symnum];

	if (sym == ident)   /* ׼�����ո�ֵ��䴦�� */
	{
		i = position(id, *ptx);
		if (i == 0)
		{
			error(11);  /* ����δ�ҵ� */
		}
		else
		{
			/* new ! ���Ӷ��ڸ������͵��ж�*/
			if(table[i].kind != variable && table[i].kind != dvariable && table[i].kind != array)
			{
				error(12);  /* ��ֵ����ʽ���� */
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
					error(13);  /* û�м�⵽��ֵ���� */
				}
				memcpy(nxtlev, fsys, sizeof(bool)*symnum);
				expressiondo(nxtlev, ptx, lev); /* ����ֵ�����Ҳ���ʽ */
				if(i != 0 && table[i].kind!=array)
				{
					/* expression��ִ��һϵ��ָ������ս�����ᱣ����ջ����ִ��sto������ɸ�ֵ */
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
		if (sym == readsym) /* ׼������read��䴦�� */
		{
			getsymdo;
			if (sym != lparen)
			{
				error(34);  /* ��ʽ����Ӧ�������� */
			}
			else
			{
				do {
					getsymdo;	// ��ȡ�ַ� 
					/*���Ӹ�ʽ������*/
					if(sym == quotation){//�ж��Ƿ�Ϊ���� 
						// write("count=",count," ans=?",ans);
						// output: count=$count ans=$ans
						char tempstr[32];	//�趨������ 
						int tspos = 0; 		//�趨������ָ�� 
						while(ch!='"'){		//�ж����ý��� 
							//printf("%c",ch);//����ʱʹ�� 
							tempstr[tspos++]=ch;//���ַ����浽������ 
							getchdo;		//��ȡ�ַ� 
						}
						tempstr[tspos]='\0';//���������ֹ����Ȼ�������
						getchdo; 			//��ȡ�ַ� 
						strcpy(str[nowstr],tempstr);// ����ȡ�����ַ������뻺����
						getsymdo;			//��ȡ�ַ�
						nowstr++; /* new! ��׼������ַ���+1 */
						if(nowstr > 32){	//�������жϻ������Ƿ���� 
							error(1);		//�������� 
						}
						gendo(spt, 0, nowstr-1,0); //���ɻ��������ָ�� 
					}
					else if (sym == ident)
					{
						i = position(id, *ptx); /* ����Ҫ���ı��� */
						if (i == 0)
						{
							error(35);  /* read()��Ӧ���������ı����� */
						}
						else if (!(table[i].kind == variable || table[i].kind == dvariable))
						{
							error(32);	/* read()������ı�ʶ�����Ǳ���, thanks to amd */
						}
						else
						{
							gendo(opr, 0, 16,0);  /* ��������ָ���ȡֵ��ջ�� */
							gendo(sto, lev-table[i].level, table[i].adr,0);   /* ���浽���� */
						}
						getsymdo;
					}
					else
					{
						i=0;
					}

					

				} while (sym == comma); /* һ��read���ɶ�������� */
			}
			if(sym != rparen)
			{
				error(33);  /* ��ʽ����Ӧ�������� */
				while (!inset(sym, fsys))   /* �����ȣ�ֱ���յ��ϲ㺯���ĺ������ */
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
			if (sym == writesym)    /* ׼������write��䴦����read���� */
			{	getsymdo;			//���Ŷ�ȡ 
				if (sym == lparen)	//�﷨�����ж� 
				{
					do {
						getsymdo; 	//���Ŷ�ȡ 
						/*���Ӹ�ʽ�����*/
						if(sym == quotation){	// �����ʽ 
							// write("count=",count," ans=?",ans);
							// output: count=$count ans=$ans
							char tempstr[32];	// ������ʱ������ 
							int tspos = 0; 		// ���û�����ָ�� 
							while(ch!='"'){
								//printf("%c",ch);	//����ʱʹ�� 
								tempstr[tspos++]=ch;//��ȡԴ���� 
								getchdo;				
							}
							tempstr[tspos]='\0';//���������ֹ����Ȼ�������
							getchdo; 
							strcpy(str[nowstr],tempstr);// ����ȡ�����ַ������뻺���� 
							getsymdo;
							nowstr++; 			/* new! ��׼������ַ���+1 */
							if(nowstr > 32){	//�������������Ƿ���� 
								error(1);
							}
							gendo(spt, 0, nowstr-1,0);// �������������ָ�� 
						}
						/*�Ǹ�ʽ���������Ϊ�����������*/
						else{
							memcpy(nxtlev, fsys, sizeof(bool)*symnum);
							nxtlev[rparen] = true;	//���ڴ����� 
							nxtlev[comma] = true;	/* write�ĺ������Ϊ) or , */
							expressiondo(nxtlev, ptx, lev); /* ���ñ��ʽ�����˴���read��ͬ��readΪ��������ֵ */
							gendo(opr, 0, 14,0);  	/* �������ָ����ջ����ֵ */	
						}
					} while (sym == comma);
					if (sym != rparen)
					{error(33);  /* write()��ӦΪ�������ʽ */}
					else{getsymdo;}
				}
				gendo(opr, 0, 15,0);  /* ������� */}
			else
			{
				if (sym == callsym) /* ׼������call��䴦�� */
				{
					getsymdo;
					if (sym != ident)
					{
						error(14);  /* call��ӦΪ��ʶ�� */
					}
					else
					{
						i = position(id, *ptx);
						if (i == 0)
						{
							error(11);  /* ����δ�ҵ� */
						}
						else
						{
							if (table[i].kind == procedur)
							{
								gendo(cal, lev-table[i].level, table[i].adr,0);   /* ����callָ�� */
							}
							else
							{
								error(15);  /* call���ʶ��ӦΪ���� */
							}
						}
						getsymdo;
					}
				}
				else
				{
					if (sym == ifsym)   /* ׼������if��䴦�� */
					{
						getsymdo;
						memcpy(nxtlev, fsys, sizeof(bool)*symnum);
						nxtlev[thensym] = true;
						nxtlev[dosym] = true;   /* �������Ϊthen��do */
						conditiondo(nxtlev, ptx, lev); /* �������������߼����㣩���� */
						if (sym == thensym)
						{
							getsymdo;
						}
						else
						{
							error(16);  /* ȱ��then */
						}
						cx1 = cx;   /* ���浱ǰָ���ַ */
						gendo(jpc, 0, 0,0);   /* ����������תָ���ת��ַδ֪����ʱд0 */
						statementdo(fsys, ptx, lev);    /* ����then������ */
						code[cx1].a = cx;   /* ��statement�����cxΪthen�����ִ�����λ�ã�������ǰ��δ������ת��ַ */
					}
					else
					{
						if (sym == beginsym)    /* ׼�����ո�����䴦�� */
						{
							getsymdo;
							memcpy(nxtlev, fsys, sizeof(bool)*symnum);
							nxtlev[semicolon] = true;
							nxtlev[endsym] = true;  /* �������Ϊ�ֺŻ�end */
							/* ѭ��������䴦������ֱ����һ�����Ų�����俪ʼ���Ż��յ�end */
							statementdo(nxtlev, ptx, lev);

							while (inset(sym, statbegsys) || sym==semicolon)
							{
								if (sym == semicolon)
								{
									getsymdo;
								}
								else
								{
									error(10);  /* ȱ�ٷֺ� */
								}
								statementdo(nxtlev, ptx, lev);
							}
							if(sym == endsym)
							{
								getsymdo;
							}
							else
							{
								error(17);  /* ȱ��end��ֺ� */
							}
						}
						else
						{
							if (sym == whilesym)    /* ׼������while��䴦�� */
							{
								cx1 = cx;   /* �����ж�����������λ�� */
								getsymdo;
								memcpy(nxtlev, fsys, sizeof(bool)*symnum);
								nxtlev[dosym] = true;   /* �������Ϊdo */
								conditiondo(nxtlev, ptx, lev);  /* ������������ */
								cx2 = cx;   /* ����ѭ����Ľ�������һ��λ�� */
								gendo(jpc, 0, 0,0);   /* ����������ת��������ѭ���ĵ�ַδ֪ */
								if (sym == dosym)
								{
									getsymdo;
								}
								else
								{
									error(18);  /* ȱ��do */
								}
								statementdo(fsys, ptx, lev);    /* ѭ���� */
								gendo(jmp, 0, cx1,0); /* ��ͷ�����ж����� */
								code[cx2].a = cx;   /* ��������ѭ���ĵ�ַ����if���� */
							}
							/* new !*/
							else if(sym == forsym){	//�ж�for�ؼ��� 
								getsymdo;			//��ȡ�ַ� 
								if(sym == ident){	//�﷨�ж�Ӧ��Ϊ���� 
									i = position(id,*ptx);//Ѱ�ұ����ڷ��ű��е�λ�� 
									if(i == 0)error(11);//δ�ҵ��򱨴� 
									else{//�жϱ���Ӧ��Ϊ���ͻ��߸����ͣ����򽫱��� 
										if(table[i].kind != variable && table[i].kind != dvariable )
										{
											error(12);  /* ��ֵ����ʽ���� */
											i = 0;
										}
									}
									getsymdo;//���Ŷ��� 
									if(sym == becomes){//������Ҫ���ڱ������г�ʼ����ֵ 
										getsymdo;
									}
									else error(13);
									memcpy(nxtlev,fsys,sizeof(bool)*symnum);
									expressiondo(nxtlev,ptx,lev);//���ñ��ʽ�����ɸ�ֵ 
									if(i){//ջ����ֵ�浽���Ŀ���ַ�ڴ�
										gendo(sto,lev-table[i].level,table[i].adr,0);
									}
								}
								else error(17);
								cx1 = cx;//��¼��ǰ��label 
								getsymdo;//���Ŷ�ȡ 
								memcpy(nxtlev,fsys,sizeof(bool)*symnum);//������ 
								nxtlev[dosym]=true;//������ 
								conditiondo(nxtlev,ptx,lev);//���������ж���� 
								cx2 = cx;//��¼���ڵ�label 
								gendo(jpc,0,0,0);//����ֵ�ж���תָ�����ֵδָ�� 
								if(sym == dosym){//�﷨�ж� 
									getsymdo;
								}
								else error(18);//����������䣬�ж�forѭ���ڲ������ 
								statementdo(fsys,ptx,lev);
								gendo(jmp,0,cx1,0);	//���е���䶼������ʱ��������label������ת�ĵ�ַ��ֵ 
								code[cx2].a=cx;		//Ҳ����ȷ��ָ��ĵ�ַ 
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
											/*�����жϷֺ�*/
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
								memset(nxtlev, 0, sizeof(bool)*symnum); /* �������޲��ȼ��� */
								testdo(fsys, nxtlev, 19);   /* �������������ȷ�� */
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

/*���ʽ����*/

int expression(bool* fsys, int* ptx, int lev)
{
	enum symbol addop;  /* ���ڱ��������� */
	bool nxtlev[symnum];

	if(sym==plus || sym==minus) /* ��ͷ�������ţ���ʱ��ǰ���ʽ������һ�����Ļ򸺵��� */
	{
		addop = sym;    /* ���濪ͷ�������� */
		getsymdo;
		memcpy(nxtlev, fsys, sizeof(bool)*symnum);
		nxtlev[plus] = true;
		nxtlev[minus] = true;
		termdo(nxtlev, ptx, lev);   /* ������ */
		if (addop == minus)
		{
			gendo(opr,0,1,0); /* �����ͷΪ��������ȡ��ָ�� */
		}
	}
	else    /* ��ʱ���ʽ��������ļӼ� */
	{
		memcpy(nxtlev, fsys, sizeof(bool)*symnum);
		nxtlev[plus] = true;
		nxtlev[minus] = true;
		termdo(nxtlev, ptx, lev);   /* ������ */
	}
	while (sym==plus || sym==minus)
	{
		addop = sym;
		getsymdo;
		memcpy(nxtlev, fsys, sizeof(bool)*symnum);
		nxtlev[plus] = true;
		nxtlev[minus] = true;
		termdo(nxtlev, ptx, lev);   /* ������ */
		if (addop == plus)
		{
			gendo(opr, 0, 2,0);   /* ���ɼӷ�ָ�� */
		}
		else
		{
			gendo(opr, 0, 3,0);   /* ���ɼ���ָ�� */
		}
	}
	return 0;
}

/*���*/
int term(bool* fsys, int* ptx, int lev)
{
	enum symbol mulop;  /* ���ڱ���˳������� */
	bool nxtlev[symnum];

	memcpy(nxtlev, fsys, sizeof(bool)*symnum);
	nxtlev[times] = true;
	nxtlev[slash] = true;
	factordo(nxtlev, ptx, lev); /* �������� */
	while(sym==times || sym==slash)
	{
		mulop = sym;
		getsymdo;
		factordo(nxtlev, ptx, lev);
		if(mulop == times)
		{
			gendo(opr, 0, 4,0);   /* ���ɳ˷�ָ�� */
		}
		else
		{
			gendo(opr, 0, 5,0);   /* ���ɳ���ָ�� */
		}
	}
	return 0;
}

/*���Ӵ���*/
int factor(bool* fsys, int* ptx, int lev)
{
	int i;
	bool nxtlev[symnum];
	testdo(facbegsys, fsys, 24);    /* ������ӵĿ�ʼ���� */
	/* while(inset(sym, facbegsys)) */  /* ѭ��ֱ���������ӿ�ʼ���� */
	if(inset(sym,facbegsys))    /* BUG: ԭ���ķ���var1(var2+var3)�ᱻ����ʶ��Ϊ���� */
	{
		if(sym == ident)    /* ����Ϊ��������� */
		{
			i = position(id, *ptx); /* �������� */
			if (i == 0)
			{
				error(11);  /* ��ʶ��δ���� */
			}
			else
			{
				switch (table[i].kind)
				{
				case constant:  /* ����Ϊ���� */
					if(table[i].val)
					gendo(lit, 0, table[i].val,0);    /* ֱ�Ӱѳ�����ֵ��ջ */
					else gendo(lit, 0, 0,table[i].dval); /*new!ȡ����ֵ*/
					break;
				case variable:  /* ����Ϊ���� */
					gendo(lod, lev-table[i].level, table[i].adr,0);   /* �ҵ�������ַ������ֵ��ջ */
					break;
				case dvariable:  /* new!����Ϊ������� */
					gendo(lod, lev-table[i].level, table[i].adr,0);   /* �ҵ�������ַ������ֵ��ջ */
					break;
				case procedur:  /* ����Ϊ���� */
					error(21);  /* ����Ϊ���� */
					break;
				case array:
					getsymdo;				//��ȡ�ַ� 
					if(sym == lspsym){		//�ж��﷨�ṹ 
						getsymdo;			//��ȡ�ַ� 
						if(sym == number){	//��Ҫָ���±� 
							getsymdo;		//��ȡ�ַ� 
							int pos_in_table = position(id,*ptx);
							int pos = num;	//��ȡ�±���������ַ 
							if(pos <= table[pos_in_table].upper - table[pos_in_table].bottom){//Խ���ж� 
								gendo(lod, lev-table[i].level, table[pos+i].adr,0);		//ȡ��Ӧ��ַ��ֵ����ջ 
								//printf("%d %d %d\n",table[pos].adr+i+1,table[pos].adr+i,table[pos].adr);
							}
							else error(36);//��������Ӧ����Խ���ж� 
							if(sym != rspsym){//�﷨�ṹ�ж� 
								error(7);		//������ 
							}
						}
						else error(8);			//�Ƿ�ָ���±� 
					}
					else error(6);				//�Ƿ��������� 
					break;
				case tuple:
					getsymdo;//��ȡ���� 
					if(sym == lparen){		//�Ƿ������� 
						getsymdo;			//��ȡ�ַ� 
						if(sym == number){	//�Ƿ�ָ���±� 
							getsymdo;		//��ȡ�ַ� 
							int pos_in_table = position(id,*ptx);
							int pos = num;	//��ȡ�±��Ԫ���Ӧ�����еĻ���ַ 
							if(pos <= table[pos_in_table].upper - table[pos_in_table].bottom){//Խ���ж� 
								gendo(dli,0 ,0 ,heap[table[pos_in_table].bottom+num]);//ֱ�Ӵ��ڴ���ȡֵ�ŵ�ջ�� 
							}
							else error(42);	//Ԫ��Խ���ж� 
							if(sym != rparen){
								error(7);	//�����Ƿ����� 
							}
						}
						else error(8);		//�Ƿ�ָ���±� 
					}
					else error(6); 			//���÷�ʽ�Ƿ�Ϊ���� 
				}//MonkeyPeach.PL0
			}
			getsymdo;
		}
		else
		{
			if(sym == number)   /* ����Ϊ���� */
			{
				if (num > amax)
				{
					error(31);
					num = 0;
				}
				gendo(lit, 0, num,0);
				getsymdo;
			}
			if(sym == dnumber)   /* new ! ����Ϊ������ */
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
				if (sym == lparen)  /* ����Ϊ���ʽ */
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
						error(22);  /* ȱ�������� */
					}
				}
				testdo(fsys, facbegsys, 23);    /* ���Ӻ��зǷ����� */
			}
		}
	}
	return 0;
}

/*��������*/
int condition(bool* fsys, int* ptx, int lev)
{
	enum symbol relop;
	bool nxtlev[symnum];

	if(sym == oddsym)   /* ׼������odd���㴦�� */
	{
		getsymdo;
		expressiondo(fsys, ptx, lev);
		gendo(opr, 0, 6,0);   /* ����oddָ�� */
	}
	else
	{
		/* �߼����ʽ���� */
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

/*���ͳ���*///MonkeyPeach.PL0
void interpret()
{
	int p, b, t;    /* ָ��ָ�룬ָ���ַ��ջ��ָ�� */
	struct instruction i;   /* ��ŵ�ǰָ�� */
	//int s[stacksize];   /* ջ */
	
	double s[stacksize]={0.0};   /* new ! ջ */
	
	//printf("start pl0\n");
	t = 0;
	b = 0;
	p = 0;
	s[0] = s[1] = s[2] = 0;
	do {
		i = code[p];    /* ����ǰָ�� */
		p++;
		switch (i.f)
		{
		case lit:   /* ��a��ֵȡ��ջ�� */
			s[t] = i.a;
			t++;
			break;
		/* new�� ������������ */
		case dli:   /* ��a��ֵȡ��ջ�� */
			s[t] = i.d;
			t++;
			break;
		case opr:   /* ��ѧ���߼����� */
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
				/*new! ת��Ϊdouble����ջʱǧ��ע�����ͣ���Ȼ��������*/
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
				/*new! ת��Ϊdouble����ջʱǧ��ע�����ͣ���Ȼ��������*/
				scanf("%lf", &(s[t]));
				fprintf(fa2, "%lf\n", s[t]);
				t++;
				break;
			}
			break;
		/* new! �ַ�����׼����� */
		case spt:
			printf("%s",str[(int)i.a]);
			break; 
		case lod:   /* ȡ��Ե�ǰ���̵����ݻ���ַΪa���ڴ��ֵ��ջ�� */
			s[t] = s[base(i.l,s,b)+i.a];
			t++;
			break;
		case sto:   /* ջ����ֵ�浽��Ե�ǰ���̵����ݻ���ַΪa���ڴ� */
			t--;
			s[base(i.l,s,b)+i.a] = s[t];
			break;
		case stoa:  /* new ջ����ֵ�浽Ԫ���Ӧ���ڴ�ռ��� */
			t--;
			heap[i.a+i.l] = s[t];
			break;
		case cal:   /* �����ӹ��� */
			s[t] = base(i.l, s, b); /* �������̻���ַ��ջ */
			s[t+1] = b; /* �������̻���ַ��ջ������������base���� */
			s[t+2] = p; /* ����ǰָ��ָ����ջ */
			b = t;  /* �ı����ַָ��ֵΪ�¹��̵Ļ���ַ */
			p = i.a;    /* ��ת */
			break;
		case inte:  /* �����ڴ� */
			t += i.a;
			break;
		case jmp:   /* ֱ����ת */
			p = i.a;
			break;
		case jpc:   /* ������ת */
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
/* ͨ�����̻�ַ����l����̵Ļ�ַ */
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
