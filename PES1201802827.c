#include "intal.h"

#include <string.h>

#include <stdio.h>

#include <stdlib.h>

static void swapper(char **ptr1  ,char **ptr2)
{
  
  char *swap=*ptr1;
  *ptr1=*ptr2;
  *ptr2=swap;
}
static void heapification(char **arr, int n, int i) 
{
    // Find max_ele among root, left child and right child
  int max_ele,left,right;
  while(i<n)
  {
     max_ele = i;
     left = 2*i+1;
     right = 2*i+2;
  
    if (left < n && (intal_compare(arr[left],arr[max_ele])==1))//intal_compare(arr[left],arr[max_ele])==1
      max_ele = left;
  
    if (right < n && (intal_compare(arr[right],arr[max_ele])==1))//intal_compare(arr[right],arr[max_ele])==1
      max_ele = right;
  
    // Swap and continue heapifying if root is not max_ele
    //if (max_ele != i) {
      //swapper(&arr[i], &arr[max_ele]);
      //heapification(arr, n, max_ele);//propogate the effect again for the new parent obtained.
    //}
    if(max_ele==i)
        return;
    //printf("%s <----> %s  at index %d\n",arr[i],arr[max_ele],max_ele);
    swapper(&arr[i], &arr[max_ele]);

    i=max_ele;
  }

  }

char * intal_add(const char* intal1, const char* intal2)

{
  //addition is carried from right to left 
  //however the the operand with minimal digits is the delimeter
  //hence we'll find the operand with minimal length

  if (strlen(intal1) < strlen(intal2)) {
    const char * temp = intal2;
    intal2 = intal1;
    intal1 = temp;
  }
  
  if(strcmp(intal2,"0")==0)
  {
    char *result=(char*)malloc(sizeof(char)*(strlen(intal1)+1));
    result[strlen(intal1)]='\0';
    strcpy(result,intal1);
    return result;
  }
  int small, large;
  //always here len_op1 > len_op2
 
  int len_op1 = strlen(intal1);
  int carry = 0;
  int res_len = len_op1;
  int len_op2 = strlen(intal2);
 
  char *res_intal = (char *)malloc(sizeof(char)*(len_op1 + 2));

  res_intal[len_op1 + 1] = '\0';

  for (small = len_op2-1, large=len_op1-1; small>=0; small--, large--) {
    int sum = (intal1[large] - '0') + (intal2[small] - '0') + carry;
    carry = sum / 10;
    sum = sum % 10;
    res_intal[res_len--] = sum + '0';

  }

  while (large >= 0) {
    int sum = (intal1[large] - '0') + carry;
    carry = sum / 10;
    sum = sum % 10;
    res_intal[res_len--] = sum + '0';
    large--;

  }

  if (carry != 0) {
    res_intal[0] = carry + '0';
    return res_intal;
  } 
  else {

    res_intal[0] = '0';
       
       }





  //trimmer function
 
  int index = -1;
  for (int i = 0; i < strlen(res_intal); i++) {
    if (res_intal[i] != '0') {
      index = i;
      break;
    }
  }
  if (index == 0) //'no lead zeroes'
  {

    return res_intal;
  } 
  else if (index == -1) //'filled with zeroes only'
  {

    char * res = (char * ) malloc(sizeof(char)*2);
    res[0] = '0';
    res[1] = '\0';

    free(res_intal);
    res_intal = NULL;
    return res;
  } 
  else 
  {
    int j;

    char * result = (char * ) malloc(sizeof(char) * (strlen(res_intal) - index+1));
    result[strlen(res_intal) - index]='\0';
    for (j = 0; j < strlen(res_intal) - index; j++)
    		result[j] = res_intal[index + j];
   
    free(res_intal);

   
    res_intal = NULL;
   
    return result;

  }

}
int intal_compare(const char* intal1, const char* intal2) {
  int stop;
  if (strlen(intal1) > strlen(intal2))
    return +1;
  else if (strlen(intal1) < strlen(intal2))
    return -1;
  else
  {
    for ( stop = 0; stop < strlen(intal1); stop++) {
      if ((intal1[stop]-'0') > (intal2[stop]-'0'))
        return 1;
      if ((intal1[stop]-'0') < (intal2[stop]-'0'))
        return -1;
    }
    if(stop==strlen(intal1))
      return 0;
  }
  return 19999;

}

