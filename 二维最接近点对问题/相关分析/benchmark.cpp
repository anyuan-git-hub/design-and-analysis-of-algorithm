#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Point {
    ll x, y;
    int id;
};

double distPoint(const Point& a, const Point& b) {
    double dx = (double)a.x - b.x;
    double dy = (double)a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double bruteForceAll(const vector<Point>& p) {
    int n = (int)p.size();
    if (n < 2) return 0.0;

    double ans = 1e100;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans = min(ans, distPoint(p[i], p[j]));
        }
    }
    return ans;
}

bool cmpX(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool cmpY(const Point& a, const Point& b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

double bruteSmall(const vector<Point>& p) {
    double ans = 1e100;
    int n = (int)p.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans = min(ans, distPoint(p[i], p[j]));
        }
    }

    return ans;
}

double divideSolve(const vector<Point>& px, const vector<Point>& py) {
    int n = (int)px.size();

    if (n <= 3) {
        return bruteSmall(px);
    }

    int mid = n / 2;
    ll midX = px[mid].x;

    vector<Point> leftPx(px.begin(), px.begin() + mid);
    vector<Point> rightPx(px.begin() + mid, px.end());

    unordered_set<int> leftIds;
    leftIds.reserve(mid * 2);

    for (int i = 0; i < mid; i++) {
        leftIds.insert(px[i].id);
    }

    vector<Point> leftPy, rightPy;
    leftPy.reserve(mid);
    rightPy.reserve(n - mid);

    for (const auto& p : py) {
        if (leftIds.count(p.id)) {
            leftPy.push_back(p);
        } else {
            rightPy.push_back(p);
        }
    }

    double dLeft = divideSolve(leftPx, leftPy);
    double dRight = divideSolve(rightPx, rightPy);
    double ans = min(dLeft, dRight);

    vector<Point> strip;
    strip.reserve(n);

    for (const auto& p : py) {
        if (fabs((double)p.x - midX) < ans) {
            strip.push_back(p);
        }
    }

    for (int i = 0; i < (int)strip.size(); i++) {
        for (int j = i + 1; j < (int)strip.size() && j <= i + 7; j++) {
            if ((double)strip[j].y - strip[i].y >= ans) {
                break;
            }
            ans = min(ans, distPoint(strip[i], strip[j]));
        }
    }

    return ans;
}

double divideClosestPair(vector<Point> p) {
    int n = (int)p.size();
    if (n < 2) return 0.0;

    vector<Point> px = p;
    vector<Point> py = p;

    sort(px.begin(), px.end(), cmpX);
    sort(py.begin(), py.end(), cmpY);

    return divideSolve(px, py);
}

vector<Point> generateRandomPoints(int n, mt19937_64& rng) {
    vector<Point> points;
    points.reserve(n);

    uniform_int_distribution<ll> coordDist(0, 1000000000LL);

    for (int i = 0; i < n; i++) {
        points.push_back({coordDist(rng), coordDist(rng), i});
    }

    return points;
}

template <typename Func>
double measureTimeMs(Func func) {
    auto start = chrono::high_resolution_clock::now();
    volatile double ans = func();
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = end - start;
    return elapsed.count();
}

int main() {
    mt19937_64 rng(20260427);

    vector<int> testSizes = {
        100, 500, 1000, 2000, 4000, 8000, 16000, 32000
    };

    int repeatTimes = 5;

    ofstream fout("runtime_result.csv");
    fout << "n,brute_ms,divide_ms\n";

    cout << fixed << setprecision(6);
    cout << "n,brute_ms,divide_ms\n";

    for (int n : testSizes) {
        double bruteTotal = 0.0;
        double divideTotal = 0.0;

        for (int t = 0; t < repeatTimes; t++) {
            vector<Point> points = generateRandomPoints(n, rng);

            double bruteTime = measureTimeMs([&]() {
                return bruteForceAll(points);
            });

            double divideTime = measureTimeMs([&]() {
                return divideClosestPair(points);
            });

            bruteTotal += bruteTime;
            divideTotal += divideTime;
        }

        double bruteAvg = bruteTotal / repeatTimes;
        double divideAvg = divideTotal / repeatTimes;

        cout << n << "," << bruteAvg << "," << divideAvg << "\n";
        fout << n << "," << bruteAvg << "," << divideAvg << "\n";
    }

    fout.close();

    return 0;
}

