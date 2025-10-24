#include <stdio.h>

int main() {
  int n;
  printf("Your student ID: ");
  scanf("%d", &n);
  if(n == 2025046018) printf("Your name is Kim RaeHyeon");
  else if(n == 2025046027) printf("Your name is Kim WooJin");
  else if (n == 2025046022) printf("Your name is Hong TaeGyeong");
  else if (n == 2025046032) printf("Your name is Kim jungHun");
  else printf("can't search student ID"):

  return 0;
}
