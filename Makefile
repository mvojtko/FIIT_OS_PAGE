.DEFAULT_GOAL := all
ROOT_DIR = .
OUT_DIR = $(ROOT_DIR)/build
SRC_DIR = $(ROOT_DIR)/src

RM = /usr/bin/rm -f
MAKE = /usr/bin/make

$(OUT_DIR):
	@echo "Creating   OUT_DIR $(OUT_DIR)"
	@/usr/bin/mkdir -p $(OUT_DIR)
	@echo ""

.PHONY: all
all: $(OUT_DIR)
	@echo "Producing to $(OUT_DIR)"
	@echo ""
	@echo "SUCCESS"

.PHONY: clean
clean:
	@echo "Deleting   OUT_DIR $(OUT_DIR)"
	@$(RM) -r $(OUT_DIR)
	@echo ""
	@echo "SUCCESS"
