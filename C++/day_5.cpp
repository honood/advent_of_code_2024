// https://adventofcode.com/2024/day/5
//
// clang++ -std=gnu++20 -stdlib=libc++ day_5.cpp -o day_5 && ./day_5 && rm day_5

#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <iostream>

constexpr std::string raw_input();

auto parse_input(std::string const& input) {
  std::istringstream iss{input};
  while (iss.peek() == '\n') {
    iss.get();
  }

  std::unordered_map<int, std::unordered_set<int>> rules{};
  std::string line{};
  while (std::getline(iss, line) && !line.empty()) {
    size_t pos = line.find('|');
    int first = std::stoi(line.substr(0, pos));
    int second = std::stoi(line.substr(pos + 1));
    rules[first].emplace(second);
  }

  std::vector<std::vector<int>> updates{};
  while (std::getline(iss, line) && !line.empty()) {
    std::istringstream line_iss{line};
    std::vector<int> update{};
    std::string page{};
    while (std::getline(line_iss, page, ',')) {
      update.emplace_back(std::stoi(page));
    }
    if (!update.empty()) {
      updates.emplace_back(std::move(update));
    }
  }

  return std::pair{rules, updates};
}

bool is_correct_update(std::vector<int> const& update,
                       std::unordered_map<int, std::unordered_set<int>> const& rules) {
  return std::is_sorted(update.begin(), update.end(), [&rules](int lhs, int rhs) {
    return rules.contains(lhs) && rules.at(lhs).contains(rhs);
  });
}

void sort_update(std::vector<int>& update,
                 std::unordered_map<int, std::unordered_set<int>> const& rules) {
  std::sort(update.begin(), update.end(), [&rules](int lhs, int rhs) {
    return rules.contains(lhs) && rules.at(lhs).contains(rhs);
  });
}

int add_up_middle_page_nums(std::vector<int> mid_pages) {
  return std::reduce(mid_pages.cbegin(), mid_pages.cend());
}

int main() {
  auto [rules, updates] = parse_input(raw_input());

  std::vector<int> part1_mid_pages{};
  std::vector<int> part2_mid_pages{};
  for (auto& update : updates) {
    if (is_correct_update(update, rules)) {
      part1_mid_pages.emplace_back(update[update.size() / 2]);
    } else {
      sort_update(update, rules);
      part2_mid_pages.emplace_back(update[update.size() / 2]);
    }
  }

  int part1_sum = add_up_middle_page_nums(part1_mid_pages);
  assert(part1_sum == 4569);
  std::cout << "What do you get if you add up the middle page number from those correctly-ordered updates? " << part1_sum << '\n';

  int part2_sum = add_up_middle_page_nums(part2_mid_pages);
  assert(part2_sum == 6456);
  std::cout << "What do you get if you add up the middle page numbers after correctly ordering just those updates? " << part2_sum << '\n';
}

