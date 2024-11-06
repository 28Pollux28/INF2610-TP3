HANDIN_NAME = handin
ARCHIVE = $(HANDIN_NAME).tar.gz

handin:
	@echo "Collecting all .c files..."
	@find . -name "*.c" | tar -czf $(ARCHIVE) -T -
	@echo "$(ARCHIVE) created with all .c files from current and subdirectories."

clean:
	rm -f $(ARCHIVE)
	@echo "Cleaned up $(ARCHIVE)."