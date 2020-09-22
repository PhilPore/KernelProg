#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline char * sub_str(char * dest, char *src, int s_idx, int edix){
 // ...
  //...
  dest = malloc(((edix-s_idx)+1)*sizeof(char));
  int i;
  int j;
  for(i = s_idx,j; i < edix+1; i++,j++){
    dest[j] = src[i];
  }

  return dest;
}

static inline char * asm_sub_str(char * dest, char *src, int s_idx, int edix){
  //...
  //...
  dest = malloc(((edix-s_idx)+1)*sizeof(char));
  //int diff = edix-s_idx+1;
  int d0;
  int d1;
  int d2; 
  int fi;
  /*
  __asm__ volatile (
   "movl %1, %%eax;\n"
   "movl %%eax, %0;"
   :"=r"(d1)
   :"r"(s_idx)
   :"%eax"

  );*/
  //__asm__("movl %1 %eax");
  __asm__ __volatile__(
                        
                      "1:\tlodsb\n\t"
                       "stosb\n\t"
                       "addl $1, %%edx\n\t"
                       "cmp %%edx,%%ecx\n\t"
                       "jne 1b"
                     : "=&S" (d0), "=&D" (d1), "=&a" (d2)  
                     : "0" (src+s_idx),"1" (dest), "c" (edix+1), "d" (s_idx) 
                     : "memory");
  //printf("%d",d1);
  //dest[0] = d1;
 // printf("%d %d %d", d0,d1,d2);
  return dest;
}

int main(int argc,char **argv) {
    if (argc == 0){
        return 0;
    }
    char *str = argv[1];
    int s_ind = *argv[2] - '0';
    int e_ind = *argv[3] - '0';
    //char substr1[e_ind-s_ind+2]; //need that extra space for null terminator. Excuse thhese, I'm moronic.
    //char substr2[e_ind-s_ind+2];
    printf("%s %d %d\n", str, s_ind, e_ind);
    char *dest= sub_str(dest,str,s_ind,e_ind);
    printf("%s\n",dest);
    char *dest2 = asm_sub_str(dest2,str,s_ind,e_ind);
    printf("%s\n",dest2);
    if (strcmp(dest,dest2) == 0){
      printf("The two are Equal.\n");
    }
    else{
      printf("False.\n");
    }
    free(dest);
    free(dest2);
  //get a string and starting and ending indices from the command line,
  //call a C function, d1=sub_str(d,s,s_idx,e_idx),
  //call a C function, d2=asm_sub_str(d,s,s_idx,e_idx) using inlining,
  //compare the two strings d1 and d2 and return the result.
///http://ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html

    return 0;
}
