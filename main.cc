#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <fstream>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <cassert>
#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
//#include <atcoder/all>
#endif

using namespace std;
//using namespace atcoder;
#define INF 2e9
#define repi(n) for(int i=0;i<n;i++)
#define rep(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(),a.end()
#define uset unordered_set
#define umap unordered_map
typedef long long ll;
typedef vector<int> vi;
typedef vector< vector<int> > vvi;
typedef vector<ll> vl;
typedef vector< vector<ll> > vvl;
typedef vector<bool> vb;
typedef vector< vector<bool> > vvb;
typedef vector<double> vd;
typedef vector< vector<double> > vvd;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

struct Edge{
	int to;
	ll w;
	Edge(int to,ll w):to(to),w(w){}
};

using Graph=vector<vector<Edge>>;

template <typename T>
bool chmin(T &x,T y){
	if(x>y){
		x=y;
		return true;
	}
	return false;
}

template <typename T>
bool chmax(T &x,T y){
	if(x<y){
		x=y;
		return true;
	}
	return false;
}

template <typename T>
string toBinary(T x){
	string res="";
	while(x!=0){
		if(x&1){
			res="1"+res;
		}
		else{
			res="0"+res;
		}
		x=x>>1;
	}
	return res;
}

int toDecimal(string s){
	int res=0;
	int d=1;
	for(int i=s.size()-1;i>=0;i--){
		if(s[i]=='1'){
			res+=d;
		}
		d*=2;
	}
	return res;
}

//O(logn)
ll pow_origin(ll x,ll n){
	ll ret=1;
	while(n>0){
		if(n&1)ret=ret*x;
		x=x*x;
		n>>=1;
	}
	return ret;
}

template <typename T>
void printVector(vector<T> &x){
	for(auto i : x)cout<<i<<" ";
	cout<<endl;
}

template <typename T>
void printVector2d(vector< vector<T> > &x){
	for(auto &i : x){
		for(auto j : i){
			cout<<j<<" ";
		}
		cout<<endl;
	}
}

void printYesOrNo(bool x){
	cout<<(x ? "Yes" : "No")<<endl;
}

struct Pos {
    int y, x;
};

bool operator<(const Pos &lhs,const Pos &rhs){
	if(lhs.y!=rhs.y){
		return lhs.y<rhs.y;
	}
	else{
		return lhs.x<rhs.x;
	}
}

bool operator==(const Pos &lhs,const Pos &rhs){
	return lhs.y==rhs.y && lhs.x==rhs.x;
}

bool operator!=(const Pos &lhs,const Pos &rhs){
	return lhs.y!=rhs.y || lhs.x!=rhs.x;
}

enum class Response {
    not_broken, broken, finish, invalid
};

struct Field {
    int N;
    int C;
    vector<vector<int>> is_broken;
    int total_cost;

    Field(int N, int C) : N(N), C(C), is_broken(N, vector<int>(N, 0)), total_cost(0) {}

    Response query(int y, int x, int power) {
        total_cost += power + C;
        cout << y << " " << x << " " << power << endl; // endl does flush
        int r;
        cin >> r;
        switch (r) {
        case 0:
            return Response::not_broken;
        case 1:
            is_broken[y][x] = 1;
            return Response::broken;
        case 2:
            is_broken[y][x] = 1;
            return Response::finish;
        default:
            return Response::invalid;
        }
    }
};

struct Solver {
    int N;
    int C;
    set<Pos> source_pos;
    deque<Pos> house_pos;
	vector<vector<int>> exs;
    Field field;
	int power;
	int div;

    Solver(int N, const set<Pos>& source_pos, const deque<Pos>& house_pos, int C) : 
        N(N), source_pos(source_pos), house_pos(house_pos), C(C), field(N, C) {
			exs.resize(N,vector<int>(N,-1));
			switch(C){
			case 1:
				power=10;
				div=10;
				break;
			case 2:
				power=20;
				div=8;
				break;
			case 4:
				power=40;
				div=6;
				break;
			case 8:
				power=50;
				div=4;
				break;
			case 16:
				power=60;
				div=3;
				break;
			default:
				power=100;
				div=2;
		}
    }

