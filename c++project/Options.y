/*
OPTIONSparser.y
Bisonc++ input file
Mara Kim
*/

%class-name OptionsParser
%parsefun-source OptionsParser.cc
%scanner OptionsScanner.h
%baseclass-preinclude "Options.types.h"

%polymorphic string: string_type;
             svector: Mode::svector_type;
             svpair: Mode::svpair_type;
             tmap: Mode::type_map;

%token NEWLINE
%token <string> VARIABLE STRING
%type <string> variable string 
%type <svector> stringlist
%type <svpair> expr
%type <tmap> option_details

%%
/* rules */

input:
    option_details
      { _options->_new($1); }
;
option_details:
    /* empty */
      { $$; }
  | option_details expr
      { ($1)[($2).first] = ($2).second;
        $$ = $1; }
  | option_details NEWLINE
  | option_details error NEWLINE
;
expr:
    variable stringlist NEWLINE
      { ($$).first = $1;
        ($$).second = $2; }
;
stringlist:
    /* empty */
      { $$; }
  | stringlist string
      { ($1).push_back($2);
        $$ = $1; }
;
variable:
    VARIABLE
      { $$ = d_scanner.matched(); }
;
string:
    STRING
      { $$ = d_scanner.matched(); }
;
