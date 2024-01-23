#include <bits/stdc++.h>
using namespace std;

int npins, nnets; 
vector<int> upperP, lowerP; 

unordered_map<int, pair<int, int>> sortIntervalsByPriority(const map<int, pair<int, int>>& interval) {
    vector<pair<int, pair<int, int>>> tmp(interval.begin(), interval.end());
    sort(tmp.begin(), tmp.end(), [](const auto &left, const auto &right) {
        return left.second.first != right.second.first ? left.second.first > right.second.first : left.second.second > right.second.second;
    });

    unordered_map<int, pair<int, int>> sortedInterval;
    for (const auto &elem : tmp) {
        sortedInterval[elem.first] = elem.second;
    }
    return sortedInterval;
}

bool isHead(int i, vector<vector<int>> &trunk) { 
    if (trunk[i][i] == -1) {
        return false; 
    }
    for (int j = 1; j <= nnets; j++) {
        if (trunk[j][i] > 0 && j != i) {
            return false;
        }
    }
    return true;
}

void updateResult(vector<vector<char>>& result, int i, int j, int k, int position, int start, int end, int tracksSize) {
    char symbol = (j == start && k == i) || (j == end && k == i) ? (k == tracksSize ? 'o' : 'x') : (k == tracksSize ? 'o' : (k == i ? '-' : '|'));
    result[k][position] = symbol;
}


void print_graph(map<int, pair<int, int>> &interval, vector<vector<int>> &tracks) {
    int space = 1; int tmp = npins;
    int pset = 5*npins;
    while (tmp/10 > 0) {
        tmp = tmp / 10;
        space++;
    }    
    cout << "\nCol number:";
    for (int i = 1; i <= npins; i++) {
        for (int j = 1; j <= 3-space; j++) cout << " ";
        cout << setw(space) << i; cout << "  ";
    }
    space = 1; tmp = nnets;
    while (tmp/10 > 0) {
        tmp = tmp / 10;
        space++;
    }
    cout << "\nUpper pins:";
    for (int i = 1; i <= npins; i++) {
        for (int j = 1; j <= 3-space; j++) cout << " ";
        cout << setw(space) << upperP[i]; cout << "  ";
    }
    cout << "\n           ";
    for (int i = 1; i <= pset; i++) cout << "-";
    cout << "\n";

    vector<vector<char>> graph(tracks.size(), vector<char>(pset, ' '));
    for (int i = 0; i < tracks.size(); i++) { 
        for (int n = 0; n < tracks[i].size(); n++) { 
            int net = tracks[i][n];
            int start = interval[tracks[i][n]].first; 
            int end = interval[tracks[i][n]].second; 
            for (int j = start; j <= end; j++) {
                int position = 2+(j-1)*5;
                if (upperP[j] == net) {
                    for (int k = i; k >= 0; k--) {
                        updateResult(graph, i, j, k, position, start, end, 0);
                    }
                }
                else if (lowerP[j] == net) {
                    for (int k = i; k < tracks.size(); k++) {
                        updateResult(graph, i, j, k, position, start, end, tracks.size()-1);
                    }
                }
            }
            for (int j = 0; j < pset; j++) {
                if (j < 2+(start-1)*5 || j > 2+(end-1)*5) continue;
                if (graph[i][j] == ' ') graph[i][j] = '-'; 
            }
        }
    }
    for (auto &row: graph) {
        cout << "           ";
        for (auto &elem: row) {
            cout << elem;
        }
        cout << '\n';
    }

    cout << "           ";
    for (int i = 1; i <= pset; i++) cout << "-";
    cout << "\nLower pins:";
    for (int i = 1; i <= npins; i++) cout << "  " << lowerP[i] << "  ";
    cout << '\n';

}

