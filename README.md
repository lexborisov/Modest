# Modest — a pure C HTML renderer

[![Build Status](https://travis-ci.org/lexborisov/Modest.svg?branch=master)](https://travis-ci.org/lexborisov/Modest)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/11105/badge.svg)](https://scan.coverity.com/projects/lexborisov-modest)
[![Donate](https://img.shields.io/badge/Donate-PayPal-blue.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=L59E49K2NVUHE)

Modest is a fast HTML renderer implemented as a pure C99 library with no outside dependencies.

* Mailing List: [https://groups.google.com/forum/#!forum/modest-engine](https://groups.google.com/forum/#!forum/modest-engine)
* IRC: [#modest-engine on `irc.freenode.net <http://freenode.net>`](http://webchat.freenode.net?channels=%23modest-engine)
* Public [tracker by trello](https://trello.com/b/sdqpT8Ep/modest)

## Now

```text
The current version is 0.0.6 - devel
```

## Features

* MyCORE — base module, it is used by all other modules
* MyHTML — HTML parser by [specification](https://html.spec.whatwg.org/multipage/)
* MyCSS —  CSS parser and modules by [specification](https://drafts.csswg.org/)
* MyENCODING — work with character encodings, detecting encoding, convert encodings by [specification](https://encoding.spec.whatwg.org/)
* MyFONT — work with font, metrics, calculating size and more by [specification](https://www.microsoft.com/en-us/Typography/SpecificationsOverview.aspx)
* MyURL — URL parser by [specification](https://url.spec.whatwg.org/)
* MyPORT — system depended code: threads (if build with threads, default), work with memory, io, timers
* Modest — calculating, compare, renderer

## Introduction

[Introduction](https://lexborisov.github.io/Modest/)

## Dependencies

None

## Installation

See [INSTALL.md](https://github.com/lexborisov/Modest/blob/master/INSTALL.md)

## External Bindings and Wrappers
* [Crystal wrapper](https://github.com/kostya/modest) for CSS Selectors (Modest Finder)

## Examples

See [examples](https://github.com/lexborisov/modest/tree/master/examples) directory

## AUTHOR

Alexander Borisov <lex.borisov@gmail.com>

## COPYRIGHT AND LICENSE

Copyright (C) 2015-2017 Alexander Borisov

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA

See the [LICENSE] file.


[LICENSE]: https://github.com/lexborisov/myhtml/blob/master/LICENSE
