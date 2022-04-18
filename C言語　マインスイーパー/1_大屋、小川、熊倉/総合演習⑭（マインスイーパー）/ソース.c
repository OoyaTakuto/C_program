/*ぜんかいのあらすじ：爆弾の数が明らかに不審な件について*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void out();
char kakunin( int, int);
int set_bom();
int set_line_bom();
void bomber1( int, int);
void oku_line_bom(int, int);
void bigbom2();
void bigbom3();
int c_bigbom(int, int);

int limit, level, l_box1, l_box2, cnt2 = 0, flg3 = 0, db = 0;
int bom[20][20] = {0};
char check[20][20];
int random_number = 0;
int log[20][20] = { 0 };

int main(void)
{
	
	int a, b, c = 0, g, h, x, y, cnt = 1, flg = 0, flg2 = 0, b_limit = 0, box = 0, b_cnt = 0, b_box = 0, b_okiba = 0, bomm, cation = 0;
	
	char hanayama;

	while (1) {
		srand((unsigned int)time(NULL));
		printf("難易度を選択してください（０：デバッグ１　１：デバッグ２　２：ノーマル１　３：ノーマル２　４：ハード１　５：ハード２）：");
		scanf("%d", &level);
		flg =flg2 = flg3 = b_cnt = b_okiba = b_box = bomm = 0;
		c = 0;
		cnt2 = 1;
		check[20][20];
		memset(check, 0, sizeof(check));
		bom[20][20];
		memset(bom, 0, sizeof(bom));
		log[20][20];
		memset(log, 0, sizeof(log));
		while (flg == 0) {
			switch (level) {
			case 0:
				limit = 5;
				b_limit = 3;
				bomm = b_limit+1;
				cnt = 18;
				l_box1 = set_line_bom();
				flg = 2;
				break;
			case 1:
				limit = 5;
				b_limit = 3;
				bomm = b_limit+4;
				cnt = 19;
				bigbom2();
				flg = 1;
				break;
			case 2:
				limit = 10;
				do {
					b_limit = rand() % 9 + 6;
				} while (b_limit > 8);
				cnt = (100 - (b_limit + 4)) + 1;
				bomm = b_limit + 4;
				bigbom2();
				flg = 1;
				break;
			case 3:
				limit = 10;
				do {
					b_limit = rand() % 9 + 6;
				} while (b_limit > 8);
				cnt = (100 - (b_limit + limit)) + 1;
				bomm = b_limit + 1;
				l_box1 = set_line_bom();
				flg = 2;
				break;
			case 4:
				limit = 20;
				do {
					b_limit = rand() % 17 + 12;
				} while (b_limit > 16);
				printf("%d\n", b_limit);
				cnt = (400 - (b_limit + 9)) + 1;
				bomm = b_limit + 9;
				bigbom3();
				flg = 3;
				break;
			case 5:
				limit = 20;
				do {
					b_limit = rand() % 17 + 12;
				}while (b_limit > 16);
				cnt = (400 - (b_limit + limit)) + 1;
				bomm = b_limit + 1;
				l_box1 = set_line_bom();
				flg = 4;
				break;
			default:
				printf("数字の2～5を入力してください\n");
				break;
			}
		}

		while (c < b_limit) {
			flg = 0;
			while (flg == 0) {
				a = set_bom();
				b = set_bom();
				if (bom[a][b] != 1 && bom[a][b] != 2) {
					bom[a][b] = 1;
					flg = 1;
				}
			}
			c++;
		}

		out();

		do {
			flg2 = 0;
			printf("\n爆弾数：%d個\n", bomm);
			printf("場所を入力してください（x y）[%d 個目]:\n", cnt2);
			scanf("%d", &x);
			scanf("%d", &y);
			x = x - 1;
			y = y - 1;
			while (flg2 == 0) {
				if (x >= limit || y >= limit) {
					printf("盤面の外の座標です。もう一度入力してください\n");
					scanf("%d", &x);
					scanf("%d", &y);
					x = x - 1;
					y = y - 1;
				}
				else if (log[x][y] == 1) {		/*11/17　ここまで：何故かすでに開けた場所を何回も開けられるところで躓いた*/
					printf("すでに開けた場所です。もう一度入力してください（x y）[%d 回目]:\n", cnt2+1);
					scanf("%d", &x);
					scanf("%d", &y);
					x = x - 1;
					y = y - 1;
				}
				else {
					flg2 = 1;
				}
			}
			log[x][y] = 1;

			if (bom[x][y] == 1) {
				printf("爆弾！\n");
				flg3 = 1;
			}
			else if (bom[x][y] == 2) {
				check[x][y] = '!';
				out();
			}
			else {
				a = kakunin(x, y);
				check[x][y] = a;
				out();
				cnt2++;
			}
			if (cnt2 == cnt) {
				printf("成功！\n");
				flg3 = 1;
			}
			switch (level) {
			case 0:
				if (random_number == 1) {
					if (b_cnt == limit - 1) {
						cation = 0;
					}
					else {
						cation = b_cnt + 1;
					}
					box = bom[l_box1][b_cnt];
					bom[l_box1][b_cnt] = bom[l_box1][cation];
					bom[l_box1][cation] = box;
				}
				else if (random_number == 2) {
					if (b_cnt == limit - 1) {
						cation = 0;
					}
					else {
						cation = b_cnt + 1;
					}
					box = bom[b_cnt][l_box1];
					bom[b_cnt][l_box1] = bom[cation][l_box1];
					bom[cation][l_box1] = box;
				}
				b_cnt = cation;
				break;
			case 3:
				if (random_number == 1) {
					if (b_cnt == limit - 1) {
						cation = 0;
					}
					else {
						cation = b_cnt + 1;
					}
					box = bom[l_box1][b_cnt];
					bom[l_box1][b_cnt] = bom[l_box1][cation];
					bom[l_box1][cation] = box;
				}
				else if (random_number == 2) {
					if (b_cnt == limit - 1) {
						cation = 0;
					}
					else {
						cation = b_cnt + 1;
					}
					box = bom[b_cnt][l_box1];
					bom[b_cnt][l_box1] = bom[cation][l_box1];
					bom[cation][l_box1] = box;
				}
				b_cnt = cation;
				break;
			case 5:
				do {
					do{
						b_box = rand() % limit + 0;
					} while (b_box >= limit || b_okiba == b_box);
				} while (b_cnt == b_box);
				if (random_number == 1) {
					box = bom[l_box1][b_cnt];
					bom[l_box1][b_cnt] = bom[l_box1][b_box];
					bom[l_box1][b_box] = box;
				}
				else if (random_number == 2) {
					box = bom[b_cnt][l_box1];
					bom[b_cnt][l_box1] = bom[b_box][l_box1];
					bom[b_box][l_box1] = box;
				}
				b_cnt = b_box;
				b_okiba = b_box;
				break;
			}
		} while (flg3 == 0);
		
		out();

		printf("もう一度遊びますか？（y/n）：");
		do {
			rewind(stdin);
			scanf("%c", &hanayama);
			if (hanayama == 'n') {
				flg3 = 0;
			}
			else if (hanayama == 'y') {
				flg3 = 2;
			}
			else {
				printf("不正な入力です。もう一度入力してください：");
			}
		} while (flg3 == 1);

		if (flg3 == 0) {
			break;
		}

	}
	return 0;
}

