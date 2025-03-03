# rules
all:
	$(MAKE) test -C ./ft_printf

test: all

.PHONY: all test
