%define api.prefix {lef}
%error-verbose
%language "c++"
%glr-parser
%debug
%token-table
%define "parser_class_name" {LEFParser}

%code requires {
	namespace lef {
		class LEFData;
	}
}

%param {class lef::LEFData *lefdata}

%{
#include <iostream>
#include <string>
#include "lefdata.h"
#include "lefscanner.h"

#define leflex (lefdata->getLexer())->leflex
#define leflineno (int)(lefdata->getLexer())->lineno()
#define leftext (lefdata->getLexer())->YYText()

%}

%union {
	int v_int;
	std::string* v_str;
	double v_double;
}

%token <v_int> INTEGER
%token <v_str> STRING
%token <v_double> DOUBLE

%token VERSION
%token NAMESCASESENSITIVE
%token BUSBITCHARS
%token DIVIDERCHAR
%token UNITS
%token END
%token DATABASE
%token MICRONS
%token USEMINSPACING
%token OBS
%token PIN
%token CLEARANCEMEASURE
%token MANUFACTURINGGRID
%token LAYER
%token TYPE
%token SPACING
%token DIRECTION
%token PITCH
%token OFFSET
%token WIDTH
%token RESISTANCE
%token EDGECAPACITANCE
%token CAPACITANCE
%token VIA
%token RECT
%token VIARULE
%token TO
%token BY
%token OVERHANG
%token METALOVERHANG
%token SITE
%token SYMMETRY
%token CLASS
%token SIZE
%token MACRO
%token FOREIGN
%token ORIGIN
%token USE
%token SHAPE
%token PORT
%token PATH
%token LIBRARY

%token AREA
%token PICOFARADS
%token OHMS
%token MILLIWATTS
%token CURRENT
%token MILLIAMPS
%token VOLTAGE
%token VOLTS
%token TIME
%token NANOSECONDS
%token POWER
%token FREQUENCY
%token MEGAHERTZ

%start lef_file

%%
lef_file:
	  lef_file_alternative1
	| lef_file_alternative2
;

lef_file_alternative1: options layers vias viarules sites macros end_library;
lef_file_alternative2: options macros end_library;

end_library: END LIBRARY;

options:
	  option
	| option options;

option:
	  version
	| cases
	| bitchars
	| dividechar
	| units
	| useminamespacing
	| clearensmeasure
	| manufacturinggrid
	;

version: VERSION DOUBLE;
cases: NAMESCASESENSITIVE STRING;
bitchars: BUSBITCHARS STRING
{
	lefdata->setSubBitChar(*$2);
};
dividechar: DIVIDERCHAR STRING
{
	lefdata->setDivideChar(*$2);
};
units: UNITS database_lists END UNITS;

database_lists:
	  database_list
	| database_lists database_list
	;

database_list:
DATABASE MICRONS INTEGER { lefdata->units.databaseLEFconvertFactor = $3; }
| CAPACITANCE PICOFARADS INTEGER {lefdata->units.capacitanceConvertFactor = $3;}
| TIME NANOSECONDS INTEGER {lefdata->units.timeConvertFactor = $3;}
| RESISTANCE OHMS INTEGER {lefdata->units.resistanceConvertFactor = $3;}
| POWER MILLIWATTS INTEGER {lefdata->units.powerConvertFactor = $3;}
| CURRENT MILLIAMPS INTEGER {lefdata->units.currentConvertFactor = $3;}
| VOLTAGE VOLTS INTEGER {lefdata->units.voltageConvertFactor = $3;}
| FREQUENCY MEGAHERTZ INTEGER {lefdata->units.frequencyConvertFactor = $3;}
;
useminamespacing: USEMINSPACING OBS STRING | USEMINSPACING PIN STRING;
clearensmeasure: CLEARANCEMEASURE STRING;
manufacturinggrid: MANUFACTURINGGRID DOUBLE;

layers:
	  layer
	| layers layer
;

layer: layer_name layer_options END STRING;
layer_name:
LAYER STRING
{
	lefdata->addLayer(*$2);
}

layer_options: layer_option | layer_options layer_option;
layer_option:
  TYPE STRING {	lefdata->setLayerType(*$2);}
| SPACING DOUBLE;
| DIRECTION STRING
| AREA DOUBLE {	lefdata->setLayerArea($2);}
| PITCH DOUBLE DOUBLE {	lefdata->setLayerPitch($2,$3);}
| PITCH DOUBLE {	lefdata->setLayerPitch($2,$2);}
| OFFSET DOUBLE
| OFFSET INTEGER
| WIDTH DOUBLE
| WIDTH INTEGER
| RESISTANCE STRING DOUBLE
| RESISTANCE STRING INTEGER
| CAPACITANCE STRING DOUBLE
| CAPACITANCE STRING INTEGER
| EDGECAPACITANCE DOUBLE
;

vias:
	  via
	| vias via
;

via: via_name via_layers END STRING;

via_name:
VIA STRING STRING
{
	lefdata->addViaName(*$2);
};

via_layers: via_layer | via_layers via_layer;
via_layer: via_layer_name via_rects;

via_layer_name:
LAYER STRING
{
	lefdata->addViaLayer(*$2);
};