void out()
{
	int i, j;
	printf("   ");
	for (i = 1; i <= limit; i++) {
		printf("%2d", i);
	}
	printf("\n");
	if (limit == 5)
		printf("  +----------+\n");
	else if (limit == 10)
		printf("  +---------------------+\n");
	else
		printf("  +-----------------------------------------+\n");
	for (i = 0; i < limit; i++) {
		printf("%2d|", i + 1);
			for (j = 0; j < limit; j++) {
				if (check[i][j] == '!') {
					printf("%c", check[i][j]);
				}
				else if ((db == 1 ||flg3 == 1) && bom[i][j] == 1) {
					printf("■");
				}
				else if ((db == 1 || flg3 == 1) && bom[i][j] == 2 && check[i][j] == 0) {
					printf("◆");
				}
				else if (check[i][j] == NULL) {
					printf("  ");
				}
				else {
					printf(" %c", check[i][j]);
				}
			}
			printf(" |\n");
	}
	if (limit == 5)
		printf("  +----------+\n");
	else if (limit == 10) {
		printf("  +---------------------+\n");
	}
	else {
		printf("  +-----------------------------------------+\n");
	}
}


char kakunin(int x, int y)
{
	int edword;
	char cnt = '0';

	if (bom[x - 1][y] == 1 && x > 0) {
		cnt++;
	}
	if (bom[x + 1][y] == 1 && x <=limit ) {
		cnt++;
	}
	if (bom[x][y - 1] == 1 && y > 0) {
		cnt++;
	}
	if (bom[x][y + 1] == 1 && y <= limit) {
		cnt++;
	}
	if (bom[x - 1][y - 1] == 1 && (x > 0) && (y > 0)) {
		cnt++;
	}
	if (bom[x + 1][y - 1] == 1 && (x <= limit) && (y > 0)) {
		cnt++;
	}
	if (bom[x - 1][y + 1] == 1 && (x > 0) && (y <= limit)) {
		cnt++;
	}
	if (bom[x + 1][y + 1] == 1 && (x <= limit) && (y < limit)) {
		cnt++;
	}

	if (cnt == '0') {
		if ((x + 1 < limit) && check[x + 1][y] == 0) {
			bomber1(x + 1, y);
		}
		if (((x - 1) >= 0) && check[x - 1][y] == 0) {
			bomber1(x - 1, y);
		}
		if ((y + 1 < limit) && check[x][y + 1] == 0) {
			bomber1(x, y + 1);
		}
		if ((y - 1 >= 0) && check[x][y - 1] == 0) {
			bomber1(x, y - 1);
		}
		if (x + 1 < limit && y + 1 < limit && check[x + 1][y + 1] == 0) {
			bomber1(x + 1, y + 1);
		}
		if (x + 1 < limit && y - 1 >= 0 && check[x + 1][y - 1] == 0) {
			bomber1(x + 1, y - 1);
		}
		if (x - 1 >= 0 && y + 1 < limit && check[x - 1][y + 1] == 0) {
			bomber1(x - 1, y + 1);
		}
		if (x - 1 >= 0 && y - 1 >= 0 && check[x - 1][y - 1] == 0) {
			bomber1(x - 1, y - 1);
		}
	}
	return cnt;
}

