#####

DIRS = $(wildcard ./*)

all:
	@for dir in $(DIRS);do 	\
		if test -d $$dir; then \
			echo "$$dir: $(MAKE) $@"; \
			if (cd $$dir; $(MAKE) $@) ; then \
				true; \
			else \
				exit 1; \
			fi; \
		fi \
	done

clean:
	@for dir in $(DIRS);do 	\
		if test -d $$dir; then \
			echo "$$dir: $(MAKE) $@"; \
			if (cd $$dir; $(MAKE) $@) ; then \
				true; 	\
			else \
				echo "$$dir: make failed" \
				exit 1; \
			fi; \
		fi \
	done
