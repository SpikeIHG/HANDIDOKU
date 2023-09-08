#include"Utility.hpp"
#include"Hanidoku.hpp"
static Hanidoku* doku_set;
static Hanidoku mydoku;
static Map mymap_;
static Map mymap_l;
static Map mymap_r;
static Map map;

int main(void)
{
	showmenu();
	game_is_on();
}





void showmenu()
{
	printf("=================================================================================================\n");
	printf("\t\t\t\t欢迎使用DPLL与HANIDOKU系统，这是一个非常朴素的界面    ε٩(๑> ₃ <)۶з \n");
	printf("下面是我的一些简单功能  (●′ω`●) \n\n");
	printf("\t\t1.执行DPLL\t\t1.读取并保存文件\n\n");
	printf("下面是附加功能--Hanidoku(;￢д￢) (“▔□▔)\n\n");
	printf("\t\t2.生成hanidoku并进行游戏\t\t3.解决hanidoku\t\t0. 终止程序\n");
	printf("=================================================================================================\n\n");
	printf("请给我一个指令吧  （=ˇωˇ=）<(￣︶￣)>\n");
}
void game_is_on(void)
{
	int choice{ 0 };
	Stack history{ nullptr };
	mapping(mymap_);

	while (scanf("%d", &choice) && choice)
	{
		eatline();
		switch (choice)
		{
		case 1:
		{
			clear_the_stack(history);
			CNF cnf;
			char filename[100];
			int strategy{ 0 };
			int ltr_num{ 0 };
			clock_t start, finish;

			printf("请输入你想要测试的文件\n");
			scanf("%s", filename);
			eatline();
			CNF_EXACTER(cnf,filename,ltr_num);
			printf("请输入你想要使用的策略\n");
			scanf("%d", &strategy);
			eatline();
			printf("稍等片刻，程序反应中……\n");
			start = clock();
			int status=DPLL(cnf, history, strategy);
			finish = clock();
			printf("保存最后一次dpll运行的结果请输入名称\n");
			char filename2[100];
			scanf("%s", filename2);
			eatline();
			double duration = (double)(finish - start) / CLOCKS_PER_SEC;
			present_answer(cnf, filename2,ltr_num,status,duration*1000);
			printf("成功!（=ˇωˇ=）<(￣︶￣)>");
			break;
		}
		case 2:
		{
			clear_the_stack(history);
			read_doku(doku_set, "easy_hanidoku.txt", 5900);
			srand(5934);
			int idx = 1;//rand() % 239;
			char filename[] = "test.cnf";
			TranstoCNF(doku_set[idx], filename, mymap_);
			printf("skjdfjlksd");
			CNF cnf; int ltr_num{ 0 };
			CNF_EXACTER(cnf, filename, ltr_num);
			printf("gdfjlk");
			DPLL(cnf, history,1);

			FILE*out=fopen("sodu_ans.txt", "w");
			check_right_flow(out);
			Hanidoku ans, record;
			trans_to_sodu(cnf, out,ans);
			fclose(out);
			strcpy(record, ans);
			printf("\n挖洞生成一个随机的数独ε٩(๑> ₃ <)۶з 请输入想要挖去的个数\n");
			int num{ 0 };
			while (scanf("%d", &num)) {
				if (num < 5 || num>50)
					printf("挖的数量太少或者是太多了,重新输入一个数字吧\n");
				else
					break;
			}
			change_doku(record, num);
			getchar();
			system("cls");
			showmenu();
			print_doku(record);
			putchar('\n');
			int l, r, v;
			printf("请输入对应的行号 列号 与填入的值 1 1 1 .eg （输入-1 打印答案并退出 输入 0得到提示,-2 ）\n");
			while (scanf("%d %d %d", &r, &l, &v) && r != -1)
			{
				if (r != 0) {
					if (r <= 5)
					{
						int j = 5;
						for (int i = 1; i < r; ++i)
							l += (j++);
					}
					else
					{
						int j = 8;
						for (int i = 6; i < r; ++i)
							l += (j--);
						l += 35;
					}
					record[l - 1] = v + '0';
				}
				else
				{
					if (l <= 5)
					{
						int j = 5;
						for (int i = 1; i < l; ++i)
							v += (j++);
					}
					else
					{
						int j = 8;
						for (int i = 6; i < l; ++i)
							v += (j--);
						v += 35;
					}
					record[v - 1] = ans[v - 1];
				}

				getchar();
				system("cls");
				showmenu();
				print_doku(record);
				putchar('\n');
			}
			if (r == -1) {
				print_doku(ans);
				getchar();
				/*/system("cls"); */
			}
			break;
		}
		case 0:
		{
			printf("感谢您的使用，若有任何建议，都可以通过github issue 哦，——Winter  ε٩(๑> ₃ <)۶з");
			return;
			break;
		}
		default: {
			printf("是不是输入了错误的指令阿，检查一下吧  ε٩(๑> ₃ <)۶з\n");
			break;
		}
		}
		getchar();
		system("cls");
		showmenu();
	}
}
void traverse(const CNF& cnf)
{
	CNode* scan = cnf.first_clause_head->next;
	for (; scan; scan = scan->next)
	{
		Node* first_elem = scan->first_elem_r;
		printf("%d ", first_elem->value);
		for (Node* cur = first_elem->next; cur != first_elem; cur = cur->next)
			printf("%d ", cur->value);
		putchar('\n');
	}
	int count{ 0 };
	for (auto scan = cnf.first_literal_head->next; scan; scan = scan->next)
		++count;
	printf("*****%d   *****", count);
}
void check_the_stack(const Stack& s)
{
	int idx{ 1 };
	Snode* step = s;
	while (step)
	{
		printf("第%d步操作：\t", idx);
		switch (step->cls_idx) {
		case NODE:
		{
			printf("删除结点，结点的值是%d,结点所属的句子序号是%d \n", step->pos->value, step->pos->cls_idx);
			break;
		}
		case LINE:
		{
			printf("删除的是一列数，被删除的数的值是%d\n", step->line_del->first_elem_l->value);
			break;
		}
		case SECRETNUM:
		{
			printf("这是一次分段点*********************************\n");
			break;
		}
		default:
		{
			printf("删除的是一个句子，句子的序号是%d,\n", step->cls_idx);
			break;
		}
		}
		++idx; step = step->next;
	}
}
void present_answer(const CNF& cnf,char filename[], int n,int status,double time_)
{
	FILE* out = fopen(filename, "w");
	check_right_flow(out);
	
	fprintf(out, "s %d\n", status);
	if (status) {
		fprintf(out, "v ");
		for (int i = 1; i <= n; ++i)
		{
			fprintf(out, "%d ", (cnf.literal_set[i]->is_positive ? i : -i));
		}
		fprintf(out, "\n");
	}
	fprintf(out, "t %f毫秒",time_);
	fclose(out);
}
inline void featline(FILE* f)
{
	char word[100];
	while (fscanf(f, "%s", word) && strcmp(word, "cnf"))
		continue;
}
inline void eatline(void)
{
	while (getchar() != '\n')
		continue;
}
void CNF_EXACTER(CNF& cnf, char filename[], int& n)
{
	FILE* infile = fopen(filename, "r");
	check_right_flow(infile);
	featline(infile);

	fscanf(infile, "%d%d", &cnf.ltr_num, &cnf.cls_num);			// 读入对应的数量
	n = cnf.ltr_num;
	cnf.clause_set = (Cset)malloc(sizeof(CNode*) * (cnf.cls_num + 1));
	cnf.literal_set = (Lset)malloc(sizeof(LNode*) * (cnf.ltr_num + 1));
	memset(cnf.clause_set, 0, sizeof(CNode*) * (cnf.cls_num + 1));
	memset(cnf.literal_set, 0, sizeof(LNode*) * (cnf.ltr_num + 1));
	int val{ 0 };
	cnf.first_clause_head = nullptr;
	cnf.first_literal_head = nullptr;

	for (int i = 1; i <= cnf.cls_num; ++i)
	{
		CNode* new_clause = (CNode*)malloc(sizeof(CNode));
		new_clause->first_elem_r = nullptr;
		new_clause->row_value_n = 0;
		cnf.clause_set[i] = new_clause;

		if (i == 1) {
			cnf.first_clause_head = new_clause->prev = new_clause->next = new_clause;
		}
		else
		{
			cnf.clause_set[1]->prev = new_clause;
			cnf.clause_set[i - 1]->next = new_clause;
			new_clause->prev = cnf.clause_set[i - 1];
			new_clause->next = cnf.clause_set[1];
		}

		while (fscanf(infile, "%d", &val) && val)
		{
			Node* pnew = (Node*)malloc(sizeof(Node));			// 分配一个新的结点
			if (!new_clause->row_value_n) {			// 当是第一个自变量时
				pnew->next = pnew->prev = pnew;
				new_clause->first_elem_r = pnew;
			}
			else {
				new_clause->first_elem_r->prev->next = pnew;
				pnew->prev = new_clause->first_elem_r->prev;
				pnew->next = new_clause->first_elem_r;
				new_clause->first_elem_r->prev = pnew;
			}
			pnew->value = val;
			pnew->cls_idx = i;
			++new_clause->row_value_n;			// 增加字面量数的统计
			if (!cnf.literal_set[abs(val)])
			{
				LNode* new_line = (LNode*)malloc(sizeof(LNode));
				new_line->is_positive = 0;
				new_line->line_value_n = 0;
				if (!cnf.first_literal_head)
				{
					new_line->prev = new_line->next = new_line;
					cnf.first_literal_head = new_line;
				}
				else		// 还没有任何的指针
				{
					new_line->next = cnf.first_literal_head;
					new_line->prev = cnf.first_literal_head->prev;
					cnf.first_literal_head->prev->next = new_line;
					cnf.first_literal_head->prev = new_line;
				}
				// 还没有任何的指针
				cnf.literal_set[abs(val)] = new_line;
				new_line->first_elem_l = pnew;
				pnew->front = pnew->rear = pnew;
			}
			else
			{
				cnf.literal_set[abs(val)]->first_elem_l->front->rear = pnew;
				pnew->front = cnf.literal_set[abs(val)]->first_elem_l->front;
				pnew->rear = cnf.literal_set[abs(val)]->first_elem_l;
				cnf.literal_set[abs(val)]->first_elem_l->front = pnew;
			}
			++cnf.literal_set[abs(val)]->line_value_n;
		}
	}

	cnf.clause_set[0] = cnf.clause_set[cnf.cls_num];
	cnf.literal_set[0] = cnf.literal_set[cnf.ltr_num];
	CNode* tmp1 = (CNode*)malloc(sizeof(CNode));
	LNode* tmp2 = (LNode*)malloc(sizeof(LNode));
	tmp1->next = cnf.first_clause_head;
	tmp2->next = cnf.first_literal_head;
	cnf.clause_set[cnf.cls_num]->next = nullptr;
	cnf.first_literal_head->prev->next = nullptr;

	cnf.first_literal_head->prev = tmp2;
	cnf.first_clause_head->prev = tmp1;			//  目前看起来似乎也可以为 nullptr

	cnf.first_clause_head = tmp1;
	cnf.first_literal_head = tmp2;
	fclose(infile);
}
void push(Stack& s, Node* n, CNode* cls, LNode* ltr, int idx, int neg = -1)
{
	Snode* newp = (Snode*)malloc(sizeof(Snode));
	newp->clause_del = cls;
	newp->pos = n;
	newp->cls_idx = idx;
	newp->next = s;
	newp->line_del = ltr;
	newp->is_positive = neg;
	s = newp;
}
inline void stamp(Stack& s)
{
	Snode* mark = (Snode*)malloc(sizeof(Snode));
	mark->clause_del = nullptr;
	mark->line_del = nullptr;
	mark->pos = nullptr;
	mark->cls_idx = SECRETNUM;
	mark->is_positive = -1;
	mark->next = s;
	s = mark;
}
inline Status set_is_empty(const CNF& cnf)
{
	return cnf.cls_num == 0 && cnf.ltr_num == 0;
}
Status clause_is_empty(const CNF& cnf)
{
	for (CNode* scan = cnf.first_clause_head->next; scan; scan = scan->next)
		if (!scan->row_value_n)
		{
#ifdef DEBUG
			printf("\n%d是空的\n", scan->first_elem_r->cls_idx);
#endif // DEBUG

			return OK;
		}
}
void delnode(CNF& cnf, Node* cur, Stack& history)
{
	push(history, cur, nullptr, nullptr, NODE);					// 先进行回溯			就可以保证不改了
	if (cur->next != cur) {
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		if (cnf.clause_set[cur->cls_idx]->first_elem_r == cur)
			cnf.clause_set[cur->cls_idx]->first_elem_r = cur->next;			// 保证指向始终有效
	}
	if (cur->rear != cur) {
		cur->rear->front = cur->front;
		cur->front->rear = cur->rear;
		if (cnf.literal_set[abs(cur->value)]->first_elem_l == cur)
			cnf.literal_set[abs(cur->value)]->first_elem_l = cur->rear;
	}
	--cnf.clause_set[cur->cls_idx]->row_value_n;
	--cnf.literal_set[abs(cur->value)]->line_value_n;
}
void delline(CNF& cnf, LNode* cur, Stack& history)
{
	push(history, nullptr, nullptr, cur, LINE, cur->is_positive);
	//if (cnf.ltr_num == 1)
	//{
#ifdef DEBUG
		//printf("%%%%%%%%%%");
#endif // DEBUG

	//	cur->is_positive = (cur->first_elem_l->value > 0 ? 1 : 0);
	//	cnf.cls_num = 0;
	//	return;
	//}
	if (cur->next)				// 不是尾戒点
	{
		cur->next->prev = cur->prev;
		cur->prev->next = cur->next;
	}
	else
	{
		cur->prev->next = cur->next;
	}
	if (cur->first_elem_l->value > 0)
		cnf.literal_set[abs(cur->first_elem_l->value)]->is_positive = 1;
	else
		cnf.literal_set[abs(cur->first_elem_l->value)]->is_positive = 0;

	--cnf.ltr_num;
}
void delclause(CNF& cnf, Node* cur, Stack& history)
{
	push(history, nullptr, cnf.clause_set[cur->cls_idx], nullptr, cur->cls_idx);				// 先进行push 这样才不改变
	Node* scan;
	for (scan = cur; scan->next != scan; scan = scan->next)
		delnode(cnf, scan, history);
	delnode(cnf, scan, history);

#ifdef DEBUG
	if (cnf.clause_set[cur->cls_idx]->row_value_n) { printf("%d %d %BAD----------", cnf.clause_set[cur->cls_idx]->row_value_n, cur->cls_idx); exit(0); }
#endif
	// 还需要回收句子
	//if (cnf.cls_num==1)
	//{
	//	//delline(cnf, cnf.literal_set[abs(cur->value)],history);
	//	printf("%%%%%%%");
	//	cnf.cls_num = 0;
	//	return;
	//}
	if (cnf.clause_set[cur->cls_idx]->next)			// 如果删除的是头结点 如果删除的不是尾戒点
	{
		cnf.clause_set[cur->cls_idx]->next->prev = cnf.clause_set[cur->cls_idx]->prev;
		cnf.clause_set[cur->cls_idx]->prev->next = cnf.clause_set[cur->cls_idx]->next;
	}
	else {
		cnf.clause_set[cur->cls_idx]->prev->next = cnf.clause_set[cur->cls_idx]->next;
	}
	cnf.cls_num--;
}
void UnitPropgate(CNF& cnf, Stack& history)
{
	for (CNode* scan = cnf.first_clause_head->next; scan; scan = scan->next)
	{
		if (scan->row_value_n == 1)
		{
			Node* key = scan->first_elem_r;			// 拿到关键的结点
			for (Node* cur = key->rear; cur != key; cur = cur->rear)				// 先要进行上下遍历
			{
				if (cur->value == key->value)
					delclause(cnf, cur, history);
				else
					delnode(cnf, cur, history);
			}
		}
	}
}
void PureLiteralAssign(CNF& cnf, Stack& history)
{
	for (LNode* scan = cnf.first_literal_head->next; scan; scan = scan->next)
	{
		if (scan->line_value_n == 1)
		{
			delclause(cnf, scan->first_elem_l, history);
			delline(cnf, scan, history);
			// 就是赋值并且删除
		}
	}
}
void set_value(CNF& cnf, LNode* curr, Stack& history, int val)			// 赋值
{
	Node* key = curr->first_elem_l;
#ifdef DEBUG
	int count{ 0 };
#endif // DEBUG
	Node* cur;
	for (cur = key; cur->rear != cur; cur = cur->rear)
	{
#ifdef DEBUG
		++count;
#endif // DEBUG
		if (cur->value == val)
			delclause(cnf, cur, history);
		else
			delnode(cnf, cur, history);
#ifdef DEBUG
		printf("SS");

		if (count < 200)
		{
			printf("(%d)", cur->value);
		}
		if (count >= 200)
			exit(0);
#endif // DEBUG
	}
	if (cur->value == val)
		delclause(cnf, cur, history);
	else
		delnode(cnf, cur, history);
	delline(cnf, curr, history);
}
int ChooseBetterValue(const CNF& cnf, int choice)
{
	static int count{ 0 };
	++count;
	switch (choice)
	{
	case 1:	return cnf.first_literal_head->next->first_elem_l->value;
	case 2:
	{
		int lucky_num = cnf.first_literal_head->next->first_elem_l->value;
		if (count % 3 == 0)
			return lucky_num;
		int maxn = -1;
		for (LNode* scan = cnf.first_literal_head->next; scan; scan = scan->next)
		{
			if (scan->line_value_n > maxn)
			{
				maxn = scan->line_value_n;
				lucky_num = scan->first_elem_l->value;
			}
		}
		return lucky_num;
	}
	case 3:
	{
		int lucky_num = cnf.first_literal_head->next->first_elem_l->value;
		int maxn = -1;
		for (LNode* scan = cnf.first_literal_head->next; scan; scan = scan->next)
		{
			if (scan->line_value_n > maxn)
			{
				maxn = scan->line_value_n;
				lucky_num = scan->first_elem_l->value;
			}
		}
		return lucky_num;
	}
	case 4:
	{
		LNode* scan;
		for (scan = cnf.first_literal_head; scan->next; scan = scan->next);
		return scan->first_elem_l->value;
	}
	}
}
void revert(CNF& cnf, Stack& s)					// 回溯的函数
{
	while (s && s->cls_idx != SECRETNUM)
	{
		switch (s->cls_idx) {
		case NODE:
		{
			if (s->pos->next != s->pos)
			{
				s->pos->prev->next = s->pos;
				s->pos->next->prev = s->pos;
			}
			if (s->pos->front != s->pos)
			{
				s->pos->front->rear = s->pos;
				s->pos->rear->front = s->pos;
			}
			++cnf.clause_set[s->pos->cls_idx]->row_value_n;
			++cnf.literal_set[abs(s->pos->value)]->line_value_n;
			break;
		}
		case LINE:
		{
			if (s->line_del->next) {
				s->line_del->next->prev = s->line_del;
				s->line_del->prev->next = s->line_del;
			}
			else
			{
				s->line_del->prev->next = s->line_del;
			}
			s->line_del->is_positive = s->is_positive;
			++cnf.ltr_num;
			break;
		}
		default:
		{
			if (s->clause_del->next) {
				s->clause_del->next->prev = s->clause_del;
				s->clause_del->prev->next = s->clause_del;
			}
			else {
				s->clause_del->prev->next = s->clause_del;
			}
			++cnf.cls_num;
			break;
		}
		}
		Snode* del = s;
		s = s->next;
		free(del);
	}
	if (s && s->cls_idx == SECRETNUM)
	{
		Snode* del = s;
		s = s->next;
		free(del);
	}
}
Status DPLL(CNF& cnf, Stack& history,int choice=3)
{
	stamp(history);								// 每一次递归调用先打个标记
	UnitPropgate(cnf, history);
	PureLiteralAssign(cnf, history);

	if (set_is_empty(cnf)) {
		//revert(cnf, history);
		return SATISFIED;
	}
	if (clause_is_empty(cnf)) {
		revert(cnf, history);
		return DISATISFIED;
	}

	stamp(history);
	int lucky_num = ChooseBetterValue(cnf, choice);
	set_value(cnf, cnf.literal_set[abs(lucky_num)], history, lucky_num);
	cnf.literal_set[abs(lucky_num)]->is_positive = lucky_num > 0 ? 1 : 0;

	if (DPLL(cnf, history,choice)) {
		//revert(cnf, history);
		//revert(cnf, history);
		return SATISFIED;
	}
	else {
		revert(cnf, history);
		set_value(cnf, cnf.literal_set[abs(lucky_num)], history, -lucky_num);
		cnf.literal_set[abs(lucky_num)]->is_positive = lucky_num > 0 ? 0 : 1;
		if (DPLL(cnf, history,choice)) {
			//revert(cnf, history);
			return SATISFIED;
		}
		else
		{
			revert(cnf, history);
			return DISATISFIED;
		}
	}
}
void read_doku(Hanidoku*& sets, const char filename[], int size)
{
	sets = (Hanidoku*)malloc(sizeof(Hanidoku) * size);
	FILE* fp = fopen(filename, "r");
	check_right_flow(fp);

	int i{ 0 };
	while (fscanf(fp, "%s", sets[i]) && strcmp(sets[i++], ""))
		continue;
	fclose(fp);
}
void trans_to_cnf(Hanidoku doku, FILE* fp)
{
	int orig = 4;
	for (int i = 1; i <= 61; ++i)
	{
		if (doku[i + orig] != '0')
		{
			if (i <= 35)
			{
				int row{ 1 };
				int line = i;
				for (int j = 5; j <= 8; ++j)
					if (line > j)
					{
						line = line - j;
						++row;
					}
				fprintf(fp, "%d 0\n", mymap_[row][line] + doku[i + orig] - '0');
			}
			else
			{
				int row{ 6 };
				int line = i - 35;
				for (int j = 8; j >= 5; --j)
					if (line > j)
					{
						line = line - j;
						++row;
					}
					else
						break;
				fprintf(fp, "%d 0\n", mymap_[row][line] + doku[i + orig] - '0');
			}
		}
	}
}
inline void check_the_right_flow(FILE* fp)
{
	if (!fp)
		exit(EXIT_FAILURE);
}
inline void line_break(FILE* fp)
{
	fprintf(fp, "0\n");
}
void TranstoCNF(Hanidoku hanidoku, char filename[], const Map& map)
{
#ifdef DEBUG
	//int counter{ 0 };
#endif // DEBUG

	FILE* out_file = fopen(filename, "w");
	check_the_right_flow(out_file);
	int row{ 1 }, line{ 1 }, num{ 0 };
	for (int i = 1; i <= 61; ++i)
	{
		if (hanidoku[i + 4] != '0')
			++num;
	}
	fprintf(out_file, "c this is my hanidoku file , we trans the doku to CNF\n"
		"p cnf 549 %d\n", 10597 + num);
	trans_to_cnf(hanidoku, out_file);

	int seed1 = (((rand() + 43534) % 45) / 9) * 9 + 1;
	int seed2 = ((rand() % 54) / 9) * 9 + 45 + 2;
	int seed3 = ((rand() % 63) / 9) * 9 + 99 + 3;
	int seed4 = (((rand()) % 72) / 9) * 9 + 162 + 4;
	int seed5 = (((rand()) % 81) / 9) * 9 + 234 + 5;
	int seed6 = (((rand()) % 72) / 9) * 9 + 315 + 6;
	int seed7 = (((rand()) % 63) / 9) * 9 + 387 + 7;
	int seed8 = (((rand()) % 54) / 9) * 9 + 450 + 8;
	int seed9 = (((rand()) % 45) / 9) * 9 + 504 + 9;
	//fprintf(out_file, "%d 0\n", seed1);
	////fprintf(out_file, "%d 0\n", seed2);
	////fprintf(out_file, "%d 0\n", seed3);
	//fprintf(out_file, "%d 0\n", seed4);
	////fprintf(out_file, "%d 0\n", seed5);
	//fprintf(out_file, "%d 0\n", seed6);
	//fprintf(out_file, "%d 0\n", seed7);
	////fprintf(out_file, "%d 0\n", seed8);
	//fprintf(out_file, "%d 0\n", seed9);

	// 格约束
	int counter{ 0 };
	for (row = 1; row <= 5; ++row)
	{
		for (line = 1; line <= 4 + row; ++line)
		{
			for (int i = 1; i <= 9; ++i)
				for (int j = i + 1; j <= 9; ++j)
#ifdef DEBUG
				{
					++counter;
#endif // DEBUG

					fprintf(out_file, "-%d -%d 0\n", map[row][line] + i, map[row][line] + j);
#ifdef DEBUG
				}
#endif // DEBUG

			for (int i = 1; i <= 9; ++i)
				fprintf(out_file, "%d ", map[row][line] + i);
			line_break(out_file);
#ifdef DEBUG
			++counter;
#endif // DEBUG

		}
	}

	for (row = 6; row <= 9; ++row)
	{
		for (line = 1; line <= 14 - row; ++line)
		{
			for (int i = 1; i <= 9; ++i)
				for (int j = i + 1; j <= 9; ++j)
#ifdef DEBUG
				{
					++counter;
#endif // DEBUG

					fprintf(out_file, "-%d -%d 0\n", map[row][line] + i, map[row][line] + j);
#ifdef DEBUG
				}
#endif // DEBUG

			for (int i = 1; i <= 9; ++i)
				fprintf(out_file, "%d ", map[row][line] + i);
			line_break(out_file);
#ifdef DEBUG
			++counter;
#endif // DEBUG

		}
	}

	// 行约束
	int delta{ 0 };
	for (int i = 1; i <= 5; ++i)
	{
		for (int j = 1; j <= i + 4; ++j)				// 某一行的所有
		{
			for (int k = j + 1; k <= i + 4; ++k)
			{
				for (int val = 1; val <= 9; ++val)
#ifdef DEBUG
				{
					++counter;
#endif // DEBUG

					fprintf(out_file, "-%d -%d 0\n", map[i][j] + val, map[i][k] + val);
#ifdef DEBUG
				}
#endif // DEBUG

				for (int c1 = 1; c1 <= 9; ++c1)
					for (int c2 = 1; c2 <= 9; ++c2)
						if (abs(c1 - c2) >= i + 4)
#ifdef DEBUG
						{
							++counter;
#endif // DEBUG
							fprintf(out_file, "-%d -%d 0\n", map[i][j] + c1, map[i][k] + c2);
#ifdef DEBUG
						}
#endif // DEBUG

			}
		}
	}

	for (int i = 6; i <= 9; ++i)
	{
		for (int j = 1; j <= 14 - i; ++j)
		{
			for (int k = j + 1; k <= 14 - i; ++k)
			{
				for (int val = 1; val <= 9; ++val)
#ifdef DEBUG
				{
					++counter;
#endif // DEBUG
					fprintf(out_file, "-%d -%d 0\n", map[i][j] + val, map[i][k] + val);
#ifdef DEBUG
				}
#endif // DEBUG

				for (int c1 = 1; c1 <= 9; ++c1)
					for (int c2 = 1; c2 <= 9; ++c2)
						if (abs(c1 - c2) >= 14 - i)
#ifdef DEBUG
						{
							++counter;
#endif // DEBUG
							fprintf(out_file, "-%d -%d 0\n", map[i][j] + c1, map[i][k] + c2);
#ifdef DEBUG
						}
#endif // DEBUG

			}
		}
	}
	axis_traverse_l(mymap_l, map);
	axis_traverse_r(mymap_r, map);

	for (int i = 1; i <= 5; ++i)
	{
		for (int j = 1; j <= i + 4; ++j)				// 某一行的所有
		{
			for (int k = j + 1; k <= i + 4; ++k)
			{
				for (int val = 1; val <= 9; ++val)
					fprintf(out_file, "-%d -%d 0\n", mymap_l[i][j] + val, mymap_l[i][k] + val);
				for (int c1 = 1; c1 <= 9; ++c1)
					for (int c2 = 1; c2 <= 9; ++c2)
						if (abs(c1 - c2) >= i + 4)
							fprintf(out_file, "-%d -%d 0\n", mymap_l[i][j] + c1, mymap_l[i][k] + c2);
			}
		}
	}
	for (int i = 6; i <= 9; ++i)
	{
		for (int j = 1; j <= 14 - i; ++j)
		{
			for (int k = j + 1; k <= 14 - i; ++k)
			{
				for (int val = 1; val <= 9; ++val)
					fprintf(out_file, "-%d -%d 0\n", mymap_l[i][j] + val, mymap_l[i][k] + val);
				for (int c1 = 1; c1 <= 9; ++c1)
					for (int c2 = 1; c2 <= 9; ++c2)
						if (abs(c1 - c2) >= 14 - i)
							fprintf(out_file, "-%d -%d 0\n", mymap_l[i][j] + c1, mymap_l[i][k] + c2);
			}
		}
	}


	// 斜方向的两个约束
	for (int i = 1; i <= 5; ++i)
	{
		for (int j = 1; j <= i + 4; ++j)				// 某一行的所有
		{
			for (int k = j + 1; k <= i + 4; ++k)
			{
				for (int val = 1; val <= 9; ++val)
					fprintf(out_file, "-%d -%d 0\n", mymap_r[i][j] + val, mymap_r[i][k] + val);
				for (int c1 = 1; c1 <= 9; ++c1)
					for (int c2 = 1; c2 <= 9; ++c2)
						if (abs(c1 - c2) >= i + 4)
							fprintf(out_file, "-%d -%d 0\n", mymap_r[i][j] + c1, mymap_r[i][k] + c2);
			}
		}
	}
	for (int i = 6; i <= 9; ++i)
	{
		for (int j = 1; j <= 14 - i; ++j)
		{
			for (int k = j + 1; k <= 14 - i; ++k)
			{
				for (int val = 1; val <= 9; ++val)
					fprintf(out_file, "-%d -%d 0\n", mymap_r[i][j] + val, mymap_r[i][k] + val);
				for (int c1 = 1; c1 <= 9; ++c1)
					for (int c2 = 1; c2 <= 9; ++c2)
						if (abs(c1 - c2) >= 14 - i)
							fprintf(out_file, "-%d -%d 0\n", mymap_r[i][j] + c1, mymap_r[i][k] + c2);
			}
		}
	}
	fclose(out_file);
}
void clear_the_stack(Stack& s)
{
	while (s)
	{
		Snode* del = s;
		s = s->next;
		free(del);
	}
}

