#include "arrays.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;
static int N, M;
static vector<int> A, B;
static int used_questions;

bool compare(int i, int j) {
  if (i <= 0 || j <= 0 || i > N || j > M) {
    printf("Invalid question: %d %d\n", i, j);
    exit(0);
  }
  used_questions++;
  return A[i-1] < B[j-1];
}

int main() {
  int K;
  scanf("%d%d%d", &N, &M, &K);
  for (int i = 0; i < N; i++) {
    int a;
    scanf("%d", &a);
    A.push_back(a);
  }
  for (int i = 0; i < M; i++) {
    int b;
    scanf("%d", &b);
    B.push_back(b);
  }

  int ans = find_k(N, M, K);
  bool correct = false;
  if (ans >= 1 && ans <= N && A[ans-1] == K) {
    correct = true;
  }
  if (-ans >= 1 && -ans <= M && B[-ans-1] == K) {
    correct = true;
  }

  if (correct) printf("Correct!\n");
  else printf("Incorrect: %d\n", ans);

  printf("Used %d comparisons\n", used_questions);
}
