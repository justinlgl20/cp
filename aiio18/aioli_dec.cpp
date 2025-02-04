#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> A_wins_against;
vector<int> B_wins_against;
vector<int> psa_a;
vector<int> psa_b;

int32_t main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> A;
    vector<int> B;
    queue<int> Aq;
    for (int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        A.push_back(x);
        Aq.push(x);
    }
    queue<int> Bq;
    for (int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        B.push_back(x);
        Bq.push(x);
    }
    psa_a.push_back(0);
    psa_b.push_back(0);
    A_wins_against.push_back(1e9);
    B_wins_against.push_back(1e9);
    for (int i = 0; i < N; i++)
    {
        while (Bq.size() and A[i]<Bq.front()) Bq.pop();
        A_wins_against.push_back(Bq.size());
        psa_a.push_back(psa_a.back()+Bq.size());
    }
    for (int i = 0; i < N; i++)
    {
        while (Aq.size() and B[i]<Aq.front()) Aq.pop();
        B_wins_against.push_back(Aq.size());
        psa_b.push_back(psa_b.back()+Aq.size());
    }



    int S;
    cin >> S;
    for (int i = 0; i < S; i++)
    {
        int a, b;
        cin >> a >> b;
        lower_bound(A_wins_against.rbegin(), A_wins_against.rbegin()+a, N-b);
        int l = 0;
        int r = a+1;
        while (l != r-1)
        {
            int mid = (l+r)/2;
            if (A_wins_against[mid] > N-b)
            {
                l = mid;
            } else 
            {
                r = mid;
            }
        }
        cout << psa_a[l]-(N-b)*(l) << " ";
        l = 0;
        r = b+1;
        while (l != r-1)
        {
            int mid = (l+r)/2;
            if (B_wins_against[mid] > N-a) 
            {
                l = mid;
            } else 
            {
                r = mid;
            }
        }
        cout <<psa_b[l]-(N-a)*(l) << "\n";
    }
}
