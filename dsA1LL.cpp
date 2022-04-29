typedef struct songInfo {
	char* artist;
	char* title;
	char* rating;
	struct songInfo* prev;
	struct songInfo* next;
} songInfo;
