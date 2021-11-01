#include "./include/mine.h"

Matrix::Matrix(int row, int col, block blocktype)
{
	this->row = row;
	this->col = col;
	matrix = new vector<block>(row * col, blocktype);
}

void Mine::print()
{
	/*int index1 = 1, index2 = 1;
	for (index1 = 1; index1 <= row; index1++)
	{
		for (index2 = 1; index2 <= col; index2++)
		{
			if (VisibleData(index2, index1) == VISIBLE)
			{
				switch (blockData(index2, index1))
				{
				case MINE:
					cout << "☉";
					break;
				case EMPTY:
					cout << "□";
					break;
				case MINE1:
					cout << "①";
					break;
				case MINE2:
					cout << "②";
					break;
				case MINE3:
					cout << "③";
					break;
				case MINE4:
					cout << "④";
					break;
				case MINE5:
					cout << "⑤";
					break;
				case MINE6:
					cout << "⑥";
					break;
				case MINE7:
					cout << "⑦";
					break;
				case MINE8:
					cout << "⑧";
					break;
				}
			}
			else if (VisibleData(index2, index1) == INVISIBLE)
				cout << "■";
			else if (VisibleData(index2, index1) == FLAG)
				cout << "Ψ";
			else if (VisibleData(index2, index1) == UNKNOWN)
				cout << "？";
			else
				exit(0);
		}
		cout << endl;
	}*/
}

block &Matrix::at(const int x, const int y)
{
		return matrix->at(static_cast<std::vector<block, std::allocator<block>>::size_type>(y) * col + x);
}
block &Matrix::at(const int iter)
{
	return matrix->at(iter);
}

bool Matrix::put(const int x, const int y, const block &data)
{
	if (x >= row || y >= col || x<0||y<0)
		return false;
	else
	{
		matrix->at(static_cast<std::vector<block, std::allocator<block>>::size_type>(x) * col + y) = data;
		return true;
	}
}

Mine::Mine()
{
	data_map = NULL;
	user_map = NULL;
	row = col = mine_num = flag_num = unknown_num = invisible_num = 0;
	has_mine = false;
}

Mine::Mine(const int row, const int col, const int mine_num, const int x, const int y)
{
	this->row = row;
	this->col = col;
	this->mine_num = mine_num;
	data_map = new Matrix(row, col, EMPTY);
	user_map = new Matrix(row, col, INVISIBLE);
	flag_num = unknown_num = 0;
	invisible_num = row * col;
	has_mine = false;
}

Mine::~Mine()
{
	delete (data_map);
	delete (user_map);
}

block Mine::blockData(const int x, const int y) const
{
	return data_map->at(x, y);
}

int Mine::mark(const int x, const int y)
{
	if (x > col || y > row || x < 0 || y < 0)
		return 0;
	if (VisibleData(x, y) == VISIBLE)
		return 0;
	else if (VisibleData(x, y) == INVISIBLE)
	{
		user_map->at(x, y) = FLAG;
		emit updateUserMap(x, y, user_map->at(x, y));
		flag_num++;
		invisible_num--;
		emit markchange(flag_num, unknown_num);
	}
	else if (VisibleData(x, y) == FLAG)
	{
		user_map->at(x, y) = UNKNOWN;
		emit updateUserMap(x, y, user_map->at(x, y));
		unknown_num++;
		flag_num--;
		emit markchange(flag_num, unknown_num);
	}
	else
	{
		user_map->at(x, y) = INVISIBLE;
		emit updateUserMap(x, y, user_map->at(x, y));
		unknown_num--;
		invisible_num++;
		emit markchange(flag_num, unknown_num);
	}
	return 1;
}

