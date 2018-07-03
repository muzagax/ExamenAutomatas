%{
 	/*
	 * Nombre del equipo: Jár
	 * Ejecución del programa: jar-lexer.exe archivo-del-codigo-fuente
	 * Al ejecutar el comando, el programa mostrará en pantalla por línea cada lexema encontrado
	 * con su respectiva clasificación. En caso de encontrar un error, mostrará también el mensaje respectivo
	 * el cual incluye el lexema que generó dicho error
	 * Al final de la ejecución el programa muestra el total de tokens y de errores encontrados.
	 */

    #include <iostream>
	#include <string>
	#include "nodos.h"
    #include "parser.tab.h"
    #define YY_DECL extern "C" int yylex()
	
	using namespace std;
	int tokens = 0;
 	int errores = 0;
%}

%option noyywrap yylineno
/* Números negativos con decimales */
NUMND	-[0-9]+\.[0-9]+
/* Números positivos con decimales */
NUMPD	[0-9]+\.[0-9]+
/* Números negativos */
NUMN	-[0-9]+
/* Números positivos */
NUMP 	[0-9]
/* Identificadores alfanuméricos */
IDALFA	[a-zA-Z_][a-zA-Z0-9_]*
%%
"hilera"	{
        yylval.hilera = new string(yytext,yyleng);
		return t_hilera;
	}
"entero"	{
        yylval.hilera = new string(yytext,yyleng);
		return t_entero;
	}
"bool"	{

        yylval.hilera = new string(yytext,yyleng);
		return t_boolean;
	}
"si"	{
        yylval.hilera = new string(yytext,yyleng);
		return t_si;
	}
"sino" {
	yylval.hilera = new string(yytext,yyleng);
		return t_sino;	
	}
"pero"	{
	yylval.hilera = new string(yytext,yyleng);
		return t_pero;
	}
"mientras" {
	yylval.hilera = new string(yytext,yyleng);
		return t_mientras;
	}
"para"	{
        yylval.hilera = new string(yytext,yyleng);
		return t_para;
	}
"hasta"	{
        yylval.hilera = new string(yytext,yyleng);
		return t_hasta;
	}
"COMENTARIO".*;	{
        	/**yylval.palabras = yytext;
		return t_comentario;**/
		//esto hay que reconocerlo e ignorarlo :P
	}

"imprimir" {
		yylval.hilera = new string(yytext,yyleng);
		return t_imprimir;

	}

"escanear" {
		yylval.hilera = new string(yytext,yyleng);
		return t_escanear;
	}
"Iniciar" {
		yylval.hilera = new string(yytext,yyleng);
		return t_iniciar;
	}

"retornar"	{
        yylval.hilera = new string(yytext,yyleng);
		return t_retornar;
	}
"vacio"	{
        yylval.hilera = new string(yytext,yyleng);
		return t_vacio;
	}
"mayor_que"	{
        yylval.valores = MAYOR;
		return t_mayor_que;
	}
"menor_que"	{   
        yylval.valores = MENOR;
		return t_menor_que;
	}
"mayor_igual"	{
        yylval.valores = MAYOR_IGUAL;
		return t_mayor_igual;
	}
"menor_igual"	{
        yylval.valores = MENOR_IGUAL;
		return t_menor_igual;
	}
"diferente_a"	{
        yylval.valores = DIFERENTE;
		return t_diferente_a;
	}
"igual_a"	{
        yylval.valores = IGUAL;
		return t_igual_a;
	}
{NUMND}+ 	{
        yylval.valores = atoi(yytext);
		return t_num_neg_dec;
 	}
{NUMPD}+ 	{
        yylval.valores = atoi(yytext);
		return t_num_pos_dec;
 	}
{NUMN}+ 	{
        yylval.valores = atoi(yytext);
		return t_num_neg;
 	}
{NUMP}+ 	{
        yylval.valores = atoi(yytext);
		return t_num_pos;
 	}
{IDALFA}+ 	{
        yylval.hilera = new string(yytext,yyleng);
		return t_id;
 	}
"+"		{
        yylval.valores = SUMA;
		return t_mas;
	}
"-"		{
        yylval.valores = RESTA;
		return t_menos;
	}
"*"		{
        yylval.valores = MULTI;
		return t_multiplicacion;
	}
"/"		{
        yylval.valores = DIV;
		return t_division;
	}
"%"		{
        yylval.valores = MOD;
		return t_modulo;
	}
"="		{

		return t_igual_a;
	}
"&"	{
        yylval.valores = AND;
		return t_and;
	}
"|"	{
        yylval.valores = OR;
		return t_or;
	}
"!"	{
        yylval.valores = NEG;
		return t_negacion;
	}
"("		{

		return t_parent_iz;
	}
")"	{

		return t_parent_de;
	}
":"	{

		return t_dos_puntos;
	}
";"	{

		return t_punto_coma;
	}
","	{

		return t_coma;
	}
"\""	{

		return t_comillas;
	}
"["	{

		return t_cuadrado_iz;
	}
"]"	{

		return t_cuadrado_de;
	}
[ \t\n]	;
.	{
		/* Para todos los demás lexemas no clasificados */
        yylval.error = yytext;
		return t_error_lexico;
	}
%%
