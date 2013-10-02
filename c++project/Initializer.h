// Initializer.h
// Parses command line arguments
//
// Copyright (C) 2013 Mara Kim
//
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see http://www.gnu.org/licenses/.


#ifndef INITIALIZER_H_
#define INITIALIZER_H_

#include <argp.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include "Info.h"

extern "C" {
    int Initializer_argp_funcall(int key, char* arg, struct argp_state *state);
}

/** Processes program arguments
 *  and generates usage, help, and version documentation
 */
class Initializer {
public:
    typedef argp_state state; /**< GNU Argp state struct.
                                   See <http://www.gnu.org/software/libc/manual/html_node/Argp-Parsing-State.html> */
    typedef std::function<int (char*,state*)> optFunc; /**< std::function object corresponding to functions with signature
                                                        *   'int (char*, Initializer::state*)' */

    /** Special events during argument parsing
     *  corresponding to GNU Argp special keys.
     *  See <http://www.gnu.org/software/libc/manual/html_node/Argp-Special-Keys.html>
     *  for a description of Argp special keys.
     */
    enum event_t { ARG = ARGP_KEY_ARG, /**< Generated for each non-option command line argument.
                                        *   Equivalent to ARGP_KEY_ARG. */
                   ARGS = ARGP_KEY_ARGS, /**< Generated when the last command line argument was not handled.
                                          *   Useful for consuming all remaining arguments.
                                          *   Equivalent to ARGP_KEY_ARGS. */
                   END = ARGP_KEY_END, /**< Generated when there are no more command line arguments.
                                        *   Equivalent to ARGP_KEY_END. */
                   NO_ARGS = ARGP_KEY_NO_ARGS, /**< Generated when there are no non-option command line arguments.
                                                *   Equivalent to ARGP_KEY_NO_ARGS. */
                   INIT = ARGP_KEY_INIT, /**< Generated before any parsing is done.
                                          *   Equivalent to ARGP_KEY_INIT. */
                   SUCCESS = ARGP_KEY_SUCCESS, /**< Generated when parsing completes successfully.
                                                *   Equivalent to ARGP_KEY_SUCCESS. */
                   ERROR = ARGP_KEY_ERROR, /**< Generated when an error occurs during parsing.
                                            *   Equivalent to ARGP_KEY_ERROR. */
                   FINI = ARGP_KEY_FINI /**< Generated after parsing terminates, regardless of success.
                                         *   Equivalent to ARGP_KEY_FINI. */
                 }; 

    /** Return values for option and event processing functions during parsing.
     *  See <http://www.gnu.org/software/libc/manual/html_node/Argp-Parser-Functions.html>
     *  for a description of Argp parser functions.
     */
    enum signal_t { GOOD = 0, /**< Indicates the option or event was handled. Equivalent to 0. */
                    UNKNOWN = ARGP_ERR_UNKNOWN /**< Indicates the option or event was not handled.
                                                *   Equivalent to ARGP_ERR_UNKNOWN. */
                  }; 

    /** Construct an Initializer.
     *  Initializes the private argp _argp struct.
     *  See <http://www.gnu.org/software/libc/manual/html_node/Argp-Parsers.html>
     *  for details on struct argp.
     *  \param argc The argument count
     *  \param argv The argument vector
     *  \param argdoc A string describing usage of non-option arguments to be printed with `--usage`.
     *                See argp::args_doc.
     *  \param progdoc Text to be printed before and after the `--help` documentation, the two sections
     *                 separated by '\\v' (vertical tab). See argp::doc.
     */
    Initializer(int argc, char** argv, const char* argdoc = 0, const char* progdoc = 0);
    virtual ~Initializer();

    /** Define an option flag.
     *  Adds an argp_option struct to the Argp option vector.
     *  See <http://www.gnu.org/software/libc/manual/html_node/Argp-Option-Vectors.html>
     *  for details on struct argp_option.
     *  \param longflag Long name for the option, corresponding to the long option '--longflag'.
     *                  May be zero to indicate that this option only has a shortflag. See argp_option::name.
     *  \param shortflag Integer key for the option. If this is a printable ASCII character, also specifies
     *                   a short option '--shortflag'. See argp_option::key.
     *  \param argument If not null, the name of the argument associated with this option, which is required
     *                  unless arg_optional is false. See argp_option::arg. This argument is given with the
     *                  '--longflag=value' or '--shortflag value' syntax convention.
     *                  See <http://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html>.
     *  \param doc The documentation string for this option for printing in help messages. See argp_option::doc.
     *  \param function The function called when this option is seen during parsing. This should be a function
     *                  with the signature 'int (char* arg, Initializer::state* state)', where arg is the
     *                  value of the argument given with the option (if not null) and state is the parser state.
     *                  The function should return Initializer::GOOD (ie. 0) to indicate success, or some non-zero
     *                  value (such as Initializer::UNKNOWN) if some error occured.
     *                  The function may be passed in as a function pointer, functor, or lambda expression.
     *  \param arg_optional Indicates whether the argument to this option is optional.
     *                      See OPTION_ARG_OPTIONAL at <http://www.gnu.org/software/libc/manual/html_node/Argp-Option-Flags.html>.
     *  \param hidden Indicates whether this option is hidden during `--help` output.
     *                      See OPTION_HIDDEN at <http://www.gnu.org/software/libc/manual/html_node/Argp-Option-Flags.html>.
     */
    void option(const char* longflag, const int shortflag, const char* argument, const char* doc, optFunc function,
                const bool arg_optional = false, const bool hidden = false);

