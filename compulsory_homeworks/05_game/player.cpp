#include <bits/stdc++.h>
using namespace std;
typedef int8_t i8;
typedef vector<pair<int,int>> vii;

class Player
{
    public:
        i8* state;
        int row, col, player, winLength;

    i8 indexAt(const int r,const int c) const
    {
        return state[r * col + c];
    }

    vii freeCells() const
    {
        vector<pair<int,int>> empty;
        for (int r= 0;r<row;r++)
        {
            for (int c= 0;c<col;c++)
            {
                if (indexAt(r,c) == '0') empty.emplace_back(r,c);
            }
        }
        return empty;
    }

    bool win(const bool myPlayer) const
    {
        constexpr std::pair<int, int> directions[]
        {
            {0, 1},  {1, 0},  {1, 1}, {1, -1}, // horizon, vertical, downright, downleft
        };

        for (const auto pair : directions)
        {
            for (int r = 0; r < row; r++)
            {
                for (int c = 0; c < col; c++)
                {
                    const int endRow = r + (winLength - 1) * pair.first;
                    const int endCol = c + (winLength - 1) * pair.second;

                    if (endRow < 0 || endRow >= col || endCol < 0 || endCol >= col) continue;

                    for (int i = 0; i < winLength; i++)
                    {
                        if (myPlayer) // max
                        {
                            if (indexAt(r + i * pair.first, c + i * pair.second) != player) return false;
                        }
                        else // min
                        {
                            if (indexAt(r + i * pair.first, c + i * pair.second) == player ||
                            indexAt(r + i * pair.first, c + i * pair.second) == 0
                            )
                                return false;
                        }
                    }

                    return true;
                }
            }
        }
        return false;
    }


    int minimaxABprune(bool max)
    {
        if (freeCells().empty())
        {
            if (win(true)) return 1;
            if (win(false)) return -1;
            return 0;
        }

        if (max)
        {
            int max = -INT_MIN;
            for (int i = 0; i < row*col; i++)
            {
                if (state[i] == '0') state[i] = '1';
            }
        }
    }
};

extern "C" {

void chooseMove(int a, int b, bool max)
{

}



}
