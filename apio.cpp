/*
 * we can transform the task to " find the maximum number of elements with sum <= m in a range l r " by using dfs order
 * we can answer the previous query using persistent segment tree ( it is similar to find the k'th element in an array using binary tree )
 * it can be solved using dsu on tree also ( my dsu on tree solution : https://github.com/besherislambouley/Dispatching2/blob/master/apio.cpp ) 
*/
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 547
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ld pai=acos(-1);
ll N , n , m ;
vll v[100009] ;
ll c[100009] , l[100009] , ord[100009] , st[100009] , en[100009] , timer ;
map < ll , ll > id12,id21 ; set < ll > s ;
struct NODE {
        ll sum , num ;
        NODE *left , *right ;
        NODE (){
                sum = num = 0 ;
                left = right = NULL ;
        }
}*version[100009] ;
void dfs ( int node , int p ) {
        ord[ timer ]= node ;
        st [ node ] = timer ++ ;
        for ( auto u : v[node] ) {
                if ( u == p ) C ;
                dfs ( u , node ) ;
        }
        en [ node ] = timer - 1 ;
}
void build ( NODE *node , int l , int r ) {
        if ( l == r ) return ;
        node -> left = new NODE ;
        node -> right= new NODE ;
        build ( node->left , l , mid ) ;
        build ( node->right, mid +1,r);
}
void upd ( NODE *pre , NODE *node , int l , int r , int id ) {
        if ( l == r ) {
                node -> num = pre->num + 1 ;
                node -> sum = pre->sum + id21[l] ;
                return ;
        }
        if ( id <= mid ) {
                node -> left = new NODE ;
                node ->right = pre -> right ;
                upd ( pre -> left , node -> left , l , mid , id ) ;
        }
        else {
                node -> left = pre -> left ;
                node ->right = new NODE ;
                upd ( pre -> right , node -> right , mid+1 , r , id ) ;
        }
        node -> num = node->left->num + node->right->num ;
        node -> sum = node->left->sum + node->right->sum ;
}
ll query ( NODE *L , NODE *R , int l , int r , ll still , ll ans ) {
        if ( l == r ) {
                ans += min ( R->num - L-> num ,  still / id21[l] ) ;
                return ans ;
        }
        ll cost = R->left->sum - L->left->sum ;
        ll bon  = R->left->num - L->left->num ;
        if ( still >= cost ) return query ( L->right , R->right , mid+1 , r , still - cost , ans + bon ) ;
        else return query ( L->left , R->left , l , mid , still , ans ) ;
}
int main () {
        cin >> n >> m ;
        for ( int i = 0 ; i < n ; i ++ ) {
                int b ;
                cin >> b >> c[i] >> l[i] ;
                s.ins ( c[i] ) ;
                b -- ;
                if ( b == -1 ) C ;
                int a = i ;
                v[a].pb ( b ) ;
                v[b].pb ( a ) ;
        }
        for ( auto u : s ) id12 [u] = N , id21[N] = u , N ++ ;
        N -- ;
        for ( int i = 0 ; i < n ; i ++ ) c[i] = id12 [c[i]] ;
        dfs ( 0 , 0 ) ;
        version[0] = new NODE ;
        build ( version[0] , 0 , N ) ;
        for ( int i = 0 ; i < n ; i ++ ) {
                version[i+1] = new NODE ;
                upd ( version[i] , version[i+1] , 0 , N , c [ ord[i] ] ) ;
        }
        ll ans = 0 ;
        for ( int i = 0 ; i < n ; i ++ ) {
                ll num = query ( version [ st[i] ] , version[ en[i]+1 ] , 0 , N , m , 0 ) ;
                ans = max ( ans , num * l[i] ) ;
        }
        cout << ans << endl ;
}
