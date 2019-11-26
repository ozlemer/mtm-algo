#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct polynomial{
    int coef;
    int deg;
    struct polynomial *next;
    
}poly;

poly * CreateNode();
poly * CreatePoly(int);
void displayList(poly *);
void SumPolynomials(poly *, poly *,poly *);
void Simplification(poly *);
void MultiplyPolynomial(poly *, poly* ,poly *);


int main()
{
    printf("Hello World\n");
    poly *p1, *p2,*sum,* product;
    int n1,n2;
    printf("Please enter the number of terms for first polynomial: ");
    scanf("%d",&n1);
    printf("Please enter the number of terms for second polynomial: ");
    scanf("%d",&n2);
    printf("Please enter terms from highest degree to lowest degree for first polynomial\n");
    p1 = CreatePoly(n1);
    printf("Please enter terms from highest degree to lowest degree for second polynomial\n");
    p2 = CreatePoly(n2);
    sum = CreateNode();
    SumPolynomials(p1,p2,sum);
    printf("SUM: ");
    displayList(sum);
    product = CreateNode();
    MultiplyPolynomial(p1,p2,product);
    Simplification(product);
    printf("MULTIPLY: ");
    displayList(product);
    
    return 0;
}

poly * CreateNode(){
    poly *node;
    
    node = (poly *)calloc(sizeof(poly),1);
    if(node == NULL){
        printf("Memory can not be allocated! \'CreateNode\'");
        exit(0);
    }
    else{
        node->next = NULL;
        return node;
    }
}
poly * CreatePoly(int n){
    poly *polynomial,*tail, *tmp;
    int coef, deg,i;
    
    polynomial = (poly *)calloc(sizeof(poly),1);
    if(polynomial == NULL){
        printf("Memory can not be allocated! \'CreatePoly\'");
        exit(0);
    }
    else{
        printf("node 1 coefficient: ");
        scanf("%d",&coef);
        printf("node 1 degree: ");
        scanf("%d",&deg);
        polynomial->coef = coef;
        polynomial->deg = deg;
        polynomial->next = NULL;
        tmp = polynomial;
        
        for(i=2;i<=n;i++){
            tail = (poly *)calloc(sizeof(poly),1);
            if(tail == NULL){
                printf("Memory can not be allocated! \'CreatePoly\'");
                exit(0);
            }
            else{
                printf("node %d coefficient: ",i);
                scanf("%d",&coef);
                printf("node %d degree: ",i);
                scanf("%d",&deg);
                
                tail->coef = coef;
                tail->deg = deg;
                tail->next = NULL;
                
                tmp->next = tail;
                tmp = tmp->next;
                
            }
        }
        
        return polynomial;
    }    
    
}

void displayList(poly *polynomial)
{
    poly *tmp;
    if(polynomial == NULL)
    {
        printf(" List is empty.");
    }
    else
    {
        tmp = polynomial;
        while(tmp->next != NULL)
        {
            printf("%dx\^%d",tmp->coef, tmp->deg);       
            tmp = tmp->next;
            if(tmp->next !=NULL)
                printf(" + ");
        }
        printf("\n");
    }
}

void SumPolynomials(poly* poly1, poly *poly2, poly *sum){
    
    poly* ptr1,*ptr2,*ptrs,*ptrf,*head;
    ptr1 = poly1;
    ptr2 = poly2;
    ptrs = CreateNode();
    ptrs=sum;
    
    while(ptr1 && ptr2){
        if(ptr1->deg > ptr2->deg){
            ptrs->coef = ptr1->coef;
            ptrs->deg = ptr1->deg;
            ptr1 = ptr1->next;
        }
        else if(ptr1->deg < ptr2->deg){
            ptrs->coef = ptr2->coef;
            ptrs->deg = ptr2->deg;
            ptr2 = ptr2->next;
        }
        else{
            ptrs->coef = ptr1->coef + ptr2->coef;
            ptrs->deg = ptr1->deg;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        
        ptrs->next = CreateNode();
        ptrs = ptrs->next;
    }
    
    
    
    while(ptr1 || ptr2){
        if(ptr1){
            ptrs->coef = ptr1->coef;
            ptrs->deg = ptr1->deg;
            ptr1 = ptr1->next;   
        }
        if(ptr2){
            ptrs->coef = ptr2->coef;
            ptrs->deg = ptr2->deg;
            ptr2 = ptr2->next; 
        }
        
        ptrs->next = CreateNode();
        ptrs = ptrs->next;
    }
    
    ptrs->next = NULL;
    
}
void Simplification(poly * polyp){
    poly *ptr1,*ptr2,*delete;
    ptr1 = polyp;
    
    while(ptr1 && ptr1->next){
        ptr2 = ptr1;
        
        while(ptr2->next){
            if(ptr1->deg == ptr2->next->deg){
                ptr1->coef = ptr1->coef + ptr2->next->coef;
                delete = ptr2->next;
                ptr2->next = ptr2->next->next;
                
                free(delete);
            }
            else{
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
    }
}
void MultiplyPolynomial(poly *poly1, poly* poly2,poly *product){
    poly *ptr1, *ptr2, *ptrp;
    int coef, deg;
    
    ptrp = product;
    ptr1 = poly1;
    ptr2 = poly2;
    
    coef = 0; deg = 0;
    while(ptr1){
        while(ptr2){
            
            ptrp->coef = (ptr1->coef) * (ptr2->coef);
            ptrp->deg = (ptr1->deg)+ (ptr2->deg);
            ptrp->next = CreateNode();
            ptrp = ptrp->next;
            ptr2 = ptr2->next;
        }
        ptr2 = poly2;
        ptr1 = ptr1->next;
    }
    
}