char * intal_diff(const char* intal1, const char* intal2) {
  const char * temp;
  if (strlen(intal1) < strlen(intal2)) {
    temp = intal2;
    intal2 = intal1;
    intal1 = temp;
  } else if (strlen(intal1) == strlen(intal2)) {
    for (int stop = 0; stop < strlen(intal1); stop++) {
      if ((intal1[stop] - '0') > (intal2[stop] - '0')) {
      	
        break;
      }
      if((intal2[stop] - '0') > (intal1[stop] - '0'))
      {
      	 temp = intal2;
        intal2 = intal1;
        intal1 = temp;
        break;
      }
    }
  }
 

  int small, large;
  //always here len_op1 > len_op2 i.e intal1-intal2
  int len_op1 = strlen(intal1);
  int carry = 0;
  int res_len = len_op1 - 1;
  int len_op2 = strlen(intal2);
 
  char * res_intal = (char * ) malloc(sizeof(char) * (len_op1+1));

  res_intal[len_op1] = '\0';
  for (small = len_op2 - 1, large = len_op1 - 1; small >= 0; small--, large--) {
    int difference = (intal1[large] - '0') - (intal2[small] - '0') - carry;
    if (difference < 0) {
      difference += 10;
      carry = 1;
    } else
      carry = 0;
    res_intal[res_len--] = difference + '0';
   
  }
  while (large >= 0) {
    int difference = (intal1[large] - '0') - carry;
    if (difference < 0) {
      difference += 10;
      carry = 1;
    } else
      carry = 0;
    res_intal[res_len--] = difference + '0';
    large--;
  }
  int index = -1;
  for (int i = 0; i < strlen(res_intal); i++) {
    if (res_intal[i] != '0') {
      index = i;
      break;
    }
  }
  if (index == 0) {
    return res_intal;
  } else if (index == -1) {
    char * res = (char * ) malloc(sizeof(char)*2);
    res[0] = '0';
    res[1] = '\0';
    free(res_intal);
    res_intal=NULL;

    return res;
  } else {
    int j;
    char * result = (char * ) malloc(sizeof(char) * (strlen(res_intal) - index+1));
     result[strlen(res_intal) - index]='\0';
    for (j = 0; j < strlen(res_intal) - index; j++)
      result[j] = res_intal[index + j];
    //result[j] = '\0';
    free(res_intal);
    res_intal = NULL;
  
    return result;
    
  }

}

char * intal_multiply(const char* intal1, const char* intal2) {
  if (strlen(intal1) < strlen(intal2)) {
    const char * temp = intal2;
    intal2 = intal1;
    intal1 = temp;
  }
 
  if((strcmp(intal1,"0")==0) || (strcmp(intal1,"0")==0))
  {
    char *result=(char*)malloc(sizeof(char)*2);
    result[0]='0';
    result[1]='\0';
    return result;
  }
  int small, large;
  //always here len_op1 > len_op2
  int len_op1 = strlen(intal1);
  int carry = 0;
  int len_op2 = strlen(intal2);
  int res_len = len_op1 + len_op2 + 1;

  char * res_intal = (char * ) malloc(sizeof(char) * res_len);
  res_intal[res_len - 1] = '\0';
  for (int y = 0; y < res_len - 1; y++)
    res_intal[y] = '0';

  for (small = len_op2 - 1; small >= 0; small--) {
    carry = 0;

    for (large = len_op1 - 1; large >= 0; large--) {

     

      int sum = (intal2[small] - '0') * (intal1[large] - '0') + (res_intal[large + small + 1] - '0') + carry;
      carry = sum / 10;
      sum = sum % 10;
      res_intal[large + small + 1] = sum + '0';
     

    }
    if (carry > 0) {
      res_intal[large + small + 1] = carry + '0';
    }

  }

  int index = -1;
  for (int i = 0; i < strlen(res_intal); i++) {
    if (res_intal[i] != '0') {
      index = i;
      break;
    }
  }
  if (index == 0) {
    return res_intal;
  } else if (index == -1) {
    char * res = (char * ) malloc(sizeof(char)*2);
    res[0] = '0';
    res[1] = '\0';
    free(res_intal);
    res_intal=NULL;
    return res;
  } else {
    int j;
    char * result = (char * ) malloc(sizeof(char) * (strlen(res_intal) - index+1));
     result[strlen(res_intal) - index]='\0';
    for (j = 0; j < strlen(res_intal) - index; j++)
      result[j] = res_intal[index + j];
    //result[j] = '\0';
    free(res_intal);
    res_intal = NULL;
    
    return result;

  }

}

