/*
Options.l
Flexc++ input file
Mara Kim
*/

%class-name = OptionsScanner
%lex-source = "OptionsScanner.cc"


LINECOMMENT_S           "//"
MULTILINECOMMENT_S      "/*"
MULTILINECOMMENT_E      "*/"
STRING_S                \"
INCLUDE_S               "#include "
VARNAME			[A-Z_]+
SEPARATOR               [;,]

%x ASSIGN MULTILINECOMMENT STRING INCLUDE

/* rules */
%%

{VARNAME}               begin(StartCondition__::ASSIGN); return OptionsParser::VARIABLE;

{INCLUDE_S}             begin(StartCondition__::INCLUDE);
<INCLUDE>{
    .+                      begin(StartCondition__::INITIAL); pushStream(matched());
}

{LINECOMMENT_S}.*

{MULTILINECOMMENT_S}    begin(StartCondition__::MULTILINECOMMENT);
<MULTILINECOMMENT>{
    {MULTILINECOMMENT_E}    begin(StartCondition__::INITIAL);
    .|\n
}

<ASSIGN>{
    {STRING_S}              begin(StartCondition__::STRING);
    [^[:space:]"]+           return OptionsParser::STRING;
    \n                      begin(StartCondition__::INITIAL); return OptionsParser::NEWLINE;
    [[:space:]]             /* empty */
}

<STRING>{
    {STRING_S}              setMatched(matched().substr(0,length()-1)); begin(StartCondition__::ASSIGN); return OptionsParser::STRING;
    "\\\""                  more();
    [^\"]                   more();
}

\n                      return OptionsParser::NEWLINE;
[[:space:]]             /* empty */
.                       /* empty */
