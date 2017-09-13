// Solve maze at compile time
// Todd Fleming 2017

#include <stdio.h>
#include <tuple>

using namespace std;

template <int rows, int cols>
struct Maze
{
    char s[rows][cols + 1];
};

template <int rows, int cols>
constexpr auto find(const Maze<rows, cols> &m, char c)
{
    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < cols; ++col)
            if (m.s[row][col] == c)
                return tuple{row, col};
    throw std::runtime_error("char not found");
}

template <typename T>
constexpr bool solve(T &m, int row, int col)
{
    if (m.s[row][col] == '$')
        return true;
    else if (m.s[row][col] == ' ')
        m.s[row][col] = '.';
    else if (m.s[row][col] != '^')
        return false;
    if (solve(m, row + 1, col) || solve(m, row - 1, col) || solve(m, row, col + 1) || solve(m, row, col - 1))
        return true;
    m.s[row][col] = ' ';
    return false;
}

template <typename T>
constexpr T solve(T m)
{
    auto[row, col] = find(m, '^');
    if (solve(m, row, col))
        return m;
    throw std::runtime_error("path not found");
}

int main()
{
    constexpr auto m = solve(Maze<13, 30>{
        "##############################",
        "#               ###          #",
        "### ####### ### ######### ####",
        "#         # #   ##           #",
        "####### ### ######### ###### #",
        "#  $    ### #         ###### #",
        "########### ################ #",
        "###                    ##### #",
        "####### ##############       #",
        "#######      #         #######",
        "############## ###############",
        "#^                           #",
        "##############################",
    });
    for (auto &s : m.s)
        printf("%s\n", s);
}
