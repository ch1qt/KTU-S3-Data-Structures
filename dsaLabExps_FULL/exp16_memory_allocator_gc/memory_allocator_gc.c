#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TOTAL_MEMORY_SIZE 1000

// Structure for a memory block
struct MemoryBlock {
    int id; // For easier identification
    int start_address;
    int size;
    bool is_free;
    bool is_marked; // For garbage collection
    struct MemoryBlock *prev;
    struct MemoryBlock *next;
};

// Head of the doubly linked list representing the memory heap
struct MemoryBlock *memory_head = NULL;
int next_block_id = 0;

// Function to initialize memory
void initMemory() {
    memory_head = (struct MemoryBlock *)malloc(sizeof(struct MemoryBlock));
    if (memory_head == NULL) {
        fprintf(stderr, "Memory allocation failed for initial block!\n");
        exit(EXIT_FAILURE);
    }
    memory_head->id = next_block_id++;
    memory_head->start_address = 0;
    memory_head->size = TOTAL_MEMORY_SIZE;
    memory_head->is_free = true;
    memory_head->is_marked = false;
    memory_head->prev = NULL;
    memory_head->next = NULL;
}

// Function to print the current memory map
void printMemoryMap() {
    printf("\n--- Memory Map ---\n");
    struct MemoryBlock *current = memory_head;
    while (current != NULL) {
        printf("Block ID: %d, Addr: %d, Size: %d, Status: %s, Marked: %s\n",
               current->id, current->start_address, current->size,
               current->is_free ? "FREE" : "ALLOCATED",
               current->is_marked ? "YES" : "NO");
        current = current->next;
    }
    printf("------------------\n");
}

// Function to allocate memory (First Fit)
struct MemoryBlock* allocate(int requested_size) {
    if (requested_size <= 0) {
        printf("Requested size must be positive.\n");
        return NULL;
    }

    struct MemoryBlock *current = memory_head;
    while (current != NULL) {
        if (current->is_free && current->size >= requested_size) {
            // Found a suitable free block
            if (current->size == requested_size) {
                current->is_free = false;
                printf("Allocated Block ID: %d, Addr: %d, Size: %d\n", current->id, current->start_address, current->size);
                return current;
            } else { // Split the block
                struct MemoryBlock *new_free_block = (struct MemoryBlock *)malloc(sizeof(struct MemoryBlock));
                if (new_free_block == NULL) {
                    fprintf(stderr, "Memory allocation failed for new free block!\n");
                    exit(EXIT_FAILURE);
                }
                new_free_block->id = next_block_id++;
                new_free_block->start_address = current->start_address + requested_size;
                new_free_block->size = current->size - requested_size;
                new_free_block->is_free = true;
                new_free_block->is_marked = false;
                new_free_block->next = current->next;
                new_free_block->prev = current;

                if (current->next != NULL) {
                    current->next->prev = new_free_block;
                }
                current->next = new_free_block;

                current->size = requested_size;
                current->is_free = false;
                printf("Allocated Block ID: %d, Addr: %d, Size: %d (split from larger block)\n", current->id, current->start_address, current->size);
                return current;
            }
        }
        current = current->next;
    }

    printf("Memory allocation failed for size %d. No suitable block found.\n", requested_size);
    return NULL;
}

// Function to deallocate memory
void deallocate(struct MemoryBlock* block_to_free) {
    if (block_to_free == NULL) return;

    block_to_free->is_free = true;
    printf("Deallocated Block ID: %d, Addr: %d, Size: %d\n", block_to_free->id, block_to_free->start_address, block_to_free->size);

    // Coalesce with previous block if free
    if (block_to_free->prev != NULL && block_to_free->prev->is_free) {
        block_to_free->prev->size += block_to_free->size;
        block_to_free->prev->next = block_to_free->next;
        if (block_to_free->next != NULL) {
            block_to_free->next->prev = block_to_free->prev;
        }
        printf("Coalesced Block ID: %d with previous Block ID: %d\n", block_to_free->id, block_to_free->prev->id);
        free(block_to_free);
        block_to_free = block_to_free->prev; // Continue with the merged block
    }

    // Coalesce with next block if free
    if (block_to_free->next != NULL && block_to_free->next->is_free) {
        struct MemoryBlock *next_block = block_to_free->next;
        block_to_free->size += next_block->size;
        block_to_free->next = next_block->next;
        if (next_block->next != NULL) {
            next_block->next->prev = block_to_free;
        }
        printf("Coalesced Block ID: %d with next Block ID: %d\n", block_to_free->id, next_block->id);
        free(next_block);
    }
}

// --- Garbage Collector Functions ---

// Mark phase: Mark reachable blocks
void mark(struct MemoryBlock* block) {
    if (block != NULL && !block->is_marked && !block->is_free) {
        block->is_marked = true;
        // In a real GC, you'd traverse pointers within this block to mark other blocks
        // For this simulation, we only mark the block itself if it's considered 'in use'
    }
}

// Sweep phase: Reclaim unmarked, allocated blocks
void sweep() {
    printf("\n--- Running Garbage Collector (Sweep Phase) ---\n");
    struct MemoryBlock *current = memory_head;
    while (current != NULL) {
        if (!current->is_free && !current->is_marked) {
            // This block is allocated but not marked, so it's garbage
            printf("Reclaiming garbage Block ID: %d, Addr: %d, Size: %d\n", current->id, current->start_address, current->size);
            struct MemoryBlock *block_to_reclaim = current;
            current = current->next; // Move to next before deallocating current
            deallocate(block_to_reclaim);
        } else {
            // Reset mark for next cycle
            current->is_marked = false;
            current = current->next;
        }
    }
    printf("--- Sweep Phase Complete ---\n");
}

int main() {
    initMemory();
    printMemoryMap();

    struct MemoryBlock *ptr1 = allocate(100);
    struct MemoryBlock *ptr2 = allocate(50);
    struct MemoryBlock *ptr3 = allocate(200);
    printMemoryMap();

    deallocate(ptr2);
    printMemoryMap();

    struct MemoryBlock *ptr4 = allocate(75);
    printMemoryMap();

    // Simulate some blocks being 'reachable' (marked)
    // In a real system, these would be determined by root pointers
    if (ptr1) mark(ptr1);
    if (ptr4) mark(ptr4);

    sweep(); // Run GC
    printMemoryMap();

    // Deallocate remaining manually for clean exit
    deallocate(ptr1);
    deallocate(ptr3); // This one was not marked, so it should have been swept by GC
    deallocate(ptr4);
    printMemoryMap();

    // Free the initial memory_head if it's the only block left and free
    if (memory_head != NULL && memory_head->is_free && memory_head->prev == NULL && memory_head->next == NULL) {
        free(memory_head);
        memory_head = NULL;
    }

    return 0;
}
