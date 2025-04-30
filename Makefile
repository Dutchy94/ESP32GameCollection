PROJECT_DIR := $(CURDIR)

DIRS := central module common

default: create_dirs create_files

create_dirs:
	@for dir in $(DIRS); do \
		mkdir -p $(PROJECT_DIR)/$$dir; \
	done

create_files:
	@echo "// main.cpp – Platzhalter" > $(PROJECT_DIR)/central/main.cpp
	@echo "// main.cpp – Platzhalter" > $(PROJECT_DIR)/module/main.cpp
	@echo "// protocol.h – Platzhalter" > $(PROJECT_DIR)/common/protocol.h
	@echo "// utils.h – Platzhalter" > $(PROJECT_DIR)/common/utils.h
	@touch $(PROJECT_DIR)/central/README.md
	@touch $(PROJECT_DIR)/module/README.md
	@touch $(PROJECT_DIR)/common/README.md
	@echo "# ESP-NOW Spielsystem" > $(PROJECT_DIR)/README.md
	@touch $(PROJECT_DIR)/.gitignore

clean:
	@rm -rf $(DIRS) README.md .gitignore
