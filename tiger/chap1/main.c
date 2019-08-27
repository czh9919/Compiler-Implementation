#include "prog1.h"
#include "slp.h"
#include "stdio.h"
#include "util.h"
int maxargs(A_stm prog)
{
    switch (prog->kind)
    {
    case A_compoundStm:
    {
        int left = maxargs(prog->u.compound.stm1);
        int right = maxargs(prog->u.compound.stm2);
        return (left > right) ? left : right;
    }
    break;
    case A_assignStm:

        break;
    case A_printStm:
        /* code */
        break;

    default:
        break;
    }
}
