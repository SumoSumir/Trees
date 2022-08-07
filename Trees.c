#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct data
{
	int n;
	struct data *left,*right;
}data;
data *head=NULL;

data *stack[10],*stack2[10];

int top=0,top2=0,delCount=0;

void input()
{
data *temp,*trav;
int placed=0;

    temp= (data*)malloc(sizeof(data*));
	temp->n=0;
	char inp[10];
	printf("\nEnter no. data :");
	getchar();
	fgets(inp,sizeof(inp)-1,stdin);
	temp->n=atoi(inp);
	temp->left=NULL;
	temp->right=NULL;
	if(head==NULL)
	    head=temp;
	else
	{
		trav=head;
		while(placed==0)
		{
			if(trav->n < temp->n)
			{
				if(trav->right==NULL)
				{ 
					trav->right=temp;
					placed++; 
				}
				else
					trav=trav->right;
			}
			else if (trav->n > temp->n)
			{
			if(trav->left==NULL)
			{
				trav->left=temp; 
				placed++;
			}
			else
				trav=trav->left;
			}
			else // for repeated elements we assumed placed for bst
				placed++;
		}
}
}

void push(data *element)
{
	stack[top++]=element;
}

data* pop()
{
	return stack[--top];
}

void push2(data *element)
{
	stack2[top2++]=element;
}

data* pop2()
{
	return stack2[--top2];
}

data* popQ()
{
	return stack[delCount++];
}

void printStack()
{
	int i;
	printf("\nStack has:");
	for(i=top;i>=0;i--)
	printf("%d\t",stack[i]->n);
	printf("\n");
}

void pre() //format (vlr)
{
	data *tmp=head;
	top=0;
	while(1)
	{
		while(tmp!=NULL)
		{
		printf("%d,",tmp->n);
		if(tmp->right!=NULL)
			push(tmp->right);
		tmp=tmp->left;
	    }
		if(top>0)
		tmp=pop();
		else
		break;
	}
}

void post() //format (lrv) 
//2 stacks method
{
	data *tmp=head;
	top=0;
	top2=0;
	push(tmp);
	while(top>0)
	{
		push2(tmp); //stack 2
		if(tmp->left)
		push(tmp->left);
		if(tmp->right)
		push(tmp->right);
		tmp=pop();
	}
	
	while(top2>0)
	{
		tmp=pop2();
		printf("%d,",tmp->n);
	}
}


void in() //format (lvr), iterative w/o stack
{
	data *current,*predecessor;
	current=head;
	while(current!=NULL)
	{
		if(current->left==NULL)
		{
			printf("%d,",current->n);
			current=current->right;
		}
		else
		{
			predecessor=current->left;
			// why predecessor->right!=current ??? -
			//Ans:to have stop point to revert back to old tree
			while(predecessor->right!=NULL && predecessor->right!=current)  
			predecessor=predecessor->right;      
			if(predecessor->right==NULL)
			{
				predecessor->right=current;
				current=current->left;
			}
			else
			{
				predecessor->right=NULL;
				printf("%d,",current->n);
				current=current->right;
			}
		}
	}
}

void in2()  //format (lvr)
// iterative using stack
{
data *tmp=head;
top=0;
	while(1)
	{
		if(tmp!=NULL)
		{
			push(tmp);
			tmp=tmp->left;
	    }
	    else
	    {
			if(top>0)
			{
				tmp=pop();
				printf("%d,",tmp->n);
				tmp=tmp->right;
			}
			else
				break;
	    }
	}
}


void LO() // level order uses queue -- if stack was used it would give mirror
{
	data *tmp=head;
	delCount=0;
	top=0;
	while(tmp && delCount<=top)
	{
		printf("%d,",tmp->n);
		if(tmp->left)
		push(tmp->left);
		if(tmp->right)
		push(tmp->right);
		tmp=popQ();
	}
}

int heightRecursive(data *element)
{
	int leftHeight,rightHeight;
	if(element==NULL)
	return 0;
	else
	{
		leftHeight=heightRecursive(element->left);
		rightHeight=heightRecursive(element->right);
		if(leftHeight>rightHeight)
		return (leftHeight+1);
		else
		return (rightHeight+1);
	}
}


int height()
{
	data *tmp;
	int height=0,QNodecount;
	top=0;
	delCount=0;
	
	if(head==NULL)
	return 0;
	
	push(head);
	while(1)
	{
    	QNodecount=top-delCount;
		if(QNodecount==0)
		return height;
		height++;
		
		while(QNodecount>0)
		{
			tmp=popQ();
			if(tmp->left!=NULL)
			push(tmp->left);
			if(tmp->right!=NULL)
			push(tmp->right);
			QNodecount--;
		}
	}
	
}


void mirror() //altered level order and pre order.. 
            //(using stack) - will show as mirrored pre order traversal
{
	data *tmp=head;
	top=0;
	do
	{
		printf("%d,",tmp->n);
		if(tmp->left!=NULL)
		    push(tmp->left);
		if(tmp->right!=NULL)
			push(tmp->right);
		tmp=pop();
	}while(top>-1);
}

int main() //TD free all the data
{
	int choice=0,max=0;
	printf("\nTrees\n\n");
	while(choice!=8)
	{
		printf("\n\n1)Input\n2)Pre\n3)Mirror\n4)Height\n5)Post\n6)In"
        "\n7)Level Order\n8)Exit\n");
		scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            {
                input(); //w/o rec
                break;
            } 
            case 2:
            { 
                pre(); // w/o recursion
                break;
            } 
            case 3:
            {
                mirror(); // w/o rec
                break;
            } 
            case 4:
            { 
                max=heightRecursive(head);  // rec used
                printf("height = %d",max);
                max=height();  //non rec
                printf("\nHeight from non rec : %d",max);
                break;
            }
            case 5:
            {
                post();
                break;
            }
            case 6:
            {
                in();
                printf("\n\n");
                in2();
                break;
            }
            case 7:
            {
                LO();
                break;
            }
            case 8: 
            break;
            default:
                printf("Invalid input");
        }
    }
	return 0;
}
