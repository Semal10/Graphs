#include<bits/stdc++.h>
#include<climits>

using namespace std;

#define debug(x,y) cout<<(#x)<<" " <<(#y)<<" is " << (x) <<" "<< (y) << endl
#define watch(x) cout<<(#x)<<" is " << (x) << endl
#define fast ios_base::sync_with_stdio(false)
#define fie(i,a,b) for(i=a;i<b;i++)
#define MOD 1000000007
#define PB push_back
#define EB emplace_back
#define MP make_pair
#define FI first
#define SE second
#define ll long long
#define lld long long int
#define ALL(x) (x).begin(),(x).end()
#define endl "\n"

typedef vector<int> vi;
typedef vector<vector<int>> vii;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<pair<int, int>> vpi;
typedef long long LL;

const lld INF = (1ll) << 56;
const long long OO = 2e18;
const double pi = 2 * acos(0.0);

lld par[100001];
lld size[100001];
lld n;
lld numComponents;
vector<vector<pair<lld, lld>>> MST(100001);
vector<bool> visited(100001);

void UnionFind(lld siz) {
	n = siz;
	numComponents = n;
	for (lld i = 0; i <= n; i++) {
		par[i] = i;
		size[i] = 1;
	}
}

lld find(lld p) {
	lld root = p;
	while (root != par[root]) {
		root = par[root];
	}

	//Path-Compression
	while (p != root) {
		lld next = par[p];
		par[p] = root;
		p = next;
	}
	return root;
}

bool connected(lld p, lld q) {
	return find(p) == find(q);
}

lld componentSize(lld p) {
	return size[find(p)];
}

lld totalComponents() {
	return numComponents;
}

void unify(lld p, lld q) {
	if (connected(p, q)) return;

	lld root1 = find(p);
	lld root2 = find(q);

	if (size[root1] < size[root2]) {
		size[root2] += size[root1];
		par[root1] = root2;
	}
	else {
		size[root1] += size[root2];
		par[root2] = root1;
	}

	numComponents--;
}

lld sum = 0;

void dfs(lld u) {
	visited[u] = true;
	for (lld i = 0; i < MST[u].size(); i++) {
		if (!visited[MST[u][i].second]) {
			sum += MST[u][i].first;
			dfs(MST[u][i].second);
		}
	}
}


int main() {
	fast;
	cin.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	lld i, n, m;
	cin >> n >> m;
	UnionFind(n);
	vector<pair<lld, pair<lld, lld>>> adj;
	for (i = 0; i < m; i++) {
		lld w, x, y;
		cin >> x >> y >> w;
		//lld two = pow(2, w);
		adj.push_back({two, {x, y}});
	}
	sort(adj.begin(), adj.end());
	for (i = 0; i < adj.size(); i++) {
		if (!connected(adj[i].second.first, adj[i].second.second)) {
			MST[adj[i].second.first].push_back({adj[i].first, adj[i].second.second});
			MST[adj[i].second.second].push_back({adj[i].first, adj[i].second.first});
			unify(adj[i].second.first, adj[i].second.second);
		}
	}
	//memset(visited, false, sizeof(visited));
	dfs();
	cout << sum << endl;
	lld temp = sum;
	vector<lld> bit;
	while (temp) {
		bit.push_back(temp % 2);
		temp /= 2;
	}
	reverse(bit.begin(), bit.end());
	for (i = 0; i < bit.size(); i++) {
		cout << bit[i];
	}

}