constexpr std::string raw_input() {
  return R"(
96|15
69|95
69|66
41|61
41|26
41|28
66|75
66|96
66|99
66|95
25|74
25|89
25|48
25|61
25|75
11|74
11|26
11|51
11|82
11|95
11|61
17|58
17|63
17|41
17|39
17|62
17|64
17|46
63|25
63|27
63|46
63|24
63|12
63|53
63|11
63|52
72|24
72|11
72|23
72|85
72|61
72|82
72|53
72|36
72|95
61|74
61|83
61|91
61|93
61|87
61|52
61|69
61|51
61|42
61|27
19|36
19|89
19|75
19|85
19|25
19|28
19|65
19|52
19|41
19|46
19|64
39|23
39|96
39|64
39|12
39|82
39|15
39|95
39|99
39|85
39|36
39|25
39|61
58|25
58|63
58|65
58|23
58|95
58|39
58|36
58|64
58|22
58|82
58|72
58|75
58|89
75|74
75|87
75|61
75|89
75|99
75|18
75|53
75|11
75|88
75|48
75|28
75|82
75|91
75|51
89|69
89|26
89|24
89|87
89|74
89|52
89|67
89|17
89|91
89|86
89|27
89|85
89|93
89|88
89|62
36|53
36|67
36|92
36|93
36|82
36|85
36|28
36|18
36|91
36|74
36|52
36|24
36|42
36|87
36|26
36|86
27|17
27|91
27|69
27|48
27|66
27|34
27|83
27|19
27|26
27|22
27|96
27|93
27|18
27|72
27|67
27|15
27|39
91|72
91|46
91|41
91|17
91|66
91|63
91|39
91|93
91|15
91|96
91|34
91|12
91|83
91|69
91|42
91|58
91|22
91|62
15|63
15|65
15|85
15|82
15|36
15|75
15|88
15|61
15|95
15|52
15|28
15|74
15|11
15|12
15|46
15|53
15|41
15|23
15|87
93|46
93|41
93|25
93|75
93|72
93|66
93|99
93|12
93|58
93|22
93|17
93|15
93|39
93|65
93|63
93|62
93|79
93|11
93|64
93|95
28|51
28|72
28|22
28|91
28|17
28|26
28|79
28|18
28|62
28|34
28|67
28|69
28|93
28|58
28|39
28|48
28|74
28|87
28|86
28|42
28|92
67|91
67|41
67|17
67|12
67|79
67|58
67|96
67|72
67|63
67|65
67|42
67|46
67|39
67|86
67|25
67|93
67|22
67|62
67|69
67|66
67|34
67|83
23|34
23|93
23|82
23|24
23|87
23|69
23|83
23|18
23|67
23|85
23|26
23|52
23|88
23|51
23|89
23|61
23|48
23|53
23|36
23|28
23|27
23|92
23|74
26|34
26|66
26|93
26|96
26|63
26|62
26|65
26|22
26|67
26|69
26|12
26|17
26|15
26|48
26|91
26|39
26|86
26|19
26|51
26|83
26|72
26|42
26|79
26|58
12|23
12|82
12|11
12|27
12|46
12|25
12|92
12|61
12|18
12|85
12|75
12|53
12|52
12|89
12|41
12|88
12|87
12|74
12|99
12|95
12|36
12|64
12|24
12|28
24|52
24|18
24|53
24|42
24|92
24|48
24|66
24|58
24|88
24|62
24|93
24|69
24|27
24|91
24|67
24|34
24|51
24|74
24|17
24|83
24|26
24|87
24|28
24|86
62|79
62|58
62|96
62|41
62|22
62|11
62|15
62|65
62|36
62|75
62|64
62|82
62|99
62|95
62|66
62|46
62|72
62|23
62|12
62|61
62|19
62|39
62|63
62|25
48|65
48|39
48|93
48|15
48|62
48|67
48|51
48|19
48|79
48|42
48|66
48|96
48|17
48|72
48|91
48|34
48|41
48|86
48|22
48|58
48|63
48|69
48|12
48|83
85|74
85|42
85|17
85|26
85|91
85|53
85|67
85|87
85|88
85|62
85|51
85|58
85|83
85|69
85|24
85|52
85|34
85|27
85|28
85|92
85|48
85|86
85|18
85|93
83|15
83|72
83|66
83|86
83|62
83|65
83|17
83|79
83|58
83|64
83|22
83|12
83|11
83|39
83|25
83|63
83|41
83|96
83|42
83|69
83|75
83|46
83|19
83|93
64|75
64|26
64|48
64|27
64|51
64|87
64|74
64|92
64|95
64|85
64|18
64|52
64|82
64|11
64|61
64|28
64|53
64|23
64|36
64|88
64|24
64|89
64|67
64|99
99|83
99|82
99|18
99|91
99|53
99|89
99|48
99|27
99|69
99|24
99|88
99|74
99|52
99|28
99|36
99|34
99|92
99|23
99|85
99|87
99|61
99|67
99|26
99|51
42|17
42|65
42|72
42|63
42|15
42|12
42|99
42|66
42|75
42|62
42|22
42|95
42|19
42|58
42|46
42|11
42|96
42|39
42|23
42|25
42|86
42|64
42|79
42|41
51|69
51|58
51|79
51|25
51|63
51|17
51|65
51|67
51|41
51|39
51|19
51|62
51|93
51|12
51|83
51|86
51|42
51|91
51|34
51|66
51|15
51|72
51|22
51|96
87|58
87|51
87|96
87|42
87|93
87|83
87|19
87|17
87|72
87|48
87|22
87|79
87|39
87|67
87|62
87|86
87|92
87|27
87|34
87|69
87|66
87|91
87|18
87|26
46|87
46|64
46|28
46|74
46|24
46|26
46|27
46|85
46|61
46|48
46|18
46|95
46|89
46|88
46|36
46|92
46|23
46|75
46|11
46|82
46|53
46|52
46|51
46|99
22|95
22|41
22|99
22|63
22|61
22|15
22|39
22|82
22|85
22|96
22|64
22|23
22|11
22|65
22|46
22|12
22|19
22|72
22|24
22|89
22|52
22|25
22|75
22|36
74|39
74|83
74|93
74|48
74|51
74|67
74|42
74|34
74|17
74|27
74|58
74|72
74|18
74|91
74|22
74|62
74|69
74|86
74|87
74|79
74|19
74|66
74|26
74|92
86|62
86|99
86|19
86|96
86|23
86|11
86|65
86|58
86|15
86|61
86|66
86|79
86|17
86|95
86|25
86|75
86|22
86|46
86|72
86|41
86|12
86|64
86|63
86|39
52|17
52|88
52|93
52|62
52|92
52|48
52|91
52|69
52|28
52|83
52|74
52|27
52|86
52|26
52|79
52|51
52|34
52|66
52|18
52|87
52|42
52|58
52|53
52|67
53|93
53|26
53|87
53|48
53|86
53|67
53|74
53|42
53|17
53|92
53|62
53|58
53|66
53|39
53|51
53|27
53|79
53|28
53|91
53|83
53|69
53|34
53|22
53|18
82|52
82|85
82|24
82|88
82|74
82|17
82|48
82|67
82|53
82|26
82|83
82|92
82|28
82|51
82|69
82|18
82|27
82|87
82|34
82|86
82|42
82|89
82|93
82|91
65|74
65|28
65|99
65|88
65|64
65|52
65|61
65|46
65|27
65|24
65|53
65|63
65|95
65|85
65|75
65|36
65|41
65|87
65|89
65|11
65|12
65|23
65|25
65|82
34|66
34|19
34|39
34|83
34|22
34|72
34|64
34|93
34|79
34|12
34|15
34|86
34|75
34|41
34|96
34|62
34|69
34|65
34|46
34|63
34|17
34|58
34|42
34|25
95|36
95|18
95|52
95|67
95|24
95|89
95|92
95|82
95|88
95|48
95|61
95|26
95|53
95|74
95|28
95|51
95|91
95|87
95|23
95|85
95|34
95|83
95|27
95|99
88|53
88|26
88|91
88|69
88|28
88|17
88|86
88|62
88|83
88|58
88|48
88|87
88|22
88|27
88|42
88|51
88|92
88|66
88|18
88|34
88|93
88|74
88|67
88|79
92|17
92|91
92|83
92|34
92|69
92|51
92|42
92|93
92|15
92|86
92|62
92|67
92|63
92|39
92|19
92|26
92|72
92|66
92|48
92|79
92|65
92|58
92|22
92|96
18|42
18|15
18|22
18|67
18|62
18|58
18|86
18|39
18|17
18|66
18|26
18|34
18|83
18|72
18|96
18|92
18|19
18|79
18|69
18|51
18|93
18|65
18|91
18|48
79|85
79|15
79|65
79|89
79|39
79|75
79|11
79|61
79|63
79|12
79|41
79|72
79|82
79|19
79|36
79|99
79|24
79|64
79|25
79|46
79|95
79|22
79|96
79|23
96|74
96|95
96|85
96|65
96|52
96|25
96|23
96|36
96|89
96|53
96|24
96|11
96|41
96|64
96|88
96|63
96|99
96|61
96|46
96|75
96|28
96|12
96|82
69|12
69|62
69|65
69|86
69|79
69|11
69|58
69|17
69|63
69|15
69|93
69|39
69|75
69|42
69|46
69|41
69|96
69|64
69|72
69|19
69|25
69|22
41|18
41|64
41|52
41|74
41|23
41|95
41|53
41|89
41|85
41|25
41|36
41|82
41|99
41|46
41|87
41|92
41|27
41|75
41|11
41|88
41|24
66|23
66|41
66|22
66|25
66|79
66|11
66|82
66|15
66|64
66|61
66|36
66|12
66|19
66|65
66|85
66|39
66|46
66|63
66|72
66|89
25|88
25|26
25|92
25|28
25|46
25|95
25|11
25|23
25|36
25|87
25|82
25|27
25|53
25|18
25|52
25|24
25|85
25|64
25|99
11|48
11|89
11|18
11|87
11|28
11|23
11|34
11|85
11|92
11|36
11|52
11|24
11|91
11|27
11|53
11|99
11|88
11|67
17|95
17|99
17|36
17|79
17|61
17|15
17|11
17|19
17|65
17|96
17|22
17|12
17|25
17|23
17|72
17|75
17|66
63|85
63|99
63|74
63|36
63|82
63|18
63|61
63|41
63|95
63|89
63|64
63|28
63|23
63|87
63|75
63|88
72|52
72|88
72|46
72|64
72|41
72|25
72|12
72|99
72|96
72|63
72|15
72|19
72|75
72|65
72|89
61|88
61|82
61|67
61|89
61|26
61|92
61|28
61|53
61|48
61|85
61|18
61|36
61|24
61|34
19|12
19|11
19|82
19|63
19|61
19|88
19|96
19|23
19|95
19|15
19|24
19|53
19|99
39|63
39|65
39|24
39|89
39|41
39|72
39|19
39|46
39|88
39|11
39|52
39|75
58|66
58|12
58|79
58|61
58|41
58|46
58|19
58|11
58|96
58|15
58|99
75|95
75|24
75|36
75|27
75|52
75|67
75|23
75|85
75|26
75|92
89|28
89|18
89|34
89|53
89|51
89|92
89|48
89|42
89|83
36|34
36|88
36|69
36|89
36|83
36|48
36|27
36|51
27|62
27|86
27|42
27|58
27|51
27|79
27|92
91|79
91|65
91|64
91|19
91|25
91|86
15|89
15|25
15|99
15|64
15|24
93|42
93|86
93|19
93|96
28|83
28|66
28|27
67|19
67|15
23|91

27,51,67,91,42,86,58,66,39,72,96
88,64,61,72,82,46,36,63,41,95,75
17,62,58,66,79,22,39,72,19,96,65,63,12,41,25,46,64,75,11,95,99,23,61
12,41,39,93,95,66,86,62,42,11,58
18,92,26,48,67,83,69,42,62,58,66,79,39,19,15
64,46,61,66,63,99,23,11,75,17,41
46,75,11,95,99,61,36,82,85,24,52,53,74,87,27,18,92,26,48
18,92,61,74,27,48,99,67,89,36,52,26,11,91,95
75,22,85,36,15,89,72,39,79,99,46,61,23,11,19,64,95
66,58,72,93,79,17,34,65,42,64,39
83,87,51,42,69,93,91,26,24,89,88,17,86,18,53,92,67
83,93,42,86,66,96,15,63,12,41,25,64,75
67,95,53,87,75,92,18,36,99
25,64,11,23,24,99,15,96,88,61,46,95,63
51,91,83,69,42,17,62,58,66,79,22,39,72
26,69,86,66,72,15,63
34,91,92,22,17,74,58,79,66,53,83
87,86,51,26,28,17,18,92,24,67,27,42,91,85,34,53,69
51,67,91,34,83,69,93,42,86,17,62,58,66,79,22,72,19,96,15,65,63,12,41
48,69,83,27,42,86,34,62,93,58,53,18,88,67,52,87,24,91,74
96,15,65,63,12,41,25,46,64,75,11,95,23,61,36,82,89,52,88,53,28
72,95,11,41,89,19,82,12,63,79,22,25,36,65,61,96,66,75,39,64,15,23,99
41,39,22,25,69,11,86,93,66,42,19,46,64,72,15,79,96,65,58,12,75
12,41,25,46,64,11,23,61,36,82,89,85,24,52,53,28,74,87,27
42,83,79,28,66,74,48,53,26,93,62,67,51,91,18,88,87
34,19,96,15,66,17,69,22,79,26,72,86,67,91,48,18,39,93,51,92,42
91,34,83,69,93,86,17,62,58,79,22,39,72,19,96,15,65,63,12,25,46
99,23,61,36,82,24,88,53,28,74,87,27,92,26,48,34,83
96,15,65,63,12,41,25,46,64,75,11,95,99,61,36,82,85,24,52,88,28
66,27,48,18,96
11,95,99,82,52,53,27,92,48
17,66,39,12,41,93,51
86,62,58,66,22,72,19,96,15,65,63,12,41,25,46,64,75,11,95,99,23
26,85,27,52,92,82,34,51,87,83,67,23,89,36,74,24,28,69,53,91,18
46,64,75,11,95,99,23,61,36,82,89,85,52,88,53,74,87,18,92,26,48
83,85,92,87,88,74,28,48,18,52,82,93,24
17,22,19,63,99
79,11,39,86,19,65,46,62,93,42,64,96,69,25,72,66,15,12,41,58,22
15,41,72,23,64,99,62,36,12,58,25,95,96
74,92,51,28,91,34,69,42,67,48,66,87,26,27,22,79,93,39,18,17,83
66,93,91,72,67,87,83,22,86,18,42,39,51,34,62,27,69,17,74,58,92
62,34,58,66,72,42,51,17,86
75,61,12,87,95,99,82,11,52,64,74,36,28
87,27,18,48,51,83,93,86,62,58,66,79,39,72,19
87,51,42,88,74,26,52,53,17,24,27,83,86,34,62,92,18,48,93,58,28
72,96,41,64,95,36,88
61,88,82,67,91,28,36,89,52,83,23,87,34,26,18,51,69,48,24
88,53,28,74,87,27,18,92,26,48,51,34,83,69,93,42,86,17,58,66,79
36,27,18,82,92,83,99
89,61,34,88,82,93,91
75,24,72,61,96,63,82,39,41,52,15,65,95
74,53,24,18,26,36,88
91,34,83,93,42,86,17,62,58,66,22,39,72,19,96,15,65,63,12,25,46
72,96,12,41,25,75,23,89,88
11,25,27,75,24,74,82,85,88,53,36,87,95,28,63,64,89
89,82,52,74,27,63,61,95,53
89,52,51,95,99,53,85,11,18,23,88,87,27,28,64
61,36,89,87,83,69,93
62,67,12,72,25,19,42,39,83,66,65,63,34,41,86,58,79,22,91
69,42,63,22,79,39,15,96,12,65,67,86,91,93,58,48,72,51,83
82,89,24,52,53,74,87,27,18,92,26,48,51,67,91,34,69,42,86
87,27,18,92,26,48,51,67,91,83,93,86,17,62,66,79,22
72,19,86,25,96,23,12,95,39,11,22,41,99,46,63
46,25,86,66,22,96,63,62,42,93,69,39,15,12,79,64,34
92,87,18,53,83,58,22,93,91,74,51
17,62,58,66,79,22,39,72,96,15,65,63,12,41,25,46,64,75,11,95,99,23,61
58,66,79,72,12,75,95,61,82
19,15,41,25,46,64,75,36,85,52,53
26,79,66,17,91,18,93,62,34,92,58,51,67,83,53,74,28,88,42,27,87
26,18,28,69,27,48,89,51,42,36,24,91,83
72,41,22,61,79,23,63,65,36,62,11,46,99,15,25,95,19,75,12,58,64
34,83,69,93,42,17,58,79,22,39,72,19,96,15,63,41,25,46,64
74,87,18,26,48,67,91,34,83,69,93,42,17,62,22,39,72
83,79,66,15,91,63,96,25,58,12,72,65,62,34,69,19,39,42,22,86,41,67,93
96,15,65,63,41,25,64,61,82,89,24,52,28
11,23,61,36,82,24,88,53,28,27,18,92,26,48,51,67,91
93,51,69,34,41,96,22,17,19,58,65,15,79,62,39,63,91,83,42
65,63,12,41,25,46,64,75,11,95,99,23,61,36,82,89,85,24,52,88,53,74,87
46,95,11,41,19,23,89,65,96,99,66,36,25,12,72,75,82,64,15,79,61,39,22
23,75,74,82,53,11,88,24,27,18,85,95,87,25,36,46,26,92,64,99,89,61,28
52,11,27,12,61,74,24,63,75,64,46,36,89,95,99,87,41,82,85,88,28,23,25
82,24,88,53,28,74,87,27,18,92,26,48,51,67,91,34,83,69,93,42,86
88,63,61,52,75,23,12,89,72,36,95
89,95,63,39,36,41,46,19,72,24,64,25,85,75,61,22,99
99,82,89,24,52,88,53,28,87,27,92,26,48,51,91,34,83
51,69,72,91,79,86,93,96,48,22,27,42,62
46,22,65,83,86,39,62,69,15,64,75,63,42,17,96,66,58,41,25,72,19
83,69,86,17,62,58,66,79,22,39,72,19,15,65,63,12,41,25,46,64,75
74,67,28,42,26,91,18
15,65,12,25,11,95,99,61,36,82,85,24,88,28,74
69,93,42,86,17,62,58,66,79,22,72,19,96,15,65,63,12,41,25,46,64,75,11
95,99,23,82,89,88,28,74,27,18,92
95,23,61,82,89,85,24,52,53,74,27,18,92
41,62,64,42,69,72,11
19,65,11,95,89,46,25,36,66,22,23,12,72,63,41,79,64,82,15,39,75,99,96
58,22,72,36,65,39,25,23,64,96,82,99,11,41,79,15,66,19,12
23,61,82,89,24,52,28,18,51,67,91
58,66,22,39,72,19,96,65,12,41,25,46,75,95,23,61,36
36,66,22,15,46,41,64
93,69,92,36,24,83,82,87,53,52,61,85,91,74,26,89,34,18,88
82,89,85,52,88,28,74,27,92,26,48,51,67,91,34,83,69,42,86
95,39,22,58,72,23,99,12,63,25,75,96,62
11,95,99,36,82,89,85,52,88,53,28,74,87,27,18,26,48,67,91
72,96,15,65,12,46,64,75,11,95,36
95,99,23,61,36,82,89,85,24,88,53,28,74,87,27,92,26,91,34
34,18,27,92,67,95,23,61,48,51,53,26,85,91,88,99,74,89,28
42,24,85,69,26,28,74,89,88,36,83
58,66,79,22,39,96,15,65,63,64,11,99,23,36,82
28,48,67,83,42,22,39
93,82,69,74,51,24,34,85,89,42,36,52,27,53,28,92,67,91,83,87,88,26,48
18,83,28,17,66,69,93,26,52
85,89,53,26,36,46,88,24,99,52,27,25,18,92,75,74,11
17,62,58,66,22,72,19,96,15,65,63,12,41,25,46,64,75,11,99,23,61
58,66,79,39,19,96,65,63,75,95,99
61,36,82,89,85,24,52,88,28,74,87,27,18,92,26,48,51,91,34,83,69
63,41,25,46,64,95,23,61,89,85,24,52,53,28,74,87,27
79,22,39,72,19,15,65,63,12,41,25,46,75,11,95,99,23,36,82,89,85
65,11,25,53,82,88,74,12,15,63,41,64,89,23,24,99,46,75,95,52,36
52,27,61,87,24
62,39,15,65,63,41,11,95,99
67,19,34,15,12,63,72
85,23,79,95,11,39,19,46,72
83,93,51,86,69,91,48,19,22,96,34,58,79,17,26,92,65
83,74,67,88,18,69,34,27,51,92,42,66,28,53,91,62,26,87,48,17,79
42,17,66,79,72,19,15,12,25,46,64,95,99
28,18,64,87,25,99,74,89,82,11,36,24,75,61,12
62,92,48,79,17,53,27,18,83,28,86,69,67,88,74
83,91,48,93,36,24,92,74,89,88,69,42,51,85,26,18,52,34,53,87,82
46,64,99,82,28,26,48
12,95,23,99,75,64,41,15,74,24,11
22,72,19,96,15,65,63,25,46,75,99,23,36,82,89,85,24
41,25,64,11,95,23,85,24,87
87,27,48,51,83,69,93,17,58,72,19
25,79,64,96,99,66,15,39,11,12,63,61,75,89,41,82,46,95,72,19,65
85,48,42,52,69,26,83,24,93,74,36,34,67
27,87,92,24,99,46,11,64,53,75,95,88,74,26,89,28,52,85,25
89,24,52,74,87,27,92,48,67,34,69,86,17
17,89,83,24,92
17,58,39,96,15,65,63,12,41,64,75,95,99,23,61
82,12,46,61,25,15,53,65,75,99,36,24,88,52,28,89,41,11,23,85,64,74,95
86,19,69,18,93
87,27,92,26,48,51,67,91,34,83,69,93,42,86,17,62,58,66,79,22,39,72,19
95,87,27,26,91,36,24,23,74,82,89,53,85,28,52,51,88,48,92,11,61,99,18
74,87,27,92,26,48,91,34,83,93,42,17,62,58,66,79,22,39,72
48,88,85,52,46,92,24,99,74,36,89,61,27,23,64,26,87
12,95,18,41,85,23,61
39,96,41,46,11,36,52
93,42,86,17,62,58,22,39,96,15,65,41,25,46,75,11,95
82,85,53,28,26,67,86
46,99,11,39,64,58,42,65,19,22,15,75,95,17,25,79,86,12,72
15,65,64,95,36,82,85,24,88,53,28
99,23,24,64,95,87,65
63,61,95,24,53,64,88,27,52,85,74
96,64,11,95,99,61,36,82,89,85,28
89,46,25,88,18,11,92,28,82,87,52,95,53,99,26,75,74,36,27,64,24
99,75,11,85,25,27,92,95,52,74,87,61,82,18,24,41,36
22,96,15,63,25,11,61,89,24
88,53,58,79,83,93,48,87,92
41,58,93,12,15,22,67,96,83,79,25,66,19
66,93,41,69,72,62,46,63,15,17,19,58,65,96,83
15,22,72,24,64,96,41,75,23
34,26,91,52,67,48,92,51,27
85,87,65,24,28,88,36,89,52,11,99,23,61,12,63,41,82
53,63,99,61,12,95,74,36,41,88,23,28,15,85,64
42,93,39,91,69,19,79,58,41,72,63,86,66,12,17,62,22,46,83,65,25,15,34
82,88,83,99,61,28,85,26,87,18,34,51,48
27,26,48,51,67,91,34,83,42,62,58,79,22,39,72,19,96
92,26,48,67,91,34,69,93,42,86,58,66,79,22,39,72,19,15,65
27,92,88,34,69,51,18,85,93,24,62,52,26
36,85,15,88,96,11,64,75,53,28,61
89,87,27,52,28,85,18,61,24,67,99,91,74,51,11,92,95
34,83,69,93,42,17,62,58,66,79,22,72,19,96,15,65,63,12,41,46,64
65,25,79,93,46,72,83,86,58,63,66,91,34,15,41
17,52,88,18,85,89,91
42,91,28,58,48,17,26,67,24,74,69,62,34,83,52
82,85,24,52,28,74,87,27,18,92,91,34,69,42,86
58,12,41,66,83,42,19,17,62,79,46,25,22,15,39,93,65,96,69,63,34,91,86
63,15,83,65,46,25,69,19,42,75,39,79,41,12,62,72,58
69,17,62,66,96,25,75
26,48,67,91,34,83,69,42,86,17,58,79,22,39,72,19,63
72,19,65,46,64,75,11,82,24
64,63,99,46,17,19,22,65,15,61,58,23,72
83,79,65,15,42,39,91,69,72,34,86,17,62,63,66,58,51,22,96,93,12,67,41
34,51,69,66,92,42,26,18,52,67,53,27,17,83,28,93,87,88,91,86,74
74,87,27,18,92,26,48,51,34,83,93,86,17,62,58,66,79,39,72
91,42,63,96,79,62,22,51,26,65,72
86,93,26,66,48,74,18,17,58,27,91,51,79,39,34,28,92
24,75,46,27,82,89,36,28,64,87,25,18,95,61,74,53,92,88,99,52,23,41,11
85,23,87,36,61,89,74,99,27,64,95,53,11,26,18,25,88,46,75,52,82
74,64,82,87,27
62,66,46,58,75,79,65,64,72,19,39,25,41,12,96,36,11,99,23,22,61
48,51,67,91,34,93,42,17,58,66,39,19,96,15,65,63,12
28,93,26,58,87,91,69,86,22,53,66
18,92,26,48,51,67,91,34,69,93,42,86,17,62,58,66,79,39,96
96,15,65,63,12,25,46,11,95,99,61,82,89,85,24,52,88
42,91,93,65,63,17,72,51,19,79,83,69,41
24,61,67,52,11,36,99,85,53,82,51
)";
}
