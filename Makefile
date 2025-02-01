# rules
all:
	$(MAKE) test -C ./printf

test: all
	
.PHONY: all test