int Mine::click(const int x, const int y)
{
	if (has_mine == false) create_mine(x, y);
	if (x > col || y > row || x < 0 || y < 0)
		return 0;
	stack<xy> s;
	const int drow[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	const int dcol[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
	xy xy = {x, y};
	if (blockData(x, y) == EMPTY)
	{
		s.push(xy);
		while (!s.empty())
		{
			xy.x = s.top().x;
			xy.y = s.top().y;
			s.pop();
			if (blockData(xy.x, xy.y) == EMPTY)
			{
				for (int i = 0; i < 8; i++)
				{
					int nx = xy.x + dcol[i];
					int ny = xy.y + drow[i];
					struct xy nxy = {nx, ny};
					if (0 < nx && nx <= col && ny > 0 && ny <= row && VisibleData(nx, ny) == INVISIBLE && blockData(nx, ny) != MINE)
					{
						s.push(nxy);
					}
				}
				user_map->at(xy.x, xy.y) = VISIBLE;
				emit updateUserMap(xy.x, xy.y, VISIBLE);
				invisible_num--;
			}
			else {
				user_map->at(xy.x, xy.y) = VISIBLE;
				emit updateUserMap(xy.x, xy.y, VISIBLE);
				invisible_num--;
			}
		}
		return 1;
	}
	else if (blockData(x, y) == MINE)
	{
		game_loss(x,y);
		return -1;
	}
	else
	{
		if (VisibleData(x, y) == INVISIBLE)
		{
			user_map->at(x, y) = VISIBLE;
			emit updateUserMap(x, y, VISIBLE);
			invisible_num--;
			return 1;
		}
		else if (VisibleData(x, y) == VISIBLE)
		{
			int Flag_count = 0;
			for (int i = 0; i < 8; i++)
			{
				int nx = x + dcol[i];
				int ny = y + drow[i];
				if (0 <= nx && nx < col && ny >= 0 && ny < row && VisibleData(nx, ny) == FLAG)
				{
					Flag_count++;
				}
			}
			if (Flag_count >= blockData(xy.x, xy.y))
			{
				for (int i = 0; i < 8; i++)
				{
					int nx = x + dcol[i];
					int ny = y + drow[i];
					if (0 <= nx && nx < col && ny >= 0 && ny < row && VisibleData(nx, ny) == INVISIBLE)
					{
						click(nx, ny);
					}
				}
			}
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

block Mine::VisibleData(const int x, const int y) const
{
	return user_map->at(x, y);
}

int Mine::create_mine(const int x, const int y)
{
	int new_row = 0, new_col = 0;
	int mine_count = mine_num;
	for (; mine_count != 0; mine_count--)
	{
		srand((unsigned)time(NULL) + rand());
		new_row = rand() % row;
		new_col = rand() % col;
		if (!(new_row < (y + 2) && new_row >(y - 2) && new_col < (x + 2) && new_col >(x - 2)) && new_col >= 0 && new_row >= 0)
			if (data_map->at(new_col, new_row) != MINE)
				data_map->at(new_col, new_row) = MINE;
			else
				mine_count++;
		else
			mine_count++;
	}
	const int drow[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	const int dcol[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	int iter = 0;
	for (iter = 0; iter < row * col; iter++)
	{
		if (data_map->at(iter) == MINE)
			for (int i = 0; i < 8; i++)
			{
				new_row = iter / col + drow[i];
				new_col = iter % col + dcol[i];
				if (new_row >= 0 && new_row < row && new_col >= 0 && new_col < col)
					if (data_map->at(new_col, new_row) != MINE)
						data_map->at(new_col, new_row)++;
					else
						;
				else
					;
			}
		else
			;
	}
	has_mine = true;
	return 0;
}

block Mine::show(const int x, const int y)
{
	if (user_map->at(x, y) == VISIBLE) {
		return data_map->at(x, y);
	}
	else {
		return user_map->at(x, y);
	}
}

void Mine::game_loss(const int x, const int y)
{
	for (int iter = 0; iter < col * row; iter++)
	{
		if (VisibleData(iter % col, iter / col) != VISIBLE) {
			user_map->at(iter) = VISIBLE;
			emit updateUserMap(iter % col, iter / col, VISIBLE);
		}
	}
	flag_num = unknown_num = 0;
	emit markchange(flag_num, unknown_num);
	user_map->at(x, y) = EXPLODE_MINE;
	emit updateUserMap(x, y, EXPLODE_MINE);
	emit lossSignal();
}

void Mine::game_win()
{
	for (int iter = 0; iter < col * row; iter++)
	{
		if (VisibleData(iter % col, iter / col) != VISIBLE) {
			user_map->at(iter) = VISIBLE;
			emit updateUserMap(iter % col, iter / col, VISIBLE);
		}
	}
	flag_num = unknown_num = 0;
	emit markchange(flag_num, unknown_num);
	emit winSignal();
}

void Mine::checkWin()
{
	if (mine_num == flag_num) {
		int check_count = mine_num;
		for(int row_iter=0;row_iter<row;row_iter++)
			for (int col_iter = 0; col_iter < col; col_iter++) {
				if (VisibleData(col_iter, row_iter) == FLAG && blockData(col_iter, row_iter) == MINE)
					check_count--;
			}
		if (check_count == 0) {
			game_win();
		}
	}
	else if (mine_num == (invisible_num + unknown_num + flag_num)) {
		game_win();
	}
}