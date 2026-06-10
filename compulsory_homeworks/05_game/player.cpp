#include <bits/stdc++.h>
using namespace std;
typedef int8_t i8;
typedef vector<pair<int, int>> vii;

class Player
{
public:
    i8* state;
    int row, col;
    int player, winLength;

    i8 indexAt(const int r, const int c) const
    {
        return state[r * col + c];
    }

    vii freeCells() const
    {
        vector<pair<int, int>> empty;
        for (int r = 0; r < row; r++)
            for (int c = 0; c < col; c++)
                if (indexAt(r, c) == 0) empty.emplace_back(r, c);

        return empty;
    }

    bool win(const bool myPlayer) const // checks if winLenth is reached in some direction
    {
        constexpr std::pair<int, int> directions[]
        {
            {0, 1}, {1, 0}, {1, 1}, {1, -1}, // horizon, vertical, downright, downleft
        };

        for (const auto [dx, dy] : directions)
        {
            for (int r = 0; r < row; r++)
            {
                for (int c = 0; c < col; c++)
                {
                    const int endrow = r + (winLength - 1) * dx;
                    const int endcol = c + (winLength - 1) * dy;
                    if (endrow < 0 || endrow >= row || endcol < 0 || endcol >= col) continue;
                    bool isWin = true;
                    for (int i = 0; i < winLength; i++)
                    {
                        if (indexAt(r + i * dx, c + i * dy) != player)
                        {
                            isWin = false;
                            break;
                        }
                    }
                    if (isWin) return true;
                }
            }
        }
        return false;
    }


    int minimaxABprune(const bool turn, int alpha, int beta, vii &free)
    {
        if (win(true)) return 1;
        if (win(false)) return -1;

        const i8 me = player;
        const i8 id = (player == 1) ? 2 : 1;
        if (turn)
        {
            int best = INT_MIN;
            for (auto [x, y] : free)
            {
                state[x * col + y] = me;
                best = max(best, minimaxABprune(false, alpha, beta, free));
                state[x * col + y] = 0;

                alpha = max(alpha, best);
                if (alpha>=beta) break;
            }
            return best;
        }

        int best = INT_MAX;
        for (auto [x, y] : free)
        {
            state[x * col + y] = id;
            best = min(best, minimaxABprune(true, alpha, beta, free));
            state[x * col + y] = 0;

            beta = min(beta, best);
            if (alpha>=beta) break;
        }
        return best;
    }

    Player(i8* s, const int r,const int c, const int id, const int len)
    {
        state = s;
        row = r;
        col = c;
        player = id;
        winLength = len;
    }
};

extern "C" {

void chooseMove(
    i8* state,
    const int row, const int col,
    const int playerID,
    const int winLength,
    int* outrow, int* outcol)
{
    Player p{state, row, col, playerID, winLength};
    vii free = p.freeCells();
    if (free.empty()) return;

    int bestScore = INT_MIN;
    for (auto [r, c] : free)
    {
        state[r * col + c] = playerID;
        const int score = p.minimaxABprune(false, INT_MIN, INT_MAX, free);
        state[r * col + c] = 0;

        if (score > bestScore)
        {
            bestScore = score;
            *outrow = r;
            *outcol = c;
        }
    }
}

}
