/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

%{
#include "common/hash-str.h"

#include "director/lingo/lingo.h"
#include "director/lingo/lingo-gr.h"

Common::HashMap<Common::String, int, Common::IgnoreCase_Hash, Common::IgnoreCase_EqualTo> vars;

extern int yylex();
extern int yyparse();
void yyerror(char *s) { warning("%s", s); }

using namespace Director;

%}

%union { float f; int i; Common::String *s; }

%token UNARY
%token<f> FLOAT
%token<i> INT
%token<s> VAR
%token<s> STRING
%token OP_INTO
%token OP_TO
%token FUNC_MCI
%token FUNC_MCIWAIT
%token FUNC_PUT
%token FUNC_SET

%type<i> expr
%type<i> func

%right '='
%left '+' '-'
%left '*' '/' '%'
%right UNARY

%%

list: statement
	| list '\n' statement
	;

statement: expr
	| func
	;

expr: INT						{ $$ = g_lingo->code2(g_lingo->func_constpush, (inst)$1); }
	| VAR						{ g_lingo->code1(g_lingo->func_varpush); g_lingo->codeString($1->c_str()); $$ = g_lingo->code1(g_lingo->func_eval); delete $1; }
	| expr '+' expr				{ g_lingo->code1(g_lingo->func_add); }
	| expr '-' expr				{ g_lingo->code1(g_lingo->func_sub); }
	| expr '*' expr				{ g_lingo->code1(g_lingo->func_mul); }
	| expr '/' expr				{ g_lingo->code1(g_lingo->func_div); }
	| '+' expr  %prec UNARY		{ $$ = $2; }
	| '-' expr  %prec UNARY		{ $$ = $2; g_lingo->code1(g_lingo->func_negate); }
	| '(' expr ')'				{ $$ = $2; }
	|
	;

func: FUNC_MCI STRING			{ g_lingo->code1(g_lingo->func_mci); g_lingo->codeString($2->c_str()); delete $2; }
	| FUNC_MCIWAIT VAR			{ g_lingo->code1(g_lingo->func_mciwait); g_lingo->codeString($2->c_str()); delete $2; }
	| FUNC_PUT expr OP_INTO VAR	{ g_lingo->code1(g_lingo->func_varpush); g_lingo->codeString($4->c_str()); g_lingo->code1(g_lingo->func_assign); $$ = $2; delete $4; }
	| FUNC_SET VAR '=' expr		{ g_lingo->code1(g_lingo->func_varpush); g_lingo->codeString($2->c_str()); g_lingo->code1(g_lingo->func_assign); $$ = $4; delete $2; }
	| FUNC_SET VAR OP_TO expr	{ g_lingo->code1(g_lingo->func_varpush); g_lingo->codeString($2->c_str()); g_lingo->code1(g_lingo->func_assign); $$ = $4; delete $2; }
	;

%%