void trans_to_sodu(const CNF& cnf,FILE*out,Hanidoku doku)
{
	int idx{ 0 };
	for (int i = 1; i <= 549; ++i)
	{
		if (cnf.literal_set[i]->is_positive) {
			doku[idx] = i - (idx) * 9 + '0';
			fprintf(out, "%c ", i - (idx++) * 9 + '0');
		}
	}
	doku[idx] = '\0';
}
void print_doku(const Hanidoku& doku)
{
	int orig = 4;
	for (int i = 1; i <= 61; ++i)
	{
		if (i <= 35)
		{
			int line{ i };
			int row{ 0 };
			for (int j = 5; j <= 8; ++j)
				if (line > j) {
					line = line - j;
					++row;
				}
			if (line == 1) {
				putchar('\n');
				for (int t = 1; t <= 10 - row; ++t)
					putchar(' ');
			}
			printf("%d ", doku[i-1] - '0');
		}
		else
		{
			int row{ 6 };
			int line = i - 35;
			for (int j = 8; j >= 5; --j)
				if (line > j)
				{
					line = line - j;
					++row;
				}
				else
					break;
			if (line == 1) {
				putchar('\n');
				for (int t = 1; t <= row+1; ++t)
					putchar(' ');
			}
			printf("%d ", doku[i-1] - '0');
		}
	}
}
void change_doku(Hanidoku& doku, int num)
{
	srand(time(NULL));
	int idx = { 0 };
	while (num)
	{
		idx = rand() % 61;
		if (doku[idx] != '0')
		{
			doku[idx] = '0';
			--num;
		}
	}
}
