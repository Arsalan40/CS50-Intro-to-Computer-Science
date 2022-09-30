//Problem: to recover JPG from forensic images

#include <stdio.h>
#include <stdlib.h>

//program will take 2 arguments from users and returns images(50) as output.

int main(int argc, char *argv[])
{
    //arguments should be
   if (argc != 2)
   {
      printf("Usage: ./recover IMAGE");
      return 1;
   }
   //opening card.raw file for reading
   
   //fopen function is used to open a file and will return file pointer if successfull
   FILE *file = fopen(argv[1], "r");    //function taking two parameters, card file we want to open in argv[1] and mode operation which is to read(r)
   //if failed to read print error message
   if (file == NULL)
   {
    // returning NULL if failed to open
      printf("Could not open");
      return 1;
   }

   unsigned char buffer[512];       //storing 512 chunks array of memory into a file

   //variable to count images we have found
   int image_count = 0;
   //using pointer of file to output the data from file
   FILE *output = NULL;
   //to name a saved file as 3 char(3 decimal number)
   char *file_name = malloc(8 * sizeof(char));

   //to read data from memory, used fread function as given
   while (fread(buffer, sizeof(char), 512, file) != 0)    //taking 4 arguments, pointer to where storing the read data, size of each element, no of element to read at once, the file where to read data from
   {
      //checking if first 3 bytes are similar to JPG and also checking for the fourth byte
      //if start of new jpg, write it into filename
     if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
     {
        sprintf(file_name, "%03i.jpg", image_count);  // stores a formatted string at a location in memory

        output = fopen(file_name, "w");     //opening new filename to write keep count of the images found

        image_count++;
     }
     //checking if output file is opened earlier, if yes true is returned
     if (output != NULL)
     {
       fwrite(buffer, sizeof(char), 512, output);    //if true writing from buffer to the output file.
     }

   }
   free(file_name);   // free the memory allocated dynamically
   fclose(output);
   fclose(file);
   return 0;
}