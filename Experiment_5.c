#include <stdio.h>
#include <stdlib.h>

int main() {
   int page_size, file_count, i;
   int *file_sizes;
   int total_file_size = 0, total_page_size = 0;
   int external_fragmentation = 0, internal_fragmentation = 0;

   printf("Enter page size: ");
   scanf("%d", &page_size);

   printf("Enter number of files: ");
   scanf("%d", &file_count);

   // Allocate memory for file sizes array
   file_sizes = (int *) malloc(file_count * sizeof(int));

   // Read file sizes from user input
   for(i = 0; i < file_count; i++) {
      printf("Enter size of file %d: ", i+1);
      scanf("%d", &file_sizes[i]);
      total_file_size += file_sizes[i];
   }

   // Calculate total page size
   total_page_size = (total_file_size / page_size + 1) * page_size;

   // Calculate external fragmentation
   external_fragmentation = total_page_size - total_file_size;

   // Calculate internal fragmentation for each file
   for(i = 0; i < file_count; i++) {
      internal_fragmentation += page_size - (file_sizes[i] % page_size);
   }

   printf("\nTotal file size: %d\n", total_file_size);
   printf("Total page size: %d\n", total_page_size);
   printf("External fragmentation: %d\n", external_fragmentation);
   printf("Internal fragmentation: %d\n", internal_fragmentation);

   // Free memory for file sizes array
   free(file_sizes);

   return 0;
}