void bomber1(int x, int y)
{
	char cnt = '0';
	if (bom[x][y] == 2) {
		cnt = '!';
	}
	else {
		if (bom[x - 1][y] == 1 && x > 0) {
			cnt++;
		}
		if (bom[x + 1][y] == 1 && x <= limit) {
			cnt++;
		}
		if (bom[x][y - 1] == 1 && y > 0) {
			cnt++;
		}
		if (bom[x][y + 1] == 1 && y <= limit) {
			cnt++;
		}
		if (bom[x - 1][y - 1] == 1 && (x > 0) && (y > 0)) {
			cnt++;
		}
		if (bom[x + 1][y - 1] == 1 && (x <= limit) && (y > 0)) {
			cnt++;
		}
		if (bom[x - 1][y + 1] == 1 && (x > 0) && (y <= limit)) {
			cnt++;
		}
		if (bom[x + 1][y + 1] == 1 && (x <= limit) && (y < limit)) {
			cnt++;
		}
	}

	log[x][y] = 1;
	check[x][y] = cnt;
	if (x >= 0 && y >= 0 && x < limit && y < limit) {
		cnt2++;
	}
}

int set_bom()
{
	int a;
		do {
			a = rand() % limit + 0;
		} while (a >= limit);
	
	return a;
}

void bigbom2() {
	int a, b, flg = 0;
	do {
		do {
			a = rand() % (limit - 1) + 0;
		} while (a >= (limit - 1));
		do {
			b = rand() % (limit - 1) + 0;
		} while (b >= (limit - 1));
		flg = c_bigbom(a, b);
	} while (flg == 1);
	bom[a][b] = 1;
	bom[a + 1][b] = 1;
	bom[a][b + 1] = 1;
	bom[a + 1][b + 1] = 1;
}

void bigbom3() {
	int a, b, flg = 0;
	do {
		do {
			a = rand() % (limit - 2) + 0;
		} while (a >= (limit - 2));
		do {
			b = rand() % (limit - 2) + 0;
		} while (b >= (limit - 2));
		flg = c_bigbom(a, b);
	} while (flg == 1);
	bom[a][b] = 1;
	bom[a + 1][b] = 1;
	bom[a + 2][b] = 1;
	bom[a][b + 1] = 1;
	bom[a][b + 2] = 1;
	bom[a + 1][b + 1] = 1;
	bom[a + 2][b + 1] = 1;
	bom[a + 1][b + 2] = 1;
	bom[a + 2][b + 2] = 1;

}

int c_bigbom(int a, int b)
{
	int i, j, flg = 0;
	if (limit == 10) {
		for (i = a; i <= a + 1; i++) {
			for (j = b; j <= b + 1; j++) {
				if (bom[i][j] == 1) {
					flg = 1;
				}
			}
		}
	}
	else {
		for (i = a; i <= a + 2; i++) {
			for (j = b; j <= b + 2; j++) {
				if (bom[i][j] == 1) {
					flg = 1;
				}
			}
		}
	}

	return flg;
}

int set_line_bom() 
{
	int flg = 0, i = 0;
	
	/////////////////////////////
	int limit_random = 0;
	do {
		random_number = rand() % 3 + 1;
	} while (random_number > 2);
	switch (random_number) {
	case 1:
		do {
			do {
				limit_random = rand() % limit + 0;
			} while (limit_random > (limit - 1));
			while (i < limit) {
				if (bom[limit_random][i] == 1) {
					flg = 0;
					break;
				}
				else {
					flg = 1;
				}
				i++;
			}
		} while (flg == 0);
		break;
	case 2:
		do {
			do {
				limit_random = rand() % limit + 0;
			} while (limit_random > (limit - 1));
			while (i < limit) {
				if (bom[i][limit_random] == 1) {
					flg = 0;
					break;
				}
				else {
					flg = 1;
				}
				i++;
			}
		} while (flg == 0);
		break;
	}

	oku_line_bom(random_number, limit_random);
	return limit_random;
	//////////////////////////////////
}

void oku_line_bom(int xy, int bangou)
{
	int i;

	switch (xy) {
	case 1:
		bom[bangou][0] = 1;
		for (i = 1; i < limit; i++) {
			bom[bangou][i] = 2;
		}
		break;
	case 2:
		bom[0][bangou] = 1;
		for (i = 1; i < limit; i++) {
			bom[i][bangou] = 2;
		}
		break;
	}
	//　11/16 ここまで（ライン爆弾埋め込みまで　次回はライン爆弾を動かすプログラムを作りたいなぁとボブは訝しんだ）
}