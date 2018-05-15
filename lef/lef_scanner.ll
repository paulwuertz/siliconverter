%{
#include <cstdlib>
#include <string>

#include "lefscanner.h"

#define YY_DECL int lef::LEFScanner::leflex(\
	lef::LEFParser::semantic_type* leflval,\
	lef::LEFData *lefdata)
%}

%option prefix="lef"
%option c++
%option batch
%option stack
%option debug
%option verbose
%option pointer
%option yywrap
%option nounput
%option yylineno

NUMBER			[0-9]
INTEGER			-{NUMBER}+|{NUMBER}+
EXPONENT		[eE][+-]?{INTEGER}
DOUBLE			{INTEGER}("."{INTEGER})?{EXPONENT}?

STRING			[A-Za-z]|[A-Za-z0-9_,.-<>\"\[\]\/\(\)]

SEMICOLON			";"
COMMENT				"#"
VERSION				"VERSION"
NAMESCASESENSITIVE	"NAMESCASESENSITIVE"
BUSBITCHARS			"BUSBITCHARS"
DIVIDERCHAR			"DIVIDERCHAR"
UNITS				"UNITS"
END					"END"
DATABASE			"DATABASE"
MICRONS				"MICRONS"
USEMINSPACING		"USEMINSPACING"
OBS					"OBS"
PICOFARADS "PICOFARADS"
PIN					"PIN"
CLEARANCEMEASURE	"CLEARANCEMEASURE"
MANUFACTURINGGRID	"MANUFACTURINGGRID"
LAYER				"LAYER"
TYPE				"TYPE"
SPACING				"SPACING"
DIRECTION			"DIRECTION"
PITCH				"PITCH"
OFFSET				"OFFSET"
WIDTH				"WIDTH"
RESISTANCE			"RESISTANCE"
EDGECAPACITANCE		"EDGECAPACITANCE"
CAPACITANCE			"CAPACITANCE"
VIA					"VIA"
RECT				"RECT"
VIARULE				"VIARULE"
TO					"TO"
BY					"BY"
USE					"USE"
OVERHANG			"OVERHANG"
METALOVERHANG		"METALOVERHANG"

AREA				"AREA"
SITE				"SITE"
SYMMETRY			"SYMMETRY"
CLASS				"CLASS"
SIZE				"SIZE"
MACRO				"MACRO"
FOREIGN				"FOREIGN"
ORIGIN				"ORIGIN"
SHAPE				"SHAPE"
PORT				"PORT"
PATH				"PATH"
LIBRARY				"LIBRARY"

OHMS "OHMS"
MILLIWATTS "MILLIWATTS"
CURRENT "CURRENT"
MILLIAMPS "MILLIAMPS"
VOLTAGE "VOLTAGE"
VOLTS "VOLTS"
TIME "TIME"
NANOSECONDS "NANOSECONDS"
POWER "POWER"
FREQUENCY "FREQUENCY"
MEGAHERTZ "MEGAHERTZ"

%%

{SEMICOLON}.*				{}
{COMMENT}.*					{}
{VERSION}+					{ return lef::LEFParser::token::VERSION; }
{NAMESCASESENSITIVE}+		{ return lef::LEFParser::token::NAMESCASESENSITIVE; }
{BUSBITCHARS}+				{ return lef::LEFParser::token::BUSBITCHARS; }
{DIVIDERCHAR}+				{ return lef::LEFParser::token::DIVIDERCHAR; }
{UNITS}+					{ return lef::LEFParser::token::UNITS; }
{END}+						{ return lef::LEFParser::token::END; }
{DATABASE}+					{ return lef::LEFParser::token::DATABASE; }
{MICRONS}+					{ return lef::LEFParser::token::MICRONS; }
{USEMINSPACING}+			{ return lef::LEFParser::token::USEMINSPACING; }
{OBS}+						{ return lef::LEFParser::token::OBS; }
{PIN}+						{ return lef::LEFParser::token::PIN; }
{CLEARANCEMEASURE}+			{ return lef::LEFParser::token::CLEARANCEMEASURE; }
{MANUFACTURINGGRID}+		{ return lef::LEFParser::token::MANUFACTURINGGRID; }
{LAYER}+					{ return lef::LEFParser::token::LAYER; }
{TYPE}+						{ return lef::LEFParser::token::TYPE; }
{SPACING}+					{ return lef::LEFParser::token::SPACING; }
{DIRECTION}+				{ return lef::LEFParser::token::DIRECTION; }
{PITCH}+					{ return lef::LEFParser::token::PITCH; }
{OFFSET}+					{ return lef::LEFParser::token::OFFSET; }
{PATH}+						{ return lef::LEFParser::token::PATH; }
{WIDTH}+					{ return lef::LEFParser::token::WIDTH; }
{RESISTANCE}+				{ return lef::LEFParser::token::RESISTANCE; }
{EDGECAPACITANCE}+			{ return lef::LEFParser::token::EDGECAPACITANCE; }
{CAPACITANCE}+				{ return lef::LEFParser::token::CAPACITANCE; }
{VIA}+						{ return lef::LEFParser::token::VIA; }
{RECT}+						{ return lef::LEFParser::token::RECT; }
{VIARULE}+					{ return lef::LEFParser::token::VIARULE; }
{TO}+						{ return lef::LEFParser::token::TO; }
{BY}+						{ return lef::LEFParser::token::BY; }
{OVERHANG}+					{ return lef::LEFParser::token::OVERHANG; }
{METALOVERHANG}+			{ return lef::LEFParser::token::METALOVERHANG; }
{SITE}+						{ return lef::LEFParser::token::SITE; }
{SYMMETRY}+					{ return lef::LEFParser::token::SYMMETRY; }
{CLASS}+					{ return lef::LEFParser::token::CLASS; }
{SIZE}+						{ return lef::LEFParser::token::SIZE; }
{MACRO}+					{ return lef::LEFParser::token::MACRO; }
{FOREIGN}+					{ return lef::LEFParser::token::FOREIGN; }
{ORIGIN}+					{ return lef::LEFParser::token::ORIGIN; }
{USE}+						{ return lef::LEFParser::token::USE; }
{SHAPE}+					{ return lef::LEFParser::token::SHAPE; }
{PORT}+						{ return lef::LEFParser::token::PORT; }
{LIBRARY}+					{ return lef::LEFParser::token::LIBRARY; }

{AREA}+ 		{return lef::LEFParser::token::AREA; }
{PICOFARADS}+ 		{return lef::LEFParser::token::PICOFARADS; }
{OHMS}+				{return lef::LEFParser::token::OHMS; }
{MILLIWATTS}+				{return lef::LEFParser::token::MILLIWATTS; }
{CURRENT}+				{return lef::LEFParser::token::CURRENT; }
{MILLIAMPS}+				{return lef::LEFParser::token::MILLIAMPS; }
{VOLTAGE}+				{return lef::LEFParser::token::VOLTAGE; }
{VOLTS}+				{return lef::LEFParser::token::VOLTS; }
{TIME}		{return lef::LEFParser::token::TIME; }
{NANOSECONDS}		{return lef::LEFParser::token::NANOSECONDS; }
{POWER}		{return lef::LEFParser::token::POWER; }
{FREQUENCY}		{return lef::LEFParser::token::FREQUENCY; }
{MEGAHERTZ}		{return lef::LEFParser::token::MEGAHERTZ; }

{INTEGER}* {
	leflval->v_int = atoi(yytext);
	return lef::LEFParser::token::INTEGER;
}

{DOUBLE}* {
	leflval->v_double = atof(yytext);
	return lef::LEFParser::token::DOUBLE;
}

{STRING}* {
	leflval->v_str = new std::string(yytext, yyleng);
	return lef::LEFParser::token::STRING;
}

[ \n\t\r]+ {}
