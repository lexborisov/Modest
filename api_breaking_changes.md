0.0.5 => 0.0.6
===========
* MyHTML split to MyHTML and MyCORE
* Removed all io print functions to file: ```myhtml_tree_print_by_node```, ```myhtml_tree_print_node_children```, ```myhtml_tree_print_node```; Use serializations instead of their
* If you use encoding enum, like ```MyHTML_ENCODING_UTF8```, now it ```MyENCODING_UTF_8```, i.e ```MyHTML_ENCODING_* => MyENCODING_*```
* Functions migrated to MyCORE from MyHTML: ```myhtml_incoming_buffer_*``` => ```mycore_incoming_buffer_*```, ```myhtml_string*``` => ```mycore_string*```, ```myhtml_utils*``` => ```mycore_utils*```

0.0.1 => 0.0.4
===========
Removed all depending on the Tree. Now you can get a tree of nodes ```myhtml_node_tree```
Please, see [myhtml api_breaking_changes file](https://github.com/lexborisov/myhtml/blob/master/api_breaking_changes.md) 

* From: ```modest_finder_t * modest_finder_by_stylesheet(myhtml_tree_t* myhtml_tree, mycss_stylesheet_t *stylesheet, myhtml_collection_t** collection, myhtml_tree_node_t* base_node, mycss_selectors_list_t* selector_list);```
* To: ``modest_finder_t * modest_finder_by_stylesheet(mycss_stylesheet_t *stylesheet, myhtml_collection_t** collection, myhtml_tree_node_t* base_node);```

* From: ```modest_status_t modest_finder_by_selectors_list(modest_finder_t* finder, myhtml_tree_t* myhtml_tree, myhtml_tree_node_t* scope_node, mycss_selectors_list_t* selector_list, myhtml_collection_t** collection);```
* To: ``modest_status_t modest_finder_by_selectors_list(modest_finder_t* finder, myhtml_tree_node_t* scope_node, mycss_selectors_list_t* selector_list, myhtml_collection_t** collection);```

* From: ```modest_status_t modest_finder_thread_process(modest_t* modest, modest_finder_thread_t* finder_thread, myhtml_tree_t* myhtml_tree, myhtml_tree_node_t* scope_node, mycss_selectors_list_t* selector_list);```
* To: ``modest_status_t modest_finder_thread_process(modest_t* modest, modest_finder_thread_t* finder_thread, myhtml_tree_node_t* scope_node, mycss_selectors_list_t* selector_list);```
