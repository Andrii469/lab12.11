#include <stack>
#include <iostream>
#include <string>
#include <algorithm>
#include <locale>
using namespace std;

const int OPEN_VAL = 0;
const int CLOSE_VAL = 1;
const int START_VAL = -1;

struct T_cell
{
    int i_;
    int j_;
    T_cell(int i, int j) : i_(i), j_(j)
    {}

    bool operator==(const T_cell& c)
    {
        return i_ == c.i_ && j_ == c.j_;
    }

    bool operator!=(T_cell c)
    {
        return !(*this == c);
    }
};

struct T_path_node
{
    T_cell  prev_cell_;
    T_cell  cur_cell_;

    T_path_node
    (
        T_cell  prev_cell,
        T_cell  cur_cell
    ) : prev_cell_(prev_cell), cur_cell_(cur_cell)
    {}
};

ostream& operator<<(ostream& os, const T_cell& cell)
{
    os << "(" << cell.i_ << ", " << cell.j_ << ")";
    return os;
}


typedef stack<T_path_node>  T_path_stack;

bool fill_stack(T_path_stack& path_stack)
{
    const int m = 9;
    const int n = 9;
    int labirint[m][n] = { {1, 1,  1, 1,  1, 0, 1, 1, 1},
                           {1, 0,  0, 0,  1, 0, 1, 0, 1},
                           {1, 0,  1, 0,  0, 0, 1, 0, 1},
                           {1, 0,  1, 0,  1, 0, 1, 0, 1},
                           {1, 0,  0, 0,  0, 0, 1, 0, 1},
                           {1, 0,  1, 1,  1, 1, 1, 0, 1},
                           {1, 0,  0, 1,  0, 0, 0, 0, 1},
                           {1, 1,  0, 0,  0, 1, 1, 1, 1},
                           {1, 1,  1, 1, -1, 1, 1, 1, 1} };


    for (int cur_cell_val = START_VAL; ; --cur_cell_val)
    {

        int  start_stack_size = path_stack.size();
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (labirint[i][j] == cur_cell_val)
                {
                    //Обходимо сусідні квадрати.
                    for (int  i_sosed = max(i - 1, 0);
                        i_sosed <= min(i + 1, m - 1); ++i_sosed)
                    {
                        for (int  j_sosed = std::max(j - 1, 0);
                            j_sosed <= (j + 1, n - 1); ++j_sosed)
                        {
                            //якщо стовбці і рядки співпадають і квадрат вільний, то:
                            if ((i_sosed == i || j_sosed == j)
                                && labirint[i_sosed][j_sosed] == OPEN_VAL)
                            {
                                labirint[i_sosed][j_sosed] = cur_cell_val - 1;
                                path_stack
                                    .push(
                                        T_path_node(
                                            T_cell(i, j),
                                            T_cell(i_sosed, j_sosed)) );

                                //якщо клітка крайня, то:
                                if (i_sosed == 0 || i_sosed == m - 1
                                    || j_sosed == 0 || j_sosed == n - 1)
                                {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (path_stack.size() == start_stack_size) return false;
    }
}

void print_path(T_path_stack  path_stack)
{
    cout << "The path:" << endl;
    for (;;)
    {
        T_cell  prev_cell = path_stack.top().prev_cell_;
        cout << path_stack.top().cur_cell_ << endl;
        if (path_stack.size() == 1)
        {
            std::cout << path_stack.top().prev_cell_ << endl;
            return;
        }
        while (path_stack.top().cur_cell_ != prev_cell)
        {
            path_stack.pop();
        }
    }
}

int main()
{

    T_path_stack  path_stack;

    if (!fill_stack(path_stack))
    {
        cout << "There is no way out!"//немає виходу
            << endl;
    }
    else
    {
        print_path(path_stack);
    }
    return 0;
}