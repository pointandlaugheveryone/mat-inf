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

    bool win(const i8 setPlayer) const
    {
        const pair<int, int> directions[] = {
            {0, 1}, {1, 0}, {1, 1}, {1, -1}
        };

        for (auto [dx, dy] : directions)
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
                        if (indexAt(r + i * dx, c + i * dy) != setPlayer)
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

    int minimaxABprune(const bool turn, const int alpha, const int beta, const vii& free)
    {
        const i8 opponent = (player == 1) ? 2 : 1;
        if (win(1)) return 1;
        if (win(opponent)) return -1;
        if (free.empty()) return 0;
        if (turn)
        {
            int best = INT_MIN;
            for (int i = 0; i < free.size(); i++)
            {
                auto [x, y] = free[i];
                state[x * col + y] = player;
                vii next = free;
                next.erase(next.begin() + i);
                best = max(best,minimaxABprune(false, alpha, beta, next));
                state[x * col + y] = 0;

                if (max(alpha, best) >= beta) break;
            }
            return best;
        }

        int best = INT_MAX;
        for (int i = 0; i < free.size(); i++)
        {
            auto [x, y] = free[i];
            state[x * col + y] = opponent;
            vii next = free;
            next.erase(next.begin() + i);
            best = min(best,minimaxABprune(true, alpha, beta, next));
            state[x * col + y] = 0;

            if (alpha >= min(beta, best)) break;
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