void print_result(map<int, pair<int, int>> &interval, vector<vector<int>> &tracks) {
    
    cout << "\n(1) Number of tracks: " << tracks.size() << '\n';

    int len = 0;
    for (int i = 0; i < tracks.size(); i++) {
        for (int j = 0; j < tracks[i].size(); j++) {
            int net = tracks[i][j];
            len += interval[net].second - interval[net].first;
            int x = 0, y = 0;
            for (int k = 1; k <= npins; k++) {
                if (upperP[k] == net) x++;
                if (lowerP[k] == net) y++;
            }
            len += (i+1)*x;
            len += (tracks.size()-i)*y;
        }
    }
    cout << "(2) Overall wire length: " << len << '\n';

    int via = 0;
    for (int k = 1; k <= npins; k++) {
        if (upperP[k] != 0) via++;
        if (lowerP[k] != 0) via++;
    }
    cout << "(3) Number of vias: " << via << '\n';
    
}



int main(int argc, char** argv) {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }
    upperP.emplace_back(0), lowerP.emplace_back(0);
    in >> npins >> nnets;
    vector<vector<int>> trunk(npins, vector<int>(npins, 0));
    map<int, pair<int, int>> interval;

    int temp = npins;
    int col = 1;
    while(temp--){
        int iupper, ilower;
        in >> iupper >> ilower;
        upperP.emplace_back(iupper);
        lowerP.emplace_back(ilower);
        if (interval.count(iupper)) {
            if (col > interval[iupper].second) interval[iupper].second = col;
        }
        else if (iupper != 0) {
            interval[iupper] = make_pair(col, 0);
        }
        if (interval.count(ilower)) {
            if (col > interval[ilower].second) interval[ilower].second = col;
        }
        else if (ilower != 0) interval[ilower] = make_pair(col, 0);
        col++;

        if (iupper == 0 || ilower == 0) continue;
        trunk[iupper][ilower] = 1;
    }

    cout << "Sort Intervals By Priority: \n";
    auto sortinterval = sortIntervalsByPriority(interval);
    for (auto &elem: sortinterval) {
        cout << "interval " << elem.first << ": [" << elem.second.first << ", " << elem.second.second << "]\n";
    }

    cout << "\nLeft-edge algorithm: " << '\n';
    for (int i = 0; i < npins; i++) {
        for (int j = 0; j < npins; j++) {
            
            if (trunk[i][j]) cout << "interval " << i << " -> interval " << j << '\n';
        }
    }

    int watermark = 0;
    vector<vector<int>> tracks;
    while (!sortinterval.empty()) {
        if (tracks.size() > npins) break;
        vector<int> heads;
        for (int i = 1; i <= nnets; i++) {
            if (isHead(i, trunk)) {
                heads.push_back(i);
            }
        }
        vector<int> nets; nets.reserve(100);
        vector<int> watermarks;
        bool isNetAdded = false;
        for (auto &elem: sortinterval) {
            if (elem.second.first <= watermark) continue;
            if (!isHead(elem.first, trunk)) continue;
            for (auto &e: trunk[elem.first]) e = -1;
            nets.emplace_back(elem.first);
            watermark = elem.second.second;
            watermarks.push_back(watermark);
            isNetAdded = true;
        }
        if (isNetAdded) {
            cout << "\ntrack " << tracks.size()+1 << ":\n";
            cout << "  heads: ";
            for (auto head : heads) {
                cout << "interval " << head << ", ";
            }
            cout << "\n  route:\n";
            for (size_t i = 0; i < nets.size(); ++i) {
                int net = nets[i];
                int netWatermark = watermarks[i]; // Assuming watermarks is a vector or similar and aligned with nets

                cout << "    interval " << net << "[" << sortinterval[net].first << ", " << sortinterval[net].second << "], \n";
                cout << "    watermark = " << netWatermark << "\n";
            }
        }
        tracks.emplace_back(nets);
        for (auto &elem: nets) sortinterval.erase(elem);

        watermark = 0;

        if (!isNetAdded) {
            break;
        }
    }

    for (int i = 1; i <= 6*npins; i++) cout << "=";
    cout << "\nThe Output: ";
    print_result(interval, tracks);
    for (int i = 1; i <= 6*npins; i++) cout << "=";
    cout << "\nThe routing graph: ";
    print_graph(interval, tracks);
    for (int i = 1; i <= 6*npins; i++) cout << "=";
    cout << '\n';
}