char* intal_factorial(unsigned int n)
{
    
 
  if(n==0||n==1)
  {
    char *result=(char*)malloc(sizeof(char)*2);
    result[0]='1';
    result[1]='\0';
   
    return result;
  }
  if(n==2)
  {
    char *result=(char*)malloc(sizeof(char)*2);
    result[0]='2';
    result[1]='\0';
    return result;
  }
  char *res;char prev[6];
  char *previous_result;
  unsigned int temp=n-1;

 
  sprintf(prev,"%u",temp);
  res=(char*)malloc(sizeof(char)*6);

  res[5]='\0';
  
  sprintf(res,"%d",n);
  
  
  
  for(unsigned int i=0;i<n-2;i++)
  {
        previous_result=res;
       
        res=intal_multiply(res,prev);
        
       
        sprintf(prev,"%u",--temp);
        free(previous_result);previous_result=NULL;

  }
  
  return res;

}
int intal_max(char **arr, int n)
{
  char *maximum=arr[0];
  int max_ele_index=0;
  for (int i=1;i<n;i++)
  {
      if(intal_compare(maximum,arr[i])==-1)
      {
        maximum=arr[i];
        max_ele_index=i;
      }
  }
  return max_ele_index;
}
int intal_min(char **arr, int n)
{
  char *minimum=arr[0];
  int min_ele_index=0;
  for (int i=1;i<n;i++)
  {
      if(intal_compare(minimum,arr[i])==1)
      {
        minimum=arr[i];
        min_ele_index=i;
      }
  }
  return min_ele_index;

}
int intal_search(char **arr, int n, const char* key)
{
  int loop_index=-1;
  for(loop_index=0;loop_index<n;loop_index++ )
  {
    if(intal_compare(arr[loop_index],key)==0)
    {
          return loop_index;
    }
  }
  
  return -1;
}
int intal_binsearch(char **arr, int n, const char* key)
{
 
  int right=n-1;
  int compared_result=2;
  int left=0;
  int mid_index;
  while(left < right)
  { 
    mid_index=(right+left)/2;
    compared_result=intal_compare(arr[mid_index],key);
    
      if(compared_result!=-1)
      {
        right=mid_index;
      }
      else
      {
        left=mid_index+1;
      }

  }
  if(intal_compare(key,arr[left])==0)
    return left;
  else
    return -1;

}

void intal_sort(char **arr, int n)
{
  if(n==1)
    return;
  
  for (int parent = n / 2 - 1; parent >= 0; parent--)
      heapification(arr, n, parent);
    //heapifying all sub heaps
    //n/2-1 is the last parent index
  for (int sorting = n - 1; sorting >=0; sorting--) {
      swapper(&arr[0], &arr[sorting]);
      //max heap is considered to get a nondecreasing order of elements
      // Heapifying the  root element suffices , as it inturn heapifies the whole tree
      heapification(arr, sorting, 0);
    }
}

