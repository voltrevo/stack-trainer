#include "AI.hpp"

#include <array>
#include <limits>
#include <vector>

const double infinity = std::numeric_limits<double>::infinity();

int Height(const unsigned short (&field)[23]) {
  for (int i = 3; i < 22; i++) {
    if (field[i] != emptyLine) {
      return 23 - i;
    }
  }

  return 0;
}

int RoofCount(const unsigned short (&field)[23]) {
  int count = 0;

  for (int i = 4; i < 22; i++) {
    auto roofs = (field[i - 1] & (field[i - 1] ^ field[i]));

    if (roofs == 0) {
      continue;
    }

    for (int j = 0; j < 10; j++) {
      if ((roofs & (leftSide >> j)) != 0) {
        count++;
      }
    }
  }

  return count;
}

std::array<double, 2> Features(const unsigned short (&field)[23]) {
  std::array<double, 2> res;

  res[0] = RoofCount(field);
  res[1] = Height(field);

  return res;
}

double Heuristic(const unsigned short (&field)[23]) {
  auto features = Features(field);
  return -(features[0] + features[1]);
}

bool findAndLock(Board& board) {
  bool stateFlags[20][10][4] = {};

  struct State {
    Pos pos;
    char rotation;
  };

  double bestHeuristic = -infinity;
  State bestState;

  std::vector<State> stateQueue;

  auto pushValidState = [&](
    const State& state,
    bool checked = false
  ) {
    bool& flag = stateFlags[state.pos.y - 2][state.pos.x][state.rotation];

    if (flag) {
      return false;
    }

    flag = true;

    auto piece = board.piece;
    piece.i = state.rotation;

    if (checked || board.checkPiece(piece, state.pos)) {
      stateQueue.push_back(state);
      return true;
    }

    return false;
  };

  pushValidState(State{.pos = board.piecePos, .rotation = board.piece.i});

  while (!stateQueue.empty()) {
    auto state = stateQueue.back();
    stateQueue.pop_back();

    // Try locking here
    {
      auto piece = board.piece;
      piece.i = state.rotation;
      state.pos.y++;

      bool check = board.checkPiece(piece, state.pos);

      if (check) {
        pushValidState(state, true);
      }

      state.pos.y--;

      if (!check) {
        auto lockBoard = board;
        lockBoard.piece = piece;
        lockBoard.piecePos = state.pos;
        lockBoard.lockPiece();
        double heuristic = Heuristic(lockBoard.field);

        if (heuristic > bestHeuristic) {
          bestHeuristic = heuristic;
          bestState = state;
        }
      }
    }

    char xMax = state.pos.x + 1;

    for (state.pos.x--; state.pos.x <= xMax; state.pos.x++) {
      bool pushed = pushValidState(state);

      if (!pushed) {
        continue;
      }

      if (board.piece.iMax == 4) {
        state.rotation = (state.rotation + 1) % 4;
        pushValidState(state);
        state.rotation = (state.rotation + 2) % 4;
        pushValidState(state);
        state.rotation = (state.rotation + 1) % 4;
      } else if (board.piece.iMax == 2) {
        state.rotation = !state.rotation;
        pushValidState(state);
        state.rotation = !state.rotation;
      }
    }
  }

  if (bestHeuristic == -infinity) {
    return false;
  }

  board.piecePos = bestState.pos;
  board.piece.i = bestState.rotation;
  board.lockPiece();

  return true;
}
