Welcome to the Thue Reference Manual
====================================

The Thue programming language:  Programming with grammars

    > What is a Thue?

Thue is...uhm...well...

OK, I got it.  Thue is a language based on the concept of the [semi-Thue grammar/process](https://en.wikipedia.org/wiki/Semi-Thue_system), which is named for (and possibly created by; evidence is unclear) the Norwegian mathematician [Axel Thue](https://en.wikipedia.org/wiki/Axel_Thue) (pronounced /TOO-ay/).  It is, in essence, an arbitrary grammar, which can (by its arbitrary nature) be used to define/recognize _Type 0_ languages from [Chomsky's hierarchy](https://en.wikipedia.org/wiki/Chomsky_hierarchy).  Because the grammar can be used to define a language of such complexity, the process, itself, is Turing Complete.

As a result, the Thue language (which, of course, would be much funnier if it rhymed with the Infocom "dark places" creature, but _c'est la vie_, I guess...) is an arbitrary grammar system, not unlike `yacc` or a similar beast, except that there is no way to distinguish between a terminal and a nonterminal symbol--they are completely interchangeable.

    > Write "Thue" with burin.

A Thue program consists of two parts:  The first part is the set of grammar/production rules, where each rule has the form:

        lhs::=rhs

where the _lhs_ is the string to be recognized, and the _rhs_ is the string that is to replace the _lhs_.  Each string (lhs and rhs) can be completely arbitrary, except that the _lhs_ cannot (for rather obvious reasons) include the production symbol (`::=`).  The _rhs_, however, is not restricted in any way.

Terminating the rulebase is a production symbol alone on a line, surrounded by (optional) whitespace.  Following that is the description of the initial state which Thue will work with.  Each line after the rulebase is concatenated to form the initial state.

Once loaded, the Thue program nondeterministically applies the rulebase to the current state.  It continues to do so until no rules apply to the state (pragmatically, this means that no _lhs_ can be found in the state).

    > What is a burin?

Don't worry about it.  It's an [Infocom](https://en.wikipedia.org/wiki/Infocom) joke.

Actually, let's go with it.  A [burin](https://en.wikipedia.org/wiki/Burin) is tool to inscribe mystical symbols into an object.  Thue has one.

    > Examine burin.

Added to this simple system are two strings which are used to permit Thue to communicate with the outside world.

The first of these is the input symbol (`:::`).  The input symbol is actually the _lhs_ of an implicit rule of which the user (or system's "input stream") is a component.  The input symbol, therefore, is replaced by a line of text received from the "input stream."

As a counterpart of input, the output symbol (`~`) is supplied.  Like the input symbol, the output symbol triggers an implicit rule which, in this case, encompasses the "output stream."  The specific effect is that all text to the right of the output symbol in the rhs of a production is sent to the output stream.

Note that either (or both) of these implicit rules may be overridden by providing explicit rules that perform some other task.

    > Examine Thue.

The implementation of Thue, itself, is rather uninteresting, except for
three command-line switches:

 - __`d`__:  Activates "Debug Mode," which prints the state immediately after any rule is applied.
 - __`l`__:  Activates "Left Mode," which requires Thue to apply rules deterministically in a left-to-right fashion.
 - __`r`__:  Activates "Right Mode," which is identical to "Left Mode," except that rule application occurs right-to-left.

The command-line switches must appear after the Thue filename (i.e., `thue examples/hello.t d`), and the last incidence of 'l' or 'r' overrides all others.

    > Look under Thue.

Sample programs included are:

 - `dec.t`:  Decrements a binary number
 - `hello.t`:  Hello, World!
 - `inc.t`:  Increments a binary number
 - `incany.t`:  Increments a binary number input by the user
 - `test.t`:  A simple example to highlight nondeterminism

Other bits of code are available around the Internet, of course.

    > Amusing.

Apologies to Axel Thue for mangling the pronunciation of his name for a cheap joke.  Apologies to whatever is left of Infocom for (unknowingly) supplying the format of the cheap joke.

Thue(__footnote 1__) is described in some detail [on Wikipedia](https://en.wikipedia.org/wiki/Thue_%28programming_language%29)(__footnote 2__), as well.

    > Footnote 1.

The Thue interpreter was written a long time ago and has not been maintained to any significant extent.  It may do strange things and will certainly be formatted oddly.  I had peculiar ideas of how C code should look, back then.

Also, the original release (which can still be found across the Internet) used a notification-only public license.  For this release forward, I have changed this to the GPLv3.  In fifteen years, nobody notified me that they were using it, so I don't think I'm letting a massive audience down and I would rather any forks or changes be made available to the world, at this point.

    > Footnote 2.

Thue is arguably important solely(__footnote 3__) because it's what apparently keeps [my Wikipedia page](https://en.wikipedia.org/wiki/John_Colagioia) from deletion.

    > Footnote 3.

I couldn't pass up the opportunity for a nested footnote.  Sorry.

    > Exit.