char* intal_fibonacci(unsigned int n)
{
  char *fibo_0=(char*)malloc(sizeof(char)*2);
  char *free1;
  char *fibo_1=(char*)malloc(sizeof(char)*2);
  fibo_0[0]='0';
  fibo_0[1]='\0';
  fibo_1[0]='1';
  fibo_1[1]='\0';
  char *res_intal;
  free1=fibo_0;
  
  if(n==0)
  {
    free(fibo_1);
    return fibo_0;
  }
  if(n==1)
  {
    free(fibo_0);
    return fibo_1;
  }
  for(unsigned int start=0;start <= n-2;start++)
  {
      free1=fibo_0;
      //printf("free :%p fibo_0:%p fibo_1:%p\n",free1,fibo_0,fibo_1);
      
      res_intal=intal_add(fibo_0,fibo_1);
     
      fibo_0=fibo_1;
      fibo_1=res_intal;
      //printf("add :%p fibo_1:%p  fibo_0:%p \n",res_intal,fibo_1,fibo_0);
      free(free1);free1=NULL;

  }
  free(fibo_0);
  fibo_0=NULL;
  return res_intal;
}
char* intal_bincoeff(unsigned int n, unsigned int k)
{
  if(k > n-k)
    k=n-k;
  if(k==0)
  {
    //return res_pascal[0];
    char *quick=(char*)malloc(sizeof(char)*2);
    
    quick[0]='1';
    quick[1]='\0';

    return quick;
  }
  if(k==1)
  {
    char* larger=(char*)malloc(sizeof(char)*1002);
    larger[1001]='\0';
    sprintf(larger,"%u",n);
    return larger;
  }

  /*char *zero=(char *)malloc(sizeof(char)*2);
  zero[0]='0';
  zero[1]='\0';*/
  char *freeable;
  char **res_pascal = (char**) malloc((k+1)* sizeof(char*));
  res_pascal[0]=(char*)malloc(sizeof(char)*2);
  res_pascal[0][0]='1';
  res_pascal[0][1]='\0';
  
  for(int init=1;init < k+1;init++)
  {
    res_pascal[init]=(char*)malloc(sizeof(char)*2);
    res_pascal[init][0]='0';
    res_pascal[init][1]='\0';
  }
  
  
  for (int start=1;start <= n;start++)
  {
    
    for(int combinations= (k > start) ? start : k  ;combinations > 0 ;combinations--)
    {
      
          freeable=res_pascal[combinations];
          res_pascal[combinations]=intal_add(res_pascal[combinations],res_pascal[combinations-1]);
          
          free(freeable);
          freeable=NULL;

          if(start==n && combinations==k)
          {
             char * res_intal=(char*)malloc(sizeof(char)*(strlen(res_pascal[k])+1));
              res_intal[strlen(res_pascal[k])]='\0';
              strcpy(res_intal,res_pascal[combinations]);
              
              for(int h=0;h<k+1;h++)
              {
                free(res_pascal[h]);
              }
              
              free(res_pascal);
              
              return res_intal;
          }
          
      
    } 
    
  }
  
  return res_pascal[k];
  

}
char* coin_row_problem(char **arr, int n)
{
  
  if(n==1)
  {
    char *immediate=(char *)malloc(sizeof(char)*(strlen(arr[0])+1));
    immediate[strlen(arr[0])]='\0';
    strcpy(immediate,arr[0]);
    return immediate;

  } 
  char *current_ptr=(char*)malloc(sizeof(char)*(strlen(arr[0])+1));
  char *previous_result=(char*)malloc(sizeof(char)*2);
  //char *intermediate;
  //current_ptr[1002]='\0';
  //previous_result[1002]='\0';
  previous_result[0]='0';previous_result[1]='\0';
  //intermediate[1002]='\0';
  char *add_res;char* freeable;
  strcpy(current_ptr,arr[0]);
  current_ptr[strlen(arr[0])]='\0';
  for(int looper=2;looper <=n ;looper++)
  {
      freeable=previous_result;
      add_res=intal_add(arr[looper-1],previous_result);
      if(intal_compare(add_res,current_ptr)==1)
      { 
      	//free(previous_result);
      	
      	previous_result=current_ptr;
        	current_ptr=add_res;
      }
      else
      {
      	free(add_res);add_res=NULL;
      	previous_result=current_ptr;
      }
      if(freeable!=previous_result)
      {
        //printf("%d\n",freeable==previous_result);
      	free(freeable);freeable=NULL;

      }
  }
  	
  if(previous_result!=current_ptr)
  {
  	free(previous_result);
  	previous_result=NULL;

  }
  return current_ptr;


}
char* intal_pow(const char* intal1, unsigned int n)
{
  if(strcmp(intal1,"0")==0)
  {
    char * res_intal=(char*)malloc(sizeof(char)*2);
    res_intal[0]='0';
    res_intal[1]='\0';
    return res_intal;
  }
  if(n==0)
  {
    char * res_intal=(char*)malloc(sizeof(char)*2);
    res_intal[0]='1';
    res_intal[1]='\0';
    return res_intal;
  }
  if(strcmp(intal1,"1")==0)
  {
    char * res_intal=(char*)malloc(sizeof(char)*2);
    res_intal[0]='1';
    res_intal[1]='\0';
    return res_intal;
  }
  if(n==1)
  {
    char *res_intal=(char *)malloc(sizeof(char)*(strlen(intal1)+1));
    res_intal[strlen(intal1)]='\0';
    strcpy(res_intal,intal1);
    return res_intal;
  }

 
  /*char *temp_res= intal_pow(intal1,n/2);
  char *mul_result=intal_multiply(temp_res,temp_res);
  free(temp_res); 
  if(n%2==0)
  {
    return mul_result;
  }
  else
  {
    char *k=intal_multiply(mul_result,intal1);
    free(mul_result);
    return k;
  }*/
    char *final_res=(char*)malloc(sizeof(char)*2);
    final_res[1]='\0';
    final_res[0]='1';
    char *dummy=(char*)malloc(sizeof(char)*(strlen(intal1)+1));
    char *last;
    strcpy(dummy,intal1); dummy[strlen(intal1)]='\0';
    char *base=dummy;
    char* pre_base;char* freeable;
    while(n>0)
    {
      if(n%2!=0)
      {
        freeable=intal_multiply(base,final_res);
        
        last=final_res;
        final_res=freeable;
        free(last);
        last=NULL;
      }
      n=n/2;
      if(n==0)
        break;
      pre_base=base;
      base=intal_multiply(base,base);
      free(pre_base);pre_base=NULL;
    }
    free(base);base=NULL;
    return final_res;

    



}
static void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}
static char* trim(char *string)
{
    int stop=-1;
    for(int h=0;h<strlen(string);h++)
    {
        if(string[h]!='0')
        {
            stop=h;
            break;
        }
    }
    if(stop==0)
    {
        char *new=(char*)malloc(sizeof(char)*(strlen(string)+1));
        new[strlen(string)]='\0';
        strcpy(new,string);
        return new;
    }
    if(stop==-1)
    {
        char *new=(char*)malloc(sizeof(char)*2);
        new[1]='0';
        new[0]='\0';
        return new;
    }
    else
    {
        char *res=(char*)malloc(sizeof(char)*(strlen(string)+1-stop));
        res[strlen(string)-stop]='\0';
        for(int j=0;j<strlen(string)-stop;j++)
        {
            res[j]=string[j+stop];
        }
        return res;
    }
}
char* intal_mod(const char* intal1, const char* intal2)
{
    if (intal_compare(intal2, "0") == 0)
    {
        return NULL;
    }

    int compare_res = intal_compare(intal1, intal2);
    if (compare_res < 0)
    {
        char *temp=(char*)malloc(sizeof(char)*(strlen(intal1)+1));
        temp[strlen(intal1)]='\0';
        strcpy(temp,intal1);       
        return temp;
        
    }
    if (compare_res == 0)
    {
        char *zero=(char*)malloc(sizeof(char)*2);
       zero[0]='0';
       zero[1]='\0';
       return zero;
    }

    int len1 = strlen(intal1);
    int len2 = strlen(intal2);

    char *quotient = (char*)malloc(sizeof(char)*(len1+1));
    quotient[0]='\0';

    char *free_ptr;

    char *previous = (char*)malloc(sizeof(char)*(len1+1));
    previous[len1]='\0';
    strncpy(previous, intal1, len2);
    *(previous + len2) = '\0';

    if (intal_compare(previous, intal2) < 0)
    {
        strncpy(previous, intal1, len2 + 1);
        *(previous + len2 + 1) = '\0';
    }

    int i, count, len_previous, previous_len = strlen(previous);

    for (i = 0; i < (len1 - previous_len + 1); i++)
    {
        count = 0;

        while (intal_compare(previous, intal2) >= 0)
        {

            count++;
            free_ptr = previous;
            previous = intal_diff(previous, intal2);
            free(free_ptr);
        }
        append(quotient, count + '0');

        if (i != len1 - previous_len)
        {
            len_previous = strlen(previous);
            char *new_ptr = (char *)malloc(sizeof(char)*(len_previous + 2));
            strcpy(new_ptr, previous);
            append(new_ptr, *(char *)(intal1 + previous_len + i));
            
            free(previous);
            free_ptr = new_ptr;
            previous = trim(new_ptr);
            free(free_ptr);

        }
    }
    free(previous);
    
    char *temp1=intal_multiply(quotient,intal2);
    
    char *temp2=quotient;
    quotient=temp1;
    free(temp2);
   
    temp1=intal_diff((intal1),quotient);
    
    temp2=quotient;
    quotient=temp1;
    free(temp2);
    return quotient;
}
char* intal_gcd(const char* intal1, const char* intal2)
{
   if((intal_compare(intal1,"0")==0)&&(intal_compare(intal2,"0")==0))
   {
    char *res_intal=(char*)malloc(sizeof(char)*2);
    res_intal[0]='0';
    res_intal[1]='\0';
    return res_intal;
   }
   
   if(intal_compare(intal1,intal2)==-1)
   {
   	const char *temp=intal1;
   	intal1=intal2;
   	intal2=temp;
    
   }
   char *A;char *B;
   A=(char*)malloc(sizeof(char)*(strlen(intal1))+1);strcpy(A,intal1);A[strlen(intal1)]='\0';
   B=(char*)malloc(sizeof(char)*(strlen(intal2))+1);strcpy(B,intal2);B[strlen(intal2)]='\0';
  


   char *mod_res;
   while(intal_compare(B,"0")!=0)
   {
    mod_res=intal_mod(A,B);
    strcpy(A,B);
    A[strlen(B)]='\0';
    
    strcpy(B,mod_res);
    B[strlen(mod_res)]='\0';
    free(mod_res);mod_res=NULL;
    

   }
   free(B);B=NULL;
   return A;
}