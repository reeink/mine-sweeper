#include "mine.h"


Matrix::Matrix(short row, short col, block blocktype)
{
	this->row = row;
	this->col = col;
	matrix = new vector<block>(row * col, blocktype);
}

void Mine::print()
{
	int index1 = 1, index2 = 1;
	for (index1 = 1; index1 <= row; index1++) {
		for (index2 = 1; index2 <= col; index2++) {
			if (VisibleData(index2, index1) == VISIBLE) {
				switch (blockData(index2, index1)) {
				case MINE:
					cout << "¨‘";
					break;
				case EMPTY:
					cout << "¡õ";
					break;
				case MINE1:
					cout << "¢Ù";
					break;
				case MINE2:
					cout << "¢Ú";
					break;
				case MINE3:
					cout << "¢Û";
					break;
				case MINE4:
					cout << "¢Ü";
					break;
				case MINE5:
					cout << "¢Ý";
					break;
				case MINE6:
					cout << "¢Þ";
					break;
				case MINE7:
					cout << "¢ß";
					break;
				case MINE8:
					cout << "¢à";
					break;
				}
			}
			else if (VisibleData(index2, index1) == INVISIBLE) cout << "¡ö";
			else if (VisibleData(index2, index1) == FLAG) cout << "¦·";
			else if (VisibleData(index2, index1) == UNKNOWN) cout << "£¿";
			else exit(0);
		}
		cout << endl;
	}
}

block& Matrix::at(short x, short y)
{
	return matrix->at((y - 1) * col + x - 1);
}
block& Matrix::at(short iter)
{
	return matrix->at(iter);
}

bool Matrix::put(short x, short y, const block& data)
{
	if (x > row || y > col) return false;
	else {
		matrix->at((x - 1) * col + y - 1) = data;
		return true;
	}
}

Mine::Mine()
{
	data_map = NULL;
	user_map = NULL;
	row = col = mine_num = flag_num = unknown_num = 0;
}

Mine::Mine(const short row, const short col, const short mine_num, const short x, const short y)
{
	int mine_count = mine_num;
	this->row = row;
	this->col = col;
	this->mine_num = mine_num;
	data_map = new Matrix(row, col, EMPTY);
	user_map = new Matrix(row, col, INVISIBLE);
	flag_num = unknown_num = 0;
	int new_row = 0, new_col = 0;
	for (; mine_count != 0; mine_count--)
	{
		srand((unsigned)time(NULL)+ rand());
		new_row = rand() % row + 1;
		new_col = rand() % col + 1;
		if (!(new_row<(y + 2) && new_row>(y - 2) && new_col<(x + 2) && new_col>(x - 2)) && new_col > 0 && new_row > 0)
			if (data_map->at(new_col, new_row) != MINE) data_map->at(new_col, new_row)= MINE;
			else mine_count++;
		else mine_count++;
	}
	const int drow[8] = { -1,-1,-1,0,0,1,1,1 };
	const int dcol[8] = { -1,0,1,-1,1,-1,0,1 };
	int iter = 0;
	for (iter = 0; iter < row * col; iter++) {
		if (data_map->at(iter) == MINE)
			for (int i = 0; i < 8; i++) {
				new_row = iter / col + 1 + drow[i];
				new_col = iter % col + 1 + dcol[i];
				if (new_row > 0 && new_row <= row && new_col > 0 && new_col <= col)
					if (data_map->at(new_col, new_row) != MINE) data_map->at(new_col, new_row)++;
					else;
				else;
			}
		else;
	}
	click(x, y);
}

Mine::~Mine()
{
	delete(data_map);
	delete(user_map);
}

block Mine::blockData(const short x, const short y)const
{
	return data_map->at(x, y);
}

int Mine::operateMark(const short x, const short y)
{
	if (x > col || y > row || x < 0 || y < 0) return 0;
	if (VisibleData(x, y) == VISIBLE) return 0;
	else if (VisibleData(x, y) == INVISIBLE) {
		user_map->at(x, y) = FLAG;
		flag_num++;
	}
	else if (VisibleData(x, y) == FLAG) {
		user_map->at(x, y) = UNKNOWN;
		flag_num--;
	}
	else user_map->at(x, y) = INVISIBLE;
	return 1;
}

int Mine::click(const short x,const short y)
{
	if (x > col || y > row || x<0 || y<0) return 0;
	stack<xy>s;
	const int drow[8] = { -1,-1,-1,0,0,1,1,1 };
	const int dcol[8] = { -1,0,1,-1,1,-1,0,1 };
	xy xy = { x,y };
	if (blockData(x, y) == EMPTY)
	{
		s.push(xy);
		while (!s.empty())
		{
			xy.x = s.top().x;
			xy.y = s.top().y;
			s.pop();
			if (blockData(xy.x, xy.y) == EMPTY) {
				for (int i = 0; i < 8; i++) {
					short int nx = xy.x + dcol[i];
					short int ny = xy.y + drow[i];
					struct xy nxy = { nx,ny };
					if (0 < nx && nx <= col && ny > 0 && ny <= row && VisibleData(nx, ny) == INVISIBLE && blockData(nx,ny)!=MINE) {
						s.push(nxy);
					}
				}
				user_map->at(xy.x, xy.y) = VISIBLE;
			}
			else user_map->at(xy.x, xy.y) = VISIBLE;
		}
		return 1;
	}
	else if (blockData(x , y) == MINE) {
		user_map->at(x, y) = VISIBLE;
		return -1;
	}
	else {
		if (VisibleData(x , y) == INVISIBLE) {
			user_map->at(x, y) = VISIBLE;
			return 1;
		}
		else if (VisibleData(x , y) == VISIBLE) {
			short Flag_count = 0;
			for (int i = 0; i < 8; i++) {
				short int nx = xy.x + dcol[i];
				short int ny = xy.y + drow[i];
				if (0 <= nx && nx < col && ny >= 0 && ny < row && VisibleData(nx, ny) == FLAG) {
					Flag_count++;
				}
			}
			if (Flag_count >= blockData(xy.x, xy.y)) {
				for (int i = 0; i < 8; i++) {
					short int nx = xy.x + dcol[i];
					short int ny = xy.y + drow[i];
					if (0 <= nx && nx < col && ny >= 0 && ny < row && VisibleData(nx, ny) == INVISIBLE) {
						click(nx, ny);
					}
				}
			}
			return 1;
		}
		else {
			return 0;
		}
	}
}

block Mine::VisibleData(const short x, const short y)const
{
	return user_map->at(x, y);
}
