#include <algorithm>
#include <array>
#include <fstream>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;

struct MegaMillionOnePlay {
  std::array<int, 5> white_balls;
  int mega_ball = 0;

  void Clear() { *this = MegaMillionOnePlay{}; }

  std::string ToString() const {
    std::string rst;
    for (auto b : white_balls) {
      rst += std::to_string(b) + " ";
    }
    rst += "+ " + std::to_string(mega_ball);
    return rst;
  }
};

MegaMillionOnePlay GenOnePlay() {
  std::random_device rd;
  std::mt19937 rng(rd());
  MegaMillionOnePlay play;

  // 1-70
  int n_picked_white = 0;
  while(n_picked_white < 5) {
    bool exists = false;
    int r = (rng() % 70) + 1;
    for (int i = 0; i < n_picked_white; i++) {
      if (play.white_balls[i] == r) {
        exists = true;
        break;
      }
    }
    if (!exists) {
      play.white_balls[n_picked_white++] = r;
    }
  }

  std::sort(play.white_balls.begin(), play.white_balls.end());

  // 1-25
  play.mega_ball = (rng() % 25) + 1;

  return play;
}

struct WiningHistory {
  std::vector<MegaMillionOnePlay> plays;
  int64_t total_winning_prize;

  std::string ToString() const {
    std::string rst;
    rst += std::to_string(total_winning_prize) + "\n";
    for (const auto& play : plays) {
      rst += play.ToString() + "\n";
    }
    rst += "\n";
    return rst;
  }
};

class MegaMillions {
  const std::string M5 = "5 + MEGA";
  const std::string FIVE = "5";
  const std::string M4 = "4 + MEGA";
  const std::string FOUR = "4";
  const std::string M3 = "3 + MEGA";
  const std::string THREE = "3";
  const std::string M2 = "2 + MEGA";
  const std::string M1 = "1 + MEGA";
  const std::string M = "MEGA";

 public:
  void Init() {
    winning_numbers_.Clear();
    total_prize_winning_ = 0;
    wining_history_.clear();
  }

  // n: How many plays
  void Run(int n = 1) {
    if (!winning_numbers_.mega_ball) {
      std::cout << "Set the winning numbers first." << std::endl;
    }

    for (int i = 1; i <= n; i++) {
      // Randomly gen one play.
      MegaMillionOnePlay play = GenOnePlay();

      // Claim money!
      Claim(play);
    }
  }

  void Claim(const MegaMillionOnePlay& play) {
    int matched_white = 0;
    for (int i = 0; i < 5; i++) {
      matched_white += play.white_balls[i] == winning_numbers_.white_balls[i];
    }

    bool matched_mega = play.mega_ball == winning_numbers_.mega_ball;
    if (matched_mega) {
      if (matched_white == 0) {
        wining_history_[M].plays.push_back(play);
        wining_history_[M].total_winning_prize += 2;
        total_prize_winning_ += 2;
      } else if (matched_white == 1) {
        wining_history_[M1].plays.push_back(play);
        wining_history_[M1].total_winning_prize += 4;
        total_prize_winning_ += 4;
      } else if (matched_white == 2) {
        wining_history_[M2].plays.push_back(play);
        wining_history_[M2].total_winning_prize += 10;
        total_prize_winning_ += 10;
      } else if (matched_white == 3) {
        wining_history_[M3].plays.push_back(play);
        wining_history_[M3].total_winning_prize += 202;
        total_prize_winning_ += 202;
      } else if (matched_white == 4) {
        wining_history_[M4].plays.push_back(play);
        wining_history_[M4].total_winning_prize += 12314;
        total_prize_winning_ += 12314;
      } else if (matched_white == 5) {
        wining_history_[M5].plays.push_back(play);
        wining_history_[M5].total_winning_prize += 830000000;
        total_prize_winning_ += 830'000'000;
      }
    } else {
      if (matched_white == 3) {
        wining_history_[THREE].plays.push_back(play);
        wining_history_[THREE].total_winning_prize += 10;
        total_prize_winning_ += 10;
      } else if (matched_white == 4) {
        wining_history_[FOUR].plays.push_back(play);
        wining_history_[FOUR].total_winning_prize += 489;
        total_prize_winning_ += 489;
      } else if (matched_white == 5) {
        wining_history_[FIVE].plays.push_back(play);
        wining_history_[FIVE].total_winning_prize += 2'912'502;
        total_prize_winning_ += 2'912'502;
      }
    }
  }

  void Print() {
    std::cout << std::endl;
    for (const auto& [k, v] : wining_history_) {
      std::cout << k << std::endl;
      std::cout << v.ToString() << std::endl << std::endl;
    }

    std::cout << "Winning numbers: " << winning_numbers_.ToString()
              << std::endl;
    std::cout << "Total winning prize: " << total_prize_winning_ << std::endl;
  }

  void SetWinningNumbers(const MegaMillionOnePlay& winning_numbers) {
    winning_numbers_ = winning_numbers;
    std::sort(winning_numbers_.white_balls.begin(),
              winning_numbers_.white_balls.end());
  }

 private:
  int64_t total_prize_winning_;
  MegaMillionOnePlay winning_numbers_;
  std::unordered_map<std::string, WiningHistory> wining_history_;
};

int main() {
  MegaMillions machine;
  machine.SetWinningNumbers(
      {.white_balls = {7, 29, 60, 63, 66}, .mega_ball = 15});

  machine.Run(200);
  machine.Print();
  return 0;
}