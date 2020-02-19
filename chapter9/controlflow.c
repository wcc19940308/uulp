//
// Created by 王琛超 on 2020/2/18.
//

#include <stdio.h>
#include <string.h>
#include "smsh.h"


enum states   { NEUTRAL, WANT_THEN, THEN_BLOCK }; // 正常区，执行完if需要then，根据if的结果判断是否执行then下面的内容
enum results  { SUCCESS, FAIL };

static int if_state  = NEUTRAL; // 中立区
static int if_result = SUCCESS;
static int last_stat = 0;

int	syn_err(char *);

int ok_to_execute()
/*
 * purpose: determine the shell should execute a command
 * returns: 1 for yes, 0 for no
 * details: if in THEN_BLOCK and if_result was SUCCESS then yes
 *          if in THEN_BLOCK and if_result was FAIL    then no
 *          if in WANT_THEN  then syntax error (sh is different)
 */
{
    int	rv = 1;		/* default is positive */

    if ( if_state == WANT_THEN ){
        syn_err("then expected");
        rv = 0;
    }
    // 当执行到then的时候根据if的结果是否为真决定是否执行then的内容
    else if ( if_state == THEN_BLOCK && if_result == SUCCESS )
        rv = 1;
    else if ( if_state == THEN_BLOCK && if_result == FAIL )
        rv = 0;
    return rv;
}

int is_control_command(char *s)
/*
 * purpose: boolean to report if the command is a shell control command
 * returns: 0 or 1
 */
{
    return (strcmp(s, "if") == 0 || strcmp(s, "then") == 0 || strcmp(s, "fi") == 0);
}


int do_control_command(char **args)
/*
 * purpose: Process "if", "then", "fi" - change state or detect error
 * returns: 0 if ok, -1 for syntax error
 *   notes: I would have put returns all over the place, Barry says "no"
 */
{
    char *cmd = args[0];
    int	rv = -1;

    if( strcmp(cmd,"if")==0 ){
        if ( if_state != NEUTRAL )
            rv = syn_err("if unexpected");
        else {
            // 如果是if，那么处理if后面的指令
            last_stat = process(args + 1);
            if_result = (last_stat == 0 ? SUCCESS : FAIL );
            if_state = WANT_THEN;
            rv = 0;
        }
    }
    else if ( strcmp(cmd,"then")==0 ){
        if ( if_state != WANT_THEN )
            rv = syn_err("then unexpected");
        else {
            if_state = THEN_BLOCK;
            rv = 0;
        }
    }
    else if ( strcmp(cmd,"fi")==0 ){
        if ( if_state != THEN_BLOCK )
            rv = syn_err("fi unexpected");
        else {
            if_state = NEUTRAL;
            rv = 0;
        }
    }
    else
        fatal("internal error processing:", cmd, 2);
    return rv;
}

int syn_err(char *msg)
/* purpose: handles syntax errors in control structures
 * details: resets state to NEUTRAL
 * returns: -1 in interactive mode. Should call fatal in scripts
 */
{
    if_state = NEUTRAL;
    fprintf(stderr,"syntax error: %s\n", msg);
    return -1;
}