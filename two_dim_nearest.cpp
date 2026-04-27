#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point
{
    ll x, y;
    ll id;
};

bool cmp_x(const Point& x, const Point& y)
{
    if (x.x != y.x)
        return x.x < y.x;
    return x.y < y.y;
}

bool cmp_y(const Point& a, const Point& b) 
{
    if (a.y != b.y) 
        return a.y < b.y;
    return a.x < b.x;
}

void quickSort(vector<Point> &p, ll l, ll r, bool (*cmp)(const Point&, const Point&))
{
    if (l >= r)
        return;
    
    ll i = l, j = r;
    Point pivot = p[(l+r)/2];

    while (i <= j)
    {
        while (cmp(p[i], pivot)) i++;
        while (cmp(pivot, p[j])) j--;

        if (i <= j)
        {
            swap(p[i], p[j]);
            i++;
            j-- ;                  
        }
    }
    
    quickSort(p, l, j, cmp);
    quickSort(p, i, r, cmp);
}

double dist(const Point& x, const Point& y)
{
    double dx = x.x - y.x;
    double dy = x.y - y.y;
    return sqrt(dx * dx + dy * dy);
}

double bruteForce(const vector<Point>& pp)
{
    if (pp.size() == 0 || pp.size() == 1)
        return 1e100;
    if (pp.size() == 2)
        return dist(pp[0], pp[1]);
    if (pp.size() == 3)
        return min({dist(pp[0], pp[1]), dist(pp[0], pp[2]), dist(pp[1], pp[2])});
    return 1e100;
}

double solve(const vector<Point>& px, const vector<Point>& py)
{
    if (px.size() <= 3)
        return bruteForce(px);

    ll mid = px.size()/2;
    double midX = px[mid].x;
    
    vector<Point> l_px(px.begin(), px.begin() + mid);
    vector<Point> r_px(px.begin() + mid, px.end());
    vector<Point> l_py, r_py;

    unordered_set<ll> l_ids;
    for (int i = 0; i < mid; i++)
        l_ids.insert(px[i].id);

    for (auto & p : py)
        if (l_ids.count(p.id))
            l_py.push_back(p);
        else
            r_py.push_back(p);

    double ans = min(solve(l_px, l_py), solve(r_px, r_py));

    vector<Point> strip;
    for (auto& p : py)
        if (fabs(midX - p.x) < ans)
            strip.push_back(p);

    for (int i = 0; i < strip.size(); i++)
        for (int j = i + 1; j < strip.size() && j <= i + 6; j++)
        {
            if (strip[j].y - strip[i].y >= ans)
                break;
            ans = min(ans, dist(strip[i], strip[j]));
        }
    
    return ans;
}

int main()
{
    ll n;
    cin >> n;

    vector<Point> a(n), px(n), py(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].x >> a[i].y;
        a[i].id = i;
        px[i] = a[i];
        py[i] = a[i];
    }

    if (n < 2)
    {
        cout << fixed << setprecision(2) << 0.00 << endl;
        return 0;
    }

    quickSort(px, 0, n - 1, cmp_x);
    quickSort(py, 0, n - 1, cmp_y);

    double ans = solve(px, py);

    cout << fixed << setprecision(2) << ans << endl;

    return 0;
}
