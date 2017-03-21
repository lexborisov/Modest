0.0.6
===========
Now Modest engine split by modules:

* MyCORE — base module, it is used by all other modules
* MyHTML — HTML parser by [specification](https://html.spec.whatwg.org/multipage/)
* MyCSS —  CSS parserand modules by [specification](https://drafts.csswg.org/)
* MyENCODING — work with character encodings, detecting encoding, convert encodings by [specification](https://encoding.spec.whatwg.org/)
* MyFONT — work with font, metrics, calculating size and more by [specification](https://www.microsoft.com/en-us/Typography/SpecificationsOverview.aspx)
* MyURL — URL parser by [specification](https://url.spec.whatwg.org/)
* MyUNICODE — normalization, change character register and more (in dev)
* MyPORT — system depended code: threads (if build with threads, default), work with memory, io, timers
* Modest — renderer

Each of the modules can build without other modules if he not dependent at it. It is good for those need only URL parse and not need other modules.
MyHTML split to MyHTML and MyCORE. MyCORE is a base module which include shared functions for all others modules.

* Removed all io print functions to file: ```myhtml_tree_print_by_node```, ```myhtml_tree_print_node_children```, ```myhtml_tree_print_node```; Use serializations instead of their
* If you use encoding enum, like ```MyHTML_ENCODING_UTF8```, now it ```MyENCODING_UTF_8```, i.e ```MyHTML_ENCODING_* => MyENCODING_*```
* Functions migrated to MyCORE from MyHTML: ```myhtml_incoming_buffer_*``` => ```mycore_incoming_buffer_*```, ```myhtml_string*``` => ```mycore_string*```, ```myhtml_utils*``` => ```mycore_utils*```
* Fully refactoring build system with GNU Make (Makefile), now it expects generally accepted parameters and rules, like ```test```, ```install```, ```clean```, ```library``` and other
* Tested create a DLL library for Windows OS
* Support [create ports](https://github.com/lexborisov/Modest/wiki/Add-new-port) for different OS or for simple change work with memory, io, threads (if build with threads, default)
* Support [add self modules](https://github.com/lexborisov/Modest/wiki/Add-new-module) for build library
* Now all return statuses, like a ```myhtml_status_t```, ```mycss_status_t``` changed to global mystatus_t (unsigned int)

0.0.5
===========
* Small fixes
* Added URL parser by specification https://url.spec.whatwg.org/

0.0.4
===========
February 14, 2017

* API breaking changes!!! See [api_breaking_changes](https://github.com/lexborisov/modest/blob/master/api_breaking_changes.md)
* See [MyHTML CHANGELOG](https://github.com/lexborisov/myhtml/blob/master/CHANGELOG.md) for version 3.0.0

0.0.1
===========
August 29, 2016

* First commit