    /** Define an option flag with additional aliases.
     *  Adds a number of argp_option structs to the Argp option vector.
     *  See <http://www.gnu.org/software/libc/manual/html_node/Argp-Option-Vectors.html>
     *  for details on struct argp_option.
     *  argp_option structs after the first are aliased to be combined with the first option.
     *  See OPTION_ALIAS at <http://www.gnu.org/software/libc/manual/html_node/Argp-Option-Flags.html>.
     *  \param longflags Long names for the option, where each corresponds to the long option '--longflag'.
     *                   May be empty to indicate that there are no long names. See argp_option::name.
     *  \param shortflag Integer keys for the option. For those that are printable ASCII characters, also specifies
     *                   a short option '--shortflag'. Should not be empty. See argp_option::key.
     *  \param argument If not null, the name of the argument associated with this option, which is required
     *                  unless arg_optional is false. See argp_option::arg. This argument is given with the
     *                  '--longflag=value' or '--shortflag value' syntax convention.
     *                  See <http://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html>.
     *  \param doc The documentation string for this option for printing in help messages. See argp_option::doc.
     *  \param function The function called when this option is seen during parsing. This should be a function
     *                  with the signature 'int (char* arg, Initializer::state* state)', where arg is the
     *                  value of the argument given with the option (if not null) and state is the parser state.
     *                  The function should return Initializer::GOOD (ie. 0) to indicate success, or some non-zero
     *                  value (such as Initializer::UNKNOWN) if some error occured.
     *                  The function may be passed in as a function pointer, functor, or lambda expression.
     *  \param arg_optional Indicates whether the argument to this option is optional.
     *                      See OPTION_ARG_OPTIONAL at <http://www.gnu.org/software/libc/manual/html_node/Argp-Option-Flags.html>.
     *  \param hidden Indicates whether this option is hidden during `--help` output.
     *                      See OPTION_HIDDEN at <http://www.gnu.org/software/libc/manual/html_node/Argp-Option-Flags.html>.
     */
    void option(const std::vector<const char*>& longflags, const std::vector<int>& shortflags,
                const char* argument, const char* doc, optFunc function,
                const bool arg_optional = false, const bool hidden = false);

    /** Define a function to handle a parser event.
     *  See Initializer::event_t for a description of parser events.
     *  \param event The event handled by the function.
     *  \param function The function called when this option is seen during parsing. This should be a function
     *                  with the signature 'int (char* arg, Initializer::state* state)', where arg is the
     *                  value of the argument given with the option (if not null) and state is the parser state.
     *                  The function should return Initializer::GOOD (ie. 0) to indicate success, or some non-zero
     *                  value (such as Initializer::UNKNOWN) if some error occured.
     *                  The function may be passed in as a function pointer, functor, or lambda expression.
     */
    void event(event_t event, optFunc function);

    /** Parse the arguments.
     *  \return 0 if successful, otherwise an error code.
     */
    error_t parse();

    /** C style function hook for GNU Argp.
     *  The value of argp::parser during parsing.
     *  See <http://www.gnu.org/software/libc/manual/html_node/Argp-Parser-Functions.html>.
     *  \param key The key of the current option or event.
     *  \param arg Either null, or the value of the argument to the option,
     *             or the value of a non-option argument.
     *  \param state The state of the parser.
     *               See <http://www.gnu.org/software/libc/manual/html_node/Argp-Parsing-State.html>.
     */
    friend int Initializer_argp_funcall(int key, char* arg, state* state);

    /** Print usage and exit.
     *  Wraps a call to argp_usage(argp_state*).
     *  See <http://www.gnu.org/software/libc/manual/html_node/Argp-Helper-Functions.html>
     *  \param state The parser state
     */
    static void print_usage(state* state);
private:
    // hook to key handlers
    int argp_funcall(int key, char* arg, state* state);

    int _argc;
    char** _argv;
    std::vector<argp_option> _arg_opts;
    std::map<int, optFunc> _arg_funcs;
    argp _argp;
};

#endif /* INITIALIZER_H_ */