	//答えを求める
    void solve() {

		auto cmp=[&](const Pos &lhs,const Pos &rhs){
			return distance(lhs,leastSource(lhs))<distance(rhs,leastSource(rhs));
		};
		
		while(house_pos.size()!=0){
			sort(all(house_pos),cmp);
			move(house_pos[0],leastSource(house_pos[0]));
			house_pos.pop_front();
		}

        // should receive Response::finish and exit before entering here
        assert(false);
    }

	//ユークリッド距離
	int distance(Pos a,Pos b){
		return (a.y-b.y)*(a.y-b.y)+(a.x-b.x)*(a.x-b.x);
	}

	//最も遠い水源を求める
	Pos farSource(Pos h){
		Pos res;
		int dist=-1;
		for(auto s : source_pos){
			int d=distance(h,s);
			if(dist<d){
				dist=d;
				res=s;
			}
		}
		return res;
	}

	//最も近い水源を求める
	Pos leastSource(Pos h){
		Pos res;
		int dist=INF;
		for(auto s : source_pos){
			int d=distance(h,s);
			if(dist>d){
				dist=d;
				res=s;
			}
		}
		return res;
	}

	//評価関数
	int examine(Pos m,Pos g,int cnt){
		return distance(m,g)+predict_s(m.y,m.x);
	}

	int move_point(Pos current,Pos tmpg,int p){
		int y=current.y;
		int x=current.x;
		vi dx{0,0,1,-1};
		vi dy{1,-1,0,0};
		while(y!=tmpg.y || x!=tmpg.x){
			int d=INF;
			Pos m=Pos{0,0};
			for(int i=0;i<4;i++){
				int yy=y+dy[i];
				int xx=x+dx[i];
				if(xx<0 || xx>=N || yy<0 || yy>=N)continue;
				if(chmin(d,distance(Pos{yy,xx},tmpg))){
					m=Pos{yy,xx};
				}
			}
			p=max(power,(p/5))*destruct(m.y,m.x,max(power,p/5));
			if(exs[m.y][m.x]!=-1)p+=(exs[m.y][m.x])*(power);
			y=m.y;
			x=m.x;
		}
		return p;
	}

	bool isInside(Pos a){
		return (a.y>=0 && a.y<N && a.x>=0 && a.x<N);
	}

	//ゴールへの移動
    void move(Pos start, Pos goal) {
		map<Pos,int> seen;
		set<Pos> pseen;
		Pos cur=start;
		int cnt=1;
		int range=10;
		vector<Pos> path;
		path.push_back(cur);
		pseen.insert(cur);
		while(cur!=goal){
			//距離が50以内になったらゴールに直接移動する
			if(distance(cur,goal)<=2*range*range){
				path.push_back(goal);
				cur=goal;
			}
			else{
				/*
				vi dx{0,0,range,-range,range,range,-range,-range};
				vi dy{range,-range,0,0,range,-range,range,-range};
				*/
				vi dx{0,0,range,-range};
				vi dy{range,-range,0,0};
				double e=1e18;	//最も低い評価値
				Pos m=Pos{0,0};	//移動するマス
				bool bflag=false;
				for(int i=0;i<4;i++){
					int yy=cur.y+dy[i];
					int xx=cur.x+dx[i];
					if(!isInside(Pos{yy,xx}))continue;
					Pos mc=Pos{yy,xx};
					if(distance(cur,goal)>distance(mc,goal)){
						int yt=mc.y;
						int xt=mc.x;
						int md=INF;
						for(int j=yt-2;j<=yt+2;j++){
							for(int k=xt-2;k<=xt+2;k++){
								if(j<0 || j>=N || k<0 || k>=N)continue;
								if(exs[j][k]!=-1){
									if(chmin(md,distance(Pos{yt,xt},Pos{j,k}))){
										mc.y=j;
										mc.x=k;
									}
								}
							}
						}
						if(exs[mc.y][mc.x]==-1)exs[mc.y][mc.x]=predict_s(mc.y,mc.x);
						if(exs[mc.y][mc.x]*(power)<=200 && seen[Pos{yt,xt}]<=1){
							m=Pos{yt,xt};
							bflag=true;
							break;
						}
					}
				}
				if(!bflag){	
				//4方向の座標のマスを評価して移動する場所を決める
				for(int i=0;i<4;i++){
					int yy=cur.y+dy[i];
					int xx=cur.x+dx[i];
					if(yy<0 || yy>=N || xx<0 || xx>=N)continue;
					int md=INF;
					int yt=yy;
					int xt=xx;
					for(int j=yt-2;j<=yt+2;j++){
						for(int k=xt-2;k<=xt+2;k++){
							if(j<0 || j>=N || k<0 || k>=N)continue;
							if(exs[j][k]!=-1){
								if(chmin(md,distance(Pos{yt,xt},Pos{j,k}))){
									yy=j;
									xx=k;
								}
							}
						}
					}
					if(exs[yy][xx]==-1)exs[yy][xx]=predict_s(yy,xx);
					//ex=マス{yy,xx}の評価値
					double ss=(double)cnt;
					double ex=(double)distance(Pos{yt,xt},goal)/10+(double)exs[yy][xx]*1000.0/ss+(double)seen[Pos{yt,xt}]*10.0/ss;
					//cout<<"#ex : "<<ex<<endl;
					if(chmin(e,ex)){
						//移動するマスを一番評価値が低いものに更新する
						m=Pos{yt,xt};
					}
				}
				}
				//移動して座標を更新する
				seen[m]++;
				cur=m;
				if(pseen.find(cur)!=pseen.end()){
					while(path.back()!=cur){
						pseen.erase(path.back());
						path.pop_back();
					}
				}
				else{
					path.push_back(cur);
					pseen.insert(cur);
					goal=leastSource(cur);
				}
				cnt++;
			}
		}
			int initial_power=power;
			for(int i=0;i<path.size();i++){
				if(i==0){
					initial_power=destruct(path[i].y,path[i].x,initial_power)*initial_power;
					if(exs[path[i].y][path[i].x]!=-1)initial_power+=(exs[path[i].y][path[i].x])*(power);
					continue;
				}
				initial_power=move_point(path[i-1],path[i],initial_power);
			}
		}