via_rects: via_rect | via_rects via_rect;
via_rect:
RECT DOUBLE DOUBLE DOUBLE DOUBLE
{
	lefdata->addViaLayerRectangle($2,$3,$4,$5);
};

viarules:
	  viarule
	| viarules viarule
;

viarule: viarule_name viarule_layers END STRING;
viarule_name: VIARULE STRING STRING;
viarule_layers: viarule_layer | viarule_layers viarule_layer;
viarule_layer: viarule_layer_name viarule_layer_options;
viarule_layer_name: LAYER STRING;
viarule_layer_options: viarule_layer_option | viarule_layer_options viarule_layer_option;

viarule_layer_option:
	  viarule_layer_option_direction
	| viarule_layer_option_width
	| viarule_layer_option_overhang
	| viarule_layer_option_metaloverhang
	| viarule_layer_option_rect
	| viarule_layer_option_spacing
	;

viarule_layer_option_direction: DIRECTION STRING;
viarule_layer_option_width: WIDTH DOUBLE TO INTEGER | WIDTH DOUBLE TO DOUBLE;
viarule_layer_option_overhang: OVERHANG INTEGER | OVERHANG DOUBLE;
viarule_layer_option_metaloverhang: METALOVERHANG INTEGER | METALOVERHANG DOUBLE;
viarule_layer_option_rect: RECT DOUBLE DOUBLE DOUBLE DOUBLE;
viarule_layer_option_spacing: SPACING INTEGER BY INTEGER | SPACING INTEGER BY DOUBLE | SPACING DOUBLE BY INTEGER | SPACING DOUBLE BY DOUBLE;

sites:
	  site
	| sites site
;

site: site_name site_options END STRING;
site_name: SITE STRING;
site_options: site_option | site_options site_option;
site_option:
	  site_class
	| site_symmetry
	| site_size
	;

site_class: CLASS STRING;
site_symmetry: SYMMETRY STRING STRING | SYMMETRY STRING;
site_size: SIZE DOUBLE BY DOUBLE;

macros:
	  macro
	| macro macros
	;

macro: macro_name macro_options END STRING;

macro_name: MACRO STRING
	{
		lefdata->addMacroName(*$2);
	};

macro_options:
	  macro_option
	| macro_options macro_option
	;

macro_option:
	  macro_class
	| macro_foreign
	| macro_origin
	| macro_size
	| macro_symmetrie
	| macro_site
	| macro_pin
	| macro_obs
	;

macro_class:
  CLASS STRING
  {
	  lefdata->setMacroClass(*$2);
  }
| CLASS STRING STRING
  {
	  lefdata->setMacroClass(*$2+" "+*$3);
  }
macro_foreign: FOREIGN STRING DOUBLE DOUBLE;
macro_site:
SITE STRING
{
	lefdata->setMacroSite(*$2);
};
macro_origin: ORIGIN DOUBLE DOUBLE;
macro_size:
SIZE DOUBLE BY DOUBLE
{
	lefdata->setMacroSize($2,$4);
};

macro_symmetrie: SYMMETRY STRING | SYMMETRY STRING STRING | SYMMETRY STRING STRING STRING;

macro_pin: macro_pin_options END STRING;

macro_pin_options:
	  macro_pin_option
	| macro_pin_option macro_pin_options
	;

macro_pin_option:
	  macro_pin_name
	| macro_pin_use
	| macro_pin_direction
	| macro_pin_shape
	| macro_pin_port
	;

macro_pin_name:
PIN STRING
{
	lefdata->addMacroPinName(*$2);
};

macro_pin_use: USE STRING;
macro_pin_direction:
DIRECTION STRING
{
	lefdata->setMacroPinDirection(*$2);
}
|
DIRECTION STRING STRING;
macro_pin_shape: SHAPE STRING;
macro_pin_port: PORT macro_pin_port_infos END;
macro_pin_port_infos:
	  macro_pin_port_info
	| macro_pin_port_info macro_pin_port_infos
	;

macro_pin_port_info:
	  macro_pin_port_layer
	| macro_pin_port_rect
	| macro_pin_port_class
	| WIDTH DOUBLE
	| WIDTH INTEGER
	| PATH DOUBLE DOUBLE DOUBLE DOUBLE
;

macro_pin_port_layer:
LAYER STRING
{
	lefdata->addMacroPinPortLayer(*$2);
};

macro_pin_port_rect:
RECT DOUBLE DOUBLE DOUBLE DOUBLE
{
	lefdata->addMacroPinPortRectangle($2,$3,$4,$5);
};

macro_pin_port_class: CLASS STRING;

macro_obs: OBS macro_obs_infos END;
macro_obs_infos:
	  macro_obs_info
	| macro_obs_info macro_obs_infos
	;
macro_obs_info:
	  macro_obs_layer
	| macro_obs_rect
	;

macro_obs_layer:
LAYER STRING
{
	lefdata->addMacroPinObstructionLayer(*$2);
};

macro_obs_rect:
RECT DOUBLE DOUBLE DOUBLE DOUBLE
{
	lefdata->addMacroPinObstructionRectangle($2,$3,$4,$5);
};

%%

void lef::LEFParser::error(const std::string &s) {
	std::cout << "Error message: " << s << " on line " << leflineno << ", yytext: " << leftext <<std::endl;
}
