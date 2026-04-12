$(info auto_init_script)

GRAPHVIZ_PLAIN = $(BUILD_DIR)/$(TARGET).plain
$(info GRAPHVIZ_PLAIN=$(GRAPHVIZ_PLAIN))
$(info CC_DOT=$(CC_DOT))

ADJACENCY_LIST = $(BUILD_DIR)/$(TARGET).adjlist
$(info ADJACENCY_LIST=$(ADJACENCY_LIST))

INIT_ORDER_FILE = $(BUILD_DIR)/$(TARGET).init
$(info INIT_ORDER_FILE=$(INIT_ORDER_FILE))

$(GRAPHVIZ_PLAIN): preproc_graphviz
	$(info ComposeGraphVizPlainComment...)
	$(CC_DOT) -Tplain $(SOURCES_DOT_RES) > $@

$(ADJACENCY_LIST):$(GRAPHVIZ_PLAIN)
	$(info AdjacencyList...)
	gawk '/^edge / { print $$3 " " $$2 }' $< > $@
	$(info SortAdjacencyList...)
	sort -u $(ADJACENCY_LIST) -o $(ADJACENCY_LIST)
	
$(INIT_ORDER_FILE):$(ADJACENCY_LIST)
	$(info TopologicalSorting...)
	tsort $(ADJACENCY_LIST) | tac > $@


.PHONY: auto_init
auto_init: preproc_graphviz $(ARTIFACTS) $(INIT_ORDER_FILE)
	$(info RunAutoInit...)