	//マスの頑丈さを推測する関数
    int predict_s(int y, int x) {
        // excavate (y, x) with fixed power until destruction
		int cnt=1;
        while(!field.is_broken[y][x]) {
            Response result = field.query(y, x, power+20);
            if (result == Response::finish) {
                cerr << "total_cost=" << field.total_cost << endl;
                exit(0);
            } else if (result == Response::invalid) {
                cerr << "invalid: y=" << y << " x=" << x << endl;
                exit(1);
            } else if(result == Response::broken) {
				vi dx{0,0,1,-1};
				vi dy{1,-1,0,0};
				for(int i=0;i<4;i++){
					int yy=y+dy[i];
					int xx=x+dx[i];
					if(xx<0 || xx>=N || yy<0 || yy>=N)continue;
					if(source_pos.find(Pos{yy,xx})!=source_pos.end()){
						source_pos.insert(Pos{y,x});
						break;
					}
				}
				return cnt;
			}
			cnt++;
			if(cnt==1000/(power+20))return cnt;
        }
		return 0;
    }

	//掘削をする関数
    int  destruct(int y, int x,int p) {
		int cnt=1;
        // excavate (y, x) with fixed power until destruction
        while(!field.is_broken[y][x]) {
            Response result = field.query(y, x, p);
            if (result == Response::finish) {
                cerr << "total_cost=" << field.total_cost << endl;
				//ofstream res("./score.txt",ios::app);
				//res<<field.total_cost<<endl;
                exit(0);
            } else if (result == Response::invalid) {
                cerr << "invalid: y=" << y << " x=" << x << endl;
                exit(1);
            } else if(result == Response::broken) {
				vi dx{0,0,1,-1};
				vi dy{1,-1,0,0};
				for(int i=0;i<4;i++){
					int yy=y+dy[i];
					int xx=x+dx[i];
					if(xx<0 || xx>=N || yy<0 || yy>=N)continue;
					if(field.is_broken[yy][xx]){
						source_pos.insert(Pos{yy,xx});
					}
				}
				source_pos.insert(Pos{y,x});
				return cnt;
			}
			cnt++;
        }
		return 0;
    }
};

int main() {
	//値の入力
    int N, W, K, C;
    cin >> N >> W >> K >> C;
    set<Pos> source_pos;
    deque<Pos> house_pos(K);
    for (int i = 0; i < W; i++) {
		int y,x;
		cin>>y>>x;
		source_pos.insert(Pos{y,x});
    }
    for (int i = 0; i < K; i++) {
        cin >> house_pos[i].y >> house_pos[i].x;
    }
    Solver solver(N, source_pos, house_pos, C);
	//答えを求める
    solver.solve();
}
