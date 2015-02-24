#include <stdio.h>
#include <pseudocode.h>

void
gotolabel(int lblidx)
{
	printf("\tgotolabel .L%i\n",lblidx);
}


void
gofalse(int lblidx)
{
	printf("\tgofalse .L%i\n",lblidx);
}

void
do_operation(int op)
{
    switch (op) {
    case '+':
        printf("\taddstack(_acc_reg)\n");
        break;
    case '-':
        printf("\tsubstack(_acc_reg)\n");
        break;
    case '*':
        printf("\tmulstack(_acc_reg)\n");
        break;
    case '/':
        printf("\tdivstack(_acc_reg)\n");
        break;
        /*
         * case OR: case DIV: case MOD: case AND: ; 
         */
    }
    rvalue();
}

void
rvalue(void)
{
    printf("\t_acc_reg=pop()\n");
}

void
memrecall(char const *label)
{
	printf("\t_acc_reg=recall(offsetof(%s))\n",label);
}

void
lvalue(char const *label)
{
	printf("\tstore(offsetof(%s),_acc_reg)\n",label);
}

void
mklbl(int lblidx)
{
	printf(".L%i:\n",lblidx);
}
